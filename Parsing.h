#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "GrayscaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "CropFilter.h"
#include "GaussianBlurFilter.h"
#include "CollageFilter.h"
#include "CompressionFilter.h"
#include "PixelFilter.h"
#include "ShadeFilter.h"
#include "Filter.h"
#include "Image.h"


class Parser {
public:
    Parser(int argc, const char *argv[], Image &image);

    void Parse();

private:
    void Consume();

    void ParseGrayscaleFilter();

    void ParseNegativeFilter();

    void ParseSharpeningFilter();

    void ParseEdgeDetectionFilter();

    void ParseCropFilter();

    void ParseGaussianFilter();

    void ParseCollageFilter();

    void ParseShadeFilter();

    void ParseCompressionFilter();

    void ParsePixelFilter();


    void ApplyFilter();

    int pos_ = 3;
    const int argc_ = 0;
    Image &image_;
    const char **argv_;
    std::unique_ptr<Filter> filter_;
    using Command = std::function<void()>;
    std::unordered_map<std::string, Command> commands_;
};

void ParseCmdLine(int argc, const char *argv[], Image &image);