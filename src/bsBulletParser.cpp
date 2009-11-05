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
     KEYWORD_GUN = 258,
     KEYWORD_FUNCTION = 259,
     KEYWORD_STATE = 260,
     KEYWORD_LOOP = 261,
     KEYWORD_WHILE = 262,
     KEYWORD_IF = 263,
     KEYWORD_ELSE = 264,
     KEYWORD_GOTO = 265,
     KEYWORD_WAIT = 266,
     KEYWORD_DIE = 267,
     INTEGER = 268,
     REAL = 269,
     IDENTIFIER = 270,
     SYMBOL_LTE = 271,
     SYMBOL_GTE = 272,
     SYMBOL_EQ = 273,
     SYMBOL_NEQ = 274,
     SYMBOL_LOG_AND = 275,
     SYMBOL_LOG_OR = 276,
     SYMBOL_INC = 277,
     SYMBOL_DEC = 278,
     SYMBOL_ADD_A = 279,
     SYMBOL_SUB_A = 280,
     SYMBOL_MUL_A = 281,
     SYMBOL_DIV_A = 282,
     TOKEN_ERROR = 283
   };
#endif
/* Tokens.  */
#define KEYWORD_GUN 258
#define KEYWORD_FUNCTION 259
#define KEYWORD_STATE 260
#define KEYWORD_LOOP 261
#define KEYWORD_WHILE 262
#define KEYWORD_IF 263
#define KEYWORD_ELSE 264
#define KEYWORD_GOTO 265
#define KEYWORD_WAIT 266
#define KEYWORD_DIE 267
#define INTEGER 268
#define REAL 269
#define IDENTIFIER 270
#define SYMBOL_LTE 271
#define SYMBOL_GTE 272
#define SYMBOL_EQ 273
#define SYMBOL_NEQ 274
#define SYMBOL_LOG_AND 275
#define SYMBOL_LOG_OR 276
#define SYMBOL_INC 277
#define SYMBOL_DEC 278
#define SYMBOL_ADD_A 279
#define SYMBOL_SUB_A 280
#define SYMBOL_MUL_A 281
#define SYMBOL_DIV_A 282
#define TOKEN_ERROR 283




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
#line 177 "bsBulletParser.cpp"

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  47
/* YYNRULES -- Number of rules. */
#define YYNRULES  112
/* YYNRULES -- Number of states. */
#define YYNSTATES  223

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    44,    43,     2,     2,
      32,    33,    41,    39,    34,    40,     2,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    35,
      37,    31,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    16,    23,    30,    38,
      40,    43,    45,    48,    54,    57,    61,    63,    67,    69,
      72,    77,    80,    84,    87,    91,    93,    96,    98,   101,
     103,   105,   107,   109,   111,   113,   115,   117,   119,   121,
     123,   125,   127,   129,   131,   133,   136,   142,   150,   158,
     164,   172,   180,   185,   189,   193,   198,   203,   208,   213,
     218,   227,   233,   239,   245,   251,   255,   261,   268,   273,
     275,   279,   281,   283,   288,   290,   292,   296,   298,   302,
     304,   308,   312,   314,   318,   322,   326,   330,   332,   336,
     340,   342,   346,   350,   354,   356,   359,   362,   364,   366,
     368,   370,   374,   377,   380,   384,   386,   390,   392,   395,
     397,   399,   401
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      46,     0,    -1,    47,    -1,    48,    -1,    47,    48,    -1,
       3,    87,    29,    54,    30,    -1,     3,    87,    29,    49,
      54,    30,    -1,     3,    87,    29,    50,    54,    30,    -1,
       3,    87,    29,    49,    50,    54,    30,    -1,    65,    -1,
      49,    65,    -1,    51,    -1,    50,    51,    -1,    87,    31,
       4,    52,    56,    -1,    32,    33,    -1,    32,    53,    33,
      -1,    87,    -1,    53,    34,    87,    -1,    55,    -1,    54,
      55,    -1,    87,    31,     5,    57,    -1,    29,    30,    -1,
      29,    58,    30,    -1,    29,    30,    -1,    29,    59,    30,
      -1,    60,    -1,    58,    60,    -1,    61,    -1,    59,    61,
      -1,    62,    -1,    64,    -1,    65,    -1,    66,    -1,    68,
      -1,    70,    -1,    71,    -1,    74,    -1,    62,    -1,    63,
      -1,    65,    -1,    67,    -1,    69,    -1,    70,    -1,    71,
      -1,    35,    -1,    75,    35,    -1,     8,    32,    75,    33,
      57,    -1,     8,    32,    75,    33,    57,     9,    57,    -1,
       8,    32,    75,    33,    57,     9,    63,    -1,     8,    32,
      75,    33,    56,    -1,     8,    32,    75,    33,    56,     9,
      56,    -1,     8,    32,    75,    33,    56,     9,    64,    -1,
      87,    31,    75,    35,    -1,    87,    22,    35,    -1,    87,
      23,    35,    -1,    87,    24,    75,    35,    -1,    87,    25,
      75,    35,    -1,    87,    26,    75,    35,    -1,    87,    27,
      75,    35,    -1,    88,    31,    75,    35,    -1,    88,    31,
      29,    75,    34,    75,    30,    35,    -1,     6,    32,    75,
      33,    57,    -1,     7,    32,    75,    33,    57,    -1,     6,
      32,    75,    33,    56,    -1,     7,    32,    75,    33,    56,
      -1,    10,    87,    35,    -1,    11,    32,    75,    33,    35,
      -1,    87,    87,    85,    36,    72,    35,    -1,    87,    87,
      85,    35,    -1,    73,    -1,    72,    34,    73,    -1,    84,
      -1,    87,    -1,    12,    32,    33,    35,    -1,    76,    -1,
      77,    -1,    76,    21,    77,    -1,    78,    -1,    77,    20,
      78,    -1,    79,    -1,    78,    18,    79,    -1,    78,    19,
      79,    -1,    80,    -1,    79,    37,    80,    -1,    79,    38,
      80,    -1,    79,    16,    80,    -1,    79,    17,    80,    -1,
      81,    -1,    80,    39,    81,    -1,    80,    40,    81,    -1,
      82,    -1,    81,    41,    82,    -1,    81,    42,    82,    -1,
      81,    43,    82,    -1,    83,    -1,    39,    82,    -1,    40,
      82,    -1,    87,    -1,    88,    -1,    84,    -1,    89,    -1,
      32,    75,    33,    -1,    87,    85,    -1,    32,    33,    -1,
      32,    86,    33,    -1,    75,    -1,    86,    34,    75,    -1,
      15,    -1,    44,    87,    -1,    90,    -1,    91,    -1,    13,
      -1,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    56,    56,    63,    67,    76,    90,   111,   119,   143,
     147,   156,   160,   169,   179,   183,   190,   195,   207,   211,
     220,   229,   233,   240,   244,   251,   255,   264,   268,   277,
     281,   285,   289,   293,   297,   301,   305,   312,   316,   320,
     324,   328,   332,   336,   343,   347,   354,   360,   367,   377,
     383,   390,   400,   406,   426,   446,   463,   480,   497,   517,
     523,   533,   539,   548,   554,   563,   571,   579,   589,   601,
     605,   614,   618,   625,   632,   640,   644,   653,   657,   666,
     670,   676,   685,   689,   695,   701,   707,   716,   720,   726,
     735,   739,   745,   751,   760,   764,   769,   777,   781,   785,
     789,   793,   800,   809,   813,   820,   825,   837,   845,   854,
     858,   865,   874
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_GUN", "KEYWORD_FUNCTION",
  "KEYWORD_STATE", "KEYWORD_LOOP", "KEYWORD_WHILE", "KEYWORD_IF",
  "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_DIE", "INTEGER",
  "REAL", "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ",
  "SYMBOL_NEQ", "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC",
  "SYMBOL_DEC", "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A",
  "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'", "'}'", "'='", "'('", "')'", "','",
  "';'", "':'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'$'",
  "$accept", "script_file", "gun_definition_list", "gun_definition",
  "member_list", "function_list", "function", "function_arguments",
  "argument_list", "state_list", "state", "function_compound_statement",
  "state_compound_statement", "function_statement_list",
  "state_statement_list", "function_statement", "state_statement",
  "expression_statement", "state_conditional_statement",
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
     275,   276,   277,   278,   279,   280,   281,   282,   283,   123,
     125,    61,    40,    41,    44,    59,    58,    60,    62,    43,
      45,    42,    47,    37,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    49,
      49,    50,    50,    51,    52,    52,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    76,    76,    77,    77,    78,
      78,    78,    79,    79,    79,    79,    79,    80,    80,    80,
      81,    81,    81,    81,    82,    82,    82,    83,    83,    83,
      83,    83,    84,    85,    85,    86,    86,    87,    88,    89,
      89,    90,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     5,     6,     6,     7,     1,
       2,     1,     2,     5,     2,     3,     1,     3,     1,     2,
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
       0,     0,     0,     2,     3,   107,     0,     1,     4,     0,
       0,     0,    11,     0,    18,     9,     0,     0,     0,    10,
      12,     0,     0,     5,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     7,     0,     0,    53,    54,
     111,   112,     0,     0,     0,     0,     0,    74,    75,    77,
      79,    82,    87,    90,    94,    99,    97,    98,   100,   109,
     110,     0,     0,     0,     0,     0,     0,     8,     0,    95,
      96,   108,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,    56,    57,
      58,     0,     0,     0,    20,    52,   101,    76,    78,    80,
      81,    85,    86,    83,    84,    88,    89,    91,    92,    93,
     103,   105,     0,    14,     0,    16,     0,    13,     0,     0,
       0,     0,     0,    23,    44,     0,    27,    37,    38,    39,
      40,    41,    42,    43,     0,    97,   104,     0,    15,     0,
       0,     0,     0,     0,    21,     0,    25,    29,    30,    31,
      32,    33,    34,    35,    36,    98,     0,     0,     0,     0,
       0,    24,    28,    45,     0,     0,   106,    17,     0,     0,
       0,     0,    22,    26,     0,     0,     0,     0,    65,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,     0,     0,     0,     0,    73,     0,    59,    61,
      62,    46,    66,     0,    69,    71,    72,    63,    64,    49,
       0,     0,     0,    67,     0,     0,    47,    48,    70,    50,
      51,     0,    60
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     4,    10,    11,    12,    92,   114,    13,
      14,   117,    94,   145,   125,   146,   126,   127,   128,   148,
     129,   150,   130,   151,   131,   132,   133,   203,   204,   154,
     134,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      87,   112,    56,    57,    58,    59,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -172
