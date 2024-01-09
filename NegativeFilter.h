#pragma once

#include "Filter.h"

class NegativeFilter : public Filter {
public:
    Image Apply(const Image &image) override;
};