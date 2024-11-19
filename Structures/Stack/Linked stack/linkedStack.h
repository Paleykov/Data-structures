#pragma once

template <class T>
class LinkedStack
{
private:
    struct Node
    {
        T value;
        Node* next;
    };
    Node* topn;

    void copy(const LinkedStack<T>& other)
    {
        Node* otherTop = other.topn;
        Node* previous = nullptr;

        while (otherTop)
        {
            Node* newNode = new Node;
            newNode->value = otherTop->value;
            newNode->next = nullptr;

            if (!topn)
            topn = newNode;
            else
            previous->next = newNode;

            previous = newNode;
            otherTop = otherTop->next;
        }
    }

    void deallocate()
    {
        while (!this->empty())
        {
            this->pop();
        }
    }

    
public:
    LinkedStack<T>() = default;

    LinkedStack<T>& operator = (const LinkedStack<T>& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }

    LinkedStack<T>(const LinkedStack<T>& other)
    {
        this->copy(other);
    }

    const T& top() const
    {
        if(empty())
        throw std::out_of_range("Stack is empty.");

        return topn->value;
    }

    void pop()
    {
        if(empty())
        throw std::out_of_range("Stack is empty.");
        
        Node* toDelete = topn;
        topn = topn->next;
        delete toDelete;
    }

    void push(const T& element)
    {
        Node* temp = new Node;
        temp->value = element;
        temp->next = topn;
        topn = temp;
    }

    bool empty() const
    {
        return topn == nullptr;
    }
};