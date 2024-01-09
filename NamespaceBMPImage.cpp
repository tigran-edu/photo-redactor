#include "NamespaceBMPImage.h"


const int INFORMATION_DIB_HEADER_SIZE = 40;
const int32_t NUMBER_OF_BITS_PER_PIXEL = 24;
const int32_t INFORMATION_BMP_HEADER_SIZE = 14;
const int32_t APPLICATION_SPECIFIC_START = 6;
const int32_t BMP_OFFSET = 54;
const int32_t PRINT_RESOLUTION_OF_THE_IMAGE = 2835;


void image::WriteVariable(int32_t variable, unsigned char arr[], int32_t start, int32_t end) {
    for (int32_t i = start; i <= end; ++i) {
        arr[i] = variable >> (i - start) * 8;
    }

}

int32_t image::Padding(int32_t width) {
    return (4 - (3 * width) % 4) % 4;
}

int32_t image::GetSize(const Image &image) {
    return 54 + 3 * (image::Padding(image.GetWidth()) + image.GetWidth()) * image.GetHeight();
}

Image image::ReadBMP(const char *path) {
    std::ifstream input(path, std::ios::in | std::ios::binary);
    int32_t width = 0;
    int32_t height = 0;
    if (input.is_open()) {
        unsigned char file_format[2];
        image::Read(input, file_format);
        if (file_format[0] != 'B' || file_format[1] != 'M') {
            throw std::invalid_argument("This file is not BMP-file: " + std::string(path));
        }
        input.seekg(16, std::ios::cur);

        image::Read(input, width);
        image::Read(input, height);
    } else {
        throw std::invalid_argument("Убедитесь, пожалуйста, что это путь к BMP-файлу: " + std::string(path));
    }
    const int padding = Padding(width);
    Image image(width, height);
    input.seekg(BMP_OFFSET, std::ios::beg);
    for (int32_t y = 0; y < std::abs(height); ++y) {
        for (int32_t x = 0; x < width; ++x) {
            unsigned char color[3];
            image::Read(input, color);
            Pixel tmp_pixel(color[2], color[1], color[0]);
            if (height <  0) {
                image.RewritePixel(tmp_pixel, x, std::abs(height) - 1 - y);
            } else {
                image.RewritePixel(tmp_pixel, x, y);
            }
        }
        input.ignore(padding);
    }
    input.close();
    return image;
}

void image::WriteBMP(const Image &image, const char *path) {
    int32_t size = image::GetSize(image);
    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();
    const int padding = image::Padding(width);
    std::ofstream output(path, std::ios::out | std::ios::binary);
    if (output.is_open()) {
        unsigned char information_bmp_header[INFORMATION_DIB_HEADER_SIZE] = {};
        information_bmp_header[0] = 'B';
        information_bmp_header[1] = 'M';

        WriteVariable(size, information_bmp_header, 2, 5);
        for (int i = APPLICATION_SPECIFIC_START; i <= APPLICATION_SPECIFIC_START + 3; ++i) {
            information_bmp_header[i] = '\0';
        }
        WriteVariable(BMP_OFFSET, information_bmp_header, 10, 13);

        output.write(reinterpret_cast<char*>(&information_bmp_header), INFORMATION_BMP_HEADER_SIZE);


        unsigned char information_dib_header[INFORMATION_DIB_HEADER_SIZE] = {};
        information_dib_header[0] = INFORMATION_DIB_HEADER_SIZE;

        // width
        WriteVariable(width, information_dib_header, 4, 7);

        // height
        WriteVariable(height, information_dib_header, 8, 11);

        information_dib_header[12] = 1;

        information_dib_header[14] = NUMBER_OF_BITS_PER_PIXEL;

        WriteVariable(  size - BMP_OFFSET, information_dib_header, 20, 23);
        WriteVariable(  PRINT_RESOLUTION_OF_THE_IMAGE, information_dib_header, 24, 31);


        output.write(reinterpret_cast<char*>(&information_dib_header), INFORMATION_DIB_HEADER_SIZE);
        unsigned char color_padding[3] = {0, 0, 0};
        for (int32_t y = 0; y < height; ++y) {
            for (int32_t x = 0; x < width; ++x) {
                unsigned char color[3];
                Pixel tmp_pixel = image.GetPixel(x, y);
                color[0] = tmp_pixel.blue;
                color[1] = tmp_pixel.green;
                color[2] = tmp_pixel.red;
                output.write(reinterpret_cast<char*>(&color), 3);
            }
            output.write(reinterpret_cast<char*>(&color_padding), padding);
        }
    } else {
        throw std::invalid_argument("Убедитесь, пожалуйста, что это путь к BMP-файлу: " + std::string(path));
    }
    output.close();
}