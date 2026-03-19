#ifndef __LIBNTIL_PARAM_H
#define __LIBNTIL_PARAM_H

#include <stddef.h>
#ifndef __cplusplus
	#ifndef bool
	#define bool	unsigned char
	#endif
	#ifndef true
	#define true	1
	#endif
	#ifndef false
	#define false	0
	#endif
#endif

#ifdef _MSC_VER
	#ifdef _WIN64
	#define C2C_LONG	__int64
	#else
	#define C2C_LONG	long
	#endif
#else
	#define C2C_LONG	long
#endif

/////////////////////////////////////////////////////////////////////////////
// Message Events Defined for CallBack

// ===================== MAIN EVENT ===================== //
#define C2C_REGISTERING			0x01
#define C2C_REGISTER_AGAIN		0x02
#define C2C_REGISTER_DONE		0x03
#define C2C_REGISTER_FAIL		0x04
#define C2C_OUTGOING_STATE		0x05
#define C2C_OUTGOING_ERROR		0x06
#define C2C_INCOMING_STATE		0x07
#define C2C_INCOMING_ERROR		0x08
#define C2C_REMOTE_RSP			0x09
#define C2C_P2P_MODE			0x0A			// 10
#define C2C_RELAY_MODE			0x0B
#define C2C_RECV_404			0x0C
#define C2C_RECV_BUSY			0x0D
#define C2C_NOANSWER			0x0E
#define C2C_PACKET_LOSS			0x0F			// 15
#define C2C_CALL_TERMINATED		0x10
#define C2C_CONNECT_TIMEOUT		0x11
#define C2C_LAN_SCAN_TIMEOUT	0x12
#define C2C_LAN_SCAN_ERROR		0x13
#define C2C_COMMAND_MESSAGE		0x14			// 20
#define C2C_COMMAND_ERROR		0x15
#define C2C_COMMAND_ACK			0x16
#define C2C_QOS_LEVEL_DOWN		0x17
#define C2C_QOS_LEVEL_UP		0x18
#define C2C_LOGOUT_BY_SVR		0x19			// 25
#define C2C_RELEASE_DONE		0x1A
#define C2C_RELEASE_FAIL		0x1B
#define C2C_RECV_ALERT			0x1C
#define C2C_SETUP_DONE			0x1D
#define C2C_SETUP_ERROR			0x1E			// 30
#define C2C_RECV_4XX			0x1F
#define C2C_ARDT_DONE			0x20
#define C2C_ARDT_FAIL			0x21
#define C2C_RELEASE_REQ			0x22
#define C2C_ARDT_REQ			0x23			// 35
#define C2C_REQ_CANCELED		0x24
#define C2C_INFO_MSG			0x25
#define C2C_INFO_ACK			0x26
#define C2C_BYTE_MESSAGE		0x27
#define C2C_BYTE_ERROR			0x28			// 40
#define C2C_BYTE_ACK			0x29
#define C2C_CONNECT_STATE		0x2A
#define C2C_CONNECT_ERROR		0x2B
#define C2C_CONNECT_P2P			0x2C
#define C2C_CONNECT_RELAY		0x2D			// 45
#define C2C_NOTIFY_DONE			0x2E
#define C2C_NOTIFY_ERROR		0x2F
#define C2C_SERVICE_READY		0x30
#define C2C_COMMAND_PROCESS		0x31
#define C2C_BYTE_PROCESS		0x32			// 50
#define C2C_LOGOUT_DONE			0x33
#define C2C_LOGOUT_FAIL			0x34
#define C2C_INFO_ERROR			0x35
#define C2C_INCOMING_DETECTED	0x36
#define C2C_RELAY_TO_P2P_DONE	0x37			// 55
#define C2C_RELAY_TO_P2P_FAIL	0x38
#define C2C_ARTP_DONE			0x39
#define C2C_ARTP_FAIL			0x3A
#define C2C_ARTP_END			0x3B
#define C2C_SP_INFO_DONE		0x3C			// 60
#define C2C_SP_INFO_UPDATE		0x3D
#define C2C_SEND_IOT_DONE		0x3E
#define C2C_SEND_IOT_FAIL		0x3F
#define C2C_SEND_ALERT_DONE		0x40
#define C2C_SEND_ALERT_FAIL		0x41			// 65
#define C2C_RELAY_ALERT			0x42
#define C2C_MAIN_TASK_BLOCKING	0x43
#define C2C_RUNNING_CHECK		0x44
#define C2C_AUDIO_QOS_DOWN		0x45
#define C2C_AUDIO_QOS_UP		0x46			// 70
#define C2C_IOT_ACK_RECYCLED	0x47
#define C2C_CMD_ACK_RECYCLED	0x48
#define C2C_P2P_MODE_CHANGING	0x49
#define C2C_RTP_PRE_ALLOCATE    0x4A

