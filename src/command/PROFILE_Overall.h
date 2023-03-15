#ifndef PROFILE_OVERALL_H
#define PROFILE_OVERALL_H

#include <string>
#include <vector>
#include "../utils/ImgText.h"
#include "../request/API_Callback.h"
#include <iostream>

class PROFILE_Overall 
{
    public:
        PROFILE_Overall();
        void sendOverall(std::string uuid);
};

#endif