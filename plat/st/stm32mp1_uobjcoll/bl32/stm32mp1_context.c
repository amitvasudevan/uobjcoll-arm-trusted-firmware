/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/libc/errno.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/platform_def.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/drivers/st/stm32mp1_clk.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/dt-bindings/clock/stm32mp1-clks.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/mmio.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/stm32mp1_context.h>

#define TAMP_BOOT_ITF_BACKUP_REG_ID	U(20)
#define TAMP_BOOT_ITF_MASK		U(0x0000FF00)
#define TAMP_BOOT_ITF_SHIFT		8

int stm32_save_boot_interface(uint32_t interface, uint32_t instance)
{
	uint32_t bkpr_itf_idx = tamp_bkpr(TAMP_BOOT_ITF_BACKUP_REG_ID);

	stm32mp_clk_enable(RTCAPB);

	mmio_clrsetbits_32(bkpr_itf_idx,
			   TAMP_BOOT_ITF_MASK,
			   ((interface << 4) | (instance & 0xFU)) <<
			   TAMP_BOOT_ITF_SHIFT);

	stm32mp_clk_disable(RTCAPB);

	return 0;
}
