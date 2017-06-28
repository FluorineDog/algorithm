#include "ntt.h"
#include "ntt_helper.h"
#include <cmath>
using std::vector;
#include <unordered_map>
TimeDomain init(const std::vector<unsigned int>& number){
  constexpr int input_base_sz = 32;
  // assume base = 1 << 32
  TimeDomain td;
  td.reserve(N);
  ull tmp = 0;
  int shift = 0;
  for(auto digit:number) {
    tmp += digit << shift;
    shift += 32;
    while(shift >= truck_sz){
      td.push_back(tmp & (truck - 1));
      tmp >>= truck_sz;
      shift -= truck_sz;
    }
  }
  td.resize(N, 0);
  return td;
}

void regular(TimeDomain& td){
  ull carry = 0;
  for(auto &digit : td){
    carry += digit;
    digit = carry & (truck - 1);
    carry >>= truck_sz;
  }
}

//static std::unordered_map<int, ull> root_table;
//ull get_root(int size){
//  auto & result = root_table[size];
//  if(result == 0){
//    ull subroot = root_table[size/2];
//    result = subroot * subroot % Prime;
//  }
//  return result;
//}


FreqDomain fast_fourier_transform(const TimeDomain& td, int size, int root){
  if(size == 1){
    return FreqDomain {td[0]};
  }
  TimeDomain tdEven(size/2);
  TimeDomain tdOdd(size/2);
  for(int i = 0; i < size/2; i++){
    tdEven[i] = td[2*i];
    tdOdd[i] = td[2*i + 1];
  }
  ull next_root = root*root % Prime;
  FreqDomain even_fd = fast_fourier_transform(tdEven, size/2, next_root);
  FreqDomain odd_fd = fast_fourier_transform(tdOdd, size/2, next_root);
  FreqDomain result(size);
  ull shift = 1;
  for(int i = 0; i < size/2; ++i){
    result[i] = (even_fd[i] + odd_fd[i] * shift) % Prime;
    result[i + size/2] = (even_fd[i] + odd_fd[i] * (Prime-shift)) % Prime;
    shift = shift * root % Prime;
  }
  return std::move(result);
}

FreqDomain fft(const TimeDomain& td){
  return fast_fourier_transform(td, N, Root);
}
TimeDomain rfft(const FreqDomain& fd){
  auto td = fast_fourier_transform(fd, N, RootRev);
  for(auto &digit:td){
    digit = digit * NRev % Prime;
  }
  return td;
}
FreqDomain multiply(const FreqDomain &fd1, const FreqDomain &fd2){
  FreqDomain fd0(fd1.size());
  for(int i = 0; i < fd0.size(); ++i){
    fd0[i] = fd1[i] * fd2[i] % Prime;
  }
  return fd0;
}
