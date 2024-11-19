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
Box<T>* SLLtoDLL(DoubleBox<T> *head)
{
    if(head == nullptr)
    return nullptr;

    Box<T> *newHead = nullptr;
    Box<T> *newCURR = nullptr;

    DoubleBox<T>* current = head;

    while(current!=nullptr)
    {
        Box<T> *node = new Box<T>(current->data);

        if(newHead == nullptr)
        {
            newHead = node;
            newCURR = newHead;
        }
        else
        {
            newCURR->next = node;
            newCURR = newCURR->next;
        }

        current = current->next;
    }

    return newHead;
}