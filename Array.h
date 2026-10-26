#pragma once
#include <ostream>

struct ArrayData
{
    int *items = nullptr;
    int count = 0;
    int capacity = 0;
};

void arrayPushBack(ArrayData &array, int value);
bool arrayInsertAt(ArrayData &array, int index, int value);
bool arrayGetAt(const ArrayData &array, int index, int &value);
bool arrayEraseAt(ArrayData &array, int index, int &value);
bool arraySetAt(ArrayData &array, int index, int value);
int arrayLength(const ArrayData &array);
void arrayWrite(const ArrayData &array, std::ostream &out);
void arrayClear(ArrayData &array);

