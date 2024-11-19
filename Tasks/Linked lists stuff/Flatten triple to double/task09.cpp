//#include "task09.h"
#include <iostream>
#include "sll_utils.h"

struct TripleBox
{
    int value;
    TripleBox* next;
    TripleBox* previous;
    TripleBox* child;

    TripleBox(int value, TripleBox* next = nullptr, TripleBox* previous = nullptr, TripleBox* child = nullptr)
        : value(value), next(next), previous(previous), child(child) {}
};

struct DoubleBox
{
    int value;
    DoubleBox* next;
    DoubleBox* previous;

    DoubleBox(int value, DoubleBox* next = nullptr, DoubleBox* previous = nullptr)
        : value(value), next(next), previous(previous) {}
};

// Helper function to append a DoubleBox to the end of a DoubleBox list.
void appendDoubleBox(DoubleBox*& head, DoubleBox*& tail, int value) 
{
    DoubleBox* newBox = new DoubleBox(value);

    if (!head) 
    {
        head = tail = newBox;
    } 
    else 
    {
        tail->next = newBox;
        newBox->previous = tail;
        tail = newBox;
    }
}

void flatten(TripleBox* head, DoubleBox*& flattenedHead, DoubleBox*& flattenedTail) 
{
    if (!head) 
    return;

    // Append the current TripleBox node to the flattened list.
    appendDoubleBox(flattenedHead, flattenedTail, head->value);

    // Recursively flatten the child list (if it exists).
    if (head->child) 
    flatten(head->child, flattenedHead, flattenedTail);

    // Recursively flatten the next list.
    flatten(head->next, flattenedHead, flattenedTail);
}

DoubleBox* flatten(TripleBox* head)
{
    DoubleBox* flattenedHead = nullptr;
    DoubleBox* flattenedTail = nullptr;

    flatten(head, flattenedHead, flattenedTail);

    return flattenedHead;
}

void deallocate(TripleBox* head) 
{
    while (head) 
    {
        TripleBox* toDelete = head;
        head = head->next;
        deallocate(toDelete->child);  // Recursively deallocate child lists.
        delete toDelete;
    }
}

void deallocate(DoubleBox* head) 
{
    while (head) 
    {
        DoubleBox* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

bool areEqual(DoubleBox* list1, DoubleBox* list2)
{
    while (list1 && list2)
    {
        if (list1->value != list2->value)
        {
            return false;
        }

        list1 = list1->next;
        list2 = list2->next;
    }

    return !list1 && !list2;
}

int main()
{
        TripleBox* box1 = new TripleBox(1);
        TripleBox* box2 = new TripleBox(2);
        TripleBox* box3 = new TripleBox(3);
        TripleBox* box4 = new TripleBox(4);
        TripleBox* box5 = new TripleBox(5);
        TripleBox* box6 = new TripleBox(6);
        TripleBox* box7 = new TripleBox(7);
        TripleBox* box8 = new TripleBox(8);
        TripleBox* box9 = new TripleBox(9);
        TripleBox* box10 = new TripleBox(10);
        TripleBox* box11 = new TripleBox(11);
        TripleBox* box12 = new TripleBox(12);
        
        box1->next = box2;
        box2->previous = box1;
        box2->next = box3;
        box3->previous = box2;
        box3->next = box4;
        box4->previous = box3;
        box4->next = box5;
        box5->previous = box4;
        box5->next = box6;
        box6->previous = box5;

        box3->child = box7;
        box7->next = box8;
        box8->previous = box7;
        box8->next = box9;
        box9->previous = box8;
        box9->next = box10;
        box10->previous = box9;

        box8->child = box11;
        box11->next = box12;
        box12->previous = box11;

        TripleBox* list = box1;

        DoubleBox* expected = new DoubleBox(1, new DoubleBox(2, new DoubleBox(3, new DoubleBox(7, new DoubleBox(8, new DoubleBox(11, new DoubleBox(12, new DoubleBox(9, new DoubleBox(10, new DoubleBox(4, new DoubleBox(5, new DoubleBox(6))))))))))));

        DoubleBox* actual = flatten(list);

        DoubleBox* current = actual;

        while (current != nullptr) 
        {
            std::cout << current->value << " ";
            current = current->next;
        }

        deallocate(list);
        deallocate(actual);
        deallocate(expected);
}