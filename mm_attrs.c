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
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "mm_debug.h"
#include "mm_attrs.h"
#include "mm_attrs_private.h"
#include "mm_error.h"

int mm_attrs_get_type(MMHandleType h, int idx, MMAttrsType *attrtype)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(h && idx >= 0 && idx < attrs->count && attrtype, MM_ERROR_COMMON_INVALID_ARGUMENT);
	*attrtype=attrs->items[idx].value.type;
	return MM_ERROR_NONE;
}


int mm_attrs_get_flags(MMHandleType h, int idx, int *flags)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && flags, MM_ERROR_COMMON_INVALID_ARGUMENT);

	*flags=attrs->items[idx].flags;
	return MM_ERROR_NONE;
}


int mm_attrs_get_valid_type(MMHandleType h, int idx, int *type)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && type, MM_ERROR_COMMON_INVALID_ARGUMENT);
	*type=attrs->items[idx].value_spec.type;
	return MM_ERROR_NONE;
}


int mm_attrs_get_valid_range(MMHandleType h, int idx, int *min, int *max)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && min && max, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (min) {
		*min = attrs->items[idx].value_spec.spec.int_spec.range.min;
	}
	if (max) {
		*max = attrs->items[idx].value_spec.spec.int_spec.range.max;
	}
	return MM_ERROR_NONE;
}


int mm_attrs_get_valid_array(MMHandleType h, int idx, int *count,  int **array)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	if (count)
		*count = 0;
	return_val_if_fail(attrs && count && idx >= 0 && idx < attrs->count && array, MM_ERROR_COMMON_INVALID_ARGUMENT);
	if (count)
		*count = attrs->items[idx].value_spec.spec.int_spec.array.count;
	*array=attrs->items[idx].value_spec.spec.int_spec.array.array;
	return MM_ERROR_NONE;
}


int mm_attrs_get_size(MMHandleType h, int *size)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(h && size, MM_ERROR_COMMON_INVALID_ARGUMENT);
	*size = attrs->count;
	return MM_ERROR_NONE;
}


int mm_attrs_get_name(MMHandleType h, int idx, char **name)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && name, MM_ERROR_COMMON_INVALID_ARGUMENT);
	*name = attrs->items[idx].name;
	return MM_ERROR_NONE;
}


int mm_attrs_get_index(MMHandleType h, const char *attrname, int *index)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	int i;

	return_val_if_fail(h && attrname && index, MM_ERROR_COMMON_INVALID_ARGUMENT);

	for (i = 0; i < attrs->count; i++) {
		if (0 == strcmp(attrs->items[i].name, attrname)) {
			*index = i;
			return MM_ERROR_NONE;
		}
	}
	return MM_ERROR_COMMON_OUT_OF_ARRAY;
}


int mm_attrs_set_int(MMHandleType h, int idx, int val)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mmf_attribute_t *item = &attrs->items[idx];
	return_val_if_fail(item, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (!mmf_attribute_check_flags(item, MM_ATTRS_FLAG_WRITABLE))
	{
		return MM_ERROR_COMMON_INVALID_PERMISSION;
	}
	
	if (mmf_attribute_validate_int(item, val))
	{
		int ret = 0;
		ret = mmf_attribute_set_int(item, val);

		if (ret == 0)
			return MM_ERROR_NONE;
		else
			return MM_ERROR_COMMON_INVALID_ATTRTYPE;
	}

	if (item->value_spec.type == MMF_VALUE_SPEC_INT_RANGE)
		return MM_ERROR_COMMON_OUT_OF_RANGE;
	else if (item->value_spec.type == MMF_VALUE_SPEC_INT_ARRAY)
		return MM_ERROR_COMMON_OUT_OF_ARRAY;
	else
		return MM_ERROR_COMMON_INVALID_ARGUMENT;		
}


int mm_attrs_get_int(MMHandleType h, int idx,  int *val)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && val, MM_ERROR_COMMON_INVALID_ARGUMENT);
	mmf_attribute_t *item = &attrs->items[idx];
	return_val_if_fail(item, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (mmf_attribute_check_flags(item, MM_ATTRS_FLAG_READABLE))
	{
		*val=mmf_value_get_int(&attrs->items[idx].value);
		return MM_ERROR_NONE;
	}

	return MM_ERROR_COMMON_INVALID_PERMISSION;
}


