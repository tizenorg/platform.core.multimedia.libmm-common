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

#ifndef MMF_ATTRS_PRIVATE_H_
#define MMF_ATTRS_PRIVATE_H_

#include <stdbool.h>
#include <mm_types.h>
#include <mm_attrs.h>
#include <pthread.h>

#ifdef __cplusplus
	extern "C" {
#endif

#define MMF_IS_VALUE_TYPE(t) ((t) == MMF_VALUE_TYPE_INT || \
		(t) == MMF_VALUE_TYPE_DOUBLE || \
		(t) == MMF_VALUE_TYPE_STRING || \
		(t) == MMF_VALUE_TYPE_DATA)

#define MMF_IS_VALUE_SPEC_TYPE(t) ((t) == MMF_VALUE_SPEC_NONE || \
		(t) == MMF_VALUE_SPEC_INT_ARRAY || \
		(t) == MMF_VALUE_SPEC_INT_RANGE) || \
		(t) == MMF_VALUE_SPEC_DOUBLE_ARRAY || \
		(t) == MMF_VALUE_SPEC_DOUBLE_RANGE)

#define MM_ATTRS_WRITE_LOCK(attrs)		do { pthread_mutex_lock(&attrs->write_lock); } while (0)
#define MM_ATTRS_WRITE_UNLOCK(attrs)	do { pthread_mutex_unlock(&attrs->write_lock); } while (0)

enum mmf_value_type {
	MMF_VALUE_TYPE_INT = MM_ATTRS_TYPE_INT,
	MMF_VALUE_TYPE_DOUBLE=MM_ATTRS_TYPE_DOUBLE,
	MMF_VALUE_TYPE_STRING = MM_ATTRS_TYPE_STRING,
	MMF_VALUE_TYPE_DATA = MM_ATTRS_TYPE_DATA,
};

enum mmf_value_spec_type {
	MMF_VALUE_SPEC_NONE = MM_ATTRS_VALID_TYPE_NONE,
	MMF_VALUE_SPEC_INT_ARRAY = MM_ATTRS_VALID_TYPE_INT_ARRAY,
	MMF_VALUE_SPEC_INT_RANGE = MM_ATTRS_VALID_TYPE_INT_RANGE,
	MMF_VALUE_SPEC_DOUBLE_ARRAY = MM_ATTRS_VALID_TYPE_DOUBLE_ARRAY,
	MMF_VALUE_SPEC_DOUBLE_RANGE = MM_ATTRS_VALID_TYPE_DOUBLE_RANGE,
};

typedef struct mmf_value					mmf_value_t;
typedef struct mmf_value_spec				mmf_value_spec_t;
typedef struct mmf_attribute				mmf_attribute_t;
typedef struct mmf_attrs					mmf_attrs_t;
typedef struct mmf_attrs_list				mmf_attrs_list_t;
typedef struct mmf_attribute_construct_info	mmf_attrs_construct_info_t;

typedef bool (*mmf_attrs_commit_func_t)(int attr_idx,
                                        const char* attr_name,
                                        const mmf_value_t *value,
                                        void *commit_param);

struct mmf_value {
	int type;
	int size;
	union {
		int i_val;
		double d_val;
		char *s_val;
		void *p_val;
	} value;
};

struct mmf_value_spec {
	int type;
	union {
		union {
			struct {
				int *array;
				int count;
				int dval;
			} array;
			struct {
				int min;
				int max;
				int dval;
			} range;
		} int_spec;
		union {
			struct {
				double *array;
				int count;
				double dval;
			} array;
			struct {
				double min;
				double max;
				double dval;
			} range;
		} double_spec;
		struct {
			int max_length;
		} string_spec;
	} spec;
};

struct mmf_attribute {
	char *name;
	int flags;
	mmf_value_t value;
	mmf_value_t tmpval;
	mmf_value_spec_t value_spec;
};

struct mmf_attrs {
	char *name;
	int count;
	mmf_attribute_t *items;
	mmf_attrs_commit_func_t commit_func;
	void *commit_param;
	pthread_mutex_t write_lock;
};

struct mmf_attrs_list {
	MMHandleType attrs;
	mmf_attrs_list_t *next;
};

