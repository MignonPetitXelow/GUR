#ifndef IMGTEXT_H
#define IMGTEXT_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

class ImgText
{
    public:
        ImgText();
        char* convertToASCII(const char* path);
};

#endif 