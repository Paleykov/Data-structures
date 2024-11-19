#include <iostream>

template <typename T>
struct TripleBox
{
    TripleBox *next;
    TripleBox *previous;
    TripleBox *child;
    T value;

    TripleBox(T value, TripleBox<T>* next = nullptr, TripleBox<T>* previous = nullptr, TripleBox<T>* child = nullptr): next(next), previous(previous), child(child), value(value){}
};

template <typename T>
struct DoubleBox
{
    DoubleBox *next;
    DoubleBox *previous;
    T value;

    DoubleBox(T value, DoubleBox<T>* next = nullptr, DoubleBox<T>* previous = nullptr): next(next), previous(previous), value(value){}
};

template <typename T>
void append(DoubleBox<T> *&head, DoubleBox<T> *&tail, T value)
{
    DoubleBox<T> *newBox = new DoubleBox<T>(value);

    if(head==nullptr)
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

template <typename T>
void flatten(TripleBox<T> *headT, DoubleBox<T> *&head, DoubleBox<T> *&tail)
{
    if(!head)
    return;

    append(head, tail, headT->value);

    if(headT->child != nullptr)
    flatten(headT->child, head, tail);

    flatten(headT->next, head, tail);
}

template <typename T>
DoubleBox<T>* flatten(TripleBox<T> *headT)
{
    DoubleBox<T> *headDLL = nullptr;
    DoubleBox<T> *tailDLL = nullptr;

    flatten(headT, headDLL, tailDLL);

    return headDLL;
}

template <typename T>
void deallocate(TripleBox<T>* head) 
{
    while (head) 
    {
        TripleBox<T>* toDelete = head;
        head = head->next;
        deallocate(toDelete->child);  // Recursively deallocate child lists.
        delete toDelete;
    }
}

template <typename T>
void deallocate(DoubleBox<T>* head) 
{
    while (head) 
    {
        DoubleBox<T>* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

template <typename T>
bool areEqual(DoubleBox<T>* list1, DoubleBox<T>* list2)
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
        TripleBox<int>* box1 = new TripleBox<int>(1);
        TripleBox<int>* box2 = new TripleBox<int>(2);
        TripleBox<int>* box3 = new TripleBox<int>(3);
        TripleBox<int>* box4 = new TripleBox<int>(4);
        TripleBox<int>* box5 = new TripleBox<int>(5);
        TripleBox<int>* box6 = new TripleBox<int>(6);
        TripleBox<int>* box7 = new TripleBox<int>(7);
        TripleBox<int>* box8 = new TripleBox<int>(8);
        TripleBox<int>* box9 = new TripleBox<int>(9);
        TripleBox<int>* box10 = new TripleBox<int>(10);
        TripleBox<int>* box11 = new TripleBox<int>(11);
        TripleBox<int>* box12 = new TripleBox<int>(12);
        
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

        TripleBox<int>* list = box1;

        DoubleBox<int>* expected = new DoubleBox<int>(1, new DoubleBox<int>(2, new DoubleBox<int>(3, new DoubleBox<int>
        (7, new DoubleBox<int>(8, new DoubleBox<int>(11, new DoubleBox<int>(12, new DoubleBox<int>(9, 
        new DoubleBox<int>(10, new DoubleBox<int>(4, new DoubleBox<int>(5, new DoubleBox<int>(6))))))))))));

        DoubleBox<int>* actual = flatten(list);

        DoubleBox<int>* current = actual;

        while (current != nullptr) 
        {
            std::cout << current->value << " ";
            current = current->next;
        }

        deallocate(list);
        deallocate(actual);
        deallocate(expected);
}
