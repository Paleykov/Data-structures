#include <iostream>
#include <functional>

// проверява дали има поне един елемент в списъка, удовлетворяващ предиката predicate (квантор за съществуване)

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};


template <typename T>
bool any(Box<T> *head, std::function<bool(const T&)> predicate)
{
    Box<T> *current = head;

    while(current!=nullptr)
    {
        if(predicate(current->data))
        return true;
    }

    return false;
}