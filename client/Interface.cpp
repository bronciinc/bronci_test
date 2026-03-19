#ifdef _WIN32
#include <windows.h>
#else
#include <mutex>
#include <chrono>
#include <thread>

typedef std::mutex CRITICAL_SECTION;
inline void InitializeCriticalSection(CRITICAL_SECTION *cs) { }
inline void EnterCriticalSection(CRITICAL_SECTION *cs) { cs->lock(); }
inline void LeaveCriticalSection(CRITICAL_SECTION *cs) { cs->unlock(); }

typedef unsigned long long ULONGLONG;
inline ULONGLONG GetTickCount64() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
inline void Sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
#endif
#include <stdio.h>
#include <string>
#include <list>

#include <vector>
#include <limits>
#include <map>
#include <cstring>

#include "libntil.h"
#include "crc.hpp"


constexpr int MAX_C2CSENDERBUF_SIZE = 1024-128-1;
constexpr int MAX_WESPSENDERBUF_SIZE = MAX_C2CSENDERBUF_SIZE*3/4;

constexpr int SIZE_REG_BUFF = 64;

constexpr int STRING_UID_LENGTH = 10; //XXXX-XXXX[null]

#define STRING_SERVER_URL       "webgateinc.iptnet.net"
#define STRING_UID_APPEND       "@webgateinc.iptnet.net"
#define STRING_UID_ID           "webgate"
#define STRING_UID_PASSWORD     "p2p@webgate"


enum class LINK_STATUS
{
  UNLINKED,
  LINKING,
  LINKED_DIRECT,
  LINKED_RELAY
};

typedef struct tagC2CMessage
{
  int lineId;
  unsigned int message;
  C2C_LONG wParam;
  C2C_LONG lParam;
}C2C_MESSAGE;

typedef struct tagC2CData
{
  int lineID;
  unsigned char* data;
  unsigned long length;
}C2C_DATA;


std::list<C2C_MESSAGE*> g_listMessage;
CRITICAL_SECTION g_csC2CMessageQue;

std::list<C2C_DATA*> g_listData;
CRITICAL_SECTION g_csC2CDataQue;


char m_pcRegID[SIZE_REG_BUFF];
char m_pcRegPassword[SIZE_REG_BUFF];
unsigned long m_ulCmdNumber;

LINK_STATUS link[8];

#define NUM_CONNECTION  0


#define TAG_TEST        "test_state."
#define CMD_TEST_ACK    "ACK_test_state."
#define CMD_TEST_START  "start"
#define CMD_TEST_DONE   "done"


typedef struct {
  uint32_t tid;
  uint32_t gop;
  uint32_t fid;
  uint32_t crc32;
} frame_t;

typedef struct {
  ULONGLONG tick;
  frame_t header;
  bool ok;
} capture_t;


using captre_v = std::vector<capture_t>;

std::map<uint32_t, captre_v> test_captures;
ULONGLONG test_start;
ULONGLONG test_done;

extern const uint32_t cfg_gops;


static void dumpGop_v(captre_v& result)
{
  for( auto& it: result)
  {
    printf("     - [%lld] %s : tid=%d, gop=%d, frame=%d, crc32=0x%x\r\n", it.tick, it.ok?"OK":"NG", it.header.tid, it.header.gop, it.header.fid, it.header.crc32);
  }
}

static bool checkGop(captre_v& gop)
{
  uint32_t seq = 0;
  bool err = false;
  ULONGLONG last_tick = 0;

  for( auto& it: gop)
  {
    if( test_start > it.tick )
    {
      printf(" time error : frame=%lldms < start=%lldms >  \r\n", it.tick, test_start);
      err = true;
    }

    if( test_done < it.tick )
    {
      printf(" time error : done=%lldms < frame=%lldms \r\n", test_done, it.tick);
      err = true;
    }

    if( last_tick > it.tick )
    {
      printf(" time error : last_tick=%lldms > frame=%lldms \r\n", last_tick, it.tick);
      err = true;
    }

    if( seq != it.header.fid )
    {
      printf(" Sequence error : %d expected, but not %d \r\n", seq, it.header.fid);
      err = true;
    }

    if( err )
    {
      dumpGop_v(gop);
      break;
    }

    seq++;
    last_tick = it.tick;
  }

  return !err;
}

