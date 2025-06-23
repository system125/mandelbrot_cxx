
#include <iostream>
#include <Eigen/Dense>
# include "lib_mandelbrot.h"
#include <opencv2/opencv.hpp>
#include <execution>
#include <ranges>
#include <complex>

int main(){

    float x_min = -1.5; float x_max = 2.5;
    float y_min = -.5; float y_max = 5;
    int n_grid_point = 1000;


    auto c = std::complex<float>(-0.5251993f, 0.5251993f);

    std::cout << "This is main.."<<std::endl;

    auto img = compute_mandelbrot_iter(x_min,x_max,y_min,y_max,n_grid_point);
    auto julia_img = compute_julia_set(
        c,x_min,x_max,y_min,y_max,n_grid_point
    );
    cv::Mat combined;
    int thickness = 5;
    cv::Scalar red(0, 0, 255); // BGR format for red


    cv::hconcat(img,julia_img,combined);
    cv::imshow("Mandelbrot +Julia set",combined);
    cv::waitKey(0);
    return 0;
}