int mm_attrs_set_double(MMHandleType h, int idx, double val)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mmf_attribute_t *item = &attrs->items[idx];
	return_val_if_fail(item, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (!mmf_attribute_check_flags(item, MM_ATTRS_FLAG_WRITABLE))
	{
		return MM_ERROR_COMMON_INVALID_PERMISSION;
	}
	
	if (mmf_attribute_validate_double(item, val))
	{
		int ret = 0;
		ret = mmf_attribute_set_double(item, val);

		if (ret == 0)
			return MM_ERROR_NONE;
		else
			return MM_ERROR_COMMON_INVALID_ATTRTYPE;
	}

	if (item->value_spec.type == MMF_VALUE_SPEC_DOUBLE_RANGE)
		return MM_ERROR_COMMON_OUT_OF_RANGE;
	else if (item->value_spec.type == MMF_VALUE_SPEC_DOUBLE_ARRAY)
		return MM_ERROR_COMMON_OUT_OF_ARRAY;
	else
		return MM_ERROR_COMMON_INVALID_ARGUMENT;	
}


int mm_attrs_get_double(MMHandleType h, int idx, double *val)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && val, MM_ERROR_COMMON_INVALID_ARGUMENT);
	mmf_attribute_t *item = &attrs->items[idx];
	return_val_if_fail(item, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (mmf_attribute_check_flags(item, MM_ATTRS_FLAG_READABLE))
	{
		*val=mmf_value_get_double(&attrs->items[idx].value);
		return MM_ERROR_NONE;
	}

	return MM_ERROR_COMMON_INVALID_PERMISSION;
}


int mm_attrs_set_string(MMHandleType h, int idx, const char *string, int size)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count, MM_ERROR_COMMON_INVALID_ARGUMENT);

		mmf_attribute_t *item = &attrs->items[idx];

	return_val_if_fail(item, MM_ERROR_COMMON_INVALID_ARGUMENT);

	MM_ATTRS_WRITE_LOCK(attrs);

	if (mmf_attribute_check_flags(item, MM_ATTRS_FLAG_WRITABLE))
	{
		int ret = 0;
		ret = mmf_attribute_set_string(item, string, size);

		MM_ATTRS_WRITE_UNLOCK(attrs);

		if (ret == 0)
			return MM_ERROR_NONE;
		else
			return MM_ERROR_COMMON_INVALID_ARGUMENT;
	}

	MM_ATTRS_WRITE_UNLOCK(attrs);

	return MM_ERROR_COMMON_INVALID_PERMISSION;
}


int mm_attrs_get_string(MMHandleType h, int idx,char **sval, int *size)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && sval, MM_ERROR_COMMON_INVALID_ARGUMENT);

	MM_ATTRS_WRITE_LOCK(attrs);

	if (!(attrs->items[idx].flags & MM_ATTRS_FLAG_READABLE)) {
		mmf_debug(MMF_DEBUG_LOG, "Access denied.\n");
		MM_ATTRS_WRITE_UNLOCK(attrs);
		return MM_ERROR_COMMON_INVALID_PERMISSION;
	}

	*sval = mmf_value_get_string(&attrs->items[idx].value,size);

	MM_ATTRS_WRITE_UNLOCK(attrs);

	return MM_ERROR_NONE;
}


int mm_attrs_set_data(MMHandleType h, int idx, void *data, int size)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mmf_attribute_t *item = &attrs->items[idx];
	return_val_if_fail(item, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (mmf_attribute_check_flags(item, MM_ATTRS_FLAG_WRITABLE))
	{
		int ret = 0;
		ret =  mmf_attribute_set_data(item, data, size);

		if (ret == 0)
			return MM_ERROR_NONE;
		else
			return MM_ERROR_COMMON_INVALID_ARGUMENT;
	}

	return MM_ERROR_COMMON_INVALID_ARGUMENT;
}


int mm_attrs_get_data(MMHandleType h, int idx,void **data,  int *size)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;
	return_val_if_fail(attrs && idx >= 0 && idx < attrs->count && data, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (!(attrs->items[idx].flags & MM_ATTRS_FLAG_READABLE)) {
		mmf_debug(MMF_DEBUG_LOG, "Access denied.\n");
		return MM_ERROR_COMMON_INVALID_PERMISSION;
	}
	*data=mmf_value_get_data(&attrs->items[idx].value,size);
	return MM_ERROR_NONE;
}


int mm_attrs_set_int_by_name(MMHandleType attrs, const char *name, int val)
{
	return_val_if_fail(attrs && name, -1);
	int idx = 0;
	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		return mm_attrs_set_int(attrs, idx, val);
	}
	return -1;
}


