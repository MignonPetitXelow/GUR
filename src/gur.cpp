#include "request/API_Callback.h"
#include "command/PROFILE_Overall.h"

std::string UID;
std::string PATH = "playerInfo/nickname";

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "🚫 → Usage: " << argv[0] << " <uid> [path] [--overall]" << std::endl;
        return 0;
    }
    UID = argv[1];
    if(argc == 3)
    {
            PATH = argv[2];
            API_Callback __apicll;
            __apicll.API_CALL(UID, PATH);
    }
    if(argc == 2)
    {
        PROFILE_Overall overall;
        overall.sendOverall(argv[1]);
    }
    return 0;
}
