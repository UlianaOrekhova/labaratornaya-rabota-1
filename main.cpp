#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Array.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "FullTree.h"

using namespace std;

struct Database
{
    map<string, ArrayData> arrays;
    map<string, SSpisok> singlyLists;
    map<string, DSpisok> doublyLists;
    map<string, StackData> stacks;
    map<string, QueueData> queues;
    map<string, FullTree> trees;
};

void printResult(bool result)
{
    cout << (result ? "-> TRUE" : "-> FALSE") << endl;
}

void printValues(const ArrayData &items)
{
    cout << "->";
    if (items.count == 0)
        cout << " (empty)";
    else
        arrayWrite(items, cout);
    cout << endl;
}

void printValues(const SSpisok &items)
{
    cout << "->";
    if (items.head == nullptr)
        cout << " (empty)";
    else
        listWrite(items, cout);
    cout << endl;
}

void printValues(const DSpisok &items)
{
    cout << "->";
    if (items.head == nullptr)
        cout << " (empty)";
    else
        dListWrite(items, cout);
    cout << endl;
}

void printValues(const StackData &items)
{
    cout << "->";
    if (items.top == nullptr)
        cout << " (empty)";
    else
        stackWrite(items, cout);
    cout << endl;
}

void printValues(const QueueData &items)
{
    cout << "->";
    if (items.head == nullptr)
        cout << " (empty)";
    else
        queueWrite(items, cout);
    cout << endl;
}

void printValues(const FullTree &items)
{
    cout << "->";
    if (items.root == nullptr)
        cout << " (empty)";
    else
        treeWrite(items, cout);
    cout << endl;
}

void loadData(const string &fileName, Database &db)
{
    ifstream file(fileName);
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        stringstream input(line);
        char type;
        string name;
        if (!(input >> type >> name))
            continue;

        int value;
        if (type == 'M')
        {
            ArrayData &items = db.arrays[name];
            while (input >> value)
                arrayPushBack(items, value);
        }
        else if (type == 'F')
        {
            SSpisok &items = db.singlyLists[name];
            while (input >> value)
                listPushBack(items, value);
        }
        else if (type == 'L')
        {
            DSpisok &items = db.doublyLists[name];
            while (input >> value)
                dListPushBack(items, value);
        }
        else if (type == 'S')
        {
            StackData &items = db.stacks[name];
            while (input >> value)
                stackPush(items, value);
        }
        else if (type == 'Q')
        {
            QueueData &items = db.queues[name];
            while (input >> value)
                queuePush(items, value);
        }
        else if (type == 'T')
        {
            FullTree &items = db.trees[name];
            while (input >> value)
                treeInsert(items, value);
        }
    }
}

void saveData(const string &fileName, const Database &db)
{
    ofstream file(fileName);
    if (!file.is_open())
    {
        cout << "Cannot write file" << endl;
        return;
    }

    for (const auto &item : db.arrays)
    {
        file << "M " << item.first;
        arrayWrite(item.second, file);
        file << endl;
    }
    for (const auto &item : db.singlyLists)
    {
        file << "F " << item.first;
        listWrite(item.second, file);
        file << endl;
    }
    for (const auto &item : db.doublyLists)
    {
        file << "L " << item.first;
        dListWrite(item.second, file);
        file << endl;
    }
    for (const auto &item : db.stacks)
    {
        file << "S " << item.first;
        stackWrite(item.second, file);
        file << endl;
    }
    for (const auto &item : db.queues)
    {
        file << "Q " << item.first;
        queueWrite(item.second, file);
        file << endl;
    }
    for (const auto &item : db.trees)
    {
        file << "T " << item.first;
        treeWrite(item.second, file);
        file << endl;
    }
}

void printNamed(const string &name, const Database &db)
{
    auto item = db.arrays.find(name);
    if (item != db.arrays.end())
    {
        printValues(item->second);
        return;
    }

    auto f = db.singlyLists.find(name);
    if (f != db.singlyLists.end())
    {
        printValues(f->second);
        return;
    }

    auto l = db.doublyLists.find(name);
    if (l != db.doublyLists.end())
    {
        printValues(l->second);
        return;
    }

    auto s = db.stacks.find(name);
    if (s != db.stacks.end())
    {
        printValues(s->second);
        return;
    }

    auto q = db.queues.find(name);
    if (q != db.queues.end())
    {
        printValues(q->second);
        return;
    }

    auto t = db.trees.find(name);
    if (t != db.trees.end())
    {
        printValues(t->second);
        return;
    }

    cout << "-> Container not found" << endl;
}

