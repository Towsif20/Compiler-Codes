/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1605020.y" /* yacc.c:339  */

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



#line 156 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    INT = 262,
    FLOAT = 263,
    DOUBLE = 264,
    CHAR = 265,
    RETURN = 266,
    VOID = 267,
    PRINTLN = 268,
    ADDOP = 269,
    MULOP = 270,
    ASSIGNOP = 271,
    RELOP = 272,
    LOGICOP = 273,
    NOT = 274,
    SEMICOLON = 275,
    COMMA = 276,
    LPAREN = 277,
    RPAREN = 278,
    LCURL = 279,
    RCURL = 280,
    LTHIRD = 281,
    RTHIRD = 282,
    INCOP = 283,
    DECOP = 284,
    CONST_INT = 285,
    CONST_FLOAT = 286,
    ID = 287,
    DO = 288,
    SWITCH = 289,
    DEFAULT = 290,
    BREAK = 291,
    CASE = 292,
    CONTINUE = 293,
    CONST_CHAR = 294,
    BITOP = 295,
    LOWER_THAN_ELSE = 296
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define INT 262
#define FLOAT 263
#define DOUBLE 264
#define CHAR 265
#define RETURN 266
#define VOID 267
#define PRINTLN 268
#define ADDOP 269
#define MULOP 270
#define ASSIGNOP 271
#define RELOP 272
#define LOGICOP 273
#define NOT 274
#define SEMICOLON 275
#define COMMA 276
#define LPAREN 277
#define RPAREN 278
#define LCURL 279
#define RCURL 280
#define LTHIRD 281
#define RTHIRD 282
#define INCOP 283
#define DECOP 284
#define CONST_INT 285
#define CONST_FLOAT 286
#define ID 287
#define DO 288
#define SWITCH 289
#define DEFAULT 290
#define BREAK 291
#define CASE 292
#define CONTINUE 293
#define CONST_CHAR 294
#define BITOP 295
#define LOWER_THAN_ELSE 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 289 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   116,   116,   207,   216,   227,   237,   248,   261,   339,
     383,   383,   544,   544,   682,   693,   705,   716,   731,   730,
     764,   789,   845,   857,   865,   877,   890,   902,   913,   926,
     938,   952,   961,   972,   983,  1016,  1046,  1079,  1115,  1143,
    1180,  1189,  1203,  1241,  1311,  1326,  1381,  1396,  1476,  1489,
    1560,  1575,  1624,  1639,  1757,  1790,  1820,  1836,  1866,  1951,
    1967,  1989,  2011,  2054,  2098,  2109,  2117,  2129
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "INT",
  "FLOAT", "DOUBLE", "CHAR", "RETURN", "VOID", "PRINTLN", "ADDOP", "MULOP",
  "ASSIGNOP", "RELOP", "LOGICOP", "NOT", "SEMICOLON", "COMMA", "LPAREN",
  "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "INCOP", "DECOP",
  "CONST_INT", "CONST_FLOAT", "ID", "DO", "SWITCH", "DEFAULT", "BREAK",
  "CASE", "CONTINUE", "CONST_CHAR", "BITOP", "LOWER_THAN_ELSE", "$accept",
  "start", "program", "unit", "func_declaration", "func_definition", "@1",
  "@2", "parameter_list", "compound_statement", "@3", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -74

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      73,   -74,   -74,   -74,    10,    73,   -74,   -74,   -74,   -74,
      -7,   -74,   -74,    28,    36,     6,    21,   -74,    27,    59,
      22,    50,    63,    66,   -74,    69,    73,    78,   -74,   -74,
      74,    84,   -74,    71,   -74,    69,    83,   -74,    94,   -74,
     -74,   -74,    89,    90,    93,    30,    95,    30,    30,   -74,
      30,   -74,   -74,    65,   -74,   -74,    87,    64,   -74,   -74,
      18,   100,   -74,   103,     5,   107,   -74,   -74,    30,     1,
      30,   108,    91,    45,   -74,   -74,   104,    30,    30,   105,
     -74,   -74,    30,   -74,   -74,   -74,    30,    30,    30,    30,
     106,     1,   109,   -74,   110,   -74,   -74,   111,   114,   112,
     -74,   -74,   107,   116,   -74,    94,    30,    94,   117,   -74,
      30,   -74,   132,   115,   -74,   -74,   -74,    94,    94,   -74,
     -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    22,    23,    24,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    27,     0,     0,     0,    21,     0,    12,
       0,    17,     0,    25,     9,     0,     0,    10,    16,    28,
       0,    18,    13,    15,     8,     0,     0,    20,     0,    14,
      11,    26,     0,     0,     0,     0,     0,     0,     0,    40,
       0,    60,    61,    42,    33,    31,     0,     0,    29,    32,
      57,     0,    44,    46,    48,    50,    52,    56,     0,     0,
       0,     0,     0,    57,    54,    55,     0,    65,     0,    27,
      19,    30,     0,    62,    63,    41,     0,     0,     0,     0,
       0,     0,     0,    39,     0,    59,    67,     0,    64,     0,
      45,    47,    51,    49,    53,     0,     0,     0,     0,    58,
       0,    43,    35,     0,    37,    38,    66,     0,     0,    36,
      34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   -74,   135,   -74,   -74,   -74,   -74,   -74,    33,
     -74,    11,    12,   -74,   -74,   -52,   -67,   -47,   -42,   -73,
      55,    54,    56,   -41,   -74,   -74,   -74
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    35,    25,    20,    54,
      38,    55,    56,    14,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    97,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,    73,    91,    71,    96,    81,    74,    75,    76,   100,
      11,     9,    10,     1,     2,    47,     9,    10,     3,    87,
      48,    49,    88,    50,   106,    13,    90,    21,    92,    19,
      73,    51,    52,    53,    82,    73,    99,   116,    33,    73,
      73,    73,    73,    26,    47,    27,    83,    84,   104,    48,
      15,    22,    50,   112,    16,   114,    17,    18,    32,    23,
      51,    52,    53,    73,   113,   119,   120,    42,    40,    43,
      44,     1,     2,    83,    84,    45,     3,    46,    47,    24,
       1,     2,    28,    48,    49,     3,    50,    77,    31,    80,
      29,    78,    30,    31,    51,    52,    53,    42,    34,    43,
      44,     1,     2,    39,    36,    45,     3,    46,    47,    37,
      41,    68,    69,    48,    49,    70,    50,    72,    31,    79,
      85,    86,    89,    94,    51,    52,    53,    95,    93,   105,
      87,    16,   107,   108,   109,   110,   117,   115,   118,   111,
      12,   101,   103,   102
};

