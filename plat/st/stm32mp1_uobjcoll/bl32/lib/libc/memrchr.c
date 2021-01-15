/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/string.h>

#undef memrchr

void *memrchr(const void *src, int c, size_t len)
{
	const unsigned char *s = src + (len - 1);

	while (len--) {
		if (*s == (unsigned char)c) {
			return (void*) s;
		}

		s--;
	}

	return NULL;
}
