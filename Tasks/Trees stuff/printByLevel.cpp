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

void atLevel(Box* root, std::size_t n, std::vector<int>& current)
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