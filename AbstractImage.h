#pragma once

class AbstractImage
{
public:
    virtual ~AbstractImage() = default;
    virtual void load() = 0;

private:
    unsigned int width_;
    unsigned int height_;
};
