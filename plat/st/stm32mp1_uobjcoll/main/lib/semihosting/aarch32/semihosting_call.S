/*
 * Copyright (c) 2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/arch/asm_macros.S>

	.globl	semihosting_call

func semihosting_call
	svc	#0x123456
	bx	lr
endfunc semihosting_call