static void viewResult(void)
{
  printf("\r\n");
  printf("============================================\r\n");
  printf("         CHECK                              \r\n");
  printf("============================================\r\n");

  ULONGLONG last_tick=0;
  ULONGLONG sum_frames = 0;

  if( test_captures.size() > cfg_gops )
  {
    printf(" (error) captured gop size(%lld) is over %d\r\n", (long long)test_captures.size(), cfg_gops);
  }

  for( uint32_t gop_id=0; gop_id < cfg_gops; gop_id++)
  {
    auto pGop = test_captures.find(gop_id);

    if( pGop == test_captures.end() )
    {
      printf("  - (error) no GOP #%d\r\n", gop_id);
      continue;
    }
    sum_frames += pGop->second.size();

    printf(" - GOP #%d testing : ", pGop->first);
    if( true == checkGop(pGop->second) )
    {
      printf("OK\r");
    }

    ULONGLONG tick = pGop->second.front().tick;
    if( last_tick > tick)
    {
      printf("  - (error) the time sequence of GOP #%d(tick:%lld) < the last tick %lld\r\n", gop_id, tick, last_tick);
    }
    last_tick = tick;
  }

  double elpased = (double)(test_done - test_start)/1000.;

  printf("============================================\r\n");
  printf("         RESULT                             \r\n");
  printf("============================================\r\n");
  printf(" - CMD time diff=%5.2fs (%lld ~ %lld)\r\n", elpased, test_start, test_done);
  printf(" - expect : frames=%d\r\n", cfg_gops*30);
  printf(" - received : frames=%lld, fps=%5.2f\r\n", sum_frames, sum_frames/elpased);
  printf(" - loss frames=%lld, ratio=%5.1f%%\r\n", cfg_gops*30 - sum_frames, float(cfg_gops*30 - sum_frames)*100./(cfg_gops*30));

  printf(" - DONE\r\n");
}

static void checkVideo(C2C_DATA* pData)
{
  frame_t* pheader = (frame_t*)pData->data;

  boost::crc_32_type crc32;
  crc32.process_bytes( pheader+1, pData->length - sizeof(frame_t));
  bool ok = (pheader->crc32 == crc32.checksum())? true: false;


  capture_t result;

  result.header = *pheader;
  result.tick = GetTickCount64();
  result.ok = ok;

  test_captures[result.header.gop].push_back( result );
}

static int getTID(std::string tag)
{
  uint32_t tid=0;

  std::size_t pos = tag.find('.');
  if (pos != std::string::npos)
  {
    std::string numberPart = tag.substr(pos + 1);

    tid = std::stoi(numberPart);
  }

  return tid;
}


static void SetLinkStatus(int nLineID, LINK_STATUS ucStatus)
{
  link[nLineID] = ucStatus;
}

static LINK_STATUS GetLinkStatus(int nLineID)
{
  return link[nLineID];
}



//Brunci P2P Callback functions
static void C2C_MessageCallback(unsigned int message, C2C_LONG wParam, C2C_LONG lParam, int lineId, void* arg_extra)
{
	printf("C2C_Message[%u]<%lld,%lld> lineID:%d\n", message, (long long)wParam, (long long)lParam, lineId);

	C2C_MESSAGE* pMessage = new C2C_MESSAGE;
	pMessage->lineId = lineId;
	pMessage->message = message;
	pMessage->wParam = wParam;
	pMessage->lParam = lParam;

	::EnterCriticalSection(&g_csC2CMessageQue);
	g_listMessage.push_back(pMessage);
	::LeaveCriticalSection(&g_csC2CMessageQue);
}