static const yytype_uint8 yycheck[] =
{
      47,    48,    69,    45,    77,    57,    47,    48,    50,    82,
       0,     0,     0,     7,     8,    14,     5,     5,    12,    14,
      19,    20,    17,    22,    91,    32,    68,    15,    70,    23,
      77,    30,    31,    32,    16,    82,    78,   110,    26,    86,
      87,    88,    89,    21,    14,    23,    28,    29,    89,    19,
      22,    30,    22,   105,    26,   107,    20,    21,    25,    32,
      30,    31,    32,   110,   106,   117,   118,     3,    35,     5,
       6,     7,     8,    28,    29,    11,    12,    13,    14,    20,
       7,     8,    32,    19,    20,    12,    22,    22,    24,    25,
      27,    26,    26,    24,    30,    31,    32,     3,    20,     5,
       6,     7,     8,    32,    30,    11,    12,    13,    14,    25,
      27,    22,    22,    19,    20,    22,    22,    22,    24,    32,
      20,    18,    15,    32,    30,    31,    32,    23,    20,    23,
      14,    26,    23,    23,    23,    21,     4,    20,    23,    27,
       5,    86,    88,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    12,    43,    44,    45,    46,    47,    53,
      54,     0,    45,    32,    55,    22,    26,    20,    21,    23,
      50,    54,    30,    32,    20,    49,    21,    23,    32,    27,
      26,    24,    51,    54,    20,    48,    30,    25,    52,    32,
      51,    27,     3,     5,     6,    11,    13,    14,    19,    20,
      22,    30,    31,    32,    51,    53,    54,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    22,    22,
      22,    60,    22,    59,    65,    65,    60,    22,    26,    32,
      25,    57,    16,    28,    29,    20,    18,    14,    17,    15,
      60,    58,    60,    20,    32,    23,    61,    67,    68,    60,
      61,    62,    64,    63,    65,    23,    58,    23,    23,    23,
      21,    27,    57,    60,    57,    20,    61,     4,    23,    57,
      57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      48,    47,    49,    47,    50,    50,    50,    50,    52,    51,
      51,    53,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    67,    67,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       2,     3,     1,     1,     1,     3,     6,     1,     4,     1,
       2,     1,     1,     1,     7,     5,     7,     5,     5,     3,
       1,     2,     1,     4,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     2,     2,     1,     1,     4,     3,
       1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 117 "1605020.y" /* yacc.c:1646  */
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

			(yyvsp[0])->code = codes + ".code\n" + (yyvsp[0])->code;

			(yyvsp[0])->code = (yyvsp[0])->code + "OUTDEC PROC  \n\
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

			(yyval)->code = (yyvsp[0])->code;
			//$$->code = codes;

			FILE * asmcode = fopen("code.asm","w");

			fprintf(asmcode, (yyvsp[0])->code.c_str());

			fclose(asmcode);

			asmcode = fopen("code.asm", "r");

			optimization(asmcode);
		}
		//write your code in this block in all the similar blocks below

		(yyval) = new SymbolInfo();

		(yyval)->name = (yyvsp[0])->name;

		fprintf(parserLog, "At line no  %d : start : program\n\n%s\n\n",line_count, (yyval)->name.c_str());
	}
