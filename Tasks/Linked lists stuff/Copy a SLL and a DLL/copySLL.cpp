#include <iostream>

template <typename T>
struct Box
{
    T data;
    Box *next;

    Box(T data, Box* next = nullptr): data(data), next(next){}
};

template <typename T>
Box<T>* copyList (Box<T>* otherhead)
{
    Box<T> *newHead = nullptr;
    Box<T> *newcurr = newHead;
    Box<T> *current = otherhead;

    if(otherhead == nullptr)
    return nullptr;

    while (current != nullptr)
    {
        Box<T> *newNode = new Box<T>(current->data);

        if (newHead == nullptr) 
        {
            newHead = newNode;
            newcurr = newHead;
        } 
        else 
        {
            newcurr->next = newNode;
            newcurr = newcurr->next;
        }

        current = current->next;
    }

    return newHead;
}

int main() {
    Box<int>* head1 = new Box<int>(1);
    head1->next = new Box<int>(4);
    head1->next->next = new Box<int>(7);
    head1->next->next->next = new Box<int>(5);

    Box<int>* head2 = copyList(head1);

    Box<int>* current = head1;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    current = head2;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }

    return 0;
}