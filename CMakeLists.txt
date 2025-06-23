cmake_minimum_required(VERSION 3.10)
project(mandelbrot_cxx)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(TBB REQUIRED)

add_library(lib_mandelbrot STATIC
    lib_mandelbrot.cxx
    lib_mandelbrot.h
    # Uncomment the next line if you have this file
    # lib_mandelbrot_iter.cpp
)
target_link_libraries(lib_mandelbrot PRIVATE Eigen3::Eigen ${OpenCV_LIBS})
target_include_directories(lib_mandelbrot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lib_mandelbrot PRIVATE ${OpenCV_INCLUDE_DIRS})

add_executable(mandelbrot_cxx main.cxx)
target_compile_features(mandelbrot_cxx PRIVATE cxx_std_23)
target_include_directories(mandelbrot_cxx PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(mandelbrot_cxx PRIVATE lib_mandelbrot ${OpenCV_LIBS} Eigen3::Eigen TBB::tbb)
