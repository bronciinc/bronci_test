#include <string>
#include <iostream>
#include <map>
#include <functional>
#if __has_include(<format>)
#include <format>
namespace strfmt = std;
#else
#include <fmt/format.h>
namespace strfmt = fmt;
#endif
#include <thread>

#include <signal.h>
#include <unistd.h>

#include <nlohmann/json.hpp>
#include "crc.hpp"   // for boost::crc_32_type

#include "libntil.h"

#define MAX_FRAME_SIZE_OF_PRIMARY_STREAM ((512+1024)*1024)		// 1.5 MB
#define ALLOWABLE_MAX_LINE        12

#define SLEEP(x)    sleep(x)

using json = nlohmann::json;

namespace mylog
{
template <typename... Args>
void error(strfmt::format_string<Args...> fmt, Args&&... args) {
    // Format the string
    std::string message = strfmt::format(fmt, std::forward<Args>(args)...);

    // Output to console (could also write to file, etc.)
    std::cout << "(ERR) " << message << '\n';
}

template <typename... Args>
void message(strfmt::format_string<Args...> fmt, Args&&... args) {
    // Format the string
    std::string message = strfmt::format(fmt, std::forward<Args>(args)...);

    // Output to console (could also write to file, etc.)
    std::cout << "(LOG) " << message << '\n';
}

void message(std::string_view message) {
    // Output to console (could also write to file, etc.)
    std::cout << "(LOG) " << message << '\n';
}
}

std::map<int, json> test_config;
int lineID;

inline bool startsWith(const std::string& str, const std::string& prefix) { return str.compare(0, prefix.size(), prefix) == 0; }

static void cb_lpStartStreming(void* args)
{
  int line = (long)args;

  lineID = line;
  mylog::message("[CB-lpStartStreming] line={}", line);
}

static void cb_lpCloseStreaming(int line)
{
  mylog::message("[CB-lpCloseStreaming] line={}", line);
}

