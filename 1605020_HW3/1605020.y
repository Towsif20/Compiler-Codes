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



void yyerror(char *s)
{
	errors++;

	//return;
}


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
}
	| unit {
		$$ = new SymbolInfo();

		$$->name = $1->name ;

		fprintf(parserLog,"At line no : %d program : unit\n\n%s\n\n",line_count, $$->name.c_str());
	}
	;

unit : var_declaration	{

	$$ = new SymbolInfo();

	$$->name = $1->name ;

	fprintf(parserLog,"At line no : %d unit : var_declaration\n\n%s\n\n",line_count, $$->name.c_str());
}
     | func_declaration	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name ;

		 	fprintf(parserLog,"At line no : %d unit : func_declaration\n\n%s\n\n",line_count, $$->name.c_str());
		 }
     | func_definition	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name ;

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
			s->function->setParamCount(paramList[i]->name, paramList[i]->dectype);
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
			s->function->setParamCount(paramList[i]->name, paramList[i]->dectype);
		}

		s->function->retType = $1->name;
	}

}	compound_statement	{

	$$->name = $1->name +" " + $2->name + "(" + $4->name + ")"   + $7->name ;

	fprintf(parserLog,"At line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n%s\n\n",line_count, $$->name.c_str());
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

				fprintf(parserError,"Error at Line No.%d:  Multiple defination of function %s\n\n",line_count,$2->name.c_str());
			}




			}compound_statement{


			$$->name = $1->name + " " + $2->name + "()" + "\n" + $6->name  ;
			fprintf(parserLog,"At line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n%s\n\n",line_count, $$->name.c_str());
		}
 		;


