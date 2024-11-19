#include <iostream>

template <typename T>
struct Box
{
    T data;
    Box *next;

    Box(T data, Box* next = nullptr): data(data), next(next){}
};

template <typename T>
void removeDups(Box<T> *&head)
{
    Box<T> *current = head->next;
    Box<T> *previous = head;

    while(current!=nullptr)
    {
        if(current->data == previous->data)
        {
            Box<T>* toDelete = current;
            previous->next = current->next;
            current = current->next;
            delete toDelete;
        }
        else
        {
            previous = previous->next;
            current = current->next;
        }
    }
}
