cmake_minimum_required(VERSION 3.5)
project(ntt)
#pragma omp parral for
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
add_library(ntt ntt.cpp)
add_library(fntt fntt.cpp)
add_executable(tt test.cpp ntt fntt)
# add_executable(gg ggtest.cpp)
# target_link_libraries(gg gtest gtest_main fntt)

