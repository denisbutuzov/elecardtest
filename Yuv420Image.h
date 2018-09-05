#pragma once

#include "AbstractImage.h"

class Yuv420Image
        : public AbstractImage
{
public:
    Yuv420Image() = default;
    Yuv420Image(std::vector<unsigned char> &data);
    virtual void saveOnDisk(const std::string &fileName);
private:
    virtual void load(const std::string &fileName) override;
};
