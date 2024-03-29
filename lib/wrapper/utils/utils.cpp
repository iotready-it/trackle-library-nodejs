#include "utils.hpp"

void log(const std::initializer_list<std::string> &strings)
{
    std::stringstream sstm;

    // if (wrapperLog)
    // {
    sstm.str("");
    for (const auto &str : strings)
    {
        sstm << str;
    }

    std::cout << sstm.str() << std::endl;
    // }
}

std::string extractBufferByte(const unsigned char *buf, uint32_t buflen)
{
    std::stringstream sstm;
    for (size_t i = 0; i < buflen; ++i)
    {
        if (i > 0)
        {
            sstm << ", ";
        }
        sstm << "0x" << std::hex << static_cast<int>(buf[i]);
    }

    return sstm.str();
}