static const short int yypact[] =
{
      28,    23,    68,    28,  -172,  -172,    82,  -172,  -172,    23,
      23,    23,  -172,     7,  -172,  -172,   230,    23,    59,  -172,
    -172,    93,    73,  -172,  -172,    78,   116,   136,   193,   193,
     193,   193,    21,    97,  -172,  -172,    80,   108,  -172,  -172,
    -172,  -172,   193,   193,   193,    23,   138,   163,   172,   117,
      60,   100,    75,  -172,  -172,  -172,   161,  -172,  -172,  -172,
    -172,   168,   175,   179,   164,   103,   180,  -172,   184,  -172,
    -172,  -172,  -172,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   165,  -172,  -172,  -172,
    -172,    86,   189,    56,  -172,  -172,  -172,   172,   117,    60,
      60,   100,   100,   100,   100,    75,    75,  -172,  -172,  -172,
    -172,  -172,   112,  -172,   126,  -172,    43,  -172,   188,   190,
     191,    23,   192,  -172,  -172,   142,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,   186,   219,  -172,   193,  -172,    23,
     196,   197,   198,   203,  -172,   155,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,   205,   193,   193,   193,   204,
     193,  -172,  -172,  -172,   193,   161,  -172,  -172,   193,   193,
     193,   207,  -172,  -172,   187,   214,   215,   216,  -172,   225,
     129,   226,   227,   229,   228,   193,   231,   103,   103,   103,
     232,  -172,    23,   189,   189,   189,  -172,   234,  -172,  -172,
    -172,   255,  -172,   141,  -172,  -172,   161,  -172,  -172,   256,
     193,    16,    23,  -172,    64,   208,  -172,  -172,  -172,  -172,
    -172,   235,  -172
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -172,  -172,  -172,   266,  -172,   261,    22,  -172,  -172,   111,
      81,   -88,  -108,  -172,  -172,   127,   148,  -105,    63,    61,
       9,  -172,  -172,  -172,  -172,  -103,  -102,  -172,    65,  -172,
     -27,  -172,   206,   202,   113,   -50,   131,   -37,  -172,  -171,
     115,  -172,    -1,   -93,  -172,  -172,  -172
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       6,    46,    61,    62,    63,    66,    69,    70,    16,    16,
      22,   147,    25,   152,   153,    68,    22,    25,    15,    19,
      25,   205,     5,   155,   120,    64,    65,   101,   102,   103,
     104,     1,    25,    20,    40,    41,     5,    23,     5,    20,
     147,   205,   152,   153,    71,    93,   107,   108,   109,   140,
     141,   142,   155,    42,   122,   143,    40,    41,     5,   111,
      43,    44,   118,   119,   120,    45,   121,   122,     7,    40,
      41,     5,   142,   144,     5,    42,    77,    78,   124,   199,
     200,   201,    43,    44,    64,    65,   123,    45,    42,    34,
     115,   124,   135,   116,    24,    43,    44,    79,    80,    24,
      45,     5,    24,   216,    36,   207,   208,   209,     5,    37,
     166,     9,     5,    65,    24,   135,    83,    84,    85,   113,
     159,    18,    21,    35,   135,   149,   219,    67,    33,   175,
     176,   177,    93,   179,   165,    75,    76,    66,   167,    81,
      82,   181,   182,   183,   135,   136,   137,   186,   118,   119,
     120,    38,   121,   122,   149,    40,    41,     5,   197,   138,
     139,   140,   141,   142,   191,   192,   122,   143,    40,    41,
       5,    39,   161,    72,    42,   212,   213,   124,    40,    41,
       5,    43,    44,   215,    73,   172,    45,    42,    99,   100,
     124,   206,    74,    86,    43,    44,    91,    42,   110,    45,
      40,    41,     5,    88,    43,    44,    40,    41,     5,    45,
      89,   206,   105,   106,    90,    95,   185,    96,   116,    42,
     156,   163,   157,   158,   160,    42,    43,    44,   168,   169,
     170,    45,    43,    44,     5,   171,   174,    45,   221,   178,
     184,    26,    27,    28,    29,    30,    31,   187,   188,   189,
     164,    86,    26,    27,    28,    29,    30,    31,   190,   193,
     194,    32,   195,   196,   211,   214,   198,   202,   210,     8,
     222,    17,   173,   162,   217,   220,    98,   218,     0,    97,
     180
};