static void cb_lpMessage(unsigned int message, C2C_LONG arg1, C2C_LONG arg2, int lineId, void* arg_extra)
{
  int ret = 0;
  std::string out;

  strfmt::format_to(std::back_inserter(out), "[CB-lpMessage]");
  switch(message)
  {
  case C2C_REGISTER_DONE:
    // recv register done notification from svr
    strfmt::format_to(std::back_inserter(out), "[C2C_REGISTER_DONE]");
    break;

  case C2C_REGISTER_FAIL:
    strfmt::format_to(std::back_inserter(out), "[C2C_REGISTER_FAIL]");
    if(arg1 == C2C_UNAUTHORIZED)
    {
      // register failed because of invalid password or account
      strfmt::format_to(std::back_inserter(out), "\n ...Registration failed! accout or password may be invalid");
    }
    else if(arg1 == C2C_INVALID_ACCOUNT)
    {
      // register failed because account does not exist
      strfmt::format_to(std::back_inserter(out), "\n ...Registration failed! accout is invalid");
    }
    else if(arg1 == C2C_SRV_NO_RESP)
    {
      // register failed because server did not response
      strfmt::format_to(std::back_inserter(out), "\n ...Registration failed! server did not response");
    }
    else if(arg1 == C2C_SRV_DISCONNECT)
    {
      // register failed because server disconnected the connection
      strfmt::format_to(std::back_inserter(out), "\n ...Registration failed! server disconnected");
    }
    // _c2c_register_status = message;
    // _c2c_register_reason = arg1;
    break;

  case C2C_OUTGOING_STATE:
    // recv "outgoing call processing" notification from remote
    strfmt::format_to(std::back_inserter(out), "[C2C_OUTGOING_STATE]");
    if(arg1 == C2C_PROCESSING)
    {
    }
    else if(arg1 == C2C_NEED_AUTH)
    {
    }
    break;

  case C2C_OUTGOING_ERROR:
    strfmt::format_to(std::back_inserter(out), "[C2C_OUTGOING_ERROR]");
    if(arg1 == C2C_UNAUTHORIZED)
    {
    // outgoing call event: account or password for IPCam is invalid
    }
    else if(arg1 == C2C_SRV_NO_RESP)
    {
    }
    break;

  case C2C_INCOMING_STATE:
    strfmt::format_to(std::back_inserter(out), "[C2C_INCOMING_STATE]");
    strfmt::format_to(std::back_inserter(out), "\n ...event...from line {}", lineId);
    // a new incoming call
    if(arg2)
    {
      C2C_CALL_INFO* cinfo = (C2C_CALL_INFO*)arg2;
      strfmt::format_to(std::back_inserter(out), "\n ...A new incomming call! From {}, to {}, custom-info is {}, auth-lv={}, line={}", cinfo->szPeerId, cinfo->szLocalId, cinfo->szCustomInfo, cinfo->nAuthLevel, lineId);
    }
    break;

  case C2C_REMOTE_RSP:
    // recv response from remote side
    strfmt::format_to(std::back_inserter(out), "[C2C_REMOTE_RSP]");
    break;

  case C2C_P2P_MODE:
    // media streaming starts in P2P mode
    strfmt::format_to(std::back_inserter(out), "[C2C_P2P_MODE]");
    strfmt::format_to(std::back_inserter(out), "\n ...Media session has been established in P2P mode!");
    strfmt::format_to(std::back_inserter(out), "\n ...socket={}, line={}", arg1, lineId);

    ret = NTIL_SendCommandByRtp(lineId, (char*)"CONNECTED", (char*)"C2C_P2P_MODE", true);
    strfmt::format_to(std::back_inserter(out), "\n ...NTIL_SendCommandByRtp to line {} returns {}", lineId, ret);
    if(arg2)
    {
      C2C_CALL_INFO* cinfo = (C2C_CALL_INFO*)arg2;
      strfmt::format_to(std::back_inserter(out), "\n ...(arg2) peer={}, custom-info={}, auth-lv={}, line={}", cinfo->szPeerId, cinfo->szCustomInfo, cinfo->nAuthLevel, lineId);
    }
    break;

  case C2C_RELAY_MODE:
    // media streaming starts in relay mode
    strfmt::format_to(std::back_inserter(out), "[C2C_RELAY_MODE]");
    strfmt::format_to(std::back_inserter(out), "\n ...Media session has been established in RELAY mode!");
    strfmt::format_to(std::back_inserter(out), "\n ...socket={}, line={}", arg1, lineId);

    ret = NTIL_SendCommandByRtp(lineId, (char*)"CONNECTED", (char*)"C2C_RELAY_MODE", true);
    strfmt::format_to(std::back_inserter(out), "\n ...NTIL_SendCommandByRtp to line {} returns {}", lineId, ret);
    if(arg2)
    {
      C2C_CALL_INFO* cinfo = (C2C_CALL_INFO*)arg2;
      strfmt::format_to(std::back_inserter(out), "\n ...(arg2) peer={}, custom-info is {}, auth-lv={}, line={}", cinfo->szPeerId, cinfo->szCustomInfo, cinfo->nAuthLevel, lineId);
    }
    break;

  case C2C_PACKET_LOSS:
    // packet loss event, call disconnect
    strfmt::format_to(std::back_inserter(out), "[C2C_PACKET_LOSS]");
    break;

  case C2C_CALL_TERMINATED:
    // call disconnect notification
    strfmt::format_to(std::back_inserter(out), "[C2C_CALL_TERMINATED]");
    strfmt::format_to(std::back_inserter(out), "\n ...Media session has been stopped ... peer={}, line={}", (char*)arg2, lineId);
    break;

  case C2C_RECV_BUSY:
    // outgoing call event: remote busy
    strfmt::format_to(std::back_inserter(out), "[C2C_RECV_BUSY]");
    break;

  case C2C_RECV_404:
    // callee does not exist (offline), or call session no longer exists
    strfmt::format_to(std::back_inserter(out), "[C2C_RECV_404]");
    break;

  case C2C_NOANSWER:
    // outgoing call event: callsetup process has done, but remote has no further action
    strfmt::format_to(std::back_inserter(out), "[C2C_NOANSWER]");
    break;

  case C2C_CONNECT_TIMEOUT:
    // incoming call event: wait P2P connection timeout
    strfmt::format_to(std::back_inserter(out), "[C2C_CONNECT_TIMEOUT]");
    break;

  case C2C_COMMAND_MESSAGE:
    // command MESSAGE from remote side
    strfmt::format_to(std::back_inserter(out), "[C2C_COMMAND_MESSAGE]");
    {
      char *msg = (char*)arg1;
      char *peer = (char*)arg2;
      char *feedback = (char*)arg_extra;

      if(msg==NULL || peer==NULL)
        break;

      strfmt::format_to(std::back_inserter(out), "\n ...from {}, msg={}, line={}", peer, msg, lineId);

      // reply with echo
      if(feedback)
      {
        strcpy(feedback, msg);
      }
    }
    break;

  case C2C_COMMAND_ACK:
    // command ACK from remote side
    strfmt::format_to(std::back_inserter(out), "[C2C_COMMAND_ACK]");
    {
      char *msg = (char*)arg1;
      char *peer = (char*)arg2;
      if(msg==NULL || peer==NULL)
        break;
      strfmt::format_to(std::back_inserter(out), "\n ...from {}, msg={}, line={}", peer, msg, lineId);
    }
    break;

  case C2C_COMMAND_ERROR:
    strfmt::format_to(std::back_inserter(out), "[C2C_COMMAND_ERROR]");
    // error notification for previous sent command
    {

    }
    break;

  case C2C_QOS_LEVEL_DOWN:
    strfmt::format_to(std::back_inserter(out), "[C2C_QOS_LEVEL_DOWN]");
    break;

  case C2C_QOS_LEVEL_UP:
    strfmt::format_to(std::back_inserter(out), "[C2C_QOS_LEVEL_UP]");
    ret = NTIL_SendCommandByRtp(lineId, (char*)"QOS_REPORT", (char*)"C2C_QOS_LEVEL_UP", true);
    strfmt::format_to(std::back_inserter(out), "\n ...NTIL_SendCommandByRtp to line {} returns {}", lineId, ret);
    break;

  case C2C_SERVICE_READY:
    strfmt::format_to(std::back_inserter(out), "[C2C_SERVICE_READY]");
    break;

  case C2C_INCOMING_DETECTED:
    strfmt::format_to(std::back_inserter(out), "[C2C_INCOMING_DETECTED]");
    break;

  case C2C_RTP_PRE_ALLOCATE:
    strfmt::format_to(std::back_inserter(out), "[C2C_RTP_PRE_ALLOCATE]");
    break;

  case C2C_LOGOUT_BY_SVR:
    strfmt::format_to(std::back_inserter(out), "[C2C_LOGOUT_BY_SVR]");
    break;

  default:
    strfmt::format_to(std::back_inserter(out), "[UNKNOWN] [{}]{:#x}", lineId, message);
    break;
  }

  mylog::message(out);
}

