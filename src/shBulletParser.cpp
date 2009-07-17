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
     KEYWORD_BULLET = 258,
     KEYWORD_AREA = 259,
     KEYWORD_SPLINE = 260,
     KEYWORD_STATE = 261,
     KEYWORD_REPEAT = 262,
     KEYWORD_IF = 263,
     KEYWORD_ELSE = 264,
     KEYWORD_GOTO = 265,
     KEYWORD_WAIT = 266,
     KEYWORD_SET = 267,
     KEYWORD_AFFECTORS = 268,
     INTEGER = 269,
     REAL = 270,
     IDENTIFIER = 271,
     SYMBOL_LTE = 272,
     SYMBOL_GTE = 273,
     SYMBOL_EQ = 274,
     SYMBOL_NEQ = 275,
     SYMBOL_LOG_AND = 276,
     SYMBOL_LOG_OR = 277,
     TOKEN_ERROR = 278
   };
#endif
/* Tokens.  */
#define KEYWORD_BULLET 258
#define KEYWORD_AREA 259
#define KEYWORD_SPLINE 260
#define KEYWORD_STATE 261
#define KEYWORD_REPEAT 262
#define KEYWORD_IF 263
#define KEYWORD_ELSE 264
#define KEYWORD_GOTO 265
#define KEYWORD_WAIT 266
#define KEYWORD_SET 267
#define KEYWORD_AFFECTORS 268
#define INTEGER 269
#define REAL 270
#define IDENTIFIER 271
#define SYMBOL_LTE 272
#define SYMBOL_GTE 273
#define SYMBOL_EQ 274
#define SYMBOL_NEQ 275
#define SYMBOL_LOG_AND 276
#define SYMBOL_LOG_OR 277
#define TOKEN_ERROR 278




/* Copy the first part of user declarations.  */
#line 1 "BulletParser.y"


#include <iostream>
#include <stdlib.h> // for Linux
#include "shAbstractSyntaxTree.h"

