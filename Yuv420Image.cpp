#include <fstream>
#include <iostream>

#include "Yuv420Image.h"

Yuv420Image::Yuv420Image(std::vector<BYTE> &data)
    : data_(data)
{

}

void Yuv420Image::saveImage(const std::string &name) const
{
    std::ofstream stream(name, std::ios::binary);
    if (!stream)
    {
        std::cerr << "ERROR: Could not open file " << name << " for writing!" << std::endl;
        exit(1);
    }

    for (unsigned int i = 0; i < data_.size(); i++)
    {
        const auto data = &data_[i];

        stream.write(reinterpret_cast<const char*>(data), sizeof(BYTE));
    }

    stream.close();
}
