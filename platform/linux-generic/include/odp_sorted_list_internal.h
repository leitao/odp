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

/* Enters the pair <sort_key, user_data> into a list of such entries, all
 * sorted by sort_key (lowest value first with ties going to the oldest
 * entry).  The user_data is an arbitrary/opaque value.  It is returned later
 * when a odp_int_sorted_list_remove() call is made.
 */
int odp_sorted_list_insert(odp_int_sorted_pool_t sorted_pool,
			   odp_int_sorted_list_t sorted_list,
			   uint64_t              sort_key,
			   uint64_t              user_data);

/* The odp_sorted_list_find function returns 1 iff a <sort_key, user_data>
 * pair exists in the linked list whose user_data field matches the given
 * user_data.  If no such entry exists in this list 0 is returned and if the
 * sorted_pool or sorted_list arguments are invalid -1 is returned.
 * If the optional sort_key_ptr argument is supplied, then if the matching
 * entry is found, it's sort_key is returned via this pointer,
 */
int odp_sorted_list_find(odp_int_sorted_pool_t sorted_pool,
                         odp_int_sorted_list_t sorted_list,
                         uint64_t              user_data,
                         uint64_t             *sort_key_ptr);

/* Deletes a <sort_key, user_data> pair from the given sorted list. Returns 0
 * if the pair is found, otherwise returns -1.
 */
int odp_sorted_list_delete(odp_int_sorted_pool_t sorted_pool,
			   odp_int_sorted_list_t sorted_list,
			   uint64_t              user_data);

/* Removes and returns the list entry with the smallest sort_key.  The
 * sort_key is returned via the out ptr sort_key_ptr, and the opaque user data
 * is the return value of odp_int_sorted_list_remove().  Returns -1 if the
 * sorted_list is empty (or upon an error), in which case the value pointed to
 * by sort_key_ptr remains unchanged.
 */
int odp_sorted_list_remove(odp_int_sorted_pool_t sorted_pool,
                           odp_int_sorted_list_t sorted_list,
                           uint64_t             *sort_key_ptr,
                           uint64_t             *user_data_ptr);

void odp_sorted_list_stats_print(odp_int_sorted_pool_t sorted_pool);

void odp_sorted_pool_destroy(odp_int_sorted_pool_t sorted_pool);

#ifdef __cplusplus
}
#endif

#endif
