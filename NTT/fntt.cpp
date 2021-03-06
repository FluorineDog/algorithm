#include "ntt.h"
#include "ntt_helper.h"
#include <iostream>

using std::vector;
class Mapper {
public:
  Mapper(){
    data.resize(N);
    data[0] = 0;
    int n = 1;
    int offset = N / 2;
    while(offset){
      for(int j = 0; j < n; ++j){
        data[j+n] = data[j] + offset;
      }
      n <<= 1;
      offset >>= 1;
    }
  }
private:
  vector<int> data;
public:
  int get(int n){
    return data[n];
  }
};
static Mapper mapper;

static FreqDomain faster_fourier_transform(TimeDomain&& td, int root_base){
  vector<ull> roots(n_sz);
  for(auto &r:roots){
    r = root_base;
    root_base = root_base * root_base % Prime;
  }
  int endpt = n_sz - 1;
  for(int step = 0; step < endpt; ++step){
    int offset = 1 << step;
#pragma omp parallel for
    for(int beg = 0; beg < N; beg += 2*offset){
      ull root = roots[n_sz - 1 - step];
      ull shift = 1;
      for(int i = beg; i < beg + offset; ++i){
        ull even = td[i];
        ull odd  = td[i+offset]*shift;
        ull left = (even + odd) % Prime;
        ull right = (even + Prime*Prime - odd)%Prime;
        td[i] = left;
        td[i + offset] = right;
        shift = root * shift % Prime;
        int pause = 1+1;
      }
    }
  }

  for(int step = endpt; step < n_sz; ++step){
    int offset = 1 << step;
    for(int beg = 0; beg < N; beg += 2*offset){
      ull root = roots[n_sz - 1 - step];
      ull shift = 1;
#pragma omp parallel for
      for(int i = beg; i < beg + offset; ++i){
        ull even = td[i];
        ull odd  = td[i+offset]*shift;
        ull left = (even + odd) % Prime;
        ull right = (even + Prime*Prime - odd)%Prime;
        td[i] = left;
        td[i + offset] = right;
        shift = root * shift % Prime;
        int pause = 1+1;
      }
    }
  }

  return std::move(td);
}

FreqDomain fntt(const TimeDomain& td){
  TimeDomain td_reorder(td.size());
#pragma omp parallel for
  for(int i = 0; i < td.size(); ++i){
    td_reorder[i] = td[mapper.get(i)];
    // std::cerr << Mapper::get(i) << "\t";
  }
  // std::cerr << std::endl;
  return faster_fourier_transform(std::move(td_reorder), Root);
}

TimeDomain rfntt(const FreqDomain& fd){
  TimeDomain fd_reorder(fd.size());
#pragma omp parallel for
  for(int i = 0; i < fd.size(); ++i){
    fd_reorder[i] = fd[mapper.get(i)];
  }
  auto td = faster_fourier_transform(std::move(fd_reorder), RootRev);
  for(auto &digit:td){
    digit = digit * NRev % Prime;
  }
  return td;
}
