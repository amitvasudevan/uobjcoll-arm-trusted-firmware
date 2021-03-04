// SPDX-License-Identifier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2012 David Gibson, IBM Corporation.
 */
#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libfdt/libfdt_env.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libfdt/fdt.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libfdt/libfdt.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libfdt/libfdt_internal.h>

int fdt_create_empty_tree(void *buf, int bufsize)
{
	int err;

	err = fdt_create(buf, bufsize);
	if (err)
		return err;

	err = fdt_finish_reservemap(buf);
	if (err)
		return err;

	err = fdt_begin_node(buf, "");
	if (err)
		return err;

	err =  fdt_end_node(buf);
	if (err)
		return err;

	err = fdt_finish(buf);
	if (err)
		return err;

	return fdt_open_into(buf, buf, bufsize);
}