#line 1545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 207 "1605020.y" /* yacc.c:1646  */
    {
	(yyval) = new SymbolInfo();

	(yyval)->name = (yyvsp[-1])->name + "\n" + (yyvsp[0])->name;

	fprintf(parserLog,"At line no : %d program : program unit\n\n%s\n\n",line_count, (yyval)->name.c_str());

	(yyval)->code = (yyvsp[-1])->code + (yyvsp[0])->code;
}
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 216 "1605020.y" /* yacc.c:1646  */
    {
		(yyval) = new SymbolInfo();

		(yyval)->name = (yyvsp[0])->name ;

		fprintf(parserLog,"At line no : %d program : unit\n\n%s\n\n",line_count, (yyval)->name.c_str());

		(yyval)->code = (yyvsp[0])->code;
	}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 227 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();

	(yyval)->name = (yyvsp[0])->name ;

	fprintf(parserLog,"At line no : %d unit : var_declaration\n\n%s\n\n",line_count, (yyval)->name.c_str());

	(yyval)->code = (yyvsp[0])->code;
}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 237 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();

			 (yyval)->name = (yyvsp[0])->name ;

		 	fprintf(parserLog,"At line no : %d unit : func_declaration\n\n%s\n\n",line_count, (yyval)->name.c_str());

			(yyval)->code = (yyvsp[0])->code;

		 }
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 248 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = (yyvsp[0])->name ;

			 (yyval)->code = (yyvsp[0])->code;

		 	fprintf(parserLog,"At line no : %d unit : func_definition\n\n%s\n\n",line_count, (yyval)->name.c_str());
		 }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 261 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[-5])->name + (yyvsp[-4])->name + "(" + (yyvsp[-2])->name + ");\n" ;
	fprintf(parserLog,"At line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n%s\n\n",line_count, (yyval)->name.c_str());

	SymbolInfo * s = table->lookup((yyvsp[-4])->name);

	if(s == NULL)
	{
		table->insert((yyvsp[-4])->name, "ID", "Function");

		s = table->lookup((yyvsp[-4])->name);

		s->function = new Function();

		for(int i=0;i<paramList.size();i++)
		{
			s->function->param_list.push_back(paramList[i]->name);
			s->function->param_type.push_back(paramList[i]->dectype);
			s->function->setParamCount();
			//s->function->setParamCount(paramList[i]->name, paramList[i]->dectype);
		}

		paramList.clear();

		s->function->retType = (yyvsp[-5])->name;


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

				if(s->function->retType != (yyvsp[-5])->name)
				{
					errors++;

					fprintf(parserError, "Error at line no : %d : Return Type Mismatch \n\n", line_count);


				}

				paramList.clear();

			}
	}


}
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 339 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[-4])->name + " " + (yyvsp[-3])->name + "();\n" ;

			fprintf(parserLog,"At line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n%s\n\n",line_count, (yyval)->name.c_str());

			SymbolInfo * s = table->lookup((yyvsp[-3])->name);

			if(s == NULL)
			{
				table->insert((yyvsp[-3])->name, "ID", "Function");

				s = table->lookup((yyvsp[-3])->name);



				s->function = new Function();

				s->function->retType = (yyvsp[-4])->name;

			}

			{
				if(s->function->param_count != 0)
				{
					errors++;

					fprintf(parserError, "Error at line no  %d : Invalid number of parameters\n\n", line_count);
				}

				if(s->function->retType != (yyvsp[-4])->name)
				{
					errors++;

					fprintf(parserError, "Error at line no. %d : Return Type Mismatch\n\n", line_count);
				}
			}

		}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 383 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();




	SymbolInfo * s = table->lookup((yyvsp[-3])->name);

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

				if(s->function->retType != (yyvsp[-4])->name)
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
						fprintf(parserError,"Error at Line No.%d:  Multiple defination of function %s\n\n",line_count,(yyvsp[-3])->name.c_str());
		}
	}

	else
	{
		table->insert((yyvsp[-3])->name, "ID", "Function");

		s = table->lookup((yyvsp[-3])->name);

		s->function = new Function();

		for(int i=0;i<paramList.size();i++)
		{
			s->function->add_number_of_parameter(paramList[i]->name + IntToString(table->current->id+1), paramList[i]->dectype);
			//s->function->setParamCount(paramList[i]->name, paramList[i]->dectype);
		}

		s->function->retType = (yyvsp[-4])->name;
	}

}
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 466 "1605020.y" /* yacc.c:1646  */
    {

	(yyval)->name = (yyvsp[-6])->name +" " + (yyvsp[-5])->name + "(" + (yyvsp[-3])->name + ")"   + (yyvsp[0])->name ;

	fprintf(parserLog,"At line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

	(yyval)->code = (yyvsp[-5])->name + "proc\n";

	if((yyvsp[-5])->name == "main")
	{
		(yyval)->code = (yyval)->code + " mov ax, @data\n\tmov ds, ax\n" + (yyvsp[0])->code + "LReturn" + curfunction + ":\n\tmov ah, 4ch\n\tint 21h\n";
	}

	else
	{
		SymbolInfo * s = table->lookup((yyvsp[-5])->name);

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

		codes += (yyvsp[0])->code + "LReturn" + curfunction + ":\n";


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

		(yyval)->code = codes + (yyvsp[-5])->name + " endp\n";
	}

}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 544 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();

			SymbolInfo * s = table->lookup((yyvsp[-2])->name);

			if(s == NULL)
			{
				table->insert((yyvsp[-2])->name, "ID", "Function");

				s = table->lookup((yyvsp[-2])->name);

				s->function = new Function();

				s->function->defined = true;

				s->function->retType = (yyvsp[-3])->name;
			}

			else if(s->function->defined == false)
			{
				if(s->function->param_count != 0)
				{
					errors++;
					fprintf(parserError,"Error at Line No.%d:  Invalid number of parameters \n\n",line_count);
				}

				if(s->function->retType != (yyvsp[-3])->name)
				{
					errors++;

					fprintf(parserError,"Error at Line No.%d: Return Type Mismatch \n\n",line_count);
				}

				s->function->defined = true;

			}

			else
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d:  Multiple definition of function %s\n\n",line_count,(yyvsp[-2])->name.c_str());
			}

			curfunction = (yyvsp[-2])->name;
			variables.push_back(curfunction + "_return");

			(yyvsp[-3])->name = (yyvsp[-3])->name + " " + (yyvsp[-2])->name + "()";




			}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 597 "1605020.y" /* yacc.c:1646  */
    {


			(yyval)->name = (yyvsp[-5])->name + " " + (yyvsp[-4])->name + "()" + "\n" + (yyvsp[0])->name  ;
			fprintf(parserLog,"At line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			(yyval)->code = (yyvsp[-4])->name + " proc\n";
			//here
			if((yyvsp[-4])->name == "main")
			{
				(yyval)->code = (yyval)->code + " mov ax, @data\n\tmov ds, ax\n" + (yyvsp[0])->code + " LReturn" + curfunction + ":\n\tmov ah, 4ch\n\tint 21h\n";
			}

			else
			{
				SymbolInfo * s = table->lookup((yyvsp[-4])->name);

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

				codes += (yyvsp[0])->code + "LReturn" + curfunction + ":\n";



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

				(yyval)->code = codes + (yyvsp[-4])->name + " endp\n";

			}

			//$$->name = $1->name + $6->name;


		}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 682 "1605020.y" /* yacc.c:1646  */
    {
	(yyval) = new SymbolInfo();

	(yyval)->name = (yyvsp[-3])->name + ","  + (yyvsp[-1])->name + (yyvsp[0])->name;
	fprintf(parserLog,"At line no : %d parameter_list  : parameter_list COMMA type_specifier ID\n\n%s\n\n",line_count, (yyval)->name.c_str());

	//here

	paramList.push_back(new SymbolInfo((yyvsp[0])->name, "ID", (yyvsp[-1])->name));

}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 693 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[-2])->name + "," + (yyvsp[0])->name ;

			paramList.push_back(new SymbolInfo("","ID",(yyvsp[0])->name));

			fprintf(parserLog,"At line no : %d parameter_list  : parameter_list COMMA type_specifier\n\n%s\n\n",line_count, (yyval)->name.c_str());

		}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 705 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[-1])->name + (yyvsp[0])->name ;

			paramList.push_back(new SymbolInfo((yyvsp[0])->name, "ID", (yyvsp[-1])->name));

			fprintf(parserLog,"At line no : %d parameter_list  : type_specifier ID\n\n%s\n\n",line_count, (yyval)->name.c_str());
		}
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 716 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[0])->name ;

			paramList.push_back(new SymbolInfo("", "ID", (yyvsp[0])->name));

			fprintf(parserLog,"At line no : %d parameter_list  : type_specifier\n\n%s\n\n",line_count, (yyval)->name.c_str());
		}
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 731 "1605020.y" /* yacc.c:1646  */
    {
											(yyval) = new SymbolInfo();

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
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 748 "1605020.y" /* yacc.c:1646  */
    {




					(yyval)->name = "{\n" + (yyvsp[-1])->name + "\n}" ;

					fprintf(parserLog, "At line no : %d compound_statement : LCURL statements RCURL\n\n%s\n\n", line_count, (yyval)->name.c_str());

					(yyval)->code = (yyvsp[-1])->code;

					table->printAll(parserLog);

					table->ExitScope(parserLog);

}
#line 2175 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 764 "1605020.y" /* yacc.c:1646  */
    {

					table->EnterScope(parserLog, 10);

					for(int i=0;i<paramList.size();i++)
					{
						table->insert(paramList[i]->name, "ID", paramList[i]->dectype);

						variables.push_back(paramList[i]->name + IntToString(table->current->id));

					}
					paramList.clear();

					(yyval) = new SymbolInfo();


					(yyval)->name = "{}";

					fprintf(parserLog, "At line no : %d compound_statement : LCURL RCURL\n\n{}\n\n", line_count);

					table->printAll(parserLog);
						table->ExitScope(parserLog);
				}
#line 2203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 789 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[-2])->name +" " + (yyvsp[-1])->name + ";\n"  ;

	fprintf(parserLog, "At line no: %d var_declaration : type_specifier declaration_list SEMICOLON\n\n%s\n\n",line_count, (yyval)->name.c_str());

	if((yyval)->name == "void ")
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

				table->insert(decList[i]->name, decList[i]->type, (yyvsp[-2])->name + "array");
			}

			else
			{
				functionVariables.push_back(decList[i]->name + IntToString(table->current->id));

				table->insert(decList[i]->name, decList[i]->type, (yyvsp[-2])->name );

				variables.push_back(decList[i]->name + IntToString(table->current->id));
			}
		}
	}

	decList.clear();
}
#line 2262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 845 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


		fprintf(parserLog, "At line no: %d type_specifier : INT\n\n%s\n\n", line_count, (yyvsp[0])->getName().c_str());

		(yyval)->name = "int ";

		//$$->setName($1->getName() + " ");

}
#line 2279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 857 "1605020.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo();

			fprintf(parserLog, "At line no: %d type_specifier : FLOAT\n\n%s\n\n", line_count, (yyvsp[0])->getName().c_str());

			(yyval)->name = "float ";
			//$$->setName($1->getName() + " ");
		}
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 865 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			fprintf(parserLog, "At line no: %d type_specifier : VOID\n\n%s\n\n", line_count, (yyvsp[0])->getName().c_str());

			(yyval)->name = "void ";
			//$$->setName($1->getName() + " ");
		}
