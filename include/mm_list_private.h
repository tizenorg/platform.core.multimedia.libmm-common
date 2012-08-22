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


/**
 * This file declares data structures and functions of managing list.
 *
 * @file		mmf_list_private.h
 * @author
 * @version		1.0
 * @brief		This file declares data structures and functions of managing list.
 */

#ifndef __MMF_LIST_PRIVATE_H__
#define	__MMF_LIST_PRIVATE_H__

#ifdef __cplusplus
	extern "C" {
#endif


/**
 * Append item to list
 *
 * @return
 * @remark
 * @see
 */
int mmf_list_append(void *data);


/**
 * Remove item from list
 *
 * @return
 * @remark
 * @see
 */
int mmf_list_remove(int id);


/**
 * Find data with its id
 *
 * @return
 * @remark
 * @see
 */
void *mmf_list_find(int id);

/**
 * Find id with its data
 *
 * @return
 * @remark
 * @see
 */
int mmf_list_find_by_data(void *data);

#ifdef __cplusplus
	}
#endif

#endif	/* __MMF_LIST_PRIVATE_H__ */
