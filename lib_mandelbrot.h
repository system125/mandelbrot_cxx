
#ifndef MANDEL_LIB
#define MANDEL_LIB

#include <Eigen/Dense>
#include <opencv2/opencv.hpp>



cv::Mat compute_mandelbrot_iter(
    float x_min,
    float x_max,
    float y_min,
    float y_max,
    int N_GRID_POINTS,
    int N_ITER = 100
);

cv::Mat compute_julia_set(
    std::complex<float> c,
    float x_min,
    float x_max,
    float y_min,
    float y_max,
    int N,
    int max_iter = 100
);

#endif