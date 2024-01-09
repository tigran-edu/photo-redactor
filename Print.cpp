#include <iostream>
#include "Print.h"

void Print::PrintInformation() {
    std::cout
            << "Приветствую! Чтобы начать пользоваться фильтром - ввидите путь к файлу, откуда нужно считать, а после к файлу, куда записывать. Оба файла должны быть формата BMP";
    std::cout << "В этом редакторе фотографий есть 10 фильтров:" << std::endl;
    std::cout
            << "1. Crop: чтобы его использовать, введи -crop, а также укажи новые размеры для фотографии, сначала Width, потом Height. Учтите, что если указать размеры, которые больше чем у исходного фото, то ничего не произойдет."
            << std::endl;
    std::cout << "2. Grayscale: чтобы его использовать, введи -gs, дополнительно ничего указывать не нужно"
              << std::endl;
    std::cout << "3. Negative: чтобы его использовать, введи -neg, дополнительно ничего указывать не нужно "
              << std::endl;
    std::cout << "4. Sharpening: чтобы его использовать, введи -sharp, дополнительно ничего указывать не нужно"
              << std::endl;
    std::cout
            << "5. Edge Detection: чтобы его использовать, введи -edge и threshold, threshold принимает значения от 0 до 1"
            << std::endl;
    std::cout << "6. PixelFilter: чтобы его использовать введи -pix, а также указать Pixel_width и Pixel_height. Причем Pixel_width < Image_width / 25. Аналогично с Height " << std::endl;
    std::cout << "7. CompressionFilter: чтобы его использовать введи -comp. Ничего больше указыватьь не нужно." << std::endl;
    std::cout << "8. GaussianBlurFilter: чтобы его использовать введи -blur и значение sigma, принимает значения больше 0." << std::endl;
    std::cout << "9. ShadeFilter: чтобы его использовать введи -shade и 3 значения: Red, Green, Blue. Все числа целые от 0 до 255" << std::endl;
    std::cout << "10. CollageFilter: чтобы его использовать введи -collage, дополнительно ничего указывать не нужно" << std::endl;

}
