#pragma once

#include "Filter.h"
#include "MatrixFilter.h"

class PixelFilter : public Filter {
public:
    Image Apply(const Image& image) override;

    PixelFilter(int32_t width, int32_t height);

private:
    int32_t width_of_pixel_ = 0;
    int32_t height_of_pixel_ = 0;

};
