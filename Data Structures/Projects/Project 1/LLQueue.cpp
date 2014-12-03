#include "LLQueue.hpp"

LLQueue::LLQueue()
{
    front = rear = 0;
}

LLQueue::~LLQueue()
{
    char temp;
    while (dequeue(temp)) {}
}

void LLQueue::enqueue(const char& val)
{
    QNode* newQNode = new QNode(val);
    if(front == 0)
        front = rear = newQNode;
    else
    {
        rear->next = newQNode;
        rear = newQNode;
    }
}

bool LLQueue::dequeue(char& num)
{
    if(isEmpty())
        return false;
    // set that value into data
    num = front->data;
    // move front to new location
    front = front->next;
    return true;
}

bool LLQueue::isEmpty()
{
    // return true if the front is null
    return front == 0;
}
