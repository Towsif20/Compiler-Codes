%{
#include<bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>

//int  count = 0;
#include "SymbolTable.h"
#define YYSTYPE SymbolInfo*

using namespace std;

int  yyparse();
int  yylex();

extern FILE * yyin;

FILE * parserLog;
FILE * parserError;

extern FILE * logout;
extern FILE * tokenout;

int  flag =0;
int  errFlag=0;

extern int  line_count;
extern int  errors;

SymbolTable *table;

extern char * yytext;




vector<SymbolInfo*> argList;
vector<SymbolInfo*> decList;
vector<SymbolInfo*> paramList;
vector<string> variables;
vector<string> functionVariables;
vector<pair<string, string>> arrayDec;
string curfunction;

void yyerror(char *s)
{
	errors++;

	//return;
}

int labelCount=0;
int tempCount=0;

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

void optimization(FILE * asmcode);


%}

%token IF ELSE FOR WHILE
%token INT FLOAT DOUBLE CHAR RETURN VOID
%token PRINTLN ADDOP MULOP ASSIGNOP RELOP LOGICOP NOT
%token SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP
%token CONST_INT CONST_FLOAT ID
%token DO SWITCH DEFAULT BREAK CASE CONTINUE CONST_CHAR BITOP

%left RELOP LOGICOP BITOP
%left ADDOP MULOP
//%right


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE







%%



start : program
	{
		//if(errors == 0)
		{
			string codes = "";

			codes += ".model small\n\.stack 100h\n\.data\n";

			for(int i=0;i<variables.size();i++)
			{
				codes += variables[i] + " dw ?\n";
			}

			for(int i=0;i<arrayDec.size();i++)
			{
				codes += arrayDec[i].first + " dw " + arrayDec[i].second + " dup(?)\n";
			}

			$1->code = codes + ".code\n" + $1->code;

			$1->code = $1->code + "OUTDEC PROC  \n\
		    PUSH AX \n\
		    PUSH BX \n\
		    PUSH CX \n\
		    PUSH DX  \n\
		    CMP AX,0 \n\
		    JGE BEGIN \n\
		    PUSH AX \n\
		    MOV DL,'-' \n\
		    MOV AH,2 \n\
		    INT 21H \n\
		    POP AX \n\
		    NEG AX \n\
		    \n\
		    BEGIN: \n\
		    XOR CX,CX \n\
		    MOV BX,10 \n\
		    \n\
		    REPEAT: \n\
		    XOR DX,DX \n\
		    DIV BX \n\
		    PUSH DX \n\
		    INC CX \n\
		    OR AX,AX \n\
		    JNE REPEAT \n\
		    MOV AH,2 \n\
		    \n\
		    PRINT_LOOP: \n\
		    POP DX \n\
		    ADD DL,30H \n\
		    INT 21H \n\
		    LOOP PRINT_LOOP \n\
		    \n\
		    MOV AH,2\n\
		    MOV DL,10\n\
		    INT 21H\n\
		    \n\
		    MOV DL,13\n\
		    INT 21H\n\
			\n\
		    POP DX \n\
		    POP CX \n\
		    POP BX \n\
		    POP AX \n\
		    ret \n\
		OUTDEC ENDP \n\
		END MAIN\n";

			$$->code = $1->code;
			//$$->code = codes;

			FILE * asmcode = fopen("code.asm","w");

			fprintf(asmcode, $1->code.c_str());

			fclose(asmcode);

			asmcode = fopen("code.asm", "r");

			optimization(asmcode);
		}
		//write your code in this block in all the similar blocks below

		$$ = new SymbolInfo();

		$$->name = $1->name;

		fprintf(parserLog, "At line no  %d : start : program\n\n%s\n\n",line_count, $$->name.c_str());
	}
	;

program : program unit{
	$$ = new SymbolInfo();

	$$->name = $1->name + "\n" + $2->name;

	fprintf(parserLog,"At line no : %d program : program unit\n\n%s\n\n",line_count, $$->name.c_str());

	$$->code = $1->code + $2->code;
}
	| unit {
		$$ = new SymbolInfo();

		$$->name = $1->name ;

		fprintf(parserLog,"At line no : %d program : unit\n\n%s\n\n",line_count, $$->name.c_str());

		$$->code = $1->code;
	}
	;

unit : var_declaration	{

	$$ = new SymbolInfo();

	$$->name = $1->name ;

	fprintf(parserLog,"At line no : %d unit : var_declaration\n\n%s\n\n",line_count, $$->name.c_str());

	$$->code = $1->code;
}
     | func_declaration	{

			 $$ = new SymbolInfo();

			 $$->name = $1->name ;

		 	fprintf(parserLog,"At line no : %d unit : func_declaration\n\n%s\n\n",line_count, $$->name.c_str());

			$$->code = $1->code;

		 }
     | func_definition	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name ;

			 $$->code = $1->code;

		 	fprintf(parserLog,"At line no : %d unit : func_definition\n\n%s\n\n",line_count, $$->name.c_str());
		 }
     ;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON{

	$$ = new SymbolInfo();


	$$->name = $1->name + $2->name + "(" + $4->name + ");\n" ;
	fprintf(parserLog,"At line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n%s\n\n",line_count, $$->name.c_str());

	SymbolInfo * s = table->lookup($2->name);

	if(s == NULL)
	{
		table->insert($2->name, "ID", "Function");

		s = table->lookup($2->name);

		s->function = new Function();

		for(int i=0;i<paramList.size();i++)
		{
			s->function->param_list.push_back(paramList[i]->name);
			s->function->param_type.push_back(paramList[i]->dectype);
			s->function->setParamCount();
			//s->function->setParamCount(paramList[i]->name, paramList[i]->dectype);
		}

		paramList.clear();

		s->function->retType = $1->name;


	}

	else
	{

		int num = s->function->param_count;

		if(num != paramList.size())
		{
			errors++;

			fprintf(parserError,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);
		}

		else
			{
				vector<string> types = s->function->param_type;

				for(int i=0;i<num;i++)
				{
					if(paramList[i]->dectype != types[i])
					{
						errors++;

						fprintf(parserError, "Error at line no : %d :Type Mismatch \n\n", line_count);

						break;
					}

				}

				if(s->function->retType != $1->name)
				{
					errors++;

					fprintf(parserError, "Error at line no : %d : Return Type Mismatch \n\n", line_count);


				}

				paramList.clear();

			}
	}


}
		| type_specifier ID LPAREN RPAREN SEMICOLON	{

			$$ = new SymbolInfo();


			$$->name = $1->name + " " + $2->name + "();\n" ;

			fprintf(parserLog,"At line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n%s\n\n",line_count, $$->name.c_str());

			SymbolInfo * s = table->lookup($2->name);

			if(s == NULL)
			{
				table->insert($2->name, "ID", "Function");

				s = table->lookup($2->name);



				s->function = new Function();

				s->function->retType = $1->name;

			}

			{
				if(s->function->param_count != 0)
				{
					errors++;

					fprintf(parserError, "Error at line no  %d : Invalid number of parameters\n\n", line_count);
				}

				if(s->function->retType != $1->name)
				{
					errors++;

					fprintf(parserError, "Error at line no. %d : Return Type Mismatch\n\n", line_count);
				}
			}

		}
		;

