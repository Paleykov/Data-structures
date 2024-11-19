#include <iostream>
#include <functional>

//създава нов свързан списък с елементите, удовлетворяващи предиката predicate

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T>
Box<T>* filter(Box<T> *head, std::function<bool(const T&)> predicate)
{
    Box<T> *newHead = nullptr;
    Box<T> *currentNew = nullptr;
    Box<T> *current = head;
    
    while(current != nullptr)
    {
        if(predicate(current->data) == true)
        {
            Box<T> *node = new Box<T>(current->data);

            if(newHead == nullptr)
            {
                newHead = node;
                currentNew = newHead;
            }
            else
            {
                node->next = currentNew->next;
                currentNew->next = node;
                currentNew = currentNew->next;
            }
        }
        current = current->next;
    }

    return newHead;
}