void printHelp()
{
    cout << "MCREATE name, MPUSH name value, MINSERT name index value, MGET name index, MDEL name index, MSET name index value, MLEN name, MREAD name" << endl;
    cout << "FPUSH/FTAIL name value, FHEAD name value, FBEFORE name target value, FAFTER name target value" << endl;
    cout << "FDEL name value, FDELAT name index, FDELHEAD name, FDELTAIL name, FDELBEFORE name target, FDELAFTER name target, FGET name index, FFIND name value, FREAD name" << endl;
    cout << "L commands: LPUSH/LTAIL/LHEAD/LBEFORE/LAFTER/LDEL/LDELAT/LDELHEAD/LDELTAIL/LDELBEFORE/LDELAFTER/LGET/LFIND/LREAD" << endl;
    cout << "SPUSH name value, SPOP name, SGET name, SREAD name; QPUSH name value, QPOP name, QGET name, QREAD name" << endl;
    cout << "TINSERT name value, TGET name value, TREAD name, TISFULL name, ISMEMBER name value, PRINT name, HELP, EXIT" << endl;
}

void execute(const string &command, Database &db, bool &changed)
{
    changed = false;
    stringstream input(command);
    string operation;
    input >> operation;

    if (operation.empty())
        return;

    if (operation == "HELP")
    {
        printHelp();
        return;
    }

    if (operation == "PRINT")
    {
        string name;
        if (input >> name)
            printNamed(name, db);
        else
            cout << "Missing container name" << endl;
        return;
    }

    string name;
    int value, index, target;

    if (operation == "MCREATE")
    {
        if (!(input >> name))
        {
            cout << "Missing container name" << endl;
            return;
        }
        if (db.arrays.find(name) == db.arrays.end())
        {
            db.arrays[name];
            changed = true;
            cout << "-> OK" << endl;
        }
        else
            cout << "-> EXISTS" << endl;
        return;
    }

    if (operation == "MPUSH")
    {
        if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
        arrayPushBack(db.arrays[name], value);
        changed = true;
        cout << "-> OK" << endl;
        return;
    }
    if (operation == "MINSERT")
    {
        if (!(input >> name >> index >> value)) { cout << "Invalid arguments" << endl; return; }
        if (arrayInsertAt(db.arrays[name], index, value)) { changed = true; cout << "-> OK" << endl; }
        else cout << "-> Invalid index" << endl;
        return;
    }
    if (operation == "MGET")
    {
        if (!(input >> name >> index)) { cout << "Invalid arguments" << endl; return; }
        auto item = db.arrays.find(name);
        if (item != db.arrays.end() && arrayGetAt(item->second, index, value)) cout << "-> " << value << endl;
        else cout << "-> Invalid index or container" << endl;
        return;
    }
    if (operation == "MDEL")
    {
        if (!(input >> name >> index)) { cout << "Invalid arguments" << endl; return; }
        auto item = db.arrays.find(name);
        if (item != db.arrays.end() && arrayEraseAt(item->second, index, value)) { changed = true; cout << "-> " << value << endl; }
        else cout << "-> Invalid index or container" << endl;
        return;
    }
    if (operation == "MSET")
    {
        if (!(input >> name >> index >> value)) { cout << "Invalid arguments" << endl; return; }
        auto item = db.arrays.find(name);
        if (item != db.arrays.end() && arraySetAt(item->second, index, value)) { changed = true; cout << "-> OK" << endl; }
        else cout << "-> Invalid index or container" << endl;
        return;
    }
    if (operation == "MLEN")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.arrays.find(name);
        if (item != db.arrays.end()) cout << "-> " << arrayLength(item->second) << endl;
        else cout << "-> 0" << endl;
        return;
    }
    if (operation == "MREAD")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.arrays.find(name);
        if (item != db.arrays.end()) printValues(item->second);
        else cout << "-> Container not found" << endl;
        return;
    }

    if (operation == "FPUSH" || operation == "FTAIL" || operation == "FHEAD" || operation == "FBEFORE" || operation == "FAFTER")
    {
        if (operation == "FBEFORE" || operation == "FAFTER")
        {
            if (!(input >> name >> target >> value)) { cout << "Invalid arguments" << endl; return; }
            bool result;
            if (operation == "FBEFORE")
                result = listInsertBefore(db.singlyLists[name], target, value);
            else
                result = listInsertAfter(db.singlyLists[name], target, value);
            if (result) { changed = true; cout << "-> OK" << endl; }
            else cout << "-> Target not found" << endl;
        }
        else
        {
            if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
            if (operation == "FHEAD")
                listPushFront(db.singlyLists[name], value);
            else
                listPushBack(db.singlyLists[name], value);
            changed = true;
            cout << "-> OK" << endl;
        }
        return;
    }

    if (operation == "FDEL" || operation == "FDELAT" || operation == "FDELHEAD" || operation == "FDELTAIL" || operation == "FDELBEFORE" || operation == "FDELAFTER")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.singlyLists.find(name);
        if (item == db.singlyLists.end()) { cout << "-> Container not found" << endl; return; }
        bool result = false;
        if (operation == "FDEL")
        {
            if (!(input >> value)) { cout << "Missing value" << endl; return; }
            result = listEraseValue(item->second, value);
        }
        else if (operation == "FDELAT")
        {
            if (!(input >> index)) { cout << "Missing index" << endl; return; }
            result = listEraseAt(item->second, index, value);
        }
        else if (operation == "FDELHEAD") result = listEraseHead(item->second, value);
        else if (operation == "FDELTAIL") result = listEraseTail(item->second, value);
        else if (operation == "FDELBEFORE")
        {
            if (!(input >> target)) { cout << "Missing target" << endl; return; }
            result = listEraseBefore(item->second, target, value);
        }
        else
        {
            if (!(input >> target)) { cout << "Missing target" << endl; return; }
            result = listEraseAfter(item->second, target, value);
        }
        if (result) { changed = true; cout << "-> " << value << endl; }
        else cout << "-> Element not found" << endl;
        return;
    }

    if (operation == "FGET" || operation == "FFIND" || operation == "FREAD")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.singlyLists.find(name);
        if (item == db.singlyLists.end()) { cout << "-> Container not found" << endl; return; }
        if (operation == "FREAD") printValues(item->second);
        else if (operation == "FGET")
        {
            if (!(input >> index)) { cout << "Missing index" << endl; return; }
            if (listGetAt(item->second, index, value)) cout << "-> " << value << endl;
            else cout << "-> Invalid index" << endl;
        }
        else
        {
            if (!(input >> value)) { cout << "Missing value" << endl; return; }
            printResult(listContains(item->second, value));
        }
        return;
    }

    if (operation == "LPUSH" || operation == "LTAIL" || operation == "LHEAD" || operation == "LBEFORE" || operation == "LAFTER")
    {
        if (operation == "LBEFORE" || operation == "LAFTER")
        {
            if (!(input >> name >> target >> value)) { cout << "Invalid arguments" << endl; return; }
            bool result;
            if (operation == "LBEFORE")
                result = dListInsertBefore(db.doublyLists[name], target, value);
            else
                result = dListInsertAfter(db.doublyLists[name], target, value);
            if (result) { changed = true; cout << "-> OK" << endl; }
            else cout << "-> Target not found" << endl;
        }
        else
        {
            if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
            if (operation == "LHEAD")
                dListPushFront(db.doublyLists[name], value);
            else
                dListPushBack(db.doublyLists[name], value);
            changed = true;
            cout << "-> OK" << endl;
        }
        return;
    }

    if (operation == "LDEL" || operation == "LDELAT" || operation == "LDELHEAD" || operation == "LDELTAIL" || operation == "LDELBEFORE" || operation == "LDELAFTER")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.doublyLists.find(name);
        if (item == db.doublyLists.end()) { cout << "-> Container not found" << endl; return; }
        bool result = false;
        if (operation == "LDEL")
        {
            if (!(input >> value)) { cout << "Missing value" << endl; return; }
            result = dListEraseValue(item->second, value);
        }
        else if (operation == "LDELAT")
        {
            if (!(input >> index)) { cout << "Missing index" << endl; return; }
            result = dListEraseAt(item->second, index, value);
        }
        else if (operation == "LDELHEAD") result = dListEraseHead(item->second, value);
        else if (operation == "LDELTAIL") result = dListEraseTail(item->second, value);
        else if (operation == "LDELBEFORE")
        {
            if (!(input >> target)) { cout << "Missing target" << endl; return; }
            result = dListEraseBefore(item->second, target, value);
        }
        else
        {
            if (!(input >> target)) { cout << "Missing target" << endl; return; }
            result = dListEraseAfter(item->second, target, value);
        }
        if (result) { changed = true; cout << "-> " << value << endl; }
        else cout << "-> Element not found" << endl;
        return;
    }

    if (operation == "LGET" || operation == "LFIND" || operation == "LREAD")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.doublyLists.find(name);
        if (item == db.doublyLists.end()) { cout << "-> Container not found" << endl; return; }
        if (operation == "LREAD") printValues(item->second);
        else if (operation == "LGET")
        {
            if (!(input >> index)) { cout << "Missing index" << endl; return; }
            if (dListGetAt(item->second, index, value)) cout << "-> " << value << endl;
            else cout << "-> Invalid index" << endl;
        }
        else
        {
            if (!(input >> value)) { cout << "Missing value" << endl; return; }
            printResult(dListContains(item->second, value));
        }
        return;
    }

    if (operation == "SPUSH")
    {
        if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
        stackPush(db.stacks[name], value);
        changed = true;
        cout << "-> OK" << endl;
        return;
    }
    if (operation == "SPOP" || operation == "SGET" || operation == "SREAD")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.stacks.find(name);
        if (item == db.stacks.end()) { cout << "-> Container not found" << endl; return; }
        if (operation == "SREAD") printValues(item->second);
        else if (operation == "SGET")
        {
            if (stackPeek(item->second, value)) cout << "-> " << value << endl;
            else cout << "-> Stack is empty" << endl;
        }
        else
        {
            if (stackPop(item->second, value)) { changed = true; cout << "-> " << value << endl; }
            else cout << "-> Stack is empty" << endl;
        }
        return;
    }

    if (operation == "QPUSH")
    {
        if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
        queuePush(db.queues[name], value);
        changed = true;
        cout << "-> OK" << endl;
        return;
    }
    if (operation == "QPOP" || operation == "QGET" || operation == "QREAD")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.queues.find(name);
        if (item == db.queues.end()) { cout << "-> Container not found" << endl; return; }
        if (operation == "QREAD") printValues(item->second);
        else if (operation == "QGET")
        {
            if (queuePeek(item->second, value)) cout << "-> " << value << endl;
            else cout << "-> Queue is empty" << endl;
        }
        else
        {
            if (queuePop(item->second, value)) { changed = true; cout << "-> " << value << endl; }
            else cout << "-> Queue is empty" << endl;
        }
        return;
    }

    // Binary tree commands
    if (operation == "TINSERT")
    {
        if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
        if (treeInsert(db.trees[name], value))
        {
            changed = true;
            cout << "-> OK" << endl;
        }
        else
            cout << "-> EXISTS" << endl;
        return;
    }

    if (operation == "TGET" || operation == "ISMEMBER")
    {
        if (!(input >> name >> value)) { cout << "Invalid arguments" << endl; return; }
        auto item = db.trees.find(name);
        bool result = (item != db.trees.end() && treeContains(item->second, value));
        printResult(result);
        return;
    }

    if (operation == "TISFULL" || operation == "TFULL")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.trees.find(name);
        if (item == db.trees.end())
            cout << "-> Container not found" << endl;
        else
            printResult(treeIsFull(item->second));
        return;
    }

    if (operation == "TREAD")
    {
        if (!(input >> name)) { cout << "Missing container name" << endl; return; }
        auto item = db.trees.find(name);
        if (item != db.trees.end()) printValues(item->second);
        else cout << "-> Container not found" << endl;
        return;
    }

    cout << "Unknown command. Enter HELP" << endl;
}

