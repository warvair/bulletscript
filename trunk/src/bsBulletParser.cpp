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
#define YYLAST   511

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  68
/* YYNRULES -- Number of rules. */
#define YYNRULES  172
/* YYNRULES -- Number of states. */
#define YYNSTATES  362

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
       2,     2,     2,     2,     2,     2,    48,    47,     2,     2,
      36,    37,    45,    43,    38,    44,    39,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    35,
      41,    34,    42,     2,     2,     2,     2,     2,     2,     2,
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
      34,    42,    49,    57,    65,    74,    80,    87,    94,   102,
     104,   107,   109,   112,   118,   120,   123,   128,   130,   133,
     139,   142,   146,   148,   152,   154,   157,   163,   165,   168,
     173,   175,   178,   183,   186,   190,   193,   197,   200,   204,
     207,   211,   213,   216,   218,   221,   223,   226,   228,   231,
     233,   235,   237,   239,   241,   243,   245,   247,   249,   251,
     253,   255,   257,   259,   261,   263,   265,   267,   269,   271,
     273,   275,   277,   279,   281,   283,   285,   287,   289,   292,
     298,   306,   314,   320,   328,   336,   342,   350,   358,   364,
     372,   380,   385,   389,   393,   398,   403,   408,   413,   420,
     426,   432,   439,   446,   453,   460,   465,   474,   480,   486,
     492,   498,   504,   510,   516,   522,   526,   532,   539,   544,
     546,   550,   552,   554,   559,   561,   563,   567,   569,   573,
     575,   579,   583,   585,   589,   593,   597,   601,   603,   607,
     611,   613,   617,   621,   625,   627,   630,   633,   635,   637,
     639,   641,   645,   648,   651,   655,   657,   661,   663,   666,
     668,   670,   672
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      50,     0,    -1,    51,    -1,    52,    -1,    51,    52,    -1,
      53,    -1,    54,    -1,     4,   112,    32,    66,    33,    -1,
       4,   112,    32,    60,    66,    33,    -1,     4,   112,    32,
      56,    66,    33,    -1,     4,   112,    32,    56,    60,    66,
      33,    -1,     4,   112,    32,    55,    66,    33,    -1,     4,
     112,    32,    55,    60,    66,    33,    -1,     4,   112,    32,
      55,    56,    66,    33,    -1,     4,   112,    32,    55,    56,
      60,    66,    33,    -1,     3,   112,    32,    68,    33,    -1,
       3,   112,    32,    64,    68,    33,    -1,     3,   112,    32,
      58,    68,    33,    -1,     3,   112,    32,    58,    64,    68,
      33,    -1,    87,    -1,    55,    87,    -1,    57,    -1,    56,
      57,    -1,   112,    34,     5,   109,    35,    -1,    59,    -1,
      58,    59,    -1,   112,    34,   112,    35,    -1,    61,    -1,
      60,    61,    -1,   112,    34,     6,    62,    70,    -1,    36,
      37,    -1,    36,    63,    37,    -1,   112,    -1,    63,    38,
     112,    -1,    65,    -1,    64,    65,    -1,   112,    34,     8,
      62,    71,    -1,    67,    -1,    66,    67,    -1,   112,    34,
       7,    72,    -1,    69,    -1,    68,    69,    -1,   112,    34,
       7,    73,    -1,    32,    33,    -1,    32,    74,    33,    -1,
      32,    33,    -1,    32,    75,    33,    -1,    32,    33,    -1,
      32,    76,    33,    -1,    32,    33,    -1,    32,    77,    33,
      -1,    78,    -1,    74,    78,    -1,    79,    -1,    75,    79,
      -1,    80,    -1,    76,    80,    -1,    81,    -1,    77,    81,
      -1,    82,    -1,    83,    -1,    87,    -1,    89,    -1,    90,
      -1,    95,    -1,    96,    -1,    99,    -1,    82,    -1,    84,
      -1,    87,    -1,    91,    -1,    94,    -1,    95,    -1,    82,
      -1,    85,    -1,    87,    -1,    92,    -1,    94,    -1,    95,
      -1,    96,    -1,    82,    -1,    86,    -1,    87,    -1,    88,
      -1,    93,    -1,    94,    -1,    95,    -1,    35,    -1,   100,
      35,    -1,    11,    36,   100,    37,    70,    -1,    11,    36,
     100,    37,    70,    12,    70,    -1,    11,    36,   100,    37,
      70,    12,    83,    -1,    11,    36,   100,    37,    71,    -1,
      11,    36,   100,    37,    71,    12,    71,    -1,    11,    36,
     100,    37,    71,    12,    84,    -1,    11,    36,   100,    37,
      72,    -1,    11,    36,   100,    37,    72,    12,    72,    -1,
      11,    36,   100,    37,    72,    12,    85,    -1,    11,    36,
     100,    37,    73,    -1,    11,    36,   100,    37,    73,    12,
      73,    -1,    11,    36,   100,    37,    73,    12,    86,    -1,
     112,    34,   100,    35,    -1,   112,    25,    35,    -1,   112,
      26,    35,    -1,   112,    27,   100,    35,    -1,   112,    28,
     100,    35,    -1,   112,    29,   100,    35,    -1,   112,    30,
     100,    35,    -1,   112,    39,   112,    34,   100,    35,    -1,
     112,    39,   112,    25,    35,    -1,   112,    39,   112,    26,
      35,    -1,   112,    39,   112,    27,   100,    35,    -1,   112,
      39,   112,    28,   100,    35,    -1,   112,    39,   112,    29,
     100,    35,    -1,   112,    39,   112,    30,   100,    35,    -1,
     113,    34,   100,    35,    -1,   113,    34,    32,   100,    38,
     100,    33,    35,    -1,     9,    36,   100,    37,    70,    -1,
      10,    36,   100,    37,    70,    -1,     9,    36,   100,    37,
      71,    -1,    10,    36,   100,    37,    71,    -1,     9,    36,
     100,    37,    72,    -1,    10,    36,   100,    37,    72,    -1,
       9,    36,   100,    37,    73,    -1,    10,    36,   100,    37,
      73,    -1,    13,   112,    35,    -1,    14,    36,   100,    37,
      35,    -1,   112,   112,   110,    40,    97,    35,    -1,   112,
     112,   110,    35,    -1,    98,    -1,    97,    38,    98,    -1,
     109,    -1,   112,    -1,    15,    36,    37,    35,    -1,   101,
      -1,   102,    -1,   101,    24,   102,    -1,   103,    -1,   102,
      23,   103,    -1,   104,    -1,   103,    21,   104,    -1,   103,
      22,   104,    -1,   105,    -1,   104,    41,   105,    -1,   104,
      42,   105,    -1,   104,    19,   105,    -1,   104,    20,   105,
      -1,   106,    -1,   105,    43,   106,    -1,   105,    44,   106,
      -1,   107,    -1,   106,    45,   107,    -1,   106,    46,   107,
      -1,   106,    47,   107,    -1,   108,    -1,    43,   107,    -1,
      44,   107,    -1,   112,    -1,   113,    -1,   109,    -1,   114,
      -1,    36,   100,    37,    -1,   112,   110,    -1,    36,    37,
      -1,    36,   111,    37,    -1,   100,    -1,   111,    38,   100,
      -1,    18,    -1,    48,   112,    -1,   115,    -1,   116,    -1,
      16,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    59,    59,    66,    70,    79,    83,    90,   101,   112,
     135,   158,   181,   204,   239,   277,   288,   299,   322,   348,
     352,   361,   365,   374,   383,   387,   396,   405,   409,   418,
     428,   432,   439,   444,   456,   460,   469,   480,   484,   493,
     502,   506,   515,   524,   528,   535,   539,   546,   550,   557,
     561,   568,   572,   581,   585,   594,   598,   607,   611,   620,
     624,   628,   632,   636,   640,   644,   648,   655,   659,   663,
     667,   671,   675,   682,   686,   690,   694,   698,   702,   706,
     713,   717,   721,   725,   729,   733,   737,   744,   748,   755,
     761,   768,   778,   784,   791,   801,   807,   814,   824,   830,
     837,   847,   853,   873,   893,   910,   927,   944,   964,   971,
     992,  1013,  1031,  1049,  1067,  1088,  1094,  1104,  1110,  1119,
    1125,  1134,  1140,  1149,  1155,  1164,  1172,  1180,  1190,  1202,
    1206,  1215,  1219,  1227,  1234,  1242,  1246,  1255,  1259,  1268,
    1272,  1278,  1287,  1291,  1297,  1303,  1309,  1318,  1322,  1328,
    1337,  1341,  1347,  1353,  1362,  1366,  1371,  1379,  1383,  1387,
    1391,  1395,  1402,  1411,  1415,  1422,  1427,  1439,  1447,  1456,
    1460,  1467,  1476
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
  "TOKEN_ERROR", "'{'", "'}'", "'='", "';'", "'('", "')'", "','", "'.'",
  "':'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'$'", "$accept",
  "script_file", "definition_list", "definition", "emitter_definition",
  "controller_definition", "member_list", "affector_list",
  "affector_declaration", "emitter_list", "emitter", "function_list",
  "function", "function_arguments", "argument_list", "event_list", "event",
  "emitter_state_list", "emitter_state", "controller_state_list",
  "controller_state", "function_compound_statement",
  "event_compound_statement", "emitter_state_compound_statement",
  "controller_state_compound_statement", "function_statement_list",
  "event_statement_list", "emitter_state_statement_list",
  "controller_state_statement_list", "function_statement",
  "event_statement", "emitter_state_statement",
  "controller_state_statement", "expression_statement",
  "function_conditional_statement", "event_conditional_statement",
  "emitter_state_conditional_statement",
  "controller_state_conditional_statement", "assignment_statement",
  "member_assignment_statement", "property_statement",
  "function_iteration_statement", "event_iteration_statement",
  "emitter_state_iteration_statement",
  "controller_state_iteration_statement", "goto_statement",
  "wait_statement", "fire_statement", "controller_list",
  "controller_entry", "die_statement", "constant_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
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
     285,   286,   123,   125,    61,    59,    40,    41,    44,    46,
      58,    60,    62,    43,    45,    42,    47,    37,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    54,    55,
      55,    56,    56,    57,    58,    58,    59,    60,    60,    61,
      62,    62,    63,    63,    64,    64,    65,    66,    66,    67,
      68,    68,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    75,    76,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    79,
      79,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    82,    82,    83,
      83,    83,    84,    84,    84,    85,    85,    85,    86,    86,
      86,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    94,    95,    96,    96,    97,
      97,    98,    98,    99,   100,   101,   101,   102,   102,   103,
     103,   103,   104,   104,   104,   104,   104,   105,   105,   105,
     106,   106,   106,   106,   107,   107,   107,   108,   108,   108,
     108,   108,   109,   110,   110,   111,   111,   112,   113,   114,
     114,   115,   116
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     5,     6,     6,     7,     1,
       2,     1,     2,     5,     1,     2,     4,     1,     2,     5,
       2,     3,     1,     3,     1,     2,     5,     1,     2,     4,
       1,     2,     4,     2,     3,     2,     3,     2,     3,     2,
       3,     1,     2,     1,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       7,     7,     5,     7,     7,     5,     7,     7,     5,     7,
       7,     4,     3,     3,     4,     4,     4,     4,     6,     5,
       5,     6,     6,     6,     6,     4,     8,     5,     5,     5,
       5,     5,     5,     5,     5,     3,     5,     6,     4,     1,
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
       0,     0,     0,     0,     2,     3,     5,     6,   167,     0,
       0,     1,     4,     0,     0,     0,    24,     0,    34,     0,
      40,     0,     0,     0,    21,     0,    27,     0,    37,    19,
       0,    25,     0,     0,    35,     0,     0,    15,    41,     0,
       0,     0,     0,     0,    20,    22,     0,     0,     0,    28,
       0,     0,     7,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    16,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,     9,     0,     8,     0,     0,
     102,   103,   171,   172,     0,     0,     0,     0,     0,   134,
     135,   137,   139,   142,   147,   150,   154,   159,   157,   158,
     160,   169,   170,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    42,     0,     0,    26,     0,    13,    12,    10,
       0,   155,   156,   168,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   162,
     105,   106,   107,     0,     0,     0,     0,    39,   101,     0,
       0,     0,     0,     0,    49,    87,     0,    57,    80,    81,
      82,    83,    84,    85,    86,     0,   157,    30,     0,    32,
       0,    36,    14,   161,   136,   138,   140,   141,   145,   146,
     143,   144,   148,   149,   151,   152,   153,   163,   165,     0,
      23,     0,    29,     0,     0,     0,    47,     0,    55,    73,
      74,    75,    76,    77,    78,    79,   157,     0,     0,     0,
       0,     0,    50,    58,    88,     0,     0,    31,     0,     0,
       0,     0,    45,     0,    53,    67,    68,    69,    70,    71,
      72,   157,   164,     0,     0,     0,     0,     0,    43,     0,
      51,    59,    60,    61,    62,    63,    64,    65,    66,   158,
       0,     0,     0,    48,    56,     0,     0,     0,     0,   125,
       0,     0,    33,     0,     0,     0,    46,    54,   166,     0,
       0,     0,     0,    44,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,     0,   123,   124,    98,   126,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   133,     0,   115,   121,   122,    95,     0,   129,
     131,   132,     0,   111,   112,   113,   114,   108,   119,   120,
      92,   117,   118,    89,     0,     0,   127,     0,    99,   100,
       0,     0,     0,    96,    97,   130,    93,    94,    90,    91,
       0,   116
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    22,    23,    24,    15,
      16,    25,    26,   114,   168,    17,    18,    27,    28,    19,
      20,   192,   171,   147,   112,   239,   223,   197,   156,   240,
     224,   198,   157,   158,   242,   226,   200,   159,   160,   161,
     244,   245,   228,   202,   162,   163,   164,   205,   328,   329,
     248,   165,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   139,   189,    98,    99,   100,   101,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -221
