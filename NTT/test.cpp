#include <iostream>
#include "ntt.h"
#include "ntt_helper.h"
#include <random>
#include <cassert>
using std::cout;
using std::vector;
using std::cin;
int main(){
  std::default_random_engine e(123);
  unsigned NUM = (3 << n_sz) / 32;

  std::vector<unsigned int> va(NUM, 0xFFFFFFFF), vb(NUM, 0xFFFFFFFF);
  // for(auto &x: va){
  //   x = e();
  // }
  // for(auto &x: vb){
  //   x = e();
  // }
  auto a = init(va);
  vector<unsigned>().swap(va);
  auto b = init(vb);
  vector<unsigned>().swap(vb);
  auto fa = fft(a);
  vector<ull>().swap(a);
  auto fb = fft(b);
  vector<ull>().swap(b);
  auto fc = multiply(fa, fb);
  vector<ull>().swap(fa);
  vector<ull>().swap(fa);
  auto c = rfft(fc);
  vector<ull>().swap(fc);
  regular(c);

  assert(c[0] == 1);
  int count = (1<<n_sz) / 2;
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
