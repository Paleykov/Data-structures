#include <iostream>
#include <stdexcept>
#include <cmath>
#include <functional>
#include <vector>

struct Box
    {
        int data;
        Box* left;
        Box* right;

        Box(int data, Box* left = nullptr, Box* right = nullptr)
            : data(data), left(left), right(right) {}
    };

void map(std::function<Box* (Box*)> function, Box*& root)
{
    if (!root)
    {
        return;
    }

    map(function, root->left);
    map(function, root->right);
    root = function(root);
}