func_definition : type_specifier ID LPAREN parameter_list RPAREN 	{

	$$ = new SymbolInfo();




	SymbolInfo * s = table->lookup($2->name);

	if(s != NULL)
	{
		if(s->function->defined == false)
		{
			int num = s->function->param_count;

			if(num != paramList.size())
			{
				errors++;

				fprintf(parserError, "Error at line No. %d : Invalid number of parameters\n\n", line_count);
			}

			else
			{
				vector<string> types = s->function->param_type;

				for(int i=0;i<num;i++)
				{
					if(paramList[i]->dectype != types[i])
					{
						errors++;

						fprintf(parserError, "Error at line no %d Type Mismatch\n\n", line_count);

						break;
					}
				}

				if(s->function->retType != $1->name)
				{
					errors++;

					fprintf(parserError,"Error at Line No.%d: Return Type Mismatch1 \n\n",line_count);
				}
			}

			s->function->getclear();

			for(int i=0;i<paramList.size();i++)
			{
				s->function->add_number_of_parameter(paramList[i]->name + IntToString(table->current->id+1), paramList[i]->dectype);
			}


			s->function->defined = true;
		}



		else
		{
						errors++;
						fprintf(parserError,"Error at Line No.%d:  Multiple defination of function %s\n\n",line_count,$2->name.c_str());
		}
	}

	else
	{
		table->insert($2->name, "ID", "Function");

		s = table->lookup($2->name);

		s->function = new Function();

		for(int i=0;i<paramList.size();i++)
		{
			s->function->add_number_of_parameter(paramList[i]->name + IntToString(table->current->id+1), paramList[i]->dectype);
			//s->function->setParamCount(paramList[i]->name, paramList[i]->dectype);
		}

		s->function->retType = $1->name;
	}

}	compound_statement	{

	$$->name = $1->name +" " + $2->name + "(" + $4->name + ")"   + $7->name ;

	fprintf(parserLog,"At line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n%s\n\n",line_count, $$->name.c_str());

	$$->code = $2->name + "proc\n";

	if($2->name == "main")
	{
		$$->code = $$->code + " mov ax, @data\n\tmov ds, ax\n" + $7->code + "LReturn" + curfunction + ":\n\tmov ah, 4ch\n\tint 21h\n";
	}

	else
	{
		SymbolInfo * s = table->lookup($2->name);

		for(int i=0;i<functionVariables.size();i++)
		{
			s->function->var_list.push_back(functionVariables[i]);
		}

		functionVariables.clear();

		string codes = "";
	 	//codes += $$->code + "\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";

		for(int i=0;i<4;i++)
		{
			char ch = 'a' + i;
			string st;
			st.push_back(ch);
			codes += "\tpush " + st + "x\n";
		}

		vector<string> para_list = s->function->param_list;
		vector<string> var_list = s->function->var_list;

		for(int i=0;i<para_list.size();i++)
		{
			codes += "\tpush " + para_list[i] + "\n";
		}

		for(int i=0;i<var_list.size();i++)
		{
			codes += "\tpush " + var_list[i] + "\n";
		}

		codes += $7->code + "LReturn" + curfunction + ":\n";


		for(int i=var_list.size()-1;i>=0;i--)
		{
			codes += "\tpop " + var_list[i] + "\n";
		}

		for(int i=para_list.size()-1;i>=0;i--)
		{
			codes += "\tpop " + para_list[i] + "\n";
		}

		//codes += "\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax";

		for(int i=3;i>=0;i--)
		{
			char ch = 'a' + i;
			string st;
			st.push_back(ch);
			codes += "\tpop " + st + "x\n";
		}

		codes += "\tret\n";

		$$->code = codes + $2->name + " endp\n";
	}

}

		| type_specifier ID LPAREN RPAREN {

			$$ = new SymbolInfo();

			SymbolInfo * s = table->lookup($2->name);

			if(s == NULL)
			{
				table->insert($2->name, "ID", "Function");

				s = table->lookup($2->name);

				s->function = new Function();

				s->function->defined = true;

				s->function->retType = $1->name;
			}

			else if(s->function->defined == false)
			{
				if(s->function->param_count != 0)
				{
					errors++;
					fprintf(parserError,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);
				}

				if(s->function->retType != $1->name)
				{
					errors++;

					fprintf(parserError,"Error at Line No.%d: Return Type Mismatch \n\n",line_count);
				}

				s->function->defined = true;

			}

			else
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d:  Multiple definition of function %s\n\n",line_count,$2->name.c_str());
			}

			curfunction = $2->name;
			variables.push_back(curfunction + "_return");

			$1->name = $1->name + " " + $2->name + "()";




			}compound_statement{


			$$->name = $1->name + " " + $2->name + "()" + "\n" + $6->name  ;
			fprintf(parserLog,"At line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n%s\n\n",line_count, $$->name.c_str());

			$$->code = $2->name + " proc\n";
			//here
			if($2->name == "main")
			{
				$$->code = $$->code + " mov ax, @data\n\tmov ds, ax\n" + $6->code + " LReturn" + curfunction + ":\n\tmov ah, 4ch\n\tint 21h\n";
			}

			else
			{
				SymbolInfo * s = table->lookup($2->name);

				for(int i=0;i<functionVariables.size();i++)
				{
					s->function->var_list.push_back(functionVariables[i]);
				}

				functionVariables.clear();

				string codes = "";
			 	//codes += $$->code + "\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";

				for(int i=0;i<4;i++)
				{
					char ch = 'a' + i;
					string st;
					st.push_back(ch);
					codes += "\tpush " + st + "x\n";
				}

				vector<string> para_list = s->function->param_list;
				vector<string> var_list = s->function->var_list;

				for(int i=0;i<para_list.size();i++)
				{
					codes += "\tpush " + para_list[i] + "\n";
				}

				for(int i=0;i<var_list.size();i++)
				{
					codes += "\tpush " + var_list[i] + "\n";
				}

				codes += $6->code + "LReturn" + curfunction + ":\n";



				for(int i=var_list.size()-1;i>=0;i--)
				{
					codes += "\tpop " + var_list[i] + "\n";
				}

				for(int i=para_list.size()-1;i>=0;i--)
				{
					codes += "\tpop " + para_list[i] + "\n";
				}

				//codes += "\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax";

				for(int i=3;i>=0;i--)
				{
					char ch = 'a' + i;
					string st;
					st.push_back(ch);
					codes += "\tpop " + st + "x\n";
				}

				codes += "\tret";

				$$->code = codes + $2->name + " endp\n";

			}

			//$$->name = $1->name + $6->name;


		}
 		;


