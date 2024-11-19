#include <iostream>
#include <stdexcept>
#include <cmath>
#include <functional>
#include <vector>

class BST
{
private:
    struct Box
    {
        int data;
        Box* left;
        Box* right;

        Box(int data, Box* left = nullptr, Box* right = nullptr)
            : data(data), left(left), right(right) {}
    };

    Box* root;

    bool find(Box* root, int element) const
    {
        if (!root)
        {
            return false;
        }

        if (root->data == element)
        {
            return true;
        }
        else if (root->data < element)
        {
            return find(root->right, element);
        }

        return find(root->left, element);
    }

    void leaves(Box* root, std::vector<int>& current) const
    {
        if (!root)
        {
            return;
        }

        if (!root->left && !root->right)
        {
            current.push_back(root->data);
        }

        leaves(root->left, current);
        leaves(root->right, current);
    }

    void atLevel(Box* root, std::size_t n, std::vector<int>& current) const
    {
        if (!root)
        {
            return;
        }

        if (n == 0)
        {
            current.push_back(root->data);
            return;
        }

        atLevel(root->left, n - 1, current);
        atLevel(root->right, n - 1, current);
    }


public:
    BST() : root(nullptr) {}
  

    bool find(int element) const
    {
        return this->find(this->root, element);
    }


    std::vector<int> leaves() const
    {
        std::vector<int> result;

        this->leaves(this->root, result);
    
        return result;
    }

    std::vector<int> atLevel(std::size_t n) const
    {
        std::vector<int> result;

        this->atLevel(this->root, n, result);
    
        return result;
    }

    
};