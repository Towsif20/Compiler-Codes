#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

class SymbolInfo
{
    string name;
    string type;

public:

    SymbolInfo * next;

    SymbolInfo(string n, string t)
    {
        name = n;
        type = t;
        next = NULL;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setType(string type)
    {
        this->type = type;
    }

    string getName()
    {
        return name;
    }

    string getType()
    {
        return type;
    }
};

class ScopeTable
{
    SymbolInfo ** table;

    int size;

    int id;

    static int count;

    int hash(string key)
    {
        int h = 7;

        int len = key.length();

        for (int i = 0; i < len ; i++)
        {
            h = h*37 + key[i];
        }

        return h%size;
    }

public:

    ScopeTable * parentScope;

    ScopeTable(int n)
    {
        size = n;

        table = new SymbolInfo*[size];

        for(int i=0; i<size; i++)
        {
            table[i] = NULL;
        }

        count++;

        id = count;

        parentScope = NULL;
    }

    bool insert(string name, string type);
    SymbolInfo * lookUp(string name);
    bool Delete(string name);
    void print();
    int getSize()
    {
        return size;
    }

    int getId(){ return id; }

    ~ScopeTable();

};

SymbolInfo * ScopeTable::lookUp(string name)
{
    int ind = hash(name);

    SymbolInfo * temp = table[ind];

    int pos = 0;

    while(temp != NULL)
    {
        if(temp->getName().compare(name)==0)
        {
            cout<<"found in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;
            break;
        }

        temp = temp->next;
        pos++;
    }


    //if(temp == NULL) cout<<"not found\n";
    return temp;
}

bool ScopeTable::insert(string name, string type)
{
    SymbolInfo * s = lookUp(name);

    if(s != NULL)
        return false;

    int ind = hash(name);

    SymbolInfo * temp = new SymbolInfo(name, type);

    //cout<<"working?? \n";

    SymbolInfo * t = table[ind];

    int pos = 0;

    if(t == NULL)
    {
        table[ind] = temp;
        table[ind]->next = NULL;

        cout<<"inserted in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;

        return true;
    }

    pos++;

    while(t->next != NULL)
       {
           t = t->next;

           pos++;
       }
    //cout<<"working?? \n";

    t->next = temp;

    cout<<"inserted in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;

    return true;
}

bool ScopeTable::Delete(string name)
{
    SymbolInfo * s = lookUp(name);

    if(s == NULL)
        return false;

    int ind = hash(name);

    SymbolInfo * temp = table[ind];

    SymbolInfo * prev = temp;

    int pos = 0;

    while(temp != NULL)
    {
        if(temp->getName().compare(name)==0)
        {
            break;
        }

        prev = temp;

        temp = temp->next;

        pos++;

    }

    if(temp == table[ind])
    {
        table[ind] = table[ind]->next;

        delete temp;

        cout<<"Deleted in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;

        return true;
    }

    else
    {
        prev->next = temp->next;

        delete temp;

        cout<<"Deleted in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;

        return true;
    }
}

void ScopeTable::print()
{
    cout<<"ScopeTable # "<<id<<endl<<endl;

    for(int i=0; i<size; i++)
    {
        SymbolInfo * temp = table[i];

        cout<<i<<" ---> ";

        while(temp!= NULL)
        {
            cout<<"< "<<temp->getName()<<" : "<<temp->getType()<<" >     ";

            temp = temp->next;
        }

        cout<<endl;
    }

    cout<<endl;
}

ScopeTable::~ScopeTable()
{
    for(int i =0; i<size; i++)
    {
        SymbolInfo * temp = table[i];

        SymbolInfo * prev = temp;

        while(temp != NULL)
        {
            prev = temp;

            temp = temp->next;

            delete prev;
        }
    }

    delete table;

    //delete parentScope;
}

class SymbolTable
{
    int size;

    ScopeTable * current;

    int count;

public:

    SymbolTable(int n)
    {
        count = 1;

        size = n;

        current = new ScopeTable(size);

        current->parentScope = NULL;
    }

    void EnterScope(int n);

    void ExitScope();

    bool insert(string name, string type);

    bool remove(string name);

    SymbolInfo * lookup(string name);

    void printCurrent();

    void printAll();

};

void SymbolTable::EnterScope(int n)
{
    ScopeTable * s = new ScopeTable(n);

    ScopeTable * temp = current;

    current = s;

    current->parentScope = temp;

    count++;

    cout<<"New Scopetable with id "<<current->getId()<<" created\n\n";
}

void SymbolTable::ExitScope()
{
    ScopeTable * temp = current;

    if(temp->parentScope == NULL)
        return;

    current = current->parentScope;

    cout<<"Scopetable with id "<<temp->getId()<<" removed\n\n";

    temp->~ScopeTable();

    count--;

}

bool SymbolTable::insert(string name, string type)
{
    return current->insert(name, type);
}

bool SymbolTable::remove(string name)
{
    return current->Delete(name);
}

SymbolInfo * SymbolTable::lookup(string name)
{
    ScopeTable * temp = current;

    SymbolInfo * s = NULL;

    while(temp != NULL)
    {
        s = temp->lookUp(name);

        if(s != NULL)
            break;

        temp = temp->parentScope;
    }

    if(s == NULL)
        cout<<"not found\n"<<endl;

    return s;
}

void SymbolTable::printCurrent()
{
    current->print();
}

void SymbolTable::printAll()
{
    ScopeTable * temp = current;

    while(temp != NULL)
    {
        //cout<<"Symbol Table #"<<
        temp->print();

        temp = temp->parentScope;
    }
}

int ScopeTable::count = 0;

int main()
{
    ifstream input("input.txt");

    int size;

    input>>size;

    SymbolTable s(size);

    char ch, p;

    string name, type;

    while(input>>ch)
    {

        if(ch == 'I')
        {
            input>>name>>type;

            s.insert(name, type);
        }

        else if(ch == 'L')
        {
            input>>name;

            s.lookup(name);
        }

        else if(ch == 'D')
        {
            input>>name;

            s.remove(name);
        }

        else if(ch == 'P')
        {
            input>>p;

            if(p == 'A')
                s.printAll();

            else if(p == 'C')
                s.printCurrent();
        }

        else if(ch == 'S')
        {
            s.EnterScope(size);
        }

        else if(ch == 'E')
        {
            s.ExitScope();
        }

        else
            break;

        //s.printAll();

    }
}






















