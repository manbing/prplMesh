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

#ifndef _TLVF_IEEE_1905_1_TLVWSCM1_H_
#define _TLVF_IEEE_1905_1_TLVWSCM1_H_

#include <cstddef>
#include <stdint.h>
#include <tlvf/swap.h>
#include <string.h>
#include <memory>
#include <tlvf/BaseClass.h>
#include "tlvf/ieee_1905_1/eTlvType.h"
#include "tlvf/WSC/sM1.h"

namespace ieee1905_1 {


class tlvWscM1 : public BaseClass
{
    public:
        tlvWscM1(uint8_t* buff, size_t buff_len, bool parse = false, bool swap_needed = false);
        tlvWscM1(std::shared_ptr<BaseClass> base, bool parse = false, bool swap_needed = false);
        ~tlvWscM1();

        const eTlvType& type();
        const uint16_t& length();
        WSC::sM1& M1Frame();
        void class_swap();
        static size_t get_initial_size();

    private:
        bool init();
        eTlvType* m_type = nullptr;
        uint16_t* m_length = nullptr;
        WSC::sM1* m_M1Frame = nullptr;
};

}; // close namespace: ieee1905_1

#endif //_TLVF/IEEE_1905_1_TLVWSCM1_H_
