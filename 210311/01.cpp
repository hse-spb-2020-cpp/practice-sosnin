#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

namespace hse::cpp {

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
static_assert(sizeof(BMPFileHeader) == 14);
#pragma pack(pop)

// static_assert(sizeof(BMPInfoHeader) == 40);

// char *raw_header[14];
// ... // read data to raw_header
// BMPFileHeader *bmp_header = reinterpret_cast<BMPFileHeader*>(raw_header);

// BMPFileHeader file_header{};
// ...
// input_stream.read(reinterpret_cast<char*>(&file_header), sizeof file_header);

}  // namespace hse::cpp

int main(int argc, char *argv[]) {
    using namespace hse::cpp;

    if (argc < 2) {
        printf("Usage: %s <message>\n", argv[0]);
        return 1;
    }

    std::string message(argv[1]);
    std::cout << message << std::endl;

    return 0;
}
