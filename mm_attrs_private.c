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

 

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
#include "mm_debug.h"
#include "mm_attrs_private.h"

int mmf_value_init(mmf_value_t *value, int type)
{
	return_val_if_fail(value, -1);
	return_val_if_fail(MMF_IS_VALUE_TYPE(type), -1);
	memset(value, 0, sizeof(*value));
	value->type = type;
	return 0;
}

int mmf_value_copy(mmf_value_t *dest, const mmf_value_t *src)
{
	return_val_if_fail(dest && src && src->type == dest->type, -1);
	switch (src->type) {
	case MM_ATTRS_TYPE_INT:
		dest->value.i_val = src->value.i_val;
		break;
	case MM_ATTRS_TYPE_DOUBLE:
		dest->value.d_val = src->value.d_val;
		break;
	case MM_ATTRS_TYPE_STRING:
		if (src->value.s_val)
		{
			dest->value.s_val = strdup(src->value.s_val);
			dest->size = src->size;
		}
		else
		{
			dest->value.s_val = NULL;
			dest->size = 0;
		}
		break;
	case MM_ATTRS_TYPE_DATA:
		dest->value.p_val = src->value.p_val;
		dest->size = src->size;
		break;
	default:
		break;
	}
	return 0;
}

int mmf_value_set_int(mmf_value_t *v, int ival)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_INT, -1);
	v->value.i_val = ival;
	return 0;
}

int mmf_value_get_int(const mmf_value_t *v)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_INT, -1);
	return v->value.i_val;
}

int mmf_value_set_double(mmf_value_t *v, double dval)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_DOUBLE, -1);
	v->value.d_val = dval;
	return 0;
}

double mmf_value_get_double(mmf_value_t *v)
{
        return_val_if_fail(v->type == MMF_VALUE_TYPE_DOUBLE, -1);
        return v->value.d_val;
}

int mmf_value_set_string(mmf_value_t *v, const char *sval,int size)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_STRING, -1);
	if (v->value.s_val != NULL) {
		free(v->value.s_val);
		v->value.s_val = NULL;
		v->size = 0;
	}
	if (sval){
		v->value.s_val = strdup(sval);
		v->size = size;
		}
	else{
		v->value.s_val = NULL;
		v->size = 0;
		}
	return 0;
}

const char* mmf_value_get_string(const mmf_value_t *v, int *size)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_STRING, NULL);
	*size=v->size;
	return v->value.s_val;
}

int mmf_value_set_data(mmf_value_t *v, void *data,int size)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_DATA, -1);
	v->value.p_val = data;
	v->size=size;
	return 0;
}

void* mmf_value_get_data(const mmf_value_t *v,int *size)
{
	return_val_if_fail(v && v->type == MMF_VALUE_TYPE_DATA, NULL);
	*size=v->size;
	return v->value.p_val;
}

void mmf_value_dump(const mmf_value_t *value)
{
	return_if_fail(value);
	switch (value->type) {
	case MMF_VALUE_TYPE_INT:
		mmf_debug(MMF_DEBUG_LOG, "value[int]: %d\n", value->value.i_val);
		break;
	case MMF_VALUE_TYPE_DOUBLE:
		mmf_debug(MMF_DEBUG_LOG, "value[double]: %f\n", value->value.d_val);
		break;
	case MMF_VALUE_TYPE_STRING:
		mmf_debug(MMF_DEBUG_LOG, "value[string]: %s\n", value->value.s_val);
		break;
	case MMF_VALUE_TYPE_DATA:
		mmf_debug(MMF_DEBUG_LOG, "value[data]: %p\n", value->value.p_val);
		break;
	default:
		mmf_debug(MMF_DEBUG_LOG, "value invalid!!\n");
		break;
	}
}

