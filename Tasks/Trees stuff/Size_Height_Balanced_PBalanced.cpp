#include <iostream>

struct Box {
    int data;
    Box* left;
    Box* right;

    Box(int data, Box* left = nullptr, Box* right = nullptr)
        : data(data), left(left), right(right) {}
};

int size(Box* root)
    {
        if (!root)
        {
            return 0;
        }

        return 1 + size(root->left) + size(root->right);
    }

    int height(Box* root)
    {
        if (!root)
        {
            return 0;
        }

        return 1 + std::max(height(root->left), height(root->right));
    }

    bool isBalanced(Box* root) 
    {
        if (!root)
        {
            return true;
        }

        return isBalanced(root->left) &&
               isBalanced(root->right) &&
               (std::abs(height(root->left) - height(root->right)) < 2);
    }

    bool isPerfectlyBalanced(Box* root) 
    {
        if (!root)
        {
            return true;
        }

        return isPerfectlyBalanced(root->left) &&
               isPerfectlyBalanced(root->right) &&
               (std::abs(size(root->left) - size(root->right)) < 2);
    }