/*
 * Copyright (c) 2012-2017 Roberto E. Vargas Caballero
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*
 * Portions copyright (c) 2018-2019, ARM Limited and Contributors.
 * All rights reserved.
 */

#ifndef STDIO_H
#define STDIO_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/cdefs.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stddef.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/aarch32/stdio_.h>

#define EOF            -1

int printf(const char *fmt, ...) __printflike(1, 2);
int snprintf(char *s, size_t n, const char *fmt, ...) __printflike(3, 4);

#ifdef STDARG_H
int vprintf(const char *fmt, va_list args);
int vsnprintf(char *s, size_t n, const char *fmt, va_list args);
#endif

int putchar(int c);
int puts(const char *s);

#endif /* STDIO_H */
