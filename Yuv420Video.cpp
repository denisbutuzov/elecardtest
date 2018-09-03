#include <iostream>
#include <fstream>

#include "Yuv420Video.h"

YuvVideo::YuvVideo(const std::string &name)
{
    std::ifstream stream(name, std::ios::binary);
    if(!stream)
    {
        std::cerr << "ERROR: Could not open file " << name << "for reading." << std::endl;
        exit(1);
    }

}