#include <iostream>

template <typename T>
struct DoubleBox
{
    DoubleBox *next;
    DoubleBox *previous;
    T data;

    DoubleBox(T data, DoubleBox *next = nullptr, DoubleBox *previous = nullptr): data(data), next(next), previous(previous){}
};

template <typename T>
DoubleBox<T>* copyList (DoubleBox<T> *otherHead)
{
    DoubleBox<T> *headNew = nullptr;
    DoubleBox<T> *currNew = nullptr;

    DoubleBox<T> *current = otherHead;

    while(current!=nullptr)
    {
        DoubleBox<T> *newBox = new DoubleBox<T>(current->data);

        if(headNew == nullptr)
        {
            headNew = newBox;
            currNew = headNew;
        }
        else
        {
            currNew->next = newBox;
            newBox->previous = currNew;
            currNew = currNew->next;
        }

        current = current->next;
    }

    return headNew;
}
