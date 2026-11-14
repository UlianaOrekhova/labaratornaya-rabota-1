#include "FullTree.h"

static bool insertAtLevel(TreeNode *root, TreeNode *newNode, int level)
{
    if (root == nullptr)
        return false;

    if (level == 1)
    {
        if (root->left == nullptr)
        {
            root->left = newNode;
            return true;
        }
        if (root->right == nullptr)
        {
            root->right = newNode;
            return true;
        }
        return false;
    }

    return insertAtLevel(root->left, newNode, level - 1) ||
           insertAtLevel(root->right, newNode, level - 1);
}

static int treeHeight(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static void writeLevel(TreeNode *root, int level, std::ostream &out)
{
    if (root == nullptr)
        return;

    if (level == 1)
    {
        out << " " << root->info;
        return;
    }

    writeLevel(root->left, level - 1, out);
    writeLevel(root->right, level - 1, out);
}

void insertTree(TreeNode *&root, const int &value)
{
    TreeNode *newNode = new TreeNode{value, nullptr, nullptr};
    if (root == nullptr)
    {
        root = newNode;
        return;
    }

    int level = 1;
    while (!insertAtLevel(root, newNode, level))
        level++;
}

bool containsTree(TreeNode *root, const int &value)
{
    if (root == nullptr)
        return false;
    if (root->info == value)
        return true;
    return containsTree(root->left, value) || containsTree(root->right, value);
}

bool isFullTree(TreeNode *root)
{
    if (root == nullptr)
        return true;

    if (root->left == nullptr && root->right == nullptr)
        return true;
    if (root->left == nullptr || root->right == nullptr)
        return false;

    return isFullTree(root->left) && isFullTree(root->right);
}

bool treeEmpty(TreeNode *root)
{
    return root == nullptr;
}

void writeTreeValues(TreeNode *root, std::ostream &out)
{
    int height = treeHeight(root);
    for (int level = 1; level <= height; level++)
        writeLevel(root, level, out);
}

void clearTree(TreeNode *root)
{
    if (root == nullptr)
        return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}
