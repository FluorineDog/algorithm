#include <string>
#include <iostream>
#include "ntt_helper.h"
using namespace std;
void output(const char key[], long long value){
	cout << "constexpr ull " << key << " = " << value << ";" << endl;
}

#define PUT(key) output(#key , (key))
int main(){
	cout<< R"(#ifndef DOG_NTT_C11_HELPER_H_
#define DOG_NTT_C11_HELPER_H_

#include "ntt.h"
)";
	PUT(Prime);
	PUT(N);
	PUT(n_sz);
	PUT(truck);
	PUT(truck_sz);
	PUT(Kappa);
	PUT(Root);
	PUT(RootRev);
	PUT(NRev);
	cout<<R"(#endif )" << endl;
	return 0;
}