// ===================== SUB EVENT ===================== //
#define C2C_SUCCESS				0x0
#define	C2C_ERROR_OCCUR			0x01
#define	C2C_UNAUTHORIZED		0x02
#define	C2C_INVALID_ACCOUNT		0x03
#define C2C_SRV_DISCONNECT		0x04
#define C2C_SRV_NO_RESP			0x05
#define C2C_NEED_AUTH			0x06
#define C2C_PROCESSING			0x07
#define C2C_REMOTE_BUSY			0x08
#define C2C_REMOTE_UNREACHED	0x09
#define C2C_REMOTE_NO_RESP		0x0A			// 10
#define C2C_LOCAL_BUSY			0x0B
#define C2C_MESSAGE_TOO_LARGE	0x0C
#define C2C_FORBIDDEN			0x0D
#define C2C_TIMEOUT				0x0E
#define C2C_RELAY_FAIL			0x0F			// 15
#define C2C_RELAY_NO_RESP		0x10
#define C2C_UNAVAILABLE			0x11
#define C2C_INVALID_ARGS		0x12
#define C2C_INVALID_STATE		0x13
#define C2C_SOCKET_ERROR		0x14			// 20
#define	C2C_STARTUP_FAIL		0x15
#define C2C_GET_INFO_FAIL		0x16
#define C2C_NOT_ALLOWED			0x17
#define C2C_BAD_FORMAT			0x18
#define C2C_OUT_OF_MEMORY		0x19			// 25
#define C2C_INVALID_FRAME		0x1A
#define C2C_BUFFER_OVERFLOW		0x1B
#define C2C_REDIRECT			0x1C
#define C2C_OP_DENIED			0x1D
#define C2C_NO_RESOURCE			0x1E
#define C2C_SVR_FAIL			0x1F
#define C2C_TRYING				0x20
#define C2C_OP_PENDING			0x21
#define C2C_PENDING_TIMEOUT		0x22
#define C2C_TCP_SENDER_TRY		0x23
#define C2C_TCP_SENDER_BUSY		0x24

// =============== Global Definition =================== //
#define	RTP_COMMAND_MESSAGE		0x80
#define	RTP_COMMAND_ACK			0x81
#define RTP_COMMAND_ERROR		0x82
#define RTP_COMMAND_TIMEOUT		0x83

#define C2C_NETWORK_MODE_UDP		0
#define C2C_NETWORK_MODE_TCP		1
#define C2C_NETWORK_MODE_UDP_RELAY	2

#define C2C_TRANS_MODE_P2P			0
#define C2C_TRANS_MODE_RELAY		1
#define C2C_TRANS_MODE_LAN			2
#define C2C_TRANS_MODE_UDP_RELAY	3
#define C2C_TRANS_MODE_NONE			-1

#define BYTE_CMD_TAG			"B64MSG"

#define RECV_BY_RTP				0
#define RECV_BY_PROTOCOL		1

#define C2C_ALERT_TYPE_MOTION		0x01
#define C2C_ALERT_TYPE_AUDIO		0x02