parameter_list  : parameter_list COMMA type_specifier ID	{
	$$ = new SymbolInfo();

	$$->name = $1->name + ","  + $3->name + $4->name;
	fprintf(parserLog,"At line no : %d parameter_list  : parameter_list COMMA type_specifier ID\n\n%s\n\n",line_count, $$->name.c_str());

	//here

	paramList.push_back(new SymbolInfo($4->name, "ID", $3->name));

}
		| parameter_list COMMA type_specifier{

			$$ = new SymbolInfo();


			$$->name = $1->name + "," + $3->name ;

			paramList.push_back(new SymbolInfo("","ID",$3->name));

			fprintf(parserLog,"At line no : %d parameter_list  : parameter_list COMMA type_specifier\n\n%s\n\n",line_count, $$->name.c_str());

		}
 		| type_specifier ID {

			$$ = new SymbolInfo();


			$$->name = $1->name + $2->name ;

			paramList.push_back(new SymbolInfo($2->name, "ID", $1->name));

			fprintf(parserLog,"At line no : %d parameter_list  : type_specifier ID\n\n%s\n\n",line_count, $$->name.c_str());
		}
		| type_specifier{

			$$ = new SymbolInfo();


			$$->name = $1->name ;

			paramList.push_back(new SymbolInfo("", "ID", $1->name));

			fprintf(parserLog,"At line no : %d parameter_list  : type_specifier\n\n%s\n\n",line_count, $$->name.c_str());
		}
 		;


compound_statement : LCURL
 										{
											$$ = new SymbolInfo();

											table->EnterScope(parserLog, 10);

											//table->printAll(parserLog);

											//here

											for(int i=0;i<paramList.size();i++)
											{
												table->insert(paramList[i]->name, "ID", paramList[i]->dectype);

												variables.push_back(paramList[i]->name + IntToString(table->current->id));
											}
											paramList.clear();
											}
											statements RCURL{




					$$->name = "{\n" + $3->name + "\n}" ;

					fprintf(parserLog, "At line no : %d compound_statement : LCURL statements RCURL\n\n%s\n\n", line_count, $$->name.c_str());

					$$->code = $3->code;

					table->printAll(parserLog);

					table->ExitScope(parserLog);

}
 		    | LCURL RCURL	{

					table->EnterScope(parserLog, 10);

					for(int i=0;i<paramList.size();i++)
					{
						table->insert(paramList[i]->name, "ID", paramList[i]->dectype);

						variables.push_back(paramList[i]->name + IntToString(table->current->id));

					}
					paramList.clear();

					$$ = new SymbolInfo();


					$$->name = "{}";

					fprintf(parserLog, "At line no : %d compound_statement : LCURL RCURL\n\n{}\n\n", line_count);

					table->printAll(parserLog);
						table->ExitScope(parserLog);
				}
 		    ;

var_declaration : type_specifier declaration_list SEMICOLON{

	$$ = new SymbolInfo();


	$$->name = $1->name +" " + $2->name + ";\n"  ;

	fprintf(parserLog, "At line no: %d var_declaration : type_specifier declaration_list SEMICOLON\n\n%s\n\n",line_count, $$->name.c_str());

	if($$->name == "void ")
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Type specifier cannot be void\n\n", line_count);
	}

	else
	{
		for(int i=0;i<decList.size();i++)
		{
			SymbolInfo * si = table->lookupcurrent(decList[i]->name);

			if(si != NULL)
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Multiple declaration of %s\n\n", line_count, decList[i]->name.c_str());

				continue;

			}

			if(decList[i]->type.size() == 3)
			{
				arrayDec.push_back(make_pair(decList[i]->name + IntToString(table->current->id), decList[i]->type.substr(2, decList[i]->type.size()-1)));

				decList[i]->type = decList[i]->type.substr(0,decList[i]->type.size()-1);

				table->insert(decList[i]->name, decList[i]->type, $1->name + "array");
			}

			else
			{
				functionVariables.push_back(decList[i]->name + IntToString(table->current->id));

				table->insert(decList[i]->name, decList[i]->type, $1->name );

				variables.push_back(decList[i]->name + IntToString(table->current->id));
			}
		}
	}

	decList.clear();
}
 		 ;

type_specifier	: INT	{

	$$ = new SymbolInfo();


		fprintf(parserLog, "At line no: %d type_specifier : INT\n\n%s\n\n", line_count, $1->getName().c_str());

		$$->name = "int ";

		//$$->setName($1->getName() + " ");

}
 		| FLOAT	{
			$$ = new SymbolInfo();

			fprintf(parserLog, "At line no: %d type_specifier : FLOAT\n\n%s\n\n", line_count, $1->getName().c_str());

			$$->name = "float ";
			//$$->setName($1->getName() + " ");
		}
 		| VOID	{

			$$ = new SymbolInfo();


			fprintf(parserLog, "At line no: %d type_specifier : VOID\n\n%s\n\n", line_count, $1->getName().c_str());

			$$->name = "void ";
			//$$->setName($1->getName() + " ");
		}
 		;

