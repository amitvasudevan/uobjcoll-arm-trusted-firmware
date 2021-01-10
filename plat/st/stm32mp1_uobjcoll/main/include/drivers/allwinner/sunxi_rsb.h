/*
 * Copyright (c) 2017-2018 ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SUNXI_RSB_H
#define SUNXI_RSB_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stdint.h>

int rsb_init_controller(void);
int rsb_set_bus_speed(uint32_t source_freq, uint32_t bus_freq);
int rsb_set_device_mode(uint32_t device_mode);
int rsb_assign_runtime_address(uint16_t hw_addr, uint8_t rt_addr);

int rsb_read(uint8_t rt_addr, uint8_t reg_addr);
int rsb_write(uint8_t rt_addr, uint8_t reg_addr, uint8_t value);

#endif /* SUNXI_RSB_H */
