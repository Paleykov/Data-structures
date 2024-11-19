#include <iostream>
#include <functional>

//слива два сортирани свързани списъка (ако *this или other не са сортирани, да не се прави нищо) 
//в нов сортиран масив ([1 3 5 7], [2 4 6 8] ---> [1 2 3 4 5 6 7 8]); 
//за сравнение на два елемента използва comparator

template <typename T>
struct Box
{
    Box *next;
    T data;

    Box(const T& data, Box *next = nullptr): data(data), next(next){}
};

template <typename T>
void merge(Box<T> *&headFirst, Box<T> *&headSecond, 
std::function<bool(const T&, const T&)> comparator = [](const T& first, const T& second)->bool{return first < second;})
{
    // Proverka dali purviq list e sortiran
    if(headFirst)
    {
        Box<T>* current = headFirst;
        while(current->next!=nullptr)
        {
            if(comparator(current->data, current->next->data) == false)
            return;

            current = current->next;  
        }
    }

    // Proverka dali vtoriq list e sortiran
    if(headSecond)
    {
        Box<T>* current = headSecond;
        while(current->next!=nullptr)
        {
            if(comparator(current->data, current->next->data) == false)
            return;

            current = current->next;
        }
    }

    if(!headFirst)
    {
        headFirst = headSecond;
        return;
    }

    if(!headSecond)
    {
        return;
    }

    Box<T> *currentFirst = nullptr;
    Box<T> *currentSecond = nullptr;

    if(comparator(headFirst->data, headSecond->data))
    {
        currentFirst = headFirst;
        currentSecond = headSecond;
    }
    else
    {
        currentFirst = headSecond;
        currentSecond = headFirst;
    }

    while(currentFirst!=nullptr && currentSecond!=nullptr)
    {
        if(comparator(currentFirst->data, currentSecond->data) == true &&
        (currentFirst->next == nullptr || comparator(currentFirst->next->data, currentSecond->data) == false))
        {
            Box<T> *temp = new Box<T>(currentSecond->data, currentFirst->next);
            currentFirst->next = temp;

            currentSecond = currentSecond->next;
        } 

        currentFirst = currentFirst->next;
    }
}


