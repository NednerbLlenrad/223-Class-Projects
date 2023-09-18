#pragma once

#include <iostream>
#include <cstdlib>
using namespace std;

// define default capacity of the queue
#define SIZE 10


// Class for queue
class queue
{
    int* arr;		// array to store queue elements
    int capacity;	// maximum capacity of the queue
    int front;		// front points to front element in the queue (if any)
    int rear;		// rear points to last element in the queue
    int count;		// current size of the queue

public:
    queue(int size = SIZE)
    {
        arr = new int[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }// constructor
    ~queue()
    {
        delete arr; // you are not required to test this function;
        // however, are there issues with it?
    }// destructor

    void dequeue()
    {
        // check for queue underflow
        if (isEmpty())
        {
            cout << "UnderFlow\nProgram Terminated\n";
            return;
        }

        cout << "Removing " << arr[front] << '\n';

        front = (front + 1) % capacity;
        count--;
    }
    void enqueue(int item)
    {
        // check for queue overflow
        if (isFull())
        {
            cout << "OverFlow\nProgram Terminated\n";
            return;
        }

        cout << "Inserting " << item << '\n';

        rear = (rear + 1) % capacity;
        arr[rear] = item;
        count++;
    }
    int peek()
    {
        if (isEmpty())
        {
            cout << "UnderFlow\nProgram Terminated\n";
            return INT_MIN; 
        }
        return arr[front];
    }
    int size()
    {
        return count;
    }
    bool isEmpty()
    {
        return (size() == 0);
    }
    bool isFull()
    {
        return (size() == capacity);
    }
};
