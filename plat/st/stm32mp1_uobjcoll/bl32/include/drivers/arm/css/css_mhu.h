/*
 * Copyright (c) 2014-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CSS_MHU_H
#define CSS_MHU_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/libc/stdint.h>

void mhu_secure_message_start(unsigned int slot_id);
void mhu_secure_message_send(unsigned int slot_id);
uint32_t mhu_secure_message_wait(void);
void mhu_secure_message_end(unsigned int slot_id);

void mhu_secure_init(void);

#endif /* CSS_MHU_H */
