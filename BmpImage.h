#pragma once

#include <string>
#include <fstream>

#include "bitTypes.h"

struct BITMAPFILEHEADER
{
     WORD signature;
     DWORD fileSize;
     WORD reserved1;
     WORD reserved2;
     DWORD pixelOffset;
};

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
    DWORD fileSize() const;
    DWORD width() const;
    DWORD height() const;
private:
    std::ifstream file_;
    BITMAPFILEHEADER bmp_;
    BITMAPINFOHEADER info_;
};
