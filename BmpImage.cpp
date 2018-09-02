#include <iostream>

#include "BmpImage.h"

BmpImage::BmpImage(const std::string &name)
{
    std::ifstream stream(name, std::ios::binary);
    if(!stream)
    {
        std::cerr << "ERROR: Could not open file " << name << "for reading." << std::endl;
        exit(1);
    }

    stream.read(reinterpret_cast<char *>(&bmp_), sizeof(BITMAPFILEHEADER));
    stream.read(reinterpret_cast<char *>(&info_), sizeof(BITMAPINFOHEADER));
    if(!stream)
    {
        std::cerr << "ERROR: Could not read file " << name << "." << std::endl;
        exit(1);
    }

    if(bmp_.type != 19778)
    {
        std::cerr << "ERROR: Invalid type value of file " << bmp_.type << ". Expected 19778." << std::endl;
        exit(1);
    }

    if(info_.bitsPerPixel != 24)
    {
        std::cerr << "ERROR: Invalid bit deph " << info_.bitsPerPixel << ". Expected 24." << std::endl;
        exit(1);
    }

    createBitmap(stream);

    stream.close();
}

void BmpImage::createBitmap(std::ifstream &stream)
{
    unsigned char bytesPerPixel = static_cast<unsigned char>(info_.bitsPerPixel / 8);
    bytesPerRow_ = info_.width * bytesPerPixel;
    data_.resize(info_.height * bytesPerRow_);

    unsigned int padding = (4 - (bytesPerRow_ % 4)) % 4;
    char padding_data[4] = { 0, 0, 0, 0 };

    for(unsigned int i = 0; i < info_.height; i++)
    {
        auto data = &data_[(i * bytesPerRow_)];

        stream.read(reinterpret_cast<char *>(data), sizeof(BYTE) * bytesPerRow_);
        stream.read(padding_data, padding);
    }
}

void BmpImage::rgbToYuv()
{
    for (auto iter = data_.begin(); iter < data_.end(); )
    {
        auto blue = iter++;
        auto green = iter++;
        auto red = iter++;

        double y = 16.0 + (65.481 * (*red) + 128.553 * (*green) + 24.966 * (*blue)) / 256.0 ;
        double cb = 128.0 + (-37.797 * (*red) + (-74.203) * (*green) + 112.000 * (*blue)) / 256.0;
        double cr = 128.0 + (112.000 * (*red) + (-93.786) * (*green) - 18.214 * (*blue)) / 256.0;

        (*blue) = static_cast<BYTE>(y);
        (*green) = static_cast<BYTE>(cb);
        (*red) = static_cast<BYTE>(cr);
    }
}

void BmpImage::saveImage(const std::string &name) const
{
    std::ofstream stream(name, std::ios::binary);
    if (!stream)
    {
        std::cerr << "ERROR: Could not open file " << name << " for writing!" << std::endl;
        exit(1);
    }

    stream.write(reinterpret_cast<const char *>(&bmp_), sizeof(BITMAPFILEHEADER));
    stream.write(reinterpret_cast<const char *>(&info_), sizeof(BITMAPINFOHEADER));

    unsigned int padding = (4 - (bytesPerRow_ % 4)) % 4;
    char padding_data[4] = { 0, 0, 0, 0 };

    for (unsigned int i = 0; i < info_.height; ++i)
    {
        const auto data = &data_[(i * bytesPerRow_)];

        stream.write(reinterpret_cast<const char*>(data), sizeof(BYTE) * bytesPerRow_);
        stream.write(padding_data, padding);
    }

    stream.close();
}

std::vector<BYTE> BmpImage::yuvData() const
{
    std::vector<BYTE> yuv_data;

    for(auto iter = data_.cbegin(); iter < data_.cend(); )
    {
        auto blue = iter++;
        auto green = iter++;
        auto red = iter++;

        double y = 16.0 + (65.481 * (*red) + 128.553 * (*green) + 24.966 * (*blue)) / 256.0 ;

        yuv_data.push_back(static_cast<BYTE>(y));
    }

    std::vector<double> cb_data(4);
    for(auto iter = data_.cbegin(); iter < data_.cend(); )
    {
        auto blue = iter++;
        auto green = iter++;
        auto red = iter++;

        cb_data[0] = 128.0 + (-37.797 * (*red) + (-74.203) * (*green) + 112.000 * (*blue)) / 256.0;

        blue = iter++;
        green = iter++;
        red = iter++;

        cb_data[1] = 128.0 + (-37.797 * (*red) + (-74.203) * (*green) + 112.000 * (*blue)) / 256.0;

        iter += info_.width - 2;
        blue = iter++;
        green = iter++;
        red = iter++;

        cb_data[2] = 128.0 + (-37.797 * (*red) + (-74.203) * (*green) + 112.000 * (*blue)) / 256.0;

        blue = iter++;
        green = iter++;
        red = iter++;

        cb_data[3] = 128.0 + (-37.797 * (*red) + (-74.203) * (*green) + 112.000 * (*blue)) / 256.0;

        iter -= info_.width;

        double cb = (cb_data[0] + cb_data[1] + cb_data[2] + cb_data[3]) / 4;

        yuv_data.push_back(static_cast<BYTE>(cb));
    }

    std::vector<double> cr_data(4);
    for(auto iter = data_.cbegin(); iter < data_.cend(); )
    {
        auto blue = iter++;
        auto green = iter++;
        auto red = iter++;

        cr_data[0] = 128.0 + (112.000 * (*red) + (-93.786) * (*green) - 18.214 * (*blue)) / 256.0;

        blue = iter++;
        green = iter++;
        red = iter++;

        cr_data[1] = 128.0 + (112.000 * (*red) + (-93.786) * (*green) - 18.214 * (*blue)) / 256.0;

        iter += info_.width - 2;
        blue = iter++;
        green = iter++;
        red = iter++;

        cr_data[2] = 128.0 + (112.000 * (*red) + (-93.786) * (*green) - 18.214 * (*blue)) / 256.0;

        blue = iter++;
        green = iter++;
        red = iter++;

        cr_data[3] = 128.0 + (112.000 * (*red) + (-93.786) * (*green) - 18.214 * (*blue)) / 256.0;

        iter -= info_.width;

        double cr = (cr_data[0] + cr_data[1] + cr_data[2] + cr_data[3]) / 4;

        yuv_data.push_back(static_cast<BYTE>(cr));
    }

    return yuv_data;
}

