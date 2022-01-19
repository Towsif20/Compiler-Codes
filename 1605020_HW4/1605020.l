%{
#define YYSTYPE SymbolInfo *
#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<string.h>
#include<iostream>

#include"SymbolTable.h"
#include"y.tab.h"



FILE *logout;
FILE *tokenout;

int line_count = 1;

int errors = 0;


string str;
int currentline;

using namespace std;


extern YYSTYPE yylval;
extern SymbolTable *table;
extern FILE *parserLog;
void yyerror(char *);




%}



WHITESPACE [ \t\f\r\v]+
INTEGER_LITERALS [0-9]+
FLOAT_POINT_LITERALS [0-9]*\.?[0-9]+
NEWLINE \n
IDENTIFIER [A-Za-z_]+[A-Za-z0-9_]*

%x STRING
%x COMMENT

%%

{NEWLINE} {line_count++;}

"if"		{
			/* fprintf(tokenout,"<IF>");
			fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "IF");

			yylval = (YYSTYPE) s;

			return IF;

				}

"else"		{
			/* fprintf(tokenout,"<ELSE>");
			fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "ELSE");

			yylval = (YYSTYPE) s;

			return ELSE;

		}

"for" 		{
			/* fprintf(tokenout,"<FOR>");
			fprintf(logout,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "FOR");

			yylval = (YYSTYPE) s;

			return FOR;

		}

"do"		{
			/* fprintf(tokenout,"<DO>");
			fprintf(logout,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "DO");

			yylval = (YYSTYPE) s;

			return DO;

		}

"while"		{
			/* fprintf(tokenout,"<WHILE>");
			fprintf(logout,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "WHILE");

			yylval = (YYSTYPE) s;

			return WHILE;

		}

"switch"	{

				SymbolInfo  *  s = new SymbolInfo(yytext, "SWITCH");

				yylval = (YYSTYPE) s;

				return SWITCH;
						}

	"case"	{

					SymbolInfo  *  s = new SymbolInfo(yytext, "CASE");

					yylval = (YYSTYPE) s;

					return CASE;
												}

"break"		{
			/* fprintf(tokenout,"<BREAK>");
			fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "BREAK");

			yylval = (YYSTYPE) s;

			return BREAK;

		}

		"default"		{
					/* fprintf(tokenout,"<BREAK>");
					fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
					fprintf(logout,"\n"); */

					SymbolInfo  *  s = new SymbolInfo(yytext, "DEFAULT");

					yylval = (YYSTYPE) s;

					return DEFAULT;

				}

				"continue"		{
							/* fprintf(tokenout,"<BREAK>");
							fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
							fprintf(logout,"\n"); */

							SymbolInfo  *  s = new SymbolInfo(yytext, "CONTINUE");

							yylval = (YYSTYPE) s;

							return CONTINUE;

						}

