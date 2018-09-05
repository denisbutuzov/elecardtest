#include "FstreamWrapper.h"
#include "AbstractImage.h"

void AbstractImage::setSize(unsigned int width, unsigned int height)
{
    width_ = width;
    height_ = height;
}

const std::vector<unsigned char> &AbstractImage::data() const
{
    return data_;
}

unsigned int AbstractImage::width() const
{
    return width_;
}

unsigned int AbstractImage::height() const
{
    return height_;
}

void AbstractImage::fileSize(const std::string &fileName)
{
    FstreamWrapper stream(fileName, std::ios::binary | std::ios::in);

    stream.seekg(0, stream.end);
    fileSize_ = stream.tellg();
    stream.close();
}
