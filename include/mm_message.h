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

 
#ifndef __MM_MESSAGE_H__
#define	__MM_MESSAGE_H__

#ifdef __cplusplus
	extern "C" {
#endif


/**
 *         @addtogroup COMMON
 *         @{
		 * @file		mm_message.h
		 * @brief		This file declares the messages type of Multimedia framework.
		 * @version		1.0
		 *
		 * This file declares the messages type of Multimedia framework.
 */

/**
 * Enumerations of messages type.
*/
enum MMMessageType {
	/* COMMON */
	MM_MESSAGE_UNKNOWN = 0x00,			/**< Unknown message type */
	MM_MESSAGE_ERROR,				/**< Error message type */
	MM_MESSAGE_WARNING,				/**< Warning message type */
	MM_MESSAGE_STATE_CHANGED,			/**< State change message type */
	MM_MESSAGE_STATE_INTERRUPTED,			/**< State change by interrupt */
	MM_MESSAGE_READY_TO_RESUME, 			/**< Ready to resume message type */

	/* PLAYER */
	MM_MESSAGE_CONNECTING = 0x100,			/**< Connecting message type */
	MM_MESSAGE_CONNECTED,				/**< Rtspsrc has successed to connecting to server */
	MM_MESSAGE_CONNECTION_TIMEOUT,			/**< Connection timeout message type */
	MM_MESSAGE_BUFFERING,				/**< Buffering message type */
	MM_MESSAGE_BEGIN_OF_STREAM,			/**< Streaming begin message type */
	MM_MESSAGE_END_OF_STREAM,			/**< End of stream message type */
	MM_MESSAGE_BLUETOOTH_ON,			/**< Bluetooth A2DP Connection ON */
	MM_MESSAGE_BLUETOOTH_OFF,			/**< Bluetooth A2DP Connection OFF */
	MM_MESSAGE_RESUMED_BY_REW,			/**< Resumed by fast rewind message type */
	MM_MESSAGE_UPDATE_SUBTITLE,			/**< Update subtitle type */
	MM_MESSAGE_RTP_SENDER_REPORT,			/**< RTP sender report */
	MM_MESSAGE_RTP_RECEIVER_REPORT,			/**< RTP receiver report */
	MM_MESSAGE_RTP_SESSION_STATUS,			/**< RTP session status */
	MM_MESSAGE_SENDER_STATE,			/**< Sender state */
	MM_MESSAGE_RECEIVER_STATE,			/**< Receiver state */
	MM_MESSAGE_FILE_NOT_SUPPORTED,			/**< Not supported file */
	MM_MESSAGE_FILE_NOT_FOUND,			/**< Not founded file */
	MM_MESSAGE_DRM_NOT_AUTHORIZED,			/**< Not authorized to play the content */
	MM_MESSAGE_VIDEO_CAPTURED,			/**< Video frame has been captured */
	MM_MESSAGE_VIDEO_NOT_CAPTURED,			/**< video capture failed */
	MM_MESSAGE_SEEK_COMPLETED,			/**< Seek completed */
	MM_MESSAGE_PD_DOWNLOADER_START,	/**< PD downloader start message */
	MM_MESSAGE_PD_DOWNLOADER_END,		/**< PD downloader end message */
	MM_MESSAGE_DRM_NO_LICENSE,			/**< No license */
	MM_MESSAGE_DRM_EXPIRED,				/**< Expired license */
	MM_MESSAGE_DRM_FUTURE_USE,			/**< License for future use */

	/* CAMCORDER */
	MM_MESSAGE_CAMCORDER_STATE_CHANGED = 0x200,	/**< State changed.*/
	MM_MESSAGE_CAMCORDER_STATE_CHANGED_BY_ASM, 	/**< State change by audio session manager message type */
	MM_MESSAGE_CAMCORDER_MAX_SIZE,			/**< Maximum size, camcorder waits for user's order (cam_commit/cancel).*/
	MM_MESSAGE_CAMCORDER_NO_FREE_SPACE,		/**< No free space, camcorder waits for user's order (cam_commit/cancel).*/
	MM_MESSAGE_CAMCORDER_TIME_LIMIT,		/**< Time limit, camcorder waits for user's order (cam_commit/cancel)*/
	MM_MESSAGE_CAMCORDER_CAPTURED,			/**< Image captured */
	MM_MESSAGE_CAMCORDER_ERROR,			/**< Error occurred.*/
	MM_MESSAGE_CAMCORDER_FOCUS_CHANGED,		/**< Focus changed */
	MM_MESSAGE_CAMCORDER_CURRENT_VOLUME,		/**< Current volume level of real input stream */
	MM_MESSAGE_CAMCORDER_FIRMWARE_UPDATE,		/**< Firmware update */
	MM_MESSAGE_CAMCORDER_RECORDING_STATUS,		/**< Recording status. (Elapsed time, total time, file size(KB))*/
	MM_MESSAGE_CAMCORDER_STATE_CHANGED_BY_SECURITY, /**< State change by system security(ex:MDM) message type */
	MM_MESSAGE_CAMCORDER_VIDEO_SNAPSHOT_CAPTURED,	/**< Image captured while video recording */
	MM_MESSAGE_CAMCORDER_HDR_PROGRESS,		/**< Progressing percent of HDR capture */
	MM_MESSAGE_CAMCORDER_FACE_DETECT_INFO,		/**< Face detection information */
	MM_MESSAGE_CAMCORDER_VIDEO_CAPTURED,		/**< Video captured */
	MM_MESSAGE_CAMCORDER_AUDIO_CAPTURED,		/**< Audio captured */

	/* RADIO */
	MM_MESSAGE_RADIO_SCAN_START = 0x300,		/**< Radio frequency scanning initiated */
	MM_MESSAGE_RADIO_SCAN_INFO,			/**< Founded radio frequency report. check message parameters  */
	MM_MESSAGE_RADIO_SCAN_FINISH, 			/**< Radio frequency scanning has finished */
	MM_MESSAGE_RADIO_SCAN_STOP,			/**< Radio frequency scanning has stopped */
	MM_MESSAGE_RADIO_SEEK_START,			/**< Radio seeking has established */
	MM_MESSAGE_RADIO_SEEK_FINISH, 			/**< Radio seeking has finished */

	/* MEDIA CALL */
	MM_MESSAGE_MEDIACALL_RESERVED = 0x400,		/**< Reserved message for Media Call */

	/* IMAGE */
	MM_MESSAGE_IMAGE_RESERVED = 0x500,		/**< Reserved message for Image */

	/* SOUND */
	MM_MESSAGE_SOUND_PCM_CAPTURE_RESTRICTED = 0x600,	/**< Sound pcm capture is restricted by system */
	MM_MESSAGE_SOUND_PCM_INTERRUPTED,			/**< Sound pcm is interrupted by audio system */

	/* FILE INFO */
	MM_MESSAGE_FILEINFO_RESERVED = 0x700,		/**< Reserved message for File Info */

	MM_MESSAGE_NUM,					/**< The number of the messages */
};


/**
 * Union type of 'MMMessageParamType' structure. Please add type when you make new union type of MMMessageParamType
 */
enum MMMessageUnionType {
	MM_MSG_UNION_CODE,		/**< Default */
	MM_MSG_UNION_STATE,
	MM_MSG_UNION_TIME,
	MM_MSG_UNION_CONNECTION,
	MM_MSG_UNION_FIRMWARE,
	MM_MSG_UNION_RTPSENDER_REPORT,
	MM_MSG_UNION_RTPRECEIVER_REPORT,
	MM_MSG_UNION_RTPSESSION_STATUS,
	MM_MSG_UNION_SUBTITLE,
	MM_MSG_UNION_RADIO_SCAN,
	MM_MSG_UNION_RECORDING_STATUS,
	MM_MSG_UNION_REC_VOLUME_DB,
};

/*
 * Enumerations of code for MM_MESSAGE_STATE_INTERRUPTED messages type.
 */
enum MMMessageInterruptedCode {
	MM_MSG_CODE_INTERRUPTED_BY_MEDIA = 0,
	MM_MSG_CODE_INTERRUPTED_BY_CALL_START,
	MM_MSG_CODE_INTERRUPTED_BY_EARJACK_UNPLUG,
	MM_MSG_CODE_INTERRUPTED_BY_RESOURCE_CONFLICT,
	MM_MSG_CODE_INTERRUPTED_BY_ALARM_START,
	MM_MSG_CODE_INTERRUPTED_BY_ALARM_END,
	MM_MSG_CODE_INTERRUPTED_BY_EMERGENCY_START,
	MM_MSG_CODE_INTERRUPTED_BY_EMERGENCY_END,
	MM_MSG_CODE_INTERRUPTED_BY_OTHER_PLAYER_APP,
	MM_MSG_CODE_INTERRUPTED_BY_RESUMABLE_MEDIA,
};

/*
 * Enumerations of code for MM_MESSAGE_SOUND_PCM_CAPTURE_RESTRICTED messages type.
 */
enum MMMessagePcmCaptureCode {
	MM_MSG_CODE_PCM_CAPTURE_RESTRICTED = 0,
	MM_MSG_CODE_PCM_CAPTURE_ALLOWED,
};

/**
 * Message callback function type.
 */
typedef	int	(*MMMessageCallback) (int id, void *param, void *user_param);

/*
 * Enumerations of subtitle attributes for MM_MESSAGE_UPDATE_SUBTITLE messages type.
 */
typedef enum  {
	/**< region */
	MM_MSG_SUB_ATTRI_REGION_X_POS = 0,	/**< x position of subtitle region, float type */
	MM_MSG_SUB_ATTRI_REGION_Y_POS,		/**< y position of subtitle region, float type  */
	MM_MSG_SUB_ATTRI_REGION_WIDTH,		/**< width of subtitle region, float type  */
	MM_MSG_SUB_ATTRI_REGION_HEIGHT,	/**< height of subtitle region, float type  */
	/**< window */
	MM_MSG_SUB_ATTRI_WINDOW_X_PADDING,	/**< x padding of subtitle window, float type  */
	MM_MSG_SUB_ATTRI_WINDOW_Y_PADDING,	/**< y padding of subtitle window, float type  */
	MM_MSG_SUB_ATTRI_WINDOW_L_MARGIN,	/**< left margin of subtitle window, int type  */
	MM_MSG_SUB_ATTRI_WINDOW_R_MARGIN,	/**< right margin of subtitle window, int type  */
	MM_MSG_SUB_ATTRI_WINDOW_T_MARGIN,	/**< top margin of subtitle window, int type  */
	MM_MSG_SUB_ATTRI_WINDOW_B_MARGIN,	/**< bottom margin of subtitle window, int type  */
	MM_MSG_SUB_ATTRI_WINDOW_BG_COLOR,	/**< background color of subtitle window, int type  */
	MM_MSG_SUB_ATTRI_WINDOW_OPACITY,	/**< opacity of subtitle window, float type  */
	MM_MSG_SUB_ATTRI_WINDOW_SHOW_BG,	/**< how to show window background, uint type  */
	/**< font */
	MM_MSG_SUB_ATTRI_FONT_FAMILY,	/**< family of subtitle font, char* type  */
	MM_MSG_SUB_ATTRI_FONT_SIZE,		/**< size of subtitle font, float type  */
	MM_MSG_SUB_ATTRI_FONT_WEIGHT,	/**< weight of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_STYLE,		/**< style of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_COLOR,		/**< color of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_BG_COLOR,	/**< backgroung color of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_OPACITY,	/**< opacity of subtitle font, float type  */
	MM_MSG_SUB_ATTRI_FONT_BG_OPACITY,	/**< background opacity of subtitle font, float type  */
	MM_MSG_SUB_ATTRI_FONT_TOC,		/**< text outline color of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_TOT,		/**< text outline thickness of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_TOBR,		/**< text outline blur radius of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_V_ALIGN,	/**< vertical alignment of subtitle font, int type  */
	MM_MSG_SUB_ATTRI_FONT_H_ALIGN,	/**< horizontal alignment of subtitle font, int type  */
} MMMessageSubAttriType;

/**
 * Subtitle attribute Parameter.
 */
typedef struct {
	MMMessageSubAttriType attri_type;	/**< subtitle attributes type */
	unsigned int start_pos;	/**< the start position among a subtitle line from where the attribute start to apply */
	unsigned int stop_pos;	/**< the stop position among a subtitle line at where the attribute stop to apply */
	union {
		int _int;
		unsigned int _uint;
		float _float;
		char *_str;
	};
} MMSubAttribute;

/**
 * Subtitle invalid attributes define.
 */
#define MM_SUB_ATTRI_INT_INVALID -1
#define MM_SUB_ATTRI_UINT_INVALID (unsigned int)(-1)
#define MM_SUB_ATTRI_FLOAT_INVALID 0.0
#define MM_SUB_ATTRI_STR_INVALID NULL


/**
 * Message Parameter.
 */
typedef struct {
	void *data;                             /**< Allocated data */

/**
 * union.
 */
 	int union_type;    /**< Type of union. Please refer MMMessageUnionType */

	union {
		int code;                       /**< Error or warning code */
/**
 * state.
 */
		struct {
			int previous;           /**< Previous state */
			int current;            /**< Current state */
			int code;               /**< Error or warning code */
		} state;
/**
 * time.
 */
		struct {
			unsigned int elapsed;   /**< Elapsed time */
			unsigned int total;     /**< Total time */
		} time;
/**
 * connection.
 */
		struct {
			unsigned int buffering; /**< Buffering percent */
		} connection;

/**
 * firmware.
 */
		struct {
			int state;              /**< Update state*/
			int progress;           /**< Update progress percentage */
		} firmware;
/**
 * RTPSenderReport.
 */
		struct {
			unsigned char is_valid;                 /**< Structure is valid or not */
			//int64 ntptime;                        /**< The NTP timestamp indicates the point of time measured in wall clock time when this report was sent. */		  unsigned int rtptime;			/**< The RTP timestamp resembles the same time as the NTP timestamp ,but is measured in the same units and with the same random offset as the RTP timestamps in data packets */
			unsigned long long ntptime;             /**< The NTP timestamp indicates the point of time measured in wall clock time when this report was sent. */		  unsigned int rtptime;			/**< The RTP timestamp resembles the same time as the NTP timestamp ,but is measured in the same units and with the same random offset as the RTP timestamps in data packets */
			unsigned int packet_count;              /**< The sender's packet count totals up the number of RTP data packets transmitted by the sender since joining the RTP session */
			unsigned int octet_count;               /**< The total number of payload octets (i.e., not including the header or any padding) transmitted in RTP data packets by the sender since starting up transmission */
		} RTPSenderReport;      /**< RTPSenderReport message parameter structure. */
/**
 * RTPReceiverReport.
 */
		struct {
			  unsigned char is_valid;               /**< Structure is valid or not */
			  unsigned int ssrc;                    /**< The SSRC identifier of the sender whose reception is reported in this block . who the report is from */
			  unsigned char fractionlost;           /**< The sender of the receiver report estimates the fraction of the RTP data packets from source SSRC_n that it assumes to be lost since it sent the previous SR or RR packet.*/
			  unsigned int packetslost;             /**< The sender of a receiver report blocks also tries to estimate the total number of RTP data packets from source SSRC_n that have been lost since the beginning of reception. Packets that arrive late are not counted as lost, and the loss may be negative if there are duplicates. */
			  unsigned int exthighestseq;           /**< The low 16 bits of the extended highest sequence number contain the highest sequence number received in an RTP data packet from source SSRC_n, and the most significant 16 bits extend that sequence number with the corresponding count of sequence number cycles. */
			  unsigned int jitter;                  /**< An estimate of the statistical variance of the RTP data packet inter-arrival time, measured in timestamp units and expressed as an unsigned intege */
			  unsigned int lsr;                     /**< Last SR Timestamp        */
			  unsigned int dlsr;                    /**< Delay since last SR Timestamp    */
		} RTPReceiverReport;    /**< RTPReceiverReport message parameter structure. */
/**
 * RTPSessionStatus.
 */
		struct {
			double bandwidth;                       /**< Bandwidth Modifier*/
			double sender_fraction;                 /**< Fraction of packet loss by sender*/
			double receiver_fraction;               /**< Fraction of packet loss from Receiver*/
			double rtcp_bandwidth;                  /**< The total bandwidth that will be used for RTCP packets by all members of this session, in octets per second */
			double min_interval;                    /**< Minimum Interval */
			unsigned int sender_sources;            /**< Identifies the synchronization source from sender*/
			unsigned int active_sources;            /**< Identifies the Active source from sender*/
			unsigned int avg_rtcp_packet_size;      /**< Average RTCP packet size */
			unsigned int bye_members;               /**< BYE Packet members */
		} RTPSessionStatus;     /**< RTPSessionStatus message parameter structure. */
/**
 * subtitle
 */
		struct {
			unsigned long timestamp;		/**< timestamp */
			unsigned long duration;			/**< duration */
			unsigned int type;			/**< text or picture. the value of type is 0 if it's text, 1 if it's picture. */
			unsigned int attri_count;		/**< attributes count */
			MMSubAttribute **attributes;		/**< attributes of MMSubAttribute type. */
		} subtitle;

/**
 * Radio Scan Info
 */
		struct {
			int frequency;                  /**< detected active frequency with MM_MESSAGE_RADIO_SCAN_INFO */
		} radio_scan;
/**
 * Recording status
 */
		struct {
			unsigned long long elapsed;          /**< Elapsed time (ms) */
			unsigned long long total;            /**< Total time */
			unsigned long long filesize;         /**< Recording File size (KB). An approximate value. */
			unsigned long long remained_time;    /**< Remained time (ms).
			                                          This is available if time limit is not set or
			                                          time limit is bigger than estimated remained time. */
		} recording_status;

/**
 * Recording volume level - dB
 */
		float rec_volume_dB;
	};

	int size;       /**< Allocated size of 'data' */

	int reserved;   /**< reserved field for future use */
} MMMessageParamType;

/**
 * @}
 */

#ifdef __cplusplus
	}
#endif


#endif	/* __MM_MESSAGE_H__ */
