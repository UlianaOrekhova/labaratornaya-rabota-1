#pragma onse

#include <ostream>
#include <string>

class ArrayData
{
private:
    std::string *items;
    int count;
    int capacity;

    void grow();

public:
    ArrayData();
    ~ArrayData();
    ArrayData(const ArrayData &) = delete;
    ArrayData &operator=(const ArrayData &) = delete;

    void pushBack(const std::string &value);
    bool insertAt(int index, const std::string &value);
    bool getAt(int index, std::string &value) const;
    bool eraseAt(int index, std::string &value);
    bool setAt(int index, const std::string &value);
    int length() const;
    bool empty() const;
    void writeValues(std::ostream &out) const;
};
