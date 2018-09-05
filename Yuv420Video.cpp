#include <iostream>
#include <algorithm>
#include <thread>

#include "FstreamWrapper.h"
#include "Yuv420Video.h"

Yuv420Video::Yuv420Video(const std::string &fileName, std::pair<unsigned int, unsigned int> &resolution)
    :  fileName_(fileName)
{
    setSize(resolution.first, resolution.second);
    fileSize(fileName);
    bytesPerFrame_ = static_cast<unsigned int>(width_ * height_ * 1.5);
    framesNumber_ = static_cast<unsigned int>(fileSize_ / bytesPerFrame_);
    data_.resize(bytesPerFrame_);
}

void Yuv420Video::setYuv420Image(const Yuv420Image &image)
{
    yuvImage_ = image;
}

void Yuv420Video::saveOnDisk(const std::string &fileName)
{
    for(unsigned int frameNumber = 0; frameNumber < framesNumber_; frameNumber++)
    {
        FstreamWrapper stream(fileName_, std::ios::binary | std::ios::in);

        stream.seekg(frameNumber * bytesPerFrame_, stream.beg);

        auto *data = &data_[0];

        stream.read(reinterpret_cast<char *>(data), bytesPerFrame_);
        stream.close();

        overlayImageOnFrame();
        Yuv420Image::saveOnDisk(fileName);
    }
}

void Yuv420Video::load(const std::string &fileName)
{
    std::cerr << "There must be a code for load Yuv420Video." << std::endl;
    exit(1);
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
    std::thread th2([&]() { this->overlayPlane(PLANE::Cb); });
    std::thread th3([&]() { this->overlayPlane(PLANE::Cr); });
    overlayPlane(PLANE::Y);

    th2.join();
    th3.join();
}















