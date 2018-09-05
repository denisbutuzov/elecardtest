#pragma once

#include <string>
#include <vector>

class AbstractImage
{
public:
    virtual ~AbstractImage() = default;
    void setSize(unsigned int width, unsigned int height);
    const std::vector<unsigned char> &data() const;
    unsigned int width() const;
    unsigned int height() const;
private:
    virtual void load(const std::string &fileName) = 0;
protected:
    void fileSize(const std::string &fileName);
protected:
    std::vector<unsigned char> data_;
    unsigned int width_;
    unsigned int height_;
    long fileSize_;
};
