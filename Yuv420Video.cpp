#include <iostream>
#include <fstream>
#include <algorithm>

#include "Yuv420Video.h"

Yuv420Video::Yuv420Video(const std::string &name, std::pair<unsigned int, unsigned int> &resolution)
    :  name_(name)
{
    setSize(resolution.first, resolution.second);
    bytesPerFrame_ = static_cast<unsigned int>(width() * height() * 1.5);
    framesNumber_ = static_cast<unsigned int>(fileSize() / bytesPerFrame_);
    data_.resize(bytesPerFrame_);
}

long Yuv420Video::fileSize()
{
    long fileSize;

    std::ifstream stream(name_, std::ios::binary);
    if(!stream)
    {
        std::cerr << "ERROR: Could not open file " << name_ << "for reading." << std::endl;
        exit(1);
    }

    stream.seekg(0, stream.end);
    fileSize = stream.tellg();
    stream.close();

    return fileSize;
}

void Yuv420Video::setYuv420Image(const Yuv420Image &image)
{
    yuvImage_ = image;
}

void Yuv420Video::saveOnDisk(const std::string &name)
{
    for(unsigned int frameNumber = 0; frameNumber < framesNumber_; frameNumber++)
    {
        std::ifstream stream(name_, std::ios::binary);
        if(!stream)
        {
            std::cerr << "ERROR: Could not open file " << name << "for reading." << std::endl;
            exit(1);
        }

        stream.seekg(frameNumber * bytesPerFrame_, stream.beg);

        auto *data = &data_[0];
        stream.read(reinterpret_cast<char *>(data), bytesPerFrame_);
        if(!stream)
        {
            std::cerr << "ERROR: Could not read file " << name << "." << std::endl;
            exit(1);
        }

        stream.close();

        overlayImageOnFrame();
        Yuv420Image::saveOnDisk(name);
    }
}

void Yuv420Video::overlayPlane(PLANE plane)
{
    std::vector<unsigned char>::const_iterator imageIter;
    std::vector<unsigned char>::iterator frameIter;
    unsigned int scaleSize;

    switch(plane)
    {
    case PLANE::Y:
        imageIter = yuvImage_.data().cbegin();
        frameIter = data_.begin();
        scaleSize = 1;
        break;
    case PLANE::Cb:
        imageIter = yuvImage_.data().cbegin() + yuvImage_.height() * yuvImage_.width();
        frameIter = data_.begin() + height() * width();
        scaleSize = 2;
        break;
    case PLANE::Cr:
        imageIter = yuvImage_.data().cbegin() +  5 * yuvImage_.height() * yuvImage_.width() / 4;
        frameIter = data_.begin() + 5 * height() * width() / 4;
        scaleSize = 2;
    }

    for(unsigned int i = 0; i < yuvImage_.height() / scaleSize; i++)
    {
        std::copy(imageIter, imageIter + yuvImage_.width() / scaleSize, frameIter);

        imageIter += yuvImage_.width() / scaleSize;
        frameIter += width() / scaleSize;
    }
}

void Yuv420Video::overlayImageOnFrame()
{
    overlayPlane(PLANE::Y);
    overlayPlane(PLANE::Cb);
    overlayPlane(PLANE::Cr);
}















