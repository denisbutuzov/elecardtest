#pragma once

#include <string>
#include <fstream>

#include "bitTypes.h"

#pragma pack(push, 1)
struct BITMAPFILEHEADER
{
     WORD type;
     DWORD fileSize;
     WORD reserved1;
     WORD reserved2;
     DWORD pixelOffset;
};
#pragma pack(pop)

struct BITMAPINFOHEADER
{
    DWORD size;
    DWORD width;
    DWORD height;
    WORD planes;
    WORD bitsPerPixel;
    DWORD compression;
    DWORD imageSize;
};

class BmpImage
{
public:
    BmpImage(const std::string &name);
private:
    BITMAPFILEHEADER bmp_;
    BITMAPINFOHEADER info_;
};
