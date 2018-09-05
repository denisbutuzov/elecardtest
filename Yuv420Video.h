#pragma once

#include "Yuv420Image.h"

class Yuv420Video
        : public Yuv420Image
{
public:
    Yuv420Video(const std::string &fileName, std::pair<unsigned int, unsigned int> &resolution);
    void setYuv420Image(const Yuv420Image &image);
    void saveOnDisk(const std::string &fileName) override final;
private:
    enum class PLANE { Y, Cb, Cr };
    virtual void load(const std::string &fileName) override final;
    void overlayPlane(PLANE plane);
    void overlayImageOnFrame();
private:
    std::string fileName_;
    unsigned int bytesPerFrame_;
    unsigned int framesNumber_;
    Yuv420Image yuvImage_;
};
