// This code was taken from https://www.techiedelight.com/queue-implementation-cpp/
// The code has been modified from the original to provide opportunities to learn

#include "Queue.h"
#include "testQueue.h"
/*
Attributes
1 Single file but it is better practice to at least have a three file setup like main, queue.h, and queue.cpp
2 No real comments, had trouble figuring out what the code was supposed to be doing
3 Queues should be built with nodes for the head and the end. This was built with an array, which doesn't work as efficiently
4 There was no error handling for a lot of the functions which would cause the program to not function as intended if circumstances were right
5 No way to clear the queue and no copy constructor which are essential for creating a queue.
*/




// main function
int main()
{
    // call your test functions here!
    testSize();
    testIsEmpty();
    testisFull();

    testDequeue();
    testEnqueue();
    testPeek();
    return 0;
}

