#pragma once
#include "Filter.h"

class GrayscaleFilter : public Filter {
public:
    Image Apply(const Image& image) override;
};
