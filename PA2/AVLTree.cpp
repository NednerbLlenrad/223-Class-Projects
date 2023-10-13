// AVLTree.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "AVLTree.h"

using namespace std;

int main()
{
	vector<int> ascend;
	vector<int> descend;
	vector<int> random;

	for (int i = 1; i <= 100; i++)
	{
		ascend.push_back(i);
		descend.push_back(100 - i);
		random.push_back(i);
		i++;
	}

	random_device rd;
	mt19937 g(rd());
	shuffle(random.begin(), random.end(), g);

	AVLTree<int> ascendT;
	AVLTree<int> descendT;
	AVLTree<int> randomT;

	for (int i = 0; i < 50; i++)
	{
		ascendT.insert(ascend[i]);
		descendT.insert(descend[i]);
		randomT.insert(random[i]);
	}

	//Printing Height
	cout << "Ascending Tree Height:" << ascendT.getHeight() << endl;
	cout << "Decending Tree Height:" << descendT.getHeight() << endl;
	cout << "Random Tree Height:" << randomT.getHeight() << endl;

	//Printing Balance:
	cout << "Ascending Tree is balanced:" << ascendT.isBalanced() << endl;
	cout << "Decending Tree is balanced:" << descendT.isBalanced() << endl;
	cout << "Random Tree is balanced:" << randomT.isBalanced() << endl;

	// Verify contains() for odd and even numbers
	for (int i = 1; i <= 100; i++) {
		if (i % 2 == 1 && !ascendT.contains(i)) {
			std::cout << "My AVL tree implementation is wrong for odd number: " << i << std::endl;
		}
		else if (i % 2 == 0 && ascendT.contains(i)) {
			std::cout << "My AVL tree implementation is wrong for even number: " << i << std::endl;
		}
	}

	return 0;
}
