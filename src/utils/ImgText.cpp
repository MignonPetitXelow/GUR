#include "ImgText.h"

ImgText::ImgText(){}

std::string ImgText::convertToASCII(const char* dd)
{
    const char* filename = "test.jpg";
    std::ifstream file(filename, std::ios::binary);
    if(!file)
    {
        std::cout << "File not found" << std::endl;
        return NULL;
    }

    std::vector<unsigned char> header(2);
    file.read((char*)&header[0], header.size());
    if(header[0] != 0xFF || header[1] != 0xD8)
    {
        std::cout << "Not an image" << std::endl;
        return NULL;
    }

    while(true)
    {
        std::cout << "🔁 → Starting while(true)" << std::endl;
        file.read((char*)&header[0], header.size());
        if (header[0] != 0xFF)
        {
            std::cout << "💔 → Invalid JPEG marker" << std::endl;
            return NULL;
        }
        if (header[1] == 0xD9)
        {
            std::cout << "🕳️ → End of JPEG file" << std::endl;
            return NULL;
        }
        if (header[1] == 0xC0)
        {
            break;
        }
        int length = (header[2] << 8) | header[3];
        file.seekg(length - 2, std::ios::cur);
        break;
    }

    std::vector<unsigned char> dimesions(5);
    file.read((char*)&dimesions[0], dimesions.size());
    int width = (dimesions[1] << 8) | dimesions[2];
    int height = (dimesions[3] << 8) | dimesions[4];
    std::cout << "🗺️ → [width=" << width << "] [height=" << height << "]"<< std::endl;
    std::vector<unsigned char> data;
    while(true)
    {
        std::cout << "🔁 → Starting second while(true)" << std::endl;
        file.read((char*)&header[0], header.size());
        if (header[0] != 0xFF)
        {
            std::cout << "🚫 → Invalid JPEG marker" << std::endl;
            return NULL;
        }
        if (header[1] == 0xC4 || header[1] == 0xDB || header[1] == 0xDD)
        {
            int length = (header[2] << 8) | header[3];
            data.resize(data.size() + length - 2);
            file.read((char*)&data[data.size() - length + 2], length - 2);
            break;
        }
        else if (header[1] == 0xDA)
        {
            break;
        }
        else
        {
            int length = (header[2] << 8) | header[3];
            file.seekg(length - 2, std::ios::cur);
            break;
        }
    }

    std::vector<unsigned char> image_data(width * height * 3);
    int x = 0, y = 0;
    int r,g,b,grey;
    for(size_t i = 0; i < data.size(); ++i)
    {
        std::cout <<i+1<<"/"<<data.size() << "🧪 → Grey map" << std::endl;
        if(data[i] == 0xFF && data[i+1] != 0x00)
        {
            ++i;
            continue;
        }

        r = image_data[(y * width + x) * 3 + 0];
        g = image_data[(y * width + x) * 3 + 1];
        b = image_data[(y * width + x) * 3 + 2];
        grey = 0.2126 * r + 0.7152 * g + 0.0722 * b;

        if (grey < 30)
        {
            std::cout << "@";
        }
        else if (grey < 70)
        {
            std::cout << "#";
        }
        else if (grey < 110)
        {
            std::cout << "8";
        }
        else if (grey < 150)
        {
            std::cout << "&";
        }
        else if (grey < 190)
        {
            std::cout << "o";
        }
        else if (grey < 230)
        {
            std::cout << ":";
        }
        else
        {
            std::cout << ".";
        }

        ++x;
        if (x == width)
        {
            x = 0;
            ++y;
            std::cout << std::endl;
        }
    }
}