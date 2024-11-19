#include <iostream>
#include <cmath>

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(T data, Box* next = nullptr):data(data), next(next){}
};

template <typename T>
int getSize(Box<T>* head)
{
    int count = 0;
    Box<T>* current = head;

    while(current!=nullptr)
    {
        current = current->next;
        ++count;
    }

    return count;
}

template <typename T>
Box<T>* hasIntersection(Box<T>* head1, Box<T>* head2)
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
        Box<T>* buffer = head2;
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
