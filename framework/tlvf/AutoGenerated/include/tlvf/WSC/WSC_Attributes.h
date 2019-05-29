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

#ifndef _TLVF_WSC_WSC_ATTRIBUTES_H_
#define _TLVF_WSC_WSC_ATTRIBUTES_H_

#include <cstddef>
#include <stdint.h>
#include <tlvf/swap.h>
#include "tlvf/WSC/eWscAttributes.h"
#include "tlvf/WSC/eWscValues8.h"
#include "tlvf/WSC/eWscConn.h"
#include "tlvf/WSC/eWscState.h"
#include "tlvf/WSC/eWscRfBands.h"
#include "tlvf/WSC/eWscAssoc.h"
#include "tlvf/WSC/eWscValues16.h"
#include "tlvf/WSC/eWscLengths.h"

namespace WSC {

typedef struct sWscAttrVersion {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscValues8 data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_VERSION;
        data_length = 0x1;
        data = WSC_VERSION;
    }
} sWscAttrVersion;

typedef struct sWscAttrMessageType {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscValues8 data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_MSG_TYPE;
        data_length = 0x1;
        data = WSC_M1;
    }
} sWscAttrMessageType;

typedef struct sWscAttrUuidE {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_UUID_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_UUID_E;
        data_length = WSC_UUID_LENGTH;
    }
} sWscAttrUuidE;

typedef struct sWscAttrUuidR {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_UUID_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_UUID_E;
        data_length = WSC_UUID_LENGTH;
    }
} sWscAttrUuidR;

typedef struct sWscAttrMac {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_MAC_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_MAC_ADDR;
        data_length = WSC_MAC_LENGTH;
    }
} sWscAttrMac;

typedef struct sWscAttrEnroleeNonce {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_NONCE_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_ENROLLEE_NONCE;
        data_length = WSC_NONCE_LENGTH;
    }
} sWscAttrEnroleeNonce;

typedef struct sWscAttrRegistrarNonce {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_NONCE_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_REGISTRAR_NONCE;
        data_length = WSC_NONCE_LENGTH;
    }
} sWscAttrRegistrarNonce;

typedef struct sWscAttrPublicKey {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_PUBLIC_KEY_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_PUBLIC_KEY;
        data_length = WSC_PUBLIC_KEY_LENGTH;
    }
} sWscAttrPublicKey;

typedef struct sWscAttrAuthenticationTypeFlags {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint16_t data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_AUTH_TYPE_FLAGS;
        data_length = 0x2;
    }
} sWscAttrAuthenticationTypeFlags;

typedef struct sWscAttrEncryptionTypeFlags {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint16_t data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_ENCR_TYPE_FLAGS;
        data_length = 0x2;
    }
} sWscAttrEncryptionTypeFlags;

typedef struct sWscAttrConnectionTypeFlags {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscConn data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_CONN_TYPE_FLAGS;
        data_length = 0x1;
        data = WSC_CONN_ESS;
    }
} sWscAttrConnectionTypeFlags;

typedef struct sWscAttrConfigurationMethods {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint16_t data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_CONFIG_METHODS;
        data_length = 0x2;
        data = (WSC_CONFIG_PHY_PUSHBUTTON | WSC_CONFIG_VIRT_PUSHBUTTON);
    }
} sWscAttrConfigurationMethods;

typedef struct sWscAttrWscState {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscState data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_WSC_STATE;
        data_length = 0x1;
        data = WSC_STATE_NOT_CONFIGURED;
    }
} sWscAttrWscState;

typedef struct sWscAttrManufacturer {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NAME_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_MANUFACTURER;
        data_length = WSC_MAX_NAME_LENGTH;
    }
} sWscAttrManufacturer;

typedef struct sWscAttrModelName {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NAME_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_MODEL_NAME;
        data_length = WSC_MAX_NAME_LENGTH;
    }
} sWscAttrModelName;

typedef struct sWscAttrModelNumber {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NAME_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_MODEL_NUMBER;
        data_length = WSC_MAX_NAME_LENGTH;
    }
} sWscAttrModelNumber;

