#include <fstream>

class FstreamWrapper
        : public std::fstream
{
public:
    FstreamWrapper(const char *filename, std::ios_base::openmode mode);
    std::fstream &read(char *s, std::streamsize n);
    std::fstream &write(char *s, std::streamsize n);
};
