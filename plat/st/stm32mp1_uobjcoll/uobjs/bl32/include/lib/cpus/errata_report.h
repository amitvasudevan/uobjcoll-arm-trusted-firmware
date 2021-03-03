/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ERRATA_REPORT_H
#define ERRATA_REPORT_H

#ifndef __ASSEMBLER__

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/arch/arch.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/arch/arch_helpers.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/spinlock.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/utils_def.h>

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_DEBUG__
void print_errata_status(void);
#else
static inline void print_errata_status(void) {}
#endif

void errata_print_msg(unsigned int status, const char *cpu, const char *id);
int errata_needs_reporting(spinlock_t *lock, uint32_t *reported);

#endif /* __ASSEMBLER__ */

/* Errata status */
#define ERRATA_NOT_APPLIES	0
#define ERRATA_APPLIES		1
#define ERRATA_MISSING		2

#endif /* ERRATA_REPORT_H */