void clearDatabase(Database &db)
{
    for (auto &item : db.arrays)
        arrayClear(item.second);
    for (auto &item : db.singlyLists)
        listClear(item.second);
    for (auto &item : db.doublyLists)
        dListClear(item.second);
    for (auto &item : db.stacks)
        stackClear(item.second);
    for (auto &item : db.queues)
        queueClear(item.second);
    for (auto &item : db.trees)
        treeClear(item.second);
}

int main(int argc, char *argv[])
{
    string fileName = "file.data";
    string query;
    bool hasQuery = false;

    for (int i = 1; i < argc; i++)
    {
        string argument = argv[i];
        if (argument == "--file" && i + 1 < argc)
            fileName = argv[++i];
        else if (argument == "--query" && i + 1 < argc)
        {
            query = argv[++i];
            hasQuery = true;
        }
        else if (argument == "--help")
        {
            printHelp();
            return 0;
        }
    }

    Database db;
    loadData(fileName, db);

    if (hasQuery)
    {
        bool changed = false;
        execute(query, db, changed);
        if (changed)
            saveData(fileName, db);
    }
    else
    {
        cout << "Data structures. Enter HELP to see commands." << endl;
        string command;
        while (true)
        {
            cout << "> ";
            if (!getline(cin, command))
                break;
            if (command == "EXIT")
                break;
            bool changed = false;
            execute(command, db, changed);
            if (changed)
                saveData(fileName, db);
        }
    }

    clearDatabase(db);
    return 0;
}