int mmf_value_clear(mmf_value_t *value)
{
	return_val_if_fail(value, -1);
	if (value->type == MMF_VALUE_TYPE_STRING) {
		if (value->value.s_val) {
			free(value->value.s_val);
			value->value.s_val = NULL;
			value->size = 0;
		}
	}
	return 0;
}

int mmf_value_spec_init(mmf_value_spec_t *vs, int vs_type)
{
	return_val_if_fail(vs, -1);
	memset(vs, 0, sizeof(*vs));
	vs->type = vs_type;
	return 0;
}

int mmf_value_spec_set_int_range(mmf_value_spec_t *vs, int min, int max, int dval)
{
	return_val_if_fail(vs && vs->type == MMF_VALUE_SPEC_INT_RANGE, -1);

	vs->spec.int_spec.range.min = min;
	vs->spec.int_spec.range.max = max;
	vs->spec.int_spec.range.dval = dval;

	return 0;
}

int mmf_value_spec_get_int_range(mmf_value_spec_t *vs, int *min, int *max, int *dval)
{
	return_val_if_fail(vs && min && max && dval && vs->type == MMF_VALUE_SPEC_INT_RANGE, -1);

	*min = vs->spec.int_spec.range.min;
	*max = vs->spec.int_spec.range.max;
	*dval = vs->spec.int_spec.range.dval;

	return 0;
}

int mmf_value_spec_set_int_array(mmf_value_spec_t *vs, const int *array, int count, int dval)
{
	int *array_copy = NULL;

	return_val_if_fail(vs && array && vs->type == MMF_VALUE_SPEC_INT_ARRAY && count > 0, -1);

	array_copy = (int *) malloc(sizeof(int) * count);
	if (array_copy == NULL) {
		debug_error("malloc failed");
		return -1;
	}

	memcpy(array_copy, array, sizeof(int) * count);
	vs->spec.int_spec.array.array = array_copy;
	vs->spec.int_spec.array.count = count;
	vs->spec.int_spec.array.dval = dval;

	return 0;
}

int mmf_value_spec_get_int_array(mmf_value_spec_t *vs, int **array, int *count, int *dval)
{
	return_val_if_fail(vs && array && count && dval && vs->type == MMF_VALUE_SPEC_INT_ARRAY, -1);

	*array = vs->spec.int_spec.array.array;
	*count = vs->spec.int_spec.array.count;
	*dval = vs->spec.int_spec.array.dval;

	return 0;
}

int mmf_value_spec_set_double_range(mmf_value_spec_t *vs, double min, double max, double dval)
{
	return_val_if_fail(vs && vs->type == MMF_VALUE_SPEC_DOUBLE_RANGE, -1);

	vs->spec.double_spec.range.min = min;
	vs->spec.double_spec.range.max = max;
	vs->spec.double_spec.range.dval = dval;

	return 0;
}

int mmf_value_spec_get_double_range(mmf_value_spec_t *vs, double *min, double *max, double *dval)
{
	return_val_if_fail(vs && min && max && dval && vs->type == MMF_VALUE_SPEC_DOUBLE_RANGE, -1);

	*min = vs->spec.double_spec.range.min;
	*max = vs->spec.double_spec.range.max;
	*dval = vs->spec.double_spec.range.dval;

	return 0;
}

int mmf_value_spec_set_double_array(mmf_value_spec_t *vs, const double *array, int count, double dval)
{
	double *array_copy = NULL;

	return_val_if_fail(vs && array && vs->type == MMF_VALUE_SPEC_DOUBLE_ARRAY && count > 0, -1);

	array_copy = (double *) malloc(sizeof(double) * count);
	if (array_copy == NULL) {
		debug_error("malloc failed");
		return -1;
	}

	memcpy(array_copy, array, sizeof(double) * count);
	vs->spec.double_spec.array.array = array_copy;
	vs->spec.double_spec.array.count = count;
	vs->spec.double_spec.array.dval = dval;

	return 0;
}

