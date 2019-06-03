#include "linked_list.h"

template <class T>
linked_list<T>::linked_list()
{
	first = NULL;
	last = NULL;
	size_ = 0;
}

template <class T>
void linked_list<T>::add(T data)
{
	if (!first) {
		first = new node<T>;
		first->data = data;
		first->next = NULL;
		first->prev = NULL;
		last = first;
	}
	else {
		if (last == first) {
			last = new node<T>;
			last->data = data;
			last->next = NULL;
			last->prev = first;
			first->next = last;
		}
		else {
			node<T>* ins_data = new node<T>;
			ins_data->data = data;
			ins_data->next = NULL;
			ins_data->prev = last;
			last->next = ins_data;
			last = ins_data;
		}
	}
	size_++;
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
void linked_list<T>::pop()
{
	remove_internal(last);
}

template <class T>
void linked_list<T>::remove_internal(node<T>* pos)
{
	if (pos)
	{
		if (pos->prev)
			pos->prev->next = pos->next;

		if (pos->next)
			pos->next->prev = pos->prev;

		if (pos == first)
			first = pos->next;

		if (pos == last)
			last = pos->prev;

		delete pos;

		size_--;
	}
}


template <class T>
void linked_list<T>::print() const
{
	node<T> *current = first;
	while(current != nullptr)
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
	while(current!= nullptr)
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
int linked_list<T>::length() const
{
	return size_;
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