// =============== Payload Type =================== //
// *********** Audio *********** //
#define G711_U		0
#define	PCM_8K		4
#define	ADPCM		5
#define	PCM_11K		6
#define	PCM_16K		7
#define G711_A		8
#define G711_16		9
#define	ADPCM_11K	10
#define ADPCM_16K	11
#define G729		18
#define AAC			96
// *********** Video *********** //
#define JPG			26
#define MPEG4		30
#define H263		34
#define H264		35
#define H265		36
#define JPEG		JPG

// =============== Frame Type =======================
#define FRAME_TYPE_P		0
#define FRAME_TYPE_I		1
#define FRAME_TYPE_IDR		2

// ==============================================
#define C2C_QOS_STRICTEST	0
#define C2C_QOS_STRICT		1
#define C2C_QOS_DEFAULT		2
#define C2C_QOS_LOOSE		3
#define C2C_QOS_LOOSEST		4

#define C2C_TERMINATE_STATE_NORMAL			0
#define C2C_TERMINATE_STATE_PKT_LOSS		1
#define C2C_TERMINATE_STATE_RLY_DISCONNECT	2

typedef struct
{
	char*		szPeerId;
	char*		szLocalId;
	int			nAuthLevel;
	char*		szCustomInfo;
	int			nByeCode;
}
C2C_CALL_INFO;

typedef struct
{
	int			nSocket;
	int			nMode;					// 0: udp, 1: tcp
	int		    nRelayCalleePortId;
	int		    nRelayCallerPortId;
	char		szPeerIPAddr[64];
	int			nPeerPort;
}
C2C_RESOURCE_INFO;

typedef struct
{
	const char*	szLogoutId;
	const char*	szLogoutMsg;
	int			nLogoutCode;
}
C2C_LOGOUT_INFO;

typedef struct
{
	unsigned int remain_traffic;
	unsigned int remain_time;
}
C2C_RELAY_INFO;

typedef struct
{
	const char*		szExtraMessage;
	unsigned int	uExtraMessageLength;
	unsigned int	uExtraCode;
	char*			pFeedback;
	unsigned int*	pFeedbackSize;
}
C2C_EXTRA_INFO;

typedef struct
{
	int	nMaxVideoFrames;
	int	nMaxVideoSize;
	int	nMaxAudioFrames;
	int	nMaxAudioSize;
	int	nMaxVideoFramesInSec; // set to 0 to use nMaxVideoFrames only; if this field is set, the maximum number buffered video frames will refer to actual FPS and nMaxVideoFrames.
	int	nMaxAllowableLostVideoPacketNum; // valid from 8 ~ 256; when this value is large, the SDK can tolerate more video packet lost but also introduce longer video latency
}
C2C_AV_BUFFER_SETUP;

typedef struct
{
	char*			pMemPool;
	unsigned int	uMemPoolSize;
	void*			pNext;
}
C2C_MEMPOOL_SETUP;

typedef struct
{
	int		nMaxLine;
	char*	szServerAddr;
	char*	szRegAccount;
	char*	szRegPassword;
	void (*lpMessage)(unsigned int, C2C_LONG, C2C_LONG, int, void*);
	void (*lpAudio_RecvData)(int, unsigned char *, int, int, unsigned int, int);
	void (*lpVideo_RecvData)(int, unsigned char *, int, int, unsigned int, int, int, int);
	void (*lpCommand_RecvData)(int, C2C_LONG, C2C_LONG, char*, char*, void*);
	C2C_AV_BUFFER_SETUP avBufferSetup;
	unsigned int uMaxNetworkQueuePacketNum;		// at least to be 1024; set 0 to use default
	C2C_MEMPOOL_SETUP* pMemPoolSetup;
	unsigned int uExtraQueueEventSize;
}
C2C_INIT_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////
// multiple languages alert message

typedef struct
{
	const char* str;
}
C2C_LOC_ARG;

typedef struct
{
	const char* key;
	const char* val; // pure string
}
C2C_KEY_VAL;

typedef struct
{
	const char*		sound;
	const char*		action;
//	--------- expansion ---------
	unsigned int	extend_num;
	C2C_KEY_VAL*	extend_array;
}
C2C_CTRL_MSG;

