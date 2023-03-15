#include "API_Callback.h"

API_Callback::API_Callback() {}

size_t API_Callback::write_callback(char *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

/**
 * @brief Api_callback::Api_callback
 * @param uid using uid to get user information
 * @param path get information from the path (e.g. /playerInfo/nickname)
*/
std::string API_Callback::API_CALL(std::string uid, std::string path)
{
    StringSplit __1;
    std::vector<std::string> split = __1.StrPlit__(path, '/');
    std::ostringstream url;
    url << "https://enka.network/api/uid/" << uid;

    CURL *curl = curl_easy_init();
    if (!curl) { std::cerr << "⚠️ → curl_easy_init() failed" << std::endl; return ""; }

    curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    std::string response_data;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &API_Callback::write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) { std::cerr << "⚠️ → curl_easy_perform() failed" << std::endl; return ""; }

    curl_easy_cleanup(curl);

    Json::Value root;
    Json::Reader reader;

    bool parsingSuccessful = reader.parse(response_data, root);
    if (!parsingSuccessful) { std::cerr << "⚠️ → reader.parse() failed" << std::endl; return ""; }

    std::string obj;
    try
    {
        std::cout << "👀 → Looking for value from /uid/../" << split[split.size()-1] << std::endl;
        Json::Value x = root;
        for(int i = 0; i < split.size(); i++)
        {
            x = x[split[i]];
        }
        obj = x.asString();
    }
    catch(std::exception& e) { std::cerr << "🚫 → " << e.what() << std::endl; return ""; }
    
    std::cout << "✅ → Value found from /" << split[split.size()-1] << " [\"" << obj << "\"]"<<std::endl;
    return obj;
}