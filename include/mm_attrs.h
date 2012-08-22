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
 


#ifndef __MM_ATTRS_H__
#define __MM_ATTRS_H__

#include <stdarg.h>
#include <mm_types.h>

#ifdef __cplusplus
	extern "C" {
#endif


/**
	@addtogroup COMMON
	@{

 	 * @file	mm_attrs.h
	 * @version		1.0
	 * @brief		This file declares data structures and functions of attribute library.

	@par
	This part describes the APIs with respect to Multimedia Attribute Library.
	The Attribute Library is a set of attribute. An attribute contains a value,
	access flags and it's validation information. This document explains how to
	manipulate an attribute in the Attribute Library.

 */

/**
 * Enumeration for attribute values types.
 */
typedef enum{
	MM_ATTRS_TYPE_INVALID = -1,        /**< Type is invalid */
	MM_ATTRS_TYPE_INT,                 /**< Integer type attribute */
	MM_ATTRS_TYPE_DOUBLE,               /**< Double type attribute */
	MM_ATTRS_TYPE_STRING,              /**< UTF-8 String type attribute */
	MM_ATTRS_TYPE_DATA,                /**< Pointer type attribute */
	MM_ATTRS_TYPE_NUM,                 /**< Number of attribute type */
}MMAttrsType;

/**
 * Enumeration for attribute validation type.
 */
typedef enum {
	MM_ATTRS_VALID_TYPE_INVALID = -1,        /**< Invalid validation type */
	MM_ATTRS_VALID_TYPE_NONE,                /**< Do not check validity */
	MM_ATTRS_VALID_TYPE_INT_ARRAY,           /**< validity checking type of integer array */
	MM_ATTRS_VALID_TYPE_INT_RANGE,           /**< validity checking type of integer range */
	MM_ATTRS_VALID_TYPE_DOUBLE_ARRAY,           /**< validity checking type of double array */
	MM_ATTRS_VALID_TYPE_DOUBLE_RANGE,           /**< validity checking type of double range */
} MMAttrsValidType;

/**
 * Enumeration for attribute access flag.
 */
typedef enum {
	MM_ATTRS_FLAG_NONE = 0,                 /**< None flag is set */
	MM_ATTRS_FLAG_READABLE = 1 << 0,        /**< Readable */
	MM_ATTRS_FLAG_WRITABLE = 1 << 1,        /**< Writable */
	MM_ATTRS_FLAG_MODIFIED = 1 << 2,         /**< Modified */

	MM_ATTRS_FLAG_RW = MM_ATTRS_FLAG_READABLE | MM_ATTRS_FLAG_WRITABLE,	/**< Readable and Writable */
} MMAttrsFlag;


/**
 * Validity structure
 */
typedef struct {
	MMAttrsType type;
	MMAttrsFlag flag;
	MMAttrsValidType validity_type;

	/**
	 * a union that describes validity of the attribute.
	 * Only when type is 'MM_ATTRS_TYPE_INT' or 'MM_ATTRS_TYPE_DOUBLE',
	 * the attribute can have validity.
	 */
	union {
		/**
		 * Validity structure for integer array.
		 */
		struct {
			int *array;     /**< a pointer of array */
			int count;      /**< size of array */
			int dval;       /**< default value */
		} int_array;

		/**
		 * Validity structure for integer range.
		 */
		struct {
			int min;        /**< minimum range */
			int max;        /**< maximum range */
			int dval;       /**< default value */
		} int_range;

		/**
		 * Validity structure for double array.
		 */
		struct {
			double *array;  /**< a pointer of array */
			int count;      /**< size of array */
			double dval;    /**< default value */
		} double_array;

		/**
		 * Validity structure for double range.
		 */
		struct {
			double min;     /**< minimum range */
			double max;     /**< maximum range */
			double dval;    /**< default value */
		} double_range;
	};
} MMAttrsInfo;


#if     __GNUC__ >= 4
#define __NULL_TERMINATED __attribute__((__sentinel__))
#else
#define __NULL_TERMINATED
#endif

/**
 * This function is to set the integer value to the attribute by name.
 * @param	attrs		[in] MMAttrs handle
 * @param	attr_name 	[in] attribute name
 * @param	val		[in] integer value to set
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_set_int_by_name(MMHandleType attrs, const char *attr_name, int val);


/**
 * This function is to get the number of attribute in the MMAttrs.
 * @param	attrs		[in]	Handle of attributes list
 * @param	size		[out]	Number of attributes
 * @return	This function returns the number of attributes in the attribute list.
 */
int mm_attrs_get_size(MMHandleType attrs, int *size);


/**
 * This function is to get the name of attribute at the given index.
 * @param	attrs		[in]	Handle of attributes list
 * @param	index		[in]	Index of the attribute
 * @param	name		[out]	Name of attribute
 * @return	This function returns the name of attribute on success, or NULL
 *			on failure.
 */
int mm_attrs_get_name(MMHandleType attrs, int index, char **name);


/**
 * This function is to get the index of attribute at the given name.
 * @param	attrs		[in]	Handle of attributes list
 * @param	attr_name	[in]	Name of attribute
 * @param	index		[out]	Index of attribute
 * @return	This function returns the index of the attribute on success,
 *			or negative value on failure.
 */
int mm_attrs_get_index(MMHandleType attrs, const char *attr_name, int *index);


/**
 * This function is to get the integer value from the attribute by name.
 * @param	attrs		[in]	Handle of attributes list
 * @param	attr_name	[in]	Name of attribute
 * @param	val			[out]	Value of attribute
 * @return 	This function returns attribute value
 */
int mm_attrs_get_int_by_name(MMHandleType attrs, const char *attr_name, int *val);


/**
 * This function is to set the string to attribute by name.
 * @param	attrs		[in] MMAttrs handle
 * @param	attr_name 	[in] attribute name
 * @param	string		[in] string value to set
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_set_string_by_name(MMHandleType attrs, const char *attr_name, const char *string);


/**
 * This function is to get the string from the attribute by name.
 * @param	attrs		[in]	Handle of attributes list
 * @param	attr_name	[in]	Name of attribute
 * @param	val			[out]	Value of attribute
 * @return	This function returns the string value of attribute on success,
 *			or NULL on failure
 */
int mm_attrs_get_string_by_name(MMHandleType attrs, const char *attr_name, char **val);


/**
 * This function is to set the data to the attribute by name.
 * @param	attrs		[in] MMAttrs handle
 * @param	attr_name 	[in] attribute name
 * @param	data		[in] data pointer to set
 * @param	size		[in] data size to set
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_set_data_by_name(MMHandleType attrs, const char *attr_name, void *data, int size);

/**
 * This function is to get the data from the attribute by name.
 * @param	attrs			[in]	Handle of attributes list
 * @param	attr_name	[in]	Name of attribute
 * @param	data			[out] data pointer to set
 * @return	This function returns user defined value on success, or NULL
 *			on failure
 */
int mm_attrs_get_data_by_name(MMHandleType attrs, const char *attr_name, void **data);


/**
 * This function is to retrieve type of attribute.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	attrtype	[out] On return contains type of attribute
 * @return	This function returns MM_ERROR_NONE.
 * @see		MMAttrsType
 */
int mm_attrs_get_type(MMHandleType attrs, int id, MMAttrsType *attrtype);


/**
 * This function is to get flags of attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	flags		[out] On return contains flags of attribute.
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @see		MMAttrsFlag
 */
int mm_attrs_get_flags(MMHandleType attrs, int id, int *flags);


/**
 * This function is to get valid value type of attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	type		[out] On return contains valid value type of attribute
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @see		MMAttrsType
 */
int mm_attrs_get_valid_type(MMHandleType attrs, int id, int *type);


/**
 * This function is to get valid range of attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	min		[out] minimum value of the valid range.
 * @param	max		[out] maximum value of the valid range.
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_get_valid_range(MMHandleType attrs, int id, int *min, int *max);


/**
 * This function is to get valid array of attribute with given id.
 * @param	attrs		[in] list of attributes
 * @param	id		[in] ID of attribute
 * @param	count		[out] number of array
 * @param	array  		[out] on return contains valid array of attribute
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_get_valid_array(MMHandleType attrs, int id, int *count,  int **array);


/**
 * This function is to get valid double type range of attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	min		[out] minimum value of the valid range.
 * @param	max		[out] maximum value of the valid range.
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_get_valid_double_range(MMHandleType h, int idx, double *min, double *max);


/**
 * This function is to get valid double type array of attribute with given id.
 * @param	attrs		[in] list of attributes
 * @param	id		[in] ID of attribute
 * @param	count		[out] number of array
 * @param	array  		[out] on return contains valid array of attribute
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_get_valid_double_array(MMHandleType h, int idx, int *count,  double **array);


/**
 * This function is to set integer value to attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	val		[in] integer value to set
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @see		mm_attrs_get_int
 */
int mm_attrs_set_int(MMHandleType attrs, int id, int val);


/**
 * This function is to get integer value to attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	val		[out] On return contains integer value of attribute
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks 	If type of attributes is not an integer type, the value which is returned by this function is meaningless.
 * @see		mm_attrs_get_int
 */
int mm_attrs_get_int(MMHandleType attrs, int id,  int *val);


/**
 * This function is to set double value to attribute with given id.
 *
 * @param	attrs		[in]	List of attributes
 * @param	id		[in]	ID of attribute
 * @param	val		[in]	Integer value to set
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @see		mm_attrs_get_double
 */
int mm_attrs_set_double(MMHandleType attrs, int id, double val);


/**
 * This function is to set the double value to the attribute by name.
 *
 * @param	attrs		[in]	Handle of attributes list
 * @param	attr_name	[in]	Name of attribute
 * @param	val		[in]	Integer value to set
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 */
int mm_attrs_set_double_by_name(MMHandleType attrs, const char *attr_name, double val);


/**
 * This function is to get double value to attribute with given id.
 *
 * @param	attrs		[in]	List of attributes
 * @param	id		[in]	ID of attribute
 * @param	attrval		[out]	On return contains double value of attribute on success, or invalid value.
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @see		mm_attrs_set_double
 */
int mm_attrs_get_double(MMHandleType attrs, int id, double *attrval);


/**
 * This function is to get the double value from the attribute by name.
 *
 * @param	attrs		[in]	Handle of attributes list
 * @param	attr_name	[in]	Name of attribute
 * @param	val		[out]	Double value to set
 *
 * @return 	This function returns attribute value
 */
int mm_attrs_get_double_by_name(MMHandleType attrs, const char *attr_name, double *val);


/**
 * This function is to set string to attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	string		[in] String to set
 * @param	size		[in] length of string to set
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @see		mm_attrs_get_string
 */
int mm_attrs_set_string(MMHandleType attrs, int id, const char *string, int size);


/**
 * This function is to get string to attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	sval		[in] Placeholder to output string buffer
 * @param	size		[in] The field contains number of characters filled in the buffer
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks 	Application would be responsible for managing/releasing the string
 * @see 	mm_attrs_set_string
 */
int mm_attrs_get_string(MMHandleType attrs, int id,char **sval, int *size);


/**
 * This function is to set pointer to attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	data		[in] data to set
 * @param	size		[in] Length of input data
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks 	Data type is the reference to memory which is allocated by user. The allocated memory must be freed by user.
 * @see		mm_attrs_get_data
 */
int mm_attrs_set_data(MMHandleType attrs, int id, void *data,  int size);

/**
 * This function is to get pointer to attribute with given id.
 * @param	attrs		[in] List of attributes
 * @param	id		[in] ID of attribute
 * @param	data		[out] Placeholder to output data buffer
 * @param	size		[out] The field contains number of bytes filled in the buffer
 * @return 	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Application would be responsible for managing/releasing data
 * @see		mm_attrs_set_data
 */
int mm_attrs_get_data(MMHandleType attrs, int id, void **data, int *size);


/**
 * A function to get  information of the attribute
 *
 * @param	attrs		[in]	List of attributes
 * @param	id		[in]	ID of attribute
 * @param	array		[out] Contains the array of attribute on success,
 *						 or NULL pointer on failure.
 * @param	count		[out] Count of array
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Application would be responsible for managing/releasing the array
 * @see		mm_attrs_set_info
 */
int mm_attrs_get_info(MMHandleType h, int idx, MMAttrsInfo *info);


/**
 * This function is to get array of attribute with given id.
 *
 * @param	attrs		[in]	List of attributes
 * @param	id		[in]	ID of attribute
 * @param	array		[out] Contains the array of attribute on success,
 *						 or NULL pointer on failure.
 * @param	count		[out] Count of array
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Application would be responsible for managing/releasing the array
 * @see		mm_attrs_set_array
 */
int mm_attrs_get_info_by_name(MMHandleType h, const char *attr_name, MMAttrsInfo *info);

/**
 * Sets properties on an object.

 * @param	attrs					[in]	List of attributes
 * @param	err_attr_name			[out] the name of attributes that occurs error. Free this variable after use.
 * @param	attribute_name 	[in]	name of the first property to set
 * @param	...					[in]	value for the first property, followed optionally by more
 *  name/value pairs, followed by %NULL
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Multiple setter of attribute
 * @see		mm_attrs_set_int, mm_attrs_set_string, ...
 */
int mm_attrs_multiple_set(MMHandleType handle,  char **err_attr_name, const char *attribute_name, ...) __NULL_TERMINATED;


/**
 * Gets properties on an object.

 * @param	attrs					[in]	List of attributes
 * @param	err_attr_name			[out] the name of attributes that occurs error. Free this variable after use.
 * @param	attribute_name 	[in]	name of the first property to set
 * @param	...					[in]	value for the first property, followed optionally by more
 *  name/value pairs, followed by %NULL
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Multiple setter of attribute
 * @see		mm_attrs_set_int, mm_attrs_set_string, ...
 */
int mm_attrs_multiple_get(MMHandleType handle,  char **err_attr_name, const char *attribute_name, ...) __NULL_TERMINATED;


/**
 * Sets properties on an object with va_list param.

 * @param	attrs					[in]	List of attributes
 * @param	err_attr_name			[out] the name of attributes that occurs error. Free this variable after use.
 * @param	attribute_name 	[in]	name of the first property to set
 * @param	var_args				[in]	variable arguments
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Multiple setter of attribute
 * @see		mm_attrs_multiple_set
 */
int mm_attrs_set_valist (MMHandleType attrs, char **err_attr_name, const char *attribute_name, va_list var_args);


/**
 * Gets properties on an object with va_list param.

 * @param	attrs					[in]	List of attributes
 * @param	err_attr_name			[out] the name of attributes that occurs error. Free this variable after use.
 * @param	attribute_name 	[in]	name of the first property to set
 * @param	var_args				[in]	variable arguments
 *
 * @return	This function returns MM_ERROR_NONE on success, or negative value with error code.
 * @remarks	Multiple setter of attribute
 * @see		mm_attrs_multiple_get
 */
int mm_attrs_get_valist (MMHandleType attrs, char **err_attr_name, const char *attribute_name, va_list var_args);

/**
 * @}
 */

#ifdef __cplusplus
	}
#endif

#endif /* __MM_ATTRS_H__ */
