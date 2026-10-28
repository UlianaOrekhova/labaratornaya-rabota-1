#include "Array.h"

ArrayData::ArrayData()
{
    capacity = 10;
    count = 0;
    items = new std::string[capacity];
}

ArrayData::~ArrayData()
{
    delete[] items;
}

void ArrayData::grow()
{
    capacity = capacity * 2;
    std::string *newItems = new std::string[capacity];

    for (int i = 0; i < count; i++)
        newItems[i] = items[i];

    delete[] items;
    items = newItems;
}

void ArrayData::pushBack(const std::string &value)
{
    if (count == capacity)
        grow();

    items[count] = value;
    count++;
}

bool ArrayData::insertAt(int index, const std::string &value)
{
    if (index < 0 || index > count)
        return false;

    if (count == capacity)
        grow();

    for (int i = count; i > index; i--)
        items[i] = items[i - 1];

    items[index] = value;
    count++;
    return true;
}

bool ArrayData::getAt(int index, std::string &value) const
{
    if (index < 0 || index >= count)
        return false;

    value = items[index];
    return true;
}

bool ArrayData::eraseAt(int index, std::string &value)
{
    if (index < 0 || index >= count)
        return false;

    value = items[index];
    for (int i = index; i < count - 1; i++)
        items[i] = items[i + 1];

    count--;
    return true;
}

bool ArrayData::setAt(int index, const std::string &value)
{
    if (index < 0 || index >= count)
        return false;

    items[index] = value;
    return true;
}

int ArrayData::length() const
{
    return count;
}

bool ArrayData::empty() const
{
    return count == 0;
}

void ArrayData::writeValues(std::ostream &out) const
{
    for (int i = 0; i < count; i++)
        out << " " << items[i];
}
