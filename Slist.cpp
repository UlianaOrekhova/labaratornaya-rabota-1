#include "Slist.h"

Node *constructNode(int item)
{
    Node *newNode =new Node;
    newNode->item=item;
    newNode->next=nullptr;
    return newNode;
}

SSpisok::SSpisok()
{
    head =nullptr;
    tail =nullptr;
    a =0;
}

SSpisok::~SSpisok()
{
    Node *current =head;
    while (current!= nullptr)
    {
        Node *next =current->next;
        delete current;
        current =next;
    }
}

Node *SSpisok::findNode(int value) const
{
    Node *current =head;
    while (current!= nullptr)
    {
        if (current->item==value) return current;
        current =current->next;
    }
    return nullptr;
}

void SSpisok::pushFront(int value)
{
    Node *newNode =constructNode(value);
    newNode->next =head;
    head =newNode;

    if (tail==nullptr) tail =newNode;
    a++;
}

void SSpisok::pushBack(int value)
{
    Node *newNode =constructNode(value);

    if (head==nullptr)
    {
        head =newNode;
        tail =newNode;
    }
    else
    {
        tail->next =newNode;
        tail =newNode;
    }

    a++;
}

bool SSpisok::insertBefore(int target, int value)
{
    Node *current =findNode(target);
    if (current==nullptr) return false;

    if (current==head)
    {
        pushFront(value);
        return true;
    }

    Node *x =head;
    while (x->next!= current)
        x =x->next;
    Node *newNode =constructNode(value);
    x->next =newNode;
    newNode->next=current;
    a++;
    return true;
}

bool SSpisok::insertAfter(int target, int value)
{
    Node *current =findNode(target);
    if (current==nullptr) return false;

    Node *newNode =constructNode(value);
    newNode->next =current->next;
    current->next =newNode;

    if (tail==current)
        tail =newNode;

    a++;
    return true;
}

bool SSpisok::eraseValue(int value)
{
    Node *current =head;
    Node *x =nullptr;

    while (current!= nullptr && current->item!=value)
    {
        x =current;
        current =current->next;
    }

    if (current==nullptr)
        return false;

    if (x==nullptr)
        head =current->next;
    else
        x->next =current->next;

    if (tail==current)
        tail =x;

    delete current;
    a--;
    return true;
}

bool SSpisok::eraseAt(int index, int &value)
{
    if (index < 0 || index >= a)
        return false;

    Node *current =head;
    Node *x =nullptr;
    for (int i =0; i < index; i++)
    {
        x =current;
        current =current->next;
    }

    value =current->item;
    if (x==nullptr)
        head =current->next;
    else
        x->next =current->next;

    if (tail==current)
        tail =x;

    delete current;
    a--;
    return true;
}

bool SSpisok::eraseHead(int &value)
{
    return eraseAt(0, value);
}

bool SSpisok::eraseTail(int &value)
{
    return eraseAt(a - 1, value);
}

bool SSpisok::eraseBefore(int target, int &value)
{
    Node *current =findNode(target);
    if (current==nullptr || current==head)
        return false;

    Node *x =head;
    Node *beforeX=nullptr;
    while (x->next!= current)
    {
        beforeX=x;
        x =x->next;
    }

    value =x->item;
    if (beforeX==nullptr)
        head =current;
    else
        beforeX->next =current;

    delete x;
    a--;
    return true;
}

bool SSpisok::eraseAfter(int target, int &value)
{
    Node *current =findNode(target);
    if (current==nullptr || current->next==nullptr)
        return false;

    Node *removed =current->next;
    value =removed->item;
    current->next =removed->next;

    if (tail==removed)
        tail =current;

    delete removed;
    a--;
    return true;
}

bool SSpisok::getAt(int index, int &value) const
{
    if (index <0 || index>= a)
        return false;

    Node *current =head;
    for (int i =0; i < index; i++)
        current =current->next;

    value =current->item;
    return true;
}

bool SSpisok::contains(int value) const
{
    return findNode(value)!= nullptr;
}


void SSpisok::writeValues(std::ostream &out) const
{
    Node *current =head;
    while (current!= nullptr)
    {
        out << " " << current->item;
        current =current->next;
    }
}
