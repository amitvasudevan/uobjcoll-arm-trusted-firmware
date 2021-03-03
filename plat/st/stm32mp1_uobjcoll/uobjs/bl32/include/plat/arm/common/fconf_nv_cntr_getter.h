/*
 * Copyright (c) 2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FCONF_NV_CNTR_GETTER_H
#define FCONF_NV_CNTR_GETTER_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/common/nv_cntr_ids.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/fconf/fconf.h>

#define cot__nv_cntr_addr_getter(id)		nv_cntr_base_addr[id]

extern uintptr_t nv_cntr_base_addr[MAX_NV_CTR_IDS];

#endif /* FCONF_NV_CNTR_GETTER_H */