int mmf_value_spec_get_double_array(mmf_value_spec_t *vs, double **array, int *count, double *dval)
{
	return_val_if_fail(vs && array && count && dval && vs->type == MMF_VALUE_SPEC_DOUBLE_ARRAY, -1);

	*array = vs->spec.double_spec.array.array;
	*count = vs->spec.double_spec.array.count;
	*dval = vs->spec.double_spec.array.dval;

	return 0;
}

int mmf_value_spec_clear(mmf_value_spec_t *vs)
{
	return_val_if_fail(vs, -1);
	switch(vs->type) {
	case MMF_VALUE_SPEC_INT_ARRAY:
		if (vs->spec.int_spec.array.array) {
			free(vs->spec.int_spec.array.array);
			vs->spec.int_spec.array.array = NULL;
			vs->spec.int_spec.array.count = 0;
			vs->spec.int_spec.array.dval = 0;
		}
		break;
	case MMF_VALUE_SPEC_DOUBLE_ARRAY:
		if (vs->spec.double_spec.array.array) {
			free(vs->spec.double_spec.array.array);
			vs->spec.double_spec.array.array = NULL;
			vs->spec.double_spec.array.count = 0;
			vs->spec.double_spec.array.dval = 0;
		}
		break;

	default:
		break;
	}

	return 0;
}

int mmf_attribute_init(mmf_attribute_t *item, const char *name, int value_type, int flags)
{
	return_val_if_fail(item && name, -1);

	item->name = strdup(name);
	item->flags = flags;

	mmf_value_spec_init(&item->value_spec, MMF_VALUE_SPEC_NONE);
	mmf_value_init(&item->value, value_type);
	mmf_value_init(&item->tmpval, value_type);

	return 0;
}

bool mmf_attribute_check_flags(mmf_attribute_t *item, int flags)
{
	return_val_if_fail(item, false);
	return item->flags & flags;
}

bool mmf_attribute_validate_int(mmf_attribute_t *item, int val)
{
	return_val_if_fail(item, false);
	return_val_if_fail(item->value.type == MMF_VALUE_TYPE_INT, false);
	
	bool valid = true;
	int i = 0;
	
	switch (item->value_spec.type) {
	case MMF_VALUE_SPEC_INT_RANGE:
		if (val < item->value_spec.spec.int_spec.range.min || 
				val > item->value_spec.spec.int_spec.range.max) {
			valid = false;
			mmf_debug(MMF_DEBUG_LOG, "[mmf_attribute:%s] out of range\n", item->name);
		}
		break;
	case MMF_VALUE_SPEC_INT_ARRAY:
		valid = false;
		for (i = 0; i < item->value_spec.spec.int_spec.array.count; i++) {
			if (val == item->value_spec.spec.int_spec.array.array[i]) {
				valid = true;
				break;
			}
		}
		if (!valid) {
			mmf_debug(MMF_DEBUG_LOG, "[mmf_attribute:%s] out of array\n", item->name);
		}
		break;
	default:
		break;		
	}
	
	return valid;
}

bool mmf_attribute_validate_double(mmf_attribute_t *item, double val)
{
	return_val_if_fail(item, false);
	return_val_if_fail(item->value.type == MMF_VALUE_TYPE_DOUBLE, false);
	
	bool valid = true;
	int i = 0;
	
	switch (item->value_spec.type) {
	case MMF_VALUE_SPEC_DOUBLE_RANGE:
		if (val < item->value_spec.spec.double_spec.range.min || 
				val > item->value_spec.spec.double_spec.range.max) {
			valid = false;
			mmf_debug(MMF_DEBUG_LOG, "[mmf_attribute:%s] out of range\n", item->name);
		}
		break;
	case MMF_VALUE_SPEC_DOUBLE_ARRAY:
		valid = false;
		for (i = 0; i < item->value_spec.spec.double_spec.array.count; i++) {
			if (val == item->value_spec.spec.double_spec.array.array[i]) {
				valid = true;
				break;
			}
		}
		if (!valid) {
			mmf_debug(MMF_DEBUG_LOG, "[mmf_attribute:%s] out of array\n", item->name);
		}
		break;
	default:
		break;		
	}
	
	return valid;
}

