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

void deallocate(Box* root)
    {
        if (!root)
        {
            return;
        }

        deallocate(root->left);
        deallocate(root->right);
        delete root;
    }

    Box* copy(Box* root)
    {
        if (!root)
        {
            return root;
        }

        return new Box(root->data, copy(root->left), copy(root->right));
    } 