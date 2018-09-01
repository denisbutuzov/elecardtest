#include <iostream>
#include <fstream>

#include "BmpImage.h"

using namespace std;

void check_arg(int n)
{
    if(n == 1)
    {
        cerr << "Too few arguments" << endl;
        exit(1);
	}
    else if(n == 2)
    {
        cerr << "More arguments is required" << endl;
        exit(1);
    }
}

int main(int argc, char **argv)
{
    check_arg(argc);

    //argv[1] - image.bmp
    BmpImage image(argv[1]);


    //argv[2] - video.yuv
    ifstream video;
    video.open(argv[2], ios::binary);
    if(!video)
    {
        cerr << "Can not open file " << argv[2] << endl;
        exit(1);
    }



	return 0;
}
