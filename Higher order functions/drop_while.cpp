#include <iostream>
#include <functional>

//връща нов списък, съдържащ всички елементи, започвайки от първия, за който предикатът predicate връща false

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T>
Box<T>* dropWhile(Box<T> *head, std::function<bool(const T&)> predicate)
{
    Box<T> *current = head;
    while(current && predicate(current->data))
    current = current->next;

    Box<T> *newHead = nullptr;
    Box<T> *newcurrent = nullptr;

    while(current)
    {
        Box<T> *node = new Box<T>(current->data);
        if(newHead == nullptr)
        {
            newHead = node;
            newcurrent = newHead;
        }
        else
        {
            node->next = newcurrent->next;
            newcurrent->next = node;
            newcurrent = newcurrent->next;
        }

        current = current->next;
    }

    return newHead;
}