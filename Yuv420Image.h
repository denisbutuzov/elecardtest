#pragma once

#include <vector>
#include <string>

#include "bitmapTypes.h"

class Yuv420Image
{
public:
    Yuv420Image(std::vector<BYTE> &data);
    void saveImage(const std::string &name) const;
private:
    std::vector<BYTE> data_;
};
