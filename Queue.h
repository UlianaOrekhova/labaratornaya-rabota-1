#pragma once

#include <vector>
#include <deque>

class QueueData
{
private:
    std::deque<int> items;

public:
    void push(int value);
    bool pop(int &value);
    std::vector<int> values() const;
    void load(const std::vector<int> &data);
};
