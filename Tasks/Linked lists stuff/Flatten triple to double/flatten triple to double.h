#include "sll_utils.h"
#include <iostream>

struct TripleBox
{
    int value;
    TripleBox* next;
    TripleBox* previous;
    TripleBox* child;

    TripleBox(): value(0), next(nullptr),previous(nullptr),child(nullptr){}
    TripleBox(int value, TripleBox* next = nullptr, TripleBox* previous = nullptr, TripleBox* child = nullptr):value(0), next(next),previous(previous), child(child){}
};

struct DoubleBox
{
    int value;
    DoubleBox* next;
    DoubleBox* previous;
    DoubleBox():value(0), next(nullptr),previous(nullptr){}
    DoubleBox(int value, DoubleBox* next = nullptr, DoubleBox* previous = nullptr):value(0), next(next),previous(previous){}
};

DoubleBox* flatten(TripleBox* HeadTll)
{
    DoubleBox *head = nullptr;
    DoubleBox *tail = nullptr;

    TripleBox *current = HeadTll;

    if(HeadTll == nullptr)
    return nullptr;

    while (current != nullptr)
    {
        DoubleBox *NodeDll = new DoubleBox(HeadTll->value);

        if(tail == nullptr)
        head = tail = NodeDll;
        else
        {
            tail->next = NodeDll;
            NodeDll->previous = tail;
            tail = NodeDll;
        }

        if(current->child)
        {
            DoubleBox *child = flatten(current->child); 
            NodeDll->next = child;
            child->previous = NodeDll;
        }

        current = current->next; 
    }

    return head;
}
