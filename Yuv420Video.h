#pragma once

#include "Yuv420Image.h"

class Yuv420Video: public Yuv420Image
{
public:
    Yuv420Video(const std::string &name, std::pair<int, int> &resolution);
    long fileSize();
    void setYuv420Image(const Yuv420Image &image);
    void saveOnDisk(const std::string &name);
private:
    void overlayImageOnFrame();

    std::string name_;
    unsigned int bytesPerFrame_;
    unsigned int framesNumber_;
    Yuv420Image yuvImage_;
};
