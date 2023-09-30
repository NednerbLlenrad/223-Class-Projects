// MA2.h : Include file for standard system include files,
// or project specific include files.

#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {
		destroyBST(this->_root);
	}
	//Helper function to recursively destroy the bst
	void destroyBST(Node<T>* current)
	{
		if (current != nullptr)
		{
			destroyBST(current->left);
			destroyBST(current->right);
			delete current;
		}
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		if (this->_root == nullptr)//Checks if BST is null
		{
			return;
		}
		else
		{
			int h = height();//Gets the height of the levels in the BST
			for (int i = 1; i <= h + 1; i++)//Loops through level by level until it reaches the height
			{
				printLevel(_root, i);//Print helping function for recursive printing
				cout << endl;
			}
		}
	}
	//Recursive function to print the level
	void printLevel(Node<T>* current, int curLev)
	{
		if (current == NULL)//Checks if the node is null
		{
			return;
		}
		else if (curLev == 1)//Checks if the cur level is equal to 1
		{
			cout << current->value << ' ';//Prints the number if it is
		}
		else if (curLev > 1)//if level is equal to 1, then it gets the next level's left and right value
		{
			printLevel(current->left, curLev - 1);//repeats untl the level is 1 and then prints the node value
			printLevel(current->right, curLev - 1);
		}
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {
		int maxLen = 0;//Integer to check for max length
		vector<T> currentPath;//Vector to store current path being traversed
		vector<T> maxPath;//Vector to store the found maximum path

		findMax(this->_root, currentPath, maxPath, maxLen);

		for (int i = 0; i < maxPath.size(); i++)//Traverses the vector printing each value
		{
			cout << maxPath[i] << ' ';
		}
		cout << endl;
	}
	//Helper function to recursively find the max path
	void findMax(Node<T>* current, vector<T>& curPath, vector<T>& maxPath, int& maxLen)
	{
		if (current == nullptr)//Checks for nullptr
		{
			return;
		}

		curPath.push_back(current->value);//Adds the first value

		if (current->left == nullptr && current->right == nullptr)//Checks if it has reached the end of a pathway
		{
			if (curPath.size() > maxLen)//Checks for size
			{
				maxLen = curPath.size();//Updates length and path
				maxPath = curPath;
			}
		}

		findMax(current->left, curPath, maxPath, maxLen);//Traverses left and right sides
		findMax(current->right, curPath, maxPath, maxLen);

		curPath.pop_back();//Removes the last node to traverse previous subtrees
	}


	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T value) {
		return contains(this->_root, value);
	}
	//Recursive Contains helper
	bool contains(Node<T>* current, T value)
	{
		if (current == nullptr)
		{
			return false;
		}

		if (value == current->value)
		{
			return true;
		}

		if (value < current->value)
		{
			return contains(current->left, value);
		}
		else
		{
			return contains(current->right, value);
		}
	}
};

#endif

