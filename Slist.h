#pragma once
#include <ostream>

struct Node
{
    int item;
    Node *next;
};

Node *constructNode(int item);

class SSpisok
{
private:
    Node *head;
    Node *tail;
    int a;

    Node *findNode(int value) const;

public:
    SSpisok();
    ~SSpisok();
    SSpisok(const SSpisok &) = delete;
    SSpisok &operator=(const SSpisok &) = delete;

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

