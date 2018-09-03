#include <iostream>
#include <fstream>

#include "BmpImage.h"
#include "Yuv420Image.h"

void check_arg(int argNumber)
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
}

int main(int argc, char **argv)
{
    check_arg(argc);

    //argv[1] - image.bmp
    BmpImage image(argv[1]);

    Yuv420Image yuvImage = image.toYuv420Image();
    yuvImage.saveImage(argv[2]);

	return 0;
}
