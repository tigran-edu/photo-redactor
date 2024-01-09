#include "MatrixFilter.h"

DoublePixel MatrixFilter::ApplyMatrixForPixel(int32_t center_point_coordinate_x, int32_t center_point_coordinate_y,
                                              std::vector<std::vector<double>>& arr, const Image &image) {
    DoublePixel float_pixel;
    int arr_width = arr[0].size();
    int arr_height = arr.size();
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t y = (1 - arr_height) / 2; y <= (arr_height - 1) / 2; ++y) {
        for (int32_t x = (1 - arr_width) / 2; x <= (arr_width - 1) / 2; ++x) {
            Pixel tmp_pixel;
            int32_t tmp_x = std::max(0, std::min(width - 1, center_point_coordinate_x + x));
            int32_t tmp_y = std::max(0, std::min(height - 1, center_point_coordinate_y + y));
            tmp_pixel = image.GetPixel(tmp_x, tmp_y);
            DoublePixel double_tmp_pixel = tmp_pixel.ConvertToDouble();
            float_pixel += double_tmp_pixel * arr[(arr_height - 1) / 2 + y][(arr_width - 1) / 2 + x];
        }
    }
    float_pixel.blue = std::min(1.0, std::max(0.0, float_pixel.blue));
    float_pixel.green = std::min(1.0, std::max(0.0, float_pixel.green));
    float_pixel.red = std::min(1.0, std::max(0.0, float_pixel.red));
    return float_pixel;
}