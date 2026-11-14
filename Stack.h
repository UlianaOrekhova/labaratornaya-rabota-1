#ifndef STACK_H
#define STACK_H

#include <ostream>
#include <string>

class StackData
{
private:
    std::string *items;
    int count;
    int capacity;

    void grow();

public:
    StackData();
    ~StackData();
    StackData(const StackData &) = delete;
    StackData &operator=(const StackData &) = delete;

    void push(const std::string &value);
    bool pop(std::string &value);
    bool peek(std::string &value) const;
    bool empty() const;
    void writeValues(std::ostream &out) const;
};

#endif
