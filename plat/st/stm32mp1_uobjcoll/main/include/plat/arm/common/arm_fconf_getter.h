/*
 * Copyright (c) 2019-2020, ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ARM_FCONF_GETTER
#define ARM_FCONF_GETTER

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/assert.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/fconf/fconf.h>

/* ARM io policies */
#define arm__io_policies_getter(id) __extension__ ({	\
	assert((id) < MAX_NUMBER_IDS);			\
	&policies[id];					\
})

struct plat_io_policy {
	uintptr_t *dev_handle;
	uintptr_t image_spec;
	int (*check)(const uintptr_t spec);
};

extern struct plat_io_policy policies[];
int fconf_populate_arm_io_policies(uintptr_t config);

#endif /* ARM_FCONF_GETTER */
