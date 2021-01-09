/*
 * Copyright (c) 2018-2019, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/errno.h>
#include <uberspark/uobjrtl/crt/include/limits.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/platform_def.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/common/bl_common.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/common/debug.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/delay_timer.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/st/stm32mp_reset.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/mmio.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/utils_def.h>

static uint32_t id2reg_offset(unsigned int reset_id)
{
	return ((reset_id & GENMASK(31, 5)) >> 5) * sizeof(uint32_t);
}

static uint8_t id2reg_bit_pos(unsigned int reset_id)
{
	return (uint8_t)(reset_id & GENMASK(4, 0));
}

int stm32mp_reset_assert(uint32_t id, unsigned int to_us)
{
	uint32_t offset = id2reg_offset(id);
	uint32_t bitmsk = BIT(id2reg_bit_pos(id));
	uintptr_t rcc_base = stm32mp_rcc_base();

	mmio_write_32(rcc_base + offset, bitmsk);

	if (to_us != 0U) {
		uint64_t timeout_ref = timeout_init_us(to_us);

		while ((mmio_read_32(rcc_base + offset) & bitmsk) == 0U) {
			if (timeout_elapsed(timeout_ref)) {
				return -ETIMEDOUT;
			}
		}
	}

	return 0;
}

int stm32mp_reset_deassert(uint32_t id, unsigned int to_us)
{
	uint32_t offset = id2reg_offset(id) + RCC_RSTCLRR_OFFSET;
	uint32_t bitmsk = BIT(id2reg_bit_pos(id));
	uintptr_t rcc_base = stm32mp_rcc_base();

	mmio_write_32(rcc_base + offset, bitmsk);

	if (to_us != 0U) {
		uint64_t timeout_ref = timeout_init_us(to_us);

		while ((mmio_read_32(rcc_base + offset) & bitmsk) != 0U) {
			if (timeout_elapsed(timeout_ref)) {
				return -ETIMEDOUT;
			}
		}
	}

	return 0;
}
