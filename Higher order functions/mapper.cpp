#include <iostream>
#include <functional>

// създава нов свързан списък, като върху всеки елемент на текущия списък се прилага функцията mapper

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

char translate(int data)
{
    return (char)data;
}

template <typename R, typename T>
Box<R>* mapping(Box<T> *head, std::function< R (const T&)> mapper)
{
    Box<R>* newHead = nullptr;
    Box<R>* newcurrent = nullptr;

    Box<T>* current = head;

    while(current !=nullptr)
    {
        Box<R> *Node = new Box<R>(mapper(current->data));
        
        if(newHead == nullptr)
        {
            newHead = Node;
            newcurrent = newHead;
        }    
        else
        {
            Node->next = newcurrent->next;
            newcurrent->next = Node;
            newcurrent= newcurrent->next;
        }

        current = current->next;
    }   

    return newHead;
}

