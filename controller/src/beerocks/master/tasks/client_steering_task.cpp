/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include "client_steering_task.h"
#include "../db/db_algo.h"
#include "../son_actions.h"
#include "bml_task.h"

#include <beerocks/bcl/network/network_utils.h>
#include <easylogging++.h>

using namespace beerocks;
using namespace net;
using namespace son;

client_steering_task::client_steering_task(db &database_, ieee1905_1::CmduMessageTx &cmdu_tx_,
                                           task_pool &tasks_, std::string sta_mac_,
                                           std::string hostap_mac_, bool disassoc_imminent_,
                                           int disassoc_timer_, bool steer_restricted_,
                                           std::string task_name_)
    : task(task_name_), database(database_), cmdu_tx(cmdu_tx_), tasks(tasks_), sta_mac(sta_mac_),
      hostap_mac(hostap_mac_), //Chosen VAP BSSID to steer the client to
      disassoc_imminent(disassoc_imminent_), disassoc_timer(disassoc_timer_),
      steer_restricted(steer_restricted_)
{
}

void client_steering_task::work()
{
    switch (state) {
    case STEER: {
        int prev_task_id = database.get_steering_task_id(sta_mac);
        tasks.kill_task(prev_task_id);
        database.assign_steering_task_id(sta_mac, id);

        original_hostap_mac = database.get_node_parent(sta_mac);

        steer_sta();

        state = FINALIZE;
        if (steer_restricted) {
            finish();
        }
        wait_for_event(STA_DISCONNECTED);
        set_events_timeout(steering_wait_time_ms);
        break;
    }

    case FINALIZE: {

        if (!steering_success && disassoc_imminent) {
            TASK_LOG(DEBUG) << "steering failed for " << sta_mac << " from " << original_hostap_mac
                            << " to " << hostap_mac;

            /*
                 * might need to split this logic to high and low bands of 5GHz
                 * since some clients can support one but not the other
                 */
            if (database.is_node_24ghz(original_hostap_mac) && database.is_node_5ghz(hostap_mac)) {
                TASK_LOG(DEBUG) << "steering from 2.4GHz to 5GHz failed --> updating failed 5ghz "
                                   "steering attempt";
                database.update_node_failed_5ghz_steer_attempt(sta_mac);
            } else if (database.is_node_5ghz(original_hostap_mac) &&
                       database.is_node_24ghz(hostap_mac)) {
                TASK_LOG(DEBUG) << "steering from 5GHz to 2.4GHz failed, updating failed 2.4ghz "
                                   "steering attempt";
                database.update_node_failed_24ghz_steer_attempt(sta_mac);
            }
        }

        finish();
        break;
    }

    default:
        break;
    }
}

