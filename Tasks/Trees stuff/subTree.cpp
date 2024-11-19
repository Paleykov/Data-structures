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

bool isItSubtree (const Box* first, const Box* second)
{
    if(!first)
    return false;

    if(!second)
    return true;

    if(isIdentical(first, second))
    return true;

    return isItSubtree(first->left, second) || isItSubtree(first->right, second); 
}

int main() {
    Box* mainBST = new Box(10, new Box(5, new Box(2), new Box(7)), new Box(15, new Box(12), new Box(20)));
    Box* subBST = new Box(10, new Box(5), new Box(15));

    if (isItSubtree(mainBST, subBST)) {
        std::cout << "subBST is a subtree of mainBST." << std::endl;
    } else {
        std::cout << "subBST is not a subtree of mainBST." << std::endl;
    }

    return 0;
}