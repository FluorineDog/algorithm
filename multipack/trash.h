#include <algorithm>
#include <deque>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

double multipack(vector<tuple<size_t, double, size_t>> data, size_t limit) {
  // define limit * (status)
  // define status = weight(pack_type) *
  vector<double> slot(limit + 1, 0);
  // for (auto[new_weight, new_value, new_count] : data) {
  for (auto t3 : data) {
    auto new_weight = get<0>(t3);
    auto new_value = get<1>(t3);
    auto new_count = get<2>(t3);
    // #pragma omp parallel for
    new_count += 1;
    // cerr << endl;
    for (size_t offset = 0; offset < new_weight; ++offset) {
      // cerr << endl;
      deque<pair<size_t, double>> q;
      q.clear();
      for (size_t weight = offset; weight < limit + 1; weight += new_weight) {
        // for (size_t index = 0; index <= (limit - offset) / new_weight;
        //  index++) {
        // auto weight = offset + index * new_weight;
        if (!q.empty() && q.front().first == weight - new_count * new_weight) {
          // cerr << "p";
          q.pop_front();
        }
        while (!q.empty()) {
          // auto[last_i, last_v] = q.back();
          auto t2 = q.back();
          auto last_w = get<0>(t2);
          auto last_v = get<1>(t2);
          auto old_value = (weight - last_w)/ new_weight * new_value + last_v;
          if (old_value > slot[weight])
            break;
          q.pop_back();
        }
        q.push_back(make_pair(weight, slot[weight]));
        // auto[best_i, best_v] = q.front();
        auto t22 = q.front();
        auto best_w = get<0>(t22);
        auto best_v = get<1>(t22);
        auto max_value = (weight - best_w)/new_weight * new_value + best_v;
        // std::cerr << "$" << max_value << "$";
        slot[weight] = max_value;
      }
    }
  }
  return *std::max_element(slot.begin(), slot.end());
}
