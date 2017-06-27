#include "ntt.h"
using std::vector;
#include <unordered_map>
constexpr int truck_sz = 4;  // vary with N
constexpr int n_sz = 12;     // maximum 20 with truck_sz = 6

constexpr ull N = 1 << n_sz;        
constexpr ull truck = 1 << truck_sz; 

static_assert(n_sz + 2 * truck_sz < 32, "truck limit exceeds");

constexpr ull Prime = 3*N + 1;      // must be a prime
constexpr ull Root = 11;            // must be a primitive root
constexpr ull RootRev = 5586;       // must set accordingly
constexpr ull TwoRev  = 6145;       // must set accordingly
static_assert(Prime < (1ull << 32), "prime is too large");
static_assert((Root * RootRev) % Prime == 1,  "Root^-1 != RootRev");
static_assert((2 * TwoRev) % Prime == 1,      "2^-1 != TwoRev");

TimeDomain init(const std::vector<int>& number){
  constexpr int input_base_sz = 32;
  // assume base = 1 << 32
  TimeDomain td;
  td.reserve(N);
  ull tmp = 0;
  int shift = 0;
  for(auto digit:number) {
    tmp += digit << shift;
    shift += 32;
    while(shift < truck_sz){
      td.push_back(tmp & (truck - 1));
      tmp >>= truck_sz;
      shift -= truck_sz;
    }
  }
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

static std::unordered_map<int, ull> root_table;
ull get_root(int size){
  auto & result = root_table[size];
  if(result == 0){
    ull subroot = root_table[size/2];
    result = subroot * subroot % Prime;
  }
  return result;
}

ull get_sizeRev_table(int size){
  static std::unordered_map<int, ull> sizeRev_table{{2, TwoRev}};
  auto & result = sizeRev_table[size];
  if(result == 0){
    ull halfRev = sizeRev_table[size];
    result = halfRev * halfRev % Prime;
  }
  return result;
}

FreqDomain fast_fourier_transform(const TimeDomain& td, int size){
  if(size == 1){
    return FreqDomain {td[0]};
  }
  TimeDomain tdEven(size/2);
  TimeDomain tdOdd(size/2);
  for(int i = 0; i < size/2; i++){
    tdEven[i] = td[2*i];
    tdOdd[i] = td[2*i + 1];
  }
  FreqDomain even_fd = fast_fourier_transform(tdEven, size/2);
  FreqDomain odd_fd = fast_fourier_transform(tdOdd, size/2);
  FreqDomain result(size);
  
}

FreqDomain ftt(const TimeDomain& td);
TimeDomain rfft(const FreqDomain& fd);
FreqDomain multiply(const FreqDomain &fd1, const FreqDomain &fd2);