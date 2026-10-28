#pragma once

#include <ostream>
#include <string>

struct QNode
{
    std::string info;
    QNode *next;
};

class QueueData
{
private:
    QNode *head;
    QNode *tail;

public:
    QueueData();
    ~QueueData();
    QueueData(const QueueData &) = delete;
    QueueData &operator=(const QueueData &) = delete;

    void push(const std::string &value);
    bool pop(std::string &value);
    bool peek(std::string &value) const;
    bool empty() const;
    void writeValues(std::ostream &out) const;
};