static void cb_lpAudio_RecvData(int line, unsigned char *data, int len, int payload_type, unsigned int timestamps, int seq)
{
  // process received audio data
  mylog::message("[CB-audio] recv audio data {} bytes from line {}, payload-type is {}, timestamps is {}, frame-id is {}", len, line, payload_type, timestamps, seq);
}

static void cb_lpVideo_RecvData(int line, unsigned char *data, int len, int payload_type, unsigned int timestamps, int frame_rate, int frame_type, int seq)
{
  // process received video data
  mylog::message("[CB-video] recv video data {} bytes from line {}, payload-type is {}, timestamps is {}, fps={}, frame_type={}, frame-id is {}", len, line, payload_type, timestamps, frame_rate, frame_type, seq);
}


//==========================================================================================================================
// job
static inline void sendState(int nLineId, int tid, const char* msg)
{
  int nRet;

  std::string tag = strfmt::format("test_state.{:04x}",tid);
  nRet = NTIL_SendCommandByRtp(nLineId, (char*)tag.c_str(), (char*)msg, true);
  mylog::message("  - (sendState) [{}] : {}", tid, msg);
}

static void jobSendingVideo(uint32_t tid)
{
  auto it = test_config.find(tid);
  json& data = it->second;

  int result = 0;
  int size_i = data["frame"]["I"]["size"];
  int num_i = data["frame"]["I"]["num"];
  int interval_i = data["frame"]["I"]["interval"];
  int size_p = data["frame"]["P"]["size"];
  int num_p = data["frame"]["P"]["num"];
  int interval_p = data["frame"]["P"]["interval"];
  int send = data["num"];

  mylog::message("  TID={}, num={}", tid, send);
  mylog::message("  I-frame.size={}, num={}, interval={}", size_i, num_i, interval_i);
  mylog::message("  P-frame.size={}, num={}, interval={}", size_p, num_p, interval_p);

  uint16_t ts_frame=0;
  uint16_t frame_id=0;
  uint16_t gop_id=0;
  const uint16_t fps=0;
  const uint16_t bps=0;

  uint8_t* pbuff_i = new uint8_t[size_i];
  uint8_t* pbuff_p = new uint8_t[size_p];

  struct frame_t{
    uint32_t tid;	// test ID
    uint32_t gop;	// gop # : 0-based
    uint32_t fid;	// frame # : 0-based
    uint32_t crc32;	// crc32
  };

  sendState( lineID, tid, "start");
  for( int cnt_send = 0; cnt_send < send; cnt_send++)
  {
    mylog::message("  Sending... #{}", cnt_send);

    // I-frame
    for( int cnt_i = 0; cnt_i < num_i; cnt_i++)
    {
      memset( pbuff_i, 0xE0+cnt_i, size_i);

      frame_t* pheader = (frame_t*)pbuff_i;
      frame_t* pheader1 = (frame_t*)pbuff_i + 1;

      pheader1->tid = pheader->tid = tid;
      pheader1->gop = pheader->gop = gop_id;
      pheader1->fid = pheader->fid = cnt_i;
      pheader1->crc32 = pheader->crc32 = 0;

      // CRC32
      boost::crc_32_type crc32;
      crc32.process_bytes( pheader+1, size_i-sizeof(frame_t));
      pheader->crc32 = crc32.checksum();

      do
      {
        result = NTIL_VideoPutInData( lineID, pbuff_i, size_i, FRAME_TYPE_IDR, ts_frame, frame_id, gop_id, fps, bps, H264);
        if( result != size_i )
        {
          mylog::error(" -NTIL_VideoPutInData() I-[{}][{}]: {} ", cnt_send, cnt_i, result);
          mylog::message(" -NTIL_VideoPutInData() I-[{}][{}]: {} ", cnt_send, cnt_i, result);
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_i));
        frame_id++;
      } while (result != size_i);
    }

    // P-frame
    for( int cnt_p = 0; cnt_p < num_p; cnt_p++)
    {
      memset( pbuff_p, 0xC0+cnt_p, size_p);

      frame_t* pheader = (frame_t*)pbuff_p;
      pheader->tid = tid;
      pheader->gop = gop_id;
      pheader->fid = num_i+cnt_p;

      // CRC32
      boost::crc_32_type crc32;
      crc32.process_bytes( pheader+1, size_p-sizeof(frame_t));
      pheader->crc32 = crc32.checksum();

      do
      {
        result = NTIL_VideoPutInData( lineID, pbuff_p, size_p, FRAME_TYPE_P, ts_frame, frame_id, gop_id, fps, bps, H264);
        if( result != size_p )
        {
          mylog::error(" -NTIL_VideoPutInData() P-[{}][{}]: {} ", cnt_send, cnt_p, result);
          mylog::message(" -NTIL_VideoPutInData() P-[{}][{}]: {} ", cnt_send, cnt_p, result);
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_p));
        frame_id++;
      } while (result != size_p);
    }

    gop_id++;
    ts_frame++;
  }

  delete [] pbuff_i;
  delete [] pbuff_p;

  sendState( lineID, tid, "done");
  mylog::message("  Sending... DONE");

  mylog::message("  Waiting 1secs to terminate this connection");
  std::this_thread::sleep_for(std::chrono::seconds(1));

  NTIL_TerminateConnection( lineID );

  mylog::message(" (jobSendingVideo) done");
}
//==========================================================================================================================