int mm_attrs_get_int_by_name(MMHandleType attrs, const char *name, int *val)
{
	int idx = -1;
	return_val_if_fail(attrs && name && val, MM_ERROR_COMMON_INVALID_ARGUMENT);
	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		return mm_attrs_get_int(attrs, idx, val);
	}
	return MM_ERROR_COMMON_INVALID_ATTRTYPE;
}


int mm_attrs_set_string_by_name(MMHandleType attrs, const char *name, const char *string)
{
	return_val_if_fail(attrs && name, -1);

	int size;
	int idx = 0;
	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		if (string) {
			size = strlen(string);
		}
		else {
			string = NULL;
			size = 0;
		}
		
		return mm_attrs_set_string(attrs, idx, string, size);
	}
	return -1;
}


int mm_attrs_get_string_by_name(MMHandleType attrs, const char *name, char **string)
{
	int idx = -1;
	int len = 0;
	return_val_if_fail(attrs && name && string, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		return mm_attrs_get_string(attrs, idx, string, &len);
	}
	return MM_ERROR_COMMON_INVALID_ATTRTYPE;
}


int mm_attrs_set_data_by_name(MMHandleType attrs, const char *name, void *data, int size)
{
	return_val_if_fail(attrs && name, -1);
	int idx = 0;
	mm_attrs_get_index(attrs, name, &idx);

	if (idx >= 0) {
		return mm_attrs_set_data(attrs, idx, data, size);
	}
	return -1;
}


int mm_attrs_get_data_by_name(MMHandleType attrs, const char *name, void **data)
{
	int idx = -1;
	int len = 0;

	return_val_if_fail(attrs && name, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		return mm_attrs_get_data(attrs, idx, data, &len);
	}
	return MM_ERROR_COMMON_INVALID_ATTRTYPE;
}


int mm_attrs_set_double_by_name(MMHandleType attrs, const char *name, double val)
{
	int idx = -1;
	return_val_if_fail(attrs && name, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		return mm_attrs_set_double(attrs, idx, val);
	}
	return MM_ERROR_COMMON_INVALID_ATTRTYPE;
}


