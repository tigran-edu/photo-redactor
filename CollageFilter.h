#pragma once
#include "Filter.h"
#include "ShadeFilter.h"
#include "PixelFilter.h"
#include "CompressionFilter.h"


class CollageFilter : public Filter {
public:
    Image Apply(const Image &image) override;
};

