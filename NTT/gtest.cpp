#include "ntt.h"
#include "ntt_helper.h"
#include <random>
#include <cassert>
#include <gtest/gtest.h>

using std::vector;

TEST(Dog, case1){
  unsigned NUM = (truck_sz << n_sz) / 32 / 2;

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
	
}

TEST(Dog, case2){
	EXPECT_EQ(1,2);
}
