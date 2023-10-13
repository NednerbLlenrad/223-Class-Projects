// AVLTree.h : Include file for standard system include files,
// or project specific include files.

#pragma once

//Standard Libraries
#include <iostream>
#include <algorithm>
//My Header Files
#include "AVLNode.h"

template <class T>
class AVLTree
{
public:
	AVLTree() : mpRoot(nullptr)
	{}

	~AVLTree()
	{
		deleteTree(mpRoot);
	}
	//Basic functions allowing for abstraction of function use
	int getHeight() const
	{
		return getHeight(mpRoot);
	}

	void insert(const T& value)
	{
		mpRoot = insert(mpRoot, value);
	}

	bool contains(const T& value) const
	{
		return contains(mpRoot, value);
	}

	bool isBalanced() const
	{
		return isBalanced(mpRoot);
	}

private:
	AVLNode<T>* mpRoot;

	void deleteTree(AVLNode<T>* node);

	int getBalanceFactor(AVLNode<T>* node) const;

	AVLNode<T>* rightRotation(AVLNode<T>* node);

	AVLNode<T>* leftRotation(AVLNode<T>* node);

	int getHeight(AVLNode<T>* node) const;

	AVLNode<T>* insert(AVLNode<T>* node, const T& value);

	bool contains(AVLNode<T>* node, const T& value) const;

	bool isBalanced(AVLNode<T>* node) const;

};

template<class T>
inline void AVLTree<T>::deleteTree(AVLNode<T>* node)
{
	if (node == nullptr)
	{
		return;
	}
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

template<class T>
inline int AVLTree<T>::getBalanceFactor(AVLNode<T>* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return (getHeight(node->left) - getHeight(node->right));
}

template<class T>
inline AVLNode<T>* AVLTree<T>::rightRotation(AVLNode<T>* node)
{
	AVLNode<T>* leftNode = node->left;
	AVLNode<T>* rightNode = leftNode->right;

	leftNode->right = node;
	node->left = rightNode;

	node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	leftNode->height = 1 + std::max(getHeight(leftNode->left), getHeight(leftNode->right));

	return leftNode;
}

template<class T>
inline AVLNode<T>* AVLTree<T>::leftRotation(AVLNode<T>* node)
{
	AVLNode<T>* rightNode = node->right;
	AVLNode<T>* leftNode = rightNode->left;

	rightNode->left = node;
	node->right = leftNode;

	node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	rightNode->height = 1 + std::max(getHeight(rightNode->left), getHeight(rightNode->right));

	return rightNode;
}

template<class T>
inline int AVLTree<T>::getHeight(AVLNode<T>* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return node->height;
}

template<class T>
inline AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, const T& value)
{
	if (node == nullptr)
	{
		return new AVLNode<T>(value);
	}

	if (value < node->data)
	{
		node->left = insert(node->left, value);
	}
	else if (value > node->data)
	{
		node->right = insert(node->right, value);
	}
	else
	{
		return node;
	}

	node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

	int balance = getBalanceFactor(node);

	if (balance > 1)
	{
		if (value < node->left->data)
		{
			return rightRotation(node);
		}
		else
		{
			node->left = leftRotation(node->left);
			return rightRotation(node);
		}
	}
	
	if (balance < -1)
	{
		if (value > node->right->data)
		{
			return leftRotation(node);
		}
		else
		{
			node->right = rightRotation(node->right);
			return leftRotation(node);
		}
	}

	return node;
}

template<class T>
inline bool AVLTree<T>::contains(AVLNode<T>* node, const T& value) const
{
	if (node == nullptr)
	{
		return false;
	}

	if (value == node->data)
	{
		return true;
	}
	else if (value < node->data)
	{
		return contains(node->left, value);
	}
	else
	{
		return contains(node->right, value);
	}
}

template<class T>
inline bool AVLTree<T>::isBalanced(AVLNode<T>* node) const
{
	if (node == nullptr)
	{
		return true;
	}

	int balance = getBalanceFactor(node);

	if (std::abs(balance) > 1)
	{
		return false;
	}

	return isBalanced(node->left) && isBalanced(node->right);
}

