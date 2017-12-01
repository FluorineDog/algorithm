#include <algorithm>
#include <random>
#include <vector>
// using namespace std;
#include <iostream>
using std::vector;
using T = long long;
using std::pair;
using std::make_pair;
using pti = pair<T, int>;

class BinaryHeap {

public:
  BinaryHeap(std::default_random_engine &e, int mysize) {

    size = mysize;
    data.resize(size);
    location.resize(size);
    for (int i = 1; i < size; ++i) {
      data[i] = std::make_pair(e() % 1000 + 10000, i);
      location[i] = i;
    }
    data[0] = std::make_pair(2147483647, 0);
    location[0] = 0;
    make_heap();
  }

  void fixup(int leaf) {
    int cur = leaf;
    while (cur > 1) {
      if (data[cur / 2] > data[cur]) {
        swap(data[cur / 2], data[cur]);
        cur /= 2;
      } else {
        break;
      }
    }
  }
  void make_heap() {
    for (int i = size / 2; i-- > 1;) {
      fixdown(i);
    }
  }

  void extract_min() {
    // std::cerr << "xxextract " << minimum() << " at " << std::endl;
    // std::cerr << data[1].second<<"**";
    // std::cerr<< data[1].first<<std::endl;
    swap(data[1], data[size - 1]);
    // std::cerr << data[size - 1].second<<"**";
    // std::cerr<< data[size - 1].first<<std::endl;
    --size;
    location[data[size].second] = 0;
    fixdown(1);
  }

  void decrease_key(int index, T new_data) {
    // std::cerr << "xxdecrease " << data[location[index]].first
    //	<< " to " << new_data << " at " << index <<std::endl;
    if (location[index] == 0) {
      return;
    }
    if (data[location[index]].first <= new_data) {
      return;
    }
    data[location[index]].first = new_data;
    fixup(location[index]);
  }

  void swap(pti &a, pti &b) {
    std::swap(a, b);
    std::swap(location[a.second], location[b.second]);
  }
  T minimum() { return data[1].first; }
  void fixdown(int root) {
    int cur = root;
    while (cur < size / 2) {
      int min = cur;
      if (data[min] > data[cur * 2]) {
        min = cur * 2;
      }
      if (data[min] > data[cur * 2 + 1]) {
        min = cur * 2 + 1;
      }
      if (min != cur) {
        swap(data[min], data[cur]);
        cur = min;
      } else {
        break;
      }
    }
  }

private:
  vector<pair<T, int>> data;
  vector<int> location;
  int size; // fake size since data[0] always null
};
