#include <iostream>
#include <functional>

//връща нов списък, съдържащ елементи, които са резултати от прилагането на функцията zipper върху съответните елементи на *this и other

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T, typename R>
Box<R>* zipWith(Box<T> *&current, Box<T> *&other, std::function< R (const T&, const T&)> zipper)
{
    Box<R> *newHead = nullptr;
    Box<R> *newCurrent = nullptr;

    while(current && other)
    {
        Box<R> *node = new Box<R>(zipper(current->data, other->data));

        if(newHead == nullptr)
        {
            newHead = node;
            newCurrent = newHead;
        }
        else
        {
            newCurrent->next = node;
            newCurrent = newCurrent->next;
        }

        current = current->next;
        other = other->next;
    }

    return newHead;
}
