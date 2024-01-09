#pragma once
#include "Filter.h"

class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter(double sigma);
    Image Apply(const Image &image) override;
private:
    double sigma_ = 0;
};

