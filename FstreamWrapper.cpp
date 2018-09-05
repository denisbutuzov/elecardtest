#include <iostream>

#include "FstreamWrapper.h"

FstreamWrapper::FstreamWrapper(const char *filename, std::ios_base::openmode mode)
    : std::fstream(filename, mode)
{
    if(!*this)
    {
        std::cerr << "ERROR: Could not open file " << filename << "." << std::endl;
        exit(1);
    }
}

std::fstream &FstreamWrapper::read(char *s, std::streamsize n)
{
    std::fstream::read(s, n);
    if(!*this)
    {
        std::cerr << "ERROR: Could not read from file." << std::endl;
        exit(1);
    }

    return *this;
}

std::fstream &FstreamWrapper::write(char *s, std::streamsize n)
{
    std::fstream::write(s, n);
    if(!*this)
    {
        std::cerr << "ERROR: Could not write to file." << std::endl;
        exit(1);
    }

    return *this;
}