void mmf_attribute_clear(mmf_attribute_t *item)
{
	assert(item);
	if (item->name) {
		free(item->name);
		item->name = NULL;
	}

	mmf_value_clear(&item->tmpval);
	mmf_value_clear(&item->value);
	mmf_value_spec_clear(&item->value_spec);
}

bool mmf_attribute_is_modified(mmf_attribute_t *item)
{
	return_val_if_fail(item, false);
	return (item->flags & MM_ATTRS_FLAG_MODIFIED);
}

void mmf_attribute_set_modified(mmf_attribute_t *item)
{
	return_if_fail(item);
	if (!(item->flags & MM_ATTRS_FLAG_MODIFIED)) {
		mmf_value_copy(&item->tmpval, &item->value);
		item->flags |= MM_ATTRS_FLAG_MODIFIED;
	}
}

void mmf_attribute_set_readonly(mmf_attribute_t *item)
{
	return_if_fail(item);
	if (item->flags & MM_ATTRS_FLAG_WRITABLE)
		item->flags -= MM_ATTRS_FLAG_WRITABLE;
}

void mmf_attribute_set_disabled(mmf_attribute_t *item)
{
	return_if_fail(item);
	if (item->flags & MM_ATTRS_FLAG_WRITABLE)
		item->flags -= MM_ATTRS_FLAG_WRITABLE;
	if (item->flags & MM_ATTRS_FLAG_READABLE)
		item->flags -= MM_ATTRS_FLAG_READABLE;
	if (item->flags & MM_ATTRS_FLAG_MODIFIED)
		item->flags -= MM_ATTRS_FLAG_MODIFIED;
}

void mmf_attribute_commit(mmf_attribute_t *item)
{
	return_if_fail(item);
	if (item->flags & MM_ATTRS_FLAG_MODIFIED) {
		mmf_value_copy(&item->value, &item->tmpval);
		mmf_value_clear(&item->tmpval);
		item->flags ^= MM_ATTRS_FLAG_MODIFIED;
	}
}

int mmf_attribute_set_int(mmf_attribute_t *item, int val)
{
	return_val_if_fail(item, -1);
	if (mmf_value_set_int(&item->tmpval, val) == 0) {
		item->flags |= MM_ATTRS_FLAG_MODIFIED;
		return 0;
	}
	return -1;
}

int mmf_attribute_set_double(mmf_attribute_t *item, double val)
{
	return_val_if_fail(item, -1);
	if (mmf_value_set_double(&item->tmpval, val) == 0) {
		item->flags |= MM_ATTRS_FLAG_MODIFIED;
		return 0;
	}
	return -1;
}

int mmf_attribute_set_string(mmf_attribute_t *item, const char *string, int size)
{
	return_val_if_fail(item, -1);

	if (mmf_value_set_string(&item->tmpval, string,size) == 0) {
		if (string) 
			item->flags |= MM_ATTRS_FLAG_MODIFIED; 
		
		return 0;
	}
	return -1;
}

int mmf_attribute_set_data(mmf_attribute_t *item, void *data, int size)
{
	return_val_if_fail(item, -1);

	if (mmf_value_set_data(&item->tmpval, data,size) == 0) {
		item->flags |= MM_ATTRS_FLAG_MODIFIED;
		return 0;
	}
	return -1;
}

MMHandleType mmf_attrs_new(int count)
{
	return_val_if_fail(count > 0, 0);
	mmf_attrs_t *attrs;
	attrs = (mmf_attrs_t *) malloc (sizeof(mmf_attrs_t));
	attrs->count = count;
	attrs->items = (mmf_attribute_t *) malloc (sizeof(mmf_attribute_t) * count);
	memset(attrs->items, 0, sizeof(mmf_attribute_t) * count);

	if (pthread_mutex_init(&attrs->write_lock, NULL) != 0) {
		mmf_debug(MMF_DEBUG_ERROR, "mutex init failed");
		return 0;
	}

	return (MMHandleType) attrs;
}

