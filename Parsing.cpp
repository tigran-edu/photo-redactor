#include "Parsing.h"


Parser::Parser(int argc, const char *argv[], Image &image) : argc_(argc), image_(image), argv_(argv) {
    commands_["-gs"] = [&]() {
        ParseGrayscaleFilter();
        ++pos_;
    };
    commands_["-sharp"] = [&]() {
        ParseSharpeningFilter();
        ++pos_;
    };
    commands_["-crop"] = [&]() {
        ParseCropFilter();
        pos_ += 3;
    };
    commands_["-neg"] = [&]() {
        ParseNegativeFilter();
        ++pos_;
    };
    commands_["-edge"] = [&]() {
        std::cout << "Edge Detection start" << std::endl;
        ParseGrayscaleFilter();
        ParseEdgeDetectionFilter();
        pos_ += 2;
    };
    commands_["-blur"] = [&]() {
        ParseGaussianFilter();
        pos_ += 2;
    };
    commands_["-collage"] = [&]() {
        ParseCollageFilter();
        ++pos_;
    };
    commands_["-pix"] = [&]() {
        ParsePixelFilter();
        pos_ += 3;
    };
    commands_["-shade"] = [&]() {
        ParseShadeFilter();
        pos_ += 4;
    };
    commands_["-comp"] = [&]() {
        ParseCompressionFilter();
        ++pos_;
    };
}

void Parser::Parse() {
    while (pos_ < argc_) {
        Consume();
    }
}

void Parser::Consume() {
    std::string first_arg(argv_[pos_]);
    auto it = commands_.find(first_arg);
    if (it != commands_.end()) {
        it->second();
    } else if (argc_ != 3) {
        throw std::out_of_range("No such Filter: " + std::string(argv_[pos_]));
    }
}

void Parser::ParseGrayscaleFilter() {
    filter_ = std::make_unique<GrayscaleFilter>();
    ApplyFilter();
}

void Parser::ParseNegativeFilter() {
    filter_ = std::make_unique<NegativeFilter>();
    ApplyFilter();
}

void Parser::ParseSharpeningFilter() {
    filter_ = std::make_unique<SharpeningFilter>();
    ApplyFilter();
}


void Parser::ApplyFilter() {
    image_ = filter_->Apply(image_);
}

void Parser::ParseEdgeDetectionFilter() {
    if (pos_ + 1 == argc_) {
        throw std::out_of_range("usage: -edge <threshold>.");
    }
    try {
        double threshold = std::stod((argv_[pos_ + 1]));
        if (threshold > 1 || threshold < 0) {
            throw std::out_of_range("usage: 0 <= threshold <= 1");
        }
        filter_ = std::make_unique<EdgeDetectionFilter>(threshold);
        ApplyFilter();
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("threshold should be double, got: " + std::string(argv_[pos_ + 1]));
    }
}

void Parser::ParseCropFilter() {
    if (pos_ + 2 >= argc_) {
        throw std::out_of_range("usage: -crop <width> <height>.");
    }
    try {
        int32_t width = std::stoi((argv_[pos_ + 1]));
        int32_t height = std::stoi((argv_[pos_ + 2]));
        filter_ = std::make_unique<CropFilter>(width, height);
        ApplyFilter();
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("width and height should be integer, got: " + std::string(argv_[pos_ + 1]) + " " +
                                    std::string(argv_[pos_ + 2]));
    }
}

void Parser::ParseGaussianFilter() {
    double sigma = 0;
    if (pos_ + 1 == argc_) {
        throw std::out_of_range("usage: -blur <sigma>.");
    }
    try {
        sigma = std::stod((argv_[pos_ + 1]));
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("sigma should be double, got: " + std::string(argv_[pos_ + 1]));
    }
    if (sigma < 0) {
        throw std::invalid_argument("sigma should be bigger than 0, got: " + std::string(argv_[pos_ + 1]));
    }
    filter_ = std::make_unique<GaussianBlurFilter>(sigma);
    ApplyFilter();
}

void Parser::ParseCollageFilter() {
    filter_ = std::make_unique<CollageFilter>();
    ApplyFilter();
}

void Parser::ParseShadeFilter() {
    if (pos_ + 3 >= argc_) {
        throw std::out_of_range("usage: -blur <Red> <Green> <Blue>.");
    }
    try {
        int red = std::stoi((argv_[pos_ + 1]));
        int green = std::stoi((argv_[pos_ + 2]));
        int blue = std::stoi((argv_[pos_ + 3]));
        if (red > 255 || green > 255 || blue > 255 || red < 0 || green < 0 || blue < 0) {
            throw std::out_of_range("colors ranging from 0 to 255, got: " + std::string(argv_[pos_ + 1]) + " " +
                                    std::string(argv_[pos_ + 2]) + " " + std::string(argv_[pos_ + 3]));
        }
        filter_ = std::make_unique<ShadeFilter>(red, green, blue);
        ApplyFilter();
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument(
                "colors should be integer, got: " + std::string(argv_[pos_ + 1]) + " " + std::string(argv_[pos_ + 2]) +
                " " + std::string(argv_[pos_ + 3]));
    }
}

void Parser::ParseCompressionFilter() {
    filter_ = std::make_unique<CompressionFilter>();
    ApplyFilter();
}

void Parser::ParsePixelFilter() {
    if (pos_ + 2 >= argc_) {
        throw std::out_of_range("usage: -pix <Width> <Height>.");
    }
    int32_t width = 0;
    int32_t height = 0;
    try {
        width = std::stoi((argv_[pos_ + 1]));
        height = std::stoi((argv_[pos_ + 2]));
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("Width and Height should be integer, got: " + std::string(argv_[pos_ + 1]) + " " +
                                    std::string(argv_[pos_ + 2]));
    }
    filter_ = std::make_unique<PixelFilter>(width, height);
    if (width >= image_.GetWidth() / 25 || height >= image_.GetHeight() / 25) {
        throw std::invalid_argument(
                "Width and Height of pixel are soo big. Width of pixel should be smaller than width of image / 25 and Height of pixel should be smaller than height of image / 25 ");
    }
    if (height <= 2 || width <= 2) {
        throw std::invalid_argument(
                "Width and Height should be bigger than 2, got: " + std::string(argv_[pos_ + 1]) + " " +
                std::string(argv_[pos_ + 2]));
    }
    ApplyFilter();
}



void ParseCmdLine(int argc, const char *argv[], Image &image) {
    Parser parser(argc, argv, image);
    parser.Parse();
}