#line 2307 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 877 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


				(yyval)->setName((yyvsp[-2])->getName() + "," + (yyvsp[0])->getName());

				fprintf(parserLog, "At line no: %d declaration_list : declaration_list COMMA ID\n\n%s\n\n", line_count, (yyval)->name.c_str());

				decList.push_back(new SymbolInfo((yyvsp[0])->name, "ID"));


}
#line 2325 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 890 "1605020.y" /* yacc.c:1646  */
    {
				(yyval) = new SymbolInfo();


				fprintf(parserLog, "At line no: %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n%s %s %s %s %s %s\n\n", line_count, (yyvsp[-5])->getName().c_str(), ",",  (yyvsp[-3])->getName().c_str(), "[", (yyvsp[-1])->getName().c_str(), "]");

				decList.push_back(new SymbolInfo((yyvsp[-3])->name, "IDa"));



				(yyval)->setName((yyvsp[-5])->getName() + "," + (yyvsp[-3])->getName() + "[" + (yyvsp[-1])->getName() + "]");
			}
#line 2342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 902 "1605020.y" /* yacc.c:1646  */
    {

				(yyval) = new SymbolInfo();


				fprintf(parserLog, "At line no: %d declaration_list : ID\n\n%s\n\n", line_count, (yyvsp[0])->getName().c_str());

				decList.push_back(new SymbolInfo((yyvsp[0])->name, "ID"));

				(yyval)->setName((yyvsp[0])->getName());
			}
#line 2358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 913 "1605020.y" /* yacc.c:1646  */
    {

				(yyval) = new SymbolInfo();


				fprintf(parserLog, "At line no: %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n%s %s %s %s\n\n", line_count, (yyvsp[-3])->getName().c_str(), (yyvsp[-2])->getName().c_str(), (yyvsp[-1])->getName().c_str(), (yyvsp[0])->getName().c_str());

				decList.push_back(new SymbolInfo((yyvsp[-3])->name, "IDa"));

				(yyval)->setName((yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName());
			}
#line 2374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 926 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[0])->name ;

		fprintf(parserLog, "At line no: %d statements : statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

		(yyval)->code = (yyvsp[0])->code;

}
#line 2391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 938 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = (yyvsp[-1])->name + (yyvsp[0])->name ;

	 		fprintf(parserLog, "At line no: %d statements : statements statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			(yyval)->code = (yyvsp[-1])->code + (yyvsp[0])->code;

		 }
#line 2408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 952 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[0])->name;

	fprintf(parserLog, "At line no: %d statement : var_declaration\n\n%s\n\n",line_count, (yyval)->name.c_str());
}
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 961 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[0])->name;

			fprintf(parserLog, "At line no: %d statement : expression_statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			(yyval)->code = (yyvsp[0])->code;
		}
#line 2438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 972 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[0])->name;

			fprintf(parserLog, "At line no: %d statement : compound_statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			(yyval)->code = (yyvsp[0])->code;
		}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 983 "1605020.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo();


			(yyval)->name = "for(" + (yyvsp[-4])->name + (yyvsp[-3])->name + (yyvsp[-2])->name + ")" + (yyvsp[0])->name ;

			fprintf(parserLog, "At line no: %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			if((yyvsp[-4])->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
					//here
					string codes = (yyvsp[-4])->code;
					char * label1 = newLabel();
					char * label2 = newLabel();
					codes += string(label1) + ":\n";
					codes += "\tmov ax, " + (yyvsp[-3])->idval + "\n";
					codes += "\tcmp ax, 0";
					codes += "\tje " + string(label2) + "\n";
					codes += (yyvsp[0])->code;
					codes += "\tjmp " + string(label1) + "\n";
					codes += string(label2) + ":\n";
					(yyval)->code = codes;
			}


		}
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1016 "1605020.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo();


			(yyval)->name = "if(" + (yyvsp[-2])->name + ")\n" + (yyvsp[0])->name ;

			fprintf(parserLog, "At line no: %d statement : IF LPAREN expression RPAREN statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			if((yyvsp[-2])->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				//here
				string codes = (yyvsp[-2])->code;
				char * label1 = newLabel();
				codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
				codes += "\tcmp ax, 0\n";
				codes += "\tje " + string(label1) + "\n";
				codes += (yyvsp[0])->code;
				codes += string(label1) + ":\n";
				(yyval)->code = codes;
			}


		}
#line 2527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1046 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = "if(" + (yyvsp[-4])->name + ")\n" + (yyvsp[-2])->name + " else " +(yyvsp[0])->name ;

			fprintf(parserLog, "At line no: %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n%s\n\n",line_count, (yyval)->name.c_str());

			if((yyvsp[-4])->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				string codes = (yyvsp[-4])->code;
				char * label1 = newLabel();
				char * label2 = newLabel();

				codes += "\tmov ax, " + (yyvsp[-4])->idval + "\n";
				codes += "\tcmp ax, 0\n";
				codes+="\tje "+string(label1)+"\n";
				codes += (yyvsp[-2])->code;

				codes += "\tjmp " + string(label2) + "\n";
				codes += string(label1) + "\n";

				(yyval)->code = codes;
			}
		}
