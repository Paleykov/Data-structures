#include <iostream>

struct Box
{
    int data;
    Box* left;
    Box* right;

    Box(int data, Box* left = nullptr, Box* right = nullptr)
        : data(data), left(left), right(right) {}
};

bool isIdentical (const Box* first, const Box* second)
{
    if(!first && !second)
    return true;

    if (!first || !second)
    return false;

    if(first->data == second->data)
    return isIdentical(first->left, second->left) && isIdentical(first->right, second->right);

    return false;
}