#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Box
{
    int value;
    Box* left;
    Box* right;

    Box(int value, Box* left = nullptr, Box* right = nullptr)
        : value(value), left(left), right(right)
    {}
};

int height(Box* root)
{
    if (!root)
    {
        return 0;
    }

    return 1 + std::max(height(root->left), height(root->right));
}

std::vector<std::vector<int>> getTreePerLevel(Box* root)
{
    std::vector<std::vector<int>> result;
    std::queue<Box*> queue;

    if (!root)
    {
        return result;
    }

    queue.push(root);

    while (!queue.empty())
    {
        std::size_t elementsAtCurrentLevel = queue.size();
        std::vector<int> currentLevel;

        for (std::size_t i = 0; i < elementsAtCurrentLevel; ++i)
        {
            Box* currentNode = queue.front();
            std::cout << "Current value: " << currentNode->value << std::endl;
            currentLevel.push_back(currentNode->value);
            queue.pop();

            if (currentNode->left)
            {
                queue.push(currentNode->left);
            }

            if (currentNode->right)
            {
                queue.push(currentNode->right);
            }
        }

        result.push_back(currentLevel);
    }

    return result;
}

std::vector<int> levelsReverse(Box* root)
{
    std::vector<std::vector<int>> levels = getTreePerLevel(root);
    std::vector<int> result;

    for (std::size_t i = 0; i < levels.size(); ++i)
    {
        for (std::size_t j = 0; j < levels[i].size(); ++j)
        {
            result.push_back(levels[i][j]);
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    Box* root = new Box(10);
    root->left = new Box(5);
    root->right = new Box(15);
    root->left->left = new Box(3);
    root->left->right = new Box(7);
    root->right->left = new Box(12);
    root->right->right = new Box(18);

    std::vector<int> result = levelsReverse(root);

    for(int i = 0; i<result.size(); ++i)
    std::cout << result[i] << std::endl;

    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