//==========================================================================================================================
// callback
static void cbcmd_connected(C2C_LONG arg1, char* tag, char* cmd_msg, void* arg_extra)
{
  if( arg1 == RTP_COMMAND_ACK )
    mylog::message("  [CB-lpCommand][CONNECTED] tag={} msg={} extra={:p}", tag, cmd_msg, arg_extra);
  else
    mylog::message("  [CB-lpCommand][CONNECTED] type is different. tag={} msg={}  extra={:p} type={:#x}", tag, cmd_msg, arg_extra, arg1);
}

static void cbcmd_test_spec(C2C_LONG arg1, char* tag, char* cmd_msg, void* arg_extra)
{
  mylog::message("  [CB-lpCommand][TEST] tag={} msg={}, extra={:p} type={:#x}", tag, cmd_msg, arg_extra, arg1);

  uint32_t tid;

  std::string str(tag);
  std::size_t pos = str.find('.');
  if (pos != std::string::npos)
  {
    // extract after '.'
    std::string numberPart = str.substr(pos + 1);

    tid = std::stoi(numberPart);
    mylog::message("  TID={}", tid);
  }
  else
  {
    mylog::message("  Can't find TID, so the request is ignored.");
    return;
  }

  try
  {
    json data = json::parse(cmd_msg);

    // ack
    if( arg_extra != nullptr )
    {
      sprintf((char*)arg_extra, "ACK_%s", tag);
    }

    test_config[tid] = data;

    std::thread t( jobSendingVideo, tid);

    t.detach();
  }

  catch(const std::exception& e)
  {
    mylog::error(" exception {}", e.what() );

    // nack
    if( arg_extra != nullptr )
    {
      sprintf((char*)arg_extra, "NACK_%s", tag);
    }
  }
}

