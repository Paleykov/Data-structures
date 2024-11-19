#include <iostream>
#include <functional>
#include <stdexcept>

//- връща първия елемент от списъка, удовлетворяващ предиката predicate

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T>
T& find(Box<T>* head, std::function<bool(const T&)> predicate) 
{
    if(!head)
    throw std::invalid_argument("Prazna ni e glavata!");
    
    Box<T> *current = head;

    while(current!=nullptr)
    {
        if(predicate(current->data) == true)
        return current->data;

        current = current->next;
    }

    throw std::invalid_argument("Nqma takuv element");
}