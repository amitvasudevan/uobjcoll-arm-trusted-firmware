/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MICRO_DELAY_H
#define MICRO_DELAY_H

#ifndef __ASSEMBLER__
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stdint.h>
void rcar_micro_delay(uint64_t micro_sec);
#endif

#endif /* MICRO_DELAY_H */
