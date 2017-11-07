#include <algorithm>
#include <deque>
#include <tuple>
#include <vector>
using namespace std;

double multipack(vector<tuple<size_t, double, size_t>> data, size_t limit) {
  // define limit * (status)
  // define status = weight(pack_type) *
  vector<double> slot(limit + 1, 0);
  for (auto[new_weight, new_value, new_count] : data) {
    // #pragma omp parallel for
    new_count += 1;
    for (size_t offset = 0; offset < new_weight; ++offset) {
      deque<pair<int, double>> q;
      // for (size_t weight = offset; weight < limit + 1; weight += new_weight)
      // {
      for (size_t index = 0; index < (limit + 1 - offset) / new_weight;
           index++) {
        auto weight = offset + index * new_weight;
        if (!q.empty() && q.front().first == index - new_count) {
          q.pop_front();
        }
        while (!q.empty()) {
          auto[last_i, last_v] = q.back();
          auto old_value = (index - last_i) * new_value + last_v;
          if (old_value > slot[weight])
            break;
          q.pop_back();
        }
        q.push_back(make_pair(index, slot[weight]));
        auto[best_i, best_v] = q.front();
        auto max_value = (index - best_i) * new_value + best_v;
        slot[index] = max_value;
      }
    }
  }
  return slot[limit];
}
