#include "Queue.h"

QueueData::QueueData()
{
    head = nullptr;
    tail = nullptr;
}

QueueData::~QueueData()
{
    while (head != nullptr)
    {
        QNode *current = head;
        head = head->next;
        delete current;
    }
}

void QueueData::push(const std::string &value)
{
    QNode *newNode = new QNode;
    newNode->info = value;
    newNode->next = nullptr;

    if (tail == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

bool QueueData::pop(std::string &value)
{
    if (head == nullptr)
        return false;

    QNode *current = head;
    value = current->info;
    head = head->next;

    if (head == nullptr)
        tail = nullptr;

    delete current;
    return true;
}

bool QueueData::peek(std::string &value) const
{
    if (head == nullptr)
        return false;

    value = head->info;
    return true;
}

bool QueueData::empty() const
{
    return head == nullptr;
}

void QueueData::writeValues(std::ostream &out) const
{
    QNode *current = head;
    while (current != nullptr)
    {
        out << " " << current->info;
        current = current->next;
    }
}
