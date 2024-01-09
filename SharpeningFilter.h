#pragma once

#include "Filter.h"
#include "MatrixFilter.h"

class SharpeningFilter : public MatrixFilter {
public:
    Image Apply(const Image &image) override;

private:
    std::vector<std::vector<double>> matrix_arr_ = {{0,  -1, 0},
                                                   {-1, 5,  -1},
                                                   {0,  -1, 0}};
};

