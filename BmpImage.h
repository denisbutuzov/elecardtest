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

};

class BmpImage
{
public:
    BmpImage(std::string name) {}
    std::string fileSize() const;
private:
    std::ifstream file_;
    BITMAPFILEHEADER bmp_;
    BITMAPINFOHEADER info_;
};
