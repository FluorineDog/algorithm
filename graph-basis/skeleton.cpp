#include <iostream>
#include "graph.h"
#include <algorithm>
using std::cout;
using std::cerr;
using std::endl;
static int current_time = 0;
static constexpr auto white = color_t::white;
static constexpr auto black = color_t::black;



static int dfs_visit_skeleton(Graph& graph, int ver_index){
	current_time++;
	auto& vertex = graph[ver_index];
	vertex.discover_time = current_time;
	vertex.color = black;

	vertex.low = vertex.discover_time;
	int low = vertex.discover_time;
	FOR_EDGE(edge, vertex){
		auto& next_v = graph[edge->to];
		if(next_v.color == white){
			next_v.parent = vertex.from;
			int cur_low = dfs_visit_skeleton(graph, next_v.from);
			low = std::min(low, cur_low);
			vertex.low = std::min(vertex.low, cur_low);
		}
		else if(next_v.color == black){
			low = std::min(low, next_v.discover_time);
		}
	}
	current_time++;
	vertex.finish_time = current_time;
	return low;
}

static void depth_first_search_skeleton(Graph& graph){
	current_time = 0;
	for(auto& vertex : graph){
		vertex.color = white;
		vertex.parent = -1; 
	}
	for(auto vertex: graph){
		if(vertex.color == white){
			dfs_visit_skeleton(graph, vertex.from);
		}
	}
}

void test_skeleton(Graph& graph){
	depth_first_search_skeleton(graph);
	cout << endl;
	for(auto &v:graph){
		cout << v.from <<": "
			<<	v.discover_time
			<<	"->" << v.low << endl;
	}
}