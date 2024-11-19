#include <iostream>
#include <functional>

// връща списък от нови списъци, конкатенацията на които е равна на първоначалния списък и всеки подсписък 
// съдържа само еднакви елементи (["Mississippi"] ---> [["M"], ["i"], ["ss"], ["i"], ["ss"], ["i"], ["pp"], ["i"]])

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template<typename T>
Box<Box<T>*>* group(Box<T> *head)
{
    if(head == nullptr)
    return nullptr;
    
    Box<Box<T>*> *newHead = new Box<Box<T>*>(new Box<T>(head->data));
    Box<Box<T>*> *newCurrent = newHead;

    Box<T> *current = head;
    Box<T> *smallCurrent = newHead->data;

    while(current->next!=nullptr)
    {
        Box<T> *smallNode = new Box<T>(current->next->data);

        if(current->data == current->next->data)
        {
            smallCurrent->next = smallNode;
            smallCurrent = smallCurrent->next;
        }
        else
        {
            Box<Box<T>*> *BigNode = new Box<Box<T>*>(new Box<T>(current->next->data));
            newCurrent->next = BigNode;
            newCurrent = newCurrent->next;
            smallCurrent = newCurrent->data;
        }

        current = current->next;
    }

    return newHead;
}

