#include <iostream>
#include <functional>

// проверява дали всички елементи на списъка удовлетворяват предиката predicate (квантор за всеобщност)

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T>
bool all(Box<T> *head, std::function<bool(const T&)> predicate)
{
    Box<T> *current = head;

    while(current!=nullptr)
    {
        if(predicate(current->data) == false)
        return false;
    }

    return true;
}