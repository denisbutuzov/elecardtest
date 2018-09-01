#include <iostream>

#include "BmpImage.h"

BmpImage::BmpImage(std::string name)
{
    file_.open(name, std::ios::binary);
    if(!file_)
    {
        std::cerr << "ERROR: Can not open file " << name << "." << std::endl;
        exit(1);
    }

    file_.read(reinterpret_cast<char *>(&bmp_), sizeof(BITMAPFILEHEADER));
    file_.read(reinterpret_cast<char *>(&info_), sizeof(BITMAPINFOHEADER));
    if(!file_)
    {
        std::cerr << "ERROR: Can not read file " << name << "." << std::endl;
        exit(1);
    }

    if(bmp_.type != 19778)
    {
        std::cerr << "ERROR: Invalid type value of file " << bmp_.type << ". Expected 19778." << std::endl;
    }

    if(info_.bitsPerPixel != 24)
    {
        std::cerr << "ERROR: Invalid bit deph " << info_.bitsPerPixel << ". Expected 24." << std::endl;
        exit(1);
    }

    file_.close();
}
