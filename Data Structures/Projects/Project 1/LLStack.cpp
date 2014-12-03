#include "LLStack.hpp"

LLStack::LLStack()
{
    top = 0;
    size = 0;
}

LLStack::~LLStack()
{
    char temp;
    while(!isEmpty())
    {
        pop(temp);
    }
}

void LLStack::push(const char& val)
{
    SNode * newSNode = new SNode(val);
    newSNode->next = top;
    top = newSNode;
}

bool LLStack::pop(char& val)
{
    if (isEmpty())
        return false;
    
    val = top->data;
    SNode* temp = top;
    top = top->next;
    delete temp;
    return true;
}

bool LLStack::isEmpty()
{
    return top == 0;
}
