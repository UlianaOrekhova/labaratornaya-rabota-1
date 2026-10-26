#include "Queue.h"

void QueueData::push(int value)
{
    items.push_back(value);
}

bool QueueData::pop(int &value)
{
    if (items.empty()) return false;
    value = items.front();
    items.pop_front();
    return true;
}


std::vector<int> QueueData::values() const
{
    return std::vector<int>(items.begin(), items.end());
}

void QueueData::load(const std::vector<int> &data)
{
    items.clear();
    for (int value : data)
        items.push_back(value);
}
