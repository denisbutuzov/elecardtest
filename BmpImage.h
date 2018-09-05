#pragma once

#include "AbstractImage.h"
#include "Yuv420Image.h"
#include "FstreamWrapper.h"

class BmpImage
        : AbstractImage
{
public:
    BmpImage(const std::string &fileName);
    class Yuv420Image &Yuv420Image();
private:
    enum class PLANE { Cb, Cr };
    virtual void load(const std::string &fileName) override final;
    void readImageData(FstreamWrapper &stream);
    void YPlane(std::vector<unsigned char> &vec);
    void CbCrPlane(std::vector<unsigned char> &vec, PLANE plane);
private:
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
