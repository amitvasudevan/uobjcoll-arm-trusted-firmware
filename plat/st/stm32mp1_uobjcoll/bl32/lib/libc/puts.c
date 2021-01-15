/*
 * Copyright (c) 2013-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stdio.h>

int puts(const char *s)
{
	int count = 0;

	while (*s != '\0') {
		if (putchar(*s) == EOF)
			return EOF;
		s++;
		count++;
	}

	if (putchar('\n') == EOF)
		return EOF;

	return count + 1;
}