parameter_list  : parameter_list COMMA type_specifier ID	{
	$$ = new SymbolInfo();

	$$->name = $1->name + ","  + $3->name + $4->name;
	fprintf(parserLog,"At line no : %d parameter_list  : parameter_list COMMA type_specifier ID\n\n%s\n\n",line_count, $$->name.c_str());

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

											for(int i=0;i<paramList.size();i++)
											{
												table->insert(paramList[i]->name, "ID", paramList[i]->dectype);
											}
											paramList.clear();
											}
											statements RCURL{




					$$->name = "{\n" + $3->name + "\n}" ;

					fprintf(parserLog, "At line no : %d compound_statement : LCURL statements RCURL\n\n%s\n\n", line_count, $$->name.c_str());

					table->printAll(parserLog);

					table->ExitScope(parserLog);

}
 		    | LCURL RCURL	{

					table->EnterScope(parserLog, 10);

					for(int i=0;i<paramList.size();i++)
					{
						table->insert(paramList[i]->name, "ID", paramList[i]->dectype);
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
				decList[i]->type = decList[i]->type.substr(0,decList[i]->type.size()-1);

				table->insert(decList[i]->name, decList[i]->type, $1->name + "array");
			}

			else
			{
				table->insert(decList[i]->name, decList[i]->type, $1->name );
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
}
	   | statements statement	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name + $2->name ;

	 		fprintf(parserLog, "At line no: %d statements : statements statement\n\n%s\n\n",line_count, $$->name.c_str());
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
		}
	  | compound_statement	{

			$$ = new SymbolInfo();


			$$->name = $1->name;

			fprintf(parserLog, "At line no: %d statement : compound_statement\n\n%s\n\n",line_count, $$->name.c_str());
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
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON	{

			$$ = new SymbolInfo();


			$$->name = "println(" + $3->name + ");\n" ;

			fprintf(parserLog, "At line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n%s\n\n", line_count, $$->name.c_str());
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
	}

	$$->name = $1->name;

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

		cout<<"value of $3 : "<<$3->dectype<<endl;

		if($3->dectype == "float " || $3->dectype == "void ")
		{
			errors++;

			fprintf(parserError, "Error at line no %d : Non integer array index\n\n", line_count);
		}

		if(s != NULL)
		{
			if(s->dectype != "int array" && s->dectype != "float array")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			if(s->dectype == "int array")
			{
				$1->dectype = "int ";
			}

			if(s->dectype == "float array")
			{
				$1->dectype = "float ";
			}

			$$->dectype = $1->dectype;

		}


	 }
	 ;

 expression : logic_expression	{

	 $$ = new SymbolInfo();


	 $$->name = $1->name;

	 $$->dectype = $1->dectype;

	 fprintf(parserLog, "At line no : %d expression : logic_expression\n\n%s\n\n", line_count, $$->name.c_str());
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
			 else if(table->lookup($1->name) != NULL)
			 {
				 if(table->lookup($1->name)->dectype != $3->dectype)
				 {
					 errors++;

					 fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);
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

			$$->dectype = "int ";
		 }
		 ;

rel_expression	: simple_expression	{
	$$ = new SymbolInfo();


	$$->name = $1->name;

	fprintf(parserLog, "At line no : %d rel_expression : simple_expression\n\n%s\n\n", line_count, $$->name.c_str());

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

			$$->dectype = "int ";
		}
		;

simple_expression : term	{

	$$ = new SymbolInfo();


	$$->name = $1->name;

	fprintf(parserLog, "At line no: %d simple_expression : term\n\n%s\n\n", line_count, $$->name.c_str());

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

				else if($1->dectype == "float " || $3->dectype == "float ")
				{
					$$->dectype = "float ";
				}

				else
						$$->dectype = "int ";
			}
		  ;

term :	unary_expression	{

	$$ = new SymbolInfo();


				$$->name = $1->name ;

				fprintf(parserLog, "At line no : %d term : unary_expression\n\n%s\n\n", line_count, $$->name.c_str());

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
				 $$->dectype = "int ";
			 }

			 else if($2->name == "/")
			 {
				 if($1->dectype == "void " || $3->dectype == "void ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

					 $$->dectype = "int ";
				 }

				 else if($1->dectype == "int " && $3->dectype == "int ")
				 {
					 $$->dectype = "int ";
				 }

				 else
				 		{
							$$->dectype = "float ";
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

				 else if($1->dectype == "float " && $3->dectype == "float ")
				 {
					 $$->dectype = "float ";
				 }

				 else
				 		$$->dectype = "int ";
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
				$$->dectype = $2->dectype;
			}
		 }
		 | factor	{

			 $$ = new SymbolInfo();


			 $$->name = $1->name;

			 fprintf(parserLog, "At line no : %d unary_expression : factor\n\n%s\n\n", line_count, $$->name.c_str());

			 $$->dectype = $1->dectype;
		 }
		 ;

factor	: variable	{

	$$ = new SymbolInfo();


	$$->name = $1->name;

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
				vector<string> names = si->function->param_list;
				vector<string> types = si->function->param_type;

				for(int i=0;i<num;i++)
				{
					if(argList[i]->dectype != types[i])
					{
						errors++;

						fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

						break;
					}
				}
			}
		}
		argList.clear();
	}
	| LPAREN expression RPAREN	{

		$$ = new SymbolInfo();


		$$->name = "(" + $2->name + ")" ;

		fprintf(parserLog, "At line no : %d factor : LPAREN expression RPAREN\n\n%s\n\n", line_count, $$->name.c_str());

		$$->dectype = $2->dectype;
	}
	| CONST_INT	{

		$$ = new SymbolInfo();


		$$->name = $1->name;

		fprintf(parserLog, "At line no : %d factor : CONST_INT\n\n%s\n\n", line_count, $$->name.c_str());

		$$->dectype = "int ";

	}
	| CONST_FLOAT	{

		$$ = new SymbolInfo();


		$$->name = $1->name;

		fprintf(parserLog, "At line no : %d factor : CONST_FLOAT\n\n%s\n\n", line_count, $$->name.c_str());

		$$->dectype = "float ";
	}
	| variable INCOP	{

		$$ = new SymbolInfo();


		$$->name = $1->name + "++";

		$$->dectype = $1->dectype;

		fprintf(parserLog, "At line no : %d factor : variable INCOP\n\n%s\n\n", line_count, $$->name.c_str());
	}
	| variable DECOP	{

		$$ = new SymbolInfo();


		$$->name = $1->name + "--";

		$$->dectype = $1->dectype;

		fprintf(parserLog, "At line no : %d factor : variable DECOP\n\n%s\n\n", line_count, $$->name.c_str());
	}
	;

argument_list : arguments	{

	$$ = new SymbolInfo();


		$$->name = $1->name ;

		fprintf(parserLog, "At line no : %d argument_list : arguments\n\n%s\n\n", line_count, $$->name.c_str());
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
}
	      | logic_expression	{

					$$ = new SymbolInfo();


					$$->name = $1->name;

					$$->dectype = $1->dectype;

					argList.push_back($1);

					fprintf(parserLog, "At line no : %d arguments : logic_expression\n\n%s\n\n", line_count, $$->name.c_str());
				}
	      ;


%%

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
