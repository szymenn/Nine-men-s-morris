#include "linked_list.h"

template <class T>
linked_list<T>::linked_list()
{
	first = NULL;
	last = NULL;
}

template <class T>
linked_list<T>::~linked_list()
= default;


template <class T>
void linked_list<T>::add(T data)
{
	if (!first) {
		first = new node<T>;
		first->data = data;
		first->next = NULL;
		last = first;
	}
	else {
		if (last == first) {
			last = new node<T>;
			last->data = data;
			last->next = NULL;
			first->next = last;
		}
		else {
			node<T>* ins_data = new node<T>;
			ins_data->data = data;
			ins_data->next = NULL;
			last->next = ins_data;
			last = ins_data;
		}
	}
}

//template <class T>
//T linked_list<T>::find(T data)
//{
//	node<T> *current = first;
//	while(current!=NULL)
//	{
//		if(current->data == data)
//		{
//			return 
//		}
//	}
//
//}


template <class T>
T linked_list<T>::get(const int index)
{
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
}

template <class T>
T linked_list<T>::operator[](const int index)
{
	return get(index);
}

template <class T>
int linked_list<T>::find_first(T value)
{
	node<int> *current = first;
	int index = 0;
	while(current != nullptr)
	{
		if(current->data == value)
		{
			return index;
		}
		++index;
	}
	return -1;
}

template <class T>
void linked_list<T>::replace(int index, T value)
{
	node<int> *current = first;
	int i = 0;
	while(i <= index)
	{
		current = current->next;
		++i;
	}
	current->data = value;
}


template <class T>
void linked_list<T>::print() const
{
	node<T> *current = first;
	while(current!=NULL)
	{
		std::cout << current->data<< " ";
		current = current->next;
	}
	putchar('\n');
}

template <class T>
bool linked_list<T>::contains(T value)
{
	node<T> *current = first;
	while(current!=NULL)
	{
		if(current->data == value)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

template <class T>
int linked_list<T>::length()
{
	node<T> *current = first;
	int i = 0;
	while(current!=NULL)
	{
		++i;
		current = current->next;
	}
	return i;
}

template <class T>
bool linked_list<T>::is_empty()
{
	if(length() == 0)
	{
		return true;
	}
	return false;
}




