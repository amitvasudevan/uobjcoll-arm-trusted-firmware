/*
 * Copyright (c) 2013-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/libc/stddef.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/bl32/include/lib/libc/string.h>

void *memchr(const void *src, int c, size_t len)
{
	const unsigned char *s = src;

	while (len--) {
		if (*s == (unsigned char)c)
			return (void *) s;
		s++;
	}

	return NULL;
}
