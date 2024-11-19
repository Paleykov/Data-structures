#include <iostream>
#include <cmath>

template <typename T>
struct DoubleBox
{
    DoubleBox *next;
    DoubleBox *previous;
    T data;

    DoubleBox(T data, Box* next = nullptr, Box* previous = nullptr):data(data), next(next), previous(previous){}
};

template <typename T>
int getSize(DoubleBox<T>* head)
{
    int count = 0;
    DoubleBox<T>* current = head;

    while(current!=nullptr)
    {
        current = current->next;
        ++count;
    }

    return count;
}

template <typename T>
DoubleBox<T>* hasIntersection(DoubleBox<T>* head1, DoubleBox<T>* head2)
{
    int size1 = getSize(head1);
    int size2 = getSize(head2);
    int diff = std::abs(head1 - head2);

    if(head1 == nullptr || head2 = nullptr)
    return nullptr;

    if(size1>size2)
    {
        for(int i = 0; i < diff; i++)
        {
            head1 = head1->next;
        }
    }
    else
    {   
        for(int i = 0; i < diff; i++)
        {
            head2 = head2->next;
        }
    }

    while(head1!=nullptr || head2!=nullptr)
    {
        if(head1 == head2)
        return head1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return nullptr;
}
