#include "Image.h"
#include "NamespaceBMPImage.h"
#include "NegativeFilter.h"
#include "GrayscaleFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "CropFilter.h"
#include "GaussianBlurFilter.h"
#include "PixelFilter.h"
#include "ShadeFilter.h"
#include "CompressionFilter.h"
#include "Parsing.h"
#include "Print.h"
#include "CollageFilter.h"

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        Print::PrintInformation();
    } else if (argc < 3) {
        throw std::invalid_argument("Не указаны все аргументы, нужно указать пути к фотографиям: откуда считывать и куда записывать");
    } else {
        Image image;
        image = image::ReadBMP(argv[1]);
        ParseCmdLine(argc, argv, image);
        image::WriteBMP(image, argv[2]);
    }
}
