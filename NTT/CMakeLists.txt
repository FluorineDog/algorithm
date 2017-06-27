project(ntt)
add_library(ntt ntt.cpp)
add_executable(test test.cpp ntt)