declaration_list : declaration_list COMMA ID	{

	$$ = new SymbolInfo();


				$$->setName($1->getName() + "," + $3->getName());

				fprintf(parserLog, "At line no: %d declaration_list : declaration_list COMMA ID\n\n%s\n\n", line_count, $$->name.c_str());

				decList.push_back(new SymbolInfo($3->name, "ID"));


}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
				$$ = new SymbolInfo();


				fprintf(parserLog, "At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n%s %s %s %s %s %s\n\n", line_count, $1->getName().c_str(), ",",  $3->getName().c_str(), "[", $5->getName().c_str(), "]");

				decList.push_back(new SymbolInfo($3->name, "IDa"));



				$$->setName($1->getName() + "," + $3->getName() + "[" + $5->getName() + "]");
			}
 		  | ID	{

				$$ = new SymbolInfo();


				fprintf(parserLog, "At line no: %d declaration_list : ID\n\n%s\n\n", line_count, $1->getName().c_str());

				decList.push_back(new SymbolInfo($1->name, "ID"));

				$$->setName($1->getName());
			}
 		  | ID LTHIRD CONST_INT RTHIRD	{

				$$ = new SymbolInfo();


				fprintf(parserLog, "At line no: %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n%s %s %s %s\n\n", line_count, $1->getName().c_str(), $2->getName().c_str(), $3->getName().c_str(), $4->getName().c_str());

				decList.push_back(new SymbolInfo($1->name, "IDa"));

				$$->setName($1->getName() + $2->getName() + $3->getName() + $4->getName());
			}
 		  ;

statements : statement {

	$$ = new SymbolInfo();


		$$->name = $1->name ;

		fprintf(parserLog, "At line no: %d statements : statement\n\n%s\n\n",line_count, $$->name.c_str());

		$$->code = $1->code;

}
	   | statements statement	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name + $2->name ;

	 		fprintf(parserLog, "At line no: %d statements : statements statement\n\n%s\n\n",line_count, $$->name.c_str());

			$$->code = $1->code + $2->code;

		 }
	   ;

