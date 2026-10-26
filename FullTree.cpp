#include "FullTree.h"
#include <queue>

bool treeContainsNode(TNode *node, int value)
{
    if (node == nullptr)
        return false;

    if (node->item == value)
        return true;

    return treeContainsNode(node->left, value) ||
           treeContainsNode(node->right, value);
}

bool treeContains(const FullTree &tree, int value)
{
    return treeContainsNode(tree.root, value);
}

bool treeInsert(FullTree &tree, int value)
{
    if (treeContains(tree, value))
        return false;

    TNode *newNode = new TNode{value, nullptr, nullptr};

    if (tree.root == nullptr)
    {
        tree.root = newNode;
        tree.count = 1;
        return true;
    }

    std::queue<TNode*> nodes;
    nodes.push(tree.root);

    while (!nodes.empty())
    {
        TNode *current = nodes.front();
        nodes.pop();

        if (current->left == nullptr)
        {
            current->left = newNode;
            tree.count++;
            return true;
        }

        nodes.push(current->left);

        if (current->right == nullptr)
        {
            current->right = newNode;
            tree.count++;
            return true;
        }

        nodes.push(current->right);
    }

    return false;
}

bool treeIsFullNode(TNode *node)
{
    if (node == nullptr)
        return true;

    if (node->left == nullptr && node->right == nullptr)
        return true;

    if (node->left == nullptr || node->right == nullptr)
        return false;

    return treeIsFullNode(node->left) &&
           treeIsFullNode(node->right);
}

bool treeIsFull(const FullTree &tree)
{
    return treeIsFullNode(tree.root);
}

int treeHeight(TNode *node)
{
    if (node == nullptr)
        return 0;

    int left = treeHeight(node->left);
    int right = treeHeight(node->right);

    if (left > right)
        return left + 1;

    return right + 1;
}

void treeWriteLevel(TNode *node, int level, std::ostream &out)
{
    if (node == nullptr)
        return;

    if (level == 1)
        out << " " << node->item;
    else
    {
        treeWriteLevel(node->left, level - 1, out);
        treeWriteLevel(node->right, level - 1, out);
    }
}

void treeWrite(const FullTree &tree, std::ostream &out)
{
    int height = treeHeight(tree.root);

    for (int i = 1; i <= height; i++)
        treeWriteLevel(tree.root, i, out);
}

void treeClearNode(TNode *node)
{
    if (node == nullptr)
        return;

    treeClearNode(node->left);
    treeClearNode(node->right);

    delete node;
}

void treeClear(FullTree &tree)
{
    treeClearNode(tree.root);

    tree.root = nullptr;
    tree.count = 0;
}