#line 2565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1079 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = "while(" + (yyvsp[-2])->name + ") \n" + (yyvsp[0])->name ;

			fprintf(parserLog, "At line no : %d statement : WHILE LPAREN expression RPAREN statement\n\n%s\n\n", line_count, (yyval)->name.c_str());

			if((yyvsp[-2])->dectype == "void ")
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
				codes += (yyvsp[-2])->code;

				codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
				codes += "\tcmp ax, 0\n";
				codes += "\tje "+string(label2)+"\n";
				codes += (yyvsp[0])->code;

				codes += "\tjmp " + string(label1) + "\n";
				codes += string(label1) + "\n";

				(yyval)->code = codes;
			}
		}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1115 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = "println(" + (yyvsp[-2])->name + ");\n" ;

			fprintf(parserLog, "At line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n%s\n\n", line_count, (yyval)->name.c_str());

			string codes = "";

			if(table->lookUpScopeID((yyvsp[-2])->name) == -1)
			{
				errors++;

				fprintf(parserError, "Error at Line No.%d:  Undeclared Variable: %s \n\n",line_count,(yyvsp[-2])->name.c_str());
			}

			else
			{
				codes += "\tmov ax, " + (yyvsp[-2])->name + IntToString(table->lookUpScopeID((yyvsp[-2])->name));

				codes += "\n\tcall outdec\n";
			}

			(yyval)->code = codes;

		}
#line 2639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1143 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = "return " + (yyvsp[-1])->name + ";\n " ;

			fprintf(parserLog, "At line no : %d statement : RETURN expression SEMICOLON\n\n%s\n\n", line_count, (yyval)->name.c_str());

			if((yyvsp[-1])->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
			}

			else
			{
				string codes = (yyvsp[-1])->code;

				codes += "\tmov ax, " + (yyvsp[-1])->idval + "\n";

				codes += "\tmov " + curfunction + "_return, ax\n";

				codes += "\tjmp LReturn" + curfunction + "\n";

				(yyval)->code = codes;
			}



		}
#line 2676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1180 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = ";" ;

	fprintf(parserLog, "At line no : %d expression_statement : SEMICOLON\n\n%s\n\n", line_count, (yyval)->name.c_str());
}
#line 2690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1189 "1605020.y" /* yacc.c:1646  */
    {

				(yyval) = new SymbolInfo();


				(yyval)->name = (yyvsp[-1])->name + ";\n" ;

				fprintf(parserLog, "At line no : %d expression_statement : expression SEMICOLON\n\n%s\n\n", line_count, (yyval)->name.c_str());

				(yyval)->code = (yyvsp[-1])->code;
				(yyval)->idval = (yyvsp[-1])->idval;
			}
#line 2707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1203 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();




	SymbolInfo * s = table->lookup((yyvsp[0])->name);

	if(s == NULL)
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Undeclared variable %s\n\n", line_count, (yyvsp[0])->name.c_str());
	}

	else if(table->lookup((yyvsp[0])->name)->dectype == "int array" || table->lookup((yyvsp[0])->name)->dectype == "float array")
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Type Mismatch: \n\n", line_count);
	}

	if(s != NULL)
	{
		(yyval)->dectype = s->dectype;

		(yyval)->idval = (yyvsp[0])->name + IntToString(table->lookUpScopeID((yyvsp[0])->name));
	}

	(yyval)->name = (yyvsp[0])->name;
	(yyval)->type = "notarray";

	fprintf(parserLog, "At line no : %d variable : ID\n\n%s\n\n", line_count, (yyval)->name.c_str());



}
#line 2750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1241 "1605020.y" /* yacc.c:1646  */
    {

		 (yyval) = new SymbolInfo();


		 (yyval)->name = (yyvsp[-3])->name +"[" + (yyvsp[-1])->name + "]";

	 	fprintf(parserLog, "At line no : %d variable : ID LTHIRD expression RTHIRD\n\n%s\n\n", line_count, (yyval)->name.c_str());

		SymbolInfo * s = table->lookup((yyvsp[-3])->name);

		if(s == NULL)
		{
			errors++;

			fprintf(parserError, "Error at line no %d : Undeclared variable %s\n\n", line_count,(yyvsp[-3])->name.c_str());
		}

		//cout<<"value of $3 : "<<$3->dectype<<endl;

		else if((yyvsp[-1])->dectype == "float " || (yyvsp[-1])->dectype == "void ")
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
					(yyvsp[-3])->dectype = "int ";
				}

				if(s->dectype == "float array")
				{
					(yyvsp[-3])->dectype = "float ";
				}
			}

			(yyval)->dectype = (yyvsp[-3])->dectype;

			string codes = "";

			codes += (yyvsp[-1])->code + "\n";

			codes += "\tmov bx, " + (yyvsp[-1])->idval + "\n";

			codes += "\tadd bx, bx\n";

			(yyval)->idval = (yyvsp[-3])->name + IntToString(table->lookUpScopeID((yyvsp[-3])->name));

			(yyval)->code = codes;

		}

		(yyval)->type = "array";

	 }
#line 2823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1311 "1605020.y" /* yacc.c:1646  */
    {

	 (yyval) = new SymbolInfo();


	 (yyval)->name = (yyvsp[0])->name;

	 (yyval)->dectype = (yyvsp[0])->dectype;

	 fprintf(parserLog, "At line no : %d expression : logic_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

	 (yyval)->code = (yyvsp[0])->code;
	 (yyval)->idval = (yyvsp[0])->idval;

 }
#line 2843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1326 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = (yyvsp[-2])->name + " = " + (yyvsp[0])->name ;

			 fprintf(parserLog, "At line no : %d expression : variable ASSIGNOP logic_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

			 if((yyvsp[0])->dectype == "void ")
			 {
				 errors++;

				 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

				 (yyval)->dectype = "int ";
			 }

			 else
			 {
				 if((yyvsp[-2])->dectype != (yyvsp[0])->dectype)
				 {
					 errors++;

					 fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);
				 }

				 else
				 {
					 //here
					 string codes = (yyvsp[-2])->code;

					 codes += (yyvsp[0])->code;
					 codes += "\tmov ax, " + (yyvsp[0])->idval + "\n";

					 if((yyvsp[-2])->type == "notarray")
					 {
						 codes += "\tmov " + (yyvsp[-2])->idval + ", ax\n";
					 }

					 else
					 {
						 codes += "\tmov " + (yyvsp[-2])->idval + "[bx], ax\n";
					 }

					 (yyval)->code = codes;

					 (yyval)->idval = (yyvsp[-2])->idval;
				 }
			 }

			 (yyval)->dectype = (yyvsp[-2])->dectype;
		 }
