#include <iostream>
#include <fstream>

#include "BmpImage.h"

void check_arg(int n)
{
    if(n == 1)
    {
        std::cerr << "ERROR: Too few arguments." << std::endl;
        exit(1);
	}
    else if(n == 2)
    {
        std::cerr << "ERROR: More arguments is required." << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv)
{
    check_arg(argc);

    //argv[1] - image.bmp
    BmpImage image(argv[1]);


    //argv[2] - video.yuv
    std::ifstream video;
    video.open(argv[2], std::ios::binary);
    if(!video)
    {
        std::cerr << "Can not open file " << argv[2] << std::endl;
        exit(1);
    }



	return 0;
}
