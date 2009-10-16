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
     KEYWORD_UNIT = 258,
     KEYWORD_GUN = 259,
     KEYWORD_ENABLE = 260,
     KEYWORD_DISABLE = 261,
     KEYWORD_EVENT = 262,
     KEYWORD_BULLET = 263,
     KEYWORD_AREA = 264,
     KEYWORD_ARC = 265,
     KEYWORD_SPLINE = 266,
     KEYWORD_LOOP = 267,
     KEYWORD_IF = 268,
     KEYWORD_ELSE = 269,
     KEYWORD_GOTO = 270,
     KEYWORD_WAIT = 271,
     KEYWORD_SET = 272,
     KEYWORD_AFFECTORS = 273,
     KEYWORD_BASE = 274,
     KEYWORD_CENTRE = 275,
     INTEGER = 276,
     REAL = 277,
     IDENTIFIER = 278,
     SYMBOL_LTE = 279,
     SYMBOL_GTE = 280,
     SYMBOL_EQ = 281,
     SYMBOL_NEQ = 282,
     SYMBOL_LOG_AND = 283,
     SYMBOL_LOG_OR = 284,
     TOKEN_ERROR = 285
   };
#endif
/* Tokens.  */
#define KEYWORD_UNIT 258
#define KEYWORD_GUN 259
#define KEYWORD_ENABLE 260
#define KEYWORD_DISABLE 261
#define KEYWORD_EVENT 262
#define KEYWORD_BULLET 263
#define KEYWORD_AREA 264
#define KEYWORD_ARC 265
#define KEYWORD_SPLINE 266
#define KEYWORD_LOOP 267
#define KEYWORD_IF 268
#define KEYWORD_ELSE 269
#define KEYWORD_GOTO 270
#define KEYWORD_WAIT 271
#define KEYWORD_SET 272
#define KEYWORD_AFFECTORS 273
#define KEYWORD_BASE 274
#define KEYWORD_CENTRE 275
#define INTEGER 276
#define REAL 277
#define IDENTIFIER 278
#define SYMBOL_LTE 279
#define SYMBOL_GTE 280
#define SYMBOL_EQ 281
#define SYMBOL_NEQ 282
#define SYMBOL_LOG_AND 283
#define SYMBOL_LOG_OR 284
#define TOKEN_ERROR 285




/* Copy the first part of user declarations.  */
#line 1 "BulletParser.y"


#include <iostream>
#include <stdlib.h> // for Linux
#include "bsAbstractSyntaxTree.h"

using namespace BS_NMSP;

#define YYERROR_VERBOSE
#define YYSTYPE AbstractSyntaxTreeNode*

int yylex (void);

extern char *yytext;
extern int yylineno;

