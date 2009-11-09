/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KEYWORD_CONTROLLER = 258,
     KEYWORD_EMITTER = 259,
     KEYWORD_AFFECTOR = 260,
     KEYWORD_FUNCTION = 261,
     KEYWORD_STATE = 262,
     KEYWORD_EVENT = 263,
     KEYWORD_LOOP = 264,
     KEYWORD_WHILE = 265,
     KEYWORD_IF = 266,
     KEYWORD_ELSE = 267,
     KEYWORD_GOTO = 268,
     KEYWORD_WAIT = 269,
     KEYWORD_DIE = 270,
     INTEGER = 271,
     REAL = 272,
     IDENTIFIER = 273,
     SYMBOL_LTE = 274,
     SYMBOL_GTE = 275,
     SYMBOL_EQ = 276,
     SYMBOL_NEQ = 277,
     SYMBOL_LOG_AND = 278,
     SYMBOL_LOG_OR = 279,
     SYMBOL_INC = 280,
     SYMBOL_DEC = 281,
     SYMBOL_ADD_A = 282,
     SYMBOL_SUB_A = 283,
     SYMBOL_MUL_A = 284,
     SYMBOL_DIV_A = 285,
     TOKEN_ERROR = 286
   };
#endif
/* Tokens.  */
#define KEYWORD_CONTROLLER 258
#define KEYWORD_EMITTER 259
#define KEYWORD_AFFECTOR 260
#define KEYWORD_FUNCTION 261
#define KEYWORD_STATE 262
#define KEYWORD_EVENT 263
#define KEYWORD_LOOP 264
#define KEYWORD_WHILE 265
#define KEYWORD_IF 266
#define KEYWORD_ELSE 267
#define KEYWORD_GOTO 268
#define KEYWORD_WAIT 269
#define KEYWORD_DIE 270
#define INTEGER 271
#define REAL 272
#define IDENTIFIER 273
#define SYMBOL_LTE 274
#define SYMBOL_GTE 275
#define SYMBOL_EQ 276
#define SYMBOL_NEQ 277
#define SYMBOL_LOG_AND 278
#define SYMBOL_LOG_OR 279
#define SYMBOL_INC 280
#define SYMBOL_DEC 281
#define SYMBOL_ADD_A 282
#define SYMBOL_SUB_A 283
#define SYMBOL_MUL_A 284
#define SYMBOL_DIV_A 285
#define TOKEN_ERROR 286




/* Copy the first part of user declarations.  */
#line 1 "BulletParser.y"


#include <iostream>
#include <stdlib.h> // for Linux
#include "bsParseTree.h"

using namespace BS_NMSP;

#define YYERROR_VERBOSE
#define YYSTYPE ParseTreeNode*

int yylex (void);

extern char *yytext;
extern int yylineno;

static ParseTree* AST = ParseTree::instancePtr ();

