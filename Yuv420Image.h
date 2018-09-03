#pragma once

#include <vector>
#include <string>

#include "bitmapTypes.h"

class Yuv420Image
{
public:
    Yuv420Image() = default;
    Yuv420Image(std::vector<BYTE> &data);
    void setSize(int width, int height);
    void saveOnDisk(const std::string &name) const;
    int width() const;
    int height() const;
    const std::vector<BYTE> &data() const;
protected:
    std::vector<BYTE> data_;
private:
    int width_;
    int height_;
};
