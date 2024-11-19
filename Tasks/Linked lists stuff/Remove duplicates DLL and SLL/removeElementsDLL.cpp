#include <iostream>

template <typename T>
struct DoubleBox
{
    T data;
    DoubleBox *next;
    DoubleBox *previous;

    DoubleBox(T data, DoubleBox* next = nullptr, DoubleBox* previous = nullptr): data(data), next(next), previous(previous){}
};

template <typename T>
void removeAllBoxesWithValueN(DoubleBox<T> *&head, T n)
{
    if(head == nullptr)
    return;

    while(head!=nullptr && head->data == n)
    {
        DoubleBox<T> *toDelete = head;
        head->next->previous = nullptr;
        head = head->next;
        delete toDelete;
    }

    if(head == nullptr)
    return;

    DoubleBox<T> *current = head;
    DoubleBox<T> *previous = nullptr;

    while(current!=nullptr)
    {   
        if(current->data == n && current->next == nullptr)
        {
            DoubleBox<T> *toDelete = current;
            previous->next = nullptr;
            delete toDelete;
            return;
        }
        if(current->data == n)
        {
            DoubleBox<T>* toDelete = current;
            previous->next = current->next;
            current->next->previous = previous;
            current = current->next;
            delete toDelete;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}
