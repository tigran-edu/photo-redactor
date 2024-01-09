#pragma once

#include "Filter.h"

class MatrixFilter : public Filter {
public:
    DoublePixel ApplyMatrixForPixel(int32_t center_point_coordinate_x, int32_t center_point_coordinate_y,
                                    std::vector<std::vector<double>>& arr, const Image &image);
};