#include "Array.h"

void arrayGrow(ArrayData &array)
{
    int newCapacity = 10;
    if (array.capacity > 0)
        newCapacity = array.capacity * 2;

    int *newItems = new int[newCapacity];
    for (int i = 0; i < array.count; i++)
        newItems[i] = array.items[i];

    delete[] array.items;
    array.items = newItems;
    array.capacity = newCapacity;
}

void arrayPushBack(ArrayData &array, int value)
{
    if (array.count == array.capacity)
        arrayGrow(array);

    array.items[array.count] = value;
    array.count++;
}

bool arrayInsertAt(ArrayData &array, int index, int value)
{
    if (index < 0 || index > array.count)
        return false;

    if (array.count == array.capacity)
        arrayGrow(array);

    for (int i = array.count; i > index; i--)
        array.items[i] = array.items[i - 1];

    array.items[index] = value;
    array.count++;
    return true;
}

bool arrayGetAt(const ArrayData &array, int index, int &value)
{
    if (index < 0 || index >= array.count)
        return false;

    value = array.items[index];
    return true;
}

bool arrayEraseAt(ArrayData &array, int index, int &value)
{
    if (index < 0 || index >= array.count)
        return false;

    value = array.items[index];
    for (int i = index; i < array.count - 1; i++)
        array.items[i] = array.items[i + 1];

    array.count--;
    return true;
}

bool arraySetAt(ArrayData &array, int index, int value)
{
    if (index < 0 || index >= array.count)
        return false;

    array.items[index] = value;
    return true;
}

int arrayLength(const ArrayData &array)
{
    return array.count;
}

void arrayWrite(const ArrayData &array, std::ostream &out)
{
    for (int i = 0; i < array.count; i++)
        out << " " << array.items[i];
}

void arrayClear(ArrayData &array)
{
    delete[] array.items;
    array.items = nullptr;
    array.count = 0;
    array.capacity = 0;
}
