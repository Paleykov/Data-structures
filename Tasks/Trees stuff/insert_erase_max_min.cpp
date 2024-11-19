#include <iostream>

struct Box
{
    int data;
    Box* left;
    Box* right;

    Box(int data, Box* left = nullptr, Box* right = nullptr)
        : data(data), left(left), right(right) {}
};

void insert(Box*& root, int element)
    {
        if (!root)
        {
            root = new Box(element);
        }
        else if (element >= root->data)
        {
            insert(root->right, element);
        }
        else
        {
            insert(root->left, element);
        }
    }

void erase(Box*& root, int element)
    {
        if (!root)
        {
            return;
        }
        else if (root->data < element)
        {
            erase(root->right, element);
            return;
        }
        else if (root->data > element)
        {
            erase(root->left, element);
            return;
        }
        
        Box* toDelete = root;
        if (!root->left && !root->right)
        {
            root = nullptr;
        }
        else if (root->left && !root->right)
        {
            root = root->left;
        }
        else if (!root->left && root->right)
        {
            root = root->right;
        }
        else
        {
            Box* maxLeaf = extractMax(root->left);
            maxLeaf->left = root->left;
            maxLeaf->right = root->right;
            root = maxLeaf;
        }
        delete toDelete;
    }

    Box* extractMax(Box*& root)
    {
        if (root->right)
        {
            return extractMax(root->right);
        }

        Box* result = root;
        root = root->left;
        return result; 
    } 

    int min(Box*& root) 
    {
        if (!root)
        {
            throw std::logic_error("Empty BST");
        }
        Box* temp = root;

        while (temp->left)
        {
            temp = temp->left;
        }

        return temp->data;
    }

    int max(Box*& root) 
    {
        if (!root)
        {
            throw std::logic_error("Empty BST");
        }
        Box* temp = root;

        while (temp->right)
        {
            temp = temp->right;
        }

        return temp->data;
    }