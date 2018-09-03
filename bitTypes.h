#pragma once

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

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
