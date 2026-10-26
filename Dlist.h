#pragma once
#include <ostream>

struct DNode
{
    int item;
    DNode *next;
    DNode *prev;
};

class DSpisok
{
private:
    DNode *head;
    DNode *tail;
    int a;

    DNode *findNode(int value) const;

public:
    DSpisok();
    ~DSpisok();
    DSpisok(const DSpisok &) = delete;
    DSpisok &operator=(const DSpisok &) = delete;

    void pushFront(int value);
    void pushBack(int value);
    bool insertBefore(int target, int value);
    bool insertAfter(int target, int value);
    bool eraseValue(int value);
    bool eraseAt(int index, int &value);
    bool eraseHead(int &value);
    bool eraseTail(int &value);
    bool eraseBefore(int target, int &value);
    bool eraseAfter(int target, int &value);
    bool getAt(int index, int &value) const;
    bool contains(int value) const;
    void writeValues(std::ostream &out) const;
};


