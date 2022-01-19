#include<bits/stdc++.h>
#include"function.h"

using namespace std;

class SymbolInfo
{
public:

    string name;
    string type;
   
	
	
    SymbolInfo * next;
    
    string dectype;
    
    Function * function;
    
    bool defined = false;
    
    vector<string> funcparam;

	SymbolInfo()
    {
    	function = NULL;
    	next = NULL;
    }
        
    SymbolInfo(string n, string t, string decType="")
    {
        name = n;
        type = t;
        this->dectype = decType;
        
        next = NULL;
        
        function = NULL;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setType(string Type)
    {
        this->type = Type;
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

    

    //static int count;

    int hash(string key)
    {
        int h = 7;

        int len = key.length();

        for (int i = 0; i < len ; i++)
        {
            h = h*31 + key[i];
        }

        return h%size;
    }

public:

	int id = 1;
	
	int exited = 1;
	
    ScopeTable * parentScope;

    ScopeTable(int n)
    {
        size = n;

        table = new SymbolInfo*[size];

        for(int i=0; i<size; i++)
        {
            table[i] = NULL;
        }

        //count++;

        //id = count;

        parentScope = NULL;
    }

    
    bool insert(string name, string type, string decType="")
{
    SymbolInfo * s = lookUp(name);

    if(s != NULL)
        return false;

    int ind = hash(name);

    SymbolInfo * temp = new SymbolInfo(name, type, decType);

    //cout<<"working?? \n";

    SymbolInfo * t = table[ind];

    int pos = 0;

    if(t == NULL)
    {
        table[ind] = temp;
        table[ind]->next = NULL;

        //cout<<"inserted in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;

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

    //cout<<"inserted in ScopeTable# "<<id<<" at position "<<ind<<" , "<<pos<<endl<<endl;

    return true;
}
    
    
    SymbolInfo * lookUp(string name)
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
   	
   	
   	bool Delete(string name)
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

   	
   	
    
    
    void print(FILE * logout)
{


    //file<<"ScopeTable # "<<id<<endl<<endl;

    fprintf(logout,"ScopeTable # %d\n",id);

    for(int i=0; i<size; i++)
    {
        SymbolInfo * temp = table[i];

        //file<<i<<" ---> ";
        fprintf(logout," ---> ");

        while(temp!= NULL)
        {
            //file<<"< "<<temp->getName()<<" : "<<temp->getType()<<" >     ";

            //fprintf(logout, "< %s : %s >    ",(char*)temp->getName(),temp->getType());

            fprintf(logout, "< ");

            int len = temp->getName().size();

            for(int i=0;i<len;i++)
            {
            	fprintf(logout, "%c",temp->getName()[i]);
            }

            fprintf(logout, " : ");

            len = temp->getType().size();

            for(int i=0;i<len;i++)
            {
            	fprintf(logout, "%c",temp->getType()[i]);
            }

           	fprintf(logout, " >");

            temp = temp->next;
        }

        fprintf(logout,"\n");
    }

     fprintf(logout,"\n");
}
    
    
    int getSize()
    {
        return size;
    }

    int getId(){ return id; }

    ~ScopeTable()
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

};










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

    void EnterScope(FILE* fp, int n)
{
    ScopeTable * s = new ScopeTable(n);

    ScopeTable * temp = current;

    current = s;

    current->parentScope = temp;

	current->id = current->parentScope->id + current->parentScope->exited;
		
    count++;

    //cout<<"New Scopetable with id "<<current->getId()<<" created\n\n";
    fprintf(fp, "New ScopeTable with id %d created\n\n", current->id);
}



    void ExitScope(FILE * fp)
{
    ScopeTable * temp = current;
	
	if(temp == NULL)
		return;
		
    if(temp->parentScope == NULL)
        return;

    current = current->parentScope;

    //cout<<"Scopetable with id "<<temp->getId()<<" removed\n\n";
    
    fprintf(fp, "ScopeTable with id %d removed\n\n", temp->id);

    temp->~ScopeTable();

    count--;
    
    current->exited--;

}



    bool insert(string name, string type, string decType = "")
{
    return current->insert(name, type, decType);
}



    bool remove(string name)
{
    return current->Delete(name);
}

	SymbolInfo * lookupcurrent(string name)
	{
		return current->lookUp(name);
	}

    SymbolInfo * lookup(string name)
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



    void printCurrent(FILE * logout)
{
    current->print(logout);
}


    void printAll(FILE * logout)
{
    ScopeTable * temp = current;

    while(temp != NULL)
    {
        //cout<<"Symbol Table #"<<
        temp->print(logout);

        temp = temp->parentScope;
    }
}

};










