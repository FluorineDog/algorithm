#include <iostream>
#include "fiboheap.h"
#include "min_bin_heap.h"
using namespace std;

std::default_random_engine e(111);
//std::default_random_engine e1(123);
//std::default_random_engine e2(123);
static const int size = 10000;
#include <vector>
int main(){
	//auto i = std::vector<int>(size);
	//FibonacciHeap heap;
	BinaryHeap biheap(e, size);
	//Iter iters[size] = {};
	// for(int i = 1; i < size; i++){
	// 	iters[i] = heap.insert(e1()%1000 + 10000);
	// }
	for(int i = 0; i < size*4000; ++i){
		int index = i%(size-1) + 1;
		T key = e()%size - i;
		//heap.decrease_key(iters[index], key);
		
		biheap.decrease_key(index, key);
		if(i%size == 0){
			cout << biheap.minimum() << ' '<< endl;
			//heap.extract_min();
			biheap.extract_min();
		}
	}
	
	// heap.decrease_key(iters[14], -1);
	return 0;
}