MMHandleType mmf_attrs_new_from_data(const char *name,
                                     mmf_attrs_construct_info_t *info,
                                     int count,
                                     mmf_attrs_commit_func_t commit_func,
                                     void *commit_param)
{
	return_val_if_fail(info && count > 0, 0);
	MMHandleType h;
	mmf_attrs_t *attrs;

	h = mmf_attrs_new(count);
	mmf_attrs_init(h, info, count);
	attrs = (mmf_attrs_t *) h;
	attrs->name = NULL;
	if (name)
		attrs->name = strdup(name);
	attrs->commit_func = commit_func;
	attrs->commit_param = commit_param;
	return h;
}

void mmf_attrs_free(MMHandleType h)
{
	return_if_fail(h);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	if (attrs) {
		if (attrs->name) {
			free(attrs->name);
			attrs->name = NULL;
		}
		if (attrs->items) {
			int i;
			for (i = 0; i < attrs->count; i++) {
				mmf_attribute_clear(&attrs->items[i]);
			}
			free(attrs->items);
			attrs->items = NULL;
		}
		pthread_mutex_destroy(&attrs->write_lock);
		free(attrs);
	}
}

int mmf_attrs_init(MMHandleType h, mmf_attrs_construct_info_t *info, int count)
{
	return_val_if_fail(h && info && count > 0, -1);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	int i;
	int size = 0;

	for (i = 0; i < count; i++) {
		mmf_attribute_init(&attrs->items[i],
		                   info[i].name,
		                   info[i].value_type,
		                   info[i].flags);

		switch (info[i].value_type) {
		case MMF_VALUE_TYPE_INT:
			assert(attrs->items[i].value.value.i_val == 0);
			mmf_value_set_int(&attrs->items[i].value,
			                  (int)info[i].default_value);
			break;
		case MMF_VALUE_TYPE_DOUBLE:
		{
			int i_val = (int)info[i].default_value;
			double d_val = (double) i_val;
			assert(attrs->items[i].value.value.d_val == 0);
			mmf_value_set_double(&attrs->items[i].value, d_val);
			break;
		}
		case MMF_VALUE_TYPE_STRING:
			assert(attrs->items[i].value.value.s_val == NULL);
			if (info[i].default_value) {
				size = strlen(info[i].default_value)+1;
			}
			mmf_value_set_string(&attrs->items[i].value,
			                     (const char *)info[i].default_value,size);
			break;
		case MMF_VALUE_TYPE_DATA:
			assert(attrs->items[i].value.value.p_val == NULL);
			if (info[i].default_value) {
				size = sizeof(info[i].default_value)+1;
			}
			mmf_value_set_data(&attrs->items[i].value, info[i].default_value,size);
			break;
		default:
			mmf_debug(MMF_DEBUG_LOG, "ERROR: Invalid MMF_VALUE_TYPE\n");
			assert(0);
			break;
		}
	}

	return 0;
}

int mmf_attrs_commit(MMHandleType h)
{
	return_val_if_fail(h, -1);
	
	mmf_attrs_t *attrs = (mmf_attrs_t * )h;
	int i;
	int ret = 0;

	MM_ATTRS_WRITE_LOCK(attrs);

	for (i = 0; i < attrs->count; ++i) {
		if (mmf_attribute_is_modified(&attrs->items[i])) {
			if (attrs->commit_func) {
				if (attrs->commit_func(i, attrs->items[i].name,
										&attrs->items[i].tmpval,
										attrs->commit_param)) {
					mmf_attribute_commit(&attrs->items[i]);
				} else {
					/* without this, there is no way to solve modify when commit_func failed. */
					if (attrs->items[i].flags & MM_ATTRS_FLAG_MODIFIED)
						attrs->items[i].flags ^= MM_ATTRS_FLAG_MODIFIED;
					ret = -1;
				}
			} else {
				mmf_attribute_commit(&attrs->items[i]);
			}
		}
	}

	MM_ATTRS_WRITE_UNLOCK(attrs);

	return ret;
}

