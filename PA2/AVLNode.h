#pragma once

#include <iostream>

template <class T>
class AVLNode
{
public:
	AVLNode(T value) : data(value), left(nullptr), right(nullptr), height(1)
	{}

	~AVLNode()
	{}

	T data;
	AVLNode* left;
	AVLNode* right;
	int height;
};