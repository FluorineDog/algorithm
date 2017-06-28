#ifndef DOG_NTT_HELPER_H_
#define DOG_NTT_HELPER_H_
#include "ntt.h"
constexpr int truck_sz = 4;  // vary with N
constexpr int n_sz = 4;     // maximum 20 with truck_sz = 6

constexpr ull N = 1 << n_sz;        
constexpr ull truck = 1 << truck_sz; 

static_assert(n_sz + 2 * truck_sz < 32, "truck limit exceeds");
constexpr ull Prime = 3*(1<<12) + 1;      // must be a prime
constexpr ull PrimitiveRoot = 11;         // must set accordingly
static_assert(Prime < (1ull << 32), "prime is too large");
static_assert(Prime % N == 1 ,  "prime should be the form of k * N + 1");

template <int exp>
struct Helper{
  static constexpr int half = exp / 2;
  static constexpr int keep = exp & 1;
  static constexpr ull pow(const ull base)
  {
    // return Helper<bas::;
    const ull rec = Helper<half>::pow(base);
    return rec*rec*(keep?base:1) % Prime;
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
constexpr ull Root = Helper<Kappa>::pow(PrimitiveRoot);                
constexpr ull RootRev = Helper<Prime-2>::pow(Root);                 
constexpr ull NRev  = Helper<Prime-2>::pow(N);                      
static_assert((N * NRev) % Prime == 1, "N^-1 != NRev");
static_assert((Root * RootRev) % Prime == 1,  "Root^-1 != RootRev");

#endif