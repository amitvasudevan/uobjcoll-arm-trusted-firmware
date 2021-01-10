/*
 * Copyright (c) 2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TWED_H
#define TWED_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stdint.h>

#define TWED_DISABLED U(0xFFFFFFFF)

uint32_t plat_arm_set_twedel_scr_el3(void);

#endif /* TWEDE_H */
