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
 *
 * @ingroup   SLP_PG
 * @defgroup   MultiMediaPG  MultiMedia Camcorder,Player,Sound and Radio
@{
<h1 class="pg">Introduction</h1>
<h2 class="pg">Purpose</h2>

The purpose of this document is to give the application developer detailed information on creating and configuring Multimedia applications using the Multimedia Framework API's.


<h2 class="pg">Scope</h2>

The scope of this document is limited to Samsung platform Multimedia Framework API usage. 

<h2 class="pg">Abbreviations</h2>

 	<table>
 		<tr>
  			<td>
  			API
  			</td>
  			<td>
  			Application Programming Interface
  			</td>
  		</tr>
 		<tr>
  			<td>
			  JPEG
  			</td>
  			<td>
			  Joint Photographic Experts Group
  			</td>
  		</tr>
 		<tr>
  			<td>
			  AAC
  			</td>
  			<td>
  			Advanced Audio Coding
  			</td>
  		</tr>
 		<tr>
  			<td>
			  RTP
  			</td>
  			<td>
  			Realtime Transport Protocol
  			</td>
  		</tr>
 		<tr>
  			<td>
			  MMFW
  			</td>
  			<td>
			  Multimedia Framework
  			</td>
  		</tr>
  		<tr>
			<td>
			  PCM
			</td>
			<td>
			  Pulse Code Modulation
			</td>
  		</tr>
	</table>
@}
@defgroup MM_Feature 2.Feature
@ingroup MultiMediaPG
@{
<h1 class="pg">Multimedia Framework Feature</h1>

The Multimedia Framework is designed to provide easy to use services for developing multimedia applications based on an embedded Linux platform.


<h2 class="pg">Features</h2>

- Camcorder
	- Initialize Camcorder for Image capture
	- Initialize Camcorder for Video capture
	- Initialize Camcorder for Audio capture
	- Uninitialize camcorder
	- Capturing Picture
	- Record and Save a Audio/Video file or a Audio only file
	- Record and Cancel saving of a recording file
	- Record, Pause and resume recording
	- Get state of camcorder
	- Start and Stop focus
	- User defined filename for recording file
	- Set VideoStream Callback
	- Set VideoCapture Callback
	- Set Message Callback

- Player
	- Play video/audio from local file, network stream, buffer and memory data
	- Pause and resume playback
	- Seeking the position during playing
	- Setting section repeat
	- Change volume
	- Display subtitle

- Multimedia session
	- Determine application's multimedia functional policy.

- Fileinfo
	- Extracting Media Property Information
	- Extracting Media Meta (Tag) data
	- Extracting Stream information

- Sound
	- Play audio file with simple API (supports uncompressed wav/mp3 file only).
	- Playback or capture PCM with given memory buffer.

- OpenAL
	- Cross platform 3D audio API appropriate for gaming applications.
	- OpenAL in SLP only supports playback function.

- Radio
	- Listening to FM Radio
	- Scan the effective frequencies
	- Seek the frequency
	- Get/Set frequency
	- Get/Set relative volume

- Utility
	- Image processing (Rotation, Resizing, and Color converting)
	- Jpeg encoding and decoding

@}
@defgroup MM_Architecture 1.Architecture
@ingroup MultiMediaPG
@{

<h2 class="pg">Architecture diagram</h2> 


<b>Modules</b>

- Camcorder

The Camcorder Library is a module of the Multimedia framework of SLP. It is responsible for capturing various types of media data such as still image, audio frame, and video frame. According to its operating modes, the camcorder is able to 1) capture Still image, 2) record audio/video frame, and 3) record audio frame only. It provides many convenient functions to control itself. Users can select types of encoders, detailed specifications of video/audio data, and various effects that enhance the quality of the resulting file.
(The current release of SDK might not support all of the camcorder library functions because the camera driver in SDK does not support many APIs should be supported.)

 
- Player

The Player Library provides various functions for a multimedia application to implement playback of media contents. An application can play different formats of audio and audio/video files. The Player Library provides an interface for playing different formats by hiding the creation/construction of various streaming elements from the application, which makes application coding simpler and faster. 


- Multimedia Session

Session means timeline of multimedia resources are used.
Application developer can determine applications' session type as "shared", "exclusive" or "replace".
"Shared" type means the multimedia session is shared with other applications, if possible. The multimedia resources can be used by other applications.
"Exclusive" type means using the multimedia session exclusively. Other applications are not allowed to use multimedia resources during this time.
"Replace" type means this will make stop previous session but allows sharing session with following application.

 
- Fileinfo

The Fileinfo library provides APIs to extract media property information and meta data from media content. These values can be used to display detailed information of the media content without playing it.

 

- Sound

The Sound library provides fuctions to play audio files (uncompressed wav and mp3) with a very simple API and to control sound volume of predefined type.
Also provides functions to playback raw PCM from a memory buffer and capture raw PCM to a memory buffer.


 

- OpenAL

OpenAL is a cross-platform 3D audio API appropriate for use with gaming applications and many other types of audio applications. OpenAL in SLP only supports playback function.
For further information, see official website : http://connect.creativelabs.com/openal/default.aspx

 

- Radio

The Radio Library provides various functions for implementing radio application. It supports the radio operations for HW radio chipset. This library can be only used when HW radio chipset is exist. Radio APIs provides the functionality for playing/stopping radio, changing the frequency, scanning and changing radio sound volumes.

 
- Utility

The Utility library provides simple functions for a multimedia application to process YUV image data and to handle jpeg data. The Utility library for processing image data supports the conversion of color format from YUV to RGB, rotation of images, and resizing the width and height of the picture. The library also saves and loads the image in the Jpeg format. This library includes simple utility features which are related to multimedia.


@image html SLP_MultimediaFW_PG_image001.png

