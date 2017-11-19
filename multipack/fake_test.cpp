#include "trash.h"
int main(){
     size_t N, limit;
     vector<tuple<size_t, double, size_t>> data;
     for(int i = 0; i < N; ++i){
         size_t weight;
         double value;
         size_t count;
         cin >> weight >> value >> count;
         data.emplace_back(weight, value, count);
     }
     cout << multipack(std::move(data), limit) << endl;
 }
