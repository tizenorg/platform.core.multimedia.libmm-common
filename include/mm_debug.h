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
 


/* ===========================================================================================
EDIT HISTORY FOR MODULE

	This section contains comments describing changes made to the module.
	Notice that changes are listed in reverse chronological order.

when		who							what, where, why
---------	--------------------		----------------------------------------------------------
09/28/07	jhchoi.choi@samsung.com		Created
10/03/30	seungbae.shin@samsung.com	Revised (remove some ifdefs)

=========================================================================================== */
#ifndef __MMF_DEBUG_H__
#define __MMF_DEBUG_H__

#ifdef __cplusplus
	extern "C" {
#endif

enum {
	MMF_DEBUG_LEVEL_0,
	MMF_DEBUG_LEVEL_1,
	MMF_DEBUG_LEVEL_2,
	MMF_DEBUG_LEVEL_3,
	MMF_DEBUG_LEVEL_4,
	MMF_DEBUG_LEVEL_5,
	MMF_DEBUG_LEVEL_ALL,

	MMF_DEBUG_CRITICAL	= MMF_DEBUG_LEVEL_0,
	MMF_DEBUG_ERROR		= MMF_DEBUG_LEVEL_1,
	MMF_DEBUG_WARNING	= MMF_DEBUG_LEVEL_2,
	MMF_DEBUG_INFO		= MMF_DEBUG_LEVEL_3,
	MMF_DEBUG_LOG		= MMF_DEBUG_LEVEL_4,
	MMF_DEBUG_VERBOSE	= MMF_DEBUG_LEVEL_5,

	MMF_DEBUG_PROFILE	= MMF_DEBUG_LEVEL_0,
};

enum {
	MMF_DEBUG_COLOR_DEFAULT		= 0,
	MMF_DEBUG_COLOR_BLACK		= 30,
	MMF_DEBUG_COLOR_RED			= 31,
	MMF_DEBUG_COLOR_GREEN		= 32,
	MMF_DEBUG_COLOR_YELLOW		= 33,
	MMF_DEBUG_COLOR_BLUE		= 34,
	MMF_DEBUG_COLOR_MAGENTA		= 35,
	MMF_DEBUG_COLOR_CYAN		= 36,
	MMF_DEBUG_COLOR_WHITE		= 37,
};

/******************************************************************************
 *
 *	DEBUG CONFIGURATION
 *
 *****************************************************************************/
#ifndef MMF_LOG_OWNER
#define MMF_LOG_OWNER		LOG_NONE
#endif

#ifndef MMF_DEBUG_LEVEL
#define MMF_DEBUG_LEVEL		4
#endif

#ifndef MMF_DEBUG_PREFIX
#define MMF_DEBUG_PREFIX	"MMF"
#endif

#ifndef MMF_DEBUG_FILE
#define MMF_DEBUG_FILE		"/var/log/mmf-log"
#endif

#ifndef MMF_DEBUG_COLOR
#define MMF_DEBUG_COLOR		0
#endif

/******************************************************************************
 *	DEBUG OUTPUT:
 *		0 = None
 *		1 = Log Manager
 *		2 = Debug System
 *		3 = Console
 *		4 = File
 *****************************************************************************/
#ifndef MMF_DEBUG_OUTPUT
#define MMF_DEBUG_OUTPUT	1
#endif

#if (MMF_DEBUG_OUTPUT == 1)
/*
 *	LOG MANAGER
 */
#include <mm_log.h>

#define mmf_debug(type, fmt, arg...)	\
	{	\
		switch (type) {	\
			case MMF_DEBUG_VERBOSE:	\
				log_print_rel(MMF_LOG_OWNER, LOG_CLASS_VERBOSE, fmt, ##arg);	\
				break;	\
			case MMF_DEBUG_LOG:	\
				log_print_rel(MMF_LOG_OWNER, LOG_CLASS_DEBUG, fmt, ##arg);	\
				break;	\
			case MMF_DEBUG_INFO: \
				log_print_rel(MMF_LOG_OWNER, LOG_CLASS_INFO, fmt, ##arg);	\
				break;	\
			case MMF_DEBUG_WARNING:	\
				log_print_rel(MMF_LOG_OWNER, LOG_CLASS_WARNING, fmt, ##arg);	\
				break;	\
			case MMF_DEBUG_ERROR:	\
				log_print_rel(MMF_LOG_OWNER, LOG_CLASS_ERR, fmt, ##arg);	\
				break;	\
			case MMF_DEBUG_CRITICAL:	\
				log_print_rel(MMF_LOG_OWNER, LOG_CLASS_CRITICAL, fmt, ##arg);	\
				break;	\
		}	\
	}

#elif (MMF_DEBUG_OUTPUT == 2)
/*
 *	DEBUG MESSAGE SYSTEM
 */
#include <mid-map.h>
#include <message-framework-mid.h>
#include <debug-message.h>

#define mmf_debug(type, fmt, arg...)	\
	do {	\
		if (type < MMF_DEBUG_LEVEL)	\
			debug_message(MID_FMULTIMEDIA, DEBUG_VERBOSE, fmt, ##arg);	\
	} while(0)

#elif (MMF_DEBUG_OUTPUT == 3)
/*
 *	CONSOLE
 */
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#define mmf_debug(type, fmt, arg...) \
	do {	\
		if (type < MMF_DEBUG_LEVEL && type < MMF_DEBUG_LEVEL_ALL) {	\
			fprintf(stderr, "[%-10.10s] ", MMF_DEBUG_PREFIX);	\
			fprintf(stderr, fmt, ##arg);	\
		}	\
	} while(0)

#define mmf_debug_color(type, color, fmt, arg...) \
	do {	\
		if (type < MMF_DEBUG_LEVEL && type < MMF_DEBUG_LEVEL_ALL) {	\
			fprintf(stderr, "\033[%dm", color);	\
			fprintf(stderr, "[%-10.10s] ", MMF_DEBUG_PREFIX);	\
			fprintf(stderr, fmt, ##arg);	\
			fprintf(stderr, "\033[%dm", MMF_DEBUG_COLOR_DEFAULT);	\
		}	\
	} while(0)

#elif (MMF_DEBUG_OUTPUT == 4)
/*
 *	FILE
 */
#include <stdio.h>
#include <stdlib.h>

#define mmf_debug(type, fmt, arg...)	\
	do {	\
		FILE *fp;

		if (type < MMF_DEBUG_LEVEL) {	\
			fp = fopen(MMF_DEBUG_FILE, "a");	\
			fprintf(stderr, "[%-10.10s] ", MMF_DEBUG_PREFIX);	\
			fprintf(fp, fmt, ##arg);	\
			fclose(fp);	\
		}	\
	} while (0)

#else
/*
 *	NO DEBUG MESSAGE
 */
#define mmf_debug(type, fmd, arg...)

#endif	/* MMF_DEBUG_OUTPUT */

/******************************************************************************
 *
 *	DEBUG FUNCTION MACROS
 *
 *****************************************************************************/
#if (MMF_DEBUG_COLOR == 1 && MMF_DEBUG_OUTPUT == 3)
#define debug_verbose(fmt, arg...)	mmf_debug_color(MMF_DEBUG_VERBOSE,	MMF_DEBUG_COLOR_WHITE, fmt, ##arg)
#define debug_log(fmt, arg...)		mmf_debug_color(MMF_DEBUG_LOG,	MMF_DEBUG_COLOR_YELLOW, fmt, ##arg)
#define debug_msg(fmt, arg...)		mmf_debug_color(MMF_DEBUG_INFO,		MMF_DEBUG_COLOR_DEFAULT, fmt, ##arg)
#define debug_warning(fmt, arg...)	mmf_debug_color(MMF_DEBUG_WARNING,	MMF_DEBUG_COLOR_MAGENTA, fmt, ##arg)
#define debug_error(fmt, arg...)	mmf_debug_color(MMF_DEBUG_ERROR,	MMF_DEBUG_COLOR_RED, fmt, ##arg)
#define debug_critical(fmt, arg...)	mmf_debug_color(MMF_DEBUG_CRITICAL,	MMF_DEBUG_COLOR_RED, fmt, ##arg)
#define debug_profile(fmt, arg...)	mmf_debug_color(MMF_DEBUG_PROFILE,	MMF_DEBUG_COLOR_CYAN, fmt, ##arg)
#define debug_fenter()				mmf_debug_color(MMF_DEBUG_LOG, 		MMF_DEBUG_COLOR_GREEN,		"<ENTER> \n")
#define debug_fleave()				mmf_debug_color(MMF_DEBUG_LOG, 		MMF_DEBUG_COLOR_GREEN,		"<LEAVE> \n")
#define debug_enter(fmt, arg...)	mmf_debug_color(MMF_DEBUG_LOG,		MMF_DEBUG_COLOR_GREEN,		"<ENTER> [<---] " fmt,  ##arg)
#define debug_leave(fmt, arg...)	mmf_debug_color(MMF_DEBUG_LOG, 		MMF_DEBUG_COLOR_CYAN,		"<LEAVE> [--->] " fmt, ##arg)
#else
#define debug_verbose(fmt, arg...)	mmf_debug(MMF_DEBUG_VERBOSE, fmt, ##arg)
#define debug_log(fmt, arg...)		mmf_debug(MMF_DEBUG_LOG, fmt, ##arg)
#define debug_msg(fmt, arg...)		mmf_debug(MMF_DEBUG_INFO, fmt, ##arg)
#define debug_warning(fmt, arg...)	mmf_debug(MMF_DEBUG_WARNING, fmt, ##arg)
#define debug_error(fmt, arg...)	mmf_debug(MMF_DEBUG_ERROR, fmt, ##arg)
#define debug_critical(fmt, arg...)	mmf_debug(MMF_DEBUG_CRITICAL, fmt, ##arg)
#define debug_profile(fmt, arg...)	mmf_debug(MMF_DEBUG_PROFILE,	"<TIMER> " fmt, ##arg)
#define debug_fenter()				mmf_debug(MMF_DEBUG_LOG, 		"<ENTER> \n")
#define debug_fleave()				mmf_debug(MMF_DEBUG_LOG, 		"<LEAVE> \n")
#define debug_enter(fmt, arg...)	mmf_debug(MMF_DEBUG_LOG,		"<ENTER> [<---] " fmt, ##arg)
#define debug_leave(fmt, arg...)	mmf_debug(MMF_DEBUG_LOG,		"<LEAVE> [--->] " fmt, ##arg)
#endif	/* MMF_DEBUG_COLOR */

/* will be deprecated */
#define err_msg(fmt, arg...)		mmf_debug(MMF_DEBUG_ERROR, fmt "\n",##arg)
#define info_msg(fmt, arg...)		mmf_debug(MMF_DEBUG_LOG,		fmt "\n", ##arg)
#define warn_msg(fmt, arg...)		mmf_debug(MMF_DEBUG_WARNING, fmt "\n", ##arg)

#define return_if_fail(expr)	\
	if(!(expr)) {	\
		debug_warning("failed [%s]\n", #expr);	\
		return;	\
	}

#define return_val_if_fail(expr, val)	\
	if (!(expr)) {	\
		debug_warning("failed [%s]\n", #expr);	\
		return val;	\
	}

#define assert_not_reached() \
{ \
	debug_error("assert_not_reached()"); \
	assert(0); \
}


#ifdef __cplusplus
	}
#endif

#endif	/* __MMF_DEBUG_H__ */