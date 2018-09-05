#include <iostream>
#include <thread>

#include "BmpImage.h"

BmpImage::BmpImage(const std::string &fileName)
{
    load(fileName);
}

void BmpImage::load(const std::string &fileName)
{
    FstreamWrapper stream(fileName, std::ios::binary | std::ios::in);

    stream.read(reinterpret_cast<char *>(&bmp_), sizeof(BITMAPFILEHEADER));
    stream.read(reinterpret_cast<char *>(&info_), sizeof(BITMAPINFOHEADER));

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

    setSize(info_.width, info_.height);
    readImageData(stream);

    stream.close();
}

void BmpImage::readImageData(FstreamWrapper &stream)
{
    unsigned char bytesPerPixel = static_cast<unsigned char>(info_.bitsPerPixel / 8);
    unsigned int bytesPerRow = info_.width * bytesPerPixel;
    data_.resize(info_.height * bytesPerRow);

    unsigned int padding = (4 - (bytesPerRow % 4)) % 4;
    char padding_data[4] = { 0, 0, 0, 0 };

    unsigned int i = info_.height - 1;

    do
    {
        auto *data = &data_[(i * bytesPerRow)];

        stream.read(reinterpret_cast<char *>(data), sizeof(unsigned char) * bytesPerRow);
        stream.read(padding_data, padding);
    } while(--i != 0);
}

void BmpImage::YPlane(std::vector<unsigned char> &vec)
{
    for(auto iter = data_.cbegin(); iter < data_.cend(); )
    {
        auto blue = iter++;
        auto green = iter++;
        auto red = iter++;

        double y = 16.0 + (65.481 * (*red) + 128.553 * (*green) + 24.966 * (*blue)) / 256.0;

        vec.push_back(static_cast<unsigned char>(y));
    }
}

void BmpImage::CbCrPlane(std::vector<unsigned char> &vec, BmpImage::PLANE plane)
{
    unsigned int counter = 0;
    auto numberSamplesFromRow = static_cast<unsigned int>((info_.width + 1) / 2);
    for(auto iter = data_.cbegin(); iter < data_.cend(); )
    {
        auto blue = iter++;
        auto green = iter++;
        auto red = iter++;

        double pl;
        if(plane == PLANE::Cb)
        {
            pl = 128.0 + (-37.797 * (*red) + (-74.203) * (*green) + 112.000 * (*blue)) / 256.0;
        }
        else
        {
            pl = 128.0 + (112.000 * (*red) + (-93.786) * (*green) - 18.214 * (*blue)) / 256.0;
        }

        vec.push_back(static_cast<unsigned char>(pl));

        if(++counter == numberSamplesFromRow)
        {
            iter += (info_.width % 2 == 0) ? (info_.width + 1) * 3 : info_.width * 3;
            counter = 0;
        }
        else
        {
            iter += 3;
        }
    }
}

Yuv420Image &BmpImage::Yuv420Image()
{
    std::vector<unsigned char> yuv420Data;
    std::vector<unsigned char> CbData;
    std::vector<unsigned char> CrData;

    std::thread th2([&]() { this->CbCrPlane(CbData, PLANE::Cb); });
    std::thread th3([&]() { this->CbCrPlane(CrData, PLANE::Cr); });
    YPlane(yuv420Data);

    th2.join();
    th3.join();

    yuv420Data.insert(yuv420Data.end(), std::make_move_iterator(CbData.begin()), std::make_move_iterator(CbData.end()));
    yuv420Data.insert(yuv420Data.end(), std::make_move_iterator(CrData.begin()), std::make_move_iterator(CrData.end()));

    class Yuv420Image *yuvImage = new class Yuv420Image(yuv420Data);
    yuvImage->setSize(width_, height_);

    return *yuvImage;
}

