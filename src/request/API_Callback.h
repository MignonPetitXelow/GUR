#ifndef API_CALLBACK_H
#define API_CALLBACK_H

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "../utils/StringSplit.h"

class API_Callback 
{
    public:
        API_Callback();
        std::string API_CALL(std::string uid, std::string path);
        static size_t write_callback(char *ptr, size_t size, size_t nmemb, std::string *data);
};

#endif 