int mm_attrs_get_double_by_name(MMHandleType attrs, const char *name, double *val)
{
	int idx = -1;
	return_val_if_fail(attrs && name && val, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mm_attrs_get_index(attrs, name, &idx);
	if (idx >= 0) {
		*val = mm_attrs_get_double(attrs, idx, val);
		return 0;
	}
	return MM_ERROR_COMMON_INVALID_ATTRTYPE;
}


int mm_attrs_set_valist (MMHandleType attrs, char **err_attr_name, const char *attribute_name, va_list var_args)
{
	const char *name = NULL;
	int ret = MM_ERROR_NONE;

	return_val_if_fail(attrs, MM_ERROR_COMMON_INVALID_ARGUMENT);
//	return_val_if_fail(err_attr_name, MM_ERROR_COMMON_INVALID_ARGUMENT);
	return_val_if_fail(attribute_name, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (err_attr_name)
		*err_attr_name = NULL;
	name = attribute_name;

	while (name)
	{
		int idx = -1;
		MMAttrsType attr_type = MM_ATTRS_TYPE_INVALID;

		//name check
		if ((ret = mm_attrs_get_index(attrs, name, &idx)) != MM_ERROR_NONE)
		{
			if (err_attr_name)
				*err_attr_name = strdup(name);

			if (ret == MM_ERROR_COMMON_OUT_OF_ARRAY)	//to avoid confusing
				return MM_ERROR_COMMON_ATTR_NOT_EXIST;
			else
				return ret;
		}

		//type check
		if ((ret = mm_attrs_get_type(attrs, idx, &attr_type)) != MM_ERROR_NONE)
			return ret;

		//cast and set
		switch (attr_type)
		{
			case MM_ATTRS_TYPE_INT:
			{
				int val = 	va_arg ((var_args), int);
				mmf_debug(MMF_DEBUG_LOG, "(%s: %d)\n", name, val);
				ret = mm_attrs_set_int(attrs, idx, val);
				break;
			}
			case MM_ATTRS_TYPE_DOUBLE:
			{
				double val = va_arg ((var_args), double);
				mmf_debug(MMF_DEBUG_LOG, "(%s: %f)\n", name, val);
				ret = mm_attrs_set_double(attrs, idx, val);
				break;
			}
			case MM_ATTRS_TYPE_STRING:
			{
				char * val = va_arg ((var_args), char*);
				int size = va_arg ((var_args), int);
				mmf_debug(MMF_DEBUG_LOG, "(%s: \'%s\', size: %d)\n", name, val, size);
				ret = mm_attrs_set_string(attrs, idx, (const char*)val, size);
				break;
			}
			case MM_ATTRS_TYPE_DATA:
			{
				void * val = va_arg ((var_args), void*);
				int size = va_arg ((var_args), int);
				mmf_debug(MMF_DEBUG_LOG, "(%s: %p, size: %d)\n", name, val, size);
				ret = mm_attrs_set_data(attrs, idx, val, size);
				break;
			}
			case MM_ATTRS_TYPE_INVALID:
			default:
				mmf_debug(MMF_DEBUG_ERROR, "This function doesn't support attribute type(%d, name:%s)\n", attr_type, name);
				if (err_attr_name)
					*err_attr_name = strdup(name);
				ret =  MM_ERROR_COMMON_INVALID_ARGUMENT;
		}

		if (ret != MM_ERROR_NONE)
		{
			if (err_attr_name)
				*err_attr_name = strdup(name);
			mmf_debug(MMF_DEBUG_ERROR, "Setting failure.(name:%s)\n", name);
			return ret;
		}

		//next name
		name = va_arg (var_args, char*);
	}

	if (mmf_attrs_commit_err(attrs, err_attr_name) == -1)
		return MM_ERROR_CAMCORDER_INVALID_ARGUMENT;
	else
		return MM_ERROR_NONE;

	return ret;
}


int mm_attrs_get_valist (MMHandleType attrs, char **err_attr_name, const char *attribute_name, va_list var_args)
{
	const char *name = NULL;
	int ret = MM_ERROR_NONE;

	return_val_if_fail(attrs, MM_ERROR_COMMON_INVALID_ARGUMENT);
//	return_val_if_fail(err_attr_name, MM_ERROR_COMMON_INVALID_ARGUMENT);
	return_val_if_fail(attribute_name, MM_ERROR_COMMON_INVALID_ARGUMENT);

	if (err_attr_name)
		*err_attr_name = NULL;
	name = attribute_name;

	while (name)
	{
		int idx = -1;
		MMAttrsType attr_type = MM_ATTRS_TYPE_INVALID;

		//name check
		if ((ret = mm_attrs_get_index(attrs, name, &idx)) != MM_ERROR_NONE)
		{
			if (err_attr_name)
				*err_attr_name = strdup(name);

			if (ret == MM_ERROR_COMMON_OUT_OF_ARRAY)	//to avoid confusing
				return MM_ERROR_COMMON_ATTR_NOT_EXIST;
			else
				return ret;
		}

		//type check
		if ((ret = mm_attrs_get_type(attrs, idx, &attr_type)) != MM_ERROR_NONE)
			return ret;

		//cast and set
		switch (attr_type)
		{
			case MM_ATTRS_TYPE_INT:
			{
				int * val = 	va_arg ((var_args), int*);
//				mmf_debug(MMF_DEBUG_LOG, "(%s: %p)\n", name, val);
				ret = mm_attrs_get_int(attrs, idx, val);
				break;
			}
			case MM_ATTRS_TYPE_DOUBLE:
			{
				double * val = 	va_arg ((var_args), double*);
//				mmf_debug(MMF_DEBUG_LOG, "(%s: %p)\n", name, val);
				ret = mm_attrs_get_double(attrs, idx, val);
				break;
			}
			case MM_ATTRS_TYPE_STRING:
			{
				char ** val = va_arg ((var_args), char**);
				int * size = va_arg ((var_args), int*);
//				mmf_debug(MMF_DEBUG_LOG, "(%s: %p, size: %p)\n", name, val, size);
				ret = mm_attrs_get_string(attrs, idx, (char**)val, size);
				break;
			}
			case MM_ATTRS_TYPE_DATA:
			{
				void ** val = va_arg ((var_args), void**);
				int * size = va_arg ((var_args), int*);
//				mmf_debug(MMF_DEBUG_LOG, "(%s: %p, size: %p)\n", name, val, size);
				ret = mm_attrs_get_data(attrs, idx, val, size);
				break;
			}
			case MM_ATTRS_TYPE_INVALID:
			default:
//				mmf_debug(MMF_DEBUG_ERROR, "This function doesn't support attribute type(%d, name:%s)\n", attr_type, name);
				if (err_attr_name)
					*err_attr_name = strdup(name);
				ret =  MM_ERROR_COMMON_INVALID_ARGUMENT;
		}

		if (ret != MM_ERROR_NONE)
		{
			if (err_attr_name)
				*err_attr_name = strdup(name);
			mmf_debug(MMF_DEBUG_ERROR, "Setting failure.(name:%s)\n", name);
			return ret;
		}

		//next name
		name = va_arg (var_args, char*);
	}

	return ret;
}


int mm_attrs_multiple_set(MMHandleType handle,  char **err_attr_name, const char *attribute_name, ...)
{
	va_list var_args;
	int ret = MM_ERROR_NONE;

	return_val_if_fail(attribute_name, MM_ERROR_COMMON_INVALID_ARGUMENT);

	va_start (var_args, attribute_name);
	ret = mm_attrs_set_valist (handle, err_attr_name, attribute_name, var_args);
	va_end (var_args);

	return ret;
}


int mm_attrs_multiple_get(MMHandleType handle,  char **err_attr_name, const char *attribute_name, ...)
{
	va_list var_args;
	int ret = MM_ERROR_NONE;

	return_val_if_fail(attribute_name, MM_ERROR_COMMON_INVALID_ARGUMENT);

	va_start (var_args, attribute_name);
	ret = mm_attrs_get_valist (handle, err_attr_name, attribute_name, var_args);
	va_end (var_args);

	return ret;
}


int mm_attrs_get_info(MMHandleType h, int idx, MMAttrsInfo *info)
{
	mmf_attrs_t *attrs = (mmf_attrs_t *) h;

	return_val_if_fail(h, MM_ERROR_COMMON_INVALID_ARGUMENT);
	return_val_if_fail(info, MM_ERROR_COMMON_INVALID_ARGUMENT);
	return_val_if_fail( 0 <= idx && idx < attrs->count, MM_ERROR_COMMON_INVALID_ARGUMENT);

	memset(info, 0x00, sizeof(MMAttrsInfo));

	info->type = attrs->items[idx].value.type;
	info->flag = attrs->items[idx].flags;
	info->validity_type = attrs->items[idx].value_spec.type;

	switch (info->validity_type)
	{
		case MM_ATTRS_VALID_TYPE_INT_ARRAY:
			info->int_array.array = attrs->items[idx].value_spec.spec.int_spec.array.array;
			info->int_array.count = attrs->items[idx].value_spec.spec.int_spec.array.count;
			info->int_array.dval = attrs->items[idx].value_spec.spec.int_spec.array.dval;
		break;
		case MM_ATTRS_VALID_TYPE_INT_RANGE:
			info->int_range.min = attrs->items[idx].value_spec.spec.int_spec.range.min;
			info->int_range.max = attrs->items[idx].value_spec.spec.int_spec.range.max;
			info->int_range.dval = attrs->items[idx].value_spec.spec.int_spec.range.dval;
		break;
		case MM_ATTRS_VALID_TYPE_DOUBLE_ARRAY:
			info->double_array.array = attrs->items[idx].value_spec.spec.double_spec.array.array;
			info->double_array.count = attrs->items[idx].value_spec.spec.double_spec.array.count;
			info->double_array.dval = attrs->items[idx].value_spec.spec.double_spec.array.dval;
		break;
		case MM_ATTRS_VALID_TYPE_DOUBLE_RANGE:
			info->double_range.min = attrs->items[idx].value_spec.spec.double_spec.range.min;
			info->double_range.max = attrs->items[idx].value_spec.spec.double_spec.range.max;
			info->double_range.dval = attrs->items[idx].value_spec.spec.double_spec.range.dval;
		break;
		case MM_ATTRS_VALID_TYPE_NONE:
			mmf_debug(MMF_DEBUG_LOG, "Valid type none.\n");
		break;
		case MM_ATTRS_VALID_TYPE_INVALID:
		default:
		break;
	}

	return MM_ERROR_NONE;
}


int mm_attrs_get_info_by_name(MMHandleType h, const char *attr_name, MMAttrsInfo *info)
{
	int idx = -1;
	int ret = MM_ERROR_NONE;

	return_val_if_fail(h, MM_ERROR_COMMON_INVALID_ARGUMENT);
	return_val_if_fail(info, MM_ERROR_COMMON_INVALID_ARGUMENT);

	mmf_debug(MMF_DEBUG_LOG, "(attr_name:%s)\n", attr_name);

	mm_attrs_get_index(h, attr_name, &idx);

	return_val_if_fail(idx >= 0, MM_ERROR_COMMON_INVALID_ARGUMENT);

	ret = mm_attrs_get_info(h, idx, info);

	return ret;
}
