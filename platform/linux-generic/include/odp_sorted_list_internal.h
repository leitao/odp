/* Copyright 2015 EZchip Semiconductor Ltd. All Rights Reserved.
 *
 * Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ODP_INT_SORTED_LIST_H_
#define ODP_INT_SORTED_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint64_t odp_int_sorted_pool_t;
typedef uint32_t odp_int_sorted_list_t;

#define ODP_INT_SORTED_POOL_INVALID  0
#define ODP_INT_SORTED_LIST_INVALID  0

odp_int_sorted_pool_t odp_sorted_pool_create(uint32_t max_sorted_lists);

odp_int_sorted_list_t odp_sorted_list_create(odp_int_sorted_pool_t sorted_pool,
					     uint32_t              max_entries);

/* Enters the pair <sort_key, user_ptr> into a list of such entries, all
 * sorted by sort_key (lowest value first with ties going to the oldest
 * entry).  The user_ptr is an arbitrary/opaque value.  It is returned later
 * (along with the associated sort_key) when a odp_int_sorted_list_remove()
 * call is made.
 */
int odp_sorted_list_insert(odp_int_sorted_pool_t sorted_pool,
			   odp_int_sorted_list_t sorted_list,
			   uint64_t              sort_key,
			   void                 *user_ptr);

/* Removes and returns the list entry with the smallest sort_key.  The
 * sort_key is returned via the out ptr sort_key_ptr, and the opaque user ptr
 * is the return value of odp_int_sorted_list_remove().  Returns NULL if the
 * sorted_list is empty (or upon an error), in which case the value pointed to
 * by sort_key_ptr remains unchanged.
 */
void *odp_sorted_list_remove(odp_int_sorted_pool_t sorted_pool,
			     odp_int_sorted_list_t sorted_list,
			     uint64_t             *sort_key_ptr);

void odp_sorted_list_stats_print(odp_int_sorted_pool_t sorted_pool);

void odp_sorted_pool_destroy(odp_int_sorted_pool_t sorted_pool);

#ifdef __cplusplus
}
#endif

#endif