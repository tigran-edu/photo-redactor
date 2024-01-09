cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )

add_executable(
        image_processor
        Image.cpp
        Pixels.cpp
        image_processor.cpp
        NegativeFilter.cpp
        GrayscaleFilter.cpp
        SharpeningFilter.cpp
        EdgeDetectionFilter.cpp
        MatrixFilter.cpp
        CropFilter.cpp
        "NamespaceBMPImage.cpp"
        GaussianBlurFilter.cpp
        Parsing.cpp
        Print.cpp
        CompressionFilter.cpp
        PixelFilter.cpp
        ShadeFilter.cpp
        CollageFilter.cpp )