static void C2C_CommandCallback(int line, C2C_LONG wParam, C2C_LONG lParam, char* tag, char* cmd_msg, void* arg_extra)
{
  printf("C2C_CommandCallback[%9lld](%d] %s:%s (0x%llx)\n", (long long)GetTickCount64(), line, tag, cmd_msg, (unsigned long long)wParam);

  if ((tag == NULL) || (cmd_msg == NULL))
    return;

  if( strncmp(cmd_msg, CMD_TEST_ACK, strlen(CMD_TEST_ACK)) == 0 )
  {
    printf("ACK : TID=%d\r\n", getTID(tag));
  }

  if( strncmp(tag, TAG_TEST, strlen(TAG_TEST)) == 0 )
  {
    if( strncmp(cmd_msg, CMD_TEST_START, strlen(CMD_TEST_START)) == 0 )
    {
      test_start = GetTickCount64();
      printf("START : TID=%d (%lld)\r\n", getTID(tag), test_start);
    }
    if( strncmp(cmd_msg, CMD_TEST_DONE, strlen(CMD_TEST_DONE)) == 0 )
    {
      test_done = GetTickCount64();
      printf("STOP : TID=%d (%lld)\r\n", getTID(tag), test_done);
    }
  }

  if( arg_extra != nullptr )
  {
    char* buff = (char*)arg_extra;
    sprintf(buff, "%s-ok", cmd_msg);
  }
}

static void C2C_AudioCallback(int line, unsigned char* data, int len, int payload_type, unsigned int timestamps, int seq)
{
  printf("A");
}

static void C2C_VideoCallback(int line, unsigned char* data, int len, int payload_type, unsigned int timestamps, int frame_rate, int frame_type, int seq)
{
  printf("V");

  if (len > 0)
  {
    C2C_DATA* pData = new C2C_DATA;

    pData->data = new unsigned char[len];
    if (pData->data)
    {
      memcpy(pData->data, data, len);
      pData->length = len;
      pData->lineID = line;

      ::EnterCriticalSection(&g_csC2CDataQue);
      g_listData.push_back(pData);
      ::LeaveCriticalSection(&g_csC2CDataQue);
    }
    else
    {
      printf("C2C_VideoCallback(): Failed allocating memory\n");
      delete pData;
    }
  }
  else
  {
    printf("C2C_VideoCallback(): len is zero\n");
  }
}

static void C2C_lpStartStreming(void* args)
{
  printf("[CB-lpStartStreming] line=%p\n", args);
}

static void C2C_lpCloseStreaming(int line)
{
  printf("[CB-lpCloseStreaming] line=%d\n", line);
}



bool Initialize(void)
{
	::InitializeCriticalSection(&g_csC2CDataQue);
	::InitializeCriticalSection(&g_csC2CMessageQue);

  NTIL_GetRegistrationUID(m_pcRegID, SIZE_REG_BUFF, (char*)STRING_UID_ID, (char*)STRING_SERVER_URL);

  NTIL_GetRegistrationPassword(m_pcRegID, m_pcRegPassword, SIZE_REG_BUFF);

  // printf("(dbg) ID:%s, PW:%s\r\n", m_pcRegID, m_pcRegPassword);

  if (NTIL_Initialize((char*)STRING_SERVER_URL, m_pcRegID, m_pcRegPassword,
                      C2C_MessageCallback, C2C_AudioCallback, C2C_VideoCallback, C2C_CommandCallback, NULL) != 0)
  {
    return false;
  }

  NTIL_StreamingCallback( C2C_lpStartStreming, C2C_lpCloseStreaming); //setup video stream callback

  if (NTIL_StartRegisterProcess((char*)STRING_SERVER_URL, m_pcRegID, m_pcRegPassword) != 0)
  {
    return false;
  }

#ifdef _DEBUG
  int a = NTIL_GetMaxRtpCommandSize();
  int b = NTIL_GetMaxValidFeedbackSize();
  int c = NTIL_GetMaxSupportedMediaLine();
  printf("-MaxRtpCommandSize %d\n-MaxValidFeedbackSize %d\n-MaxSupportedMediaLine %d\n", a, b, c);
#endif

  return true;
}