statement : var_declaration	{

	$$ = new SymbolInfo();


	$$->name = $1->name;

	fprintf(parserLog, "At line no: %d statement : var_declaration\n\n%s\n\n",line_count, $$->name.c_str());
}
	  | expression_statement	{

			$$ = new SymbolInfo();


			$$->name = $1->name;

			fprintf(parserLog, "At line no: %d statement : expression_statement\n\n%s\n\n",line_count, $$->name.c_str());

			$$->code = $1->code;
		}
	  | compound_statement	{

			$$ = new SymbolInfo();


			$$->name = $1->name;

			fprintf(parserLog, "At line no: %d statement : compound_statement\n\n%s\n\n",line_count, $$->name.c_str());

			$$->code = $1->code;
		}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement{
			$$ = new SymbolInfo();


			$$->name = "for(" + $3->name + $4->name + $5->name + ")" + $7->name ;

			fprintf(parserLog, "At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n%s\n\n",line_count, $$->name.c_str());

			if($3->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
					//here
					string codes = $3->code;
					char * label1 = newLabel();
					char * label2 = newLabel();
					codes += string(label1) + ":\n";
					codes += "\tmov ax, " + $4->idval + "\n";
					codes += "\tcmp ax, 0";
					codes += "\tje " + string(label2) + "\n";
					codes += $7->code;
					codes += "\tjmp " + string(label1) + "\n";
					codes += string(label2) + ":\n";
					$$->code = codes;
			}


		}
	  | IF LPAREN expression RPAREN statement	%prec LOWER_THAN_ELSE{
			$$ = new SymbolInfo();


			$$->name = "if(" + $3->name + ")\n" + $5->name ;

			fprintf(parserLog, "At line no: %d statement : IF LPAREN expression RPAREN statement\n\n%s\n\n",line_count, $$->name.c_str());

			if($3->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				//here
				string codes = $3->code;
				char * label1 = newLabel();
				codes += "\tmov ax, " + $3->idval + "\n";
				codes += "\tcmp ax, 0\n";
				codes += "\tje " + string(label1) + "\n";
				codes += $5->code;
				codes += string(label1) + ":\n";
				$$->code = codes;
			}


		}
	  | IF LPAREN expression RPAREN statement ELSE statement	{

			$$ = new SymbolInfo();


			$$->name = "if(" + $3->name + ")\n" + $5->name + " else " +$7->name ;

			fprintf(parserLog, "At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n%s\n\n",line_count, $$->name.c_str());

			if($3->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				string codes = $3->code;
				char * label1 = newLabel();
				char * label2 = newLabel();

				codes += "\tmov ax, " + $3->idval + "\n";
				codes += "\tcmp ax, 0\n";
				codes+="\tje "+string(label1)+"\n";
				codes += $5->code;

				codes += "\tjmp " + string(label2) + "\n";
				codes += string(label1) + "\n";

				$$->code = codes;
			}
		}
	  | WHILE LPAREN expression RPAREN statement	{

			$$ = new SymbolInfo();


			$$->name = "while(" + $3->name + ") \n" + $5->name ;

			fprintf(parserLog, "At line no : %d statement : WHILE LPAREN expression RPAREN statement\n\n%s\n\n", line_count, $$->name.c_str());

			if($3->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				string codes = "";
				char * label1 = newLabel();
				char * label2 = newLabel();

				codes += string(label1) + "\n";
				codes += $3->code;

				codes += "\tmov ax, " + $3->idval + "\n";
				codes += "\tcmp ax, 0\n";
				codes += "\tje "+string(label2)+"\n";
				codes += $5->code;

				codes += "\tjmp " + string(label1) + "\n";
				codes += string(label1) + "\n";

				$$->code = codes;
			}
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON	{

			$$ = new SymbolInfo();


			$$->name = "println(" + $3->name + ");\n" ;

			fprintf(parserLog, "At line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n%s\n\n", line_count, $$->name.c_str());

			string codes = "";

			if(table->lookUpScopeID($3->name) == -1)
			{
				errors++;

				fprintf(parserError, "Error at Line No.%d:  Undeclared Variable: %s \n\n",line_count,$3->name.c_str());
			}

			else
			{
				codes += "\tmov ax, " + $3->name + IntToString(table->lookUpScopeID($3->name));

				codes += "\n\tcall outdec\n";
			}

			$$->code = codes;

		}
	  | RETURN expression SEMICOLON	{

			$$ = new SymbolInfo();


			$$->name = "return " + $2->name + ";\n " ;

			fprintf(parserLog, "At line no : %d statement : RETURN expression SEMICOLON\n\n%s\n\n", line_count, $$->name.c_str());

			if($2->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				string codes = $2->code;

				codes += "\tmov ax, " + $2->idval + "\n";

				codes += "\tmov " + curfunction + "_return, ax\n";

				codes += "\tjmp LReturn" + curfunction + "\n";

				$$->code = codes;
			}



		}
	  ;




expression_statement 	: SEMICOLON	{

	$$ = new SymbolInfo();


	$$->name = ";" ;

	fprintf(parserLog, "At line no : %d expression_statement : SEMICOLON\n\n%s\n\n", line_count, $$->name.c_str());
}
			| expression SEMICOLON	{

				$$ = new SymbolInfo();


				$$->name = $1->name + ";\n" ;

				fprintf(parserLog, "At line no : %d expression_statement : expression SEMICOLON\n\n%s\n\n", line_count, $$->name.c_str());

				$$->code = $1->code;
				$$->idval = $1->idval;
			}
			;

variable : ID	{

	$$ = new SymbolInfo();




	SymbolInfo * s = table->lookup($1->name);

	if(s == NULL)
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Undeclared variable %s\n\n", line_count, $1->name.c_str());
	}

	else if(table->lookup($1->name)->dectype == "int array" || table->lookup($1->name)->dectype == "float array")
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Type Mismatch: \n\n", line_count);
	}

	if(s != NULL)
	{
		$$->dectype = s->dectype;

		$$->idval = $1->name + IntToString(table->lookUpScopeID($1->name));
	}

	$$->name = $1->name;
	$$->type = "notarray";

	fprintf(parserLog, "At line no : %d variable : ID\n\n%s\n\n", line_count, $$->name.c_str());



}
	 | ID LTHIRD expression RTHIRD	{

		 $$ = new SymbolInfo();


		 $$->name = $1->name +"[" + $3->name + "]";

	 	fprintf(parserLog, "At line no : %d variable : ID LTHIRD expression RTHIRD\n\n%s\n\n", line_count, $$->name.c_str());

		SymbolInfo * s = table->lookup($1->name);

		if(s == NULL)
		{
			errors++;

			fprintf(parserError, "Error at line no %d : Undeclared variable %s\n\n", line_count,$1->name.c_str());
		}

		//cout<<"value of $3 : "<<$3->dectype<<endl;

		else if($3->dectype == "float " || $3->dectype == "void ")
		{
			errors++;

			fprintf(parserError, "Error at line no %d : Non integer array index\n\n", line_count);
		}

		else if(s != NULL)
		{
			if(s->dectype != "int array" && s->dectype != "float array")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				if(s->dectype == "int array")
				{
					$1->dectype = "int ";
				}

				if(s->dectype == "float array")
				{
					$1->dectype = "float ";
				}
			}

			$$->dectype = $1->dectype;

			string codes = "";

			codes += $3->code + "\n";

			codes += "\tmov bx, " + $3->idval + "\n";

			codes += "\tadd bx, bx\n";

			$$->idval = $1->name + IntToString(table->lookUpScopeID($1->name));

			$$->code = codes;

		}

		$$->type = "array";

	 }
	 ;

 expression : logic_expression	{

	 $$ = new SymbolInfo();


	 $$->name = $1->name;

	 $$->dectype = $1->dectype;

	 fprintf(parserLog, "At line no : %d expression : logic_expression\n\n%s\n\n", line_count, $$->name.c_str());

	 $$->code = $1->code;
	 $$->idval = $1->idval;

 }
	   | variable ASSIGNOP logic_expression	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name + " = " + $3->name ;

			 fprintf(parserLog, "At line no : %d expression : variable ASSIGNOP logic_expression\n\n%s\n\n", line_count, $$->name.c_str());

			 if($3->dectype == "void ")
			 {
				 errors++;

				 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

				 $$->dectype = "int ";
			 }

			 else
			 {
				 if($1->dectype != $3->dectype)
				 {
					 errors++;

					 fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);
				 }

				 else
				 {
					 //here
					 string codes = $1->code;

					 codes += $3->code;
					 codes += "\tmov ax, " + $3->idval + "\n";

					 if($1->type == "notarray")
					 {
						 codes += "\tmov " + $1->idval + ", ax\n";
					 }

					 else
					 {
						 codes += "\tmov " + $1->idval + "[bx], ax\n";
					 }

					 $$->code = codes;

					 $$->idval = $1->idval;
				 }
			 }

			 $$->dectype = $1->dectype;
		 }
	   ;

logic_expression : rel_expression	{

	$$ = new SymbolInfo();


		$$->name = $1->name ;

		$$->dectype = $1->dectype;

		fprintf(parserLog, "At line no : %d logic_expression : rel_expression\n\n%s\n\n", line_count, $$->name.c_str());

		//here now
		$$->code = $1->code;
		$$->idval = $1->idval;
}
		 | rel_expression LOGICOP rel_expression	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name + " " + $2->name + " " + $3->name + " " ;

	 		fprintf(parserLog, "At line no : %d logic_expression : rel_expression\n\n%s\n\n", line_count, $$->name.c_str());

			if($1->dectype == "void " || $3->dectype == "void ")
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);
			}

			else
			{
				string codes = $1->code;

				codes += $3->code;

				char *label1=newLabel();
				char *label2=newLabel();
				char *label3=newLabel();
				char *temp=newTemp();

				if($2->name == "||")
				{
					codes += "\tmov ax, " + $1->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tjne " + string(label2) +  "\n";
					codes += "\tmov ax, " + $3->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tjne " + string(label2) +  "\n";

					codes+=string(label1)+":\n";

					codes += "\tmov " + string(temp) + ", 0\n";
					codes += "\tjmp " + string(label3) + "\n";

					codes+=string(label2)+":\n";

					codes += "\tmov " + string(temp) + ", 1\n";
					codes+=string(label3)+":\n";
				}

				else
				{
					codes += "\tmov ax, " + $1->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tje " + string(label2) +  "\n";
					codes += "\tmov ax, " + $3->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tje " + string(label2) +  "\n";

					codes+=string(label1)+":\n";

					codes += "\tmov " + string(temp) + ", 1\n";
					codes += "\tjmp " + string(label3) + "\n";

					codes+=string(label2)+":\n";

					codes += "\tmov " + string(temp) + ", 0\n";
					codes+=string(label3)+":\n";
				}

				$$->code = codes;
				$$->idval = temp;
				variables.push_back(temp);
			}

			$$->dectype = "int ";
		 }
		 ;

