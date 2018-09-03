#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "bitmapTypes.h"
#include "Yuv420Image.h"

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
