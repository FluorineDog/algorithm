#include "fiboheap.h"
#include <map>
#include <assert.h>
using std::swap;
// T FibonacciHeap::nega_inf = std::numeric_limits<T>::min();
FibonacciHeap::FibonacciHeap()
	:root(nullptr)
{
}

Iter FibonacciHeap::insert(T x)
{
	this->length++;
	auto node = new FiboHeapNode(x);
	add_to_root_list(node);
	if (!root || x < minimum()) {
		root = node;
	}
	return node;
}

T FibonacciHeap::minimum() {
	return root->data;
}

bool FibonacciHeap::extract_min()
{
	if (!root) {
		return false;
	}
	length--;
	auto min = root;
	// if there are chlidren
	if (min->child) {
		auto child_iter = min->child;
		while (child_iter->parent) {
			// damn algorithm to keep parent
			child_iter->parent = nullptr;
			child_iter = child_iter->next_node;
		}
		merge_list(root, min->child);
		min->child = nullptr;
	}
	if (min->next_node == min) {
		root = nullptr;
	}
	else {
		min->next_node->prev_node = min->prev_node;
		min->prev_node->next_node = min->next_node;
		root = min->next_node;
		consolidate();
	}
	min->data = nega_inf - 1;
	return true;
}

FibonacciHeap FibonacciHeap::merge(FibonacciHeap&& heap_a, FibonacciHeap&& heap_b)
{
	FibonacciHeap heap;
	// deal with empty heap
	if (!heap_a.root) {
		return std::move(heap_b);
	}
	else if (!heap_b.root) {
		return std::move(heap_a);
	}
	merge_list(heap_a.root, heap_b.root);
	heap.root = heap_a.minimum() < heap_b.minimum() ? heap_a.root : heap_b.root;
	return heap;
}

void FibonacciHeap::decrease_key(Iter iter, T key)
{
	if(iter->data == nega_inf -1){
		return;
	}
	Iter origin = iter;
	if(iter->data < key){
		return;
	}
	iter->data = key;
	iter->mark = true;
	while(iter->mark){
		auto parent = iter->parent;
		if(parent == nullptr){
			break;
		}
		if(iter->next_node == iter){
			parent->child = nullptr;
		}
		else {
			parent->child = iter->next_node;
			iter->next_node->prev_node = iter->prev_node;
			iter->prev_node->next_node = iter->next_node;
		}
		parent->degree--;
		iter->mark = false;
		add_to_root_list(iter);
		iter = parent;
	}
	iter->mark = true;
	if(key < minimum()){
		root = origin;
	}
}

void FibonacciHeap::remove(Iter iter)
{
	decrease_key(iter, nega_inf);
	extract_min();
}

void FibonacciHeap::clear()
{
	//do nothing until
}

Iter FibonacciHeap::add_to_root_list(Iter node)
{
	if (root == nullptr) {
		node->next_node = node;
		node->prev_node = node;
		root = node;
		return node;
	}
	node->next_node = root->next_node;
	node->prev_node = root;
	node->next_node->prev_node = node;
	node->prev_node->next_node = node;
	node->parent = nullptr;
	return node;
}

Iter FibonacciHeap::adopt_child(Iter parent, Iter node)
{
	Iter& child = parent->child;
	if (child == nullptr) {
		node->next_node = node;
		node->prev_node = node;
		child = node;
	}
	else{
		node->next_node = child->next_node;
		node->prev_node = child;
		node->next_node->prev_node = node;
		node->prev_node->next_node = node;
	}
	node->parent = parent;
	parent->degree++;
	return node;
	
}

void FibonacciHeap::merge_list(Iter list_a, Iter list_b)
{
	auto beg_a = list_a->next_node;
	auto end_a = list_a;
	auto beg_b = list_b->next_node;
	auto end_b = list_b;
	end_a->next_node = beg_b;
	end_b->next_node = beg_a;
	beg_a->prev_node = end_b;
	beg_b->prev_node = end_a;
}


void FibonacciHeap::consolidate()
{
	Iter container[50] = {};
	auto slot = [&](Iter cur)->Iter& {return container[cur->degree]; };
	auto current = root;
	bool isFinished = false;
	while (!isFinished)
	{
		if (slot(current) == nullptr) {
			slot(current) = current;
			current = current->next_node;
			continue;
		}
		else if (slot(current) == current) {
			break;
		}
		auto next = current->next_node;
		isFinished = slot(next) == next;
		while (slot(current)){
			auto parent = slot(current);
			slot(current) = nullptr;
			if (current->data < parent->data) {
				swap(parent, current);
			}
			current->next_node->prev_node = current->prev_node;
			current->prev_node->next_node = current->next_node;
			adopt_child(parent, current);
			current = parent;
		}
		slot(current) = current;
		if(current->data < root->data){
			root = current;
		}
		current = next;
	}
}
static int count_node;
bool check_node(FiboHeapNode* first_son, FiboHeapNode* parent){
	count_node++;
	auto cur = first_son;
	int degree = parent->degree;
	if(first_son == nullptr){
		return degree == 0;
	}
	if(parent != first_son->parent){
		return false;
	}
	do{
		if(check_node(cur->child, cur) == false){
			return false;
		}
		cur = cur->next_node;
		degree--;
	}while(cur != first_son);
	return degree == 0;
}
#include <iostream>
bool FibonacciHeap::examinate(){
	count_node = 0;
	//static int unique = 0;
	//std::cerr <<"UNI"<< unique++<<"ID ";
	auto cur = root;
	if(root){
		do{
			if(check_node(cur->child, cur) == false){
				return false;
			}
			cur = cur->next_node;
		}while(cur != root);
	}
	return this->length == count_node;
}
