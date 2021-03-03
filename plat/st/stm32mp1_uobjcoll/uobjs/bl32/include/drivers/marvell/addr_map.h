/*
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 * https://spdx.org/licenses
 */

/* Address map types for Marvell address translation unit drivers */

#ifndef ADDR_MAP_H
#define ADDR_MAP_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/libc/stdint.h>

struct addr_map_win {
	uint64_t base_addr;
	uint64_t win_size;
	uint32_t target_id;
};

#endif /* ADDR_MAP_H */
