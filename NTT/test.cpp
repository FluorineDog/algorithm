#include <iostream>
#include "ntt.h"
int main(){
  auto a = init({11,22,33});
  auto b = init({1,0,2});
  auto fa = fft(a);
  auto fb = fft(b);
  auto fc = multiply(a, b);
  auto c = rfft(fc);
  for(int i = 0; i < 10; ++i){
    std::cout << c[i] << "\t";
  }
  std::cout << std::endl;
  return 0;
}