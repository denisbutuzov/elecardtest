#include <fstream>

class FstreamWrapper
        : public std::fstream
{
public:
    FstreamWrapper(const std::string &fileName, std::ios_base::openmode mode);
    std::fstream &read(char *s, std::streamsize n);
    std::fstream &write(const char *s, std::streamsize n);
};
