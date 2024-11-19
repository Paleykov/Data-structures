#include <iostream>

struct Box {
    int data;
    Box* left;
    Box* right;

    Box(int data, Box* left = nullptr, Box* right = nullptr)
        : data(data), left(left), right(right) {}
};

bool isInTree(const Box* first, const Box* second)
{
    if(!first)
    return false;

    if(first->data == second->data)
    {
        if(!second->left && !second->right)
        {
            return true;
        } 
        else if(!second->right)
        {
            return isInTree(first->left, second->left);
        }
        else if(!second->left)
        {
            return isInTree(first->right, second->right);
        } 
        else
        {
            return isInTree(first->left, second->left) && isInTree(first->right, second->right);
        }
    }

    return false;
}

bool partOfTree(const Box* first, const Box* second, int &result)
{
    if(!first)
    return false;

    if(!second)
    return true;

    if(isInTree(first,second))
    {
        result = first->data;
        return true;
    }

    return partOfTree(first->left, second, result) || partOfTree(first->right, second, result);
}

int main() {
    Box* mainBST = new Box(10, new Box(5, new Box(2), new Box(7)), new Box(15, new Box(12), new Box(20)));
    Box* partTree = new Box(15, new Box(12), new Box(20));

    int result;
    if (partOfTree(mainBST, partTree, result)) {
        std::cout << "partTree is a part of mainBST." << std::endl;
        std::cout << result;
    } else {
        std::cout << "partTree is not a part of mainBST." << std::endl;
    }

    return 0;
}
