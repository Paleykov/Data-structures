#include <iostream>

template <typename T>
struct Box
{
    Box* next;
    T data;

    Box(T data, Box* next = nullptr): data(data), next(next){}
};

template <typename T>
void reverseSLL(Box<T> *&head)
{
    Box<T>* temp = nullptr;
    Box<T>* prev = nullptr;
    Box<T>* current = head;

    while(current!=nullptr)
    {
        temp = current->next;
        current->next = temp;
        prev = current;
        current = temp;
    }

    head = prev;
}