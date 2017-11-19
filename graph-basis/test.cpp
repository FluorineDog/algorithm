#include <iostream>
#include <sstream>
#include "graph.h"
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
int main(){
	int vertex_size;
	cin >> vertex_size;
	Graph graph(vertex_size);
	std::string line;
	while(std::getline(cin, line)){
		std::istringstream line_in(line);
		int from, to;
		if(line_in>>from){
			while(line_in>>to){
				cerr<<from<<'-'<<to<<' ';
				add_edge(graph, from, to);
				add_edge(graph, to, from);
			}
		}
	}
	//cerr << "hehe " << graph[3].edges<< endl;
	//auto temp = transpose(graph);
	depth_first_search(graph);
	breath_first_search(graph, 2);
	test_skeleton(graph);
	cout <<endl;

    return 0;
}