#pragma once

#include "Filter.h"
#include "PixelFilter.h"

class CompressionFilter : public Filter {
public:
    Image Apply(const Image &image) override;
};

