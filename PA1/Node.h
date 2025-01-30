#pragma once

#include <iostream>

//Standard Node Template with two parameters for commands and descriptions
template <class T, class S>
class Node
{
public:
	Node(const T& cmd, const S& desc) : command(cmd), description(desc), next(nullptr) {}//Node constructor

	T getCmd() const;//Gets the command

	S getDesc() const;//Gets the description

	Node<T, S>* getNext() const;//Gets the next node

	void setNext(Node<T, S>* newNext);//Sets the next node

	void setCmd(T newData);//Sets the command of the current node

	void setDesc(S newData);//Sets the description of the current node
private:
	T command;
	S description;
	Node* next;
};

//Node Functions as decribed and ordered above.
//Simple return statements and set statements.
template<class T, class S>
T Node<T, S>::getCmd() const
{
	return this->command;
}

template<class T, class S>
S Node<T, S>::getDesc() const
{
	return this->description;
}

template<class T, class S>
Node<T, S>* Node<T, S>::getNext() const
{
	return this->next;
}

template<class T, class S>
void Node<T, S>::setNext(Node<T, S>* newNext)
{
	if (this != nullptr)
	{
		this->next = newNext;
	}
}

template<class T, class S>
void Node<T, S>::setCmd(T newData)
{
	this->command = newData;
}

template<class T, class S>
void Node<T, S>::setDesc(S newData)
{
	this->description = newData;
}
