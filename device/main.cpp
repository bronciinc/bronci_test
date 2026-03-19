#include <string>

#define STRING_UID          "O7XU-4WOP@webgateinc.iptnet.net"
#define STRING_PW           "eeBQVNGwD9"

int childmain(std::pair<std::string, std::string> u);

int main(int argc, char *argv[])
{
    std::pair<std::string, std::string> login( STRING_UID, STRING_PW);

	childmain( login );
}
