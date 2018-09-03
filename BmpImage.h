#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "bitTypes.h"
#include "Yuv420Image.h"

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
    DWORD x_pixelsPerMeter;
    DWORD y_pixelsPerMeter;
    DWORD clr_used;
    DWORD clr_important;
};

class BmpImage
{
public:
    BmpImage(const std::string &name);
    Yuv420Image &toYuv420Image();
private:
    void createBitmap(std::ifstream &stream);

    BITMAPFILEHEADER bmp_;
    BITMAPINFOHEADER info_;
    std::vector<BYTE> data_;
    unsigned int bytesPerRow_;

    Yuv420Image *yuvImage_;
};
