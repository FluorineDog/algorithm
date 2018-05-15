#include "assert.h"
#include "fiboheap.h"
#include "min_bin_heap.h"
#include <iostream>
#include <random>
using namespace std;
#
std::default_random_engine e(111);
// std::default_random_engine e1(123);
// std::default_random_engine e2(123);
static const int size = 10000;
#include <vector>
int main() {
  // auto i = std::vector<int>(size);
  FibonacciHeap heap;
  // BinaryHdeap biheap(e2, size);
  Iter iters[size] = {};
  // cerr << "insert\n";
  for (int i = 1; i < size; i++) {
    T ss = e() % 1000 + 10000;
    iters[i] = heap.insert(ss);
    // cerr << ss << ' ';
  }
  // cerr<<endl;
  for (int i = 0; i < size * 4000; ++i) {
    int index = i % (size - 1) + 1;
    long long key = (e() % size) - i;
    // cerr << "decrease " <<iters[index]->data << " to "<< key << " at " <<
    // index<<endl;
    heap.decrease_key(iters[index], key);
    // cerr << heap.examinate()<<"**";
    // biheap.decrease_key(index, key);
    if (i % size == 0) {
      T dtest = heap.minimum();
      // cout << dtest << ' '<< endl;
      // cerr << "extract "<< dtest<<endl;
      heap.extract_min();
      // biheap.extract_min();
      // cerr << heap.examinate()<<"++";
    }
  }

  // heap.decrease_key(iters[14], -1);
  return 0;
}
