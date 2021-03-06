/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include "../../bpl_cfg.h"
#include "../../common/utils/utils.h"

#include <mapf/common/logger.h>

// BRCM utils
extern "C" {
#include <bwl_utils.h>
#include <wlioctl.h>
}

using namespace beerocks::bpl;

int bpl_cfg_is_enabled() { return 1; }

int bpl_cfg_is_master() { return 0; }

int bpl_cfg_get_operating_mode() { return BPL_OPER_MODE_GATEWAY; }

int bpl_cfg_is_onboarding() { return 0; }

int bpl_cfg_is_wired_backhaul() { return 0; }

int bpl_cfg_get_band_steering() { return 0; }

int bpl_cfg_get_rdkb_extensions() { return 0; }

int bpl_cfg_get_dfs_reentry() { return 0; }

int bpl_cfg_get_passive_mode() { return 0; }

int bpl_cfg_get_client_roaming() { return 0; }

int bpl_cfg_get_wifi_params(const char *iface, int *enabled, int *acs, int *advertise_ssid)
{
    *enabled        = 1;
    *acs            = 0;
    *advertise_ssid = 1;

    return 0;
}

int bpl_cfg_get_backhaul_params(int *max_vaps, int *network_enabled, int *prefered_radio_band)
{
    *max_vaps            = 0;
    *network_enabled     = 0;
    *prefered_radio_band = 0;
    return 0;
}
int bpl_cfg_get_backhaul_vaps(char *backhaul_vaps_buf, const int buf_len) { return 0; }
int bpl_cfg_get_wifi_credentials(const int radio_dir, char ssid[BPL_SSID_LEN],
                                 char pass[BPL_PASS_LEN], char sec[BPL_SEC_LEN])
{
    std::string str_ssid, str_pass, str_sec;

    // TODO: Use constants for sizes
    if (ssid)
        utils::copy_string(ssid, str_ssid.c_str(), BPL_SSID_LEN);
    if (pass)
        utils::copy_string(pass, str_pass.c_str(), BPL_PASS_LEN);
    if (sec)
        utils::copy_string(sec, str_sec.c_str(), BPL_SEC_LEN);

    return 0;
}

int bpl_cfg_set_wifi_credentials(const int radio_dir, const char ssid[BPL_SSID_LEN],
                                 const char pass[BPL_PASS_LEN], const char sec[BPL_SEC_LEN])
{
    return -1;
}

int bpl_cfg_notify_fw_version_mismatch() { return -1; }

int bpl_cfg_notify_error(int code, const char data[BPL_ERROR_STRING_LEN]) { return -1; }

int bpl_cfg_set_wifi_iface_state(const char iface[BPL_IFNAME_LEN], int op) { return 0; }

int bpl_cfg_set_wifi_radio_tx_state(const char iface[BPL_IFNAME_LEN], int enable)
{
    uint32_t val = 0;

    if (enable) {
        val |= WL_RADIO_SW_DISABLE << 16;
    } else {
        val = WL_RADIO_SW_DISABLE << 16 | WL_RADIO_SW_DISABLE;
    }

    int ret = bwl_wl_ioctl((char *)iface, WLC_SET_RADIO, &val, sizeof(val));
    if (ret < 0) {
        MAPF_DBG("WLC_SET_RADIO failed: " << ret);
        return -1;
    }

    return 0;
}

int bpl_cfg_notify_iface_status(const BPL_INTERFACE_STATUS_NOTIFICATION *status_notif) { return 0; }
