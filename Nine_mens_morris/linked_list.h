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
	//{
		//if (!first) {
		//	first = new node<T>;
		//	first->data = data;
		//	first->next = NULL;
		//	last = first;
		//}
		//else {
		//	if (last == first) {
		//		last = new node<T>;
		//		last->data = data;
		//		last->next = NULL;
		//		first->next = last;
		//	}
		//	else {
		//		node<T>* ins_data = new node<T>;
		//		ins_data->data = data;
		//		ins_data->next = NULL;
		//		last->next = ins_data;
		//		last = ins_data;
		//	}
		//}
	//}
	//T find(T data);
	T get(const int index);
	/*{
		if (index == 0)
		{
			return this->first->data;
		}
		node<T>* current = this->first;
		for (int i = 0; i < index; ++i) 
		{
			current = current->next;
		}
		return current->data;
	}*/
	void print();
	bool contains(T value);
	T operator[](int index);
	//{
	//	return get(index);
	//}

};