static const short int yypact[] =
{
      79,     1,     1,    29,    79,  -221,  -221,  -221,  -221,     4,
      11,  -221,  -221,     1,     1,     1,  -221,     1,  -221,   139,
    -221,    90,     1,     1,  -221,     1,  -221,   181,  -221,  -221,
     360,  -221,     1,   191,  -221,   198,    98,  -221,  -221,   114,
     211,     1,     1,   214,  -221,  -221,     1,   218,   116,  -221,
     219,   136,  -221,  -221,   147,    78,   119,    85,    85,    85,
      85,   120,   221,  -221,  -221,   111,    26,   157,   162,   188,
       1,   222,   241,  -221,   251,  -221,   265,  -221,   200,   243,
    -221,  -221,  -221,  -221,    85,    85,    85,     1,   193,   206,
     225,   220,   142,   223,   230,  -221,  -221,  -221,   237,  -221,
    -221,  -221,  -221,   275,   278,   292,     1,   162,   246,   314,
    -221,   276,  -221,    42,   273,  -221,   283,  -221,  -221,  -221,
     281,  -221,  -221,  -221,  -221,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,   123,  -221,
    -221,  -221,  -221,   315,   237,   309,   312,  -221,  -221,   316,
     317,   318,     1,   327,  -221,  -221,   348,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,   332,   443,  -221,   277,  -221,
     362,  -221,  -221,  -221,   225,   220,   142,   142,   223,   223,
     223,   223,   230,   230,  -221,  -221,  -221,  -221,  -221,   301,
    -221,   177,  -221,   333,   334,   338,  -221,   398,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,   270,    85,    85,    85,
     342,    85,  -221,  -221,  -221,    85,     1,  -221,     1,   346,
     357,   363,  -221,   412,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,   306,  -221,    85,   364,   365,   366,   367,  -221,   448,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,   370,
      85,    85,    85,  -221,  -221,   237,   331,   376,   380,  -221,
     381,   410,  -221,    85,    85,    85,  -221,  -221,  -221,    85,
      85,    85,   382,  -221,  -221,   217,   383,   387,   390,   -15,
     157,   157,   157,   397,   408,   414,    85,    85,    85,    85,
      85,   413,   415,   416,   417,   424,   430,   439,    85,   440,
     246,   246,   246,  -221,     1,  -221,  -221,   339,  -221,  -221,
    -221,   441,   445,   450,   451,   452,   273,   273,   273,   309,
     309,   309,  -221,   455,  -221,  -221,  -221,   466,   -32,  -221,
    -221,   237,    -2,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     476,  -221,  -221,   477,    85,     6,  -221,     1,  -221,  -221,
      82,   141,   418,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
     459,  -221
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -221,  -221,  -221,   486,  -221,  -221,  -221,   473,    66,  -221,
     482,   124,     2,   391,  -221,   484,   285,    53,    37,   165,
      87,  -177,  -220,  -210,  -215,  -221,  -221,  -221,  -221,   261,
     279,   304,   347,  -135,   153,   155,   161,   175,   -12,  -221,
    -221,  -221,  -221,  -221,  -221,  -142,  -123,  -176,  -221,   163,
    -221,    -7,  -221,   384,   385,   180,    46,   210,   -78,  -221,
    -101,   253,  -221,    -1,  -154,  -221,  -221,  -221
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,    29,   346,   203,   143,   347,   121,   122,   151,
      44,   199,    21,    30,    21,   247,    36,   195,    39,     8,
     303,    30,    48,   204,    51,   304,    54,    49,   229,    11,
     111,    36,    39,    67,    39,   225,    13,   249,   146,    69,
      48,    51,    54,    14,    49,    51,    54,   230,    49,    54,
      88,   103,   104,   105,   109,   203,   241,   184,   185,   186,
       8,    39,   199,   247,    53,   305,   306,   307,   246,    51,
      54,    54,    49,    54,   204,    43,    47,   120,    50,   167,
      53,   229,     1,     2,    53,   249,   123,    53,   225,    45,
     325,   326,   327,   221,    71,    72,   338,   339,   340,    74,
     230,    82,    83,     8,   241,   144,    38,    45,    53,    53,
     166,    53,   169,    80,   170,    54,   246,   348,    67,    68,
      38,    84,    38,   116,    40,   106,   107,   108,    85,    86,
     356,   188,    65,    87,   201,   353,    82,    83,     8,    82,
      83,     8,   341,   342,   343,   206,    42,    46,    66,    38,
      76,   210,   236,    53,    81,   166,    84,     8,   227,    84,
     187,   129,   130,    85,    86,    70,    85,    86,    87,   231,
      78,    87,    37,   191,   358,   178,   179,   180,   181,   243,
      33,    79,    35,   131,   132,   201,   234,   235,   236,   111,
     206,   153,   237,    82,    83,     8,   206,    62,   113,     8,
     256,   257,   258,   330,   260,   255,   107,   108,   109,     8,
     238,   227,   155,    84,    52,   261,     8,   262,    67,    68,
      85,    86,   231,   115,    63,    87,   268,   243,   124,     8,
     125,    64,     8,    82,    83,     8,     8,     8,   206,     8,
       8,   127,   128,   276,   277,   278,   330,    73,   126,   298,
     108,    75,    77,    84,   110,   117,   291,   292,   293,     8,
      85,    86,   294,   295,   296,    87,   133,   134,   299,     8,
     106,   107,   108,   138,   118,   135,   136,   137,   146,   311,
     312,   313,   314,   315,   119,   149,   150,   151,     8,   152,
     153,   323,    82,    83,     8,    55,    56,    57,    58,    59,
      60,     8,    34,   331,   215,   170,   138,   176,   177,   154,
     140,   155,    84,   141,   217,   218,   172,    34,   173,    85,
      86,   193,   194,   195,    87,   152,   153,   142,    82,    83,
       8,    55,    56,    57,    58,    59,    60,   352,   232,   233,
     215,   191,   138,   182,   183,   196,   331,   155,    84,   148,
     190,   332,   207,   208,   209,    85,    86,   149,   150,   151,
      87,   152,   153,   211,    82,    83,     8,   214,   280,   250,
     251,   219,   220,   221,   252,   152,   153,   259,    82,    83,
       8,   212,   263,   155,    84,    55,    56,    57,    58,    59,
      60,    85,    86,   264,    61,   222,    87,   155,    84,   265,
     269,   270,   271,   272,   275,    85,    86,   193,   194,   195,
      87,   152,   153,   281,    82,    83,     8,   282,   283,   297,
     300,   219,   220,   221,   301,   152,   153,   302,    82,    83,
       8,   253,   308,   155,    84,   284,   285,   286,   287,   288,
     289,    85,    86,   309,   290,   266,    87,   155,    84,   310,
     316,   360,   317,   318,   319,    85,    86,   234,   235,   236,
      87,   320,   153,   237,    82,    83,     8,   321,    55,    56,
      57,    58,    59,    60,   322,   324,   333,   215,   345,   138,
     334,   273,   216,   155,    84,   335,   336,   337,   350,   351,
      12,    85,    86,   344,   361,    41,    87,    31,   145,    32,
     274,   254,   267,   213,   359,   357,   354,   349,   279,   174,
     355,   175
};

