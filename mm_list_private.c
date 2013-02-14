/*
 * libmm-common
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jonghyuk Choi <jhchoi.choi@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdlib.h>
#include <string.h>

#include <mm_error.h>

#include <mm_debug.h>
#include <mm_list_private.h>

/**
 * Definition of list item
 */
typedef struct {
	int			id;
	void		*data;
	void		*next;
} mmf_list_t;

/**
 * Globals
 */
static mmf_list_t	*g_list = NULL;
static int			g_list_id = 0;

EXPORT_API
int mmf_list_append(void *data)
{
	mmf_list_t *item;
	mmf_list_t *list;

	item = (mmf_list_t *) malloc(sizeof(mmf_list_t));

	if (item == NULL) {
		debug_error("memory allocation error\n");
		return MM_ERROR_OUT_OF_MEMORY;
	}

	/* set new list information */
	memset(item, 0, sizeof(mmf_list_t));

	item->id = g_list_id++;
	item->data = data;
	list = g_list;

	if (list == NULL) {
		/* first item */
		g_list = item;
	}
	else {
		list = g_list;

		/* move to last */
		while (list->next) {
			list = (mmf_list_t *) list->next;
		}
		list->next = item;
	}

	return item->id;
}

EXPORT_API
int mmf_list_remove(int handle)
{
	mmf_list_t *list;
	mmf_list_t *prev;

	list = g_list;
	prev = NULL;

	while (list) {
		if (list->id == handle) {
			/* remove handle */
			if (prev) {
				prev->next = list->next;
			}
			else {
				g_list = list->next;
			}

			free(list);

			return MM_ERROR_NONE;
		}

		prev = list;
		list = (mmf_list_t *) list->next;
	}

	debug_error("handle not found\n");

	return MM_ERROR_INVALID_ARGUMENT;
}

EXPORT_API
void *mmf_list_find(int handle)
{
	mmf_list_t *list;

	list = g_list;

	while (list) {
		if (list->id == handle) {
			return list->data;
		}

		list = (mmf_list_t *) list->next;
	}

	debug_error("handle not found\n");

	return NULL;
}

EXPORT_API
int mmf_list_find_by_data(void *data)
{
	mmf_list_t *list;

	list = g_list;

	while (list) {
		if (list->data == data) {
			return list->id;
		}

		list = (mmf_list_t *) list->next;
	}

	debug_error("handle not found\n");

	return -1;
}

