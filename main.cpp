#include <iostream>
#include <fstream>

void check_arg(int n) { 
    if(n == 1) {
        std::cerr << "Too few arguments" << std::endl;
        exit(1);
	}
    else if(n == 2) {
        std::cerr << "More arguments is required" << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv) {
    check_arg(argc);

    //argv[1] - video.yuv
    std::ifstream video;

    video.open(argv[1], std::ios::binary);
    if(!video)
    {
        std::cerr << "Can not open file " << argv[1] << std::endl;
        exit(1);
    }

    //argv[2] - image.bmp
    std::ofstream image;
    image.open(argv[2], std::ios::binary);
    if(!image)
    {
        std::cerr << "Can not open file " << argv[2] << std::endl;
        exit(1);
    }


	return 0;
}
