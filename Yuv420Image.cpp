#include <iostream>

#include "FstreamWrapper.h"
#include "Yuv420Image.h"

Yuv420Image::Yuv420Image(std::vector<unsigned char> &data)
{
    data_ = data;
}

void Yuv420Image::saveOnDisk(const std::string &name)
{
    FstreamWrapper stream(name, std::ios::binary | std::ios::app);

    for (unsigned int i = 0; i < data_.size(); i++)
    {
        const auto *data = &data_[i];
        stream.write(reinterpret_cast<const char *>(data), sizeof(unsigned char));
    }

    stream.close();
}

void Yuv420Image::load(const std::string &fileName)
{
    std::cerr << "There must be a code for load Yuv420Image." << std::endl;
    exit(1);
}


