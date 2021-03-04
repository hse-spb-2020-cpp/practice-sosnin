#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

namespace hse::cpp {

// #pragma pack(push, 1)
// struct BMPFileHeader {
//     uint16_t bfType;
//     uint32_t bfSize;
//     uint16_t bfReserved1;
//     uint16_t bfReserved2;
//     uint32_t bfOffBits;
// };
// #pragma pack(pop)
// char *raw_header[14];
// BMPFileHeader *bmp_header = reinterpret_cast<BMPFileHeader *>(raw_header);

class File {
public:
    File(const char *path) {
        file_ = fopen(path, "r");
    }

    ~File() {
        fclose(file_);
    }

    File(const File &other) = delete;
    File &operator=(const File &other) = delete;

    File(File &&other) noexcept {
        swap(other, *this);
    }

    File &operator=(File &&other) noexcept {
        swap(other, *this);
        return *this;
    }

    void print() {
        if (file_ == NULL)
            return;

        char buffer[100];

        while (!feof(file_)) {
            if (fgets(buffer, 100, file_) == NULL)
                break;
            fputs(buffer, stdout);
        }
    }

private:
    static void swap(File &lhs, File &rhs) {
        std::swap(lhs.file_, rhs.file_);
    }

private:
    FILE *file_;
};

}  // namespace hse::cpp

int main(int argc, char *argv[]) {
    using namespace hse::cpp;

    if (argc < 2) {
        printf("Usage: %s <file path>\n", argv[0]);
        return 1;
    }

    std::string path(argv[1]);
    File file(path.c_str());
    file.print();

    if (argc > 2) {
        int arg = std::stoi(argv[2]);
        std::cout << arg << std::endl;
    }

    return 0;
}
