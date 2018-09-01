#include <iostream>

#include "BmpImage.h"

BmpImage::BmpImage(std::string name)
{
    file_.open(name, std::ios::binary);
    if(!file_)
    {
        std::cerr << "Can not open file " << name << std::endl;
        exit(1);
    }

    file_.read(reinterpret_cast<char *>(&bmp_), sizeof(BITMAPFILEHEADER));
    if(!file_)
    {
        std::cerr << "Can not read file " << name << std::endl;
        exit(1);
    }
}

DWORD BmpImage::fileSize() const
{
    return bmp_.fileSize;
}