static const unsigned short int yycheck[] =
{
       1,     2,    14,    35,   146,   106,    38,    85,    86,    11,
      22,   146,    13,    14,    15,   191,    17,    11,    19,    18,
      35,    22,    23,   146,    25,    40,    27,    25,   170,     0,
      32,    32,    33,     7,    35,   170,    32,   191,    32,    40,
      41,    42,    43,    32,    42,    46,    47,   170,    46,    50,
      57,    58,    59,    60,    61,   197,   191,   135,   136,   137,
      18,    62,   197,   239,    27,   280,   281,   282,   191,    70,
      71,    72,    70,    74,   197,    22,    23,    84,    25,    37,
      43,   223,     3,     4,    47,   239,    87,    50,   223,    23,
     300,   301,   302,    11,    41,    42,   316,   317,   318,    46,
     223,    16,    17,    18,   239,   106,    19,    41,    71,    72,
     111,    74,   113,    35,    32,   116,   239,   332,     7,     8,
      33,    36,    35,    70,    34,     5,     6,     7,    43,    44,
     350,   138,    34,    48,   146,   345,    16,    17,    18,    16,
      17,    18,   319,   320,   321,   146,    22,    23,    34,    62,
      34,   152,    11,   116,    35,   156,    36,    18,   170,    36,
      37,    19,    20,    43,    44,    41,    43,    44,    48,   170,
      34,    48,    33,    32,   351,   129,   130,   131,   132,   191,
      15,    34,    17,    41,    42,   197,     9,    10,    11,    32,
     191,    14,    15,    16,    17,    18,   197,    32,    36,    18,
     207,   208,   209,   304,   211,   206,     6,     7,   215,    18,
      33,   223,    35,    36,    33,   216,    18,   218,     7,     8,
      43,    44,   223,    35,    33,    48,   233,   239,    35,    18,
      24,    33,    18,    16,    17,    18,    18,    18,   239,    18,
      18,    21,    22,   250,   251,   252,   347,    33,    23,    32,
       7,    33,    33,    36,    33,    33,   263,   264,   265,    18,
      43,    44,   269,   270,   271,    48,    43,    44,   275,    18,
       5,     6,     7,    36,    33,    45,    46,    47,    32,   286,
     287,   288,   289,   290,    33,     9,    10,    11,    18,    13,
      14,   298,    16,    17,    18,    25,    26,    27,    28,    29,
      30,    18,    17,   304,    34,    32,    36,   127,   128,    33,
      35,    35,    36,    35,    37,    38,    33,    32,    37,    43,
      44,     9,    10,    11,    48,    13,    14,    35,    16,    17,
      18,    25,    26,    27,    28,    29,    30,   344,    37,    38,
      34,    32,    36,   133,   134,    33,   347,    35,    36,    35,
      35,    12,    36,    36,    36,    43,    44,     9,    10,    11,
      48,    13,    14,    36,    16,    17,    18,    35,    37,    36,
      36,     9,    10,    11,    36,    13,    14,    35,    16,    17,
      18,    33,    36,    35,    36,    25,    26,    27,    28,    29,
      30,    43,    44,    36,    34,    33,    48,    35,    36,    36,
      36,    36,    36,    36,    34,    43,    44,     9,    10,    11,
      48,    13,    14,    37,    16,    17,    18,    37,    37,    37,
      37,     9,    10,    11,    37,    13,    14,    37,    16,    17,
      18,    33,    35,    35,    36,    25,    26,    27,    28,    29,
      30,    43,    44,    35,    34,    33,    48,    35,    36,    35,
      37,    33,    37,    37,    37,    43,    44,     9,    10,    11,
      48,    37,    14,    15,    16,    17,    18,    37,    25,    26,
      27,    28,    29,    30,    35,    35,    35,    34,    12,    36,
      35,    33,    39,    35,    36,    35,    35,    35,    12,    12,
       4,    43,    44,    38,    35,    22,    48,    15,   107,    15,
     239,   197,   223,   156,   351,   350,   345,   332,   255,   125,
     347,   126
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    50,    51,    52,    53,    54,    18,   112,
     112,     0,    52,    32,    32,    58,    59,    64,    65,    68,
      69,   112,    55,    56,    57,    60,    61,    66,    67,    87,
     112,    59,    64,    68,    65,    68,   112,    33,    69,   112,
      34,    56,    60,    66,    87,    57,    60,    66,   112,    61,
      66,   112,    33,    67,   112,    25,    26,    27,    28,    29,
      30,    34,    68,    33,    33,    34,    34,     7,     8,   112,
      60,    66,    66,    33,    66,    33,    34,    33,    34,    34,
      35,    35,    16,    17,    36,    43,    44,    48,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   112,   113,
     114,   115,   116,   100,   100,   100,     5,     6,     7,   100,
      33,    32,    73,    36,    62,    35,    66,    33,    33,    33,
     100,   107,   107,   112,    35,    24,    23,    21,    22,    19,
      20,    41,    42,    43,    44,    45,    46,    47,    36,   110,
      35,    35,    35,   109,   112,    62,    32,    72,    35,     9,
      10,    11,    13,    14,    33,    35,    77,    81,    82,    86,
      87,    88,    93,    94,    95,   100,   112,    37,    63,   112,
      32,    71,    33,    37,   102,   103,   104,   104,   105,   105,
     105,   105,   106,   106,   107,   107,   107,    37,   100,   111,
      35,    32,    70,     9,    10,    11,    33,    76,    80,    82,
      85,    87,    92,    94,    95,    96,   112,    36,    36,    36,
     112,    36,    33,    81,    35,    34,    39,    37,    38,     9,
      10,    11,    33,    75,    79,    82,    84,    87,    91,    94,
      95,   112,    37,    38,     9,    10,    11,    15,    33,    74,
      78,    82,    83,    87,    89,    90,    95,    96,    99,   113,
      36,    36,    36,    33,    80,   112,   100,   100,   100,    35,
     100,   112,   112,    36,    36,    36,    33,    79,   100,    36,
      36,    36,    36,    33,    78,    34,   100,   100,   100,   110,
      37,    37,    37,    37,    25,    26,    27,    28,    29,    30,
      34,   100,   100,   100,   100,   100,   100,    37,    32,   100,
      37,    37,    37,    35,    40,    73,    73,    73,    35,    35,
      35,   100,   100,   100,   100,   100,    37,    37,    37,    37,
      37,    37,    35,   100,    35,    72,    72,    72,    97,    98,
     109,   112,    12,    35,    35,    35,    35,    35,    71,    71,
      71,    70,    70,    70,    38,    12,    35,    38,    73,    86,
      12,    12,   100,    72,    85,    98,    71,    84,    70,    83,
      33,    35
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
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-3])->getStringData().c_str());
			delete (yyvsp[-3]);

			(yyval)->setChild(PT_EmitterMemberNode, 0);
			(yyval)->setChild(PT_EmitterAffectorNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 8:
#line 102 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			(yyval)->setChild(PT_EmitterMemberNode, 0);
			(yyval)->setChild(PT_EmitterAffectorNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 9:
#line 113 "BulletParser.y"
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
				(yyval)->setChild(PT_EmitterAffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterAffectorNode, (yyvsp[-2]));
			}

			(yyval)->setChild(PT_EmitterMemberNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 10:
#line 136 "BulletParser.y"
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
				(yyval)->setChild(PT_EmitterAffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterAffectorNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_EmitterMemberNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 11:
#line 159 "BulletParser.y"
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
				(yyval)->setChild(PT_EmitterMemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterMemberNode, (yyvsp[-2]));
			}
			
			(yyval)->setChild(PT_EmitterAffectorNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 12:
#line 182 "BulletParser.y"
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
				(yyval)->setChild(PT_EmitterMemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterMemberNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_EmitterAffectorNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 13:
#line 205 "BulletParser.y"
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
				(yyval)->setChild(PT_EmitterMemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterMemberNode, (yyvsp[-3]));
			}
			
			// affector list
			if ((yyvsp[-2])->getType() == PT_AffectorDecl)
			{
				// Create a PT_AffectorDeclList and make $5 the child of it.
				YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(PT_EmitterAffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterAffectorNode, (yyvsp[-2]));
			}

			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 14:
#line 240 "BulletParser.y"
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
				(yyval)->setChild(PT_EmitterMemberNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterMemberNode, (yyvsp[-4]));
			}

			// affector list
			if ((yyvsp[-3])->getType() == PT_AffectorDecl)
			{
				// Create a PT_AffectorDeclList and make $5 the child of it.
				YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(PT_EmitterAffectorNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterAffectorNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 15:
#line 278 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-3])->getStringData().c_str());
			delete (yyvsp[-3]);

			(yyval)->setChild(PT_ControllerMemberNode, 0);
			(yyval)->setChild(PT_ControllerEmitterNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, 0);
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 16:
#line 289 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			(yyval)->setChild(PT_ControllerMemberNode, 0);
			(yyval)->setChild(PT_ControllerEmitterNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 17:
#line 300 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			// emitter list
			if ((yyvsp[-2])->getType() == PT_Emitter)
			{
				// Create a PT_EmitterList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_EmitterList, (yyvsp[-2])->getLine());
				newChild->setChild(0, (yyvsp[-2]));
				(yyval)->setChild(PT_ControllerEmitterNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterAffectorNode, (yyvsp[-2]));
			}

			(yyval)->setChild(PT_ControllerMemberNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, 0);
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 18:
#line 323 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			// emitter list
			if ((yyvsp[-3])->getType() == PT_Emitter)
			{
				// Create a PT_EmitterList and make $4 the child of it.
				YYSTYPE newChild = AST->createNode(PT_EmitterList, (yyvsp[-3])->getLine());
				newChild->setChild(0, (yyvsp[-3]));
				(yyval)->setChild(PT_ControllerEmitterNode, newChild);
			}
			else
			{
				(yyval)->setChild(PT_EmitterAffectorNode, (yyvsp[-3]));
			}

			(yyval)->setChild(PT_ControllerMemberNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 19:
#line 349 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 20:
#line 353 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 21:
#line 362 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 22:
#line 366 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 23:
#line 375 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 24:
#line 384 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 25:
#line 388 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 26:
#line 397 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 27:
#line 406 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 28:
#line 410 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 29:
#line 419 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 30:
#line 429 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 31:
#line 433 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 32:
#line 440 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 33:
#line 445 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 34:
#line 457 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 35:
#line 461 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 36:
#line 470 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 37:
#line 481 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 38:
#line 485 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 39:
#line 494 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 503 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 41:
#line 507 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 42:
#line 516 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 43:
#line 525 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 44:
#line 529 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 45:
#line 536 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 46:
#line 540 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 47:
#line 547 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 48:
#line 551 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 49:
#line 558 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 50:
#line 562 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 51:
#line 569 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 52:
#line 573 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 53:
#line 582 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 54:
#line 586 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 55:
#line 595 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 56:
#line 599 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 57:
#line 608 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 58:
#line 612 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 59:
#line 621 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 625 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 61:
#line 629 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 633 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 637 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 641 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 645 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 649 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 656 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 660 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 664 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 668 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 672 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 676 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 683 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 687 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 691 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 695 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 699 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 703 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 707 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 714 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 718 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 722 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 726 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 730 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 734 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 738 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 745 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 88:
#line 749 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 89:
#line 756 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 90:
#line 762 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 91:
#line 769 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 92:
#line 779 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 93:
#line 785 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 94:
#line 792 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 95:
#line 802 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 96:
#line 808 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 97:
#line 815 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 98:
#line 825 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 99:
#line 831 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 100:
#line 838 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 101:
#line 848 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 102:
#line 854 "BulletParser.y"
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

  case 103:
#line 874 "BulletParser.y"
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

  case 104:
#line 894 "BulletParser.y"
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

  case 105:
#line 911 "BulletParser.y"
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

  case 106:
#line 928 "BulletParser.y"
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

  case 107:
#line 945 "BulletParser.y"
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

  case 108:
#line 965 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 109:
#line 972 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			
			// create 'identifier + 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-4])->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 110:
#line 993 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			
			// create 'identifier - 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-4])->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 111:
#line 1014 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier + ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-3]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 112:
#line 1032 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier - ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-3]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 113:
#line 1050 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier * ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_MultiplyStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-3]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 114:
#line 1068 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier / ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_DivideStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-3]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 115:
#line 1089 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 116:
#line 1095 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 117:
#line 1105 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 118:
#line 1111 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 119:
#line 1120 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 120:
#line 1126 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 121:
#line 1135 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 122:
#line 1141 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 123:
#line 1150 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 124:
#line 1156 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 125:
#line 1165 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 126:
#line 1173 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 127:
#line 1181 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 128:
#line 1191 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 129:
#line 1203 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 130:
#line 1207 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 131:
#line 1216 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 132:
#line 1220 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 133:
#line 1228 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 134:
#line 1235 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 135:
#line 1243 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 136:
#line 1247 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 137:
#line 1256 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 138:
#line 1260 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 139:
#line 1269 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 140:
#line 1273 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 141:
#line 1279 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 142:
#line 1288 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 143:
#line 1292 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 144:
#line 1298 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 145:
#line 1304 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 146:
#line 1310 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 147:
#line 1319 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 148:
#line 1323 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 149:
#line 1329 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 150:
#line 1338 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 151:
#line 1342 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 152:
#line 1348 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 153:
#line 1354 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 154:
#line 1363 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 155:
#line 1367 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 156:
#line 1372 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 157:
#line 1380 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 158:
#line 1384 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 159:
#line 1388 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 160:
#line 1392 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 161:
#line 1396 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 162:
#line 1403 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 163:
#line 1412 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 164:
#line 1416 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 165:
#line 1423 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 166:
#line 1428 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 167:
#line 1440 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 168:
#line 1448 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 169:
#line 1457 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 170:
#line 1461 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 171:
#line 1468 "BulletParser.y"
    {
			// This only accepts non-negative integers
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 172:
#line 1477 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3290 "bsBulletParser.cpp"

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


#line 1483 "BulletParser.y"


	
	

