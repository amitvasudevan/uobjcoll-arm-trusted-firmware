/*
 * Copyright (c) 2013-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/assert.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/arch/arch_helpers.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/features.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/bl1/bl1.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/bl2/bl2.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/common/bl_common.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/common/debug.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/auth/auth_mod.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/console.h>
#if __UBERSPARK_UOBJCOLL_CONFIGDEF_MEASURED_BOOT__
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/drivers/measured_boot/measured_boot.h>
#endif
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/extensions/pauth.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/plat/common/platform.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/bl2/bl2_private.h>

#ifdef __aarch64__
#define NEXT_IMAGE	"BL31"
#else
#define NEXT_IMAGE	"BL32"
#endif

#if !__UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__
/*******************************************************************************
 * Setup function for BL2.
 ******************************************************************************/
void bl2_setup(u_register_t arg0, u_register_t arg1, u_register_t arg2,
	       u_register_t arg3)
{
	/* Perform early platform-specific setup */
	bl2_early_platform_setup2(arg0, arg1, arg2, arg3);

	/* Perform late platform-specific setup */
	bl2_plat_arch_setup();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_CTX_INCLUDE_PAUTH_REGS__
	/*
	 * Assert that the ARMv8.3-PAuth registers are present or an access
	 * fault will be triggered when they are being saved or restored.
	 */
	assert(is_armv8_3_pauth_present());
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_CTX_INCLUDE_PAUTH_REGS__ */
}

#else /* if __UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__ */
/*******************************************************************************
 * Setup function for BL2 when __UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__=1.
 ******************************************************************************/
void bl2_el3_setup(u_register_t arg0, u_register_t arg1, u_register_t arg2,
		   u_register_t arg3)
{
	/* Perform early platform-specific setup */
	bl2_el3_early_platform_setup(arg0, arg1, arg2, arg3);

	/* Perform late platform-specific setup */
	bl2_el3_plat_arch_setup();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_CTX_INCLUDE_PAUTH_REGS__
	/*
	 * Assert that the ARMv8.3-PAuth registers are present or an access
	 * fault will be triggered when they are being saved or restored.
	 */
	assert(is_armv8_3_pauth_present());
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_CTX_INCLUDE_PAUTH_REGS__ */
}
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__ */

/*******************************************************************************
 * The only thing to do in BL2 is to load further images and pass control to
 * next BL. The memory occupied by BL2 will be reclaimed by BL3x stages. BL2
 * runs entirely in S-EL1.
 ******************************************************************************/
void bl2_main(void)
{
	entry_point_info_t *next_bl_ep_info;

	NOTICE("BL2: %s\n", version_string);
	NOTICE("BL2: %s\n", build_message);

	/* Perform remaining generic architectural setup in S-EL1 */
	bl2_arch_setup();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_TRUSTED_BOARD_BOOT__
	/* Initialize authentication module */
	auth_mod_init();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_MEASURED_BOOT__
	/* Initialize measured boot module */
	measured_boot_init();

#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_MEASURED_BOOT__ */
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_TRUSTED_BOARD_BOOT__ */

	/* Initialize boot source */
	bl2_plat_preload_setup();

	/* Load the subsequent bootloader images. */
	next_bl_ep_info = bl2_load_images();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_MEASURED_BOOT__
	/* Finalize measured boot */
	measured_boot_finish();
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_MEASURED_BOOT__ */

#if !__UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__
#ifndef __aarch64__
	/*
	 * For AArch32 state BL1 and BL2 share the MMU setup.
	 * Given that BL2 does not map BL1 regions, MMU needs
	 * to be disabled in order to go back to BL1.
	 */
	disable_mmu_icache_secure();
#endif /* !__aarch64__ */

	console_flush();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_ENABLE_PAUTH__
	/*
	 * Disable pointer authentication before running next boot image
	 */
	pauth_disable_el1();
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_ENABLE_PAUTH__ */

	/*
	 * Run next BL image via an SMC to BL1. Information on how to pass
	 * control to the BL32 (if present) and BL33 software images will
	 * be passed to next BL image as an argument.
	 */
	smc(BL1_SMC_RUN_IMAGE, (unsigned long)next_bl_ep_info, 0, 0, 0, 0, 0, 0);
#else /* if __UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__ */
	NOTICE("BL2: Booting " NEXT_IMAGE "\n");
	print_entry_point_info(next_bl_ep_info);
	console_flush();

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_ENABLE_PAUTH__
	/*
	 * Disable pointer authentication before running next boot image
	 */
	pauth_disable_el3();
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_ENABLE_PAUTH__ */

	bl2_run_next_image(next_bl_ep_info);
#endif /* __UBERSPARK_UOBJCOLL_CONFIGDEF_BL2_AT_EL3__ */
}
