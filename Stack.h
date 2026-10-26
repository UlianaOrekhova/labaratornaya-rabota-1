#pragma once
#include <vector>

class StackData
{
private:
    std::vector<int> items;

public:
    void push(int value);
    bool pop(int &value);
    std::vector<int> values() const;
    void load(const std::vector<int> &data);
};

