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
    class Yuv420Image &Yuv420Image();
private:
    void createBitmap(std::ifstream &stream);

    BITMAPFILEHEADER bmp_;
    BITMAPINFOHEADER info_;
    std::vector<BYTE> data_;
    class Yuv420Image *yuvImage_;
};
