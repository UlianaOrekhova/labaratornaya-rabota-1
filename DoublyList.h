#pragma once

#include <ostream>
#include <string>

struct DNode
{
    std::string info;
    DNode *next;
    DNode *prev;
};

class DSpisok
{
private:
    DNode *head;
    DNode *tail;
    int count;

    DNode *findNode(const std::string &value) const;

public:
    DSpisok();
    ~DSpisok();
    DSpisok(const DSpisok &) = delete;
    DSpisok &operator=(const DSpisok &) = delete;

    void pushFront(const std::string &value);
    void pushBack(const std::string &value);
    bool insertBefore(const std::string &target, const std::string &value);
    bool insertAfter(const std::string &target, const std::string &value);
    bool eraseValue(const std::string &value);
    bool eraseAt(int index, std::string &value);
    bool eraseHead(std::string &value);
    bool eraseTail(std::string &value);
    bool eraseBefore(const std::string &target, std::string &value);
    bool eraseAfter(const std::string &target, std::string &value);
    bool getAt(int index, std::string &value) const;
    bool contains(const std::string &value) const;
    int length() const;
    bool empty() const;
    void writeValues(std::ostream &out) const;
};