typedef struct
{
	const char*		action_key;
	const char*		title_key;
	unsigned int	title_args_num;
	C2C_LOC_ARG*	title_args_array;
	const char*		msg_key;
	unsigned int	msg_args_num;
	C2C_LOC_ARG*	msg_args_array;
//	--------- expansion ---------
	unsigned int	extend_num;
	C2C_KEY_VAL*	extend_array;
}
C2C_LOC_ALERT;

// for NTIL_SendAlert2()
typedef struct
{
	unsigned int alert_type;
	const C2C_LOC_ALERT* multi_lang_msg;
	const C2C_CTRL_MSG* ctl_msg;
	const char* alert_msg;
	const char* sub_uid;
	char* appendix;
}
C2C_SEND_ALERT;
typedef struct
{
	int resp_code;
	const char *msg;
}
C2C_ALERT_ACK;

// C2C JSON sytanx
typedef void* C2C_JSYNTAX;
#define NTIL_JSyntax CJSON_Syntax
#ifndef JSTR_POINTER
#define JSTR_POINTER 0xFFFFFFFF
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// IOT message

// request type
typedef enum
{
	C2C_IOT_UNKNOWN_REQ=0,
	C2C_IOT_CTRL_TRANS,
	C2C_IOT_CONTROL,
	C2C_IOT_EVENT,
	C2C_IOT_INFO,
	C2C_IOT_GET_CONFIG
}
C2C_IOT_REQ_TYPE;
#define C2C_IOT_REQ_TYPE_STR(val, str) {\
if      ((val)==C2C_IOT_UNKNOWN_REQ) (str)="";\
else if ((val)==C2C_IOT_CTRL_TRANS)  (str)="ctltrans";\
else if ((val)==C2C_IOT_CONTROL)     (str)="control";\
else if ((val)==C2C_IOT_EVENT)       (str)="event";\
else if ((val)==C2C_IOT_INFO)        (str)="info";\
else if ((val)==C2C_IOT_GET_CONFIG)  (str)="getconfig";\
}

// source type
typedef enum
{
	C2C_IOT_UNKNOWN_SRC=0,
	C2C_IOT_DEVICE,
	C2C_IOT_SERVER,
	C2C_IOT_ALEXA,
	C2C_IOT_APP
}
C2C_IOT_SRC_TYPE;
#define C2C_IOT_SRC_TYPE_STR(val, str) {\
if      ((val)==C2C_IOT_UNKNOWN_SRC) (str)="";\
else if ((val)==C2C_IOT_DEVICE)      (str)="device";\
else if ((val)==C2C_IOT_SERVER)      (str)="server";\
else if ((val)==C2C_IOT_ALEXA)       (str)="alexa";\
else if ((val)==C2C_IOT_APP)         (str)="app";\
}

