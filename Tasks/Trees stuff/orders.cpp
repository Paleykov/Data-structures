#include <iostream>
#include <vector>

struct Box
{
    int data;
    Box* left;
    Box* right;

    Box(int data, Box* left = nullptr, Box* right = nullptr)
        : data(data), left(left), right(right) {}
};

 void inorder(Box* root, std::vector<int>& current)
    {
        if (!root)
        {
            return;
        }

        inorder(root->left, current);
        current.push_back(root->data);
        inorder(root->right, current);
    }

    void preorder(Box* root, std::vector<int>& current) 
    {
        if (!root)
        {
            return;
        }

        current.push_back(root->data);
        preorder(root->left, current);
        preorder(root->right, current);
    }

    void postorder(Box* root, std::vector<int>& current)
    {
        if (!root)
        {
            return;
        }

        postorder(root->left, current);
        postorder(root->right, current);
        current.push_back(root->data);
    }