typedef struct sWscAttrSerialNumber {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NAME_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_SERIAL_NUMBER;
        data_length = WSC_MAX_NAME_LENGTH;
    }
} sWscAttrSerialNumber;

typedef struct sWscAttrPrimaryDeviceType {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint16_t category_id;
    uint8_t oui[WSC_PRIMARY_DEV_TYPE_OUI_LENGTH];
    uint16_t sub_category_id;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&category_id));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&sub_category_id));
    }
    void struct_init(){
        attribute_type = ATTR_PRIMARY_DEV_TYPE;
        data_length = WSC_PRIMARY_DEV_TYPE_LENGTH;
    }
} sWscAttrPrimaryDeviceType;

typedef struct sWscAttrDeviceName {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NAME_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_DEV_NAME;
        data_length = WSC_MAX_NAME_LENGTH;
    }
} sWscAttrDeviceName;

typedef struct sWscAttrRfBands {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscRfBands data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_RF_BANDS;
        data_length = 0x1;
    }
} sWscAttrRfBands;

typedef struct sWscAttrAssociationState {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscAssoc data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_ASSOC_STATE;
        data_length = 0x1;
        data = WSC_ASSOC_NOT_ASSOC;
    }
} sWscAttrAssociationState;

typedef struct sWscAttrDevicePasswordID {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscValues16 data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_DEV_PASSWORD_ID;
        data_length = 0x2;
        data = DEV_PW_PUSHBUTTON;
    }
} sWscAttrDevicePasswordID;

typedef struct sWscAttrConfigurationError {
    eWscAttributes attribute_type;
    uint16_t data_length;
    eWscValues16 data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_CONFIG_ERROR;
        data_length = 0x2;
        data = WSC_CFG_NO_ERROR;
    }
} sWscAttrConfigurationError;

typedef struct sWscAttrOsVersion {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint32_t data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(32, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_OS_VERSION;
        data_length = WSC_OS_VERSION_LENGTH;
        data = 0x80000001;
    }
} sWscAttrOsVersion;

typedef struct sWscAttrVersionExtension {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_VENDOR_EXTENSIONS_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_VENDOR_EXTENSION;
        data_length = WSC_VENDOR_EXTENSIONS_LENGTH;
    }
} sWscAttrVersionExtension;

typedef struct sWscAttrKeyWrapAuthenticator {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint8_t data[WSC_KEY_WRAP_AUTH_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_KEY_WRAP_AUTH;
        data_length = WSC_KEY_WRAP_AUTH_LENGTH;
    }
} sWscAttrKeyWrapAuthenticator;

typedef struct sWscAttrSsid {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NAME_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_SSID;
        data_length = WSC_MAX_NAME_LENGTH;
    }
} sWscAttrSsid;

typedef struct sWscAttrAuthenticationType {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint16_t data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_AUTH_TYPE;
        data_length = 0x2;
    }
} sWscAttrAuthenticationType;

typedef struct sWscAttrEncryptionType {
    eWscAttributes attribute_type;
    uint16_t data_length;
    uint16_t data;
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data));
    }
    void struct_init(){
        attribute_type = ATTR_ENCR_TYPE;
        data_length = 0x2;
    }
} sWscAttrEncryptionType;

typedef struct sWscAttrNetworkKey {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAX_NETWORK_KEY_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_NETWORK_KEY;
        data_length = WSC_MAX_NETWORK_KEY_LENGTH;
    }
} sWscAttrNetworkKey;

typedef struct sWscAttrBssid {
    eWscAttributes attribute_type;
    uint16_t data_length;
    char data[WSC_MAC_LENGTH];
    void struct_swap(){
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&attribute_type));
        tlvf_swap(16, reinterpret_cast<uint8_t*>(&data_length));
    }
    void struct_init(){
        attribute_type = ATTR_MAC_ADDR;
        data_length = WSC_MAC_LENGTH;
    }
} sWscAttrBssid;


}; // close namespace: WSC

#endif //_TLVF/WSC_WSC_ATTRIBUTES_H_
