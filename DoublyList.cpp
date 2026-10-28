#include "DoublyList.h"

DSpisok::DSpisok()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

DSpisok::~DSpisok()
{
    DNode *current = head;
    while (current != nullptr)
    {
        DNode *next = current->next;
        delete current;
        current = next;
    }
}

DNode *DSpisok::findNode(const std::string &value) const
{
    DNode *current = head;
    while (current != nullptr)
    {
        if (current->info == value)
            return current;
        current = current->next;
    }
    return nullptr;
}

void DSpisok::pushFront(const std::string &value)
{
    DNode *newNode = new DNode{value, head, nullptr};
    if (head != nullptr)
        head->prev = newNode;
    else
        tail = newNode;
    head = newNode;
    count++;
}

void DSpisok::pushBack(const std::string &value)
{
    DNode *newNode = new DNode{value, nullptr, tail};
    if (tail != nullptr)
        tail->next = newNode;
    else
        head = newNode;
    tail = newNode;
    count++;
}

bool DSpisok::insertBefore(const std::string &target, const std::string &value)
{
    DNode *current = findNode(target);
    if (current == nullptr)
        return false;

    if (current == head)
    {
        pushFront(value);
        return true;
    }

    DNode *newNode = new DNode{value, current, current->prev};
    current->prev->next = newNode;
    current->prev = newNode;
    count++;
    return true;
}

bool DSpisok::insertAfter(const std::string &target, const std::string &value)
{
    DNode *current = findNode(target);
    if (current == nullptr)
        return false;

    if (current == tail)
    {
        pushBack(value);
        return true;
    }

    DNode *newNode = new DNode{value, current->next, current};
    current->next->prev = newNode;
    current->next = newNode;
    count++;
    return true;
}

bool DSpisok::eraseValue(const std::string &value)
{
    DNode *current = findNode(value);
    if (current == nullptr)
        return false;

    if (current->prev != nullptr)
        current->prev->next = current->next;
    else
        head = current->next;

    if (current->next != nullptr)
        current->next->prev = current->prev;
    else
        tail = current->prev;

    delete current;
    count--;
    return true;
}

bool DSpisok::eraseAt(int index, std::string &value)
{
    if (index < 0 || index >= count)
        return false;

    DNode *current;
    if (index < count / 2)
    {
        current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
    }
    else
    {
        current = tail;
        for (int i = count - 1; i > index; i--)
            current = current->prev;
    }

    value = current->info;
    if (current->prev != nullptr)
        current->prev->next = current->next;
    else
        head = current->next;
    if (current->next != nullptr)
        current->next->prev = current->prev;
    else
        tail = current->prev;

    delete current;
    count--;
    return true;
}

bool DSpisok::eraseHead(std::string &value)
{
    return eraseAt(0, value);
}

bool DSpisok::eraseTail(std::string &value)
{
    return eraseAt(count - 1, value);
}

bool DSpisok::eraseBefore(const std::string &target, std::string &value)
{
    DNode *current = findNode(target);
    if (current == nullptr || current->prev == nullptr)
        return false;

    DNode *removed = current->prev;
    value = removed->info;
    current->prev = removed->prev;

    if (removed->prev != nullptr)
        removed->prev->next = current;
    else
        head = current;

    delete removed;
    count--;
    return true;
}

bool DSpisok::eraseAfter(const std::string &target, std::string &value)
{
    DNode *current = findNode(target);
    if (current == nullptr || current->next == nullptr)
        return false;
    value = current->next->info;
    DNode *removed = current->next;
    current->next = removed->next;
    if (removed->next != nullptr)
        removed->next->prev = current;
    else
        tail = current;
    delete removed;
    count--;
    return true;
}

bool DSpisok::getAt(int index, std::string &value) const
{
    if (index < 0 || index >= count)
        return false;

    DNode *current;
    if (index < count / 2)
    {
        current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
    }
    else
    {
        current = tail;
        for (int i = count - 1; i > index; i--)
            current = current->prev;
    }

    value = current->info;
    return true;
}

bool DSpisok::contains(const std::string &value) const
{
    return findNode(value) != nullptr;
}

int DSpisok::length() const
{
    return count;
}

bool DSpisok::empty() const
{
    return count == 0;
}

void DSpisok::writeValues(std::ostream &out) const
{
    DNode *current = head;
    while (current != nullptr)
    {
        out << " " << current->info;
        current = current->next;
    }
}
