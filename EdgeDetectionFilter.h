#pragma once

#include "Filter.h"
#include "MatrixFilter.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    EdgeDetectionFilter(double threshold);

    Image Apply(const Image& image) override;

private:
    double threshold_ = 0;
    std::vector<std::vector<double>> matrix_arr_ = {{0.0,  -1.0, 0.0},
                                                    {-1.0, 4.0,  -1.0},
                                                    {0.0,  -1.0, 0.0}};
};