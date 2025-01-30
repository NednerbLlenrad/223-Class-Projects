#pragma once

#include "Node.h"

template <class T, class S>
class LinkedList
{
public:

	LinkedList(Node<T, S>* newHead = nullptr) : pHead(newHead) {}//Default constructor

	~LinkedList()//Deconstructor
	{
		Node<T, S>* curr = pHead;
		while (curr != nullptr)
		{
			Node<T, S>* pNext = curr->getNext();
			delete curr;
			curr = pNext;
		}
	}

	Node<T, S>* getHead() const;//Returns the head

	void setHead(Node<T, S>* newHead);//Sets the head of the list.

	bool isEmpty();//Checks if the list is empty

	void add(const T& cmd, const S& desc); //Inserting into the end of the list.

	bool remove(const T& cmd); //Removing a specific entry from the list.

	void clearList();//Clears the list

	int size();//Gets the size of the list
private:
	Node<T, S>* pHead;
};

template<class T, class S>
Node<T, S>* LinkedList<T, S>::getHead() const
{
	return this->pHead;
}

template<class T, class S>
void LinkedList<T, S>::setHead(Node<T, S>* newHead)
{
	this->pHead = newHead;
}

template<class T, class S>
bool LinkedList<T, S>::isEmpty()
{
	return this->pHead == nullptr;
}

template<class T, class S>
void LinkedList<T, S>::add(const T& cmd, const S& desc)
{
	if (isEmpty())
	{
		this->pHead = new Node<T, S>(cmd, desc);
	}
	else
	{
		Node<T, S>* pTemp = this->pHead;
		while (pTemp->getNext() != nullptr)
		{
			pTemp = pTemp->getNext();
		}
		Node<T, S>* newNode = new Node<T, S>(cmd, desc);
		pTemp->setNext(newNode);
	}
}

template<class T, class S>
bool LinkedList<T, S>::remove(const T& cmd)
{
	if (!isEmpty())
	{
		Node<T, S>* curr = this->pHead;
		Node<T, S>* prev = nullptr;
		while (curr != nullptr && curr->getCmd() != cmd)
		{
			prev = curr;
			curr = curr->getNext();
		}
		if (curr != nullptr)
		{
			if (prev == nullptr)
			{
				this->pHead = this->pHead->getNext();
				delete curr;
				return 1;
			}
			else
			{
				prev->setNext(curr->getNext());
				delete curr;
				return 1;
			}
		}
	}
	return 0;
}

template<class T, class S>
void LinkedList<T, S>::clearList()
{
	Node<T, S>* curr = this->pHead;
	while (curr != nullptr)
	{
		Node<T, S>* next = curr->getNext();
		delete curr;
		curr = next;
	}
	this->pHead = nullptr;
	return;
}

template<class T, class S>
int LinkedList<T, S>::size()
{
	int size = 0;
	Node<T, S>* pTemp = this->pHead;
	while (pTemp->getNext() != nullptr)
	{
		pTemp = pTemp->getNext();
		size++;
	}
	return size;
}
