#include "SinglyList.h"

Node *constructNode(const std::string &info)
{
    Node *newNode = new Node;
    newNode->info = info;
    newNode->next = nullptr;
    return newNode;
}

SSpisok::SSpisok()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

SSpisok::~SSpisok()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

Node *SSpisok::findNode(const std::string &value) const
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->info == value)
            return current;
        current = current->next;
    }
    return nullptr;
}

void SSpisok::pushFront(const std::string &value)
{
    Node *newNode = constructNode(value);
    newNode->next = head;
    head = newNode;

    if (tail == nullptr)
        tail = newNode;

    count++;
}

void SSpisok::pushBack(const std::string &value)
{
    Node *newNode = constructNode(value);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    count++;
}

bool SSpisok::insertBefore(const std::string &target, const std::string &value)
{
    Node *current = findNode(target);
    if (current == nullptr)
        return false;

    if (current == head)
    {
        pushFront(value);
        return true;
    }

    Node *previous = head;
    while (previous->next != current)
        previous = previous->next;

    Node *newNode = constructNode(value);
    previous->next = newNode;
    newNode->next = current;
    count++;
    return true;
}

bool SSpisok::insertAfter(const std::string &target, const std::string &value)
{
    Node *current = findNode(target);
    if (current == nullptr)
        return false;

    Node *newNode = constructNode(value);
    newNode->next = current->next;
    current->next = newNode;

    if (tail == current)
        tail = newNode;

    count++;
    return true;
}

bool SSpisok::eraseValue(const std::string &value)
{
    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr && current->info != value)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
        return false;

    if (previous == nullptr)
        head = current->next;
    else
        previous->next = current->next;

    if (tail == current)
        tail = previous;

    delete current;
    count--;
    return true;
}

bool SSpisok::eraseAt(int index, std::string &value)
{
    if (index < 0 || index >= count)
        return false;

    Node *current = head;
    Node *previous = nullptr;
    for (int i = 0; i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    value = current->info;
    if (previous == nullptr)
        head = current->next;
    else
        previous->next = current->next;

    if (tail == current)
        tail = previous;

    delete current;
    count--;
    return true;
}

bool SSpisok::eraseHead(std::string &value)
{
    return eraseAt(0, value);
}

bool SSpisok::eraseTail(std::string &value)
{
    return eraseAt(count - 1, value);
}

bool SSpisok::eraseBefore(const std::string &target, std::string &value)
{
    Node *current = findNode(target);
    if (current == nullptr || current == head)
        return false;

    Node *previous = head;
    Node *beforePrevious = nullptr;
    while (previous->next != current)
    {
        beforePrevious = previous;
        previous = previous->next;
    }

    value = previous->info;
    if (beforePrevious == nullptr)
        head = current;
    else
        beforePrevious->next = current;

    delete previous;
    count--;
    return true;
}

bool SSpisok::eraseAfter(const std::string &target, std::string &value)
{
    Node *current = findNode(target);
    if (current == nullptr || current->next == nullptr)
        return false;

    Node *removed = current->next;
    value = removed->info;
    current->next = removed->next;

    if (tail == removed)
        tail = current;

    delete removed;
    count--;
    return true;
}

bool SSpisok::getAt(int index, std::string &value) const
{
    if (index < 0 || index >= count)
        return false;

    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;

    value = current->info;
    return true;
}

bool SSpisok::contains(const std::string &value) const
{
    return findNode(value) != nullptr;
}

int SSpisok::length() const
{
    return count;
}

bool SSpisok::empty() const
{
    return count == 0;
}

void SSpisok::writeValues(std::ostream &out) const
{
    Node *current = head;
    while (current != nullptr)
    {
        out << " " << current->info;
        current = current->next;
    }
}
