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
     KEYWORD_REPEAT = 261,
     KEYWORD_IF = 262,
     KEYWORD_ELSE = 263,
     KEYWORD_GOTO = 264,
     KEYWORD_WAIT = 265,
     KEYWORD_SET = 266,
     KEYWORD_AFFECTORS = 267,
     KEYWORD_BASE = 268,
     KEYWORD_CENTRE = 269,
     INTEGER = 270,
     REAL = 271,
     IDENTIFIER = 272,
     SYMBOL_LTE = 273,
     SYMBOL_GTE = 274,
     SYMBOL_EQ = 275,
     SYMBOL_NEQ = 276,
     SYMBOL_LOG_AND = 277,
     SYMBOL_LOG_OR = 278,
     TOKEN_ERROR = 279
   };
#endif
/* Tokens.  */
#define KEYWORD_BULLET 258
#define KEYWORD_AREA 259
#define KEYWORD_SPLINE 260
#define KEYWORD_REPEAT 261
#define KEYWORD_IF 262
#define KEYWORD_ELSE 263
#define KEYWORD_GOTO 264
#define KEYWORD_WAIT 265
#define KEYWORD_SET 266
#define KEYWORD_AFFECTORS 267
#define KEYWORD_BASE 268
#define KEYWORD_CENTRE 269
#define INTEGER 270
#define REAL 271
#define IDENTIFIER 272
#define SYMBOL_LTE 273
#define SYMBOL_GTE 274
#define SYMBOL_EQ 275
#define SYMBOL_NEQ 276
#define SYMBOL_LOG_AND 277
#define SYMBOL_LOG_OR 278
#define TOKEN_ERROR 279




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
#line 169 "shBulletParser.cpp"

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   186

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  34
/* YYNRULES -- Number of rules. */
#define YYNRULES  75
/* YYNRULES -- Number of states. */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    40,     2,     2,
      32,    33,    38,    36,    29,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
      34,    31,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    27,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    19,    25,    38,    50,
      63,    75,    77,    81,    84,    86,    89,    92,    95,    99,
     101,   104,   106,   108,   110,   112,   114,   116,   118,   120,
     123,   127,   133,   139,   144,   148,   152,   156,   165,   172,
     174,   176,   180,   182,   186,   188,   192,   196,   198,   202,
     206,   210,   214,   216,   220,   224,   226,   230,   234,   238,
     240,   243,   246,   248,   250,   252,   256,   259,   262,   266,
     268,   272,   274,   276,   278,   280
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      42,     0,    -1,    43,    -1,    44,    -1,    43,    44,    -1,
       3,    71,    25,    12,    45,    26,    47,    27,    -1,     3,
      71,    25,    47,    27,    -1,     4,    28,    73,    29,    72,
      29,    13,    30,    71,    25,    47,    27,    -1,     4,    28,
      29,    72,    29,    13,    30,    71,    25,    47,    27,    -1,
       4,    28,    73,    29,    72,    29,    14,    30,    71,    25,
      47,    27,    -1,     4,    28,    29,    72,    29,    14,    30,
      71,    25,    47,    27,    -1,    46,    -1,    45,    29,    46,
      -1,    71,    69,    -1,    48,    -1,    47,    48,    -1,    71,
      49,    -1,    25,    27,    -1,    25,    50,    27,    -1,    51,
      -1,    50,    51,    -1,    52,    -1,    53,    -1,    54,    -1,
      55,    -1,    56,    -1,    57,    -1,    58,    -1,    26,    -1,
      59,    26,    -1,     7,    59,    49,    -1,     7,    59,    49,
       8,    49,    -1,     7,    59,    49,     8,    53,    -1,    71,
      31,    59,    26,    -1,     6,    59,    49,    -1,     9,    71,
      26,    -1,    10,    69,    26,    -1,    11,    71,    32,    59,
      29,    59,    33,    26,    -1,    11,    71,    32,    59,    33,
      26,    -1,    60,    -1,    61,    -1,    60,    23,    61,    -1,
      62,    -1,    61,    22,    62,    -1,    63,    -1,    62,    20,
      63,    -1,    62,    21,    63,    -1,    64,    -1,    63,    34,
      64,    -1,    63,    35,    64,    -1,    63,    18,    64,    -1,
      63,    19,    64,    -1,    65,    -1,    64,    36,    65,    -1,
      64,    37,    65,    -1,    66,    -1,    65,    38,    66,    -1,
      65,    39,    66,    -1,    65,    40,    66,    -1,    67,    -1,
      36,    66,    -1,    37,    66,    -1,    71,    -1,    68,    -1,
      72,    -1,    32,    59,    33,    -1,    71,    69,    -1,    32,
      33,    -1,    32,    70,    33,    -1,    59,    -1,    70,    29,
      59,    -1,    17,    -1,    73,    -1,    74,    -1,    15,    -1,
      16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    52,    52,    59,    63,    72,    79,    85,    96,   109,
     120,   136,   140,   149,   158,   162,   171,   180,   184,   191,
     195,   204,   208,   212,   216,   220,   224,   228,   235,   239,
     246,   252,   259,   269,   278,   287,   295,   303,   310,   325,
     333,   337,   346,   350,   359,   363,   369,   378,   382,   388,
     394,   400,   409,   413,   419,   428,   432,   438,   444,   453,
     457,   462,   470,   474,   478,   482,   489,   498,   502,   509,
     514,   526,   534,   538,   545,   553
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_BULLET", "KEYWORD_AREA",
  "KEYWORD_SPLINE", "KEYWORD_REPEAT", "KEYWORD_IF", "KEYWORD_ELSE",
  "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_SET", "KEYWORD_AFFECTORS",
  "KEYWORD_BASE", "KEYWORD_CENTRE", "INTEGER", "REAL", "IDENTIFIER",
  "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ", "SYMBOL_LOG_AND",
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
     275,   276,   277,   278,   279,   123,    59,   125,    91,    44,
      93,    61,    40,    41,    60,    62,    43,    45,    42,    47,
      37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    44,
      44,    45,    45,    46,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    52,    52,
      53,    53,    53,    54,    55,    56,    57,    58,    58,    59,
      60,    60,    61,    61,    62,    62,    62,    63,    63,    63,
      63,    63,    64,    64,    64,    65,    65,    65,    65,    66,
      66,    66,    67,    67,    67,    67,    68,    69,    69,    70,
      70,    71,    72,    72,    73,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     8,     5,    12,    11,    12,
      11,     1,     3,     2,     1,     2,     2,     2,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     5,     5,     4,     3,     3,     3,     8,     6,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     1,     1,     3,     2,     2,     3,     1,
       3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,    71,     0,     0,     1,
       4,     0,    74,     0,     0,     0,     0,    14,     0,    75,
       0,    72,    73,     0,     0,    11,     0,     6,    15,     0,
      16,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,    28,    17,     0,     0,     0,     0,    19,    21,
      22,    23,    24,    25,    26,    27,     0,    39,    40,    42,
      44,    47,    52,    55,    59,    63,    62,    64,     0,     0,
       0,     0,    12,    67,    69,     0,    62,     0,     0,     0,
       0,     0,     0,    60,    61,    18,    20,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,     0,     5,     0,    68,
      34,    30,    35,    36,     0,    65,    41,    43,    45,    46,
      50,    51,    48,    49,    53,    54,    56,    57,    58,     0,
       0,     0,     0,     0,    70,     0,     0,    33,     0,     0,
       0,     0,    31,    32,     0,     0,     0,     0,     0,     0,
       0,    38,     8,    10,     0,     0,     0,     7,     9,    37
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     3,     4,     5,    24,    25,    16,    17,    30,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   102,    75,
      76,    67,    21,    22
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const short int yypact[] =
{
      68,     1,    70,    48,    68,   -72,   -72,    76,    -3,   -72,
     -72,    33,   -72,    38,    44,     1,     0,   -72,    83,   -72,
      75,   -72,   -72,    38,    65,   -72,    94,   -72,   -72,    73,
     -72,    79,    98,     1,     1,    19,   -72,     5,     5,     1,
      94,     1,   -72,   -72,     5,     5,     5,   149,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   102,   106,   108,    66,
      25,    60,   -15,   -72,   -72,   -72,    87,   -72,   105,   109,
     107,     2,   -72,   -72,   -72,    36,    94,    83,    83,   110,
     114,   111,   116,   -72,   -72,   -72,   -72,   -72,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,   -72,     1,     1,   120,   121,   -72,     5,   -72,
     -72,   136,   -72,   -72,     5,   -72,   108,    66,    25,    25,
      60,    60,    60,    60,   -15,   -15,   -72,   -72,   -72,   126,
     132,   137,     1,     1,   -72,     6,    45,   -72,     1,     1,
     138,   142,   -72,   -72,     5,   135,    22,    30,     1,     1,
     139,   -72,   -72,   -72,    49,    50,   143,   -72,   -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -72,   -72,   -72,   164,   -72,   140,   -32,   -13,   -71,   -72,
     123,   -72,    42,   -72,   -72,   -72,   -72,   -72,   -33,   -72,
      85,    82,    32,    20,    28,   -37,   -72,   -72,   -10,   -72,
      -1,    72,   170,   -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       7,    71,    74,    28,    77,    78,   110,   111,    83,    84,
      18,    82,    12,    38,    26,    18,    36,     6,     6,     6,
      12,    19,     6,    98,    99,   100,    13,    27,    66,   107,
      80,    29,    18,    26,    12,    19,     6,    44,    79,     6,
      81,    45,    46,    92,    93,    15,    66,     6,     9,   152,
       6,    44,    73,    12,    19,    45,    46,   153,    28,    94,
      95,   126,   127,   128,   142,   108,     6,     6,   129,   109,
      18,     1,     2,    23,   144,   134,   157,   158,   145,    37,
      38,   136,    39,    40,    41,    20,    90,    91,    12,    19,
       6,    33,    68,    69,    34,    32,    96,    97,     8,    42,
      43,    11,   130,   131,    31,    44,   146,   147,    29,    45,
      46,   150,   120,   121,   122,   123,   154,   155,   101,    35,
     105,   106,   118,   119,   124,   125,    35,    70,    87,    88,
      89,   140,   141,    28,    28,   103,   112,    18,    18,   104,
     113,    28,    28,   114,   135,    18,    18,    18,    18,   115,
     132,   133,   137,    18,    18,    37,    38,   138,    39,    40,
      41,   151,   139,   148,    12,    19,     6,   149,    10,   159,
      86,   117,   156,   116,    72,    42,    85,   143,    14,     0,
       0,    44,     0,     0,     0,    45,    46
};

