///////////////////////////////////////
// AUTO GENERATED FILE - DO NOT EDIT //
///////////////////////////////////////

/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _TLVF_WSC_EWSCLENGTHS_H_
#define _TLVF_WSC_EWSCLENGTHS_H_

#include <cstddef>
#include <stdint.h>
#include <tlvf/swap.h>

namespace WSC {

enum eWscLengths: uint16_t {
    WSC_MAC_LENGTH = 0x6,
    WSC_NONCE_LENGTH = 0x10,
    WSC_UUID_LENGTH = 0x10,
    WSC_VENDOR_EXTENSIONS_LENGTH = 0x6,
    WSC_PRIMARY_DEV_TYPE_LENGTH = 0x8,
    WSC_PRIMARY_DEV_TYPE_OUI_LENGTH = 0x4,
    WSC_OS_VERSION_LENGTH = 0x4,
    WSC_MAX_NAME_LENGTH = 0x20,
    WSC_MAX_NETWORK_KEY_LENGTH = 0x40,
    WSC_PUBLIC_KEY_LENGTH = 0xc0,
    WSC_KEY_WRAP_AUTH_LENGTH = 0x8,
};


}; // close namespace: WSC

#endif //_TLVF/WSC_EWSCLENGTHS_H_