void Disconnect(int nLineId);

static bool MessageHandler(void)
{
  if (g_listMessage.size())
  {
    C2C_MESSAGE* pMessage;

    ::EnterCriticalSection(&g_csC2CMessageQue);
    pMessage = g_listMessage.front();
    g_listMessage.pop_front();
    ::LeaveCriticalSection(&g_csC2CMessageQue);

    switch (pMessage->message)
    {
    case C2C_REGISTER_DONE:
      printf("[C2C_REGISTER_DONE]\r\n");
      break;

    case C2C_REGISTER_FAIL:
      printf("[C2C_REGISTER_FAIL]\r\n");
      break;

    case C2C_INVALID_STATE:
      printf("[C2C_INVALID_STATE]\r\n");
      break;

    case C2C_NO_RESOURCE:
      printf("[C2C_NO_RESOURCE]\r\n");
      break;

    case C2C_PACKET_LOSS:
      printf("[C2C_PACKET_LOSS]\r\n");
      break;

    case C2C_CALL_TERMINATED:
      printf("[C2C_CALL_TERMINATED]\r\n");
      viewResult();
      [[fallthrough]];
    case C2C_NOANSWER:
      printf("[C2C_NOANSWER]\r\n");
      Disconnect(pMessage->lineId);
      break;

    case C2C_LOGOUT_BY_SVR:
      printf("[C2C_LOGOUT_BY_SVR]\r\n");
      break;

    case C2C_P2P_MODE:
      printf("[C2C_P2P_MODE]\r\n");
      SetLinkStatus(pMessage->lineId, LINK_STATUS::LINKED_DIRECT);
      break;

    case C2C_RELAY_MODE:
      printf("[C2C_RELAY_MODE]\r\n");
      SetLinkStatus(pMessage->lineId, LINK_STATUS::LINKED_RELAY);
      Disconnect(pMessage->lineId);
      break;

    case C2C_RECV_404:
      printf("[C2C_RECV_404]\r\n");
      [[fallthrough]];
    case C2C_OUTGOING_ERROR:
      printf("[C2C_OUTGOING_ERROR]\r\n");
      break;

    case C2C_RELAY_TO_P2P_DONE:
      printf("[C2C_RELAY_TO_P2P_DONE]\r\n");
      SetLinkStatus(pMessage->lineId, LINK_STATUS::LINKED_DIRECT);
      break;

    case C2C_RELAY_TO_P2P_FAIL:
      printf("[C2C_RELAY_TO_P2P_FAIL]\r\n");
        break;

    case C2C_SERVICE_READY:
      printf("[C2C_SERVICE_READY]\r\n");
      break;

    case C2C_OUTGOING_STATE:
      printf("[C2C_OUTGOING_STATE]\r\n");
      break;

    case C2C_REMOTE_RSP:
      printf("[C2C_REMOTE_RSP]\r\n");
      break;

    case C2C_RTP_PRE_ALLOCATE:
      printf("[C2C_RTP_PRE_ALLOCATE]\r\n");
      break;

    case C2C_QOS_LEVEL_DOWN:
      printf("[C2C_QOS_LEVEL_DOWN]\r\n");
      break;

    case C2C_QOS_LEVEL_UP:
      printf("[C2C_QOS_LEVEL_UP]\r\n");
      break;

    /*case C2C_RELAY_ALERT:
      LockingUidByLineId(pMessage->lineId);
      SendWgiDbg('L', NULL, pMessage->lineId);
      break;*/
    default:
      printf("[UNKNOWN] 0x%x\r\n", pMessage->message);
      break;
    }

    delete pMessage;
  }
  else
  {
    Sleep(1);
  }

  return true;
}