@}
@defgroup MM_Camcorder Camcorder
@ingroup MultiMediaPG
@{

	@brief <sub class="ref">Also see</sub> Use Cases of @ref Camcorder_UC
<h2 class="pg">Camcorder</h2>

This part describes the APIs of the Multimedia Camcorder Library. Camcorder Library is used for recording video from video/audio input devices, capturing still images from the video input device, and audio recording from the audio input device.

Camcorder states can be changed by calling the functions shown in the following figure, "State of Camcorder".
Between each state there is intermediate state, and whilst in this state, any function call which attempts to change the camcorder state will fail.
Recording state and paused state exist when the camcorder is in video-capture mode. When in audio-capture mode, CAPTURING state will be replaced with RECORDING state.

All of the functions which change the state of the camcorder are asynchronous. The function returns immediately and a successful confirmation of state change will be notified through the message callback function. If the state is changed successfully, a state message callback function will be received with the new state, if not an error message will be received.

<b>Functions</b>
@image html SLP_MultimediaFW_PG_image002.png

<center>Figure. State of Camcorder</center>

 

The following table specifies the state changes of the camcorder module.

	<table>
		<tr>
			<td>
			<center><b>FUNCTION</b></center>
			</td>
			<td>
			<center><b>PRE-STATE</b></center>
			</td>
			<td>
			<center><b>POST-STATE</b></center>
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_create()
			</td>
			<td>
			NONE
			</td>
			<td>
			NULL
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_destroy()
			</td>
			<td>
			NULL
			</td>
			<td>
			NONE
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_realize()
			</td>
			<td>
			NULL
			</td>
			<td>
			READY
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_unrealize()
			</td>
			<td>
			READY
			</td>
			<td>
			NULL
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_start()
			</td>
			<td>
			READY
			</td>
			<td>
			PREPARE
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_stop()
			</td>
			<td>
			PREPARE
			</td>
			<td>
			READY
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_capture_start()
			</td>
			<td>
			PREPARE
			</td>
			<td>
			CAPTURING
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_capture_stop()
			</td>
			<td>
			CAPTURING
			</td>
			<td>
			PREPARE
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_record()
			</td>
			<td>
			PREPARED/PAUSED
			</td>
			<td>
			RECORDING
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_pause()
			</td>
			<td>
			RECORDING
			</td>
			<td>
			PAUSED
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_commit()
			</td>
			<td>
			RECORDING/PAUSED
			</td>
			<td>
			PREPARE
			</td>
		</tr>
		<tr>
			<td>
			mm_camcorder_cancel()
			</td>
			<td>
			RECORDING/PAUSED
			</td>
			<td>
			PREPARE
			</td>
		</tr>
	</table> 


The followings are functions to manage camcorder module.

- mm_camcorder_set_message_callback()
	- Set callback for receiving messages from camcorder. Through this callback function, camcorder sends various message including status changes, asynchronous errors, capturing, and limitations.  One thing you have to know is that message callback is working on the main loop of application.  So until releasing the main loop, message callback will not be called.

- mm_camcorder_set_video_stream_callback()
	- Set callback for user defined video stream callback function.  Users can retrieve video frame using registered callback.

- mm_camcorder_set_video_capture_callback()
	- Set callback for user defined video capture callback function.  (Image mode only)

- mm_camcorder_get_state()
	- Get the current state of camcorder.

- mm_camcorder_get_attributes()
	- Get attributes of camcorder with given attribute names. This function can get multiple attributes simultaneously. If one of attribute fails, this function will stop at that point. 'err_attr_name' let you know the name of the attribute.

- mm_camcorder_set_attributes()
	- Set attributes of camcorder with given attribute names. This function can set multiple attributes simultaneously. If one of attribute fails, this function will stop at that point.  'err_attr_name' let you know the name of the attribute.

- mm_camcorder_get_attribute_info()
	- Get detailed information of the attribute.

- mm_camcorder_init_focusing()
	- Initialize auto focusing. If auto focusing is in progressing, stop auto focusing and adjust the camera lens to initial position.

- mm_camcorder_start_focusing()
	- Start focusing.  This function return immediately. However, focusing operation will continue until it gets results. After finishing operation, you can get 'MM_MESSAGE_CAMCORDER_FOCUS_CHANGED' message.

- mm_camcorder_stop_focusing()
	- Stop focusing. This function halts focusing operation.

 
<br><br>
The followings are full proto types of camcorder functions.

- int mm_camcorder_create( MMHandleType* camcorder, MMCamPreset* info );

- int mm_camcorder_destroy(MMHandleType camcorder);

- int mm_camcorder_realize(MMHandleType camcorder);

- int mm_camcorder_unrealize(MMHandleType camcorder);

- int mm_camcorder_start(MMHandleType camcorder);

- int mm_camcorder_stop(MMHandleType camcorder);

- int mm_camcorder_capture_start(MMHandleType camcorder);

- int mm_camcorder_capture_stop(MMHandleType camcorder);

- int mm_camcorder_record(MMHandleType camcorder);

- int mm_camcorder_pause(MMHandleType camcorder);

- int mm_camcorder_commit(MMHandleType camcorder);

- int mm_camcorder_cancel(MMHandleType camcorder);

- int mm_camcorder_set_message_callback(MMHandleType camcorder, MMMessageCallback callback, void *user_data);

- int mm_camcorder_set_video_stream_callback( MMHandleType camcorder, mm_camcorder_video_stream_callback callback, void* user_data );

- int mm_camcorder_set_video_capture_callback( MMHandleType camcorder, mm_camcorder_video_capture_callback callback, void* user_data );

- int mm_camcorder_get_state(MMHandleType camcorder, MMCamcorderStateType* state);

- int #mm_camcorder_get_attributes(MMHandleType camcorder, char **err_attr_name, const char *attribute_name, ...) G_GNUC_NULL_TERMINATED;

- int #mm_camcorder_set_attributes(MMHandleType camcorder, char **err_attr_name, const char *attribute_name, ...) G_GNUC_NULL_TERMINATED;

- int mm_camcorder_get_attribute_info(MMHandleType camcorder, const char *attribute_name, MMCamAttrsInfo *info);

- int mm_camcorder_init_focusing( MMHandleType camcorder );

- int mm_camcorder_start_focusing( MMHandleType camcorder );

- int mm_camcorder_stop_focusing( MMHandleType camcorder );

 
<b>Attributes</b>

- Attribute system
	- Attribute system is an interface to operate camcorder. Depending on each attribute, camcorder behaves differently. Attribute system provides get/set functions. Setting proper attributes, a user can control camcorder as he wants (mm_camcorder_set_attributes()) Also, a user can retrieve the current status of the camcorder, calling getter function(mm_camcorder_get_attributes()). Beware, arguments of mm_camcorder_set_attributes() and mm_camcorder_get_attributes() should be finished with 'NULL'. This is a rule for the variable argument.
	- Besides its value, each Attribute also has 'type' and 'validity type'. 'type' describes variable type that the attribute can have. If you input a value that has wrong type, camcorder will not work properly or will crash. 'validity' describes array or range of values that can be set to the attribute. 'validity type' defines type of the 'validity'.
	- A user can retrieve these values using mm_camcorder_get_attribute_info().


Followings are the attributes which should be set before initialization (mm_camcorder_realize):
	- For more detail information, please refer the doxygen document of Camcorder FW.



<table>
	<tr>
		<td>
		<center><b>Attribute</b></center>
		</td>
		<td>
		<center><b>Description</b></center>
		</td>
	</tr>
    	<tr>
		<td>
		#MMCAM_MODE
		</td>
		<td>
		Mode of camcorder ( still/video/audio )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_AUDIO_DEVICE
		</td>
		<td>
		Audio device ID for capturing audio stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_DEVICE
		</td>
		<td>
		Video device ID for capturing video stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_AUDIO_ENCODER
		</td>
		<td>
		Audio codec for encoding audio stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_VIDEO_ENCODER
		</td>
		<td>
		Video codec for encoding video stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_IMAGE_ENCODER
		</td>
		<td>
		Image codec for capturing still-image
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILE_FORMAT
		</td>
		<td>
		File format for recording media stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_AUDIO_SAMPLERATE
		</td>
		<td>
		Sampling rate of audio stream ( This is an integer field )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_AUDIO_FORMAT
		</td>
		<td>
		Audio format of each sample
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_AUDIO_CHANNEL
		</td>
		<td>
		Channels of each sample ( This is an integer field )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_AUDIO_INPUT_ROUTE
		</td>
		<td>
		Set audio input route
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_FORMAT
		</td>
		<td>
		Format of video stream. This is an integer field
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_FPS
		</td>
		<td>
		Frames per second ( This is an integer field )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_WIDTH
		</td>
		<td>
		Width of input video stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_HEIGHT
		</td>
		<td>
		Height of input video stream
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_FPS_AUTO
		</td>
		<td>
		FPS Auto. When you set true to this attribute, FPS will vary depending on the amount of the light.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_HANDLE
		</td>
		<td>
		Pointer of display buffer or ID of xwindow
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_DEVICE
		</td>
		<td>
		Device ID of display
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_SOURCE_X
		</td>
		<td> 
		X position of source rectangle. When you want to crop the source, you can set the area with this value.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_SOURCE_Y
		</td>
		<td>
		Y position of source rectangle. When you want to crop the source, you can set the area with this value.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_SOURCE_WIDTH
		</td>
		<td>
		Width of source rectangle. When you want to crop the source, you can set the area with this value.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_SOURCE_HEIGHT
		</td>
		<td>
		Height of source rectangle. When you want to crop the source, you can set the area with this value.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_ROTATION
		</td>
		<td>
		Rotation of display
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_VISIBLE
		</td>
		<td>
		Visible of display
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_SCALE
		</td>
		<td>
		A scale of displayed image
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_GEOMETRY_METHOD
		</td>
		<td>
		A method that describes a form of geometry for display
		</td>
	</tr>
</table>
<br>
Followings are the attributes which should be set before recording (mm_camcorder_record()):
<br>

<table>
	<tr>
		<td>
		<center><b>Attribute</b></center>
		</td>
		<td>
		<center><b>Description</b></center>
		</td>
	</tr>
    	<tr>
		<td>
		#MMCAM_AUDIO_ENCODER_BITRATE
		</td>
		<td>
		Bitrate of Audio Encoder
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_VIDEO_ENCODER_BITRATE
		</td>
		<td>
		Bitrate of Video Encoder
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TARGET_FILENAME
		</td>
		<td>
		Target filename. Only used in Audio/Video recording. This is not used for capturing.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TARGET_MAX_SIZE
		</td>
		<td>
		Maximum size of recording file(Kbyte). If the size of file reaches this value.
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TARGET_TIME_LIMIT
		</td>
		<td>
		Time limit of recording file. If the elapsed time of recording reaches this value.
		</td>
	</tr>
</table>
<br>
Followings are the attributes which should be set before capturing (mm_camcorder_capture_start()):
<br>
	
<table>
	<tr>
		<td>
		<center><b>Attribute</b></center>
		</td>
		<td>
		<center><b>Description</b></center>
		</td>
	</tr>
    	<tr>
		<td>
		#MMCAM_IMAGE_ENCODER_QUALITY
		</td>
		<td>
		Encoding quality of Image codec
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAPTURE_FORMAT
		</td>
		<td>
		Pixel format that you want to capture
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAPTURE_WIDTH
		</td>
		<td>
		Width of the image that you want to capture
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAPTURE_HEIGHT
		</td>
		<td>
		Height of the image that you want to capture
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAPTURE_COUNT
		</td>
		<td>
		Total count of capturing
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAPTURE_INTERVAL
		</td>
		<td>
		Interval between each capturing on Multishot ( MMCAM_CAPTURE_COUNT > 1 )
		</td>
	</tr>
</table>
<br>
Followings are the attributes which can be set anytime:
<br>

<table>
	<tr>
		<td>
		<center><b>Attribute</b></center>
		</td>
		<td>
		<center><b>Description</b></center>
		</td>
	</tr>
    	<tr>
		<td>
		#MMCAM_AUDIO_VOLUME
		</td>
		<td>
		Input volume of audio source ( double value )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_DIGITAL_ZOOM
		</td>
		<td>
		Digital zoom level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_OPTICAL_ZOOM
		</td>
		<td>
		Optical zoom level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_FOCUS_MODE
		</td>
		<td>
		Focus mode
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_AF_SCAN_RANGE
		</td>
		<td>
		AF Scan range
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_AF_TOUCH_X
		</td>
		<td>
		X coordinate of touching position
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_AF_TOUCH_Y
		</td>
		<td>
		Y coordinate of touching position
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_AF_TOUCH_WIDTH
		</td>
		<td>
		Width of touching area
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_AF_TOUCH_HEIGHT
		</td>
		<td>
		Height of touching area
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_EXPOSURE_MODE
		</td>
		<td>
		Exposure mode
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_EXPOSURE_VALUE
		</td>
		<td>
		Exposure value
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_F_NUMBER
		</td>
		<td>
		f number of camera
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_SHUTTER_SPEED
		</td>
		<td>
		Shutter speed
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_ISO
		</td>
		<td>
		ISO of capturing image
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_WDR
		</td>
		<td>
		Wide dynamic range
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_ANTI_HANDSHAKE
		</td>
		<td>
		Anti Handshake
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAMERA_FOCAL_LENGTH
		</td>
		<td>
		Focal length of camera lens
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_BRIGHTNESS
		</td>
		<td>
		Brightness level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_CONTRAST
		</td>
		<td>
		Contrast level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_WB
		</td>
		<td>
		White balance
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_COLOR_TONE
		</td>
		<td>
		Color tone (Color effect)
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_SCENE_MODE
		</td>
		<td>
		Scene mode (Program mode)
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_SATURATION
		</td>
		<td>
		Saturation level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_HUE
		</td>
		<td>
		Hue level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_FILTER_SHARPNESS
		</td>
		<td>
		Sharpness level
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_CAPTURE_BREAK_CONTINUOUS_SHOT
		</td>
		<td>
		Set this as true when you want to stop multishot immediately
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_RECT_X
		</td>
		<td>
		X position of display rectangle	( This is only available when MMCAM_DISPLAY_GEOMETRY_METHOD is MM_CAMCORDER_CUSTOM_ROI )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_RECT_Y
		</td>
		<td>
		Y position of display rectangle ( This is only available when MMCAM_DISPLAY_GEOMETRY_METHOD is MM_CAMCORDER_CUSTOM_ROI )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_RECT_WIDTH
		</td>
		<td>
		Width of display rectangle ( This is only available when MMCAM_DISPLAY_GEOMETRY_METHOD is MM_CAMCORDER_CUSTOM_ROI )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DISPLAY_RECT_HEIGHT
		</td>
		<td>
		Height of display rectangle ( This is only available when MMCAM_DISPLAY_GEOMETRY_METHOD is MM_CAMCORDER_CUSTOM_ROI )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_ENABLE
		</td>
		<td>
		Enable to write tags ( If this value is FALSE, none of tag information will be written to captured file )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_IMAGE_DESCRIPTION
		</td>
		<td>
		Image description
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_ORIENTATION
		</td>
		<td>
		Orientation of captured image
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_SOFTWARE
		</td>
		<td>
		software name and version
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_LATITUDE
		</td>
		<td>
		Latitude of captured postion ( GPS information )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_LONGITUDE
		</td>
		<td>
		Longitude of captured postion ( GPS information )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_TAG_ALTITUDE
		</td>
		<td>
		Altitude of captured postion ( GPS information )
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_STROBE_CONTROL
		</td>
		<td>
		Strobe control
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_STROBE_MODE
		</td>
		<td>
		Operation Mode of strobe
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DETECT_MODE
		</td>
		<td>
		Detection mode
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DETECT_NUMBER
		</td>
		<td>
		Total number of detected object
		</td>
	</tr>
	<tr>
		<td>
		#MMCAM_DETECT_FOCUS_SELECT
		</td>
		<td>
		Select one of detected objects
		</td>
	</tr>
</table>
@}
@defgroup Camcorder_uc1 Initialize Camcorder for Image capture
@ingroup Camcorder_UC
@{

<h2 class="pg">Initialize Camcorder for Image capture	</h2>

- Purpose
	- Start preview for capturing image

 

The camcorder module is initialized for Image capture by using the following steps:

-# Create the camcorder handle using mm_camcorder_create().
-# Set message callback. Message callback is a handler for camcorder message. If camcorder is trying to deliever a certain signal that happens on runtime, it uses this method. For more detail information, refer "Set Message Callback"
-# Set video capture callback. Video capture callback is a handler for the captured image. This is the only method to deliever the image. (Do not use 'MMCAM_TARGET_FILENAME' for image capturing. It can't handle multishot.) For more detail information, refer "Set VideoCapture Callback"
-# Set various attributes using mm_camcorder_set_attributes(). You can set as many attributes as you want. If you don't set any attributes, it will operate with the default values. But as a minimum, you have to set 'MMCAM_DISPLAY_HANDLE'. This is the attribute to deliever display pointer or index, such as xid of x window. So if you don't set this, there is no way to display the image.
-# Allocate resources (memory, device node, etc) for camcorder handle using mm_camcorder_realize().
-# Start receiving input video stream (previewing) calling mm_camcorder_start().

 

The following is a sample code:

@code
MMHandleType hcam = 0;

struct appdata
{
	...
	int xid;
	...
};
struct appdata ad;


static gboolean initialize_image_capture()

{

      int err;

      MMCamPreset cam_info;

      char *err_attr_name = NULL;

      void * hdisplay = NULL;

      int hsize = 0;

 

      cam_info.videodev_type = MM_VIDEO_DEVICE_CAMERA0;

      err = mm_camcorder_create(&hcam, &cam_info);

 

      if (err != MM_ERROR_NONE)

      {

                  printf("Fail to call mm_camcorder_create = %x\n", err);

                  return FALSE;

      }

 

      mm_camcorder_set_message_callback(hcam,(MMMessageCallback)msg_callback, (void*)hcam);

      mm_camcorder_set_video_capture_callback(hcam,(mm_camcorder_video_capture_callback)camcordertest_video_capture_cb, (void*)hcam);

 

      hdisplay = &ad.xid;

      hsize = sizeof(ad.xid);

 

      // camcorder attribute setting

      err = mm_camcorder_set_attributes((MMHandleType)hcam, &err_attr_name,

            MMCAM_MODE, MM_CAMCORDER_MODE_IMAGE,

            MMCAM_IMAGE_ENCODER, MM_IMAGE_CODEC_JPEG,

            MMCAM_CAMERA_WIDTH, 640,

            MMCAM_CAMERA_HEIGHT, 480,

            MMCAM_CAMERA_FORMAT, MM_PIXEL_FORMAT_YUYV,

            MMCAM_CAMERA_FPS, 30,

            MMCAM_DISPLAY_ROTATION, MM_DISPLAY_ROTATION_270,

            MMCAM_DISPLAY_HANDLE, (void*) hdisplay,          hsize,

            MMCAM_CAPTURE_FORMAT, MM_PIXEL_FORMAT_ENCODED,

            MMCAM_CAPTURE_WIDTH, 640,

            MMCAM_CAPTURE_HEIGHT, 480,

            NULL);

 

      if (err < 0)

      {

            printf("Set attrs fail. (%s:%x)\n", err_attr_name, err);

            if (err_attr_name) {

                  free(err_attr_name);

                  err_attr_name = NULL;

                  return FALSE;

            }

      }

 

      err =  mm_camcorder_realize(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_realize  = %x\n", err);

            return FALSE;

      }

 

      // start camcorder 

      err = mm_camcorder_start(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_start  = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}

@endcode

Basically, you can check the return value to determine whether the function succeeded. But camcorder is composed of several thread context. So you have to check error code delievered by the message callback as well. It will notify you of errors that happened in other asynchronous contexts.
 
@}
@defgroup Camcorder_uc2 Initialize Camcorder for Video capture
@ingroup Camcorder_UC
@{

<h2 class="pg">Initialize Camcorder for Video capture</h2>
- Purpose
	- Start preview for video recording

 

Everything is the same with "Initialize Camcorder for Image capture" except for two things:

-# You don't need to set 'mm_camcorder_set_video_capture_callback' because the function is for capturing image.
-# Set different attributes. For example, you have to specify types of encoder for audio and video, types of fileformat (this will define muxer). You should also define detail settings of video and audio input. Set proper filename to 'MMCAM_TARGET_FILENAME', too.

 

 

The following is a sample code: 

@code
MMHandleType hcam = 0;

struct appdata
{
	...
	int xid;
	...
};
struct appdata ad;
 

static gboolean initialize_video_capture()

{

      int err;

      MMCamPreset cam_info;

      char *err_attr_name = NULL;

      void * hdisplay = NULL;

      int hsize = 0;

 

      cam_info.videodev_type = MM_VIDEO_DEVICE_CAMERA0;

      err = mm_camcorder_create(&hcam, &cam_info);

      if (err != MM_ERROR_NONE)
      {

                  printf("Fail to call mm_camcorder_create = %x\n", err);

                  return FALSE;

      }

 

      mm_camcorder_set_message_callback(hcam,(MMMessageCallback)msg_callback, hcam);

 

      hdisplay = &ad.xid;

      hsize = sizeof(ad.xid);

 

      // camcorder attribute setting 

      err = mm_camcorder_set_attributes((MMHandleType)hcam, &err_attr_name,

            MMCAM_MODE, MM_CAMCORDER_MODE_VIDEO,

            MMCAM_AUDIO_DEVICE, MM_AUDIO_DEVICE_MIC,

            MMCAM_AUDIO_ENCODER, MM_AUDIO_CODEC_AAC,

            MMCAM_VIDEO_ENCODER, MM_VIDEO_CODEC_MPEG4,

            MMCAM_FILE_FORMAT, MM_FILE_FORMAT_3GP,

            MMCAM_CAMERA_WIDTH, 1280,

            MMCAM_CAMERA_HEIGHT, 720,

            MMCAM_CAMERA_FORMAT, MM_PIXEL_FORMAT_NV12,

            MMCAM_CAMERA_FPS, 30,

            MMCAM_AUDIO_SAMPLERATE, 44100,

            MMCAM_AUDIO_FORMAT, MM_CAMCORDER_AUDIO_FORMAT_PCM_S16_LE,

            MMCAM_AUDIO_CHANNEL, 2,

            MMCAM_AUDIO_INPUT_ROUTE, MM_AUDIOROUTE_CAPTURE_NORMAL,

            MMCAM_DISPLAY_ROTATION, MM_DISPLAY_ROTATION_270,

            MMCAM_DISPLAY_HANDLE, (void*) hdisplay,        hsize,

            MMCAM_TARGET_FILENAME, TARGET_FILENAME, strlen(TARGET_FILENAME),

            NULL);

 

      if (err < 0)

      {

            printf("Set attrs fail. (%s:%x)\n", err_attr_name, err);

            if (err_attr_name) {

                  free(err_attr_name);

                  err_attr_name = NULL;

                  return FALSE;

            }

      }

 

      err =  mm_camcorder_realize(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_realize  = %x\n", err);

            return FALSE;

      }

 

      // start camcorder 

      err = mm_camcorder_start(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_start  = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc3 Initialize Camcorder for Audio capture
@ingroup Camcorder_UC
@{

<h2 class="pg">Initialize Camcorder for Audio capture</h2>
- Purpose
	- Prepare for audio recording

Everything is the same with "Initialize Camcorder for Video capture" except for attributes settings:
-# In this case, you don't need to set video information.

 

The following is a sample code: 

@code
MMHandleType hcam = 0;

struct appdata
{
	...
	int xid;
	...
};
struct appdata ad;


static gboolean initialize_audio_capture()

{

      int err;

      MMCamPreset cam_info;

      char *err_attr_name = NULL;

      void * hdisplay = NULL;

      int hsize = 0;

 

      cam_info.videodev_type = MM_VIDEO_DEVICE_NONE;

 

      err = mm_camcorder_create(&hcam, &cam_info);

 

      if (err != MM_ERROR_NONE)

      {

            printf("Fail to call mm_camcorder_create = %x\n", err);

            return FALSE;

      }

 

      mm_camcorder_set_message_callback(hcam,(MMMessageCallback)msg_callback, (void*)hcam);

 

      hdisplay = &ad.xid;

      hsize = sizeof(ad.xid);

 

     // camcorder attribute setting 

      err = mm_camcorder_set_attributes((MMHandleType)hcam, &err_attr_name,

            MMCAM_MODE, MM_CAMCORDER_MODE_AUDIO,

            MMCAM_AUDIO_DEVICE, MM_AUDIO_DEVICE_MIC,

            MMCAM_AUDIO_ENCODER, MM_AUDIO_CODEC_AAC,

            MMCAM_FILE_FORMAT, MM_FILE_FORMAT_3GP,

            MMCAM_AUDIO_SAMPLERATE, 44100,

            MMCAM_AUDIO_FORMAT, MM_CAMCORDER_AUDIO_FORMAT_PCM_S16_LE,

            MMCAM_AUDIO_CHANNEL, 2,

            MMCAM_AUDIO_INPUT_ROUTE, MM_AUDIOROUTE_CAPTURE_NORMAL,

            MMCAM_TARGET_FILENAME, TARGET_FILENAME, strlen(TARGET_FILENAME),

            MMCAM_TARGET_TIME_LIMIT, 360000,

            NULL);

 

      if (err < 0)

      {

            printf("Set attrs fail. (%s:%x)\n", err_attr_name, err);

            if (err_attr_name) {

                  free(err_attr_name);

                  err_attr_name = NULL;

                  return FALSE;

            }

      }

 

      err =  mm_camcorder_realize(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_realize  = %x\n", err);

            return FALSE;

      }

 

      // start camcorder

      err = mm_camcorder_start(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_start  = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc4 Uninitialize camcorder
@ingroup Camcorder_UC
@{

<h2 class="pg">Uninitialize camcorder</h2>
- Purpose
	- Destory camcorder handle and resources

- Preliminary condition
	- Camcorder is lauched for Image capture, Video capture, or Audio capture.

 

The initialized camcorder is uninitialized by using the following steps:
-# Stop receiving the video input stream using mm_camcorder_stop(). In audio capture mode, it will stop pipeline itself.
-# Free the allocated memory and release devices calling mm_camcorder_unrealize().
-# Destroy the camcorder handle instance using mm_camcorder_destroy().

 

The following is a sample code:

@code
static gboolean uninitialize_camcorder()

{

      int err;

 

      err =  mm_camcorder_stop(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_stop  = %x\n", err);

            return FALSE;

      }

     

      err =  mm_camcorder_unrealize(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_unrealize  = %x\n", err);

            return FALSE;

      }

 

      err = mm_camcorder_destroy(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_destroy  = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}
@endcode
@}
@defgroup Camcorder_uc5 Capturing Picture
@ingroup Camcorder_UC
@{

<h2 class="pg">Capturing Picture</h2>
- Purpose
	- Capturing still image

- Preliminary condition
	- Camcorder is launched for Image capture mode. Refer to "Initialize Camcorder for Image capture".

Steps:
-# Initialize camcorder for image capture as explained in "Initialize Camcorder for Image capture".
-# Start capturing the still image using mm_camcorder_capture_start().  The status of the camcorder is changed to 'MM_CAMCORDER_STATE_CAPTURING' after success.
-# You can stop capturing the still image using mm_camcorder_capture_stop(). But do not call mm_camcorder_capture_stop(), just after calling mm_camcorder_capture_start(). Because captured image is retrieved asynchronously, you can call mm_camcorder_capture_stop() after receiving the 'MM_MESSAGE_CAMCORDER_CAPTURE' message.
-# Beware! Since message callback of camcorder is operated on main loop of the application, you shouldn't hold main loop when you are waiting for the message 'MM_MESSAGE_CAMCORDER_CAPTURED'.
-# Recommended implementation is
	-# Just call mm_camcorder_capture_start() and return
	-# Wait for capture callback that you registered (the callback function that you set to 'mm_camcorder_set_video_capture_callback')
	-# Wait for 'MM_MESSAGE_CAMCORDER_CAPTURED' message
	-# Then call mm_camcorder_capture_stop() in the context of the message or another idle callback.
-# Uninitialize camcorder as explained in "Uninitialize camcorder"

 

The following is a sample code:

@code
static gboolean capturing_picture()

{

      int err;

 

      err =  mm_camcorder_capture_start(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_capture_start  = %x\n", err);

            return FALSE;

      }

 

      // mm_camcorder_capture_stop should be called after getting the message
      // - MM_MESSAGE_CAMCORDER_CAPTURED message


      return TRUE;

}
@endcode


Handling for captured message, please refer to the callback function of "Set Message Callback".

@}
@defgroup Camcorder_uc6 Record and Save a Audio/Video file or a Audio only file
@ingroup Camcorder_UC
@{

<h2 class="pg">Record and Save a Audio/Video file or a Audio only file</h2>
- Purpose
	- Start recording and save the file

- Preliminary condition
	- Camcorder is launched for Video capture mode. (Refer "Initialize Camcorder for Video capture".)
	- Or Camcorder is launched for Audio capture mode. (Refer "Initialize Camcorder for Video capture".)

 

A video is recorded and saved by camcorder by using the following steps:
-# Initialize camcorder for video capture or audio capture
-# Start audio/video recording using mm_camcorder_record().
-# Save the recorded Video file using mm_camcorder_commit().
-# Uninitialize camcorder. Refer "Uninitialize camcorder".

The procedure of "Audio recording" and "Audio/Video recording" is just same except for settings for video related attributes.

 

The following is a sample code:

@code
static gboolean record_and_save_video_file()

{

      int err;

 

      // Start recording 

      err =  mm_camcorder_record(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_record  = %x\n", err);

            return FALSE;

      }


      // Wait while recording 
      // ...
 

      // Save file /

      err =  mm_camcorder_commit(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_commit  = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}
@endcode

In the above example code, MMCamcorderRecord and MMCamcorderCommit will return immediately, but whether the video is captured and saved successfully or not is known through a callback function which is set using the API MMCamcorderSetMessageCallback.

@}

@defgroup Camcorder_uc7 Record and Cancel saving of a recording file
@ingroup Camcorder_UC
@{
<h2 class="pg">Record and Cancel saving of a recording file</h2>
- Purpose
	- Cancel the operation while recording.

- Preliminary condition
	- Camcorder is launched for Video capture mode. (Refer "Initialize Camcorder for Video capture".)
	- Or Camcorder is launched for Audio capture mode. (Refer "Initialize Camcorder for Video capture".)

 

A video is recorded and not saved by camcorder by using the following steps:
-# Initialize camcorder for video capture or audio capture
-# Start audio/video recording using mm_camcorder_record().
-# Cancel saving the recorded Video file using mm_camcorder_cancel().
-# Uninitialize camcorder. Refer "Uninitialize camcorder".

 

The following is a sample code:

@code

static gboolean record_and_cancel_video_file()

{

      int err;

 

      // Start recording 

      err =  mm_camcorder_record(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_record  = %x\n", err);

            return FALSE;

      }

 
      // Wait while recording  
      // ...
 

      // Cancel recording 

      err =  mm_camcorder_cancel(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_cancel = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}
@endcode
@}

@defgroup Camcorder_uc8 Record, Pause and resume recording
@ingroup Camcorder_UC
@{

<h2 class="pg">Record, Pause and resume recording</h2>
- Purpose
	- Pause and Resume operation while recording

- Preliminary condition
	- Camcorder is launched for Video capture mode. (Refer "Initialize Camcorder for Video capture".)
	- Or Camcorder is launched for Audio capture mode. (Refer "Initialize Camcorder for Video capture".)


Recording, pausing and resuming recording of a video file is accomplished by using the following steps:
-# Initialize camcorder for video capture or audio capture
-# Start recording calling mm_camcorder_record().
-# Pause recording. mm_camcorder_pause().
-# When you want to resume recording, call mm_camcorder_record again.
-# Save the recorded file. mm_camcorder_commit().
-# Uninitialize camcorder. Refer "Uninitialize camcorde".

 
The following is a sample code:

@code
static gboolean record_pause_and_resume_recording()

{

      int err;

 

      // Start recording 

      err =  mm_camcorder_record(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_record  = %x\n", err);

            return FALSE;

      }

 
      // Wait while recording  
      // ...
 

      // Pause 

      err =  mm_camcorder_pause(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_pause  = %x\n", err);

            return FALSE;

      }

 
      // Pausing...  
 

      // Resume 

      err =  mm_camcorder_record(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_record  = %x\n", err);

            return FALSE;

      }

 
      // Wait while recording  
      // ...
 

      // Save file 

      err =  mm_camcorder_commit(hcam);

      if (err < 0)

      {

            printf("Fail to call mm_camcorder_commit  = %x\n", err);

            return FALSE;

      }

 

      return TRUE;

}
@endcode


Even though recording is paused, preview is continuously displayed.

@}
@defgroup Camcorder_uc9 Get state of camcorder
@ingroup Camcorder_UC
@{

<h2 class="pg">Get state of camcorder</h2>
- Purpose
	- Get the current state of camcorder

If handle is available, you can get the current status of camcorder using mm_camcorder_get_state()

The following is a sample code:

@code
static gboolean get_state_of_camcorder()

{

      MMCamcorderStateType state;

 

      mm_camcorder_get_state(hcam, &state);

      printf("Current status is %d\n", state);

 

      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc10 Start and Stop focus
@ingroup Camcorder_UC
@{


<h2 class="pg">Start and Stop focus</h2>
- Purpose
	- Adjust lens focus

- Preliminary condition
	- Camcorder is launched for Image or Video capture mode. Refer "Initialize Camcorder for Image capture" and "Initialize Camcorder for Video capture".

 

Starting and Stopping focus feature of camcorder:
-# Initialize camcorder for image or video capture as explained in "Initialize Camcorder for Video capture" or "Initialize Camcorder for Image capture".
-# Set proper focusing mode using attribute 'MMCAM_CAMERA_FOCUS_MODE' and 'MMCAM_CAMERA_AF_SCAN_RANGE'.
-# Initialize auto focus mode and adjust the camera lens to initial position using mm_camcorder_init_focusing().
-# Start focusing of camcorder using mm_camcorder_start_focusing().
-# Focusing state will be sent through message callback.  (MM_MESSAGE_CAMCORDER_FOCUS_CHANGED)
-# If you want to stop focusing immediately, call mm_camcorder_stop_focusing().
-# But in general case, you don't need to call this. Just wait the message.
-# Uninitialize camcorder. Refer "Uninitialize camcorder".


The following is a samsple code

@code
static gboolean start_autofocus()

{

      int err;

      char * err_attr_name = NULL;

 

      // Set focus mode to 'AUTO' and scan range to 'AF Normal' 

      err = mm_camcorder_set_attributes((MMHandleType)hcam, &err_attr_name,

            MMCAM_CAMERA_FOCUS_MODE, MM_CAMCORDER_FOCUS_MODE_AUTO,

            MMCAM_CAMERA_AF_SCAN_RANGE, MM_CAMCORDER_AUTO_FOCUS_NORMAL,

            NULL);

 

      if (err < 0)

      {

            printf("Set attrs fail. (%s:%x)\n", err_attr_name, err);

            if (err_attr_name) {

                  free(err_attr_name);

                  err_attr_name = NULL;

                  return FALSE;

            }

      }

      mm_camcorder_init_focusing(hcam);

      mm_camcorder_start_focusing(hcam);

      printf("Waiting for adjusting focus\n");

 

      // Waiting for 'MM_MESSAGE_CAMCORDER_FOCUS_CHANGED' 
      // ...
 

      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc11 User defined filename for recording file
@ingroup Camcorder_UC
@{

<h2 class="pg">User defined filename for recording file</h2>

To Save an video or audio captured file with user defined name, you have to set an attribute named 'MMCAM_TARGET_FILENAM'.

In image capture mode, there is no interface to set the name of captured file because camcorder gives you a captured buffer directly. You can create an image file with proper name in the application.

 
The following is a samsple code

@code
static gboolean filename_setting()

{

      int err;

      char * new_filename =  "new_name.mp4";

 

      // camcorder attribute setting 

      err = mm_camcorder_set_attributes((MMHandleType)hcam, NULL,

                             MMCAM_TARGET_FILENAME, new_filename, strlen(new_filename),

                             NULL);

 

      printf("New file name (%s)\n", new_filename);

 
      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc12 Set VideoStream Callback
@ingroup Camcorder_UC
@{

<h2 class="pg">Set VideoStream Callback</h2>

MMCamcorderSetVideoStreamCallback API is used to set callback for receiving video stream data (preview) from the camcorder.

 

The following is a sample code:

@code
static gboolean set_video_stream_callback()

{

      mm_camcorder_set_video_stream_callback(hcam, (mm_camcorder_video_stream_callback)camcordertest_video_stream_cb, (void*)hcam);

 
      return TRUE;

}
@endcode
@code
static int

camcordertest_video_stream_cb(MMCamcorderVideoStreamDataType *stream, void *user_param)

{

      int nret = 0;

 

      printf("stream cb is called(%p, %d, %d)\n",  stream->data, stream->width, stream->height);

 

      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc13 Set VideoCapture Callback
@ingroup Camcorder_UC
@{

<h2 class="pg">Set VideoCapture Callback</h2>

mm_camcorder_set_video_capture_callback() is used to set callback for receiving still capture data from the camcorder. In here, you can handle the result data.

 
The following is a sample code:

@code
mm_camcorder_set_video_capture_callback(hcam,(mm_camcorder_video_capture_callback)

camcordertest_video_capture_cb, (void*)hcam);
@endcode
@code
static int

camcordertest_video_capture_cb(MMCamcorderCaptureDataType *src, MMCamcorderCaptureDataType *thumb, void *preview)

{

      int nret = 0;

      char m_filename[MAX_STRING_LEN];

      FILE* fp=NULL;

 

      sprintf(m_filename, "%s%03d.jpg", "./stillshot_", stillshot_count++);

 

      printf("filename : %s\n",  m_filename);

 

      fp=fopen(m_filename, "w+");

      if(fp==NULL)

      {

            printf("FileOPEN error!!\n");

            return FALSE;

      }

      else

      {

            printf("open success\n\n");

            if(fwrite(src->data, src->length, 1, fp )!=1)

            {

                  printf("File write error!!\n");

                  return FALSE;

            }

            printf("write success\n");

      }

      fclose(fp);

      printf("Capture done!\n");

 

      return TRUE;

}
@endcode

@}
@defgroup Camcorder_uc14 Set Message Callback
@ingroup Camcorder_UC
@{

<h2 class="pg">Set Message Callback</h2>

The following is a sample code:
@code
mm_camcorder_set_message_callback(hcam,(MMMessageCallback)msg_callback, (void*)hcam);
@endcode

The following code snippet explains the callback function for 'MMMessageCallback':
- First argument gives the index of the message. You can handle each message with the value.
- Second argument has a parameter structure that holds useful values for application. The original parameter type is 'MMMessageParamType'.
- It has several fields for message including union structure. By checking 'union_type' field, you can determine which type of union is used. For the type of union, refer 'MMMessageUnionType' in 'mm_types.h'.
- One message type only has one specific union in anycase. Please refer following table


<table>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_STATE_CHANGED
		</td>
		<td>
		MM_MSG_UNION_STATE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_STATE_CHANGED_BY_ASM
		</td>
		<td>
		MM_MSG_UNION_STATE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_RECORDING_STATUS
		</td>
		<td>
		MM_MSG_UNION_RECORDING_STATUS
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_FIRMWARE_UPDATE
		</td>
		<td>
		MM_MSG_UNION_FIRMWARE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_TIME_LIMIT
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_MAX_SIZE
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_NO_FREE_SPACE
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_ERROR
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_FOCUS_CHANGED
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_CURRENT_VOLUME
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_CAMCORDER_CAPTURED
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
	<tr>
		<td>
		MM_MESSAGE_READY_TO_RESUME
		</td>
		<td>
		MM_MSG_UNION_CODE
		</td>
	</tr>
</table>
	
- 'MM_MESSAGE_READY_TO_RESUME' is a message type that notifies that the camcorder is able to start again after being halting by internal session manager.

@code
static gboolean msg_callback(int message, void *msg_param, void *user_param)

{

      MMHandleType hcamcorder = (MMHandleType)user_param;

      MMMessageParamType *param = (MMMessageParamType *) msg_param;

      int err = 0;

     

      switch (message) {

            case MM_MESSAGE_CAMCORDER_ERROR:

                  printf("MM_MESSAGE_CAMCORDER_ERROR : code = %x\n", param->code);

                  break;

            case MM_MESSAGE_CAMCORDER_STATE_CHANGED:

                  g_current_state = param->state.current;

                  break;

 

            case MM_MESSAGE_CAMCORDER_CAPTURED:

            {

                  //Get mode of camcorder

                  int mode = 0;

                  err = mm_camcorder_get_attributes(hcamcorder, NULL,

                        MMCAM_MODE,  &mode,

                         NULL);

 

                  if (mode == MM_CAMCORDER_MODE_IMAGE)

                  {

                        printf("Stillshot Captured!!(number=%d)\n", param->code);

 

                        err =  mm_camcorder_capture_stop(hcam);

                        if (err < 0)

                        {

                             printf("Fail to call mm_camcorder_capture_start= %x\n", err);

                             return FALSE;

                        }

                  }

                  else

                  {

                        //Audio/Video recording

                        MMCamRecordingReport* report ;

 

                        if (param)

                             report = (MMCamRecordingReport*)(param->data);

                        else

                             return FALSE;

 

                        printf("Recording Complete(filename=%s)\n", report->recording_filename);

 

                        if (report->recording_filename)

                             free(report->recording_filename);

 

                        if (report)

                             free(report);

                  }

            }

                  break;

            case MM_MESSAGE_CAMCORDER_RECORDING_STATUS:

            {

                  unsigned int elapsed;

                  elapsed = param->recording_status.elapsed / 1000;

                  if (elapsed_time != elapsed) {

                        unsigned int temp_time;

                        int hour, minute, second;

                        elapsed_time = elapsed;

                        temp_time = elapsed;

                        hour = temp_time / 3600;

                        temp_time = elapsed % 3600;

                        minute = temp_time / 60;

                        second = temp_time % 60;

                        printf("Current Time - %d:%d:%d\n", hour, minute, second);

                  }

            }

                  break;                 

            case MM_MESSAGE_CAMCORDER_MAX_SIZE:

            {    

                  printf("Reach Size limitation.\n");

 

                  // After reaching max size, Camcorder starts to drop all buffers that

                  it receives. You have to call mm_camcorder_commit() to finish recording. 

                  err = mm_camcorder_commit(hcamcorder);

 

                  if (err < 0)

                  {

                        printf("Save recording mm_camcorder_commit  = %x\n", err);

                  }

            }

                  break;

            case MM_MESSAGE_CAMCORDER_NO_FREE_SPACE:

            {

                  printf("There is no space in storage.\n");

 

                  // If there is no free space to save recording frame, Camcorder starts to

		     drop all buffers that it receives.

		     You have to call mm_camcorder_commit() to finish recording. 

                  err = mm_camcorder_commit(hcamcorder);

 

                  if (err < 0)

                  {

                        printf("Save recording mm_camcorder_commit  = %x\n", err);

                  }

            }

                  break;

            case MM_MESSAGE_CAMCORDER_TIME_LIMIT:

            {

                  printf("Reach time limitation.\n");

 

                  // After reaching time limit, Camcorder starts to drop all buffers that it

		     receives. You have to call mm_camcorder_commit() to finish recording. 

                  err = mm_camcorder_commit(hcamcorder);

 

                  if (err < 0)

                  {

                        printf("Save recording mm_camcorder_commit  = %x\n", err);

                  }

            }

                  break;

            case MM_MESSAGE_CAMCORDER_FOCUS_CHANGED:

            {

                  printf( "Focus State changed. State:[%d]\n", param->code );

            }

                  break;

            default:

                  break;

      }

 

      return TRUE;

}
@endcode

@}

@defgroup MM_Player Player
@ingroup MultiMediaPG
@{

<h2 class="pg">Player</h2>
	@brief <sub class="ref">Also see</sub> Use Cases of @ref Player_UC

This section describes APIs used for playback of multimedia contents.

 

Player can have 5 states, and each state can be changed by calling the following functions as described in "State of mm_player" diagram. 

	<table>
    
    		<tr>
        			<td>
            <b>FUNCTION</b>
       			<td>
            <b>PRE-STATE</b><b></b>
        			<td>
            <b>POST-STATE</b><b></b>
       			<td>
            <b>SYNC TYPE</b>
    		<tr>
       			<td>
            <p>mm_player_create()
        			<td>
            NONE
        			<td>
            NULL
        			<td>
            SYNC
    		<tr>
       			<td>
            <p>mm_player_destroy()
        			<td>
            NULL
        			<td>
            NONE
        			<td>
            SYNC
    		<tr>
       			<td>
            <p>mm_player_realize()
        			<td>
            NULL
        			<td>
            READY
        			<td>
            SYNC
    		<tr>
       			<td>
            <p>mm_player_unrealize()
        			<td>
            READY
        			<td>
            NULL
        			<td>
            SYNC
    		<tr>
       			<td>
            <p>mm_player_start()
        			<td>
            READY
        			<td>
            PLAYING
        			<td>
            ASYNC
    		<tr>
       			<td>
            <p>mm_player_stop()
        			<td>
            PLAYING
        			<td>
            READY
        			<td>
            SYNC
    		<tr>
       			<td>
            <p>mm_player_pause()
        			<td>
            PLAYING
        			<td>
            PAUSED
        			<td>
            ASYNC
    		<tr>
       			<td>
            <p>mm_player_resume()
        			<td>
            PAUSED
        			<td>
            PLAYING
        			<td>
            ASYNC    
	</table>


@image html SLP_MultimediaFW_PG_image003.png
Figure. State of MMPlayer

 

Most of functions which change player state work as synchronous . But, mm_player_start() should be used asynchronously. Both  mm_player_pause() and mm_player_resume() should also be used asynchronously in the case of streaming data. So, application has to confirm the result through message callback function.

 

Note: "None" and "Null" state could be reached from any state by calling mm_player_destroy() and mm_player_unrealize().


The following are supported functions in the player module.
		- int mm_player_set_volume(MMHandleType player, MMPlayerVolumeType *volume)
		- int mm_player_get_volume(MMHandleType player, MMPlayerVolumeType *volume)
		- int mm_player_get_mute(MMHandleType player, int *mute)
		- int mm_player_set_mute(MMHandleType player, int mute)
		- int mm_player_set_position(MMHandleType player, MMPlayerPosFormatType format, int pos)
		- int mm_player_get_position(MMHandleType player, MMPlayerPosFormatType format, int *pos)
		- int mm_player_activate_section_repeat(MMHandleType player)
		- int mm_player_deactivate_section_repeat(MMHandleType player, int start, int end)
		- int mm_player_set_message_callback(MMHandleType player, MMMessageCallback callback, void *user_param)
		- int mm_player_set_subtitle_silent(MMHandleType player, int slient)
		- int mm_player_get_subtitle_silent(MMHandleType player, int *slient)
		- int mm_player_set_attribute(MMHandleType player, char **err_attr_name, const char *first_attribute_name, ...)
		- int mm_player_get_attribute(MMHandleType player, char **err_attr_name, const char *first_attribute_name, ...)
		- int mm_player_get_attribute_info(MMHandleType player, const char *attribute_name, MMPlayerAttrsInfo *info)

 

Application can set/get some values into player library for applying its properties using attributes.

 

The following are supported attributes list of player library.

			- For more detail information, please refer the doxygen document of player framework.

	<table>
    
    		<tr>
        <td><b>Attribute Name</b>
        			<td>
<b>Type</b>
        			<td>
<b>Validity Type</b>
        			<td>
<b>Default Value</b>
    		<tr>
        			<td>
"profile_uri"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"profile_user_param"         			<td>
data         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"profile_play_count"         			<td>
int         			<td>
range         			<td>
1    		<tr>
        			<td>
"streaming_type"         			<td>
int         			<td>
range         			<td>
STREAMING_SERVICE_NONE    		<tr>
        			<td>
"streaming_udp_timeout"         			<td>
int         			<td>
range         			<td>
1000msec    		<tr>
        			<td>
"streaming_user_agent"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"streaming_wap_profile"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"streaming_network_bandwidth"         			<td>
int         			<td>
range         			<td>
128000Hz    		<tr>
        			<td>
"streaming_cookie"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"streaming_proxy_ip"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"streaming_proxy_port"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"display_overlay"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"display_rotation"         			<td>
int         			<td>
range         			<td>
MM_DISPLAY_ROTATION_270    		<tr>
        			<td>
"subtitle_uri"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"content_duration"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_video_codec"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"content_video_bitrate"         			<td>
int         			<td>
array         			<td>
0    		<tr>
        			<td>
"content_video_fps"         			<td>
int         			<td>
array         			<td>
0    		<tr>
        			<td>
"content_video_width"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_video_height"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_video_track_id"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_video_track_num"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_audio_codec"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"content_audio_bitrate"         			<td>
int         			<td>
array         			<td>
0    		<tr>
        			<td>
"content_audio_channels"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_audio_samplerate"         			<td>
int         			<td>
array         			<td>
0    		<tr>
        			<td>
"content_audio_track_id"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"content_audio_track_num"         			<td>
int         			<td>
range         			<td>
0    		<tr>
        			<td>
"tag_artist"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_title"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_album"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_genre"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_author"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_copyright"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_date"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_description"         			<td>
string         			<td>
N/A         			<td>
NULL    		<tr>
        			<td>
"tag_track_num"         			<td>
int         			<td>
range         			<td>
0    
	</table>


@}
@defgroup Player_uc1 Create and initialize Player
@ingroup Player_UC
@{
<h2 class="pg">Create and initialize Player</h2>
		- Applications can create the player handle using mm_player_create().
		- And then, attributes for the player such as the url can be set through mm_player_set_attribute() .
		- Fundamentally, one url should be set to play both audio and video contents.
		- The created window id should be set to display video using the "display_overlay" attribute.
		- All messages are sent through message callback functions to the application from the player.
		- So, callback functions should be set to receive messages like error, BOS(Begin Of Stream) and EOS(End Of Stream)
		- Player is a pipelined architecture and basic pipeline is made when mm_player_realize() is called.
		- The following is a sample code to create, realize player and set the url and display id. 

@code
MMHandleType g_player = 0;
char **g_err_attr_name;
struct appdata ad;

int ret = MM_ERROR_NONE;

int initialize_video_player(char *filename)
{
	if (mm_player_create(&g_player) != MM_ERROR_NONE)
	{
		printf("failed to create player\n");
	}

	if (mm_player_set_attribute(g_player,
							g_err_attr_name,
							"profile_uri", filename, strlen(filename),
							"display_overlay", (void*)&ad.xid, sizeof(ad.xid),
							NULL) != MM_ERROR_NONE)
	{
		printf("failed to set %s attribute\n", *g_err_attr_name);
		free(g_err_attr_name);
	}

	mm_player_set_message_callback(g_player, msg_callback, (void*)g_player);

	if (mm_player_realize(g_player) != MM_ERROR_NONE)
	{
		printf("failed to realize player\n");
	}
}

int msg_callback(int message, MMMessageParamType *param, void *user_param)
{
	switch (message)
	{
		case MM_MESSAGE_ERROR:
         // Do something 
         break;

     case MM_MESSAGE_END_OF_STREAM:
         // Do something 
         break;

	case MM_MESSAGE_STATE_CHANGED:
		// Do something 
		break;

	case MM_MESSAGE_BEGIN_OF_STREAM:
		// Do something 
	    break;

	default:
        return FALSE;
	}
	return TRUE;
}
@endcode


Set message callback

		- The application must confirm some information or player status from messages of callback. It must be registered before beginning playback.

		- The Followings messages are typically used

	<table>

		<tr>			<td> MM_MESSAGE_ERROR 			</td>		</tr>
		<tr>			<td> MM_MESSAGE_STATE_CHANGED			</td>		</tr>
		<tr>			<td>MM_MESSAGE_BEGIN_OF_STREAM			</td>		</tr>
		<tr>			<td>MM_MESSAGE_END_OF_STREAM			</td>		</tr>
		<tr>			<td>MM_MESSAGE_UPDATE_SUBTITLE			</td>		</tr>
		<tr>			<td>MM_MESSAGE_BUFFERING			</td>		</tr>

	</table>



		- In the case of MM_MESSAGE_ERROR,  application can determine the specific error case from the code value of message parameter.

			- The Followings error codes are typically used. 


	<table>

		<tr>			<td>MM_ERROR_PLAYER_INTERNAL 			</td>		</tr>
		<tr>			<td>MM_ERROR_PLAYER_CODEC_NOT_FOUND 			</td>		</tr>
		<tr>			<td>MM_ERROR_PLAYER_NOT_SUPPORTED_FORMAT 			</td>		</tr>
		<tr>			<td>MM_ERROR_PLAYER_NOT_INITIALIZED 			</td>		</tr>
		<tr>			<td>MM_ERROR_PLAYER_FILE_NOT_FOUND 			</td>		</tr>

	</table>

		- Refer to the appendix for more message and error details

		- The following is a sample code of message callback implementation.

@code
void video_player_message_callback(int message, void *param, void *user_param)
{
     struct appdata *ad = (struct appdata *)user_param;
     MMMessageParamType* msg_param = (MMMessageParamType*)param;

     switch(message)
	{
		case MM_MESSAGE_ERROR:
			parse_video_player_error_code(msg_param->code, ad);
			break;

		case MM_MESSAGE_BEGIN_OF_STREAM:
			// can update video player UI 
			break;

		case MM_MESSAGE_END_OF_STREAM:
			// can close and destroy the player 	
			ecore_idler_add(video_player_close_handler, ad);
			break;

			//...
		default:
			break;

	}
}

void parse_video_player_error_code(int error_code, struct appdata *app_data)
{
     switch(error_code)
	{
		case MM_ERROR_PLAYER_CODEC_NOT_FOUND:
			// can show up error popup 
			break;

		case MM_ERROR_PLAYER_INTERNAL:
			// can show up error popup and close player 
			ecore_idler_add(video_player_close_handler, app_data);
			break;
			
			//...

		default:
			break;
	}
}

int video_player_close_handler (void *data)
{
     struct appdata *ad = (struct appdata *)data;

     close_video_player (ad);
     return 0;
}

bool close_video_player (void *data)
{
     struct appdata *ad = (struct appdata *)data;

     video_player_mgr_unrealize(ad);
	video_player_mgr_destroy(ad);
}

bool video_player_mgr_unrealize (void *data)
{
     struct appdata *ad = (struct appdata *)data;
     
     if (mm_player_unrealize(ad->player_handle) != MM_ERROR_NONE)
         return FALSE;
         
     return TRUE;
}

bool video_player_mgr_destroy (void *data)
{
     struct appdata *ad = (struct appdata *)data;   

     if (mm_player_destroy(ad-> player_handle) != MM_ERROR_NONE)
         return FALSE;
         
     return TRUE;
}
@endcode 
@}
@defgroup Player_uc2 Get and set attributes
@ingroup Player_UC
@{

<h2 class="pg">Get and set attributes</h2>

		- There are many useful attributes in the player which the Application can set or get to control the player.
		- Those are constructed when the player is created and handled by string id.
		- Supported types are int, double, string and data. And, there is variable parameter in related APIs.
		- In the case of the int and double types, a name/value pair should be set. For the string and data types, the name/value pair should be followed by the size.
		- Finally, application can get the information of each attribute using mm_player_get_attribute_info().
		- The following is a sample code.

@code
/***********************
// get content duration 
/***********************

 

int duration = 0;
char **g_err_attr_name;

if (mm_player_get_attribute(g_player, &g_err_attr_name, "content_duration", &duration, NULL) != MM_ERROR_NONE)
{
	printf("failed to set %s attribute\n", *g_err_attr_name);
	free(g_err_attr_name);

}

pirntf("file duration is = %d\n", duration);

 

/***********************
// set content duration 
/***********************

int duration = 0;
char **g_err_attr_name;

if (mm_player_get_attribute(g_player, &g_err_attr_name, "content_duration", &duration, NULL) != MM_ERROR_NONE)
{
	printf("failed to set %s attribute\n", g_err_attr_name);
	free(g_err_attr_name);
}

pirntf("duration is = %d\n", duration);

/***********************
// get attribute info    
/***********************

int method = 0;

MMPlayerAttrsInfo method_info = { 0, };

if (mm_player_get_attribute_info (g_player, "display_method", &method_info, NULL) != MM_ERROR_NONE)
{
	printf("failed to get info \n");
}

printf("type:%d \n", method_info.type); // int, double
printf("flag:%d \n", method_info.flag); // readable, writable..
printf("validity type:%d \n", method_info.validity_type);//range, array..

if (method_info. validity_type == MM_PLAYER_ATTRS_VALID_TYPE_INT_RANGE)
{
	printf("range min=%d\n", method_info.int_range.min );
	printf("range max=%\n", method_info.int_range.max );
}
@endcode

@}
@defgroup Player_uc3 Unrealize and play next file
@ingroup Player_UC
@{

<h2 class="pg">Unrealize and play next file</h2>
		- Player should be unrealized first in order to play another file.
		- If player is unrealized, all the related variables and codecs are removed.
		- So, it is necessary to set new attributes and reconstruct the player.
		- The following is a sample code to play another mp3 file. 
@code
void play_next_audio_file(char *next_filename)
{
    if (mm_player_unrealize(g_player) != MM_ERROR_NONE)
    {
         printf("failed to unrealize\n");
         exit(1); 
	}

	if (mm_player_set_attribute(g_player,
					&g_err_attr_name,
	                   "profile_uri", next_filename, strlen(filename),
	                  NULL) != MM_ERROR_NONE)
	{
		printf("failed to set %s attribute\n", g_err_attr_name);
		free(g_err_attr_name);
	}

	if (mm_player_realize(g_player) != MM_ERROR_NONE)
	{
	         printf("failed to destroy\n");
	         exit(1); 
	}

	if (mm_player_start(g_player) != MM_ERROR_NONE)
	{
	         printf("failed to destroy\n");
	         exit(1); 
	}
}
@endcode


@}
@defgroup Player_uc4 Destroy player
@ingroup Player_UC
@{

<h2 class="pg">Destroy player</h2>

		- The created player should be destroyed when application is closed.
		- So, if mm_player_destroy() is called, all allocated resources and the player handle are released.
@}
@defgroup Player_uc5 Play and end of playback
@ingroup Player_UC
@{

<h2 class="pg">Play and end of playback</h2>

		- Applications can play music or video using the mm_player_start() function when player is in the ready state. After starting, the appropriate codecs will be generated internally to play it.
		- The result of the start function is returned asynchronously through the message callback which was previously registered.
		- Playback is confirmed to the application with the MM_BEGIN_OF_STREAM(BOS) message. 
		- The MM_MESSAGE_END_OF_STREAM(EOS) is sent at the end of contents playback. 
@}
@defgroup Player_uc6 Pause and resume
@ingroup Player_UC
@{
 
<h2 class="pg">Pause and resume</h2>

		- Player can be paused during playing video or audio contents. It can also be resumed again.
		- The result of the pause or resume functions are returned asynchronously. So the result is confirmed to the application by the MM_MESSAGE_STATE_CHANGED message in the message callback.
		- Both apis may be used synchronously in the case of local playback.
		- The following is a sample code for when the player is paused and the result is checked for streaming data.

@code
void pause_video_player()
{
	if (mm_player_pause(g_player) != MM_ERROR_NONE)
	{
	        printf("failed to pause\n"); 
	}
}

int msg_callback(int message, MMMessageParamType *param, void *user_param)
{
	switch (message)
	{
	     case MM_MESSAGE_ERROR:
	         // Do something 
	         break;
	         
		case MM_MESSAGE_STATE_CHANGED:
			if (param->state.current == MM_PLAYER_STATE_PAUSED)
	                 printf("player is paused. So, application can resume it again.\n");
			break;
			
		default:
			return FALSE;
	}
	return TRUE;
}
@endcode 
@}
@defgroup Player_uc7 Change the volume during playback
@ingroup Player_UC
@{

<h3 class="pg">Change the volume during playback</h3>

		- The range of volume level is from 0 to 9. Each macro is MM_VOLUME_LEVEL_MIN and MM_VOLUME_LEVEL_MAX. The default volume level is 7.
		- Volume can be controlled during playback but, if volume is set before playing, it can be saved and applied at running time.
		- The following is a sample code to set MM_VOLUME_LEVEL_MAX volume and get it.

@code
int change_video_player_volume()
{
	MMPlayerVolumeType volume;
	int i = 0;

	for (i = 0; i < MM_VOLUME_CHANNEL_NUM; i++)
		volume.level[i] = MM_VOLUME_LEVEL_MAX;

    if (mm_player_set_volume(g_player, &volume) != MM_ERROR_NONE)
    {
        printf("failed to set volume\n");
        return FALSE;
	}

	if (mm_player_get_volume(g_player, format, &pos) != MM_ERROR_NONE)
	{
		printf("failed to get volume\n");
		return FALSE;
	}

	for (i = 0; i < MM_VOLUME_CHANNEL_NUM; i++)
		printf("channel[%d] = %d \n", i, volume.level[i]);
}
@endcode 
@}
@defgroup Player_uc8  Seeking position
@ingroup Player_UC
@{

<h3 class="pg">Seeking position</h3>

		- Player supports time and percent format to get or set position of stream.
		- The position unit is in milliseconds.
		- The following is a sample code to get and set the player position. 

@code
gboolean change_video_player_position()
{
	int format = MM_PLAYER_POS_FORMAT_TIME;
	int pos = 15000; // 15sec
	
	if (mm_player_set_position(g_player, format, pos) != MM_ERROR_NONE)
	{
	    return FALSE;
	}

	if (mm_player_get_position(g_player, format, &pos) != MM_ERROR_NONE)
	{
		return FALSE;
	}
	printf("current pos = %d (msec)\n", pos);

	return TRUE;
}
@endcode

@}
@defgroup Player_uc9 Show subtitle
@ingroup Player_UC
@{

<h3 class="pg">Show subtitle</h3>

		- Player framework can support a separate subtitle file. The filepath of subtitle should be sent through mm_player_set_attribute() before realizing the player. 

@code

if (mm_player_set_attribute(g_player,
							&g_err_name,
							"subtitle_uri",subtitle_path,strlen(subtitle_path),
							NULL) != MM_ERROR_NONE)
{
         printf("failed to set %s\n", *g_err_name);
         free(g_err_name);
}
@endcode

		- Application shall select the option of whether to show the subtitle or not.

@code
if (mm_player_set_subtitle_silent(g_player, TRUE) != MM_ERROR_NONE)
     printf("failed to set subtitle silent\n");
@endcode
 

		- Finally, application should get the parsed text data from message of callback function.

 
@code
void video_player_message_callback(int message, void *param, void *user_param)
{
     struct appdata *ad = (struct appdata *)user_param;
     MMMessageParamType* msg_param = (MMMessageParamType*)param;

     switch(message)
	{
		case MM_MESSAGE_SUBTITLE:
			if (msg_param->data != NULL)
			{
				ad->subtitle_duration = msg_param->subtitle.duration/1000;
				strcpy(ad->subtitle, msg_param->data);
				show_video_player_subtitle(ad);
			}
			break;

	
	default:
		break;

	}
}
@endcode
 
@}
@defgroup MMsession Multimedia session
@ingroup MultiMediaPG
@{
	@brief <sub class="ref">Also see</sub> Use Cases of @ref MMsession_UC

<h2 class="pg">Multimedia session</h2>

Role of Multimedia Session is to manage "operation policy" between multimedia applications in multi-tasking scenario

Multimedia Session provides functions to determine type of application's policy.

Application developer can define applications' session type as "shared", "exclusive" or "replace".

"Shared" type means the audio session is shared with other applications, if possible. The audio resources can be used by other applications.

"Exclusive" type means using the audio session exclusively. Other applications are not allowed to use multimedia resources during this time.

"Replace" type means this will make stop previous session but allows sharing session with following application.


The following are supported functions :

		- int mm_session_init(int sessiontype)

		- int mm_session_finish(void)

@}
@defgroup MMsession_uc1 Initializing Session
@ingroup MMsession_UC
@{


Initializing Session

		- To define current application's multimedia session policy.

		- Policy can be one of SHARE, EXCLUSIVE or REPLACE.

		- The following is a sample code


@code
int err;



// Init session policy to SHARE 

err = mm_session_init (MM_SESSION_TYPE_SHARE);



if (err != MM_ERROR_NONE)

    return;

 

// Multimedia API manipulation (player, camcorder, etc.) 
@endcode

@}
@defgroup MMsession_uc2 Finisihing Session
@ingroup MMsession_UC
@{

Finisihing Session

		- To finish current application's multimedia session policy

		- This API is not mandatory except internal call application.

		- This API can be also useful when application's multimedia session should be changed at runtime.

		- The following is a sample code

@code
int err;



// Init session policy to SHARE

err = mm_session_init (MM_SESSION_TYPE_SHARE);

 

if (err != MM_ERROR_NONE)

    return;



// Do something 



// Change policy to EXCLUSIVE 

err = mm_session_finish();



// Init session policy to EXCLUSIVE 

err = mm_session_init (MM_SESSION_TYPE_EXCLUSIVE);



// Do something else 
@endcode

@}
@defgroup MM_Fileinfo Fileinfo
@ingroup MultiMediaPG
@{
<h2 class="pg">Fileinfo</h2>
	@brief <sub class="ref">Also see</sub> Use Cases of @ref Fileinfo_UC

Fileinfo module provides APIs to extract media property information and meta data from media content. These values can be used to display detailed information of the media content without playing it.



For convenience, the file module provides an additional two APIs (mm_file_get_content_attr_from_memory, mm_file_get_tag_attr_from_memory) which manipulate the source data from memory instead of the file. They act the same as normal APIs (mm_file_get_content_attr, mm_file_get_tag_attr).



For performance, the file module provides an additional two APIs (mm_file_get_stream_info, mm_file_get_content_attr_simple) which extract the audio/video track count without time consuming operations.



The following are supported functions
		- int mm_file_get_content_attr (MMHandleType *attrs, const char *filename)

		- int mm_file_get_content_attr_from_memory (MMHandleType *attrs, const void *data, unsigned int size, int format)

		- int mm_file_get_content_attr_simple (MMHandleType *attrs, const char *filename)

		- int mm_file_free_content_attr (MMHandleType attrs)

		- int mm_file_get_tag_attr ((MMHandleType *attrs, const char *filename)

		- int mm_file_get_tag_attr_from_memory ((MMHandleType *attrs, const void *data, unsigned int size, int format)

		- int mm_file_free_tag_attr ((MMHandleType attrs)

		- int mm_file_get_stream_info (const char *filename, int *audio_stream_num, int *video_stream_num)



@}
@defgroup Fileinfo_uc1 Extracting Media Property Information 
@ingroup Fileinfo_UC
@{

<h3 class="pg">Extracting Media Property Information </h3>

Media property information can be extracted using the following steps:

		- Get attributes handle containing media information using mm_file_get_content_attr API

		- Use attributes functions with handle to get value

		- Free allocated media information using mm_file_free_content_attr API



The following is a sample code

@code
MMHandleType attrs;

int err;



err = mm_file_get_content_attr(&attrs, filename);

if (err != MM_ERROR_NONE)

{

      printf("error occurred to extract media information\n");

      exit(1);

}



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_DURATION, &val);

if (err == MM_ERROR_NONE)

      printf("duration: %d\n", val);

     

err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_CODEC, &val);

if (err == MM_ERROR_NONE)

      printf("video codec id: %d\n", val);

     

err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_BITRATE, &val);

if (err == MM_ERROR_NONE)

      printf("video bitrate: %d\n", val);

     

err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_FPS, &val);

if (err == MM_ERROR_NONE)

      printf("fps: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_WIDTH, &val);

if (err == MM_ERROR_NONE)

      printf("width: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_HEIGHT, &val);

if (err == MM_ERROR_NONE)

      printf("height: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_THUMBNAIL, &data, &size);

if (err == MM_ERROR_NONE)

      printf("thumbnail: %p, %d bytes\n", data, size);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_TRACK_ID, &val);

if (err == MM_ERROR_NONE)

      printf("video track id: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_VIDEO_TRACK_NUM, &val);

if (err == MM_ERROR_NONE)

      printf("video tracks: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_AUDIO_CODEC, &val);

if (err == MM_ERROR_NONE)

      printf("audio codec id: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_AUDIO_BITRATE, &val);

if (err == MM_ERROR_NONE)

      printf("audio bitrate: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_AUDIO_CHANNELS, &val);

if (err == MM_ERROR_NONE)

      printf("channels: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_AUDIO_SAMPLERATE, &val);

if (err == MM_ERROR_NONE)

      printf("sampling rate: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_AUDIO_TRACK_ID, &val);

if (err == MM_ERROR_NONE)

      printf("audio track id: %d\n", val);



err = mm_attrs_get_int(attrs, MM_FILE_CONTENT_AUDIO_TRACK_NUM,   &val);

if (err == MM_ERROR_NONE)

      printf("audio tracks: %d\n", val);

 

err = mm_file_free_content_attr (attr);
@endcode
@}
@defgroup Fileinfo_uc2 Extracting Media Meta(Tag) data
@ingroup Fileinfo_UC
@{

<h3 class="pg">Extracting Media Meta(Tag) data</h3>

Media meta data can be extracted using the following steps:

		- Get attributes handle containing meta data using mm_file_get_tag_attr API

		- Use attributes functions with handle to get value

		- Free allocated meta data using mm_file_free_tag_attr API



The following is a sample code
@code
MMHandleType attrs;

int err, val, size;

char *str;

void *data;

double fval;

 

err = mm_file_get_tag_attr (&attrs, filename);

if (err != MM_ERROR_NONE)

{

      printf("error occurred to extract meta data\n");

      exit(1);

}

 

err = mm_attrs_get_string(attrs, MM_FILE_TAG_ARTIST, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("artist: %s\n", str);

 

err = mm_attrs_get_string(attrs, MM_FILE_TAG_TITLE, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("title: %s\n", str);

 

err = mm_attrs_get_string(attrs, MM_FILE_TAG_ALBUM, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("album: %s\n", str);



err = mm_attrs_get_string(attrs, MM_FILE_TAG_COPYRIGHT, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("copyright: %s\n", str);

 

err = mm_attrs_get_string(attrs, MM_FILE_TAG_DATE, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("date: %s\n", str);



err = mm_attrs_get_string(attrs, MM_FILE_TAG_DESCRIPTION, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("description: %s\n", str);



err = mm_attrs_get_data(attrs, MM_FILE_TAG_ARTWORK, &data, &size);

err |= mm_attrs_get_int(attrs, MM_FILE_TAG_ARTWORK_SIZE, &size);

if (err == MM_ERROR_NONE && data && size > 0)

      printf("artwork: %p, %d\n", data, size);

 

err = mm_attrs_get_string(attrs, MM_FILE_TAG_TRACK_NUM, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("track: %s\n", str);



err = mm_attrs_get_string(attrs, MM_FILE_TAG_CLASSIFICATION, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("classification: %s\n", str);



err = mm_attrs_get_string(attrs, MM_FILE_TAG_RATING, &str, &size);

if (err == MM_ERROR_NONE && str)

      printf("rating: %s\n", str);



err = mm_attrs_get_double(attrs, MM_FILE_TAG_LONGITUDE, &fval);

if (err == MM_ERROR_NONE)

      printf("longitude: %4.4f\n", fval);



err = mm_attrs_get_double(attrs, MM_FILE_TAG_LATIDUE, &fval);

if (err == MM_ERROR_NONE)

      printf("latidue: %4.4f\n", fval);



err = mm_attrs_get_double(attrs, MM_FILE_TAG_ALTIDUE, &fval);

if (err == MM_ERROR_NONE)

      printf("altidue: %4.4f\n", fval);



err = mm_file_free_tag_attr (attr);
@endcode

@}
@defgroup Fileinfo_uc3 Extracting Stream information
@ingroup Fileinfo_UC
@{

<h3 class="pg">Extracting Stream information</h3>

Number of streams can be extracted using the following steps:

		- Get the number of streams using mm_file_get_stream_info API

		- Detect as video file if number of video streams is more than one.



The following is a sample code

@code
int err;

int audio_num;

int video_num;



err = mm_file_get_stream_info (filename, &audio_num, &video_num);

if (err != MM_ERROR_NONE)

{

      printf("error occurred to extract stream information\n");

      exit(1);

}



printf("content has %d audio streams\n", audio_num);

printf("content has %d video streams\n", video_num);
@endcode
@}
@defgroup MM_Sound Sound
@ingroup MultiMediaPG
@{

<h2 class="pg">Sound</h2>
	@brief <sub class="ref">Also see</sub> Use Cases of @ref Sound_UC

The Sound module has the following features:

Play or capture PCM data with given memory buffer

Play audio  file with simple API ( uncompressed WAV file only)

Control volume and audio routing information

The following are supported functions :

	- int	mm_sound_pcm_capture_close (MMSoundPcmHandle_t handle)

	- int	mm_sound_pcm_capture_open (MMSoundPcmHandle_t *handle, const unsigned int rate, MMSoundPcmChannel_t channel, MMSoundPcmFormat_t format)

	- int	mm_sound_pcm_capture_read (MMSoundPcmHandle_t handle, void *buffer, const unsigned int length)

	- int	mm_sound_pcm_play_close (MMSoundPcmHandle_t handle)

	- int	mm_sound_pcm_play_open (MMSoundPcmHandle_t *handle, const unsigned int rate, MMSoundPcmChannel_t channel, MMSoundPcmFormat_t format, const volume_type_t volume)

	- int	mm_sound_pcm_play_write (MMSoundPcmHandle_t handle, void *ptr, unsigned int length_byte)

	- int	mm_sound_play_dtmf (MMSoundDtmf_t num, const volume_type_t vol_type, const sound_time_msec_t time)

	- int	mm_sound_play_sound (const char *filename, const volume_type_t volume, mm_sound_stop_callback_func callback, void *data, int *handle)

	- int	mm_sound_stop_sound (int handle)

	- int	mm_sound_volume_add_callback (volume_type_t type, volume_callback_fn func, void *user_data)

	- int	mm_sound_volume_get_current_playing_type (volume_type_t *type)

	- int	mm_sound_volume_get_step (volume_type_t type, int *step)

	- int	mm_sound_volume_get_value (volume_type_t type, unsigned int *value)

	- int	mm_sound_volume_primary_type_clear ()

	- int	mm_sound_volume_primary_type_set (volume_type_t type)

	- int	mm_sound_volume_remove_callback (volume_type_t type)

	- int	mm_sound_volume_set_value (volume_type_t type, const unsigned int value)

	- int	mm_sound_route_add_change_callback (audio_route_policy_changed_callback_fn func, void *user_data)

	- int	mm_sound_route_get_system_policy (system_audio_route_t *route)

	- int	mm_sound_route_is_a2dp_on (char **bt_name)

	- int	mm_sound_route_remove_change_callback (void)

	- int	mm_sound_route_set_system_policy (system_audio_route_t route)

@}
@defgroup Sound_uc1 Capture PCM data
@ingroup Sound_UC
@{

<h3 class="pg">Capture PCM data</h3>

	- Application can capture PCM data

	- The following is a sample code


@code

bool g_stop_pcm_capturing = FALSE;
int capture_pcm_data()
{
	char *buffer = NULL;
	int ret = 0;
	int size = 0;
	int count = 0;
	MMSoundPcmHandle_t handle;

	size = mm_sound_pcm_capture_open(&handle, 44100, MMSOUND_PCM_MONO, MMSOUND_PCM_S16_LE);
	if(size < 0)
	{
		printf("Can not open capture handle\n");
		return -2;
	}

	buffer = alloca(size);
	while(1)
	{
		ret = mm_sound_pcm_capture_read(handle, (void*)buffer, size);
		if(ret < 0)
		{
			printf("read fail\n");
			break;
		}
		if( g_stop_pcm_capturing ) {
			break;
		}
	}
	mm_sound_pcm_capture_close(handle);

	return TRUE;
}

@endcode


@}
@defgroup Sound_uc2 Play sound file
@ingroup Sound_UC
@{

<h3 class="pg">Play sound file</h3>

	- Start playing sound file
	- Stop playing sound file
	- Uncompressed WAV file only

@code


void sound_stop_cb(void* data)
{
	struct appdata* ad = (appdata*) data;
	printf("Stop callback\n");
	ad->snd_handle = -1;
}

int play_file(void* data)
{
	struct appdata* ad = (struct appdata*) data;
	char filename[] ="/opt/media/Sound/testfile.wav";
	volume_type_t volume = VOLUME_TYPE_SYSTEM;
	int ret = 0;
	int *snd_handle = NULL;

	snd_handle = &ad->snd_handle;

	ret = mm_sound_play_sound(filename, volume, sound_stop_cb, (void*)ad, snd_handle);
	if(ret < 0)
	{
		printf("play file failed\n");
		return -1;
	}
	else
	{
		printf("play file success\n");
		return 0;
	}
}


int stop_file(void* data)
{
	int ret = 0;
	struct appdata* ad = (struct appdata*) data;

	if(ad->snd_handle != -1)
	{
		ret = mm_sound_stop_sound(ad->snd_handle);
		if(ret < 0)
		{
			printf("Stop sound failed\n");
			return -1;
		}
		else
		{
			printf("Stop sound success\n");
			return -1;
		}
	}
}
@endcode
@}
@defgroup Sound_uc3 Control Volume
@ingroup Sound_UC
@{


<h3 class="pg">Control Volume</h3>

Basically volume of SLP system is controlled by System process.
But in some case, application should control volume by itself.
	- If application does not want to be hidden by System Volume UI.
	- If application want to use Volume H/W key for special purpose.

Sample code to control Media type volume


@code

Eina_Bool volume_key_cb(void *data, int type, void *event_info)
{
		struct appdata* ad = (struct appdata*)data;
		Ecore_Event_Key *kd = (Ecore_Event_Key*) event_info;
		int cur_vol = 0;
		int ret = 0;

		if(0 == strcmp(kd->keyname, KEY_VOLUMEUP))
		{
			ret = mm_sound_volume_get_value(ad->vol_type, &cur_vol);
			if(ret < 0)
			{
				printf("Can not get volume value\n");
			}
			else
			{
				if(cur_vol == ad->max_vol)
				{
					printf("Skip\n");
				}
				else
				{
					ret = mm_sound_volume_set_value(ad->vol_type, ++cur_vol);
					if(ret < 0)
					{
						printf("Can not set volume value\n");
					}
				}
			}
		}
		else if(0 == strcmp(kd->keyname, KEY_VOLUMEDOWN))
		{
			ret = mm_sound_volume_get_value(ad->vol_type, &cur_vol);
			if(ret < 0)
			{
				printf("Can not get volume value\n");
			}
			else
			{
				if(0 == ad->max_vol)
				{
					printf("Skip\n");
				}
				else
				{
					ret = mm_sound_volume_set_value(ad->vol_type, --cur_vol);
					if(ret < 0)
					{
						printf("Can not set volume value\n");
					}
				}
			}
		}
		else
		{
			printf("Skip\n");
		}
		return EINA_FALSE;
}

int do_key_grab(void* data)
{
		struct appdata* ad = (struct appdata*)data;
		int ret = 0;
		int vol_max = 0;

		// grab key and add event handler
		if( utilx_grab_key(ad->disp, ad->win, KEY_VOLUMEUP, TOP_POSITION_GRAB) < 0)
		{
			printf("grab Volume up key fail\n");
			return -1;
		}
		if( utilx_grab_key(ad->disp, ad->win, KEY_VOLUMEDOWN, TOP_POSITION_GRAB) < 0)
		{
			printf("grab Volume down key fail\n");
			return -1;
		}

		ad->key_down = ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, volume_key_cb, ad);

		//get max volume of type
		ad->vol_type = VOLUME_TYPE_MEDIA;
		ret = mm_sound_volume_get_step(ad->vol_type, &vol_max);
		if(ret < 0)
		{
			printf("Volume get step fail\n");
			return -1;
		}

		ad->vol_max = vol_max;

		return 0;
}

@endcode

@}
@defgroup MM_OpenAL OpenAL
@ingroup MultiMediaPG
@{


<h2 class="pg">OpenAL</h2>

OpenAL is a cross-platform 3D audio API appropriate for use with gaming applications and many other types of audio applications. OpenAL in SLP only supports playback fucntion.

 

OpenAL is opensource and if you need further information, see official website : http://connect.creativelabs.com/openal/default.aspx

 
Specification and Reference

		- http://connect.creativelabs.com/openal/Documentation/Forms/AllItems.aspx

@}
@defgroup MM_Radio Radio
@ingroup MultiMediaPG
@{
 
<h2 class="pg">Radio</h2>
	@brief <sub class="ref">Also see</sub> Use Cases of @ref Radio_UC

This section describes APIs of the Multimedia FM radio library. Radio library is used for listening to FM radio, scanning all possible frequencies and seeking one frequency from current state, controling relative volume and frequency.

 

Radio can have 5 states, and each state can be changed by calling the following functions as described.

	<table>
    
    		<tr>
        			<td>
<b>FUNCTION</b>
        			<td>
<b>PRE-STATE</b>
        			<td>
<b>POST-STATE</b>
        			<td>
<b>SYNC TYPE</b>
    		<tr>
        			<td>
mm_radio_create()        			<td>
NONE        			<td>
NULL        			<td>
SYNC    		<tr>
        			<td>
mm_radio _destroy()        			<td>
NULL        			<td>
NONE        			<td>
SYNC    		<tr>
        			<td>
mm_radio_realize()        			<td>
NULL        			<td>
READY        			<td>
SYNC    		<tr>
        			<td>
mm_radio_unrealize()        			<td>
READY        			<td>
NULL        			<td>
SYNC    		<tr>
        			<td>
mm_radio_start()        			<td>
READY        			<td>
PLAYING        			<td>
SYNC    		<tr>
        			<td>
mm_radio_stop()        			<td>
PLAYING        			<td>
READY        			<td>
SYNC    		<tr>
        			<td>
mm_radio_scan_start()        			<td>
READY        			<td>
SCANNING        			<td>
ASYNC    		<tr>
        			<td>
mm_radio_scan_stop()        			<td>
SCANNING        			<td>
READY        			<td>
ASYNC    		<tr>
        			<td>
Mm_radio_seek()        			<td>
PLAYING        			<td>
PLAYING        			<td>
ASYNC    
	</table>

@image html SLP_MultimediaFW_PG_image004.png

The following are supported functions in the radio module.

		- int mm_radio_get_state(MMHandleType hradio, MMRadioStateType *state)

		- int mm_radio_set_frequency(MMHandleType hradio, int freq)

		- int mm_radio_get_frequency(MMHandleType hradio, int *pFreq)

		- int mm_radio_set_sound_path(MMHandleType hradio, MMRadioOuputType path)

		- int mm_radio_get_sound_path (MMHandleType hrado, MMRadioOuputType *pPath)

		- int mm_radio_set_message_callback(MMHandleType radio, MMMessageCallback callback, void *user_param)

@}
@defgroup Radio_uc1 Create and initialize radio
@ingroup Radio_UC
@{
 
<h3 class="pg">Create and initialize radio</h3>

		- Application can create the radio handle using mm_radio_create().

		- And, callback function must be set to get messages from radio engine using mm_radio_set_message_callback().

		- The followings messages are used. 
	<table>
    
    		<tr> 
				<td> <b>MESSAGE TYPE</b>  			</td>
				<td> <b>DESCRIPTION</b> 			</td>
    		<tr>
        			<td> MM_MESSAGE_RADIO_SCAN_START        
				<td> Radio frequency scanning initiated    
    		<tr>
        			<td> MM_MESSAGE_RADIO_SCAN_INFO        
				<td> Founded radio frequency report. check message parameters    
    		<tr>
        			<td> MM_MESSAGE_RADIO_SCAN_FINISH        
				<td> Radio frequency scanning has finished    
    		<tr>
        			<td> MM_MESSAGE_RADIO_SCAN_STOP        
				<td> Radio frequency scanning has stopped    
		<tr>
        			<td> MM_MESSAGE_RADIO_SEEK_START        
				<td> Radio seeking has established    
		<tr>
        			<td> MM_MESSAGE_RADIO_SEEK_FINISH        
				<td> Radio seeking has finished    
    
	</table>


		- The resources can be allocated by mm_radio_realize(). And, radio device is opened.

@code
MMHandleType g_radio = 0;

static int __msg_callback(int message, void *pParam, void *user_param)
{
      MMMessageParamType* param = (MMMessageParamType*)pParam;
      MMHandleType radio = (MMHandleType *) user_param;

      int ret = 0;

      printf("incomming message : %d\n", message);

      switch(message)
      {
	      case MM_MESSAGE_STATE_CHANGED:
	            printf("MM_MESSAGE_STATE_CHANGED: current : %d    old : %d\n"
	                        , param->state.current, param->state.previous);
	            break;

	      case MM_MESSAGE_RADIO_SCAN_START:
	            printf("MM_MESSAGE_RADIO_SCAN_START\n");
	            break;

	      case MM_MESSAGE_RADIO_SCAN_INFO:
			printf("MM_MESSAGE_RADIO_SCAN_INFO : freq : %d\n", param->radio_scan.frequency);
	            break;

	      case MM_MESSAGE_RADIO_SCAN_STOP:
	            printf("MM_MESSAGE_RADIO_SCAN_STOP\n");
	            break;

	      case MM_MESSAGE_RADIO_SCAN_FINISH:
	            printf("MM_MESSAGE_RADIO_SCAN_FINISHED\n");
	            break;

	      case MM_MESSAGE_RADIO_SEEK_START:
                  printf("MM_MESSAGE_RADIO_SEEK_START\n");
                  break;

	      case MM_MESSAGE_RADIO_SEEK_FINISH:
			printf("MM_MESSAGE_RADIO_SEEK_FINISHED : freq : %d\n", param->radio_scan.frequency);
	            break;

	      default:
	            printf("ERROR : unknown message received!\n");
	            break;
      }
      return true;
}

 

int init_radio(void)
{
      int ret = MM_ERROR_NONE;

	mm_radio_create(&g_radio);
	mm_radio_set_message_callback( radio, (MMMessageCallback)__msg_callback,(void*) g_radio);
	mm_radio_realize(g_radio);
	mm_radio_unrealize(g_radio);
	mm_radio_destroy(g_radio);

      return ret;
}
@endcode
@}
@defgroup Radio_uc2 Destroy and close
@ingroup Radio_UC
@{

<h3 class="pg">Destroy and close</h3>

		- The created radio should be destroyed when application is closed.

		- So, if mm_radio_unrealize() is called, radio device would be closed.

		- And, all allocated resources and the player handle are released by mm_radio_destroy().

@code
gboolean release_radio(void)
{
      if (mm_radio_unrealize(g_radio) != MM_ERROR_NONE)
	{
      		printf("failed to unrealize\n");
		return FALSE;
	}

	if (mm_radio_ destroy (g_radio) != MM_ERROR_NONE)
	{
	      printf("failed to destroy\n");
	      return FALSE;
	}
	return TRUE;
}
@endcode 




<b>Start and stop</b>

		- Application can start radio with mm_radio_start() and stop it with mm_radio_stop().

		- And, the frequency should be set before calling start.

 
@code
gboolean start_radio(void)
{
	if (mm_radio_ set_frequency (g_radio, 1077) != MM_ERROR_NONE)
	{
		printf("failed to set freq\n");

	      return FALSE;
	}

      if (mm_radio_start(g_radio) != MM_ERROR_NONE)
	{
	      printf("failed to start\n");

	      return FALSE;
	}
	return TRUE;
}

 

gboolean stop_radio(void)
{
      if (mm_radio_stop(g_radio) != MM_ERROR_NONE)
	{
      		printf("failed to stop\n");

	      return FALSE;
	}
	return TRUE;
}
@endcode
@}
@defgroup Radio_uc3 Seek frequency
@ingroup Radio_UC
@{

<h3 class="pg">Seek frequency</h3>

		- Application can seek the effective frequency of radio in playing state by mm_radio_seek().

		- After calling it, application have to check the state with MM_MESSAGE_RADIO_SEEK_START and MM_MESSAGE_RADIO_SEEK_FINISH which are sent through message callback.

		- And, if seek is finished, the frequency is sent through message parameter of callback function when MM_MESSAGE_RADIO_SEEK_FINISH is posted.


@code
gboolean seek_radio_frequency(void)
{
      if (mm_radio_seek (g_radio) != MM_ERROR_NONE)
	{
		printf("failed to seek\n");
		  
	      return FALSE;
	}
	return TRUE;
}
@endcode
@}
@defgroup Radio_uc4 Scan frequencies
@ingroup Radio_UC
@{

<h3 class="pg">Scan frequencies</h3>

		- Application can scan the effective frequency of radio in playing state by mm_radio_scan_start().

		- After calling it, application have to check the state with MM_MESSAGE_RADIO_SCAN_START , MM_MESSAGE_RADIO_SCAN_INFO, MM_MESSAGE_RADIO_SCAN_FINISH which are sent through message callback.

		- And, if frequency is found, it's sent through message parameter of callback function when . MM_MESSAGE_RADIO_SCAN_INFO is posted.

		- Finally, scanning can be stopped by mm_radio_scan_stop().  So, MM_MESSAGE_RADIO_SCAN_STOP will be sent.

 

 

 
@}
@defgroup Radio_uc5 Set/Get sound path
@ingroup Radio_UC
@{

 
<h3 class="pg">Set/Get sound path</h3>

		- Applications can set/get sound path by mm_radio_set_sound_path() and mm_radio_get_sound_path().

		- The sound path type is followings .

 
	<table>
		<tr> 			<td>SOUND PATH TYPE 			</td> 			<td>DESCRIPTION 			</td> 		</tr>
		<tr> 			<td>MM_RADIO_OUTPUT_AUTO			</td> 			<td>Automatic output mode, but not used yet 			</td> 		</tr>
		<tr> 			<td>MM_RADIO_OUTPUT_SPEAKER			</td> 			<td> 			</td> 		</tr>
		<tr> 			<td> 			</td> 			<td> 			</td> 		</tr>
	</table>

@}
*/
/**
 * @defgroup  MultiMediaPG MultiMedia Camcorder,Player,Sound and Radio
   @{
   *   @defgroup 
   *   @defgroup MM_UC Use Cases
       @{
 *   @defgroup Camcorder_UC Camcorder
 *   @defgroup Player_UC Player
 *   @defgroup Sound_UC Sound
 *   @defgroup MMsession_UC  Multimedia session
	@brief <sub class="ref">Also see</sub> Feature description of  @ref MMsession
 *   @defgroup  Fileinfo_UC Fileinfo
	@brief <sub class="ref">Also see</sub> Feature description of  @ref Fileinfo
 *   @defgroup Radio_UC Radio
	@brief <sub class="ref">Also see</sub> Feature description of  @ref Radio
       @}
     @}
*/
