#include <iostream>
#include <regex>

#include "BmpImage.h"
#include "Yuv420Image.h"
#include "Yuv420Video.h"
//#include "Foo.h"

std::pair<unsigned int, unsigned int> check_arg(int argNumber, char **arg)
{
    switch(argNumber)
    {
    case 1:
        std::cerr << "ERROR: Too few arguments." << std::endl;
        exit(1);
    case 2:
        std::cerr << "ERROR: More arguments is required." << std::endl;
        exit(1);
    case 3:
        std::cerr << "ERROR: Video file resolution is required." << std::endl;
        exit(1);
    case 4:
        std::cerr << "ERROR: Result video file name is required." << std::endl;
        exit(1);
    default: ;
    }

    std::regex regExp("(.*)x(.*)");
    std::smatch match;
    std::string str = arg[3];
    if(std::regex_search(str, match, regExp))
    {
        std::pair<unsigned int, unsigned int> resolution;
        resolution.first = static_cast<unsigned int>(std::stoi(match[1]));
        resolution.second = static_cast<unsigned int>(std::stoi(match[2]));
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
    std::pair<unsigned int, unsigned int> resolution = check_arg(argc, argv);

//    argv[1] - image.bmp
    BmpImage image(argv[1]);

    Yuv420Image yuvImage = image.Yuv420Image();

    Yuv420Video yuvVideo(argv[2], resolution);
    yuvVideo.setYuv420Image(yuvImage);
    //yuvVideo.saveOnDisk(argv[4]);

//    Foo foo;

//    foo.func1();

	return 0;
}
