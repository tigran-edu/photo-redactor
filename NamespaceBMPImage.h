#include "Image.h"

namespace image {
    int32_t Padding(int32_t width);

    Image ReadBMP(const char *path);

    void WriteBMP(const Image &image, const char *path);

    int32_t GetSize(const Image &image);

    void WriteVariable(int32_t variable, unsigned char arr[], int32_t start, int32_t end);

    template<typename T>
    void Read(std::ifstream &input, T& variable) {
        input.read(reinterpret_cast<char*>(&variable), sizeof(variable));
    }
}