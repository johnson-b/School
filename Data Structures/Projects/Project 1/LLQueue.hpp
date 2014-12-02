#ifndef LLQUEUE_H
#define LLQUEUE_H

// class for individual nodes
class QNode
{
public:
    char data;
    QNode* next;
    
    QNode(const char& val)
    {
        data = val;
        next = 0;
    }
};

class LLQueue
{
public:
    // Members for LLQueue
    QNode* front;
    QNode* rear;
    
    // Functions for LLQueue
    
    // Constructor
    LLQueue();
    
    // Deconstructor
    ~LLQueue();
    
    // Enqueue
    void enqueue(const char&);
    
    // Dequeue
    bool dequeue(char& val);
    
    // isEmpty
    bool isEmpty();
};

#endif
