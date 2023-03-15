#include "StringSplit.h"


StringSplit::StringSplit() {};

std::vector<std::string> StringSplit::StrPlit__(std::string str, char delimiter)
{
    std::vector<std::string> result;
    std::string item;

    for (char c : str)
    {
        if (c == delimiter) 
        {
            if (!item.empty()) 
            {
                result.push_back(item);
                item.clear();
            }
        } else 
        {
            item += c;
        }
    }

    if (!item.empty()) 
    {
        result.push_back(item);
    }

    return result;
}