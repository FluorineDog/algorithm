#include "graph.h"
#include <queue>
#include <iostream>
//using std::cerr;
using std::endl;
using std::queue;
void breath_first_search(Graph& graph, int source){	
	auto black = color_t::black;
	auto white = color_t::white;
	for(auto& vertex: graph){
		vertex.color = white;
		vertex.discover_time = inf;
	}
	queue<int> qq;
	graph[source].color = black;
	graph[source].discover_time = 0;
	graph[source].parent = -1;
	qq.push(source);
	while(qq.size()){
		auto& vertex = graph[qq.front()];
		qq.pop();
		// cerr << "v-" << vertex.from << endl;
		FOR_EDGE(edge, vertex){
			// cerr<<"\t-->" << edge->to << endl;
			auto& next_v = graph[edge->to];
			if(next_v.color == white){
				next_v.color = black;
				next_v.discover_time = vertex.discover_time+1;
				next_v.parent = vertex.from;
				qq.push(edge->to);
			}
		}
	}
}