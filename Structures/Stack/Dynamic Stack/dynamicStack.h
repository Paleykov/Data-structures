#pragma once
#include <vector>

template <class T>
class DynamicStack
{
    private:
    std::vector<T> stack;

    public:
    DynamicStack(): stack(){};

    const T& top() const
    {
        if(this->stack.empty())
        throw std::out_of_range("");
        return this->stack.back();
    }

    void pop()
    {
        if(this->stack.empty())
        throw std::out_of_range("");
        this->stack.pop_back();
    }

    void push(const T& element)
    {
        this->stack.push_back(element);
    }

    bool empty() const
    {
        return this->stack.empty();
    }
};