static AbstractSyntaxTree* AST = AbstractSyntaxTree::instancePtr ();

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
#line 181 "bsBulletParser.cpp"

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
#define YYLAST   245

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  35
/* YYNRULES -- Number of rules. */
#define YYNRULES  84
/* YYNRULES -- Number of states. */
#define YYNSTATES  188

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    46,     2,     2,
      38,    39,    44,    42,    35,    43,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
      40,    37,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    33,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    19,    25,    35,    42,
      55,    67,    80,    92,   106,   119,   133,   146,   152,   154,
     158,   161,   163,   166,   168,   171,   174,   177,   181,   183,
     186,   188,   190,   192,   194,   196,   198,   200,   202,   205,
     209,   215,   221,   226,   230,   234,   238,   247,   254,   256,
     258,   262,   264,   268,   270,   274,   278,   280,   284,   288,
     292,   296,   298,   302,   306,   308,   312,   316,   320,   322,
     325,   328,   330,   332,   334,   338,   341,   344,   348,   350,
     354,   356,   358,   360,   362
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      48,     0,    -1,    49,    -1,    50,    -1,    49,    50,    -1,
       8,    78,    31,    18,    51,    32,    54,    33,    -1,     8,
      78,    31,    54,    33,    -1,     8,    78,    31,    53,    18,
      51,    32,    54,    33,    -1,     8,    78,    31,    53,    54,
      33,    -1,     9,    34,    80,    35,    79,    35,    19,    36,
      78,    31,    54,    33,    -1,     9,    34,    35,    79,    35,
      19,    36,    78,    31,    54,    33,    -1,     9,    34,    80,
      35,    79,    35,    20,    36,    78,    31,    54,    33,    -1,
       9,    34,    35,    79,    35,    20,    36,    78,    31,    54,
      33,    -1,     9,    34,    80,    35,    79,    35,    19,    36,
      78,    31,    53,    54,    33,    -1,     9,    34,    35,    79,
      35,    19,    36,    78,    31,    53,    54,    33,    -1,     9,
      34,    80,    35,    79,    35,    20,    36,    78,    31,    53,
      54,    33,    -1,     9,    34,    35,    79,    35,    20,    36,
      78,    31,    53,    54,    33,    -1,    10,    78,    31,    54,
      33,    -1,    52,    -1,    51,    35,    52,    -1,    78,    76,
      -1,    61,    -1,    53,    61,    -1,    55,    -1,    54,    55,
      -1,    78,    56,    -1,    31,    33,    -1,    31,    57,    33,
      -1,    58,    -1,    57,    58,    -1,    59,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      32,    -1,    66,    32,    -1,    13,    66,    56,    -1,    13,
      66,    56,    14,    56,    -1,    13,    66,    56,    14,    60,
      -1,    78,    37,    66,    32,    -1,    12,    66,    56,    -1,
      15,    78,    32,    -1,    16,    76,    32,    -1,    17,    78,
      38,    66,    35,    66,    39,    32,    -1,    17,    78,    38,
      66,    39,    32,    -1,    67,    -1,    68,    -1,    67,    29,
      68,    -1,    69,    -1,    68,    28,    69,    -1,    70,    -1,
      69,    26,    70,    -1,    69,    27,    70,    -1,    71,    -1,
      70,    40,    71,    -1,    70,    41,    71,    -1,    70,    24,
      71,    -1,    70,    25,    71,    -1,    72,    -1,    71,    42,
      72,    -1,    71,    43,    72,    -1,    73,    -1,    72,    44,
      73,    -1,    72,    45,    73,    -1,    72,    46,    73,    -1,
      74,    -1,    42,    73,    -1,    43,    73,    -1,    78,    -1,
      75,    -1,    79,    -1,    38,    66,    39,    -1,    78,    76,
      -1,    38,    39,    -1,    38,    77,    39,    -1,    66,    -1,
      77,    35,    66,    -1,    23,    -1,    80,    -1,    81,    -1,
      21,    -1,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    58,    58,    65,    69,    78,    85,    91,   110,   128,
     139,   152,   163,   176,   199,   224,   247,   272,   281,   285,
     294,   303,   307,   316,   320,   329,   338,   342,   349,   353,
     362,   366,   370,   374,   378,   382,   386,   393,   397,   404,
     410,   417,   427,   436,   445,   453,   461,   468,   483,   491,
     495,   504,   508,   517,   521,   527,   536,   540,   546,   552,
     558,   567,   571,   577,   586,   590,   596,   602,   611,   615,
     620,   628,   632,   636,   640,   647,   656,   660,   667,   672,
     684,   692,   696,   703,   711
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_UNIT", "KEYWORD_GUN",
  "KEYWORD_ENABLE", "KEYWORD_DISABLE", "KEYWORD_EVENT", "KEYWORD_BULLET",
  "KEYWORD_AREA", "KEYWORD_ARC", "KEYWORD_SPLINE", "KEYWORD_LOOP",
  "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT",
  "KEYWORD_SET", "KEYWORD_AFFECTORS", "KEYWORD_BASE", "KEYWORD_CENTRE",
  "INTEGER", "REAL", "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ",
  "SYMBOL_NEQ", "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "TOKEN_ERROR", "'{'",
  "';'", "'}'", "'['", "','", "']'", "'='", "'('", "')'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "$accept", "script_file",
  "gun_definition_list", "gun_definition", "affector_list",
  "affector_call", "member_list", "state_definition_list",
  "state_definition", "compound_statement", "statement_list", "statement",
  "expression_statement", "conditional_statement", "assignment_statement",
  "iteration_statement", "jump_statement", "wait_statement",
  "set_statement", "constant_expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", "function_call", "function_call_arguments",
  "argument_expression_list", "identifier", "constant", "constant_integer",
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
     285,   123,    59,   125,    91,    44,    93,    61,    40,    41,
      60,    62,    43,    45,    42,    47,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    51,    51,
      52,    53,    53,    54,    54,    55,    56,    56,    57,    57,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    60,
      60,    60,    61,    62,    63,    64,    65,    65,    66,    67,
      67,    68,    68,    69,    69,    69,    70,    70,    70,    70,
      70,    71,    71,    71,    72,    72,    72,    72,    73,    73,
      73,    74,    74,    74,    74,    75,    76,    76,    77,    77,
      78,    79,    79,    80,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     8,     5,     9,     6,    12,
      11,    12,    11,    13,    12,    13,    12,     5,     1,     3,
       2,     1,     2,     1,     2,     2,     2,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       5,     5,     4,     3,     3,     3,     8,     6,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     1,     1,     1,     3,     2,     2,     3,     1,     3,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     2,     3,    80,     0,     0,
       0,     1,     4,     0,    83,     0,     0,     0,     0,     0,
       0,    23,    21,     0,    84,     0,    81,    82,     0,     0,
       0,     0,    18,     0,     0,     0,    22,     6,    24,     0,
       0,    25,     0,     0,    17,     0,     0,     0,    20,     0,
       8,     0,     0,     0,     0,     0,    37,    26,     0,     0,
       0,     0,    28,    30,    31,    32,    33,    34,    35,    36,
       0,    48,    49,    51,    53,    56,    61,    64,    68,    72,
      71,    73,     0,    71,     0,     0,     0,     0,    19,    76,
      78,     0,     0,     0,     0,     0,     0,     0,     0,    69,
      70,    27,    29,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,    42,     0,
       0,     0,     0,     5,     0,    77,     0,    43,    39,    44,
      45,     0,    74,    50,    52,    54,    55,    59,    60,    57,
      58,    62,    63,    65,    66,    67,     0,     0,     0,     0,
      79,     7,     0,     0,     0,     0,     0,     0,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,    10,     0,    12,     0,     0,     0,     0,     0,    14,
      16,     0,     9,     0,    11,    46,    13,    15
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     4,     5,     6,    31,    32,    19,    20,    21,    41,
      61,    62,    63,    64,    22,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,   117,
      91,    83,    81,    26,    27
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -91
static const short int yypact[] =
{
     100,    -2,     5,    -2,    68,   100,   -91,   -91,    39,    15,
      56,   -91,   -91,    23,   -91,   172,    -5,    -2,    -2,    30,
     -22,   -91,   -91,   113,   -91,    16,   -91,   -91,   172,    14,
      70,    53,   -91,    67,    -2,    51,   -91,   -91,   -91,    60,
      57,   -91,   109,    82,   -91,    -2,    -2,   -16,   -91,   120,
     -91,    57,    57,    -2,    67,    -2,   -91,   -91,    57,    57,
      57,    99,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,
     111,   127,   123,   178,    18,   174,   177,   -91,   -91,   -91,
     187,   -91,   149,    67,   148,   150,   207,    73,   -91,   -91,
     -91,    32,    -2,    70,    70,   159,   164,   162,   163,   -91,
     -91,   -91,   -91,   -91,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,   -91,   -91,    -2,
      -2,   152,   171,   -91,    57,   -91,    90,   -91,   195,   -91,
     -91,    57,   -91,   123,   178,    18,    18,   174,   174,   174,
     174,   177,   177,   -91,   -91,   -91,   188,   201,    -2,    -2,
     -91,   -91,     1,    55,    -2,    -2,   202,   203,   -91,   -91,
      57,   204,    -2,   101,    -2,   107,    -2,    -2,   196,   -91,
     112,   -91,   126,   -91,    -2,   134,    -2,   145,   205,   -91,
     -91,   154,   -91,   156,   -91,   -91,   -91,   -91
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -91,   -91,   -91,   233,   206,   193,   -28,    44,    20,   -90,
     -91,   180,   -91,    91,    -4,   -91,   -91,   -91,   -91,   -27,
     -91,   138,   139,   122,   104,   118,   -50,   -91,   -91,   -25,
     -91,    -1,    41,   236,   -91
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       8,     7,    10,   127,   128,    14,    24,     7,    48,    99,
     100,    37,    23,    82,    52,    36,    30,    33,    23,    30,
      90,     7,    58,    89,    93,    94,    59,    60,    30,    96,
      28,    98,    39,    33,    30,    65,    14,     7,    80,     9,
      38,    18,   108,   109,    30,    33,     7,    44,    34,    38,
      15,    42,    95,     7,    97,    38,    25,    65,   110,   111,
      80,    29,   158,    35,   143,   144,   145,   124,    11,    43,
      13,   125,    51,    52,     7,    53,    54,    55,    14,    24,
       7,    14,    24,     7,    50,    45,    30,    17,    46,    87,
     160,    30,    56,    57,   161,    58,     7,   150,    58,    59,
      60,    39,    59,    60,   153,    47,   123,    38,     1,     2,
       3,    51,    52,     7,    53,    54,    55,    86,   146,   147,
      14,    24,     7,   151,     7,    30,   162,   164,    84,    85,
       7,    56,   101,   168,   171,     7,   126,    58,   174,   176,
     173,    59,    60,   103,    39,   179,    38,   156,   157,     7,
      40,   105,    92,    23,    23,    46,   104,     7,    36,   180,
      36,    23,    30,    23,    30,    23,    23,   182,     7,    30,
      36,    30,    36,    23,    30,    23,    30,     7,   184,     7,
      30,   118,    30,    38,   119,    38,   120,   186,   148,   187,
      38,   129,    38,    14,    24,    38,   130,    38,   163,   165,
     131,    38,   132,    38,   106,   107,   170,   149,   172,   152,
     175,   177,   137,   138,   139,   140,   112,   113,   181,   154,
     183,   114,   115,   116,    40,    47,   121,   122,   135,   136,
     141,   142,   155,   166,   167,   178,   169,   185,    12,    88,
      49,   102,   133,   159,   134,    16
};

