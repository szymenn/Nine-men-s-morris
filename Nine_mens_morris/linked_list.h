#pragma once
#include <iostream>
template<class T>
struct node {
	node<T>* next;
	node<T> *prev;
	T data;
};

template<class T>
class linked_list
{
	int size_;
public:
	node<T>* head;
	node<T>* tail;
	linked_list<T>();
	void add(T data);
	T get(int index);
	int find_first(T value);
	void print() const;
	bool contains(T value);
	T operator[](int index);
	void pop();
	int length() const;
	bool is_empty();
	void remove_internal(node<T>* pos);
};
