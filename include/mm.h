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

 
#ifndef __MM_H__
#define __MM_H__

#include <stdbool.h>

#include <mm_types.h>
#include <mm_error.h>
#include <mm_message.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
	@addtogroup COMMON
	@{
	 * @file		mm.h
	 * @author
	 * @version		1.0
	 * @brief		This file includes all the necessary header files of multimediaframework.
	 
	@mainpage Multimedia Framework

	@par
	This document provides necessary information for developers who are going
	to implement multimedia application such as media player, voice recorder,
	and camera application and so on. Before entering into the detailed
	information, this also has described the overview, architecture design and
	each component of multimedia framework for the purpose of helping
	developers to understand concept or basic knowledge in relation to API for
	themselves.

	@par
	Here is outline as below.

	@par
	- @ref OVERVIEW
	- @ref ARCHITECTURE
	- @ref COMPONENT
	- @ref CONCEPT

	@section OVERVIEW	Overview

	@par
	Multimedia Framework is designed to provide easy to use services for
	developing multimedia applications based on an embedded Linux platform.

	@par
	Multimedia framework API reference has defined APIs to support functions
	as below;

	@par
	- Playback of multimedia contents.
	- Playing system sounds.
	- Controlling volume information.
	- Controlling direction of sound input / output path.
	- Recording video stream from video input device such as camera
	- Recording audio stream from audio input device such as microphone
	- Capturing still image from video input device
	- Extract meta data information from file

	@par
	This document will describe architecture of multimedia framework, basic
	concept of design of application programming, and explain how to use this
	framework

	@section ARCHITECTURE	Architecture Design

	@par
	The multimedia framework can be divided into three parts as follows;

	@par
	- Application Layer that provide high-level APIs to multimedia applications.
	- Internal Layer of Multimedia Framework.
	- Hardware/Platform Dependent Layer.

	@par
	Libraries which provide high-level APIs can be divided into five components
	again; Player, Sound, File, Image, and Camcorder. Basically each component
	can be loaded to memory independently to decrease memory foot print.

	@par
	The internal library is a library which is responsible for encoding /
	decoding multimedia stream. Application layer library uses this library
	for playback, or recording.

	@par
	Hardware / Platform dependent layer has dependency on hardware or platform.
	If hardware or platform has been changed, this layer library must be ported
	to that environment. So this can be called as Porting Layer.

	@par
	This architecture diagram below is a high-level diagram of multimedia
	framework and then also shows how multimedia framework works as well as its
	components.

	@image html		architecture.png "Architecture Diagram" width=12cm
	@image latex	architecture.png "Architecture Diagram" width=12cm

	@par
	Each components will be describes in more detail on Component Description
	section.

	@section COMPONENT	Component Description

	@par
	As mentioned previous section, Multimedia Framework can be divided into
	3 layers. Components for each layer of Multimedia Framework are as below;

	@par
	Application Export Layer

	@par
	- @ref MMFW ATTRS LIBRARY
	- @ref MMFW PLAYER LIBRARY
	- @ref MMFW CAMCORDER LIBRARY
	- @ref MMFW SOUND LIBRARY
	- @ref MMFW FILE LIBRARY

	@par
	Internal (Not exported) Layer

	@par
	- Multimedia Codec (Encoder / Decoder)

	@par
	Hardware/Platform Dependent Layer

	@par
	- MHAL (Multimedia Hardware Abstraction Layer)
	- AV System (Audio Video Input / Output System)

	@par
	Please refer to link for the further detailed description of each component.

	@section CONCEPT	Basic Concept

	@par
	Basic design concept of Multimedia Framework API will be described in this
	section.

	@par
	1. Naming Convention

	@par
	- Multimedia Framework APIs have a prefix with "MM" (stands for
	<B>M</B>ulti<B>M</B>edia <B>F</B>ramework). After this prefix, module name
	is followed by such as "MMPlayer_, MMSnd_, MMCam_".

	@par
	2. Controlled by handle

	@par
	- Basically Multimedia Framework manipulates each instance by handle.
	Camcorder Library, Attributes Library belongs to this case. Sound Library
	does not have instance because it applies attributes directly to system.

	@par
	3. Understand Attributes

	@par
	- Attributes are set of properties which each instance are configured.
	Basic understand is required for manipulating attributes. Please refer to
	@ref MMFW ATTRS LIBRARY "Attribute Library Description" to know how to use.

	@par
	4. Messages

	@par
	- Application can be notified that change of state, error occurs, how much
	time has been elapsed after playing or recording through message callback.
	Message callback will be called as deferred, so any API can be called in
	this callback function.

	@par
	5. Errors

	@par
	- Basically all Multimedia Framework API returns error code as return value.
	It returns zero (MM_ERROR_NONE) on success, or returns error code which is
	negative value. Each error code and range is defined in <mm_error.h> file.

	@par
	6. How to build

	@par
	- Each library for offering high level API will provide Package Config file
	to support pkg-config command. Be sure to that it will be installed on your
	platform SDK directory. If you want to use player library, you just append
	"pkg-config" line to your build script. For example, just append
	"pkg-config --libs --cflags mmplayer" to your build script if you want to
	use player library. The dependency with respect of MMPlayer is already
	described within package config file. Therefore, all of developers have to
	do is just use it by themselves.
*/

#ifdef __cplusplus
}
#endif
/**
	@}
 */
#endif	/* __MM_H__ */
