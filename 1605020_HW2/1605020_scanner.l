%option noyywrap

%x STRING
%x COMMENT

%{
#include<stdio.h>
#include<stdlib.h>

#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

FILE *logout;
FILE *tokenout;


string str;
int currentline;

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
            h = h*31 + key[i];
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



















int line_count=1;
int errors = 0;

SymbolTable table(10);

%}


WHITESPACE [ \t\f\r\v]+ 
INTEGER_LITERALS [0-9]+
FLOAT_POINT_LITERALS [0-9]*\.?[0-9]+
NEWLINE \n
IDENTIFIER [A-Za-z_]+[A-Za-z0-9_]*


%%

{NEWLINE} {line_count++;}

"if"		{
			fprintf(tokenout,"<IF>");
			fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}
		
"else"		{
			fprintf(tokenout,"<ELSE>");
			fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"for" 		{
			fprintf(tokenout,"<FOR>");
			fprintf(logout,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);	
			fprintf(logout,"\n");
			
		}

"do"		{
			fprintf(tokenout,"<DO>");
			fprintf(logout,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}
		
"while"		{
			fprintf(tokenout,"<WHILE>");
			fprintf(logout,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}
		
"break"		{			
			fprintf(tokenout,"<BREAK>");
			fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"int"		{
			fprintf(tokenout,"<INT>");
			fprintf(logout,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}


"char"		{
			fprintf(tokenout,"<CHAR>");
			fprintf(logout,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}
		
"float"		{
			fprintf(tokenout,"<FLOAT>");
			fprintf(logout,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"double"	{
			fprintf(tokenout,"<DOUBLE>");
			fprintf(logout,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"void"		{
			fprintf(tokenout,"<VOID>");
			fprintf(logout,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"return"	{
			fprintf(tokenout,"<RETURN>");
			fprintf(logout,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"switch"	{
			fprintf(tokenout,"<SWITCH>");
			fprintf(logout,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"case"		{
			fprintf(tokenout,"<CASE>");
			fprintf(logout,"Line no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"default"	{
			fprintf(tokenout,"<DEFAULT>");
			fprintf(logout,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}

"continue"	{
			fprintf(tokenout,"<CONTINUE>");
			fprintf(logout,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");
			
		}



"+"		|

"-"		{
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
			
			string s = yytext;
			bool f = table.insert(s,"ADDOP");
			if(f) 	table.printAll();
			fprintf(logout,"\n");
			
		}
		
"*" |
"/" |
"%" 		{
				fprintf(tokenout,"<MULOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);
				
				string s = yytext;
				bool f = table.insert(s,"MULOP");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				
		}

"++" |
"--" 		{
				fprintf(tokenout,"<INCOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);
				
				string s = yytext;
				bool f = table.insert(s,"INCOP");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				
				
				
		}

"<" |
">" |
"<=" |
">=" |
"==" |
"!=" 		{
				fprintf(tokenout,"<RELOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);
				
				string s = yytext;
				bool f = table.insert(s,"RELOP");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				
		}

"=" 		{
				fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
				string s = yytext;
				bool f = table.insert(s,"ASSIGNOP");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				
		}

"&&" | 
"||" 		{
				fprintf(tokenout,"<LOGICOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);
				string s = yytext;
				bool f = table.insert(s,"LOGICOP");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				
		}

"&" |
"|" |
"^" |
"<<" |
">>" 		{
				fprintf(tokenout,"<BITOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <BITOP> Lexeme %s found\n",line_count,yytext);
				string s = yytext;
				bool f = table.insert(s,"BITOP");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				
		}


"!" 		{
				fprintf(tokenout,"<NOT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <NOT> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
				
		}




"(" 		{
				fprintf(tokenout,"<LPAREN,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LPAREN> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}

")" 		{
				fprintf(tokenout,"<RPAREN,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RPAREN> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}

"{" 		{
				fprintf(tokenout,"<LCURL,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LCURL> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}



"}" 		{
				fprintf(tokenout,"<RCURL,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RCURL> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}

"[" 		{
				fprintf(tokenout,"<LTHIRD,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LTHIRD> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}

"]" 		{
				fprintf(tokenout,"<RTHIRD,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RTHIRD> Lexeme %s found\n",line_count,yytext);
		}

"," 		{
				fprintf(tokenout,"<COMMA,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}

";" 		{
				fprintf(tokenout,"<SEMICOLON,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
		}



{INTEGER_LITERALS}	{
				fprintf(tokenout,"<CONST_INT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
				
				string s = yytext;
				bool f = table.insert(s,"CONST_INT");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				//insert in symbol table and print symbol table content(only non empty buckets)
			}



{FLOAT_POINT_LITERALS}	{
				fprintf(tokenout,"<CONST_FLOAT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
				
				string s = yytext;
				bool f = table.insert(s,"CONST_FLOAT");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				//insert in symbol table and print symbol table content(only non empty buckets)
			}


\'[^\\]\' 	{
				fprintf(tokenout,"<CONST_CHAR,%c>",yytext[1]);
				fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");
				
				string s = yytext;
				bool f = table.insert(s,"CONST_CHAR");
				if(f) 	table.printAll();
				fprintf(logout,"\n");
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
			
			

\'[\\][\\\"abfnrtv0]\'	{

							char ascii;
							
							if(yytext[2]=='a') ascii = 7;
							if(yytext[2]=='b') ascii = 8;
							if(yytext[2]=='f') ascii = 12;
							if(yytext[2]=='n') ascii = 10;
							if(yytext[2]=='r') ascii = 13;
							if(yytext[2]=='t') ascii = 9;
							if(yytext[2]=='v') ascii = 11;
							if(yytext[2]=='0') ascii = 0;
							if(yytext[2]=='\\') ascii = 92;
							if(yytext[2]=='\"') ascii = 34;
							
							fprintf(tokenout,"<CONST_CHAR,%c>",ascii);
							fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
							fprintf(logout,"\n");
							
							string s = yytext;
							bool f = table.insert(s,"CONST_CHAR");
							if(f) 	table.printAll();
							fprintf(logout,"\n");
														
						}










{WHITESPACE}	{}	


{IDENTIFIER}	{
			fprintf(tokenout,"<ID,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
			
			string s = yytext;
			bool f = table.insert(s,"ID");
			if(f) 	table.printAll();
			fprintf(logout,"\n");
			//insert in symbol table and print symbol table content(only non empty buckets)
		}		



\"		{
			BEGIN STRING;
			str = yytext;
			currentline = line_count;
			
		}
		
		
<STRING>([^"\n]|[\\.])*    {   
                                str=str + yytext;
                                
                            }


<STRING>\"      {           
                         str=str + yytext;
                         fprintf(logout,"Line no %d: TOKEN <STRING> Lexeme %s found\n",currentline,str.c_str());
                         fprintf(logout,"\n"); 
                         
                         fprintf(tokenout,"<STRING, ");
                         
                         int len = str.size()-1;
                         
                         for(int i=1;i<len;i++)
                         {
                         	if(str[i] == '\\')
                         		{
                         			if(str[i+1] == '0')
                         				{
                         					i++;
                         					fprintf(tokenout, "\0");
                         				}
                         				
                         			if(str[i+1] == 'a')
                         				{
                         					i++;
                         					fprintf(tokenout, "\a");
                         				}
                         				
                         			if(str[i+1] == 'b')
                         				fprintf(tokenout, "\b");	
                         			
                         			if(str[i+1] == 'f')
                         				{
                         					fprintf(tokenout, "\f");
                         					i++;
                         				}
                         				
                         			if(str[i+1] == 'n')
                         				{
                         					fprintf(tokenout, "\n");
                         					i++;
                         				}
                         			
                         			if(str[i+1] == 'r')
                         				{
                         					fprintf(tokenout, "\r");
                         					i++;
                         				}
                         				
                         			if(str[i+1] == 'v')
                         				{
                         					fprintf(tokenout, "\v");
                         					i++;
                         				}
                         			
                         			if(str[i+1] == 't')
                         				{
                         					fprintf(tokenout, "\t");
                         					i++;
                         				}
                         			if(str[i+1] == '\\')
                         				{
                         					fprintf(tokenout, "\\");
                         					i++;
                         				}	
                         				
                         			if(str[i+1] == '\"')
                         				{
                         					i++;
                         					fprintf(tokenout, "\"");
                         				}
                         		}
                         		
                         	else
                         		{	
                         			fprintf(tokenout,"%c",str[i]);
                         		}
                         }
                         
                         fprintf(tokenout," >");
                         
                         BEGIN INITIAL; 
                }


<STRING>\n				{
							line_count++;
							
							 if(str[strlen(str.c_str())-2]=='\\') 
							 	 {  str=str+yytext; }
							 	 
                     		 else  
                     		 {   
                     		 	 fprintf(logout,"Error at line %d: Unterminated String %s \n",currentline,str.c_str());
                     		 	 errors++;  
                     		 	 BEGIN INITIAL; 
                     		 }
						}




\/\/			{
						BEGIN COMMENT;
						
						str = yytext;
						
						currentline = line_count;
				}
				
				
<COMMENT>[^\n]*   { 
                         str=str+yytext;
                  }



<COMMENT>\n     {   
                    
                    if(str[strlen(str.c_str())-2]=='\\')  
                    	{ 
                    	 str=str+yytext; 
                    	}
                    	
                    else    
                    	{  
                    		fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",currentline,str.c_str()); 
                    		BEGIN INITIAL;   
                    	}

                }



\/\*([^\/]|[\n])*\*\/   {

				        //fprintf(tokenout,"<COMMENT,%s> ",yytext);
				        fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count,yytext);
                        for(int i=0;i<strlen(yytext);i++)
                            {
                                if(yytext[i]=='\n')  line_count++;
                            }
                        fprintf(logout,"\n");

						}
				

{FLOAT_POINT_LITERALS}"\."[0-9]* 	{
										errors++;
										fprintf(logout,"Error at Line no %d: too many decimal point %s \n",line_count,yytext);
									}


{INTEGER_LITERALS}{IDENTIFIER} 	{
					errors++;
					fprintf(logout,"Error at Line no %d: Invalid prefix on ID or invalid suffix on Number %s \n",line_count,yytext);
							}


[0-9]*\.?[0-9]+[eE][-+]?[0-9]*\.[0-9]*		{
		                                     errors++;
						                     fprintf(logout,"Error at line %d: Ill formed number %s \n",line_count,yytext);
		                                     fprintf(logout,"\n");
						           
				            	             }



\'[^'\n]{1}  |

\'[\\]\'   {
                errors++;
		        fprintf(logout,"Error at line %d: Unterminated character  %s \n",line_count,yytext);
                fprintf(logout,"\n");		             
		   }


\'[^'\n\\][^'\n\\]+\'        {
                                    errors++;
		                            fprintf(logout,"Error at line %d: Multi character constant error  %s \n",line_count,yytext);
                                    fprintf(logout,"\n");		             
		                     }

\'\'    {       errors++;           
                fprintf(logout,"Error at line %d: Empty character constant error  %s \n",line_count,yytext);
                fprintf(logout,"\n");		             
        }

\/\*([\n]|[^\/])*     { 
                          errors++;
		                  fprintf(logout,"Error at line %d: Unterminated comment  %s \n",line_count,yytext);
                          for(int i=0;i<strlen(yytext);i++)
                            {
                                if(yytext[i]=='\n')  line_count++;
                            }
                          fprintf(logout,"\n");		             
		              }


<<EOF>>   {     
				//line_count--;
                table.printAll();    
                            
                fprintf(logout,"Total Lines: %d\n",line_count);
                fprintf(logout,"Total Errors: %d\n",errors);
                return 0;
          }








%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		//printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		//printf("Cannot open specified file\n");
		return 0;
	}
	
	logout = fopen("1605020_log.txt","w");
	tokenout = fopen("1605020_token.txt","w");

	yyin= fin;
	yylex();
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}
