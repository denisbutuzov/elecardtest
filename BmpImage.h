#pragma once

#include <string>
#include <fstream>

#include "bitTypes.h"

#pragma pack(push, 1)
struct BITMAPFILEHEADER
{
     WORD signature;
     DWORD fileSize;
     WORD reserved1;
     WORD reserved2;
     DWORD pixelOffset;
};
#pragma pack(pop)

struct BITMAPINFOHEADER
{
    DWORD dibHeaderSize;
    DWORD imageWidth;
    DWORD imageHeight;
};

class BmpImage
{
public:
    BmpImage(std::string name);
private:
    std::ifstream file_;
    BITMAPFILEHEADER bmp_;
    BITMAPINFOHEADER info_;
};