#line 2901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1381 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[0])->name ;

		(yyval)->dectype = (yyvsp[0])->dectype;

		fprintf(parserLog, "At line no : %d logic_expression : rel_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

		//here now
		(yyval)->code = (yyvsp[0])->code;
		(yyval)->idval = (yyvsp[0])->idval;
}
#line 2921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1396 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = (yyvsp[-2])->name + " " + (yyvsp[-1])->name + " " + (yyvsp[0])->name + " " ;

	 		fprintf(parserLog, "At line no : %d logic_expression : rel_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

			if((yyvsp[-2])->dectype == "void " || (yyvsp[0])->dectype == "void ")
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);
			}

			else
			{
				string codes = (yyvsp[-2])->code;

				codes += (yyvsp[0])->code;

				char *label1=newLabel();
				char *label2=newLabel();
				char *label3=newLabel();
				char *temp=newTemp();

				if((yyvsp[-1])->name == "||")
				{
					codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tjne " + string(label2) +  "\n";
					codes += "\tmov ax, " + (yyvsp[0])->idval + "\n";
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
					codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tje " + string(label2) +  "\n";
					codes += "\tmov ax, " + (yyvsp[0])->idval + "\n";
					codes += "\tcmp ax, 0\n";

					codes += "\tje " + string(label2) +  "\n";

					codes+=string(label1)+":\n";

					codes += "\tmov " + string(temp) + ", 1\n";
					codes += "\tjmp " + string(label3) + "\n";

					codes+=string(label2)+":\n";

					codes += "\tmov " + string(temp) + ", 0\n";
					codes+=string(label3)+":\n";
				}

				(yyval)->code = codes;
				(yyval)->idval = temp;
				variables.push_back(temp);
			}

			(yyval)->dectype = "int ";
		 }
#line 3004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1476 "1605020.y" /* yacc.c:1646  */
    {
	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[0])->name;

	fprintf(parserLog, "At line no : %d rel_expression : simple_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

	(yyval)->code = (yyvsp[0])->code;
	(yyval)->idval = (yyvsp[0])->idval;

	(yyval)->dectype = (yyvsp[0])->dectype;
}
#line 3022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1489 "1605020.y" /* yacc.c:1646  */
    {

			(yyval) = new SymbolInfo();


			(yyval)->name = (yyvsp[-2])->name + (yyvsp[-1])->name + (yyvsp[0])->name;

			fprintf(parserLog, "At line no : %d rel_expression : simple_expression RELOP simple_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

			if((yyvsp[-2])->dectype == "void " || (yyvsp[0])->dectype == "void ")
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d: Type Mismatch \n\n",line_count);

				(yyval)->dectype = "int ";
			}

			else
			{
				string codes = (yyvsp[-2])->code;
				codes += (yyvsp[0])->code;

				char *temp=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();

				codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
				codes += "\tcmp ax, " + (yyvsp[0])->idval + "\n";

				string op = "";

				if((yyvsp[-1])->name == "<")
					op = "jl";

				else if((yyvsp[-1])->name == "<=")
					op = "jle";

				else if((yyvsp[-1])->name == ">")
						op = "jg";

				else if((yyvsp[-1])->name == ">=")
							op = "jge";


				else if((yyvsp[-1])->name == "==")
					op = "je";

					else if((yyvsp[-1])->name == "!=")
						op = "jne";



				codes += "\t" + op + " " + string(label1) + "\n";

				codes += "\tmov " + string(temp) + ", 0\n";
				codes += "\tjmp " + string(label2) + "\n";
				codes+=string(label1)+":\n";
				codes += "\tmov " + string(temp) + ", 1\n";
				codes+=string(label2)+":\n";

				variables.push_back(temp);
				(yyval)->code = codes;
				(yyval)->idval = temp;

			}

			(yyval)->dectype = "int ";
		}
#line 3096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1560 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[0])->name;

	fprintf(parserLog, "At line no: %d simple_expression : term\n\n%s\n\n", line_count, (yyval)->name.c_str());

	//here
	(yyval)->code = (yyvsp[0])->code;
	(yyval)->idval = (yyvsp[0])->idval;

	(yyval)->dectype = (yyvsp[0])->dectype;
}
#line 3116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1575 "1605020.y" /* yacc.c:1646  */
    {

				(yyval)->name = (yyvsp[-2])->name + (yyvsp[-1])->name + (yyvsp[0])->name ;

				fprintf(parserLog, "At line no: %d simple_expression : simple_expression ADDOP term\n\n%s\n\n", line_count, (yyval)->name.c_str());

				if((yyvsp[-2])->dectype == "void " || (yyvsp[0])->dectype == "void ")
				{
					errors++;

					fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);
				}

				else
				{
					if((yyvsp[-2])->dectype == "float " || (yyvsp[0])->dectype == "float ")
					{
						(yyval)->dectype = "float ";
					}

					else
							(yyval)->dectype = "int ";

					string codes = (yyvsp[-2])->code + (yyvsp[0])->code;

					codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
					char *temp=newTemp();

					if((yyvsp[-1])->name == "+")
					{
						codes += "\tadd ax, " + (yyvsp[0])->idval + "\n";
					}
					else
					{
						codes += "\tsub ax, " + (yyvsp[0])->idval + "\n";
					}

					codes += "\tmov " + string(temp) + ", ax\n";

					(yyval)->code = codes;
					(yyval)->idval = temp;
					variables.push_back(temp);
				}



			}