using namespace Shmuppet;

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
#line 167 "shBulletParser.cpp"

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
#define YYLAST   156

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  34
/* YYNRULES -- Number of rules. */
#define YYNRULES  73
/* YYNRULES -- Number of states. */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      31,    32,    37,    35,    28,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
      33,    30,    34,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    27,     2,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    26,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    19,    25,    36,    45,
      47,    51,    54,    56,    59,    63,    66,    70,    72,    75,
      77,    79,    81,    83,    85,    87,    89,    91,    94,    98,
     104,   110,   115,   119,   123,   127,   136,   143,   145,   147,
     151,   153,   157,   159,   163,   167,   169,   173,   177,   181,
     185,   187,   191,   195,   197,   201,   205,   209,   211,   214,
     217,   219,   221,   223,   227,   230,   233,   237,   239,   243,
     245,   247,   249,   251
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      41,     0,    -1,    42,    -1,    43,    -1,    42,    43,    -1,
       3,    70,    24,    13,    44,    25,    46,    26,    -1,     3,
      70,    24,    46,    26,    -1,     4,    27,    72,    28,    73,
      29,    70,    24,    46,    26,    -1,     5,    27,    72,    29,
      70,    24,    46,    26,    -1,    45,    -1,    44,    28,    45,
      -1,    70,    68,    -1,    47,    -1,    46,    47,    -1,     6,
      70,    48,    -1,    24,    26,    -1,    24,    49,    26,    -1,
      50,    -1,    49,    50,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,    25,
      -1,    58,    25,    -1,     8,    58,    48,    -1,     8,    58,
      48,     9,    48,    -1,     8,    58,    48,     9,    52,    -1,
      70,    30,    58,    25,    -1,     7,    58,    48,    -1,    10,
      70,    25,    -1,    11,    68,    25,    -1,    12,    70,    31,
      58,    28,    58,    32,    25,    -1,    12,    70,    31,    58,
      32,    25,    -1,    59,    -1,    60,    -1,    59,    22,    60,
      -1,    61,    -1,    60,    21,    61,    -1,    62,    -1,    61,
      19,    62,    -1,    61,    20,    62,    -1,    63,    -1,    62,
      33,    63,    -1,    62,    34,    63,    -1,    62,    17,    63,
      -1,    62,    18,    63,    -1,    64,    -1,    63,    35,    64,
      -1,    63,    36,    64,    -1,    65,    -1,    64,    37,    65,
      -1,    64,    38,    65,    -1,    64,    39,    65,    -1,    66,
      -1,    35,    65,    -1,    36,    65,    -1,    70,    -1,    67,
      -1,    71,    -1,    31,    58,    32,    -1,    70,    68,    -1,
      31,    32,    -1,    31,    69,    32,    -1,    58,    -1,    69,
      28,    58,    -1,    16,    -1,    72,    -1,    73,    -1,    14,
      -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    51,    51,    58,    62,    71,    78,    84,    92,   102,
     106,   115,   124,   128,   137,   146,   150,   157,   161,   170,
     174,   178,   182,   186,   190,   194,   201,   205,   212,   218,
     225,   235,   244,   253,   261,   269,   276,   291,   299,   303,
     312,   316,   325,   329,   335,   344,   348,   354,   360,   366,
     375,   379,   385,   394,   398,   404,   410,   419,   423,   428,
     436,   440,   444,   448,   455,   464,   468,   475,   480,   492,
     500,   504,   511,   519
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_BULLET", "KEYWORD_AREA",
  "KEYWORD_SPLINE", "KEYWORD_STATE", "KEYWORD_REPEAT", "KEYWORD_IF",
  "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_SET",
  "KEYWORD_AFFECTORS", "INTEGER", "REAL", "IDENTIFIER", "SYMBOL_LTE",
  "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ", "SYMBOL_LOG_AND",
  "SYMBOL_LOG_OR", "TOKEN_ERROR", "'{'", "';'", "'}'", "'['", "','", "']'",
  "'='", "'('", "')'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "$accept", "script_file", "gun_definition_list", "gun_definition",
  "affector_list", "affector_call", "state_definition_list",
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
     275,   276,   277,   278,   123,    59,   125,    91,    44,    93,
      61,    40,    41,    60,    62,    43,    45,    42,    47,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    44,
      44,    45,    46,    46,    47,    48,    48,    49,    49,    50,
      50,    50,    50,    50,    50,    50,    51,    51,    52,    52,
      52,    53,    54,    55,    56,    57,    57,    58,    59,    59,
      60,    60,    61,    61,    61,    62,    62,    62,    62,    62,
      63,    63,    63,    64,    64,    64,    64,    65,    65,    65,
      66,    66,    66,    66,    67,    68,    68,    69,    69,    70,
      71,    71,    72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     8,     5,    10,     8,     1,
       3,     2,     1,     2,     3,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     5,
       5,     4,     3,     3,     3,     8,     6,     1,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     2,     2,
       1,     1,     1,     3,     2,     2,     3,     1,     3,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     2,     3,    69,     0,     0,
       0,     1,     4,     0,    72,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     9,     0,     6,    13,    73,
       0,     0,     0,    14,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,    26,    15,     0,     0,     0,
       0,    17,    19,    20,    21,    22,    23,    24,    25,     0,
      37,    38,    40,    42,    45,    50,    53,    57,    61,    60,
      62,    70,    71,     0,    10,    65,    67,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    59,    16,
      18,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     5,     0,    66,
       0,     8,    32,    28,    33,    34,     0,    63,    39,    41,
      43,    44,    48,    49,    46,    47,    51,    52,    54,    55,
      56,     0,    68,     0,     0,     0,    31,     7,    29,    30,
       0,     0,     0,    36,     0,    35
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     4,     5,     6,    24,    25,    19,    20,    33,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   106,    77,
      78,    70,    71,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const short int yypact[] =
{
     114,    -5,    11,    42,    36,   114,   -73,   -73,    50,    68,
      68,   -73,   -73,    40,   -73,    32,    57,    -5,    -5,     9,
     -73,    75,    -5,   105,     5,   -73,    70,   -73,   -73,   -73,
     101,   107,     6,   -73,    98,    -5,    12,   -73,    -5,    98,
      80,    80,    -5,    70,    -5,   -73,   -73,    80,    80,    80,
      77,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   -73,   108,
     110,   113,    47,    46,    71,    83,   -73,   -73,   -73,    79,
     -73,   -73,   -73,    13,   -73,   -73,   -73,    24,    70,   111,
      19,   105,   105,   112,   115,   116,   104,   -73,   -73,   -73,
     -73,   -73,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,   -73,   -73,    80,   -73,
      98,   -73,   -73,   129,   -73,   -73,    80,   -73,   113,    47,
      46,    46,    71,    71,    71,    71,    83,    83,   -73,   -73,
     -73,   117,   -73,    23,     0,    44,   -73,   -73,   -73,   -73,
      80,   119,   109,   -73,   120,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -73,   -73,   -73,   134,   -73,   121,   -32,   -19,   -72,   -73,
      93,   -73,    14,   -73,   -73,   -73,   -73,   -73,   -35,   -73,
      54,    56,    29,     1,    25,   -45,   -73,   -73,    -3,   -73,
      33,   -73,   118,   130
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      28,    76,    73,    87,    88,    81,    82,    80,    41,   112,
     113,     7,    86,    40,    41,    17,    42,    43,    44,    17,
      14,    29,     7,    37,    32,    17,    14,    29,     7,    17,
      34,    45,    46,    35,     8,    27,    11,    47,     9,   107,
      84,    48,    49,    47,    75,   111,    17,    48,    49,   137,
      23,    26,   108,    18,    28,    31,   109,   128,   129,   130,
      21,    28,   138,    96,    97,    69,    94,    95,    26,    10,
     131,    79,   140,   132,    13,    83,   141,    85,   133,    98,
      99,   135,    14,    69,    40,    41,    22,    42,    43,    44,
      29,    14,    29,     7,    14,    29,     7,   122,   123,   124,
     125,    36,    45,    89,    17,   142,   100,   101,    47,   105,
      36,    47,    48,    49,    28,    48,    49,     1,     2,     3,
     102,   103,   104,   120,   121,   126,   127,    15,    16,    32,
      38,    39,    92,    91,    93,   110,   117,   114,   134,    12,
     115,   144,   136,    90,   143,   145,   118,   116,   139,   119,
       0,    30,     0,     0,     0,     0,    74
};

