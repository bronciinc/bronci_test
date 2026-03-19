// client.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "client.h"

#define NAME_DEVICE (char*)"O7XU-4WOP"

extern const uint32_t cfg_gops;
const uint32_t cfg_gops = 50;

const char* msg_template =
R"(
{
  "frame": {
    "I": {
      "size": 262144,
      "num": 1,
      "interval": 10
    },
    "P": {
      "size": 12288,
      "num": 29,
      "interval": 10
    }
  },
  "num": %d
}
)";

int main()
{
  int m_nLineID;
  char msg_json[512];

  Initialize();

  if( false == Connect( NAME_DEVICE, &m_nLineID) )
  {
    printf(" >> [FAIL] Connection\n");
    exit(1);
  }

  sprintf( msg_json, msg_template, cfg_gops);
  if( true == SendTestCommand( m_nLineID, msg_json, strlen(msg_json)) )
  {
    TestLoop( m_nLineID );
  }
  else
  {
    printf(" >> [FAIL] SendTestCommand\n");
  }

  Disconnect( m_nLineID );

  return 0;
}