#line 3168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1624 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


				(yyval)->name = (yyvsp[0])->name ;

				fprintf(parserLog, "At line no : %d term : unary_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

				(yyval)->code = (yyvsp[0])->code;
				(yyval)->idval = (yyvsp[0])->idval;

				(yyval)->dectype = (yyvsp[0])->dectype;

}
#line 3188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1639 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = (yyvsp[-2])->name + (yyvsp[-1])->name + (yyvsp[0])->name;

			 fprintf(parserLog, "At line no : %d term : term MULOP unary_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

			 if((yyvsp[-2])->dectype == "void " || (yyvsp[0])->dectype == "void ")
			 {
				 errors++;

				 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

				 (yyval)->dectype = "int ";
			 }

			 else if((yyvsp[-1])->name == "%")
			 {
				 if((yyvsp[-2])->dectype != "int " || (yyvsp[0])->dectype != "int ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Non Integer operand on modulus operator\n\n", line_count);
				 }
				 else
				 	(yyval)->dectype = "int ";


				string codes = (yyvsp[-2])->code + (yyvsp[0])->code;
				char *temp=newTemp();

				codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
				codes += "\tmov bx, " + (yyvsp[0])->idval + "\n";
				codes += "\tmov dx, 0\n";
				codes += "div bx\n";
				codes += "\tmov " + string(temp) + ", dx\n";
				(yyval)->code = codes;
				(yyval)->idval = temp;
				variables.push_back(temp);
			 }

			 else if((yyvsp[-1])->name == "/")
			 {
				 if((yyvsp[-2])->dectype == "void " || (yyvsp[0])->dectype == "void ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

					 (yyval)->dectype = "int ";
				 }

				 else
				 {
					 if((yyvsp[-2])->dectype == "int " && (yyvsp[0])->dectype == "int ")
					 {
						 (yyval)->dectype = "int ";
					 }

					 else
					 		{
								(yyval)->dectype = "float ";
							}

							string codes = (yyvsp[-2])->code + (yyvsp[0])->code;
							char *temp=newTemp();

							codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
							codes += "\tmov bx, " + (yyvsp[0])->idval + "\n";
							codes += "\tmov dx, 0\n";
							codes += "div bx\n";
							codes += "\tmov " + string(temp) + ", ax\n";
							(yyval)->code = codes;
							(yyval)->idval = temp;
							variables.push_back(temp);

				 }
			 }

			 else
			 {
				 if((yyvsp[-2])->dectype == "void " || (yyvsp[0])->dectype == "void ")
				 {
					 errors++;

					 fprintf(parserError, "Error at line no %d : Type Mismatch\n\n", line_count);

					 (yyval)->dectype = "int ";
				 }

				 else
				 {
					 if((yyvsp[-2])->dectype == "float " && (yyvsp[0])->dectype == "float ")
					 {
						 (yyval)->dectype = "float ";
					 }

					 else
					 		(yyval)->dectype = "int ";

							string codes = (yyvsp[-2])->code + (yyvsp[0])->code;
							char *temp=newTemp();

							codes += "\tmov ax, " + (yyvsp[-2])->idval + "\n";
							codes += "\tmov bx, " + (yyvsp[0])->idval + "\n";
							codes += "\tmov dx, 0\n";
							codes += "mul bx\n";
							codes += "\tmov " + string(temp) + ", ax\n";
							(yyval)->code = codes;
							(yyval)->idval = temp;
							variables.push_back(temp);
				 }
			 }
		 }
#line 3309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1757 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[-1])->name + (yyvsp[0])->name;

	fprintf(parserLog, "At line no : %d unary_expression : ADDOP unary_expression\n\n%s\n\n",line_count, (yyval)->name.c_str());

	if((yyvsp[0])->dectype == "void ")
	{
		errors++;

		fprintf(parserError, "Error at line no %d : Type Mismatch\n\n");

		(yyval)->dectype = "int ";
	}

	else
	{
		string codes = (yyvsp[0])->code;
		if((yyvsp[-1])->name == "-")
		{
			codes += "\tmov ax, " + (yyvsp[0])->idval + "\n";
			codes += "\tneg ax\n";
			codes += "\tmov " + (yyvsp[0])->idval + ", ax\n";
		}

		(yyval)->code = codes;
		(yyval)->dectype = (yyvsp[0])->dectype;
	}

}
#line 3347 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1790 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = "!" + (yyvsp[0])->name;

		 	fprintf(parserLog, "At line no : %d unary_expression : NOT unary_expression\n\n%s\n\n",line_count, (yyval)->name.c_str());

			if((yyvsp[0])->dectype == "void ")
			{
				errors++;

				fprintf(parserError, "Error at line no %d : Type Mismatch\n\n");

				(yyval)->dectype = "int ";
			}

			else
			{
				string codes = (yyvsp[0])->code;
				codes += "\tmov ax, " + (yyvsp[0])->idval + "\n";
				codes += "\tneg ax\n";
				codes += "\tmov " + (yyvsp[0])->idval + ", ax\n";
				(yyval)->dectype = (yyvsp[0])->dectype;

				(yyval)->code = codes;
				(yyval)->idval = (yyvsp[0])->idval;
			}
		 }
#line 3382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1820 "1605020.y" /* yacc.c:1646  */
    {

			 (yyval) = new SymbolInfo();


			 (yyval)->name = (yyvsp[0])->name;

			 fprintf(parserLog, "At line no : %d unary_expression : factor\n\n%s\n\n", line_count, (yyval)->name.c_str());

			 (yyval)->dectype = (yyvsp[0])->dectype;

			 (yyval)->code = (yyvsp[0])->code;
			 (yyval)->idval = (yyvsp[0])->idval;
		 }
#line 3401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1836 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[0])->name;
	string codes = (yyvsp[0])->code;

	if((yyvsp[0])->type == "array")
	{
		char *temp=newTemp();

		codes += "\tmov ax, " + string(temp) + "[bx]\n";
		codes += "\tmov " + string(temp) + ", ax";

		variables.push_back(temp);
		(yyval)->idval = temp;
	}

	else
	{
		(yyval)->idval = (yyvsp[0])->idval;
	}

	(yyval)->code = codes;

	fprintf(parserLog, "At line no : %d factor : variable\n\n%s\n\n", line_count, (yyval)->name.c_str());

	(yyval)->dectype = (yyvsp[0])->dectype;
}
#line 3436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1866 "1605020.y" /* yacc.c:1646  */
    {

		(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[-3])->name + "(" + (yyvsp[-1])->name + ")";

		fprintf(parserLog, "At line no : %d factor : ID LPAREN argument_list RPAREN\n\n%s\n\n", line_count, (yyval)->name.c_str());

		SymbolInfo * si = table->lookup((yyvsp[-3])->name);

		if(si == NULL)
		{
			errors++;

			fprintf(parserError, "Error at line %d : Undefined function\n\n",line_count);
			(yyval)->dectype = "int ";
		}

		else if(si->function == NULL)
		{
			errors++;

			fprintf(parserError, "Error at line %d : Not A function\n\n",line_count);
			(yyval)->dectype = "int ";
		}

		else
		{
			if(si->function->defined == false)
			{
				errors++;

				fprintf(parserError, "Error at line %d : Undeclared function\n\n",line_count);
				(yyval)->dectype = "int ";
			}

			int num = si->function->param_count;

			(yyval)->dectype = si->function->retType;

			if(argList.size() != num)
			{
				errors++;

				fprintf(parserError,"Error at Line No.%d:  Invalid number of arguments \n\n",line_count);
			}

			else
			{
				string codes = (yyvsp[-1])->code;

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

				codes += "\tcall " + (yyvsp[-3])->name + "\n";

				codes += "\tmov ax, " + (yyvsp[-3])->name + "_return\n";

				char *temp=newTemp();
				codes += string(temp) + ", ax\n";

				(yyval)->code = codes;
				(yyval)->idval = temp;

				variables.push_back(temp);
			}
		}
		argList.clear();
	}
