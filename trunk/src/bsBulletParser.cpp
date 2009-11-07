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
     KEYWORD_AFFECTOR = 259,
     KEYWORD_FUNCTION = 260,
     KEYWORD_STATE = 261,
     KEYWORD_LOOP = 262,
     KEYWORD_WHILE = 263,
     KEYWORD_IF = 264,
     KEYWORD_ELSE = 265,
     KEYWORD_GOTO = 266,
     KEYWORD_WAIT = 267,
     KEYWORD_DIE = 268,
     INTEGER = 269,
     REAL = 270,
     IDENTIFIER = 271,
     SYMBOL_LTE = 272,
     SYMBOL_GTE = 273,
     SYMBOL_EQ = 274,
     SYMBOL_NEQ = 275,
     SYMBOL_LOG_AND = 276,
     SYMBOL_LOG_OR = 277,
     SYMBOL_INC = 278,
     SYMBOL_DEC = 279,
     SYMBOL_ADD_A = 280,
     SYMBOL_SUB_A = 281,
     SYMBOL_MUL_A = 282,
     SYMBOL_DIV_A = 283,
     TOKEN_ERROR = 284
   };
#endif
/* Tokens.  */
#define KEYWORD_GUN 258
#define KEYWORD_AFFECTOR 259
#define KEYWORD_FUNCTION 260
#define KEYWORD_STATE 261
#define KEYWORD_LOOP 262
#define KEYWORD_WHILE 263
#define KEYWORD_IF 264
#define KEYWORD_ELSE 265
#define KEYWORD_GOTO 266
#define KEYWORD_WAIT 267
#define KEYWORD_DIE 268
#define INTEGER 269
#define REAL 270
#define IDENTIFIER 271
#define SYMBOL_LTE 272
#define SYMBOL_GTE 273
#define SYMBOL_EQ 274
#define SYMBOL_NEQ 275
#define SYMBOL_LOG_AND 276
#define SYMBOL_LOG_OR 277
#define SYMBOL_INC 278
#define SYMBOL_DEC 279
#define SYMBOL_ADD_A 280
#define SYMBOL_SUB_A 281
#define SYMBOL_MUL_A 282
#define SYMBOL_DIV_A 283
#define TOKEN_ERROR 284




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
#line 179 "bsBulletParser.cpp"

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
#define YYLAST   321

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  49
/* YYNRULES -- Number of rules. */
#define YYNRULES  119
/* YYNRULES -- Number of states. */
#define YYNSTATES  243

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    45,    44,     2,     2,
      34,    35,    42,    40,    36,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,    33,
      38,    32,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    16,    23,    30,    38,
      45,    53,    61,    70,    72,    75,    77,    80,    86,    88,
      91,    97,   100,   104,   106,   110,   112,   115,   120,   123,
     127,   130,   134,   136,   139,   141,   144,   146,   148,   150,
     152,   154,   156,   158,   160,   162,   164,   166,   168,   170,
     172,   174,   176,   179,   185,   193,   201,   207,   215,   223,
     228,   232,   236,   241,   246,   251,   256,   261,   270,   276,
     282,   288,   294,   298,   304,   311,   316,   318,   322,   324,
     326,   331,   333,   335,   339,   341,   345,   347,   351,   355,
     357,   361,   365,   369,   373,   375,   379,   383,   385,   389,
     393,   397,   399,   402,   405,   407,   409,   411,   413,   417,
     420,   423,   427,   429,   433,   435,   438,   440,   442,   444
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      47,     0,    -1,    48,    -1,    49,    -1,    48,    49,    -1,
       3,    90,    30,    57,    31,    -1,     3,    90,    30,    53,
      57,    31,    -1,     3,    90,    30,    51,    57,    31,    -1,
       3,    90,    30,    51,    53,    57,    31,    -1,     3,    90,
      30,    50,    57,    31,    -1,     3,    90,    30,    50,    53,
      57,    31,    -1,     3,    90,    30,    50,    51,    57,    31,
      -1,     3,    90,    30,    50,    51,    53,    57,    31,    -1,
      68,    -1,    50,    68,    -1,    52,    -1,    51,    52,    -1,
      90,    32,     4,    87,    33,    -1,    54,    -1,    53,    54,
      -1,    90,    32,     5,    55,    59,    -1,    34,    35,    -1,
      34,    56,    35,    -1,    90,    -1,    56,    36,    90,    -1,
      58,    -1,    57,    58,    -1,    90,    32,     6,    60,    -1,
      30,    31,    -1,    30,    61,    31,    -1,    30,    31,    -1,
      30,    62,    31,    -1,    63,    -1,    61,    63,    -1,    64,
      -1,    62,    64,    -1,    65,    -1,    67,    -1,    68,    -1,
      69,    -1,    71,    -1,    73,    -1,    74,    -1,    77,    -1,
      65,    -1,    66,    -1,    68,    -1,    70,    -1,    72,    -1,
      73,    -1,    74,    -1,    33,    -1,    78,    33,    -1,     9,
      34,    78,    35,    60,    -1,     9,    34,    78,    35,    60,
      10,    60,    -1,     9,    34,    78,    35,    60,    10,    66,
      -1,     9,    34,    78,    35,    59,    -1,     9,    34,    78,
      35,    59,    10,    59,    -1,     9,    34,    78,    35,    59,
      10,    67,    -1,    90,    32,    78,    33,    -1,    90,    23,
      33,    -1,    90,    24,    33,    -1,    90,    25,    78,    33,
      -1,    90,    26,    78,    33,    -1,    90,    27,    78,    33,
      -1,    90,    28,    78,    33,    -1,    91,    32,    78,    33,
      -1,    91,    32,    30,    78,    36,    78,    31,    33,    -1,
       7,    34,    78,    35,    60,    -1,     8,    34,    78,    35,
      60,    -1,     7,    34,    78,    35,    59,    -1,     8,    34,
      78,    35,    59,    -1,    11,    90,    33,    -1,    12,    34,
      78,    35,    33,    -1,    90,    90,    88,    37,    75,    33,
      -1,    90,    90,    88,    33,    -1,    76,    -1,    75,    36,
      76,    -1,    87,    -1,    90,    -1,    13,    34,    35,    33,
      -1,    79,    -1,    80,    -1,    79,    22,    80,    -1,    81,
      -1,    80,    21,    81,    -1,    82,    -1,    81,    19,    82,
      -1,    81,    20,    82,    -1,    83,    -1,    82,    38,    83,
      -1,    82,    39,    83,    -1,    82,    17,    83,    -1,    82,
      18,    83,    -1,    84,    -1,    83,    40,    84,    -1,    83,
      41,    84,    -1,    85,    -1,    84,    42,    85,    -1,    84,
      43,    85,    -1,    84,    44,    85,    -1,    86,    -1,    40,
      85,    -1,    41,    85,    -1,    90,    -1,    91,    -1,    87,
      -1,    92,    -1,    34,    78,    35,    -1,    90,    88,    -1,
      34,    35,    -1,    34,    89,    35,    -1,    78,    -1,    89,
      36,    78,    -1,    16,    -1,    45,    90,    -1,    93,    -1,
      94,    -1,    14,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    57,    57,    64,    68,    77,    89,   100,   123,   146,
     169,   192,   227,   265,   269,   278,   282,   291,   300,   304,
     313,   323,   327,   334,   339,   351,   355,   364,   373,   377,
     384,   388,   395,   399,   408,   412,   421,   425,   429,   433,
     437,   441,   445,   449,   456,   460,   464,   468,   472,   476,
     480,   487,   491,   498,   504,   511,   521,   527,   534,   544,
     550,   570,   590,   607,   624,   641,   661,   667,   677,   683,
     692,   698,   707,   715,   723,   733,   745,   749,   758,   762,
     770,   777,   785,   789,   798,   802,   811,   815,   821,   830,
     834,   840,   846,   852,   861,   865,   871,   880,   884,   890,
     896,   905,   909,   914,   922,   926,   930,   934,   938,   945,
     954,   958,   965,   970,   982,   990,   999,  1003,  1010,  1019
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_GUN", "KEYWORD_AFFECTOR",
  "KEYWORD_FUNCTION", "KEYWORD_STATE", "KEYWORD_LOOP", "KEYWORD_WHILE",
  "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT",
  "KEYWORD_DIE", "INTEGER", "REAL", "IDENTIFIER", "SYMBOL_LTE",
  "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ", "SYMBOL_LOG_AND",
  "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC", "SYMBOL_ADD_A",
  "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'",
  "'}'", "'='", "';'", "'('", "')'", "','", "':'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'$'", "$accept", "script_file",
  "gun_definition_list", "gun_definition", "member_list", "affector_list",
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
     123,   125,    61,    59,    40,    41,    44,    58,    60,    62,
      43,    45,    42,    47,    37,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    50,    51,    51,    52,    53,    53,
      54,    55,    55,    56,    56,    57,    57,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    70,    70,
      71,    71,    72,    73,    74,    74,    75,    75,    76,    76,
      77,    78,    79,    79,    80,    80,    81,    81,    81,    82,
      82,    82,    82,    82,    83,    83,    83,    84,    84,    84,
      84,    85,    85,    85,    86,    86,    86,    86,    86,    87,
      88,    88,    89,    89,    90,    91,    92,    92,    93,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     5,     6,     6,     7,     6,
       7,     7,     8,     1,     2,     1,     2,     5,     1,     2,
       5,     2,     3,     1,     3,     1,     2,     4,     2,     3,
       2,     3,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     7,     7,     5,     7,     7,     4,
       3,     3,     4,     4,     4,     4,     4,     8,     5,     5,
       5,     5,     3,     5,     6,     4,     1,     3,     1,     1,
       4,     1,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     2,     2,     1,     1,     1,     1,     3,     2,
       2,     3,     1,     3,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     2,     3,   114,     0,     1,     4,     0,
       0,     0,    15,     0,    18,     0,    25,    13,     0,     0,
       0,     0,    14,    16,     0,     0,     0,    19,     0,     0,
       5,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,     0,     7,     0,     6,     0,     0,
      60,    61,   118,   119,     0,     0,     0,     0,     0,    81,
      82,    84,    86,    89,    94,    97,   101,   106,   104,   105,
     107,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,    11,    10,     8,     0,   102,   103,   115,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   109,    63,    64,    65,     0,     0,     0,
       0,     0,    27,    59,    12,   108,    83,    85,    87,    88,
      92,    93,    90,    91,    95,    96,    98,    99,   100,   110,
     112,     0,    17,    21,     0,    23,     0,    20,     0,     0,
       0,     0,     0,    30,    51,     0,    34,    44,    45,    46,
      47,    48,    49,    50,     0,   104,   111,     0,    22,     0,
       0,     0,     0,     0,    28,     0,    32,    36,    37,    38,
      39,    40,    41,    42,    43,   105,     0,     0,     0,     0,
       0,    31,    35,    52,     0,     0,   113,    24,     0,     0,
       0,     0,    29,    33,     0,     0,     0,     0,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,     0,    80,     0,    66,    68,
      69,    53,    73,     0,    76,    78,    79,    70,    71,    56,
       0,     0,    74,     0,     0,     0,    54,    55,    77,    57,
      58,     0,    67
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     4,    10,    11,    12,    13,    14,   110,
     134,    15,    16,   137,   112,   165,   145,   166,   146,   147,
     148,   168,   149,   170,   150,   171,   151,   152,   153,   223,
     224,   174,   154,    59,    60,    61,    62,    63,    64,    65,
      66,    67,   103,   131,    68,    69,    70,    71,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -143
