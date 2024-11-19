#include <iostream>
#include <functional>

// връща наредена двойка от списъци - първият съдържа всички елементи, за които predicate дава true, а вторият всички, за които дава false

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template<typename T>
std::pair<Box<T> *, Box<T> *> partition(Box<T>* head, std::function<bool(const T&)> predicate)
{
    Box<T> *current = head;

    Box<T>* headLeft = nullptr;
    Box<T>* leftCurrent = nullptr;

    Box<T>* headRight = nullptr;
    Box<T>* rightCurrent = nullptr;
    
    while(current!=nullptr)
    {
        Box<T> *node = new Box<T>(current->data);

        if(predicate(current->data))
        {
            if(headLeft == nullptr)
            {
                headLeft = node;
                leftCurrent = headLeft;
            }
            else
            {
                leftCurrent->next = node;
                leftCurrent = leftCurrent->next;
            }
        }
        else
        {
            if(headRight == nullptr)
            {
                headRight = node;
                rightCurrent = headRight;
            }
            else
            {
                rightCurrent->next = node;
                rightCurrent = rightCurrent->next;
            }
        }

        current = current->next;
    }

    return std::pair<headLeft, headRight>;
}