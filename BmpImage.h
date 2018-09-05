#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Yuv420Image.h"

class BmpImage
{
public:
    BmpImage(const std::string &name);
    class Yuv420Image &Yuv420Image();
private:
    enum class PLANE { Cb, Cr };
    void createBitmap(std::ifstream &stream);
    void YPlane(std::vector<unsigned char> &vec);
    void CbCrPlane(std::vector<unsigned char> &vec, PLANE plane);
private:
    std::vector<unsigned char> data_;
    class Yuv420Image *yuvImage_;

    struct BITMAPFILEHEADER
    {
         unsigned short type;
         unsigned int   fileSize;
         unsigned short reserved1;
         unsigned short reserved2;
         unsigned int   pixelOffset;
    } __attribute__ ((__packed__)) bmp_;

    struct BITMAPINFOHEADER
    {
        unsigned int    size;
        unsigned int    width;
        unsigned int    height;
        unsigned short  planes;
        unsigned short  bitsPerPixel;
        unsigned int    compression;
        unsigned int    imageSize;
        unsigned int    x_pixelsPerMeter;
        unsigned int    y_pixelsPerMeter;
        unsigned int    clr_used;
        unsigned int    clr_important;
    } info_;
};