static const short int yypact[] =
{
       0,    45,    11,     0,  -143,  -143,     7,  -143,  -143,    45,
      45,    45,  -143,    45,  -143,    17,  -143,  -143,   288,    45,
      45,    58,  -143,  -143,    45,    68,    38,  -143,    90,    54,
    -143,  -143,    56,    67,    71,   111,   111,   111,   111,    53,
      45,    97,    98,  -143,   102,  -143,   174,  -143,   131,   103,
    -143,  -143,  -143,  -143,   111,   111,   111,    45,   101,   124,
     109,   148,    73,   121,   142,  -143,  -143,  -143,   165,  -143,
    -143,  -143,  -143,   110,   139,   167,    45,   170,   127,   180,
     116,  -143,  -143,  -143,   172,  -143,  -143,  -143,  -143,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,    62,  -143,  -143,  -143,  -143,   187,   165,    50,
     201,   108,  -143,  -143,  -143,  -143,   109,   148,    73,    73,
     121,   121,   121,   121,   142,   142,  -143,  -143,  -143,  -143,
    -143,   140,  -143,  -143,   156,  -143,   181,  -143,   190,   199,
     206,    45,   214,  -143,  -143,   194,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,   216,   272,  -143,   111,  -143,    45,
     220,   221,   222,   223,  -143,   229,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,   218,   111,   111,   111,   225,
     111,  -143,  -143,  -143,   111,   165,  -143,  -143,   111,   111,
     111,   224,  -143,  -143,   237,   226,   230,   231,  -143,   233,
     -16,   238,   240,   241,   239,   111,   246,   127,   127,   127,
     251,  -143,    45,   201,   201,   201,  -143,   228,  -143,  -143,
    -143,   275,  -143,     2,  -143,  -143,   165,  -143,  -143,   276,
     111,    -8,  -143,    45,     4,   256,  -143,  -143,  -143,  -143,
    -143,   258,  -143
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -143,  -143,  -143,   289,  -143,   283,   144,   155,    40,  -143,
    -143,   270,    21,  -142,  -126,  -143,  -143,   136,   157,  -121,
      72,    74,    -5,  -143,  -143,  -143,  -143,  -120,  -111,  -143,
      76,  -143,    -7,  -143,   232,   215,   138,   123,   149,   -49,
    -143,   -74,   122,  -143,    -1,  -110,  -143,  -143,  -143
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       6,   140,   107,     1,    17,    22,    85,    86,    18,    18,
      26,     7,    29,   162,    32,   167,   172,   211,    26,    29,
      32,   212,   111,    29,    32,   173,   175,    32,    58,    73,
      74,    75,    79,     5,   136,   232,    31,     9,   233,    29,
      32,    32,    31,    32,   167,   172,    31,    84,    30,    31,
     126,   127,   128,    27,   173,   175,    87,    76,    77,    78,
      27,     5,    31,    31,    27,    31,     5,    52,    53,     5,
      46,   227,   228,   229,     5,   108,    52,    53,     5,    32,
      27,   219,   220,   221,     5,   133,    48,    54,    49,    43,
      93,    94,   239,    55,    56,   130,    54,   129,    57,    45,
      50,    31,    55,    56,    51,   236,     5,    57,   135,    78,
     155,    95,    96,     5,     5,   138,   139,   140,     5,   141,
     142,    47,    52,    53,     5,    52,    53,     5,    81,    82,
      90,   169,     5,    83,    88,   155,    77,    78,   225,   143,
     179,   144,    54,   104,   155,    54,    89,   114,    55,    56,
     186,    55,    56,    57,   185,    23,    57,   111,   187,   225,
     169,    97,    98,    23,   155,    20,    24,    91,    92,   195,
     196,   197,   105,   199,    40,   156,   157,    79,    76,    77,
      78,   201,   202,   203,    99,   100,   101,   206,   160,   161,
     162,   158,   159,   142,   163,    52,    53,     5,   217,   102,
     106,   138,   139,   140,   109,   141,   142,   115,    52,    53,
       5,   226,   164,   113,   144,    54,   120,   121,   122,   123,
     132,    55,    56,   235,   176,   181,    57,   144,    54,   118,
     119,   136,   226,   177,    55,    56,   160,   161,   162,    57,
     178,   142,   163,    52,    53,     5,   124,   125,   180,   183,
     194,    52,    53,     5,   188,   189,   190,   191,   198,   204,
     192,   207,   144,    54,   230,   208,   209,   205,   210,    55,
      56,    54,   216,   213,    57,   214,   215,    55,    56,   218,
      21,    25,    57,    28,   222,   231,   234,   241,     5,    41,
      42,   242,     8,    19,    44,    33,    34,    35,    36,    37,
      38,   193,   182,   237,   184,   117,   102,   200,   240,   238,
      80,    33,    34,    35,    36,    37,    38,     0,     0,     0,
      39,   116
};

