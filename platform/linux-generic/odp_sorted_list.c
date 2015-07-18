/* Copyright 2015 EZchip Semiconductor Ltd. All Rights Reserved.
 *
 * Copyright (c) 2015, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <odp.h>
#include <odp_sorted_list_internal.h>

typedef struct sorted_list_item_s sorted_list_item_t;

struct sorted_list_item_s {
	sorted_list_item_t *next_item;
	uint64_t            sort_key;
	uint64_t            user_data;
};

typedef struct {
	sorted_list_item_t *first_item;
	uint32_t            sorted_list_len;
	uint32_t            pad;
} sorted_list_desc_t;

typedef struct {
	sorted_list_desc_t descs[0];
} sorted_list_descs_t;

typedef struct {
	uint64_t             total_inserts;
	uint64_t             total_removes;
	uint32_t             max_sorted_lists;
	uint32_t             next_list_idx;
	sorted_list_descs_t *list_descs;
} sorted_pool_t;

odp_int_sorted_pool_t odp_sorted_pool_create(uint32_t max_sorted_lists)
{
	sorted_list_descs_t *list_descs;
	sorted_pool_t       *pool;
	uint32_t             malloc_len;

	pool = malloc(sizeof(sorted_pool_t));
	memset(pool, 0, sizeof(sorted_pool_t));
	pool->max_sorted_lists = max_sorted_lists;
	pool->next_list_idx    = 1;

	malloc_len = max_sorted_lists * sizeof(sorted_list_desc_t);
	list_descs = malloc(malloc_len);
	memset(list_descs, 0, malloc_len);
	pool->list_descs = list_descs;
	return (odp_int_sorted_pool_t)pool;
}

odp_int_sorted_list_t odp_sorted_list_create(odp_int_sorted_pool_t sorted_pool,
					     uint32_t max_entries ODP_UNUSED)
{
	sorted_pool_t *pool;
	uint32_t       list_idx;

	pool     = (sorted_pool_t *)sorted_pool;
	list_idx = pool->next_list_idx++;
	return (odp_int_sorted_list_t)list_idx;
}

int odp_sorted_list_insert(odp_int_sorted_pool_t sorted_pool,
			   odp_int_sorted_list_t sorted_list,
			   uint64_t              sort_key,
			   void                 *user_ptr)
{
	sorted_list_desc_t *list_desc;
	sorted_list_item_t *new_list_item, *list_item, *prev_list_item;
	sorted_pool_t      *pool;
	uint32_t            list_idx;

	pool     = (sorted_pool_t *)sorted_pool;
	list_idx = (uint32_t)sorted_list;
	if ((pool->next_list_idx    <= list_idx) ||
	    (pool->max_sorted_lists <= list_idx))
		return -1;

	list_desc     = &pool->list_descs->descs[list_idx];
	new_list_item = malloc(sizeof(sorted_list_item_t));
	memset(new_list_item, 0, sizeof(sorted_list_item_t));
	new_list_item->next_item = NULL;
	new_list_item->sort_key  = sort_key;
	new_list_item->user_data = (uint64_t)user_ptr;

	/* Now insert the new_list_item according to the sort_key (lowest
	 * value first).
	 */
	list_item      = list_desc->first_item;
	prev_list_item = NULL;
	while ((list_item) && (list_item->sort_key <= sort_key)) {
		prev_list_item = list_item;
		list_item      = list_item->next_item;
	}

	new_list_item->next_item = list_item;
	if (!prev_list_item)
		list_desc->first_item = new_list_item;
	else
		prev_list_item->next_item = new_list_item;

	list_desc->sorted_list_len++;
	pool->total_inserts++;
	return 0;
}

void *odp_sorted_list_remove(odp_int_sorted_pool_t sorted_pool,
			     odp_int_sorted_list_t sorted_list,
			     uint64_t             *sort_key_ptr)
{
	sorted_list_desc_t *list_desc;
	sorted_list_item_t *list_item;
	sorted_pool_t      *pool;
	uint64_t            user_data;
	uint32_t            list_idx;

	pool     = (sorted_pool_t *)sorted_pool;
	list_idx = (uint32_t)sorted_list;
	if ((pool->next_list_idx    <= list_idx) ||
	    (pool->max_sorted_lists <= list_idx))
		return NULL;

	list_desc = &pool->list_descs->descs[list_idx];
	if ((list_desc->sorted_list_len == 0) ||
	    (!list_desc->first_item))
		return NULL;

	list_item             = list_desc->first_item;
	list_desc->first_item = list_item->next_item;
	list_desc->sorted_list_len--;

	if (sort_key_ptr)
		*sort_key_ptr = list_item->sort_key;

	user_data = list_item->user_data;
	free(list_item);
	pool->total_removes++;
	return (void *)user_data;
}

void odp_sorted_list_stats_print(odp_int_sorted_pool_t sorted_pool)
{
	sorted_pool_t *pool;

	pool = (sorted_pool_t *)sorted_pool;
	printf("sorted_pool=0x%lX\n", sorted_pool);
	printf("  max_sorted_lists=%u next_list_idx=%u\n",
	       pool->max_sorted_lists, pool->next_list_idx);
	printf("  total_inserts=%lu total_removes=%lu\n",
	       pool->total_inserts, pool->total_removes);
}

void odp_sorted_pool_destroy(odp_int_sorted_pool_t sorted_pool)
{
	sorted_list_descs_t *list_descs;
	sorted_list_desc_t  *list_desc;
	sorted_list_item_t  *list_item, *next_list_item;
	sorted_pool_t       *pool;
	uint32_t             list_idx;

	pool       = (sorted_pool_t *)sorted_pool;
	list_descs = pool->list_descs;

	for (list_idx = 0; list_idx < pool->next_list_idx; list_idx++) {
		list_desc = &list_descs->descs[list_idx];
		list_item = list_desc->first_item;
		while (list_item) {
			next_list_item = list_item->next_item;
			free(list_item);
			list_item = next_list_item;
		}
	}

	free(list_descs);
	free(pool);
}
