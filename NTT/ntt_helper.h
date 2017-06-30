#ifndef DOG_NTT_HELPER_H_
#define DOG_NTT_HELPER_H_

#include "ntt.h"
constexpr int truck_sz = 3;   // vary with N
constexpr int n_sz = 25;      // maximum 20 with truck_sz = 6

constexpr ull N = 1ull << n_sz;        
constexpr ull truck = 1ull << truck_sz; 

constexpr bool is_prime(const ull x){
  constexpr ull ceiling = 1ull<<16;
  const ull upper_bound = x/2 < ceiling? x/2 : ceiling;
  for(int i = 2; i < upper_bound; ++i){
    if(x%i == 0) return false;
  }
  return x > 1;
}

constexpr ull prime_gen(const ull n, const ull scalar) {
  for(ull k = scalar; k < scalar + 30; ++k){
    // probability 0.2 for each trial
    ull prime = k * n + 1;
    if(is_prime(prime)) return prime;
  }
  return 3;
}


constexpr ull Prime = prime_gen(N, truck*truck);
static_assert(N*truck*truck < Prime, "truck limit exceeds");
static_assert(Prime < (1ull << 32),  "prime is too large");
static_assert(Prime % N == 1 ,       "prime should be the form of k * N + 1");

template <ull exp>
struct Helper{
  static constexpr ull half = exp / 2ull;
  static constexpr ull keep = exp & 1ull;
  static constexpr ull pow(const ull base)
  {
    const ull rec = Helper<half>::pow(base);
    return rec*rec % Prime * (keep?base:1) % Prime;
  }
};

template <>
struct Helper<1>{
  static constexpr ull pow(const ull base){return base;}
};

template <>
struct Helper<0>{
  static constexpr ull pow(const ull){return 1;}
};

constexpr ull Kappa = (Prime - 1) / N;
constexpr bool is_nth_root(const ull root){
  return Prime-1 == Helper<N/2>::pow(root);
}

constexpr ull nth_root_gen(){
  for(ull proot = 2; proot < 32; ++proot){
    ull root = Helper<Kappa>::pow(proot);
    if(is_nth_root(root)) return root;
  }
  return 0;
}

constexpr ull Root = nth_root_gen();
constexpr ull RootRev = Helper<Prime-2>::pow(Root); 
constexpr ull NRev  = Helper<Prime-2>::pow(N);                     
static_assert(Helper<Prime-1>::pow(N) == 1,       "not a prime");
static_assert(Helper<N>::pow(Root) == 1,          "may not be a prime");
static_assert(Helper<N/2>::pow(Root) == Prime-1,  "may not be a primitive root");
static_assert((N * NRev) % Prime == 1,            "N^-1 != NRev");
static_assert((Root * RootRev) % Prime == 1,      "Root^-1 != RootRev");

#endif