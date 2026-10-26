#include "Dlist.h"

DSpisok::DSpisok()
{
    head=nullptr;
    tail = nullptr;
    a = 0;
}

DSpisok::~DSpisok()
{
    DNode *current = head;
    while (current !=nullptr)
    {
        DNode *next = current->next;
        delete current;
        current = next;
    }
}

DNode *DSpisok::findNode(int value) const
{
    DNode *current = head;
    while (current !=nullptr)
    {
        if (current->item == value) return current;
        current = current->next;
    }
    return nullptr;
}

void DSpisok::pushFront(int value)
{
    DNode *newNode = new DNode{value, head, nullptr};
    if (head !=nullptr) head->prev = newNode;
    else tail = newNode;
    head=newNode;
    a++;
}

void DSpisok::pushBack(int value)
{
    DNode *newNode = new DNode{value, nullptr, tail};
    if (tail !=nullptr) tail->next = newNode;
    else head = newNode;
    tail = newNode;
    a++;
}

bool DSpisok::insertBefore(int target, int value)
{
    DNode *current = findNode(target);
    if (current ==nullptr) return false;

    if (current == head)
    {
        pushFront(value);
        return true;
    }
    DNode *newNode = new DNode{value, current, current->prev};

    current->prev->next = newNode;
    current->prev = newNode;
    
    a++;
    return true;
}

bool DSpisok::insertAfter(int target, int value)
{
    DNode *current = findNode(target);
    if (current ==nullptr) return false;
    if (current == tail)
    {
        pushBack(value);
return true;
    }
    DNode *newNode = new DNode{value, current->next, current};
    current->next->prev = newNode;
    current->next = newNode;
    a++;
    return true;
}

bool DSpisok::eraseValue(int value)
{
    DNode *current = findNode(value);
    if (current == nullptr) return false;
    if (current->prev !=nullptr) current->prev->next=current->next;
    else
        head = current->next;
    if (current->next !=nullptr) current->next->prev=current->prev;
    else tail = current->prev;
    delete current;
    a--;
    return true;
}

bool DSpisok::eraseAt(int index, int &value)
{
    if (index<0 || index>=a) return false;

    DNode *current;
    if (index< a/2)
    {
        current = head;
        for (int i=0; i < index; i++)
            current = current->next;
    }
    else
    {
        current = tail;
        for (int i = a - 1; i > index; i--)
            current = current->prev;
    }
    value = current->item;

    if (current->prev !=nullptr) current->prev->next=current->next;
    else
        head = current->next;
    if (current->next !=nullptr) current->next->prev=current->prev;
    else
        tail = current->prev;

    delete current;

    a--;
    return true;
}

bool DSpisok::eraseHead(int &value)
{
    return eraseAt(0, value);
}

bool DSpisok::eraseTail(int &value)
{
    return eraseAt(a - 1, value);
}

bool DSpisok::eraseBefore(int target, int &value)
{
    DNode *current = findNode(target);
    if (current ==nullptr || current->prev==nullptr) return false;

    DNode *removed = current->prev;
    value = removed->item;
    current->prev = removed->prev;

    if (removed->prev !=nullptr)
        removed->prev->next = current;
    else
        head = current;

    delete removed;
    a--;
    return true;
}

bool DSpisok::eraseAfter(int target, int &value)
{
    DNode *current = findNode(target);
    if (current ==nullptr || current->next==nullptr)
    return false;
    value = current->next->item;
    DNode *removed = current->next;
    current->next = removed->next;
    if (removed->next !=nullptr) removed->next->prev = current;
    else
        tail = current;
    delete removed;
    a--;
    return true;
}

bool DSpisok::getAt(int index, int &value) const
{
    if (index<0 || index>=a) return false;

    DNode *current;
    if (index< a/2)
    {
        current = head;
        for (int i=0; i < index; i++) current = current->next;
    }
    else
    {
        current = tail;
        for (int i= a-1;i> index; i--) current = current->prev;
    }

    value = current->item;
    return true;
}

bool DSpisok::contains(int value) const
{
    return findNode(value) != nullptr;
}

void DSpisok::writeValues(std::ostream &out) const
{
    DNode *current =head;
    while (current !=nullptr)
    {
    out << " " << current->item;
    current = current->next;
    }
}