static void cbcmd_test_state_ack(C2C_LONG arg1, char* tag, char* cmd_msg, void* arg_extra)
{
  if( arg1 == RTP_COMMAND_ACK )
    mylog::message("  [CB-lpCommand][ACK] tag={} msg={}, extra={:p}", tag, cmd_msg, arg_extra);
  else
    mylog::message("  [CB-lpCommand] type is different. tag={} msg={}, extra={:p} type={:#x}", tag, cmd_msg, arg_extra, arg1);
}

static void cbcmd_qos_report(C2C_LONG arg1, char* tag, char* cmd_msg, void* arg_extra)
{
  if( arg1 == RTP_COMMAND_ACK )
    mylog::message("  [CB-lpCommand][ACK] tag={} msg={}, extra={:p}", tag, cmd_msg, arg_extra);
  else
    mylog::message("  [CB-lpCommand] type is different. tag={} msg={}, extra={:p}, type={:#x}", tag, cmd_msg, arg_extra, arg1);
}

static std::map<std::string, std::function<void(C2C_LONG arg1, char* tag, char* cmd_msg, void* arg_extra)>> cmd_tag =
{
  {"CONNECTED", 	cbcmd_connected},
  {"test_spec.", 	cbcmd_test_spec},
  {"test_state.", cbcmd_test_state_ack},
  {"QOS_REPORT",  cbcmd_qos_report}
};


static void cb_lpCommand_RecvData(int line, C2C_LONG arg1, C2C_LONG arg2, char* tag, char* cmd_msg, void* arg_extra)
{
  // process received custom command
  mylog::message("[CB-lpCommand] line={}, arg1={:#2x}, tag={}, msg={}", line, arg1, tag, cmd_msg);

  auto it = std::find_if(cmd_tag.begin(), cmd_tag.end(),
    [tag](const auto& pair) { return startsWith( tag, pair.first); });

  if( it != cmd_tag.end() )
  {
    it->second( arg1, tag, cmd_msg, arg_extra);
  }
  else
  {
    mylog::message(" - uncategorized");

    // recv command MESSAGE through RTP
    if(arg1==RTP_COMMAND_MESSAGE)
    {
      if( arg_extra != nullptr )
      {
        sprintf((char*)arg_extra, "uncategorized");
      }
    }
    // recv command ACK through RTP
    else
    {
    }
  }
}
//==========================================================================================================================



//==========================================================================================================================
static void SignalRequestExit(int sigNum)
{
  mylog::message("============= p2psvr sig {}; DO NOT try NTIL_Release =============\n", sigNum);

  // ask for leaving run
  if(NTIL_IsAnyMediaSessionAlive())
  {
    NTIL_StopAllMediaSession();

    SLEEP(1);
  }

  NTIL_DeInitialize();

  exit(0);
}

static bool init_signal()
{
  if (signal(SIGTERM, SignalRequestExit) == SIG_ERR)
  {
    mylog::error("set SIGTERM failed\n");
    return false;
  }
  if (signal(SIGINT, SignalRequestExit) == SIG_ERR)
  {
    mylog::error("set SIGINT failed\n");
    return false;
  }

  return true;
}
//==========================================================================================================================


