#include "graph.h"
#include <queue>
#include <vector>
#include <stack>
#include <unordered_set>
#include <set>
using std::vector;
static int current_time = 0;
static constexpr auto white = color_t::white;
static constexpr auto black = color_t::black;
static std::stack<int> order;
using std::pair;
static void dfs_visit_scc_1(Graph& graph, int ver_index){
	current_time++;
	auto& vertex = graph[ver_index];
	vertex.discover_time = current_time;
	vertex.color = black;
	FOR_EDGE(edge, vertex){
		auto& next_v = graph[edge->to];
		if(next_v.color == white){
			next_v.parent = vertex.from;
			dfs_visit_scc_1(graph, next_v.from);
		}
	}
	current_time++;
	vertex.finish_time = current_time;
	order.push(vertex.from);
}

static void depth_first_search_scc_1(Graph& graph){
	current_time = 0;
	for(auto& vertex : graph){
		vertex.color = white;
		vertex.parent = -1; 
	}
	for(auto vertex: graph){
		if(vertex.color == white){
			dfs_visit_scc_1(graph, vertex.from);
		}
	}
}
static int current_scc_index;
static void dfs_visit_scc_2(Graph& graph, int ver_index){
	current_time++;
	auto& vertex = graph[ver_index];
	vertex.discover_time = current_time;
	vertex.color = black;
	FOR_EDGE(edge, vertex){
		auto& next_v = graph[edge->to];
		if(next_v.color == white){
			next_v.parent = vertex.from;
			dfs_visit_scc_2(graph, next_v.from);
		}
	}
	current_time++;
	vertex.finish_time = current_time;
	vertex.scc_index = current_scc_index;
}

static void depth_first_search_scc_2(Graph& graph){
	current_time = 0;
	current_scc_index = -1;
	for(auto& vertex : graph){
		vertex.color = white;
		vertex.parent = -1; 
	}
	
	while(!order.empty()){
		auto& vertex = graph[order.top()];
		order.pop();
		if(vertex.color == white){
			++current_scc_index;
			dfs_visit_scc_2(graph, vertex.from);
		}
	}
}



pair<Graph, vector<int>> strong_connected_component(Graph& graph){
	
	depth_first_search_scc_1(graph);
	auto graph_trans = transpose(graph);
	depth_first_search_scc_2(graph_trans);
	Graph scc_graph(current_scc_index + 1);
	std::set<std::pair<int, int>> edge_set;
	vector<int> scc_index_for_vertex(graph.size());


	for(auto& vertex: graph_trans){
		FOR_EDGE(edge, vertex){
			// construct edges of (G^T)^T
			edge_set.insert(std::make_pair(graph_trans[edge->to].scc_index, vertex.scc_index));
		}
		scc_index_for_vertex[vertex.from] = vertex.scc_index;
	}
	for(auto edge: edge_set){
		if(edge.first != edge.second){
			add_edge(scc_graph, edge.first, edge.second);
		}
	}

	return make_pair(std::move(scc_graph), scc_index_for_vertex);
}