#include <iostream>

void check_arg(int n) { 
    if(n == 1) {
        std::cout << "Too few arguments" << std::endl;
        exit(1);
	}
    else if(n == 2) {
        std::cout << "More arguments is required" << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv) {
    check_arg(argc);

    std::cout << "Video file name is: " << argv[1] << std::endl;
    std::cout << "Image file name is: " << argv[2] << std::endl;

	return 0;
}
