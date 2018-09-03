#include <iostream>
#include <fstream>
#include <regex>

#include "BmpImage.h"
#include "Yuv420Image.h"

std::pair<int, int> check_arg(int argNumber, char **arg)
{
    if(argNumber == 1)
    {
        std::cerr << "ERROR: Too few arguments." << std::endl;
        exit(1);
	}
    else if(argNumber == 2)
    {
        std::cerr << "ERROR: More arguments is required." << std::endl;
        exit(1);
    }
    else if(argNumber == 3)
    {
        std::cerr << "ERROR: Video file resolution is required." << std::endl;
        exit(1);
    }

    std::regex regExp("(.*)x(.*)");
    std::smatch match;
    std::string str = arg[3];
    if(std::regex_search(str, match, regExp))
    {
        std::pair<int, int> resolution;
        resolution.first = std::stoi(match[1]);
        resolution.second = std::stoi(match[2]);
        return resolution;
    }
    else
    {
        std::cerr << "ERROR: Invalid video file resolution. Expected <width>x<height>. Example: 640x480." << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv)
{
    std::pair<int, int> resolution = check_arg(argc, argv);

    //argv[1] - image.bmp
    BmpImage image(argv[1]);

    Yuv420Image yuvImage = image.toYuv420Image();
    yuvImage.saveImage(argv[2]);

	return 0;
}
