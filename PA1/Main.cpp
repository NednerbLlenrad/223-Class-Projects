//Brenden Darnell PA1 - Memory Game

/*
Questions:
1. Advantages and Disadvantages of Linked List
	Adv: Commands can easily be added and removed, due to the dynamic memory.
	Dis: Has to be traversed through to find commands. Something more akin to a binary tree would be able to be faster.
2. Advantage and Disadvantage of Array
	Adv: Allows for profiles to be retrieved and accessed very quickly and easily by using indexes.
	Dis: Has a fixed size only allowing for a set amount of profiles.
*/

#include "MemoryGame.h"
#include <iostream>

using namespace std;

int main()
{
	MemoryGame App;
	App.runApp();

	return 0;
}

