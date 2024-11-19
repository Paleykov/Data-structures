#include <iostream>
#include <stddef.h>

template <class T>
class SinglyLinkedListClassMyReal
{
    private:
    struct Box
    {
        T data;
        Box* next;

        Box(const T& data, Box* next = nullptr): data(data), next(next){}
    };

    Box* head;
    Box* tail;

    void deallocate()
    { 
        while(!this->empty())
        {
            this->pop_back();
        }
    }
    
    void copy(const SinglyLinkedListClassMyReal<T>& other)
    {
        Box* current = other.head;

        while(current!=nullptr)
        {
            this->push_back(current->data);
            current = current->next;
        }
    }

    public:
    SinglyLinkedListClassMyReal<T>(): Box(),head(nullptr), tail(nullptr){}
    // SinglyLinkedListClass(std::size_t size, const T& value = T());

    SinglyLinkedListClassMyReal<T>& operator = (const SinglyLinkedListClassMyReal<T>& other)
    {
        if(this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }

    SinglyLinkedListClassMyReal<T>(const SinglyLinkedListClassMyReal<T>& other)
    {
        this->copy(other);
    }

    ~SinglyLinkedListClassMyReal<T>()
    {
        this->deallocate();
    }

    int size() const
    {
        if (head == nullptr)
        {
            return 0;
        }

        int count = 1;
        Box* current = this->head;

        while(current->next!=nullptr)
        {
            current = current->next;
            ++count;
        }

        return count;
    }

    T& front()
    {
        return this->head->data;
    }

    const T& front() const
    {
        return this->head->data;
    }

    T& back()
    {
        return this->tail->data;
    }

    const T& back() const
    {
        return this->tail->data;
    }

    void clear()
    {
        this->deallocate();
    }

    bool empty() const
    {
        return this->head == nullptr;
    }

    void print() const
    {
        Box* current = this->head;

        while(current!=nullptr)
        {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }

    void push_back(const T& element)
    {
        if(this->head == nullptr)
        {
            this->head= new Box(element);
            this->tail = this->head;
        }
        else
        {
            this->tail->next = new Box(element);
            this->tail = this->tail->next;
        }
    }

    void pop_back()
    {
        if(empty())
        {
            return;
        }

        if(this->head == this->tail)
        {
            delete this->head;
            this->head = this->tail = nullptr;
            return;
        }

        Box* currrent = this->head;
        while(currrent->next != this->tail)
        {
            currrent = currrent->next;
        }

        delete this->tail;
        currrent->next = nullptr;
        this->tail = currrent;
    }

    void push_front(const T& element)
    {
        if(empty())
        {
            Box* newBox = new Box(element);
            this->head = this->tail = newBox;
            return;
        }

        Box* newBox = new Box(element);
        newBox->next = this->head;
        this->head = newBox;
    }
    
    void pop_front()
    {
        if(empty())
        return;

        if(this->head == this->tail)
        {
            delete this->head;
            this->head = this->tail = nullptr;
            return;
        }

        Box* toDelete = this->head;
        this-head = this->head->next;
        delete toDelete;
    }

    class Iterator 
    {
        private:
        friend class SinglyLinkedListMyReal;
        Box* box;

        public:

        Iterator(Box* box): box(box) {}

        T& operator * ()
        {
            return this->box->data;
        }

        const T& operator * () const
        {
            return this->box->data;
        }

        T* operator -> ()
        {
            return &this->box->data;
        }

        const T* operator -> () const
        {
            return &this->box->data;
        }

        Iterator& operator ++ ()
        {
            this->box = this->box->next;
            return *this;
        }

        Iterator operator ++ (int)
        {
            Iterator old(this->box);
            ++(*this);

            return old;
        }
        bool operator == (const Iterator& other) const;
        bool operator != (const Iterator& other) const;
    };

    Iterator begin()
    {
        return Iterator(this->head);
    }

    Iterator end()
    {
        return Iterator(this->tail);
    }
    
    void insert_after(Iterator pos, const T& value)
    {
        if(pos->box == this->head)
        {
            push_front(value);
        }

        Box *newBox = new Box(value);
        newBox->next = pos->box->next;
        pos->box->next = newBox;
    }

    void erase(Iterator first, Iterator last);

    void erase(Iterator pos);
};