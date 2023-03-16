#ifndef IMGTEXT_H
#define IMGTEXT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class ImgText
{
    public:
        ImgText();
        std::string convertToASCII(const char* path);
};

#endif 