#line 3526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1951 "1605020.y" /* yacc.c:1646  */
    {

		(yyval) = new SymbolInfo();


		(yyval)->name = "(" + (yyvsp[-1])->name + ")" ;

		fprintf(parserLog, "At line no : %d factor : LPAREN expression RPAREN\n\n%s\n\n", line_count, (yyval)->name.c_str());

		//here

		(yyval)->code = (yyvsp[-1])->code;
		(yyval)->idval = (yyvsp[-1])->idval;

		(yyval)->dectype = (yyvsp[-1])->dectype;
	}
#line 3547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1967 "1605020.y" /* yacc.c:1646  */
    {

		(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[0])->name;

		fprintf(parserLog, "At line no : %d factor : CONST_INT\n\n%s\n\n", line_count, (yyval)->name.c_str());

		(yyval)->dectype = "int ";

		char *temp=newTemp();

		string codes = "";

		codes += "\tmov " + string(temp) + ", " + (yyvsp[0])->name + "\n";
		(yyval)->code = codes;
		(yyval)->idval = temp;

		variables.push_back(temp);

	}
#line 3574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1989 "1605020.y" /* yacc.c:1646  */
    {

		(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[0])->name;

		fprintf(parserLog, "At line no : %d factor : CONST_FLOAT\n\n%s\n\n", line_count, (yyval)->name.c_str());

		(yyval)->dectype = "float ";

		char *temp=newTemp();

		string codes = "";

		codes += "\tmov " + string(temp) + ", " + (yyvsp[0])->name + "\n";
		(yyval)->code = codes;
		(yyval)->idval = temp;

		variables.push_back(temp);

	}
#line 3601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 2011 "1605020.y" /* yacc.c:1646  */
    {

		(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[-1])->name + "++";

		(yyval)->dectype = (yyvsp[-1])->dectype;

		fprintf(parserLog, "At line no : %d factor : variable INCOP\n\n%s\n\n", line_count, (yyval)->name.c_str());

		string codes = "";

		char *temp=newTemp();

		if((yyvsp[-1])->type == "array")
		{
			codes += "\tmov ax, " + (yyvsp[-1])->idval + "[bx]\n";
		}
		else
		{
			codes += "\tmov ax, " + (yyvsp[-1])->idval + "\n";
		}

		codes += "\tmov " + string(temp) + ", ax\n";

		if((yyvsp[-1])->type == "array")
		{
			codes += "\tmov ax, " + (yyvsp[-1])->idval + "[bx]\n";
			codes += "\tinc ax\n";
			codes += "\tmov " + (yyvsp[-1])->idval + "[bx], ax";
		}

		else
		{
			codes += "\tinc " + (yyvsp[-1])->idval + "\n";
		}

		variables.push_back(temp);
		(yyval)->code = codes;
		(yyval)->idval = temp;

	}
#line 3649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 2054 "1605020.y" /* yacc.c:1646  */
    {

		(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[-1])->name + "--";

		(yyval)->dectype = (yyvsp[-1])->dectype;

		fprintf(parserLog, "At line no : %d factor : variable DECOP\n\n%s\n\n", line_count, (yyval)->name.c_str());

		string codes = "";

		char *temp=newTemp();

		if((yyvsp[-1])->type == "array")
		{
			codes += "\tmov ax, " + (yyvsp[-1])->idval + "[bx]\n";
		}
		else
		{
			codes += "\tmov ax, " + (yyvsp[-1])->idval + "\n";
		}

		codes += "\tmov " + string(temp) + ", ax\n";

		if((yyvsp[-1])->type == "array")
		{
			codes += "\tmov ax, " + (yyvsp[-1])->idval + "[bx]\n";
			codes += "\tdec ax\n";
			codes += "\tmov " + (yyvsp[-1])->idval + "[bx], ax";
		}

		else
		{
			codes += "\tdec " + (yyvsp[-1])->idval + "\n";
		}

		variables.push_back(temp);
		(yyval)->code = codes;
		(yyval)->idval = temp;
	}
#line 3696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 2098 "1605020.y" /* yacc.c:1646  */
    {

	(yyval) = new SymbolInfo();


		(yyval)->name = (yyvsp[0])->name ;

		fprintf(parserLog, "At line no : %d argument_list : arguments\n\n%s\n\n", line_count, (yyval)->name.c_str());

		(yyval)->code = (yyvsp[0])->code;
}
#line 3712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 2109 "1605020.y" /* yacc.c:1646  */
    {

					(yyval)->name = "" ;

					fprintf(parserLog, "At line no : %d argument_list : \n\n%s\n\n", line_count, (yyval)->name.c_str());
				}
#line 3723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 2117 "1605020.y" /* yacc.c:1646  */
    {
	(yyval) = new SymbolInfo();


	(yyval)->name = (yyvsp[-2])->name + "," + (yyvsp[0])->name;

	argList.push_back((yyvsp[0]));

	fprintf(parserLog, "At line no : %d arguments : arguments COMMA logic_expression\n\n%s\n\n",line_count, (yyval)->name.c_str());

	(yyval)->code = (yyvsp[-2])->code + (yyvsp[0])->code;
}
#line 3740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 2129 "1605020.y" /* yacc.c:1646  */
    {

					(yyval) = new SymbolInfo();


					(yyval)->name = (yyvsp[0])->name;

					(yyval)->dectype = (yyvsp[0])->dectype;

					argList.push_back((yyvsp[0]));

					fprintf(parserLog, "At line no : %d arguments : logic_expression\n\n%s\n\n", line_count, (yyval)->name.c_str());

					(yyval)->code = (yyvsp[0])->code;
				}
#line 3760 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3764 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2147 "1605020.y" /* yacc.c:1906  */


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