"int"		{
			fprintf(tokenout,"<INT>");
			fprintf(logout,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");

			SymbolInfo  *  s = new SymbolInfo(yytext, "INT");

			yylval = (YYSTYPE) s;

			return INT;

		}


"char"		{
			/* fprintf(tokenout,"<CHAR>");
			fprintf(logout,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "CHAR");

			yylval = (YYSTYPE) s;

			return CHAR;

		}

"float"		{
			/* fprintf(tokenout,"<FLOAT>");
			fprintf(logout,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "FLOAT");

			yylval = (YYSTYPE) s;

			return FLOAT;
		}

"double"	{
			/* fprintf(tokenout,"<DOUBLE>");
			fprintf(logout,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n"); */

			SymbolInfo  *  s = new SymbolInfo(yytext, "DOUBLE");

			yylval = (YYSTYPE) s;

			return DOUBLE;

		}

"void"		{
			fprintf(tokenout,"<VOID>");
			fprintf(logout,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");

			SymbolInfo  *  s = new SymbolInfo(yytext, "VOID");

			yylval = (YYSTYPE) s;

			return VOID;

		}

"return"	{
			fprintf(tokenout,"<RETURN>");
			fprintf(logout,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
			fprintf(logout,"\n");

			SymbolInfo  *  s = new SymbolInfo(yytext, "RETURN");

			yylval = (YYSTYPE) s;

			return RETURN;

		}


"println" {
	SymbolInfo  *  s = new SymbolInfo(yytext, "PRINTLN");

	yylval = (YYSTYPE) s;

	return PRINTLN;
}



""


"+"		|

"-"		{
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule

			SymbolInfo * s = new  SymbolInfo(yytext, "ADDOP");

			yylval = (YYSTYPE) s;

			return ADDOP;

		}

"*" |
"/" |
"%" 		{
				fprintf(tokenout,"<MULOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);

				SymbolInfo * s = new  SymbolInfo(yytext, "MULOP");

				yylval = (YYSTYPE) s;

				return MULOP;

		}

"++" 		{

				SymbolInfo * s = new  SymbolInfo(yytext, "INCOP");

				yylval = (YYSTYPE) s;

				return INCOP;

				}
"--" 		{

				SymbolInfo * s = new  SymbolInfo(yytext, "DECOP");

				yylval = (YYSTYPE) s;

				return DECOP;

				}

"<" |
">" |
"<=" |
">=" |
"==" |
"!=" 		{
				fprintf(tokenout,"<RELOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);

				SymbolInfo * s = new  SymbolInfo(yytext, "RELOP");

				yylval = (YYSTYPE) s;

				return RELOP;

		}

"=" 		{
				fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);

				SymbolInfo * s = new  SymbolInfo(yytext, "ASSIGNOP");

				yylval = (YYSTYPE) s;

				return ASSIGNOP;

		}

"&&" |
"||" 		{
				fprintf(tokenout,"<LOGICOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);

				SymbolInfo * s = new  SymbolInfo(yytext, "LOGICOP");

				yylval = (YYSTYPE)s;

				return LOGICOP;

		}

"&" |
"|" |
"^" |
"<<" |
">>" 		{
				fprintf(tokenout,"<BITOP,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <BITOP> Lexeme %s found\n",line_count,yytext);

				SymbolInfo * s = new  SymbolInfo(yytext, "BITOP");

				yylval = (YYSTYPE)s;

				return BITOP;

		}


"!" 		{
				fprintf(tokenout,"<NOT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <NOT> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "NOT");

				yylval = (YYSTYPE)s;

				return NOT;

		}




"(" 		{
				fprintf(tokenout,"<LPAREN,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LPAREN> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "LPAREN");

				yylval = (YYSTYPE)s;

				return LPAREN;
		}

")" 		{
				fprintf(tokenout,"<RPAREN,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RPAREN> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "RPAREN");

				yylval = (YYSTYPE)s;

				return RPAREN;
		}

"{" 		{
				fprintf(tokenout,"<LCURL,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LCURL> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "LCURL");

				yylval = (YYSTYPE)s;

				return LCURL;
		}



"}" 		{
				fprintf(tokenout,"<RCURL,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RCURL> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "RCURL");

				yylval = (YYSTYPE)s;

				return RCURL;
		}

"[" 		{
				fprintf(tokenout,"<LTHIRD,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <LTHIRD> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "LTHIRD");

				yylval = (YYSTYPE)s;

				return LTHIRD;
		}

"]" 		{
				fprintf(tokenout,"<RTHIRD,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <RTHIRD> Lexeme %s found\n",line_count,yytext);

				SymbolInfo * s = new  SymbolInfo(yytext, "RTHIRD");

				yylval = (YYSTYPE)s;

				return RTHIRD;
		}

"," 		{
				fprintf(tokenout,"<COMMA,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "COMMA");

				yylval = (YYSTYPE) s;

				return COMMA;
		}

";" 		{
				fprintf(tokenout,"<SEMICOLON,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "SEMICOLON");

				yylval = (YYSTYPE)s;

				return SEMICOLON;
		}



{INTEGER_LITERALS}	{
				fprintf(tokenout,"<CONST_INT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "CONST_INT");

				yylval = (YYSTYPE)s;

				return CONST_INT;


			}



{FLOAT_POINT_LITERALS}	{
				fprintf(tokenout,"<CONST_FLOAT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "CONST_FLOAT");

				yylval = (YYSTYPE)s;

				return CONST_FLOAT;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}


\'[^\\]\' 	{
				fprintf(tokenout,"<CONST_CHAR,%c>",yytext[1]);
				fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
				fprintf(logout,"\n");

				SymbolInfo * s = new  SymbolInfo(yytext, "CONST_CHAR");

				yylval = (YYSTYPE)s;

				return CONST_CHAR;
				//insert in symbol table and print symbol table content(only non empty buckets)
			}



\'[\\][\\\"abfnrtv0]\'	{

							char ascii;

							if(yytext[2]=='a') ascii = 7;
							else if(yytext[2]=='b') ascii = 8;
							else if(yytext[2]=='f') ascii = 12;
							else if(yytext[2]=='n') ascii = 10;
							else if(yytext[2]=='r') ascii = 13;
							else if(yytext[2]=='t') ascii = 9;
							else if(yytext[2]=='v') ascii = 11;
							//if(yytext[2]=='0') ascii = 0;
							else if(yytext[2]=='\\') ascii = 92;
							else if(yytext[2]=='\"') ascii = 34;

							fprintf(tokenout,"<CONST_CHAR,%c>",ascii);
							fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
							fprintf(logout,"\n");

							string t = "";
							t.push_back(yytext[1]);

							SymbolInfo * s = new  SymbolInfo(t, "CONST_CHAR");

							yylval = (YYSTYPE)s;

							return CONST_CHAR;

						}










{WHITESPACE}	{}


{IDENTIFIER}	{
			fprintf(tokenout,"<ID,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);

			SymbolInfo * s = new  SymbolInfo(yytext, "ID");

			yylval = (YYSTYPE)s;

			return ID;
			//insert in symbol table and print symbol table content(only non empty buckets)
		}











<<EOF>>   {
				//line_count--;
                //table->printAll();

                fprintf(logout,"Total Lines: %d\n",line_count);
                fprintf(logout,"Total Errors: %d\n",errors);
                return 0;
          }



%%

int yywrap(void)
{
	return 1;
}
