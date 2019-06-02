#pragma once
#include <iostream>
template<class T>
struct node {
	node<T>* next;
	T data;
};

template<class T>
class linked_list
{
public:
	node<T>* first;
	node<T>* last;
	linked_list<T>();
	~linked_list<T>();
	void add(T data);
	T get(const int index);
	int find_first(T value);
	void print() const;
	bool contains(T value);
	T operator[](int index);
	void replace(int index, T value);
	int length();
	bool is_empty();
};
