#include <algorithm>
#include <deque>
#include <tuple>
#include <vector>
using namespace std;

double multipack(vector<tuple<size_t, double, size_t>> data, size_t limit) {
  // define limit * (status)
  // define status = index(pack_type) *
  vector<double> slot(limit + 1, 0);
  for (auto[weight, value, count] : data) {
#pragma omp parallel for
    for (int offset = 0; offset < weight; ++offset) {
      deque<pair<int, int>> q;
      for (int index = offset; index < limit + 1; index += weight) {
        if (!q.empty() && q.front().first == index + count * weight) {
          q.pop_front();
        }
        while (!q.empty()) {
          auto[last_w, last_v] = q.back();
          auto old_value = (index - last_w) / weight + last_v;
          if (old_value > slot[index])
            break;
          q.pop_back();
        }
        q.push_back(make_pair(index, value));
        auto[w, v] = q.back();
        auto max_value = (index - w) / weight + v;
        slot[index] = max_value;
      }
    }
  }
}
