#ifndef LLSTACK_H
#define LLSTACK_H

// class to implement individual node
class SNode
{
public:
    char data;
    SNode* next;
    
    SNode(const char& val)
    {
        data = val;
        next = 0;
    }
};

class LLStack
{
public:
    // used for top of stack
    SNode* top;
    // number to keep track of size of list
    int size;
    
    // constructor
    LLStack();
    // deconstructor
    ~LLStack();
    void push(const char&);
    bool pop(char&);
    bool isEmpty();
};




#endif