static const short int yycheck[] =
{
       1,    28,    29,    30,    31,    32,    43,    44,     9,    10,
      11,   116,    13,   116,   116,    42,    17,    18,     9,    10,
      21,   192,    15,   116,     8,     4,     5,    77,    78,    79,
      80,     3,    33,    11,    13,    14,    15,    30,    15,    17,
     145,   212,   145,   145,    45,    29,    83,    84,    85,     6,
       7,     8,   145,    32,    11,    12,    13,    14,    15,    86,
      39,    40,     6,     7,     8,    44,    10,    11,     0,    13,
      14,    15,     8,    30,    15,    32,    16,    17,    35,   187,
     188,   189,    39,    40,     4,     5,    30,    44,    32,    30,
      91,    35,    93,    29,    13,    39,    40,    37,    38,    18,
      44,    15,    21,   211,    31,   193,   194,   195,    15,    31,
     137,    29,    15,     5,    33,   116,    41,    42,    43,    33,
     121,    10,    11,    30,   125,   116,   214,    30,    17,   156,
     157,   158,    29,   160,   135,    18,    19,   164,   139,    39,
      40,   168,   169,   170,   145,    33,    34,   174,     6,     7,
       8,    35,    10,    11,   145,    13,    14,    15,   185,    33,
      34,     6,     7,     8,    35,    36,    11,    12,    13,    14,
      15,    35,    30,    35,    32,    34,    35,    35,    13,    14,
      15,    39,    40,   210,    21,    30,    44,    32,    75,    76,
      35,   192,    20,    32,    39,    40,    32,    32,    33,    44,
      13,    14,    15,    35,    39,    40,    13,    14,    15,    44,
      35,   212,    81,    82,    35,    35,    29,    33,    29,    32,
      32,    35,    32,    32,    32,    32,    39,    40,    32,    32,
      32,    44,    39,    40,    15,    32,    31,    44,    30,    35,
      33,    22,    23,    24,    25,    26,    27,    33,    33,    33,
      31,    32,    22,    23,    24,    25,    26,    27,    33,    33,
      33,    31,    33,    35,     9,     9,    35,    35,    34,     3,
      35,    10,   145,   125,   211,   214,    74,   212,    -1,    73,
     165
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,    46,    47,    48,    15,    87,     0,    48,    29,
      49,    50,    51,    54,    55,    65,    87,    50,    54,    65,
      51,    54,    87,    30,    55,    87,    22,    23,    24,    25,
      26,    27,    31,    54,    30,    30,    31,    31,    35,    35,
      13,    14,    32,    39,    40,    44,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    87,    88,    89,    90,
      91,    75,    75,    75,     4,     5,    75,    30,    75,    82,
      82,    87,    35,    21,    20,    18,    19,    16,    17,    37,
      38,    39,    40,    41,    42,    43,    32,    85,    35,    35,
      35,    32,    52,    29,    57,    35,    33,    77,    78,    79,
      79,    80,    80,    80,    80,    81,    81,    82,    82,    82,
      33,    75,    86,    33,    53,    87,    29,    56,     6,     7,
       8,    10,    11,    30,    35,    59,    61,    62,    63,    65,
      67,    69,    70,    71,    75,    87,    33,    34,    33,    34,
       6,     7,     8,    12,    30,    58,    60,    62,    64,    65,
      66,    68,    70,    71,    74,    88,    32,    32,    32,    87,
      32,    30,    61,    35,    31,    87,    75,    87,    32,    32,
      32,    32,    30,    60,    31,    75,    75,    75,    35,    75,
      85,    75,    75,    75,    33,    29,    75,    33,    33,    33,
      33,    35,    36,    33,    33,    33,    35,    75,    35,    57,
      57,    57,    35,    72,    73,    84,    87,    56,    56,    56,
      34,     9,    34,    35,     9,    75,    57,    63,    73,    56,
      64,    30,    35
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
#line 57 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 64 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 68 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 77 "BulletParser.y"
    {
			// Guns have the following nodes:
			// 0: name
			// 1: member variables
			// 2: functions
			// 3: states
			// members must be declared first, then functions, then events
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
			(yyval)->setChild(NameNode, (yyvsp[-3]));
			(yyval)->setChild(MemberNode, 0);
			(yyval)->setChild(FunctionNode, 0);
			(yyval)->setChild(StateNode, (yyvsp[-1]));
		;}
    break;

  case 6:
#line 91 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
			(yyval)->setChild(NameNode, (yyvsp[-4]));
			
			// member list
			if ((yyvsp[-2])->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(MemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(MemberNode, (yyvsp[-2]));
			}
			
			(yyval)->setChild(FunctionNode, 0);
			(yyval)->setChild(StateNode, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 112 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
			(yyval)->setChild(NameNode, (yyvsp[-4]));
			(yyval)->setChild(MemberNode, 0);
			(yyval)->setChild(FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(StateNode, (yyvsp[-1]));
		;}
    break;

  case 8:
#line 120 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
			(yyval)->setChild(NameNode, (yyvsp[-5]));

			// member list
			if ((yyvsp[-3])->getType() == PT_AssignStatement)
			{
				// Create a PT_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_MemberList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(MemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(MemberNode, (yyvsp[-3]));
			}

			(yyval)->setChild(FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(StateNode, (yyvsp[-1]));
		;}
    break;

  case 9:
#line 144 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 10:
#line 148 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 11:
#line 157 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 12:
#line 161 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 13:
#line 170 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 14:
#line 180 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 15:
#line 184 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 16:
#line 191 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 17:
#line 196 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 18:
#line 208 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 19:
#line 212 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 20:
#line 221 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 21:
#line 230 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 22:
#line 234 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 23:
#line 241 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 24:
#line 245 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 25:
#line 252 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 256 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 265 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 28:
#line 269 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 29:
#line 278 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 30:
#line 282 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 31:
#line 286 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 32:
#line 290 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 33:
#line 294 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 34:
#line 298 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 35:
#line 302 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 306 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 37:
#line 313 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 38:
#line 317 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 321 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 40:
#line 325 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 41:
#line 329 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 42:
#line 333 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 337 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 44:
#line 344 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 45:
#line 348 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 46:
#line 355 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 361 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 48:
#line 368 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 49:
#line 378 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 384 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 51:
#line 391 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 52:
#line 401 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 53:
#line 407 "BulletParser.y"
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

  case 54:
#line 427 "BulletParser.y"
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

  case 55:
#line 447 "BulletParser.y"
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

  case 56:
#line 464 "BulletParser.y"
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

  case 57:
#line 481 "BulletParser.y"
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

  case 58:
#line 498 "BulletParser.y"
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

  case 59:
#line 518 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 60:
#line 524 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 61:
#line 534 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 62:
#line 540 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 549 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 64:
#line 555 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 65:
#line 564 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 66:
#line 572 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 67:
#line 580 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 68:
#line 590 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 69:
#line 602 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 606 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 71:
#line 615 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 619 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 626 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 74:
#line 633 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 75:
#line 641 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 645 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 77:
#line 654 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 658 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 79:
#line 667 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 671 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 81:
#line 677 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 82:
#line 686 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 690 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 84:
#line 696 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 85:
#line 702 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 86:
#line 708 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 87:
#line 717 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 721 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 89:
#line 727 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 90:
#line 736 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 740 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 92:
#line 746 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 93:
#line 752 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 94:
#line 761 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 765 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 96:
#line 770 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 97:
#line 778 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 782 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 786 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 790 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 794 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 102:
#line 801 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 103:
#line 810 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 104:
#line 814 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 105:
#line 821 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 106:
#line 826 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 107:
#line 838 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 108:
#line 846 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 109:
#line 855 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 859 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 866 "BulletParser.y"
    {
			// This only accepts non-negative integers
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 112:
#line 875 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2414 "bsBulletParser.cpp"

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


#line 881 "BulletParser.y"


	
	