static const short int yycheck[] =
{
      19,    36,    34,    48,    49,    40,    41,    39,     8,    81,
      82,    16,    47,     7,     8,     6,    10,    11,    12,     6,
      14,    15,    16,    26,    24,     6,    14,    15,    16,     6,
      25,    25,    26,    28,     1,    26,     0,    31,    27,    26,
      43,    35,    36,    31,    32,    26,     6,    35,    36,    26,
      17,    18,    28,    13,    73,    22,    32,   102,   103,   104,
      28,    80,   134,    17,    18,    32,    19,    20,    35,    27,
     105,    38,    28,   108,    24,    42,    32,    44,   110,    33,
      34,   116,    14,    50,     7,     8,    29,    10,    11,    12,
      15,    14,    15,    16,    14,    15,    16,    96,    97,    98,
      99,    31,    25,    26,     6,   140,    35,    36,    31,    30,
      31,    31,    35,    36,   133,    35,    36,     3,     4,     5,
      37,    38,    39,    94,    95,   100,   101,     9,    10,    24,
      29,    24,    22,    25,    21,    24,    32,    25,     9,     5,
      25,    32,    25,    50,    25,    25,    92,    31,   134,    93,
      -1,    21,    -1,    -1,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    41,    42,    43,    16,    70,    27,
      27,     0,    43,    24,    14,    72,    72,     6,    13,    46,
      47,    28,    29,    70,    44,    45,    70,    26,    47,    15,
      73,    70,    24,    48,    25,    28,    31,    68,    29,    24,
       7,     8,    10,    11,    12,    25,    26,    31,    35,    36,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    70,
      71,    72,    73,    46,    45,    32,    58,    69,    70,    70,
      46,    58,    58,    70,    68,    70,    58,    65,    65,    26,
      50,    25,    22,    21,    19,    20,    17,    18,    33,    34,
      35,    36,    37,    38,    39,    30,    68,    26,    28,    32,
      24,    26,    48,    48,    25,    25,    31,    32,    60,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    65,    65,
      65,    58,    58,    46,     9,    58,    25,    26,    48,    52,
      28,    32,    58,    25,    32,    25
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
#line 52 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 59 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 63 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GunDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 72 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 6:
#line 79 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 85 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AreaGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-7]));
			(yyval)->setChild(3, (yyvsp[-5]));
		;}
    break;

  case 8:
#line 93 "BulletParser.y"
    {	
			(yyval) = AST->createNode(ASTN_SplineGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-5]));
		;}
    break;

  case 9:
#line 103 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 10:
#line 107 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AffectorStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 11:
#line 116 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AffectorCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 12:
#line 125 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 13:
#line 129 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 14:
#line 138 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 15:
#line 147 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 16:
#line 151 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 17:
#line 158 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 18:
#line 162 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 19:
#line 171 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 20:
#line 175 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 21:
#line 179 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 22:
#line 183 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 23:
#line 187 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 191 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 25:
#line 195 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 202 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 27:
#line 206 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 28:
#line 213 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 29:
#line 219 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 30:
#line 226 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 31:
#line 236 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 32:
#line 245 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_RepeatStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 33:
#line 254 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 34:
#line 262 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 35:
#line 270 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 36:
#line 277 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			
			YYSTYPE timeNode = AST->createNode(ASTN_Constant, yylineno);
			timeNode->setFloat(-1.0f);
			(yyval)->setChild(2, timeNode);
		;}
    break;

  case 37:
#line 292 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 38:
#line 300 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 304 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 313 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 41:
#line 317 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 42:
#line 326 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 330 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 336 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 45:
#line 345 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 349 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 355 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 48:
#line 361 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 49:
#line 367 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 376 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 51:
#line 380 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 52:
#line 386 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 53:
#line 395 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 54:
#line 399 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 55:
#line 405 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 56:
#line 411 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 57:
#line 420 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 58:
#line 424 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 59:
#line 429 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 60:
#line 437 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 61:
#line 441 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 445 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 449 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 64:
#line 456 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 65:
#line 465 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 66:
#line 469 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 67:
#line 476 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 68:
#line 481 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(ASTN_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 69:
#line 493 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 70:
#line 501 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 505 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 512 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Constant, yylineno);
			(yyval)->setFloat(atof (yytext));
		;}
    break;

  case 73:
#line 520 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Constant, yylineno);
			(yyval)->setFloat(atof (yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 1883 "shBulletParser.cpp"

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


#line 526 "BulletParser.y"


	
	