typedef struct
{
  char	szURL[128];
  char	szAccount[128];
  char 	szPassword[128];
  char	szLocalAccount[128];
  char 	szLocalPassword[128];
} CONFIG;

bool init_ntilsdk(std::pair<std::string, std::string> u)
{
  int max_line = ALLOWABLE_MAX_LINE;

  //============Set Account==================
  CONFIG data;
  memset(&data, 0,sizeof(data));

  strcpy(data.szURL, "webgateinc.iptnet.net");
  strcpy(data.szAccount, u.first.c_str());
  strcpy(data.szPassword, u.second.c_str());
  strcpy(data.szLocalAccount, "webgate");
  strcpy(data.szLocalPassword, "p2p@webgate");


  //==========================================
  init_signal();

  mylog::message("[init] libntil version: {}", NTIL_GetVersionString());
  mylog::message("[init] Start C2C process");

  //============Fill Initialization Info==================
  C2C_INIT_INFO init;
  memset(&init, 0, sizeof(C2C_INIT_INFO));

  NTIL_GetDefaultInitParam(&init);

  init.nMaxLine = max_line;
  init.szServerAddr = data.szURL;
  init.szRegAccount = data.szAccount;
  init.szRegPassword = data.szPassword;

  init.lpMessage = cb_lpMessage;
  init.lpAudio_RecvData = cb_lpAudio_RecvData;
  init.lpVideo_RecvData = cb_lpVideo_RecvData;
  init.lpCommand_RecvData = cb_lpCommand_RecvData;

  //init.avBufferSetup.nMaxVideoFrames = 16;		// max allowable video frames in queue
  //init.avBufferSetup.nMaxVideoFrames = 64;		// max allowable video frames in queue
  //init.avBufferSetup.nMaxVideoFrames = 128;		// max allowable video frames in queue
  //init.avBufferSetup.nMaxVideoFrames = 256;		// max allowable video frames in queue -> NG
  init.avBufferSetup.nMaxVideoFrames = 512;		// max allowable video frames in queue -> OK
  //init.avBufferSetup.nMaxVideoFrames = 1024;	// max allowable video frames in queue -> OK
  init.avBufferSetup.nMaxVideoFramesInSec = 0;
  init.avBufferSetup.nMaxVideoSize = MAX_FRAME_SIZE_OF_PRIMARY_STREAM;	// max length of a video frame
  init.avBufferSetup.nMaxAudioSize = 1400;		// max length of an audio frame

  int tx_buf_num = 6 * (32*1024) / 8;
  int rx_buf_num = 6 * (32*1024) / 8;
  NTIL_SetVideoRTPBuffer(rx_buf_num, tx_buf_num);

  if( !NTIL_Initialize2(&init, NULL) )
  {


    NTIL_StreamingCallback( cb_lpStartStreming, cb_lpCloseStreaming); //setup video stream callback
    NTIL_SetLocalAuthentication(data.szLocalAccount, data.szLocalPassword, 0);
    NTIL_StartRegisterProcess(data.szURL, data.szAccount, data.szPassword);
  }
  else
    return false;

  max_line = NTIL_GetMaxSupportedMediaLine();
  mylog::message("[init] MAX_LINE={}", max_line);

  return true;
}


int childmain(std::pair<std::string, std::string> u)
{
  size_t Chunk_sz = 0;

  mylog::message("[main] NTIL ver.{}", NTIL_GetVersionString());

  mylog::message("[main] p2p initialization begins.");

  if( false == init_ntilsdk(u) )
  {
    mylog::message("[main] p2p daemon initialization failure.");
    return 0;
  }

  mylog::message("[main] p2p daemon initialization success.");
  NTIL_ShowDebugMessage( false );

  //setup chunk size
  //NTIL_SendCommandByRtp header 128byte + null terminal
  Chunk_sz = NTIL_GetMaxRtpCommandSize();
  mylog::message("[main] p2p chunk size={}",(unsigned int) Chunk_sz);
  assert(Chunk_sz > 0);

  for(;;)
  {
    SLEEP(10);
  }

  mylog::message("[main] p2p daemon is finalizing...");
  NTIL_DeInitialize();
  mylog::message("[main] p2p daemon finalized.");

  return 0;
}