void client_steering_task::steer_sta()
{
    Socket *sta_socket = database.get_node_socket(sta_mac);
    if (database.get_node_type(sta_mac) != beerocks::TYPE_IRE_BACKHAUL) {
        if (!database.set_node_handoff_flag(sta_mac, true)) {
            LOG(ERROR) << "can't set handoff flag for " << sta_mac;
        }
    }

    std::string radio_mac = database.get_node_parent_radio(hostap_mac);

    auto request =
        message_com::create_vs_message<beerocks_message::cACTION_CONTROL_CLIENT_ALLOW_REQUEST>(
            cmdu_tx, id);

    if (request == nullptr) {
        LOG(ERROR) << "Failed building ACTION_CONTROL_CLIENT_ALLOW_REQUEST message!";
        return;
    }
    request->mac()  = network_utils::mac_from_string(sta_mac);
    request->ipv4() = network_utils::ipv4_from_string(database.get_node_ipv4(sta_mac));
    Socket *sd      = database.get_node_socket(radio_mac);
    TASK_LOG(DEBUG) << "sending allow request for " << sta_mac << " to " << radio_mac
                    << " id=" << int(id);
    son_actions::send_cmdu_to_agent(sd, cmdu_tx, radio_mac);

    // update bml listeners
    bml_task::client_allow_req_available_event client_allow_event;
    client_allow_event.sta_mac    = sta_mac;
    client_allow_event.hostap_mac = hostap_mac;
    client_allow_event.ip         = database.get_node_ipv4(sta_mac);
    tasks.push_event(database.get_bml_task_id(), bml_task::CLIENT_ALLOW_REQ_EVENT_AVAILABLE,
                     &client_allow_event);

    if (sta_socket != nullptr && sta_socket->isOpen()) {
        TASK_LOG(DEBUG) << "SLAVE " << sta_mac
                        << " has an active socket, sending BACKHAUL_ROAM_REQUEST";
        auto roam_request =
            message_com::create_vs_message<beerocks_message::cACTION_CONTROL_BACKHAUL_ROAM_REQUEST>(
                cmdu_tx, id);
        if (roam_request == nullptr) {
            LOG(ERROR) << "Failed building message!";
            return;
        }
        roam_request->params().bssid   = network_utils::mac_from_string(hostap_mac);
        roam_request->params().channel = database.get_node_channel(hostap_mac);
        son_actions::send_cmdu_to_agent(sd, cmdu_tx, radio_mac);

        // update bml listeners
        bml_task::bh_roam_req_available_event bh_roam_event;
        bh_roam_event.bssid   = hostap_mac;
        bh_roam_event.channel = database.get_node_channel(hostap_mac);
        tasks.push_event(database.get_bml_task_id(), bml_task::BH_ROAM_REQ_EVENT_AVAILABLE,
                         &bh_roam_event);

        return;
    }

    auto hostaps                   = database.get_active_hostaps();
    std::string original_radio_mac = database.get_node_parent_radio(original_hostap_mac);
    hostaps.erase(radio_mac); // remove chosen hostap from the general list
    for (auto &hostap : hostaps) {
        /*
        * send disallow to all others
        */
        Socket *sd   = database.get_node_socket(hostap);
        auto request = message_com::create_vs_message<
            beerocks_message::cACTION_CONTROL_CLIENT_DISALLOW_REQUEST>(cmdu_tx, id);

        if (request == nullptr) {
            LOG(ERROR) << "Failed building ACTION_CONTROL_CLIENT_DISALLOW_REQUEST message!";
            return;
        }
        request->mac() = network_utils::mac_from_string(sta_mac);
        /*
        * Only for the original hostap, add error code "33" to signal hostap that we want to continue 
        * to hear BTM response from client.
        */
        request->reject_sta() = (hostap == original_radio_mac) ? 33 : 0;

        son_actions::send_cmdu_to_agent(sd, cmdu_tx, hostap);
        TASK_LOG(DEBUG) << "sending disallow request for " << sta_mac << " to " << hostap
                        << " id=" << int(id) << " reject_sta=" << int(request->reject_sta());

        // update bml listeners
        bml_task::client_disallow_req_available_event client_disallow_event;
        client_disallow_event.sta_mac    = sta_mac;
        client_disallow_event.hostap_mac = hostap;
        tasks.push_event(database.get_bml_task_id(), bml_task::CLIENT_DISALLOW_REQ_EVENT_AVAILABLE,
                         &client_disallow_event);
    }

    // Send disconnect (802.11v)
    auto bss_steer_request =
        message_com::create_vs_message<beerocks_message::cACTION_CONTROL_CLIENT_BSS_STEER_REQUEST>(
            cmdu_tx, id);

    if (bss_steer_request == nullptr) {
        LOG(ERROR) << "Failed building ACTION_CONTROL_CLIENT_BSS_STEER_REQUEST message!";
        return;
    }
    bss_steer_request->params().mac            = network_utils::mac_from_string(sta_mac);
    bss_steer_request->params().disassoc_timer = disassoc_timer;
    bss_steer_request->params().bssid.mac      = network_utils::mac_from_string(hostap_mac);
    bss_steer_request->params().bssid.channel  = database.get_node_channel(hostap_mac);

    if (disassoc_imminent) {
        TASK_LOG(DEBUG) << "diassoc_imminent enabled";
        bss_steer_request->params().disassoc_imminent = 1;
    } else {
        TASK_LOG(DEBUG) << "diassoc_imminent disabled";
        bss_steer_request->params().disassoc_imminent = 0;
    }

    auto current_ap_mac = database.get_node_parent(sta_mac);

    sd = database.get_node_socket(current_ap_mac);
    son_actions::send_cmdu_to_agent(sd, cmdu_tx, original_radio_mac);
    TASK_LOG(DEBUG) << "sending 11v bss steer request, sta " << sta_mac << " steer from AP "
                    << current_ap_mac << " to AP " << hostap_mac << " channel "
                    << std::to_string(bss_steer_request->params().bssid.channel)
                    << " id=" << int(id)
                    << " disassoc_imminent=" << int(bss_steer_request->params().disassoc_imminent);

    // update bml listeners
    bml_task::bss_tm_req_available_event bss_tm_event;
    bss_tm_event.target_bssid      = hostap_mac;
    bss_tm_event.disassoc_imminent = bss_steer_request->params().disassoc_imminent;
    tasks.push_event(database.get_bml_task_id(), bml_task::BSS_TM_REQ_EVENT_AVAILABLE,
                     &bss_tm_event);
}

void client_steering_task::handle_event(int event_type, void *obj)
{
    if (event_type == STA_CONNECTED) {
        TASK_LOG(DEBUG) << "steering successful for sta " << sta_mac;
        steering_success = true;
    } else if (event_type == STA_DISCONNECTED) {
        TASK_LOG(DEBUG) << "sta " << sta_mac
                        << " disconnected after successful steering, proceeding to unblock";
    } else if (event_type == BSS_TM_REQUEST_REJECTED) {
        TASK_LOG(DEBUG) << "sta " << sta_mac << " rejected BSS_TM request";
        if (disassoc_imminent) {
            TASK_LOG(DEBUG) << "disassoc_imminent flag is true, proceeding as usual";
        } else {
            TASK_LOG(DEBUG) << "aborting task";
            finish();
        }
    } else if (event_type == BSS_TM_RESPONSE_RECEIVED) {
        bss_tm_response_received = true;
    }
}

void client_steering_task::handle_task_end()
{
    if (!bss_tm_response_received) {
        TASK_LOG(DEBUG) << "node didn't respond to 11v request, updating failed attempt";
        database.update_node_11v_responsiveness(sta_mac, false);
    }
    database.set_node_handoff_flag(sta_mac, false);
    if (!steer_restricted) {
        son_actions::unblock_sta(database, cmdu_tx, sta_mac);
    }
}
