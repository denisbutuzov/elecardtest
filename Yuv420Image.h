#pragma once

#include <vector>
#include <string>

class Yuv420Image
{
public:
    Yuv420Image() = default;
    Yuv420Image(std::vector<unsigned char> &data);
    void setSize(unsigned int width, unsigned int height);
    void saveOnDisk(const std::string &name) const;
    unsigned int width() const;
    unsigned int height() const;
    const std::vector<unsigned char> &data() const;
protected:
    std::vector<unsigned char> data_;
private:
    unsigned int width_;
    unsigned int height_;
};