int mmf_attrs_commit_err(MMHandleType h, char **err_attr_name)
{
	mmf_attrs_t *attrs = (mmf_attrs_t * )h;
	int i;
	int ret = 0;

	return_val_if_fail(h, -1);

	MM_ATTRS_WRITE_LOCK(attrs);

	for (i = 0; i < attrs->count; ++i) {
		if (mmf_attribute_is_modified(&attrs->items[i])) {
			if (attrs->commit_func) {
				if (attrs->commit_func(i, attrs->items[i].name,
										&attrs->items[i].tmpval,
										attrs->commit_param)) {
					mmf_attribute_commit(&attrs->items[i]);
				} else {
					/* without this, there is no way to solve modify when commit_func failed. */
					if (attrs->items[i].flags & MM_ATTRS_FLAG_MODIFIED)
						attrs->items[i].flags ^= MM_ATTRS_FLAG_MODIFIED;
					ret = -1;

					/* Set Error information */
					if (err_attr_name)
						*err_attr_name = strdup(attrs->items[i].name);

					break;
				}
			} else {
				mmf_attribute_commit(&attrs->items[i]);
			}
		}
	}

	MM_ATTRS_WRITE_UNLOCK(attrs);

	return ret;
}

int mmf_attrs_set_valid_type(MMHandleType h, int idx, int v_type)
{
	return_val_if_fail(h, -1);
	return_val_if_fail(idx>=0, -1);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return mmf_value_spec_init(&attrs->items[idx].value_spec, v_type);
}

int mmf_attrs_set_valid_range(MMHandleType h, int idx, int min, int max, int dval)
{
	return_val_if_fail(h, -1);
	return_val_if_fail(idx>=0, -1);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	mmf_value_spec_clear(&attrs->items[idx].value_spec);
	assert(attrs->items[idx].value_spec.type == MMF_VALUE_SPEC_INT_RANGE);
	return mmf_value_spec_set_int_range(&attrs->items[idx].value_spec, min, max, dval);
}

int mmf_attrs_set_valid_array(MMHandleType h, int idx, const int *array, int count, int dval)
{
	return_val_if_fail(h, -1);
	return_val_if_fail(idx>=0, -1);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	mmf_value_spec_clear(&attrs->items[idx].value_spec);
	assert(attrs->items[idx].value_spec.type == MMF_VALUE_SPEC_INT_ARRAY);
	return mmf_value_spec_set_int_array(&attrs->items[idx].value_spec, array, count, dval);
}

int mmf_attrs_set_valid_double_range(MMHandleType h, int idx, double min, double max, double dval)
{
	return_val_if_fail(h, -1);
	return_val_if_fail(idx>=0, -1);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	mmf_value_spec_clear(&attrs->items[idx].value_spec);
	assert(attrs->items[idx].value_spec.type == MMF_VALUE_SPEC_DOUBLE_RANGE);
	return mmf_value_spec_set_double_range(&attrs->items[idx].value_spec, min, max, dval);
}

int mmf_attrs_set_valid_double_array(MMHandleType h, int idx, const double *array, int count, double dval)
{
	return_val_if_fail(h, -1);
	return_val_if_fail(idx>=0, -1);
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	mmf_value_spec_clear(&attrs->items[idx].value_spec);
	assert(attrs->items[idx].value_spec.type == MMF_VALUE_SPEC_DOUBLE_ARRAY);
	return mmf_value_spec_set_double_array(&attrs->items[idx].value_spec, array, count, dval);
}

