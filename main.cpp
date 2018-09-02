#include <iostream>
#include <fstream>

#include "BmpImage.h"

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

    std::vector<BYTE> yuvImage = image.yuvData();

    std::ofstream stream(argv[2], std::ios::binary);
    if (!stream)
    {
        std::cerr << "ERROR: Could not open file " << argv[2] << " for writing!" << std::endl;
        exit(1);
    }

    for(unsigned int i = 0; i < yuvImage.size() - 1; i++)
    {
        stream.write(reinterpret_cast<char *>(yuvImage[i]), sizeof(BYTE));
    }

    stream.close();

	return 0;
}
