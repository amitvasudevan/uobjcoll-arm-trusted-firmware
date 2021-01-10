/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CORTEX_A9_H
#define CORTEX_A9_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/utils_def.h>

/*******************************************************************************
 * Cortex-A9 midr with version/revision set to 0
 ******************************************************************************/
#define CORTEX_A9_MIDR			U(0x410FC090)

/*******************************************************************************
 * CPU Auxiliary Control register specific definitions.
 ******************************************************************************/
#define CORTEX_A9_ACTLR_SMP_BIT		(U(1) << 6)
#define CORTEX_A9_ACTLR_FLZW_BIT	(U(1) << 3)

/*******************************************************************************
 * CPU Power Control Register
 ******************************************************************************/
#define PCR		p15, 0, c15, c0, 0

#ifndef __ASSEMBLER__
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/arch/arch_helpers.h>
DEFINE_COPROCR_RW_FUNCS(pcr, PCR)
#endif

#endif /* CORTEX_A9_H */
