
#include <Eigen/Dense>
#include <ranges>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <execution>
#include <complex>
#include <opencv2/opencv.hpp>


cv::Mat compute_mandelbrot_iter(
    float x_min,
    float x_max,
    float y_min,
    float y_max,
    int N_GRID_POINTS,
    int N_ITER = 100
){

    cv::Mat result(N_GRID_POINTS+1,N_GRID_POINTS+1,CV_8UC1);

    const auto dx = (x_max-x_min)/N_GRID_POINTS;
    const auto dy = (y_max - y_min)/N_GRID_POINTS;

    auto range = std::views::iota(0,N_GRID_POINTS+1);

    std::for_each(std::execution::par, range.begin(),range.end(),[&](int i){
        auto x = x_min + dx*i;
        for (int j = 0; j <= N_GRID_POINTS; j++){
            auto y = y_min + dy*j;
            auto c = std::complex<float>(x,y);
            auto z_n = c;

            std::cout << "Computing for z "<< c << std::endl;
            bool in_set = true;
            for (int n = 0; n < N_ITER; n++){
                if (std::abs(z_n) > 2.0f){
                    in_set = false;
                    break;
                }

                z_n = z_n*z_n + c;

            }

            auto res_int = in_set?1:0;
            result.at<uchar>(i, j) = static_cast<uchar>(
                std::min(255.0f, std::max(0.0f, res_int * 255.0f)));
            }

        }
    );


    return result;

}


cv::Mat compute_julia_set(
    std::complex<float> c,
    float x_min,
    float x_max,
    float y_min,
    float y_max,
    int N,
    int max_iter = 100
){
    cv::Mat res(N+1,N+1,CV_8UC1);

    auto dx = (x_max - x_min)/N;
    auto dy = (y_max - y_min)/N;

    auto range = std::views::iota(0,N+1);

    std::for_each(
        std::execution::par,
        range.begin(),
        range.end(),
    [&](int i){
            auto xs = x_min + i*dx;

            for (int j = 0; j <= N; j++){
                auto z_0 = std::complex<float>(
                    xs,
                    y_min + j*dy
                );

                auto z = z_0;
                auto in_set = true;

                for (int n = 0; n < max_iter; n++){
                    if (std::abs(z) > 2.0f){
                        in_set = false;
                        break;
                    }
                    z = z*z + c;
                }
            auto res_int = in_set?1:0;
            res.at<uchar>(i, j) = static_cast<uchar>(
                std::min(255.0f, std::max(0.0f, res_int * 255.0f)));
            }
    });

    return res;
}