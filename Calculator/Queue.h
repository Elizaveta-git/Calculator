#pragma once
#include <iostream>

using namespace std;

template <class type>
class Queue
{
private:
	class Node
	{
	public:
		Node* next;//pointer to the next element in the list
		type data;//element value
		Node(type data = type(), Node* next = NULL)//creating element
		{
			this->data = data;
			this->next = next;
		}
	};
	Node* head;//pointer to the end of the list
	size_t size;
public:
	Queue()
	{
		head = NULL;//zeroing head element
		size = 0;
	}
	~Queue()
	{
		while (size != 0)
		{
			pop();
		}
	}
	void push(type data)
	{
		if (isEmpty() != 0)//insert first element if list is empty
		{
			head = new Node(data);//element creation
			size++;
		}
		else//insert element in the end of the list
		{
			Node* current = head;//creation a new element
			while (current->next != NULL)//while the next element exists, move throuth the list to the end
			{
				current = current->next;
			}
			current->next = new Node(data);//creating the last element
			size++;
		}
	}
	bool isEmpty()
	{
		if (head == NULL) return true;
		else return false;
	}
	type pop()
	{
		Node* current = head;//remember the first element
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
	size_t get_size()
	{
		return size;
	}

	void print()
	{
		Node* current = this->head;//go to the beginning of the list
		while (current != NULL)//while new element exist
		{
			cout << current->data << " ";//display the value of the element
			current = current->next;//move on to the next element
		}
	}
};