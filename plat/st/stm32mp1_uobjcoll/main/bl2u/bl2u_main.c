/*
 * Copyright (c) 2015-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/assert.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stdint.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/platform_def.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/arch/arch.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/arch/arch_helpers.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/bl1/bl1.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/bl2u/bl2u.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/common/bl_common.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/common/debug.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/auth/auth_mod.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/console.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/plat/common/platform.h>

/*******************************************************************************
 * This function is responsible to:
 * Load SCP_BL2U if platform has defined SCP_BL2U_BASE
 * Perform platform setup.
 * Go back to EL3.
 ******************************************************************************/
void bl2u_main(void)
{
	NOTICE("BL2U: %s\n", version_string);
	NOTICE("BL2U: %s\n", build_message);

#if SCP_BL2U_BASE
	int rc;
	/* Load the subsequent bootloader images */
	rc = bl2u_plat_handle_scp_bl2u();
	if (rc != 0) {
		ERROR("Failed to load SCP_BL2U (%i)\n", rc);
		panic();
	}
#endif

	/* Perform platform setup in BL2U after loading SCP_BL2U */
	bl2u_platform_setup();

	console_flush();

#ifndef __aarch64__
	/*
	 * For AArch32 state BL1 and BL2U share the MMU setup.
	 * Given that BL2U does not map BL1 regions, MMU needs
	 * to be disabled in order to go back to BL1.
	 */
	disable_mmu_icache_secure();
#endif /* !__aarch64__ */

	/*
	 * Indicate that BL2U is done and resume back to
	 * normal world via an SMC to BL1.
	 * x1 could be passed to Normal world,
	 * so DO NOT pass any secret information.
	 */
	smc(FWU_SMC_SEC_IMAGE_DONE, 0, 0, 0, 0, 0, 0, 0);
	wfi();
}
