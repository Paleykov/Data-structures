#include <iostream>
#include <functional>

//- по подадена начална стойност init връща резултата от прилагането на функцията folder над всички елементи

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename R, typename T>
R foldLeft(Box<T>* head, const R& init, std::function<R(const R&, const T&)> folder)
{
    R result = init;

    Box<T> *current = head;
    while(current != nullptr)
    {
        result = folder(result, current->data);
        current = current->next;
    }

    return result;
}