#include <iostream>
#include "ntt.h"
int main(){
  auto a = init({0x12, 0});
  auto b = init({0x76543210});
  auto fa = fft(a);
  auto fb = fft(b);
  auto fc = multiply(fa, fb);
  auto c = rfft(fc);
  for(int i = 0; i < 16; ++i){
    std::cout << c[i] << "\t";
  }
  std::cout << std::endl;
  return 0;
}