void yyerror (char *a_msg)
{
	AST->addError (yylineno, a_msg);
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 183 "bsBulletParser.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   322

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  51
/* YYNRULES -- Number of rules. */
#define YYNRULES  122
/* YYNRULES -- Number of states. */
#define YYNSTATES  249

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    47,    46,     2,     2,
      36,    37,    44,    42,    38,    43,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    35,
      40,    34,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    20,    27,
      34,    42,    49,    57,    65,    74,    79,    81,    84,    86,
      89,    95,    97,   100,   106,   109,   113,   115,   119,   121,
     124,   129,   132,   136,   139,   143,   145,   148,   150,   153,
     155,   157,   159,   161,   163,   165,   167,   169,   171,   173,
     175,   177,   179,   181,   183,   185,   188,   194,   202,   210,
     216,   224,   232,   237,   241,   245,   250,   255,   260,   265,
     270,   279,   285,   291,   297,   303,   307,   313,   320,   325,
     327,   331,   333,   335,   340,   342,   344,   348,   350,   354,
     356,   360,   364,   366,   370,   374,   378,   382,   384,   388,
     392,   394,   398,   402,   406,   408,   411,   414,   416,   418,
     420,   422,   426,   429,   432,   436,   438,   442,   444,   447,
     449,   451,   453
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      49,     0,    -1,    50,    -1,    51,    -1,    50,    51,    -1,
      52,    -1,    53,    -1,     4,    94,    32,    61,    33,    -1,
       4,    94,    32,    57,    61,    33,    -1,     4,    94,    32,
      55,    61,    33,    -1,     4,    94,    32,    55,    57,    61,
      33,    -1,     4,    94,    32,    54,    61,    33,    -1,     4,
      94,    32,    54,    57,    61,    33,    -1,     4,    94,    32,
      54,    55,    61,    33,    -1,     4,    94,    32,    54,    55,
      57,    61,    33,    -1,     3,    94,    32,    33,    -1,    72,
      -1,    54,    72,    -1,    56,    -1,    55,    56,    -1,    94,
      34,     5,    91,    35,    -1,    58,    -1,    57,    58,    -1,
      94,    34,     6,    59,    63,    -1,    36,    37,    -1,    36,
      60,    37,    -1,    94,    -1,    60,    38,    94,    -1,    62,
      -1,    61,    62,    -1,    94,    34,     7,    64,    -1,    32,
      33,    -1,    32,    65,    33,    -1,    32,    33,    -1,    32,
      66,    33,    -1,    67,    -1,    65,    67,    -1,    68,    -1,
      66,    68,    -1,    69,    -1,    71,    -1,    72,    -1,    73,
      -1,    75,    -1,    77,    -1,    78,    -1,    81,    -1,    69,
      -1,    70,    -1,    72,    -1,    74,    -1,    76,    -1,    77,
      -1,    78,    -1,    35,    -1,    82,    35,    -1,    11,    36,
      82,    37,    64,    -1,    11,    36,    82,    37,    64,    12,
      64,    -1,    11,    36,    82,    37,    64,    12,    70,    -1,
      11,    36,    82,    37,    63,    -1,    11,    36,    82,    37,
      63,    12,    63,    -1,    11,    36,    82,    37,    63,    12,
      71,    -1,    94,    34,    82,    35,    -1,    94,    25,    35,
      -1,    94,    26,    35,    -1,    94,    27,    82,    35,    -1,
      94,    28,    82,    35,    -1,    94,    29,    82,    35,    -1,
      94,    30,    82,    35,    -1,    95,    34,    82,    35,    -1,
      95,    34,    32,    82,    38,    82,    33,    35,    -1,     9,
      36,    82,    37,    64,    -1,    10,    36,    82,    37,    64,
      -1,     9,    36,    82,    37,    63,    -1,    10,    36,    82,
      37,    63,    -1,    13,    94,    35,    -1,    14,    36,    82,
      37,    35,    -1,    94,    94,    92,    39,    79,    35,    -1,
      94,    94,    92,    35,    -1,    80,    -1,    79,    38,    80,
      -1,    91,    -1,    94,    -1,    15,    36,    37,    35,    -1,
      83,    -1,    84,    -1,    83,    24,    84,    -1,    85,    -1,
      84,    23,    85,    -1,    86,    -1,    85,    21,    86,    -1,
      85,    22,    86,    -1,    87,    -1,    86,    40,    87,    -1,
      86,    41,    87,    -1,    86,    19,    87,    -1,    86,    20,
      87,    -1,    88,    -1,    87,    42,    88,    -1,    87,    43,
      88,    -1,    89,    -1,    88,    44,    89,    -1,    88,    45,
      89,    -1,    88,    46,    89,    -1,    90,    -1,    42,    89,
      -1,    43,    89,    -1,    94,    -1,    95,    -1,    91,    -1,
      96,    -1,    36,    82,    37,    -1,    94,    92,    -1,    36,
      37,    -1,    36,    93,    37,    -1,    82,    -1,    93,    38,
      82,    -1,    18,    -1,    47,    94,    -1,    97,    -1,    98,
      -1,    16,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    59,    59,    66,    70,    79,    83,    90,   102,   113,
     136,   159,   182,   205,   240,   278,   287,   291,   300,   304,
     313,   322,   326,   335,   345,   349,   356,   361,   373,   377,
     386,   395,   399,   406,   410,   417,   421,   430,   434,   443,
     447,   451,   455,   459,   463,   467,   471,   478,   482,   486,
     490,   494,   498,   502,   509,   513,   520,   526,   533,   543,
     549,   556,   566,   572,   592,   612,   629,   646,   663,   683,
     689,   699,   705,   714,   720,   729,   737,   745,   755,   767,
     771,   780,   784,   792,   799,   807,   811,   820,   824,   833,
     837,   843,   852,   856,   862,   868,   874,   883,   887,   893,
     902,   906,   912,   918,   927,   931,   936,   944,   948,   952,
     956,   960,   967,   976,   980,   987,   992,  1004,  1012,  1021,
    1025,  1032,  1041
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_CONTROLLER", "KEYWORD_EMITTER",
  "KEYWORD_AFFECTOR", "KEYWORD_FUNCTION", "KEYWORD_STATE", "KEYWORD_EVENT",
  "KEYWORD_LOOP", "KEYWORD_WHILE", "KEYWORD_IF", "KEYWORD_ELSE",
  "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_DIE", "INTEGER", "REAL",
  "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ",
  "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC",
  "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A",
  "TOKEN_ERROR", "'{'", "'}'", "'='", "';'", "'('", "')'", "','", "':'",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'$'", "$accept",
  "script_file", "definition_list", "definition", "emitter_definition",
  "controller_definition", "member_list", "affector_list",
  "affector_declaration", "function_list", "function",
  "function_arguments", "argument_list", "state_list", "state",
  "function_compound_statement", "state_compound_statement",
  "function_statement_list", "state_statement_list", "function_statement",
  "state_statement", "expression_statement", "state_conditional_statement",
  "function_conditional_statement", "assignment_statement",
  "property_statement", "state_iteration_statement",
  "function_iteration_statement", "goto_statement", "wait_statement",
  "fire_statement", "controller_list", "controller_entry", "die_statement",
  "constant_expression", "logical_or_expression", "logical_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression",
  "function_call", "function_call_arguments", "argument_expression_list",
  "identifier", "property", "constant", "constant_integer",
  "constant_real", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   123,   125,    61,    59,    40,    41,    44,    58,
      60,    62,    43,    45,    42,    47,    37,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    54,    54,    55,    55,
      56,    57,    57,    58,    59,    59,    60,    60,    61,    61,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    70,    70,    70,    71,
      71,    71,    72,    72,    72,    72,    72,    72,    72,    73,
      73,    74,    74,    75,    75,    76,    77,    78,    78,    79,
      79,    80,    80,    81,    82,    83,    83,    84,    84,    85,
      85,    85,    86,    86,    86,    86,    86,    87,    87,    87,
      88,    88,    88,    88,    89,    89,    89,    90,    90,    90,
      90,    90,    91,    92,    92,    93,    93,    94,    95,    96,
      96,    97,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     4,     1,     2,     1,     2,
       5,     1,     2,     5,     2,     3,     1,     3,     1,     2,
       4,     2,     3,     2,     3,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     5,     7,     7,     5,
       7,     7,     4,     3,     3,     4,     4,     4,     4,     4,
       8,     5,     5,     5,     5,     3,     5,     6,     4,     1,
       3,     1,     1,     4,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     2,     2,     1,     1,     1,
       1,     3,     2,     2,     3,     1,     3,     1,     2,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   117,     0,
       0,     1,     4,     0,     0,    15,     0,     0,    18,     0,
      21,     0,    28,    16,     0,     0,     0,     0,    17,    19,
       0,     0,     0,    22,     0,     0,     7,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     9,     0,     8,     0,     0,    63,    64,   121,   122,
       0,     0,     0,     0,     0,    84,    85,    87,    89,    92,
      97,   100,   104,   109,   107,   108,   110,   119,   120,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    12,    10,
       0,   105,   106,   118,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
      66,    67,    68,     0,     0,     0,     0,     0,    30,    62,
      14,   111,    86,    88,    90,    91,    95,    96,    93,    94,
      98,    99,   101,   102,   103,   113,   115,     0,    20,    24,
       0,    26,     0,    23,     0,     0,     0,     0,     0,    33,
      54,     0,    37,    47,    48,    49,    50,    51,    52,    53,
       0,   107,   114,     0,    25,     0,     0,     0,     0,     0,
      31,     0,    35,    39,    40,    41,    42,    43,    44,    45,
      46,   108,     0,     0,     0,     0,     0,    34,    38,    55,
       0,     0,   116,    27,     0,     0,     0,     0,    32,    36,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,    83,     0,    69,    71,    72,    56,    76,     0,
      79,    81,    82,    73,    74,    59,     0,     0,    77,     0,
       0,     0,    57,    58,    80,    60,    61,     0,    70
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    16,    17,    18,    19,
      20,   116,   140,    21,    22,   143,   118,   171,   151,   172,
     152,   153,   154,   174,   155,   176,   156,   177,   157,   158,
     159,   229,   230,   180,   160,    65,    66,    67,    68,    69,
      70,    71,    72,    73,   109,   137,    74,    75,    76,    77,
      78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -138
static const short int yypact[] =
{
     206,    32,    32,    52,   206,  -138,  -138,  -138,  -138,    31,
      47,  -138,  -138,    82,    32,  -138,    32,    32,  -138,    32,
    -138,     4,  -138,  -138,   260,    32,    32,     9,  -138,  -138,
      32,    33,    87,  -138,    35,    89,  -138,  -138,   115,    94,
     119,   216,   216,   216,   216,    54,    32,    77,    84,  -138,
     102,  -138,   120,  -138,   209,   164,  -138,  -138,  -138,  -138,
     216,   216,   216,    32,   138,   154,   163,   197,    99,   193,
     122,  -138,  -138,  -138,   170,  -138,  -138,  -138,  -138,   155,
     191,   212,    32,   201,   167,   227,   144,  -138,  -138,  -138,
     228,  -138,  -138,  -138,  -138,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   116,  -138,
    -138,  -138,  -138,   229,   170,    21,   237,    95,  -138,  -138,
    -138,  -138,   163,   197,    99,    99,   193,   193,   193,   193,
     122,   122,  -138,  -138,  -138,  -138,  -138,   202,  -138,  -138,
     207,  -138,   165,  -138,   234,   235,   243,    32,   244,  -138,
    -138,   178,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
     246,   248,  -138,   216,  -138,    32,   247,   255,   256,   257,
    -138,   213,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,   261,   216,   216,   216,   262,   216,  -138,  -138,  -138,
     216,   170,  -138,  -138,   216,   216,   216,   259,  -138,  -138,
     225,   263,   264,   265,  -138,   266,    53,   267,   268,   269,
     272,   216,   273,   167,   167,   167,   274,  -138,    32,   237,
     237,   237,  -138,   275,  -138,  -138,  -138,   286,  -138,    51,
    -138,  -138,   170,  -138,  -138,   287,   216,    12,  -138,    32,
      24,   277,  -138,  -138,  -138,  -138,  -138,   276,  -138
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -138,  -138,  -138,   308,  -138,  -138,  -138,   298,    -8,   168,
      61,  -138,  -138,    48,     7,  -137,  -115,  -138,  -138,   145,
     166,  -135,    78,    79,    -6,  -138,  -138,  -138,  -138,  -131,
    -128,  -138,    81,  -138,   -39,  -138,   223,   226,   153,   103,
     150,   -30,  -138,   -70,   130,  -138,    -1,  -123,  -138,  -138,
    -138
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       9,    10,    64,    79,    80,    81,    85,   173,    23,    29,
      28,   178,   113,    24,   179,    24,    32,    29,    35,   181,
      38,    90,     8,   146,    32,    35,    38,     8,    37,    35,
      38,    91,    92,    38,    37,   168,   173,    36,    37,     8,
     178,    37,    49,   179,   117,    35,    38,    38,   181,    38,
       8,     8,    11,     8,    37,    37,   142,    37,   139,    82,
      83,    84,    93,    13,    27,    31,    51,    34,    53,   136,
      58,    59,     8,    47,    48,   132,   133,   134,    50,    14,
      33,   114,   233,   234,   235,    38,   238,    33,   217,   239,
      60,    33,   218,    37,    86,     8,    61,    62,   225,   226,
     227,    63,     8,   245,   144,   145,   146,    33,   147,   148,
      87,    58,    59,     8,   141,    15,   161,    88,    99,   100,
       8,    52,   242,    54,   192,    82,    83,    84,   149,    56,
     150,    60,    58,    59,     8,    89,   175,    61,    62,   101,
     102,   161,    63,   201,   202,   203,   185,   205,   231,    55,
     161,    85,    60,   135,    57,   207,   208,   209,    61,    62,
     191,   212,     8,    63,   193,   175,   105,   106,   107,   231,
     161,    84,   223,    94,   166,   167,   168,   120,    95,   148,
     169,    58,    59,     8,    26,    30,    96,   144,   145,   146,
     110,   147,   148,    46,    58,    59,     8,   241,   170,   117,
     150,    60,   126,   127,   128,   129,   108,    61,    62,     1,
       2,   187,    63,   150,    60,    83,    84,   232,    97,    98,
      61,    62,   166,   167,   168,    63,   111,   148,   169,    58,
      59,     8,    58,    59,     8,   103,   104,   115,   232,   162,
     163,    58,    59,     8,   164,   165,   198,   112,   150,    60,
     124,   125,    60,   130,   131,    61,    62,   211,    61,    62,
      63,    60,   119,    63,   138,   121,     8,    61,    62,   142,
     182,   183,    63,    39,    40,    41,    42,    43,    44,   184,
     186,   189,   190,   194,   108,    39,    40,    41,    42,    43,
      44,   195,   196,   197,    45,   200,   210,   204,   237,   240,
     213,   214,   215,   216,   219,   220,   221,   222,   224,   228,
     247,   248,    12,   236,    25,   243,   199,   188,   122,   246,
     244,   206,   123
};

static const unsigned char yycheck[] =
{
       1,     2,    41,    42,    43,    44,    45,   142,    14,    17,
      16,   142,    82,    14,   142,    16,    17,    25,    19,   142,
      21,    60,    18,    11,    25,    26,    27,    18,    21,    30,
      31,    61,    62,    34,    27,    11,   171,    33,    31,    18,
     171,    34,    33,   171,    32,    46,    47,    48,   171,    50,
      18,    18,     0,    18,    47,    48,    32,    50,    37,     5,
       6,     7,    63,    32,    16,    17,    33,    19,    33,   108,
      16,    17,    18,    25,    26,   105,   106,   107,    30,    32,
      19,    82,   219,   220,   221,    86,    35,    26,    35,    38,
      36,    30,    39,    86,    46,    18,    42,    43,   213,   214,
     215,    47,    18,   240,     9,    10,    11,    46,    13,    14,
      33,    16,    17,    18,   115,    33,   117,    33,    19,    20,
      18,    34,   237,    34,   163,     5,     6,     7,    33,    35,
      35,    36,    16,    17,    18,    33,   142,    42,    43,    40,
      41,   142,    47,   182,   183,   184,   147,   186,   218,    34,
     151,   190,    36,    37,    35,   194,   195,   196,    42,    43,
     161,   200,    18,    47,   165,   171,    44,    45,    46,   239,
     171,     7,   211,    35,     9,    10,    11,    33,    24,    14,
      15,    16,    17,    18,    16,    17,    23,     9,    10,    11,
      35,    13,    14,    25,    16,    17,    18,   236,    33,    32,
      35,    36,    99,   100,   101,   102,    36,    42,    43,     3,
       4,    33,    47,    35,    36,     6,     7,   218,    21,    22,
      42,    43,     9,    10,    11,    47,    35,    14,    15,    16,
      17,    18,    16,    17,    18,    42,    43,    36,   239,    37,
      38,    16,    17,    18,    37,    38,    33,    35,    35,    36,
      97,    98,    36,   103,   104,    42,    43,    32,    42,    43,
      47,    36,    35,    47,    35,    37,    18,    42,    43,    32,
      36,    36,    47,    25,    26,    27,    28,    29,    30,    36,
      36,    35,    34,    36,    36,    25,    26,    27,    28,    29,
      30,    36,    36,    36,    34,    34,    37,    35,    12,    12,
      37,    37,    37,    37,    37,    37,    37,    35,    35,    35,
      33,    35,     4,    38,    16,   237,   171,   151,    95,   240,
     239,   191,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    49,    50,    51,    52,    53,    18,    94,
      94,     0,    51,    32,    32,    33,    54,    55,    56,    57,
      58,    61,    62,    72,    94,    55,    57,    61,    72,    56,
      57,    61,    94,    58,    61,    94,    33,    62,    94,    25,
      26,    27,    28,    29,    30,    34,    57,    61,    61,    33,
      61,    33,    34,    33,    34,    34,    35,    35,    16,    17,
      36,    42,    43,    47,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    94,    95,    96,    97,    98,    82,
      82,    82,     5,     6,     7,    82,    61,    33,    33,    33,
      82,    89,    89,    94,    35,    24,    23,    21,    22,    19,
      20,    40,    41,    42,    43,    44,    45,    46,    36,    92,
      35,    35,    35,    91,    94,    36,    59,    32,    64,    35,
      33,    37,    84,    85,    86,    86,    87,    87,    87,    87,
      88,    88,    89,    89,    89,    37,    82,    93,    35,    37,
      60,    94,    32,    63,     9,    10,    11,    13,    14,    33,
      35,    66,    68,    69,    70,    72,    74,    76,    77,    78,
      82,    94,    37,    38,    37,    38,     9,    10,    11,    15,
      33,    65,    67,    69,    71,    72,    73,    75,    77,    78,
      81,    95,    36,    36,    36,    94,    36,    33,    68,    35,
      34,    94,    82,    94,    36,    36,    36,    36,    33,    67,
      34,    82,    82,    82,    35,    82,    92,    82,    82,    82,
      37,    32,    82,    37,    37,    37,    37,    35,    39,    37,
      37,    37,    35,    82,    35,    64,    64,    64,    35,    79,
      80,    91,    94,    63,    63,    63,    38,    12,    35,    38,
      12,    82,    64,    70,    80,    63,    71,    33,    35
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#ifndef	YYINITDEPTH
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
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
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
      size_t yyn = 0;
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

#endif /* YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


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
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
     `$$ = $1'.

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
#line 60 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 67 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 71 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 80 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 84 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 91 "BulletParser.y"
    {
			// members must be declared first, then functions, then events
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-3])->getStringData().c_str());
			delete (yyvsp[-3]);

			(yyval)->setChild(PT_MemberNode, 0);
			(yyval)->setChild(PT_AffectorNode, 0);
			(yyval)->setChild(PT_FunctionNode, 0);
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 8:
#line 103 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			(yyval)->setChild(PT_MemberNode, 0);
			(yyval)->setChild(PT_AffectorNode, 0);
			(yyval)->setChild(PT_FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 9:
#line 114 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			// affector list
			if ((yyvsp[-2])->getType() == PT_AffectorDecl)
			{
				// Create a PT_AffectorDeclList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(PT_AffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_AffectorNode, (yyvsp[-2]));
			}

			(yyval)->setChild(PT_MemberNode, 0);
			(yyval)->setChild(PT_FunctionNode, 0);
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 10:
#line 137 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			// affector list
			if ((yyvsp[-3])->getType() == PT_AffectorDecl)
			{
				// Create a PT_AffectorDeclList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(PT_AffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_AffectorNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_MemberNode, 0);
			(yyval)->setChild(PT_FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 11:
#line 160 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			// member list
			if ((yyvsp[-2])->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(PT_MemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_MemberNode, (yyvsp[-2]));
			}
			
			(yyval)->setChild(PT_AffectorNode, 0);
			(yyval)->setChild(PT_FunctionNode, 0);
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 12:
#line 183 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);

			// member list
			if ((yyvsp[-3])->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(PT_MemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_MemberNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_AffectorNode, 0);
			(yyval)->setChild(PT_FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 13:
#line 206 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			// member list
			if ((yyvsp[-3])->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(PT_MemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_MemberNode, (yyvsp[-3]));
			}
			
			// affector list
			if ((yyvsp[-2])->getType() == PT_AffectorDecl)
			{
				// Create a PT_AffectorDeclList and make $5 the child of it.
				YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(PT_AffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_AffectorNode, (yyvsp[-2]));
			}

			(yyval)->setChild(PT_FunctionNode, 0);
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 14:
#line 241 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-6])->getStringData().c_str());			
			delete (yyvsp[-6]);

			// member list
			if ((yyvsp[-4])->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, (yyvsp[-4])->getLine());
				newChild->setChild(0, (yyvsp[-4]));
				(yyval)->setChild(PT_MemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_MemberNode, (yyvsp[-4]));
			}

			// affector list
			if ((yyvsp[-3])->getType() == PT_AffectorDecl)
			{
				// Create a PT_AffectorDeclList and make $5 the child of it.
				YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(PT_AffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_AffectorNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 15:
#line 279 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());			
			delete (yyvsp[-2]);
		;}
    break;

  case 16:
#line 288 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 17:
#line 292 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 18:
#line 301 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 19:
#line 305 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 20:
#line 314 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 21:
#line 323 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 22:
#line 327 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 23:
#line 336 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 24:
#line 346 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 25:
#line 350 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 26:
#line 357 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 27:
#line 362 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 28:
#line 374 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 378 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 387 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 31:
#line 396 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 32:
#line 400 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 33:
#line 407 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 34:
#line 411 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 35:
#line 418 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 422 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 37:
#line 431 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 38:
#line 435 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 39:
#line 444 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 40:
#line 448 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 41:
#line 452 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 42:
#line 456 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 460 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 44:
#line 464 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 45:
#line 468 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 472 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 47:
#line 479 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 48:
#line 483 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 487 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 50:
#line 491 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 51:
#line 495 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 52:
#line 499 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 53:
#line 503 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 54:
#line 510 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 55:
#line 514 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 56:
#line 521 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 57:
#line 527 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 58:
#line 534 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 59:
#line 544 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 60:
#line 550 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 61:
#line 557 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 62:
#line 567 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 63:
#line 573 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			// create 'identifier + 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-2])->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 64:
#line 593 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			// create 'identifier - 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-2])->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 65:
#line 613 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier + ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 66:
#line 630 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier - ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 67:
#line 647 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier * ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_MultiplyStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 68:
#line 664 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier / ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_DivideStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 69:
#line 684 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 70:
#line 690 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 71:
#line 700 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 72:
#line 706 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 73:
#line 715 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 74:
#line 721 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 75:
#line 730 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 76:
#line 738 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 77:
#line 746 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 78:
#line 756 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 79:
#line 768 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 772 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 81:
#line 781 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 785 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 83:
#line 793 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 84:
#line 800 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 85:
#line 808 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 812 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 87:
#line 821 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 825 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 89:
#line 834 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 838 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 91:
#line 844 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 92:
#line 853 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 857 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 94:
#line 863 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 95:
#line 869 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 96:
#line 875 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 97:
#line 884 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 888 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 99:
#line 894 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 100:
#line 903 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 907 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 102:
#line 913 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 103:
#line 919 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 104:
#line 928 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 932 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 106:
#line 937 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 107:
#line 945 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 949 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 953 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 957 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 961 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 112:
#line 968 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 113:
#line 977 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 114:
#line 981 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 115:
#line 988 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 116:
#line 993 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 117:
#line 1005 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 118:
#line 1013 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 119:
#line 1022 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 120:
#line 1026 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 121:
#line 1033 "BulletParser.y"
    {
			// This only accepts non-negative integers
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 122:
#line 1042 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2629 "bsBulletParser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1048 "BulletParser.y"


	
	

