#include "Stack.h"

void StackData::push(int value)
{
    items.push_back(value);
}

bool StackData::pop(int &value)
{
    if (items.empty()) return false;
    value = items.back();
    items.pop_back();
    return true;
}


std::vector<int> StackData::values() const
{
    return items;
}

void StackData::load(const std::vector<int> &data)
{
    items =data;
}
