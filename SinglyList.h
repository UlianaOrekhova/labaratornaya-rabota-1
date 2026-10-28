#pragma once

#include <ostream>
#include <string>

struct Node
{
    std::string info;
    Node *next;
};

Node *constructNode(const std::string &info);

class SSpisok
{
private:
    Node *head;
    Node *tail;
    int count;

    Node *findNode(const std::string &value) const;

public:
    SSpisok();
    ~SSpisok();
    SSpisok(const SSpisok &) = delete;
    SSpisok &operator=(const SSpisok &) = delete;

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
