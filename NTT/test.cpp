#include <iostream>
#include "ntt.h"
#include "ntt_helper.h"
#include <random>
#include <cassert>
using std::cout;
using std::endl;
using std::vector;
using std::cin;
int main(){
  std::default_random_engine e(123);
  unsigned NUM = (truck_sz << n_sz) / 32 / 2;
  // std::vector<unsigned int> va{0x00000100};
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
  auto fa = fntt(a);
  vector<ull>().swap(a);
  auto fb = fntt(b);
  vector<ull>().swap(b);
  auto fc = multiply(fa, fb);
  vector<ull>().swap(fa);
  vector<ull>().swap(fb);
  auto c = rfntt(fc);
  vector<ull>().swap(fc);
  regular(c);
  // for(int i = 0; i < fa.size(); ++i){
  //   cout << fa[i] << "\t";
  // }
  // cout << endl;
  // for(int i = 0; i < fa0.size(); ++i){
  //   cout << fa0[i] << "\t";
  // }
  // cout << endl;

//  assert(c[0] == 1);
//  int count = (1<<n_sz) / 2;
//  for(int i = 1; i < count; ++i){
//    assert(c[i] == 0);
//  }
//  assert(c[count] == truck-2);
//  for(int i = 1; i < NUM; ++i){
//    assert(c[count+i] == truck-1);
//  }
//  std::cout << std::endl;
//
  return 0;
}