rel_expression	: simple_expression	{
	$$ = new SymbolInfo();


	$$->name = $1->name;

	fprintf(parserLog, "At line no : %d rel_expression : simple_expression\n\n%s\n\n", line_count, $$->name.c_str());

	$$->code = $1->code;
	$$->idval = $1->idval;

	$$->dectype = $1->dectype;
}
		| simple_expression RELOP simple_expression	{

			$$ = new SymbolInfo();


			$$->name = $1->name + $2->name + $3->name;

			fprintf(parserLog, "At line no : %d rel_expression : simple_expression RELOP simple_expression\n\n%s\n\n", line_count, $$->name.c_str());

			if($1->dectype == "void " || $3->dectype == "void ")
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);

				$$->dectype = "int ";
			}

			else
			{
				string codes = $1->code;
				codes += $3->code;

				char *temp=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();

				codes += "\tmov ax, " + $1->idval + "\n";
				codes += "\tcmp ax, " + $3->idval + "\n";

				string op = "";

				if($2->name == "<")
					op = "jl";

				else if($2->name == "<=")
					op = "jle";

				else if($2->name == ">")
						op = "jg";

				else if($2->name == ">=")
							op = "jge";


				else if($2->name == "==")
					op = "je";

					else if($2->name == "!=")
						op = "jne";



				codes += "\t" + op + " " + string(label1) + "\n";

				codes += "\tmov " + string(temp) + ", 0\n";
				codes += "\tjmp " + string(label2) + "\n";
				codes+=string(label1)+":\n";
				codes += "\tmov " + string(temp) + ", 1\n";
				codes+=string(label2)+":\n";

				variables.push_back(temp);
				$$->code = codes;
				$$->idval = temp;

			}

			$$->dectype = "int ";
		}
		;

simple_expression : term	{

	$$ = new SymbolInfo();


	$$->name = $1->name;

	fprintf(parserLog, "At line no: %d simple_expression : term\n\n%s\n\n", line_count, $$->name.c_str());

	//here
	$$->code = $1->code;
	$$->idval = $1->idval;

	$$->dectype = $1->dectype;
}
		  | simple_expression ADDOP term	{

				$$->name = $1->name + $2->name + $3->name ;

				fprintf(parserLog, "At line no: %d simple_expression : simple_expression ADDOP term\n\n%s\n\n", line_count, $$->name.c_str());

				if($1->dectype == "void " || $3->dectype == "void ")
				{
					errors++;

					fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
				}

				else
				{
					if($1->dectype == "float " || $3->dectype == "float ")
					{
						$$->dectype = "float ";
					}

					else
							$$->dectype = "int ";

					string codes = $1->code + $3->code;

					codes += "\tmov ax, " + $1->idval + "\n";
					char *temp=newTemp();

					if($2->name == "+")
					{
						codes += "\tadd ax, " + $3->idval + "\n";
					}
					else
					{
						codes += "\tsub ax, " + $3->idval + "\n";
					}

					codes += "\tmov " + string(temp) + ", ax\n";

					$$->code = codes;
					$$->idval = temp;
					variables.push_back(temp);
				}



			}
		  ;

term :	unary_expression	{

	$$ = new SymbolInfo();


				$$->name = $1->name ;

				fprintf(parserLog, "At line no : %d term : unary_expression\n\n%s\n\n", line_count, $$->name.c_str());

				$$->code = $1->code;
				$$->idval = $1->idval;

				$$->dectype = $1->dectype;

}
     |  term MULOP unary_expression	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name + $2->name + $3->name;

			 fprintf(parserLog, "At line no : %d term : term MULOP unary_expression\n\n%s\n\n", line_count, $$->name.c_str());

			 if($1->dectype == "void " || $3->dectype == "void ")
			 {
				 errors++;

				 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

				 $$->dectype = "int ";
			 }

			 else if($2->name == "%")
			 {
				 if($1->dectype != "int " || $3->dectype != "int ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Non Integer operand on modulus operator\n\n", line_count);
				 }
				 else
				 	$$->dectype = "int ";


				string codes = $1->code + $3->code;
				char *temp=newTemp();

				codes += "\tmov ax, " + $1->idval + "\n";
				codes += "\tmov bx, " + $3->idval + "\n";
				codes += "\tmov dx, 0\n";
				codes += "div bx\n";
				codes += "\tmov " + string(temp) + ", dx\n";
				$$->code = codes;
				$$->idval = temp;
				variables.push_back(temp);
			 }

			 else if($2->name == "/")
			 {
				 if($1->dectype == "void " || $3->dectype == "void ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

					 $$->dectype = "int ";
				 }

				 else
				 {
					 if($1->dectype == "int " && $3->dectype == "int ")
					 {
						 $$->dectype = "int ";
					 }

					 else
					 		{
								$$->dectype = "float ";
							}

							string codes = $1->code + $3->code;
							char *temp=newTemp();

							codes += "\tmov ax, " + $1->idval + "\n";
							codes += "\tmov bx, " + $3->idval + "\n";
							codes += "\tmov dx, 0\n";
							codes += "div bx\n";
							codes += "\tmov " + string(temp) + ", ax\n";
							$$->code = codes;
							$$->idval = temp;
							variables.push_back(temp);

				 }
			 }

			 else
			 {
				 if($1->dectype == "void " || $3->dectype == "void ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

					 $$->dectype = "int ";
				 }

				 else
				 {
					 if($1->dectype == "float " && $3->dectype == "float ")
					 {
						 $$->dectype = "float ";
					 }

					 else
					 		$$->dectype = "int ";

							string codes = $1->code + $3->code;
							char *temp=newTemp();

							codes += "\tmov ax, " + $1->idval + "\n";
							codes += "\tmov bx, " + $3->idval + "\n";
							codes += "\tmov dx, 0\n";
							codes += "mul bx\n";
							codes += "\tmov " + string(temp) + ", ax\n";
							$$->code = codes;
							$$->idval = temp;
							variables.push_back(temp);
				 }
			 }
		 }
     ;

