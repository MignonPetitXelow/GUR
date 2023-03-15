#include "ImgText.h"

ImgText::ImgText(){}

char* ImgText::convertToASCII(const char* dd)
{
    FILE *fptr;
    char filename[] = "test.jpg";
    unsigned char header[54];
    unsigned int width, height; //cc venodez <3
    unsigned char *image = NULL;
    int r,g,b,grey;
    char *ascii_image = NULL;
    char ascii_char[] = "$@B%8&WM#*oahkbdpwmZO0Q$L>!:-. ";

    fptr = fopen(filename, "rb");
    if (fptr == NULL) { std::cerr << "🚫 → Could not open file: " << filename << std::endl; return ""; }

    fread(header, sizeof(unsigned char), 54, fptr);
    width = *(int*)&(header[18]);
    height = *(int*)&(header[22]);
    image = (unsigned char*)malloc(3 * width * height);
    if (!image) { std::cerr << "🚫 → Failed to allocate memory for the image" << std::endl; return ""; }
    fread(image, sizeof(unsigned char), 3 * width * height, fptr);
    fclose(fptr);
    std::cout << "widht= " << width << " height= " << height << std::endl;

    ascii_image = (char*)malloc((width + 1) * height * sizeof(char));
    for (long i = 0; i < height; ++i)
    {
        for(long j = 0; j < width; ++j)
        {
            r = image[(i * width + j) * 3 + 2];
            g = image[(i * width + j) * 3 + 1];
            b = image[(i * width + j) * 3];
            grey = (int)(0.2126 * r + 0.7152 * g + 0.0722 * b);
            int index = (int)(grey / 256.0 * sizeof(ascii_char));
            if (index < 0 || index >= sizeof(ascii_char)) { std::cerr << "🚫 → Invalid index for ascii_char: " << index << std::endl; return NULL; }
            ascii_image[i * (width + 1) + j] = ascii_char[index];
        }
        ascii_image[i * (width + 1) + width] = '\n';
    }
    if (!ascii_image) { std::cerr << "🚫 → Failed to allocate memory for the ASCII image" << std::endl; return NULL; }
    
    fptr = fopen("ascii.txt", "w");
    if (fptr == NULL) { std::cout << "🚫 → Error opening file.\n" << std::endl; return NULL; }

    fprintf(fptr, "%s", ascii_image);
    fclose(fptr);

    std::cout << "📝 → Conversion of the image [\"" << filename << "\"] has been finished" << std::endl;
    return ascii_image;
}