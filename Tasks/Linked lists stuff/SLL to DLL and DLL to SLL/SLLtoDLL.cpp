#include <iostream>

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T>
struct DoubleBox
{
    DoubleBox *next;
    DoubleBox *previous;
    T data;

    DoubleBox(T& data, Box *next = nullptr, Box *previous = nullptr): data(data), next(next), previous(previous){}
};

template <typename T>
DoubleBox<T>* SLLtoDLL(Box<T> *head)
{
    if(head == nullptr)
    return nullptr;

    DoubleBox<T> *newHead = nullptr;
    DoubleBox<T> *newCURR = nullptr;

    Box<T>* current = head;

    while(current!=nullptr)
    {
        DoubleBox<T> *node = new DoubleBox<T>(current->data);

        if(newHead == nullptr)
        {
            newHead = node;
            newCURR = newHead;
        }
        else
        {
            newCURR->next = node;
            node->previous = newCURR;
            newCURR = newCURR->next;
        }

        current = current->next;
    }

    return newHead;
}