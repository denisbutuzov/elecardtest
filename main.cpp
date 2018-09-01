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

    image.rgbToYuv();
    image.saveImage(argv[2]);

	return 0;
}