static const short int yycheck[] =
{
       1,    33,    35,    16,    37,    38,    77,    78,    45,    46,
      11,    44,    15,     7,    15,    16,    26,    17,    17,    17,
      15,    16,    17,    38,    39,    40,    29,    27,    29,    27,
      40,    25,    33,    34,    15,    16,    17,    32,    39,    17,
      41,    36,    37,    18,    19,    12,    47,    17,     0,    27,
      17,    32,    33,    15,    16,    36,    37,    27,    71,    34,
      35,    98,    99,   100,   135,    29,    17,    17,   101,    33,
      71,     3,     4,    29,    29,   108,    27,    27,    33,     6,
       7,   114,     9,    10,    11,    13,    20,    21,    15,    16,
      17,    26,    13,    14,    29,    23,    36,    37,    28,    26,
      27,    25,   103,   104,    29,    32,   138,   139,    25,    36,
      37,   144,    92,    93,    94,    95,   148,   149,    31,    32,
      13,    14,    90,    91,    96,    97,    32,    29,    26,    23,
      22,   132,   133,   146,   147,    30,    26,   138,   139,    30,
      26,   154,   155,    32,     8,   146,   147,   148,   149,    33,
      30,    30,    26,   154,   155,     6,     7,    25,     9,    10,
      11,    26,    25,    25,    15,    16,    17,    25,     4,    26,
      47,    89,    33,    88,    34,    26,    27,   135,     8,    -1,
      -1,    32,    -1,    -1,    -1,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    42,    43,    44,    17,    71,    28,     0,
      44,    25,    15,    29,    73,    12,    47,    48,    71,    16,
      72,    73,    74,    29,    45,    46,    71,    27,    48,    25,
      49,    29,    72,    26,    29,    32,    69,     6,     7,     9,
      10,    11,    26,    27,    32,    36,    37,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    71,    72,    13,    14,
      29,    47,    46,    33,    59,    70,    71,    59,    59,    71,
      69,    71,    59,    66,    66,    27,    51,    26,    23,    22,
      20,    21,    18,    19,    34,    35,    36,    37,    38,    39,
      40,    31,    69,    30,    30,    13,    14,    27,    29,    33,
      49,    49,    26,    26,    32,    33,    61,    62,    63,    63,
      64,    64,    64,    64,    65,    65,    66,    66,    66,    59,
      71,    71,    30,    30,    59,     8,    59,    26,    25,    25,
      71,    71,    49,    53,    29,    33,    47,    47,    25,    25,
      59,    26,    27,    27,    47,    47,    33,    27,    27,    26
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
#line 53 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 60 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 64 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GunDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 73 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 6:
#line 80 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_BulletGunDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 86 "BulletParser.y"
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

  case 8:
#line 97 "BulletParser.y"
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

  case 9:
#line 110 "BulletParser.y"
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

  case 10:
#line 121 "BulletParser.y"
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

  case 11:
#line 137 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 12:
#line 141 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AffectorStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 13:
#line 150 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AffectorCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 14:
#line 159 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 15:
#line 163 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 16:
#line 172 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 17:
#line 181 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 18:
#line 185 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 19:
#line 192 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 20:
#line 196 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 21:
#line 205 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 22:
#line 209 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 23:
#line 213 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 217 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 25:
#line 221 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 225 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 27:
#line 229 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 28:
#line 236 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 29:
#line 240 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 30:
#line 247 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 31:
#line 253 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 32:
#line 260 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 33:
#line 270 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 34:
#line 279 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_RepeatStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 35:
#line 288 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 36:
#line 296 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 37:
#line 304 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 38:
#line 311 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			
			YYSTYPE timeNode = AST->createNode(ASTN_Constant, yylineno);
			timeNode->setFloat(-1.0f);
			(yyval)->setChild(2, timeNode);
		;}
    break;

  case 39:
#line 326 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 40:
#line 334 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 41:
#line 338 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 42:
#line 347 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 351 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 360 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 45:
#line 364 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 46:
#line 370 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 379 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 48:
#line 383 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 49:
#line 389 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 395 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 401 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 52:
#line 410 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 53:
#line 414 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 54:
#line 420 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 55:
#line 429 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 56:
#line 433 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 57:
#line 439 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 58:
#line 445 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 59:
#line 454 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 458 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 61:
#line 463 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 62:
#line 471 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 475 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 479 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 483 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 66:
#line 490 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 67:
#line 499 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 68:
#line 503 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 69:
#line 510 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 70:
#line 515 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(ASTN_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 71:
#line 527 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 72:
#line 535 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 539 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 546 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Constant, yylineno);
			(yyval)->setFloat(atof(yytext));
		;}
    break;

  case 75:
#line 554 "BulletParser.y"
    {
			(yyval) = AST->createNode(ASTN_Constant, yylineno);
			(yyval)->setFloat(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 1937 "shBulletParser.cpp"

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


#line 560 "BulletParser.y"


	
	

