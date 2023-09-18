#include "testQueue.h"
#include <iostream>


void testSize()
{
	queue qT;
	//Size 1
	qT.enqueue(2);
	if (qT.size() == 1)
	{
		cout << "Test Case Size 1: passed." << endl;
	}
	else
	{
		cout << "Test Case Size 1: failed." << endl;
	}

	qT.dequeue();
	//Size 0
	if (qT.size() == 0)
	{
		cout << "Test Case Size 0: passed." << endl;
	}
	else
	{
		cout << "Test Case Size 0: failed." << endl;
	}

}

void testIsEmpty()
{
	queue qT;
	//Size 0
	if (qT.isEmpty() == true)
	{
		cout << "Test Case on empty: passed." << endl;
	}
	else
	{
		cout << "Test Case on empty: failed." << endl;
	}

	//Size 1
	qT.enqueue(2);
	if (qT.isEmpty() == true)
	{
		cout << "Test Case on non-empty: failed." << endl;
	}
	else
	{
		cout << "Test Case on non-empty: passed." << endl;
	}
}

void testisFull()
{
	queue qT(3);
	qT.enqueue(1);
	qT.enqueue(2);
	if (qT.isFull() == true)
	{
		cout << "Test Case full: failed." << endl;
	}
	else
	{
		cout << "Test Case full: passed." << endl;
	}

	qT.enqueue(3);
	if (qT.isFull() == true)
	{
		cout << "Test Case non-full: passed." << endl;
	}
	else
	{
		cout << "Test Case non-full: failed." << endl;
	}
}

void testDequeue()
{
	queue qT;
	//Dequeue Empty
	qT.dequeue();
	cout << "Dequeue on Empty Passed." << endl;

	//Dequeue Non-Empty
	qT.enqueue(2);
	qT.enqueue(3);
	qT.dequeue();
	if (qT.size() == 1)
	{
		cout << "Dequeue nonEmpty Passed" << endl;
	}
	else
	{
		cout << "Dequeue nonEmpty Failed" << endl;
	}
}

void testEnqueue()
{
	queue qT(2);
	//Enqueue Empty
	qT.enqueue(2);
	qT.enqueue(3);
	qT.enqueue(4);
	cout << "Enqueue on Full passed." << endl;

	//Dequeue Non-Full
	qT.dequeue();
	qT.enqueue(3);
	if (qT.size() == 2)
	{
		cout << "Enque non Full Passed" << endl;
	}
	else
	{
		cout << "Dequeue non Full Failed" << endl;
	}
}

void testPeek()
{
	queue qT;
	if (qT.peek() == INT_MIN)
	{
		cout << "Peek on empty passed" << endl;
	}
	else
	{
		cout << "Peek on empty failed" << endl;
	}

	qT.enqueue(3);
	if (qT.peek() == 3)
	{
		cout << "Peek on nonempty passed" << endl;
	}
	else
	{
		cout << "Peek on nonempty failed" << endl;
	}
}