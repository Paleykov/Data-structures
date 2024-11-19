#include <iostream>

template <typename T>
struct DoubleBox
{
    DoubleBox* next;
    DoubleBox* previous;
    T data;

    DoubleBox(T data, DoubleBox* next = nullptr, DoubleBox* previous = nullptr): next(next), previous(previous), data(data){}
};

template <typename T>
void ReverseDll(DoubleBox<T> *&head)
{
    struct Node* temp = nullptr;
    struct Node* current = head;
 
    while (current != nullptr) 
    {
        temp = current->previous;
        current->previous = current->next;
        current->next = temp;
        current = current->previous;
    }
 
    if (temp != nullptr)
        head = temp->prev;
}