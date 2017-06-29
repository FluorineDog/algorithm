#include <iostream>
#include "ntt.h"
#include <random>
#include <cassert>
using std::cout;
using std::cin;
int main(){
  std::default_random_engine e(123);
  constexpr unsigned NUM = (3 << 19) / 32;
  std::vector<unsigned int> va(NUM, 0xFFFFFFFF), vb(NUM, 0xFFFFFFFF);
  /*
  for(auto &x: va){
    x = e();
  }
  for(auto &x: vb){
    x = e();
  }
  */
  const auto a = init(va);
  const auto b = init(vb);
  const auto fa = fft(a);
  const auto fb = fft(b);
  const auto fc = multiply(fa, fb);
  const auto tfa = rfft(fa);
  auto c = rfft(fc);
  regular(c);

  for(int i = 0; i < 6; ++i){
    std::cout << va[i] << "\t";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  assert(c[0] == 1);
  int count = (1<<19) / 2;
  for(int i = 1; i < count; ++i){
    assert(c[i] == 0);
  }
  assert(c[count] == 62);
  for(int i = 1; i < NUM; ++i){
    assert(c[count+i] == 63);
  }
  std::cout << std::endl;

  return 0;
}
