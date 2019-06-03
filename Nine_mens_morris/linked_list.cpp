#include "linked_list.h"

template <class T>
linked_list<T>::linked_list()
{
	head = NULL;
	tail = NULL;
	size_ = 0;
}

template <class T>
void linked_list<T>::add(T data)
{
	if (!head) {
		head = new node<T>;
		head->data = data;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	else {
		if (tail == head) {
			tail = new node<T>;
			tail->data = data;
			tail->next = NULL;
			tail->prev = head;
			head->next = tail;
		}
		else {
			node<T>* ins_data = new node<T>;
			ins_data->data = data;
			ins_data->next = NULL;
			ins_data->prev = tail;
			tail->next = ins_data;
			tail = ins_data;
		}
	}
	size_++;
}

template <class T>
T linked_list<T>::get(const int index)
{
	if (index == 0)
	{
		return this->head->data;
	}
	node<T>* current = this->head;
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
	node<int> *current = head;
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
	remove_internal(tail);
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

		if (pos == head)
			head = pos->next;

		if (pos == tail)
			tail = pos->prev;

		delete pos;

		size_--;
	}
}


template <class T>
void linked_list<T>::print() const
{
	node<T> *current = head;
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
	node<T> *current = head;
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




