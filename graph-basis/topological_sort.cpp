#include "graph.h"
#include <vector>
#include <algorithm>
static int current_time = 0;
static constexpr auto white = color_t::white;
static constexpr auto black = color_t::black;

static std::vector<int> order;
static void dfs_visit_topo(Graph& graph, int ver_index){
	current_time++;
	auto& vertex = graph[ver_index];
	vertex.discover_time = current_time;
	vertex.color = black;
	FOR_EDGE(edge, vertex){
		auto& next_v = graph[edge->to];
		if(next_v.color == white){
			next_v.parent = vertex.from;
			dfs_visit_topo(graph, next_v.from);
		}
	}
	current_time++;
	vertex.finish_time = current_time;
	order.push_back(vertex.from);
}

static void depth_first_search_topo(Graph& graph){
	current_time = 0;
	for(auto& vertex : graph){
		vertex.color = white;
		vertex.parent = -1; 
	}
	for(auto vertex: graph){
		if(vertex.color == white){
			dfs_visit_topo(graph, vertex.from);
		}
	}
}

std::vector<int> topological_sort(Graph& graph){
	order.clear();
	order.reserve(graph.size());
	depth_first_search_topo(graph);
	std::reverse(order.begin(), order.end());
	return std::move(order);
}