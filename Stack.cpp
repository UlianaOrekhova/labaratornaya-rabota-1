#include "Stack.h"

StackData::StackData()
{
    capacity = 10;
    count = 0;
    items = new std::string[capacity];
}

StackData::~StackData()
{
    delete[] items;
}

void StackData::grow()
{
    capacity = capacity * 2;
    std::string *newItems = new std::string[capacity];

    for (int i = 0; i < count; i++)
        newItems[i] = items[i];

    delete[] items;
    items = newItems;
}

void StackData::push(const std::string &value)
{
    if (count == capacity)
        grow();

    items[count] = value;
    count++;
}

bool StackData::pop(std::string &value)
{
    if (count == 0)
        return false;

    count--;
    value = items[count];
    return true;
}

bool StackData::peek(std::string &value) const
{
    if (count == 0)
        return false;

    value = items[count - 1];
    return true;
}

bool StackData::empty() const
{
    return count == 0;
}

void StackData::writeValues(std::ostream &out) const
{
    for (int i = 0; i < count; i++)
        out << " " << items[i];
}