static const short int yycheck[] =
{
       1,     9,    76,     3,     9,    10,    55,    56,     9,    10,
      11,     0,    13,     9,    15,   136,   136,    33,    19,    20,
      21,    37,    30,    24,    25,   136,   136,    28,    35,    36,
      37,    38,    39,    16,    30,    33,    15,    30,    36,    40,
      41,    42,    21,    44,   165,   165,    25,    54,    31,    28,
      99,   100,   101,    13,   165,   165,    57,     4,     5,     6,
      20,    16,    41,    42,    24,    44,    16,    14,    15,    16,
      32,   213,   214,   215,    16,    76,    14,    15,    16,    80,
      40,   207,   208,   209,    16,    35,    32,    34,    32,    31,
      17,    18,   234,    40,    41,   102,    34,    35,    45,    31,
      33,    80,    40,    41,    33,   231,    16,    45,   109,     6,
     111,    38,    39,    16,    16,     7,     8,     9,    16,    11,
      12,    31,    14,    15,    16,    14,    15,    16,    31,    31,
      21,   136,    16,    31,    33,   136,     5,     6,   212,    31,
     141,    33,    34,    33,   145,    34,    22,    31,    40,    41,
     157,    40,    41,    45,   155,    11,    45,    30,   159,   233,
     165,    40,    41,    19,   165,    10,    11,    19,    20,   176,
     177,   178,    33,   180,    19,    35,    36,   184,     4,     5,
       6,   188,   189,   190,    42,    43,    44,   194,     7,     8,
       9,    35,    36,    12,    13,    14,    15,    16,   205,    34,
      33,     7,     8,     9,    34,    11,    12,    35,    14,    15,
      16,   212,    31,    33,    33,    34,    93,    94,    95,    96,
      33,    40,    41,   230,    34,    31,    45,    33,    34,    91,
      92,    30,   233,    34,    40,    41,     7,     8,     9,    45,
      34,    12,    13,    14,    15,    16,    97,    98,    34,    33,
      32,    14,    15,    16,    34,    34,    34,    34,    33,    35,
      31,    35,    33,    34,    36,    35,    35,    30,    35,    40,
      41,    34,    33,    35,    45,    35,    35,    40,    41,    33,
      10,    11,    45,    13,    33,    10,    10,    31,    16,    19,
      20,    33,     3,    10,    24,    23,    24,    25,    26,    27,
      28,   165,   145,   231,    32,    90,    34,   185,   234,   233,
      40,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    89
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,    47,    48,    49,    16,    90,     0,    49,    30,
      50,    51,    52,    53,    54,    57,    58,    68,    90,    51,
      53,    57,    68,    52,    53,    57,    90,    54,    57,    90,
      31,    58,    90,    23,    24,    25,    26,    27,    28,    32,
      53,    57,    57,    31,    57,    31,    32,    31,    32,    32,
      33,    33,    14,    15,    34,    40,    41,    45,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    90,    91,
      92,    93,    94,    78,    78,    78,     4,     5,     6,    78,
      57,    31,    31,    31,    78,    85,    85,    90,    33,    22,
      21,    19,    20,    17,    18,    38,    39,    40,    41,    42,
      43,    44,    34,    88,    33,    33,    33,    87,    90,    34,
      55,    30,    60,    33,    31,    35,    80,    81,    82,    82,
      83,    83,    83,    83,    84,    84,    85,    85,    85,    35,
      78,    89,    33,    35,    56,    90,    30,    59,     7,     8,
       9,    11,    12,    31,    33,    62,    64,    65,    66,    68,
      70,    72,    73,    74,    78,    90,    35,    36,    35,    36,
       7,     8,     9,    13,    31,    61,    63,    65,    67,    68,
      69,    71,    73,    74,    77,    91,    34,    34,    34,    90,
      34,    31,    64,    33,    32,    90,    78,    90,    34,    34,
      34,    34,    31,    63,    32,    78,    78,    78,    33,    78,
      88,    78,    78,    78,    35,    30,    78,    35,    35,    35,
      35,    33,    37,    35,    35,    35,    33,    78,    33,    60,
      60,    60,    33,    75,    76,    87,    90,    59,    59,    59,
      36,    10,    33,    36,    10,    78,    60,    66,    76,    59,
      67,    31,    33
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
#line 58 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 65 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 69 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 78 "BulletParser.y"
    {
			// members must be declared first, then functions, then events
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
			(yyval)->setString((yyvsp[-3])->getStringData().c_str());
			delete (yyvsp[-3]);

			(yyval)->setChild(PT_MemberNode, 0);
			(yyval)->setChild(PT_AffectorNode, 0);
			(yyval)->setChild(PT_FunctionNode, 0);
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 6:
#line 90 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			(yyval)->setChild(PT_MemberNode, 0);
			(yyval)->setChild(PT_AffectorNode, 0);
			(yyval)->setChild(PT_FunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_StateNode, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 101 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
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

  case 8:
#line 124 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
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

  case 9:
#line 147 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
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

  case 10:
#line 170 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
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

  case 11:
#line 193 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
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

  case 12:
#line 228 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GunDefinition, yylineno);
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

  case 13:
#line 266 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 14:
#line 270 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 15:
#line 279 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 16:
#line 283 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 17:
#line 292 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
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
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 20:
#line 314 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 21:
#line 324 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 22:
#line 328 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 23:
#line 335 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 24:
#line 340 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 25:
#line 352 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 356 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 365 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 28:
#line 374 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 29:
#line 378 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 30:
#line 385 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 31:
#line 389 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 32:
#line 396 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 33:
#line 400 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 34:
#line 409 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 35:
#line 413 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 36:
#line 422 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 37:
#line 426 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 38:
#line 430 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 434 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 40:
#line 438 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 41:
#line 442 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 42:
#line 446 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 450 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 44:
#line 457 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 45:
#line 461 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 465 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 47:
#line 469 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 48:
#line 473 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 477 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 50:
#line 481 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 51:
#line 488 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 52:
#line 492 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 53:
#line 499 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 54:
#line 505 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 55:
#line 512 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 56:
#line 522 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 57:
#line 528 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 58:
#line 535 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 59:
#line 545 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 60:
#line 551 "BulletParser.y"
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

  case 61:
#line 571 "BulletParser.y"
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

  case 62:
#line 591 "BulletParser.y"
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

  case 63:
#line 608 "BulletParser.y"
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

  case 64:
#line 625 "BulletParser.y"
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

  case 65:
#line 642 "BulletParser.y"
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

  case 66:
#line 662 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 67:
#line 668 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 68:
#line 678 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 69:
#line 684 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 70:
#line 693 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 71:
#line 699 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 72:
#line 708 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 73:
#line 716 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 74:
#line 724 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 75:
#line 734 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 76:
#line 746 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 750 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 78:
#line 759 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 763 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 80:
#line 771 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 81:
#line 778 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 82:
#line 786 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 790 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 84:
#line 799 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 803 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 86:
#line 812 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 816 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 88:
#line 822 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 89:
#line 831 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 835 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 91:
#line 841 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 92:
#line 847 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 93:
#line 853 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 94:
#line 862 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 866 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 96:
#line 872 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 97:
#line 881 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 885 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 99:
#line 891 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 100:
#line 897 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 101:
#line 906 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 910 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 103:
#line 915 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 104:
#line 923 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 927 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 931 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 935 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 939 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 109:
#line 946 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 110:
#line 955 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 111:
#line 959 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 112:
#line 966 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 113:
#line 971 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 114:
#line 983 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 115:
#line 991 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 116:
#line 1000 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 117:
#line 1004 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 118:
#line 1011 "BulletParser.y"
    {
			// This only accepts non-negative integers
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 119:
#line 1020 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2594 "bsBulletParser.cpp"

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


#line 1026 "BulletParser.y"


	
	

