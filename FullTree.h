#pragma once

#include <ostream>
#include <string>

struct TreeNode
{
    int info;
    TreeNode *left;
    TreeNode *right;
};

void insertTree(TreeNode *&root, const int &value);
bool containsTree(TreeNode *root, const int &value);
bool isFullTree(TreeNode *root);
bool treeEmpty(TreeNode *root);
void writeTreeValues(TreeNode *root, std::ostream &out);
void clearTree(TreeNode *root);