static void DataHandler(void)
{
  int nPendingDataSize = (int)g_listData.size();

  if (nPendingDataSize == 0)
  {
    Sleep(1);
    return;
  }

  for (int i = 0;i < nPendingDataSize;i++)
  {
    C2C_DATA* pData;

    ::EnterCriticalSection(&g_csC2CDataQue);
    if (g_listData.empty())
    {
      ::LeaveCriticalSection(&g_csC2CDataQue);
      break;
    }
    pData = g_listData.front();
    g_listData.pop_front();
    ::LeaveCriticalSection(&g_csC2CDataQue);

    checkVideo(pData);

    delete pData;
  }
}


bool Connect(const char *pcUid, int* pnLineId)
{
  char pcUidWithNull[STRING_UID_LENGTH];

  memcpy(pcUidWithNull, pcUid, STRING_UID_LENGTH - 1);
  pcUidWithNull[9] = 0;

  {
    //NTIL_SetFastConnection(true);
    char pcUidWithDomain[128];
    sprintf(pcUidWithDomain, "%s%s", pcUidWithNull, STRING_UID_APPEND);

    //NTIL_ShowDebugMessage(true);

    *pnLineId = NTIL_StartConnection(pcUidWithDomain, (char*)STRING_UID_ID, (char*)STRING_UID_PASSWORD, NULL);
    //*pnLineId = NTIL_StartConnectionEnforceRelay(pcUidWithDomain, (char*)STRING_UID_ID, (char*)STRING_UID_PASSWORD, NULL);

    printf("NTIL_StartConnection(%s, %s, %s) = %d\n", pcUidWithDomain, m_pcRegID, m_pcRegPassword, *pnLineId);

    if (*pnLineId < 0)
    {
      return false;
    }

    SetLinkStatus( *pnLineId, LINK_STATUS::LINKING);

    ULONGLONG ullTimedoutTick = GetTickCount64() + (10 * 1000);

    while (ullTimedoutTick > GetTickCount64())
    {
      if( GetLinkStatus( *pnLineId ) != LINK_STATUS::LINKING )
      {
        break;
      }

      MessageHandler();
      DataHandler();
    }

    if( GetLinkStatus( *pnLineId ) > LINK_STATUS::LINKING )
    {
      return true;
    }
  }

  return false;
}

void Disconnect(int nLineId)
{
  if( GetLinkStatus( nLineId ) != LINK_STATUS::UNLINKED )
  {
    printf("NTIL_TerminateConnection(%d)\n", nLineId);

    link[nLineId] = LINK_STATUS::UNLINKED;

    if (NTIL_TerminateConnection(nLineId) != 0)
    {
      printf(">> [FAIL] Disconnection\n");
    }
  }
}

bool SendTestCommand(int nLineId, char* pucData, size_t ulLength)
{
  bool bReturn = false;

  if( GetLinkStatus( nLineId ) == LINK_STATUS::LINKED_DIRECT )
  {
    if (ulLength < MAX_WESPSENDERBUF_SIZE)
    {
      char pcTag[16];

      m_ulCmdNumber++;
      unsigned char* pucCmdNumber = (unsigned char*)&m_ulCmdNumber;
      sprintf(pcTag, "test_spec.%02x%02x", pucCmdNumber[1], pucCmdNumber[0]);

      if( NTIL_SendCommandByRtp(nLineId, pcTag, pucData, true) >= 0 )
      {
        bReturn = true;
      }
    }
  }

  return bReturn;
}

void TestLoop(int nLineId)
{
  while( GetLinkStatus( nLineId ) != LINK_STATUS::UNLINKED )
  {
    MessageHandler();
    DataHandler();
  }
}
