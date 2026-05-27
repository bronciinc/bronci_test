// client.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "client.h"
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

extern const uint32_t cfg_gops;
const uint32_t cfg_gops = 1;

#if 0
// Small P frame
const char* msg_template =
R"(
{
  "frame": {
    "I": {
      "size": 132000,
      "num": 1,
      "interval": 10
    },
    "P": {
      "size": 13200,
      "num": 29,
      "interval": 29
    }
  },
  "num": %d
}
)";
#else
// Big P frame
const char* msg_template =
R"(
{
  "frame": {
    "I": {
      "size": 132000,
      "num": 1,
      "interval": 10
    },
    "P": {
      "size": 132000,
      "num": 29,
      "interval": 29
    }
  },
  "num": %d
}
)";
#endif

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
