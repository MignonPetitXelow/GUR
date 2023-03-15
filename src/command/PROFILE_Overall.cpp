#include "PROFILE_Overall.h"

PROFILE_Overall::PROFILE_Overall() {}

void PROFILE_Overall::sendOverall(std::string uuid) {
    ImgText imgText;
    API_Callback __apicll;

    char* image = imgText.convertToASCII("test.jpg");
    std::string name = __apicll.API_CALL(uuid, "playerInfo/nickname");
    std::string signature = __apicll.API_CALL(uuid, "playerInfo/signature");
    std::string level = __apicll.API_CALL(uuid, "playerInfo/level");
    std::string worldLevel = __apicll.API_CALL(uuid, "playerInfo/worldLevel");
    std::string achievement = __apicll.API_CALL(uuid, "playerInfo/finishAchievementNum");
    std::cout << image << std::endl << std::endl;
    std::cout <<
        "   Name        > " << name << std::endl <<
        "   Signature   > " << signature << std::endl <<
        "   Level       > " << level << std::endl <<
        "   World Level > " << worldLevel << std::endl <<
        "   Achievement > " << achievement << std::endl;
    
    return 0;
}