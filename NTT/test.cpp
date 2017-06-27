#include <iostream>
#include "ntt.h"
int main(){
  auto a = init({0x10, 0});
  // auto b = init({0x76543210});
  auto fa = fft(a);
  // auto fb = fft(b);
  // auto fc = multiply(a, b);
  // auto c = rfft(fc);
  for(int i = 0; i < 16; ++i){
    std::cout << a[i] << "\t";
  }
  std::cout << std::endl;
  for(int i = 0; i < 16; ++i){
    std::cout << fa[i] << "\t";
  }
  std::cout << std::endl;
  auto ta = rfft(a);
  for(int i = 0; i < 16; ++i){
    std::cout << ta[i] << "\t";
  }
  std::cout << std::endl;
  return 0;
}