#pragma once
#include <iostream>

using namespace std;

template <class type>
class Stack
{
private:
	class Element
	{
	public:
		Element* next;//pointer to the next element in the list
		type data;//element value

		Element(type data = type(), Element* next = NULL)//creating element
		{
			this->data = data;
			this->next = next;
		}
	};
	Element* head;//pointer to the head of the list
	size_t size;


public:
	Stack()
	{
		head = NULL;//zeroing head element
		size = 0;
	}
	~Stack()
	{
		while (size != 0)
		{
			pop();
		}
	}
	void push(type data)
	{
		head = new Element(data, head);//element creation
		size++;
	}
	bool isEmpty()
	{
		if (head == NULL) return true;
		else return false;
	}
	type pop()
	{
		Element* current = head;//remember the first element
		head = head->next;//make the second element first
		type cur = current->data;
		delete current;//delete first element
		size--;
		return cur;
	}
	type top()
	{
		return head->data;
	}
};