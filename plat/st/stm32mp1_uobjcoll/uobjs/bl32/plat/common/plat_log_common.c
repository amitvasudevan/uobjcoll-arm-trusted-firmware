/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/common/debug.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/plat/common/platform.h>

/* Allow platforms to override the log prefix string */
#pragma weak plat_log_get_prefix

static const char *plat_prefix_str[] = {
	"ERROR:   ", "NOTICE:  ", "WARNING: ", "INFO:    ", "VERBOSE: "};

const char *plat_log_get_prefix(unsigned int log_level)
{
	unsigned int level;

	if (log_level < LOG_LEVEL_ERROR) {
		level = LOG_LEVEL_ERROR;
	} else if (log_level > LOG_LEVEL_VERBOSE) {
		level = LOG_LEVEL_VERBOSE;
	} else {
		level = log_level;
	}

	return plat_prefix_str[(level / 10U) - 1U];
}
