#include "graph.h"

static int current_time = 0;
static constexpr auto white = color_t::white;
static constexpr auto black = color_t::black;

static void dfs_visit(Graph& graph, int ver_index){
	current_time++;
	auto& vertex = graph[ver_index];
	vertex.discover_time = current_time;
	vertex.color = black;
	FOR_EDGE(edge, vertex){
		auto& next_v = graph[edge->to];
		if(next_v.color == white){
			next_v.parent = vertex.from;
			dfs_visit(graph, next_v.from);
		}
	}
	current_time++;
	vertex.finish_time = current_time;
}

void depth_first_search(Graph& graph){
	current_time = 0;
	for(auto& vertex : graph){
		vertex.color = white;
		vertex.parent = -1; 
	}
	for(auto vertex: graph){
		if(vertex.color == white){
			dfs_visit(graph, vertex.from);
		}
	}
}