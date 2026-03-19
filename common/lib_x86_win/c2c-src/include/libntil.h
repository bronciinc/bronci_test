#ifndef __LIBNTIL_H
#define __LIBNTIL_H

#include "libntilParam.h"

#ifdef __cplusplus
extern "C" {
#endif

// ====================== General APIs ====================== //
int NTIL_Initialize(char* svr_addr, char* reg_acc, char* reg_pwd,
							void (*lpMessage)(unsigned int, C2C_LONG, C2C_LONG, int, void*),
							void (*lpAudio_RecvData)(int, unsigned char *, int, int, unsigned int, int),
							void (*lpVideo_RecvData)(int, unsigned char *, int, int, unsigned int, int, int, int),
							void (*lpCommand_RecvData)(int, C2C_LONG, C2C_LONG, char*, char*, void*),
							void* arg);

void NTIL_SetVideoRTPBuffer(int receiver_num, int transmit_num); // set a number of video buffers for RTP, 1K bytes per buffer (packet), it can be 0.

void NTIL_GetVideoRTPBuffer(int *receiver_num, int *transmit_num);

void NTIL_SetAudioRTPBuffer(int receiver_num, int transmit_num); // set a number of audio buffers for RTP, it can be 0.

void NTIL_GetAudioRTPBuffer(int *receiver_num, int *transmit_num);

int NTIL_SetVideoRTPBufferByLine(int lineId, int receiver_num, int transmit_num); // use this API when C2C_RTP_PRE_ALLOCATE event occurred

int NTIL_SetAudioRTPBufferByLine(int lineId, int receiver_num, int transmit_num); // use this API when C2C_RTP_PRE_ALLOCATE event occurred

void NTIL_GetDefaultInitParam(C2C_INIT_INFO* init);

int NTIL_Initialize2(C2C_INIT_INFO* init, void* arg);

int NTIL_GetRegPasswordMD5(char* md5_passwd);

int NTIL_GeneratePasswordMD5(const char* uid, const char* pwd, char* md5_passwd);

int NTIL_DeInitialize(void);

int NTIL_IsLineOccupied(int line);

int NTIL_SetLocalAuthentication(char* auth_acc, char* auth_pwd, int auth_id);

int NTIL_GetMediaEncryptionMaxLevel(void); // return max encryption level

int NTIL_SetMediaEncryption(int level); // return real encryption level

int NTIL_GetCertificationMaxLevel(void); // return max certification level

int NTIL_SetCertificationLevel(int level); // return real certification level

void NTIL_SetQuickRelayMode(bool is_quick_mode);

int NTIL_GetLocalSubUid(int lineId, char* target_uid, int buf_size); // use it in C2C main message callback

void NTIL_EnableLocalAuthentication(bool enable);

void NTIL_EnableRunningCheckEvent(unsigned int periodic);

void NTIL_StreamingCallback(void (*lpStartStreaming)(void*), void (*lpCloseStreaming)(int));

int NTIL_StartRegisterProcess(char* svr_addr, char* reg_acc, char* reg_pwd);

int NTIL_StartRegisterProcess2(char* svr_addr, char* reg_acc, char* reg_pwd, char* token);

int NTIL_TerminateConnection(int lineId);

int NTIL_TerminateConnection2(int lineId, char* msg);

int NTIL_TerminateConnection3(int lineId, char* msg, int code);

int NTIL_VideoPutInDataNotCheckKeyFrame(int lineId, bool enable);

int NTIL_VideoPutInData(int lineId, unsigned char *pVideo, int length, int frame_type, unsigned int ts, unsigned int frame_id, unsigned int gop_id, int fps, unsigned int bit_rate, int payload_type);

int NTIL_AudioPutInData(int lineId, unsigned char *pAudio, int length, unsigned int ts, unsigned int frame_id, int duration, int payload_type);

int NTIL_VideoPutInDataExtra(int lineId, unsigned char *data, int dlen, unsigned char *extra, int extra_len, int frame_type, unsigned int ts, unsigned int frame_id, unsigned int gop_id, int fps, unsigned int bit_rate, int payload_type);

int NTIL_AudioPutInDataExtra(int lineId, unsigned char *data, int dlen, unsigned char *extra, int extra_len, unsigned int ts, unsigned int frame_id, int duration, int payload_type);

unsigned char *NTIL_GetVideoExtraData(int lineId, int *length); // use it in C2C receive video callback

unsigned char *NTIL_GetAudioExtraData(int lineId, int *length); // use it in C2C receive audio callback

int NTIL_RequirePutInVideoBuffer(int line, int dlen, unsigned char **buf, int *bsize); // this API can be used with NTIL_VideoPutInData() ONLY

int NTIL_RequirePutInAudioBuffer(int line, int dlen, unsigned char **buf, int *bsize); // this API can be used with NTIL_AudioPutInData() ONLY

int NTIL_GetMaxSupportedMediaLine(void);

int NTIL_GetRtpRecvScore(int line, int* video, int* audio);

int NTIL_GetPeerRtpRecvBitRate(int line, unsigned int* bps, unsigned int* avg_bps);

int NTIL_SendCommandByRtp(int line, char* tag, char* cmd_msg, bool enable_resend);

int NTIL_StartRtpReliableMode(int Line); // ARTP

int NTIL_CancelRtpReliableMode(int Line); // ARTP

int NTIL_SendCommandByProtocol(char* peerId, char * account, char * password, char* cmd_msg);

int NTIL_SendLANCommandByProtocol(char* peerId, char * account, char * password, char* cmd_msg, char* ifname);

int NTIL_SendCommandByProtocolViaConnection(int line, char* cmd_msg);

int NTIL_SendByteCommand(char* peerId, char * account, char * password, char* cmd_msg, int cmd_size);

int NTIL_SendByteCommandViaConnection(int line, char* cmd_msg, int cmd_size);

int NTIL_GetMaxValidFeedbackSize(void);

int NTIL_GetMaxRtpCommandSize(void);

int NTIL_GetMaxByteCommandSize(void);

int NTIL_SetPacketLossEventTriggerDuration(int seconds);

int NTIL_Base64Encode(char* src, int src_len, char* dest, int dest_size);

int NTIL_Base64Decode(char* src, int src_len, char* dest, int dest_size);

int NTIL_ReleaseSocketControl(int line);

bool NTIL_ShowDebugMessage(bool enable);

int NTIL_SetDefaultSocketBufferSize(int buf_size);

int NTIL_GetDefaultSocketBufferSize(void);

void NTIL_MediaBufferReset(int line);

const char* NTIL_GetVersionString(void);

bool NTIL_IsRegistrationDone(void);

int NTIL_SubscribeInfoEvent(void (*cb)(unsigned int, C2C_LONG, C2C_LONG, void*));

int NTIL_UnsubscribeInfoEvent(void (*cb)(unsigned int, C2C_LONG, C2C_LONG, void*));

int NTIL_GetServicePrivilege(C2C_SP_INFO* info);

int NTIL_RedoRegistration(void);

int NTIL_QueryTransmissionMode(int line);

int NTIL_GetReferenceRandomString(int line, char* key, int key_length);

int NTIL_SetRegistrationPollingMode(int mode);

unsigned int NTIL_GetCurrentTimestamps(void);

int NTIL_SetStringFeedback(char* content, char* feedback);

int NTIL_SetByteFeedback(char* content, int content_length, C2C_EXTRA_INFO* ex);

int NTIL_SetTcpRelayFirst(bool enable);

int NTIL_GetAuthLevel(int lineId);

int NTIL_RefreshRegisterProcess(void);

int NTIL_StartLogoutProcess(void);

int NTIL_GetRegExpireTime(void);

int NTIL_UpdateState(void);

unsigned int NTIL_GetLastServerTimestamps(void);

unsigned int NTIL_GetServerUnixTime(void);

int NTIL_IsAnyLineOccupied(void);

int NTIL_TryDelayedFeedback(int lineId, void *usr_ptr);

int NTIL_CreateDelayedIoTFeedback(int lineId, const char* feedback, int code);

int NTIL_CreateDelayedCmdFeedback(int lineId, const char* feedback);

// ====================== Embedded Device APIs ====================== //
void NTIL_ServiceSuspend(int suspend);

void NTIL_StopAllMediaSession(void);			// stop all connections

void NTIL_StopMediaSession(int line);		// stop the connection on #line

bool NTIL_IsAnyMediaSessionAlive(void);			// is there any client connecting in?

bool NTIL_IsMediaSessionAlive(int line);	// is there connection on #line?

int NTIL_SendAlert(char* alert_msg, unsigned int alert_type, char* appendix);		// "alert_type" should be one of 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, ..., 0x4000, 0x8000

int NTIL_SendAlertWithCtrl(const char* alert_msg, const C2C_CTRL_MSG* ctl_msg, unsigned int alert_type, char* appendix);

int NTIL_SendMultiLangAlert(const C2C_LOC_ALERT* alert_msg, const C2C_CTRL_MSG* ctl_msg, unsigned int alert_type, char* appendix);

int NTIL_SendAlert2(C2C_SEND_ALERT* param);

int NTIL_AcceptCurrentRequest(int line);

int NTIL_RejectCurrentRequest(int line);

int NTIL_SetStrictnessOfQoS(int qosDown, int qosUp);	// 0~4 (strictest~loosest)

int NTIL_SetLowBandwidthMode(int line, bool enable);

int NTIL_SetNotificationByProvider(char* obj, int code);

int NTIL_SetStreamingTransBehavior(int max_busy_retry, int enable_sleep_for_retry, int enable_aggresive_mode);

// ====================== Viewer APIs ====================== //
char* NTIL_BundleUID(const char* agent_uid, const char* target_uid, char* bundled_uid, unsigned int size);

int NTIL_StartConnection(char* peer_id, char* auth_acc, char* auth_pwd, char* call_msg);

int NTIL_StartLANConnection(char* peer_id, char* auth_acc, char* auth_pwd, char* call_msg, char* ifname);

int NTIL_StartConnectionEnforceRelay(char* peer_id, char* auth_acc, char* auth_pwd, char* call_msg);	// this API is for special application and is only allowed for specific accounts

int NTIL_EnforceRelaySwitchToP2P(int line);

int NTIL_GetRegistrationUID(char* reg_id, int id_size, char* suffix, char* domain);

int NTIL_GetRegistrationPassword(char* reg_id, char* passwd, int passwd_size);

int NTIL_SetNotification(char* notify_id, char* obj, int code);

int NTIL_SetC2CNotification(char* notify_id, char* obj, int code);

int NTIL_SetNotification2(char* notify_id, char* obj, int code, char* appendix);

int NTIL_SetC2CNotification2(char* notify_id, char* obj, int code, char* appendix);

int NTIL_SetNotification3(char* notify_id, char* obj, char* account, char* password, int code, char* appendix);

int NTIL_SetC2CNotification3(char* notify_id, char* obj, char* account, char* password, int code, char* appendix);

int NTIL_QueryNotification(char* notify_id, char* obj);

int NTIL_ResetAllNotification(void);

int NTIL_SetFastConnection(bool enable);

void NTIL_SetLanModeCommunication(int enable);

// ====================== For Special Case ====================== //
int NTIL_SendNotification2DesignatedUser(char* peerId, char* msg, int type, char* appendix);

// ====================== For RTOS Device ====================== //
void NTIL_SetKeepAlive(bool enable);

int NTIL_CreateKeepAlivePacket(char* data, unsigned int dsize, char* addr, unsigned int asize, unsigned short* port);

int NTIL_SetKeepAlivePacketForSleep(unsigned int keep_alive_sec);

// ====================== C2C JSON sytanx ====================== //
unsigned int NTIL_JsonLen(const char* jstr);

int NTIL_JSyntaxInit(C2C_JSYNTAX* obj, unsigned int obj_size, const char* jstr);

int NTIL_JSyntaxFree(C2C_JSYNTAX obj);

extern int NTIL_JSyntax(C2C_JSYNTAX obj, void* out, unsigned int osize, unsigned int layer_num, ...);

// ====================== IoT APIs ====================== //
void NTIL_SetIoTHandler(C2C_IOT_CALLBACK handler, void* usr_ptr);

int NTIL_SetIoTFeedback(C2C_IOT_PARAM* param, const char* cmd_msg); // use it in C2C_IOT_CALLBACK callback

unsigned int NTIL_SetWaitIoTAckExtendTimeout(unsigned int extend_sec);

int NTIL_IoTSendEvent(C2C_IOT_SRC_TYPE src_type, C2C_IOT_EVT evt_type, const char* sub_uid, const char* nickname, int delay_msec, const char *command, C2C_IOT_VAL data);

int NTIL_IoTSendEvent2(C2C_IOT_SRC_TYPE src_type, const char* evt_type, const char* sub_uid, const char* nickname, int delay_msec, const char *command, C2C_IOT_VAL data);

int NTIL_IoTSendInfo(C2C_IOT_SRC_TYPE src_type, const char* sub_uid, const char* nickname, C2C_IOT_INFO_DATA* array, unsigned int num);

int NTIL_IoTCtrlDesired(C2C_IOT_SRC_TYPE src_type, const char* from_sub_uid, const char* peerId, const char* nickname, const char* json, int flags);

int NTIL_IoTCtrlReported(C2C_IOT_SRC_TYPE src_type, const char* from_sub_uid, const char* nickname, const char* json, int flags);

int NTIL_IoTCtrlDesiredWithReported(C2C_IOT_SRC_TYPE src_type, const char* from_sub_uid, const char* peerId, const char* nickname, const char* d_json, const char* r_json, int flags);

int NTIL_IoTGetConfig(C2C_IOT_SRC_TYPE src_type);

#ifdef __cplusplus
}
#endif

#endif // #if undefined(__LIBNTIL_H)