struct mmf_attribute_construct_info {
	char *name;
	int value_type;
	int flags;
	void *default_value;
};

int mmf_value_init(mmf_value_t *value, int type);

int mmf_value_copy(mmf_value_t *dest, const mmf_value_t *src);

int mmf_value_set_int(mmf_value_t *v, int ival);

int mmf_value_get_int(const mmf_value_t *v);

int mmf_value_set_double(mmf_value_t *v, double dval);

double mmf_value_get_double(mmf_value_t *v);

int mmf_value_set_string(mmf_value_t *v, const char *sval, int size);

const char* mmf_value_get_string(const mmf_value_t *v, int *size);

int mmf_value_set_data(mmf_value_t *v, void *data, int size);

void* mmf_value_get_data(const mmf_value_t *v, int *size);

void mmf_value_dump(const mmf_value_t *value);

int mmf_value_clear(mmf_value_t *value);

int mmf_value_spec_init(mmf_value_spec_t *vs, int vs_type);

int mmf_value_spec_set_int_range(mmf_value_spec_t *vs, int min, int max, int dval);

int mmf_value_spec_get_int_range(mmf_value_spec_t *vs, int *min, int *max, int *dval);

int mmf_value_spec_set_int_array(mmf_value_spec_t *vs, const int *array, int count, int dval);

int mmf_value_spec_get_int_array(mmf_value_spec_t *vs, int **array, int *count, int *dval);

int mmf_value_spec_set_double_range(mmf_value_spec_t *vs, double min, double max, double dval);

int mmf_value_spec_get_double_range(mmf_value_spec_t *vs, double *min, double *max, double *dval);

int mmf_value_spec_set_double_array(mmf_value_spec_t *vs, const double *array, int count, double dval);

int mmf_value_spec_get_double_array(mmf_value_spec_t *vs, double **array, int *count, double *dval);

int mmf_value_spec_clear(mmf_value_spec_t *vs);

int mmf_attribute_init(mmf_attribute_t *item, const char *name, int value_type, int flags);

bool mmf_attribute_check_flags(mmf_attribute_t *item, int flags);

bool mmf_attribute_validate_int(mmf_attribute_t *item, int val);

bool mmf_attribute_validate_double(mmf_attribute_t *item, double val);

void mmf_attribute_clear(mmf_attribute_t *item);

bool mmf_attribute_is_modified(mmf_attribute_t *item);

void mmf_attribute_set_modified(mmf_attribute_t *item);

void mmf_attribute_set_readonly(mmf_attribute_t *item);

void mmf_attribute_set_disabled(mmf_attribute_t *item);

void mmf_attribute_commit(mmf_attribute_t *item);

int mmf_attribute_set_int(mmf_attribute_t *item, int val);

int mmf_attribute_set_double(mmf_attribute_t *item, double val);

int mmf_attribute_set_string(mmf_attribute_t *item, const char *string, int size);

int mmf_attribute_set_data(mmf_attribute_t *item, void *data, int size);

/* --- Create, Destroy and Initialize MmfAttrs --- */

MMHandleType mmf_attrs_new(int count);

MMHandleType mmf_attrs_new_from_data(const char *name,
                                     mmf_attrs_construct_info_t *info,
                                     int count,
                                     mmf_attrs_commit_func_t commit_func,
                                     void *commit_param);

void mmf_attrs_free(MMHandleType attrs);

int mmf_attrs_init(MMHandleType h, mmf_attrs_construct_info_t *info, int count);

int mmf_attrs_commit(MMHandleType h);

int mmf_attrs_commit_err(MMHandleType h, char **err_attr_name);

int mmf_attrs_set_valid_type(MMHandleType h, int idx, int v_type);

int mmf_attrs_set_valid_range(MMHandleType h, int idx, int min, int max, int dval);

int mmf_attrs_set_valid_array(MMHandleType h, int idx, const int *array, int count, int dval);

int mmf_attrs_set_valid_double_range(MMHandleType h, int idx, double min, double max, double dval);

int mmf_attrs_set_valid_double_array(MMHandleType h, int idx, const double *array, int count, double dval);


#ifdef __cplusplus
	}
#endif

#endif /*MMF_ATTRS_PRIVATE_H_*/