unary_expression : ADDOP unary_expression	{

	$$ = new SymbolInfo();


	$$->name = $1->name + $2->name;

	fprintf(parserLog, "At line no : %d unary_expression : ADDOP unary_expression\n\n%s\n\n",line_count, $$->name.c_str());

	if($2->dectype == "void ")
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Type Mismatch\n\n");

		$$->dectype = "int ";
	}

	else
	{
		string codes = $2->code;
		if($1->name == "-")
		{
			codes += "\tmov ax, " + $2->idval + "\n";
			codes += "\tneg ax\n";
			codes += "\tmov " + $2->idval + ", ax\n";
		}

		$$->code = codes;
		$$->dectype = $2->dectype;
	}

}
		 | NOT unary_expression	{

			 $$ = new SymbolInfo();


			 $$->name = "!" + $2->name;

		 	fprintf(parserLog, "At line no : %d unary_expression : NOT unary_expression\n\n%s\n\n",line_count, $$->name.c_str());

			if($2->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n");

				$$->dectype = "int ";
			}

			else
			{
				string codes = $2->code;
				codes += "\tmov ax, " + $2->idval + "\n";
				codes += "\tneg ax\n";
				codes += "\tmov " + $2->idval + ", ax\n";
				$$->dectype = $2->dectype;

				$$->code = codes;
				$$->idval = $2->idval;
			}
		 }
		 | factor	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name;

			 fprintf(parserLog, "At line no : %d unary_expression : factor\n\n%s\n\n", line_count, $$->name.c_str());

			 $$->dectype = $1->dectype;

			 $$->code = $1->code;
			 $$->idval = $1->idval;
		 }
		 ;

factor	: variable	{

	$$ = new SymbolInfo();


	$$->name = $1->name;
	string codes = $1->code;

	if($1->type == "array")
	{
		char *temp=newTemp();

		codes += "\tmov ax, " + string(temp) + "[bx]\n";
		codes += "\tmov " + string(temp) + ", ax";

		variables.push_back(temp);
		$$->idval = temp;
	}

	else
	{
		$$->idval = $1->idval;
	}

	$$->code = codes;

	fprintf(parserLog, "At line no : %d factor : variable\n\n%s\n\n", line_count, $$->name.c_str());

	$$->dectype = $1->dectype;
}
	| ID LPAREN argument_list RPAREN	{

		$$ = new SymbolInfo();


		$$->name = $1->name + "(" + $3->name + ")";

		fprintf(parserLog, "At line no : %d factor : ID LPAREN argument_list RPAREN\n\n%s\n\n", line_count, $$->name.c_str());

		SymbolInfo * si = table->lookup($1->name);

		if(si == NULL)
		{
			errors++;

			fprintf(parserError, "Error at line %d : Undefined function\n\n",line_count);
			$$->dectype = "int ";
		}

		else if(si->function == NULL)
		{
			errors++;

			fprintf(parserError, "Error at line %d : Not A function\n\n",line_count);
			$$->dectype = "int ";
		}

		else
		{
			if(si->function->defined == false)
			{
				errors++;

				fprintf(parserError, "Error at line %d : Undeclared function\n\n",line_count);
				$$->dectype = "int ";
			}

			int num = si->function->param_count;

			$$->dectype = si->function->retType;

			if(argList.size() != num)
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d:  Invalid number of arguments \n\n",line_count);
			}

			else
			{
				string codes = $3->code;

				vector<string> names = si->function->param_list;
				vector<string> types = si->function->param_type;
				vector<string> var_list = si->function->var_list;

				for(int i=0;i<num;i++)
				{
					codes += "\tmov ax, " + argList[i]->idval + "\n";
					codes += "\tmov " + names[i] + ", ax\n";
					if(argList[i]->dectype != types[i])
					{
						errors++;

						fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

						break;
					}
				}

				codes += "\tcall " + $1->name + "\n";

				codes += "\tmov ax, " + $1->name + "_return\n";

				char *temp=newTemp();
				codes += string(temp) + ", ax\n";

				$$->code = codes;
				$$->idval = temp;

				variables.push_back(temp);
			}
		}
		argList.clear();
	}
	| LPAREN expression RPAREN	{

		$$ = new SymbolInfo();


		$$->name = "(" + $2->name + ")" ;

		fprintf(parserLog, "At line no : %d factor : LPAREN expression RPAREN\n\n%s\n\n", line_count, $$->name.c_str());

		//here

		$$->code = $2->code;
		$$->idval = $2->idval;

		$$->dectype = $2->dectype;
	}
	| CONST_INT	{

		$$ = new SymbolInfo();


		$$->name = $1->name;

		fprintf(parserLog, "At line no : %d factor : CONST_INT\n\n%s\n\n", line_count, $$->name.c_str());

		$$->dectype = "int ";

		char *temp=newTemp();

		string codes = "";

		codes += "\tmov " + string(temp) + ", " + $1->name + "\n";
		$$->code = codes;
		$$->idval = temp;

		variables.push_back(temp);

	}
	| CONST_FLOAT	{

		$$ = new SymbolInfo();


		$$->name = $1->name;

		fprintf(parserLog, "At line no : %d factor : CONST_FLOAT\n\n%s\n\n", line_count, $$->name.c_str());

		$$->dectype = "float ";

		char *temp=newTemp();

		string codes = "";

		codes += "\tmov " + string(temp) + ", " + $1->name + "\n";
		$$->code = codes;
		$$->idval = temp;

		variables.push_back(temp);

	}
	| variable INCOP	{

		$$ = new SymbolInfo();


		$$->name = $1->name + "++";

		$$->dectype = $1->dectype;

		fprintf(parserLog, "At line no : %d factor : variable INCOP\n\n%s\n\n", line_count, $$->name.c_str());

		string codes = "";

		char *temp=newTemp();

		if($1->type == "array")
		{
			codes += "\tmov ax, " + $1->idval + "[bx]\n";
		}
		else
		{
			codes += "\tmov ax, " + $1->idval + "\n";
		}

		codes += "\tmov " + string(temp) + ", ax\n";

		if($1->type == "array")
		{
			codes += "\tmov ax, " + $1->idval + "[bx]\n";
			codes += "\tinc ax\n";
			codes += "\tmov " + $1->idval + "[bx], ax";
		}

		else
		{
			codes += "\tinc " + $1->idval + "\n";
		}

		variables.push_back(temp);
		$$->code = codes;
		$$->idval = temp;

	}
	| variable DECOP	{

		$$ = new SymbolInfo();


		$$->name = $1->name + "--";

		$$->dectype = $1->dectype;

		fprintf(parserLog, "At line no : %d factor : variable DECOP\n\n%s\n\n", line_count, $$->name.c_str());

		string codes = "";

		char *temp=newTemp();

		if($1->type == "array")
		{
			codes += "\tmov ax, " + $1->idval + "[bx]\n";
		}
		else
		{
			codes += "\tmov ax, " + $1->idval + "\n";
		}

		codes += "\tmov " + string(temp) + ", ax\n";

		if($1->type == "array")
		{
			codes += "\tmov ax, " + $1->idval + "[bx]\n";
			codes += "\tdec ax\n";
			codes += "\tmov " + $1->idval + "[bx], ax";
		}

		else
		{
			codes += "\tdec " + $1->idval + "\n";
		}

		variables.push_back(temp);
		$$->code = codes;
		$$->idval = temp;
	}
	;

