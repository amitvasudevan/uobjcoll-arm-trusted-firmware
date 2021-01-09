/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/asm_macros.S>

	.globl	semihosting_call

func semihosting_call
	hlt	#0xf000
	ret
endfunc semihosting_call