static const unsigned char yycheck[] =
{
       1,    23,     3,    93,    94,    21,    22,    23,    33,    59,
      60,    33,    13,    40,    13,    19,    17,    18,    19,    20,
      47,    23,    38,    39,    51,    52,    42,    43,    29,    54,
      35,    58,    31,    34,    35,    39,    21,    23,    39,    34,
      20,    18,    24,    25,    45,    46,    23,    33,    18,    29,
      35,    35,    53,    23,    55,    35,    15,    61,    40,    41,
      61,    17,   152,    19,   114,   115,   116,    35,     0,    28,
      31,    39,    12,    13,    23,    15,    16,    17,    21,    22,
      23,    21,    22,    23,    33,    32,    87,    31,    35,    45,
      35,    92,    32,    33,    39,    38,    23,   124,    38,    42,
      43,    31,    42,    43,   131,    38,    33,    87,     8,     9,
      10,    12,    13,    23,    15,    16,    17,    35,   119,   120,
      21,    22,    23,    33,    23,   126,   154,   155,    19,    20,
      23,    32,    33,   160,    33,    23,    92,    38,   166,   167,
      33,    42,    43,    32,    31,    33,   126,   148,   149,    23,
      37,    28,    32,   154,   155,    35,    29,    23,   162,    33,
     164,   162,   163,   164,   165,   166,   167,    33,    23,   170,
     174,   172,   176,   174,   175,   176,   177,    23,    33,    23,
     181,    32,   183,   163,    36,   165,    36,    33,    36,    33,
     170,    32,   172,    21,    22,   175,    32,   177,   154,   155,
      38,   181,    39,   183,    26,    27,   162,    36,   164,    14,
     166,   167,   108,   109,   110,   111,    42,    43,   174,    31,
     176,    44,    45,    46,    37,    38,    19,    20,   106,   107,
     112,   113,    31,    31,    31,    39,    32,    32,     5,    46,
      34,    61,   104,   152,   105,     9
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     8,     9,    10,    48,    49,    50,    23,    78,    34,
      78,     0,    50,    31,    21,    35,    80,    31,    18,    53,
      54,    55,    61,    78,    22,    79,    80,    81,    35,    54,
      78,    51,    52,    78,    18,    54,    61,    33,    55,    31,
      37,    56,    35,    79,    33,    32,    35,    38,    76,    51,
      33,    12,    13,    15,    16,    17,    32,    33,    38,    42,
      43,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      78,    79,    66,    78,    19,    20,    35,    54,    52,    39,
      66,    77,    32,    66,    66,    78,    76,    78,    66,    73,
      73,    33,    58,    32,    29,    28,    26,    27,    24,    25,
      40,    41,    42,    43,    44,    45,    46,    76,    32,    36,
      36,    19,    20,    33,    35,    39,    54,    56,    56,    32,
      32,    38,    39,    68,    69,    70,    70,    71,    71,    71,
      71,    72,    72,    73,    73,    73,    78,    78,    36,    36,
      66,    33,    14,    66,    31,    31,    78,    78,    56,    60,
      35,    39,    53,    54,    53,    54,    31,    31,    66,    32,
      54,    33,    54,    33,    53,    54,    53,    54,    39,    33,
      33,    54,    33,    54,    33,    32,    33,    33
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
#line 59 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 66 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 70 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GunDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 79 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 6:
#line 86 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 92 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-3]));
			
			if ((yyvsp[-5])->getType() == ASTN_AssignStatement)
			{
				// Create a ASTN_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(ASTN_MemberList, (yyvsp[-5])->getLine());
				newChild->setChild(0, (yyvsp[-5]));
				(yyval)->setChild(3, newChild);
			}
			else
			{
				(yyval)->setChild(3, (yyvsp[-5]));
			}
		;}
    break;

  case 8:
#line 111 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));

			if ((yyvsp[-2])->getType() == ASTN_AssignStatement)
			{
				// Create a ASTN_MemberList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(ASTN_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(3, newChild);
			}
			else
			{
				(yyval)->setChild(3, (yyvsp[-2]));
			}
		;}
    break;

  case 9:
#line 129 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-9]));
			(yyval)->setChild(3, (yyvsp[-7]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Base);
			(yyval)->setChild(4, originNode);
		;}
    break;

  case 10:
#line 140 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
			YYSTYPE sideNode = AST->createNode(ASTN_Constant, yylineno);
			sideNode->setFloat(-1.0f); // negative number means adaptive circle
			(yyval)->setChild(2, sideNode);
			(yyval)->setChild(3, (yyvsp[-7]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Base);
			(yyval)->setChild(4, originNode);
		;}
    break;

  case 11:
#line 153 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-9]));
			(yyval)->setChild(3, (yyvsp[-7]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Centre);
			(yyval)->setChild(4, originNode);
		;}
    break;

  case 12:
#line 164 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
			YYSTYPE sideNode = AST->createNode(ASTN_Constant, yylineno);
			sideNode->setFloat(-1.0f); // negative number means adaptive circle
			(yyval)->setChild(2, sideNode);
			(yyval)->setChild(3, (yyvsp[-7]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Centre);
			(yyval)->setChild(4, originNode);
		;}
    break;

  case 13:
#line 177 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-10]));
			(yyval)->setChild(3, (yyvsp[-8]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Base);
			(yyval)->setChild(4, originNode);
			
			if ((yyvsp[-2])->getType() == ASTN_AssignStatement)
			{
				// Create a ASTN_MemberList and make $11 the child of it.
				YYSTYPE newChild = AST->createNode(ASTN_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(5, newChild);
			}
			else
			{
				(yyval)->setChild(5, (yyvsp[-2]));
			}
		;}
    break;

  case 14:
#line 200 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			YYSTYPE sideNode = AST->createNode(ASTN_Constant, yylineno);
			sideNode->setFloat(-1.0f); // negative number means adaptive circle
			(yyval)->setChild(2, sideNode);
			(yyval)->setChild(3, (yyvsp[-8]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Base);
			(yyval)->setChild(4, originNode);

			if ((yyvsp[-2])->getType() == ASTN_AssignStatement)
			{
				// Create a ASTN_MemberList and make $10 the child of it.
				YYSTYPE newChild = AST->createNode(ASTN_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(5, newChild);
			}
			else
			{
				(yyval)->setChild(5, (yyvsp[-2]));
			}
		;}
    break;

  case 15:
#line 225 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-10]));
			(yyval)->setChild(3, (yyvsp[-8]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Centre);
			(yyval)->setChild(4, originNode);

			if ((yyvsp[-2])->getType() == ASTN_AssignStatement)
			{
				// Create a ASTN_MemberList and make $11 the child of it.
				YYSTYPE newChild = AST->createNode(ASTN_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(5, newChild);
			}
			else
			{
				(yyval)->setChild(5, (yyvsp[-2]));
			}
		;}
    break;

  case 16:
#line 248 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			YYSTYPE sideNode = AST->createNode(ASTN_Constant, yylineno);
			sideNode->setFloat(-1.0f); // negative number means adaptive circle
			(yyval)->setChild(2, sideNode);
			(yyval)->setChild(3, (yyvsp[-8]));
			YYSTYPE originNode = AST->createNode(ASTN_Constant, yylineno);
			originNode->setFloat(AO_Centre);
			(yyval)->setChild(4, originNode);
		
			if ((yyvsp[-2])->getType() == ASTN_AssignStatement)
			{
				// Create a ASTN_MemberList and make $10 the child of it.
				YYSTYPE newChild = AST->createNode(ASTN_MemberList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(5, newChild);
			}
			else
			{
				(yyval)->setChild(5, (yyvsp[-2]));
			}
		;}
    break;

  case 17:
#line 273 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_ArcGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 18:
#line 282 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 19:
#line 286 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AffectorStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 20:
#line 295 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AffectorCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 21:
#line 304 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 22:
#line 308 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 23:
#line 317 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 321 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 330 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 26:
#line 339 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 27:
#line 343 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 28:
#line 350 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 354 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 363 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 31:
#line 367 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 32:
#line 371 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 33:
#line 375 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 34:
#line 379 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 35:
#line 383 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 387 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 37:
#line 394 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 38:
#line 398 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 39:
#line 405 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 411 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 41:
#line 418 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 42:
#line 428 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 43:
#line 437 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 446 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 45:
#line 454 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 46:
#line 462 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 47:
#line 469 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			
			YYSTYPE timeNode = AST->createNode(ASTN_Constant, yylineno);
			timeNode->setFloat(-1.0f);
			(yyval)->setChild(2, timeNode);
		;}
    break;

  case 48:
#line 484 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 49:
#line 492 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 50:
#line 496 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 505 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 52:
#line 509 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 53:
#line 518 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 54:
#line 522 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 55:
#line 528 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 56:
#line 537 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 57:
#line 541 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 58:
#line 547 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 59:
#line 553 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 60:
#line 559 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 61:
#line 568 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 572 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 578 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 64:
#line 587 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 591 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 66:
#line 597 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 67:
#line 603 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 68:
#line 612 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 616 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 70:
#line 621 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 71:
#line 629 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 633 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 637 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 641 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 75:
#line 648 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 76:
#line 657 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 77:
#line 661 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 78:
#line 668 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 79:
#line 673 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(ASTN_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 80:
#line 685 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 81:
#line 693 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 697 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 704 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Constant, yylineno);
			(yyval)->setFloat(atof(yytext));
		;}
    break;

  case 84:
#line 712 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Constant, yylineno);
			(yyval)->setFloat(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 2161 "bsBulletParser.cpp"

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


#line 718 "BulletParser.y"


	
	