argument_list : arguments	{

	$$ = new SymbolInfo();


		$$->name = $1->name ;

		fprintf(parserLog, "At line no : %d argument_list : arguments\n\n%s\n\n", line_count, $$->name.c_str());

		$$->code = $1->code;
}
			  |	{

					$$->name = "" ;

					fprintf(parserLog, "At line no : %d argument_list : \n\n%s\n\n", line_count, $$->name.c_str());
				}
			  ;

arguments : arguments COMMA logic_expression	{
	$$ = new SymbolInfo();


	$$->name = $1->name + "," + $3->name;

	argList.push_back($3);

	fprintf(parserLog, "At line no : %d arguments : arguments COMMA logic_expression\n\n%s\n\n",line_count, $$->name.c_str());

	$$->code = $1->code + $3->code;
}
	      | logic_expression	{

					$$ = new SymbolInfo();


					$$->name = $1->name;

					$$->dectype = $1->dectype;

					argList.push_back($1);

					fprintf(parserLog, "At line no : %d arguments : logic_expression\n\n%s\n\n", line_count, $$->name.c_str());

					$$->code = $1->code;
				}
	      ;


%%

bool check(string s1, string s2)
{
	if(s1.size() != s2.size() || s1.size()<<11)
		return false;

	int j = 0;

	for(j = 0;j<s1.size();j++)
	{
		if(s1[j] == 'm')
			break;


	}

	if(j == s1.size())
		return false;

	if(s1[j] != 'm' || s1[j+1] != 'o' || s1[j+2] != 'v')
		return false;

	j = 0;

	for(j = 0;j<s2.size();j++)
	{
		if(s2[j] == 'm')
			break;


	}

	if(j == s2.size())
		return false;

	if(s2[j] != 'm' || s2[j+1] != 'o' || s2[j+2] != 'v')
		return false;

	string source1 = "";
	string source2 = "";

	string dist1 = "";
	string dist2 = "";

	int i;

	for(i = j+4; i<s1.size()-1;i++)
	{
		if(s1[i] == ' ' && source1.size() == 0)
			continue;
		if(s1[i] == ' ' || s1[i] == ',')
			break;

		source1.push_back(s1[i]);
	}

	for(;i<s1.size()-1;i++)
	{
		if((s1[i]==' '|| s1[i]==',') && dist1.size() == 0)
		 	continue;
		if(s1[i]==' ')
		 	break;

		dist1.push_back(s1[i]);
	}

	for(i=j+4;i<s2.size()-1;i++)
	{
		if(s2[i]==' ' && source2.size() == 0)
		 	continue;
		if(s2[i]==' ' || s2[i] == ',')
			break;
		source2.push_back(s2[i]);
	}

	if(dist1 == source2 && dist2 == source1)
	 	return true;

	return false;
}

void optimization(FILE * asmcode)
{
	FILE * optcode = fopen("optcode.asm", "w");

	char * line = NULL;

	size_t len = 0;
	ssize_t read = 0;

	vector<string> v;

	while((read = getline(&line, &len, asmcode)) != -1)
	{
		v.push_back(string(line));
	}

	int sz = v.size();
	int mark[sz];

	for(int i=0;i<sz;i++)
	{
		mark[i] = 1;
	}

	for(int i=0;i<sz;i++)
	{
		if(check(v[i], v[i+1]))
			mark[i+1] = 0;
	}

	for(int i=0;i<sz;i++)
	{
		if(mark[i])
			fprintf(optcode, "%s", v[i].c_str());
	}

	fclose(asmcode);
	fclose(optcode);

	if(line)
		delete line;

}


int  main(int  argc,char *argv[])
{
	table = new SymbolTable(10);



	logout= fopen("1605020_logScanner.txt","w");
	tokenout= fopen("1605020_tokenScanner.txt","w");

	FILE * fp = yyin;

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	parserLog = fopen(argv[2],"w");
	fclose(parserLog);

	parserError= fopen(argv[3],"w");
	fclose(parserError);

	parserLog = fopen(argv[2],"a");

	parserError = fopen(argv[3],"a");


	yyin=fp;

	table->EnterScope(parserLog, 10);
	yyparse();

	fprintf(parserLog,"Symbol Table : \n\n");
	table->printAll(parserLog);
	fprintf(parserLog,"Total Lines : %d \n\n",line_count);
	fprintf(parserLog,"Total Errors : %d \n\n",errors);
	fprintf(parserError,"Total Errors : %d \n\n",errors);

	fclose(fp);
	fclose(parserLog);

	fclose(parserError);

	return 0;
}
