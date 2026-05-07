// client.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "client.h"

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#if defined(__linux__) && defined(__GNUC__) && (__GNUC__ < 11)
namespace std {
    void __throw_bad_array_new_length() {
        abort();
    }
}
#endif

#define NAME_DEVICE (char*)"O7XU-4WOP"

constexpr uint32_t cfg_i_num = 1;
constexpr uint32_t cfg_p_num = 15;

extern const uint32_t cfg_frames;
const uint32_t cfg_frames = cfg_i_num + cfg_p_num;

extern const uint32_t cfg_gops;
const uint32_t cfg_gops = 50;

const char* msg_template =
R"(
{
  "frame": {
    "I": {
      "size": 131072,
      "num": %d,
      "interval": 4
    },
    "P": {
      "size": 16384,
      "num": %d,
      "interval": 1
    }
  },
  "num": %d,
  "ip" : 1,
  "ack": 0
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

  sprintf( msg_json, msg_template, cfg_i_num, cfg_p_num, cfg_gops);
  if( true == SendTestCommand( m_nLineID, msg_json, strlen(msg_json)) )
  {
    MainLoop( m_nLineID );
  }
  else
  {
    printf(" >> [FAIL] SendTestCommand\n");
  }

  Disconnect( m_nLineID );

  return 0;
}
