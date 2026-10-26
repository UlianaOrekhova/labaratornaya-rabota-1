#pragma once
#include <ostream>

struct TNode
{
    int item;
    TNode *left;
    TNode *right;
};


struct FullTree
{
    TNode *root = nullptr;
    int count = 0;
};

bool treeInsert(FullTree &tree, int value);
bool treeContains(const FullTree &tree, int value);
bool treeIsFull(const FullTree &tree);
void treeWrite(const FullTree &tree, std::ostream &out);
void treeClear(FullTree &tree);