// event record
typedef enum
{
	C2C_IOT_NO_EVENT=0,
	C2C_IOT_RECORDING_START,
	C2C_IOT_RECORDING_STOP,
	C2C_IOT_LIVEVIEW_START,
	C2C_IOT_LIVEVIEW_STOP,
	C2C_IOT_MOTION,
	C2C_IOT_ONLINE,
	C2C_IOT_OFFLINE,
	C2C_IOT_DOORBELL,
	C2C_IOT_REC_UPLOAD_START,
	C2C_IOT_REC_UPLOAD_STOP,
	C2C_IOT_LENS_COVER_OPEN,
	C2C_IOT_LENS_COVER_CLOSE,
	C2C_IOT_NIGHT_VISION_ON,
	C2C_IOT_NIGHT_VISION_OFF,
	C2C_IOT_SOUND_DETECTED,
	C2C_IOT_MOTION_STOP,
}
C2C_IOT_EVT;
#define C2C_IOT_EVT_STR(val, str) {\
if      ((val)==C2C_IOT_NO_EVENT)         (str)="";\
else if ((val)==C2C_IOT_RECORDING_START)  (str)="recording_start";\
else if ((val)==C2C_IOT_RECORDING_STOP)   (str)="recording_stop";\
else if ((val)==C2C_IOT_LIVEVIEW_START)   (str)="live_viewing_start";\
else if ((val)==C2C_IOT_LIVEVIEW_STOP)    (str)="live_viewing_stop";\
else if ((val)==C2C_IOT_MOTION)           (str)="motion";\
else if ((val)==C2C_IOT_ONLINE)           (str)="online";\
else if ((val)==C2C_IOT_OFFLINE)          (str)="offline";\
else if ((val)==C2C_IOT_DOORBELL)         (str)="doorbell_event";\
else if ((val)==C2C_IOT_REC_UPLOAD_START) (str)="record_file_upload_start";\
else if ((val)==C2C_IOT_REC_UPLOAD_STOP)  (str)="record_file_upload_stop";\
else if ((val)==C2C_IOT_LENS_COVER_OPEN)  (str)="lens_cover_open";\
else if ((val)==C2C_IOT_LENS_COVER_CLOSE) (str)="lens_cover_close";\
else if ((val)==C2C_IOT_NIGHT_VISION_ON)  (str)="nightvision_on";\
else if ((val)==C2C_IOT_NIGHT_VISION_OFF) (str)="nightvision_off";\
else if ((val)==C2C_IOT_SOUND_DETECTED)   (str)="sound_detected";\
else if ((val)==C2C_IOT_MOTION_STOP)      (str)="motion_stop";\
}

// IoT vlaue format
typedef enum
{
	C2C_IOT_JSON_STR=0,
	C2C_IOT_FLOAT,
	C2C_IOT_BOOL,
	C2C_IOT_INT,
	C2C_IOT_STR
}
C2C_IOT_FORMAT;

// receive IoT command
typedef struct
{
	const char *nickname;
	C2C_IOT_REQ_TYPE request;
	C2C_IOT_SRC_TYPE source;
	C2C_IOT_EVT event;
}
C2C_IOT_EX_MSG;
typedef struct
{
	char *desired; // JSON string
	char *reported; // JSON string
}
C2C_CTRL_STATE;
typedef struct
{
	void *usr_ptr;
	char *from_uid;
	char *from_sub_uid;
	char *to_sub_uid;
	char *command;
	union {
	const char *msg;
	C2C_CTRL_STATE *ctrl; };
	char *feedback;
	int   feedback_size;
	C2C_IOT_EX_MSG extra_msg;
	int lineID, feedback_code;
}
C2C_IOT_PARAM;
typedef void (*C2C_IOT_CALLBACK)(C2C_IOT_PARAM*);

// IoT value object
typedef struct
{
	C2C_IOT_FORMAT format;
	union {
	const char *json; // JSON string
	const char *str;
	float floating;
	bool boolean;
	int integer; };
}
C2C_IOT_VAL;

// IoT information
typedef struct
{
	int type_id;
	int delay_msec;
	C2C_IOT_VAL value;
}
C2C_IOT_INFO_DATA;

// IoT ACK
typedef struct
{
	int resp_code;
	const char *msg;
}
C2C_IOT_ACK;

////////////////////////////////////////////////////////////////////////////////////////////////////
// SP information

typedef enum
{
	CTX_UNKNOWN=0,
	CTX_TCP=1,
	CTX_UDP=2,
	CTX_SSL=3
}
C2C_SERVER_METHOD;
typedef struct
{
	char domain[256];
	unsigned short port;
	C2C_SERVER_METHOD method;
}
C2C_SERVER_ADDR;
typedef struct
{
	char token[68];
	unsigned int t_begin;	// token begin time (seconds, UTC+0)
	unsigned int t_expires;	// token expire time (seconds, UTC+0)
	unsigned int server_num;
	C2C_SERVER_ADDR server[3];
}
C2C_SP_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Old API name define (#define old new)

#define NTIL_VideoPutInDataNoWaitingIDR NTIL_VideoPutInDataNotCheckKeyFrame

#endif

