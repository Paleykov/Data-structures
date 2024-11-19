#include <iostream>
#include <vector>
#include <queue>

struct Box
{
    int value;
    std::vector<Box*> children;

    Box(int value, const std::vector<Box*>& children)
        : value(value), children(children)
    {}
};

int getHeight(Box* root)
{
    if (!root)
    {
        return 0;
    }

    int buffer = 0;
    for (std::size_t i = 0; i < root->children.size(); ++i)
    {
        buffer = std::max(buffer, getHeight(root->children[i]));
    }

    return 1 + buffer;
}

std::vector<std::vector<int>> getTreePerLevel(Box* root)
{
    std::vector<std::vector<int>> result;
    std::queue<Box*> queue;

    if (!root)
    {
        return result;
    }

    std::vector<int> currentLevel;
    queue.push(root);
    std::size_t elementsAtCurrentLevel = 1, elementsAtNextLevel = 0;

    while (!queue.empty())
    {
        Box* currentBox = queue.front();
        std::cout << "Current value: " << currentBox->value << std::endl;
        currentLevel.push_back(currentBox->value);
        queue.pop();
        --elementsAtCurrentLevel;

        for (std::size_t i = 0; i < currentBox->children.size(); ++i)
        {
            ++elementsAtNextLevel;
            queue.push(currentBox->children[i]);
        }

        if (elementsAtCurrentLevel == 0)
        {
            result.push_back(currentLevel);
            currentLevel.clear();
            elementsAtCurrentLevel = elementsAtNextLevel;
            elementsAtNextLevel = 0;
        }
    }

    return result;
}
