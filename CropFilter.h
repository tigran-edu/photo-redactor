#pragma once

#include "Filter.h"

class CropFilter : public Filter {
public:
    Image Apply(const Image &image) override;

    CropFilter(int32_t width, int32_t height);

private:
    int32_t height_ = 0;
    int32_t width_ = 0;

};