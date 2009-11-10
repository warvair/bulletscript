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
#define YYLAST   583

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  69
/* YYNRULES -- Number of rules. */
#define YYNRULES  187
/* YYNRULES -- Number of states. */
#define YYNSTATES  408

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
     104,   107,   109,   112,   118,   120,   123,   129,   134,   136,
     139,   145,   148,   152,   154,   158,   160,   163,   169,   171,
     174,   179,   181,   184,   189,   192,   196,   199,   203,   206,
     210,   213,   217,   219,   222,   224,   227,   229,   232,   234,
     237,   239,   241,   243,   245,   247,   249,   251,   253,   255,
     257,   259,   261,   263,   265,   267,   269,   271,   273,   275,
     277,   279,   281,   283,   285,   287,   289,   291,   293,   295,
     297,   299,   301,   303,   306,   312,   320,   328,   334,   342,
     350,   356,   364,   372,   378,   386,   394,   399,   403,   407,
     412,   417,   422,   427,   434,   440,   446,   453,   460,   467,
     474,   479,   488,   492,   496,   501,   506,   511,   516,   525,
     534,   543,   552,   558,   564,   570,   576,   582,   588,   594,
     600,   604,   610,   617,   622,   624,   628,   630,   632,   637,
     639,   641,   645,   647,   651,   653,   657,   661,   663,   667,
     671,   675,   679,   681,   685,   689,   691,   695,   699,   703,
     705,   708,   711,   713,   715,   717,   719,   723,   726,   729,
     733,   735,   739,   741,   744,   746,   748,   750
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      50,     0,    -1,    51,    -1,    52,    -1,    51,    52,    -1,
      53,    -1,    54,    -1,     4,   113,    32,    66,    33,    -1,
       4,   113,    32,    60,    66,    33,    -1,     4,   113,    32,
      56,    66,    33,    -1,     4,   113,    32,    56,    60,    66,
      33,    -1,     4,   113,    32,    55,    66,    33,    -1,     4,
     113,    32,    55,    60,    66,    33,    -1,     4,   113,    32,
      55,    56,    66,    33,    -1,     4,   113,    32,    55,    56,
      60,    66,    33,    -1,     3,   113,    32,    68,    33,    -1,
       3,   113,    32,    64,    68,    33,    -1,     3,   113,    32,
      58,    68,    33,    -1,     3,   113,    32,    58,    64,    68,
      33,    -1,    87,    -1,    55,    87,    -1,    57,    -1,    56,
      57,    -1,   113,    34,     5,   110,    35,    -1,    59,    -1,
      58,    59,    -1,   113,    34,   113,   111,    35,    -1,   113,
      34,   113,    35,    -1,    61,    -1,    60,    61,    -1,   113,
      34,     6,    62,    70,    -1,    36,    37,    -1,    36,    63,
      37,    -1,   113,    -1,    63,    38,   113,    -1,    65,    -1,
      64,    65,    -1,   113,    34,     8,    62,    71,    -1,    67,
      -1,    66,    67,    -1,   113,    34,     7,    72,    -1,    69,
      -1,    68,    69,    -1,   113,    34,     7,    73,    -1,    32,
      33,    -1,    32,    74,    33,    -1,    32,    33,    -1,    32,
      75,    33,    -1,    32,    33,    -1,    32,    76,    33,    -1,
      32,    33,    -1,    32,    77,    33,    -1,    78,    -1,    74,
      78,    -1,    79,    -1,    75,    79,    -1,    80,    -1,    76,
      80,    -1,    81,    -1,    77,    81,    -1,    82,    -1,    83,
      -1,    87,    -1,    88,    -1,    90,    -1,    91,    -1,    96,
      -1,    97,    -1,   100,    -1,    82,    -1,    84,    -1,    87,
      -1,    88,    -1,    92,    -1,    95,    -1,    96,    -1,    82,
      -1,    85,    -1,    87,    -1,    88,    -1,    93,    -1,    95,
      -1,    96,    -1,    97,    -1,    82,    -1,    86,    -1,    87,
      -1,    88,    -1,    89,    -1,    94,    -1,    95,    -1,    96,
      -1,    35,    -1,   101,    35,    -1,    11,    36,   101,    37,
      70,    -1,    11,    36,   101,    37,    70,    12,    70,    -1,
      11,    36,   101,    37,    70,    12,    83,    -1,    11,    36,
     101,    37,    71,    -1,    11,    36,   101,    37,    71,    12,
      71,    -1,    11,    36,   101,    37,    71,    12,    84,    -1,
      11,    36,   101,    37,    72,    -1,    11,    36,   101,    37,
      72,    12,    72,    -1,    11,    36,   101,    37,    72,    12,
      85,    -1,    11,    36,   101,    37,    73,    -1,    11,    36,
     101,    37,    73,    12,    73,    -1,    11,    36,   101,    37,
      73,    12,    86,    -1,   113,    34,   101,    35,    -1,   113,
      25,    35,    -1,   113,    26,    35,    -1,   113,    27,   101,
      35,    -1,   113,    28,   101,    35,    -1,   113,    29,   101,
      35,    -1,   113,    30,   101,    35,    -1,   113,    39,   113,
      34,   101,    35,    -1,   113,    39,   113,    25,    35,    -1,
     113,    39,   113,    26,    35,    -1,   113,    39,   113,    27,
     101,    35,    -1,   113,    39,   113,    28,   101,    35,    -1,
     113,    39,   113,    29,   101,    35,    -1,   113,    39,   113,
      30,   101,    35,    -1,   114,    34,   101,    35,    -1,   114,
      34,    32,   101,    38,   101,    33,    35,    -1,   114,    25,
      35,    -1,   114,    26,    35,    -1,   114,    27,   101,    35,
      -1,   114,    28,   101,    35,    -1,   114,    29,   101,    35,
      -1,   114,    30,   101,    35,    -1,   114,    27,    32,   101,
      38,   101,    33,    35,    -1,   114,    28,    32,   101,    38,
     101,    33,    35,    -1,   114,    29,    32,   101,    38,   101,
      33,    35,    -1,   114,    30,    32,   101,    38,   101,    33,
      35,    -1,     9,    36,   101,    37,    70,    -1,    10,    36,
     101,    37,    70,    -1,     9,    36,   101,    37,    71,    -1,
      10,    36,   101,    37,    71,    -1,     9,    36,   101,    37,
      72,    -1,    10,    36,   101,    37,    72,    -1,     9,    36,
     101,    37,    73,    -1,    10,    36,   101,    37,    73,    -1,
      13,   113,    35,    -1,    14,    36,   101,    37,    35,    -1,
     113,   113,   111,    40,    98,    35,    -1,   113,   113,   111,
      35,    -1,    99,    -1,    98,    38,    99,    -1,   110,    -1,
     113,    -1,    15,    36,    37,    35,    -1,   102,    -1,   103,
      -1,   102,    24,   103,    -1,   104,    -1,   103,    23,   104,
      -1,   105,    -1,   104,    21,   105,    -1,   104,    22,   105,
      -1,   106,    -1,   105,    41,   106,    -1,   105,    42,   106,
      -1,   105,    19,   106,    -1,   105,    20,   106,    -1,   107,
      -1,   106,    43,   107,    -1,   106,    44,   107,    -1,   108,
      -1,   107,    45,   108,    -1,   107,    46,   108,    -1,   107,
      47,   108,    -1,   109,    -1,    43,   108,    -1,    44,   108,
      -1,   113,    -1,   114,    -1,   110,    -1,   115,    -1,    36,
     101,    37,    -1,   113,   111,    -1,    36,    37,    -1,    36,
     112,    37,    -1,   101,    -1,   112,    38,   101,    -1,    18,
      -1,    48,   113,    -1,   116,    -1,   117,    -1,    16,    -1,
      17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    59,    59,    66,    70,    79,    83,    90,   101,   112,
     135,   158,   181,   204,   239,   277,   288,   299,   322,   348,
     352,   361,   365,   374,   383,   387,   396,   403,   412,   416,
     425,   435,   439,   446,   451,   463,   467,   476,   487,   491,
     500,   509,   513,   522,   531,   535,   542,   546,   553,   557,
     564,   568,   575,   579,   588,   592,   601,   605,   614,   618,
     627,   631,   635,   639,   643,   647,   651,   655,   659,   666,
     670,   674,   678,   682,   686,   690,   697,   701,   705,   709,
     713,   717,   721,   725,   732,   736,   740,   744,   748,   752,
     756,   760,   767,   771,   778,   784,   791,   801,   807,   814,
     824,   830,   837,   847,   853,   860,   870,   879,   899,   919,
     936,   953,   970,   990,   997,  1018,  1039,  1057,  1075,  1093,
    1114,  1120,  1127,  1147,  1167,  1184,  1201,  1218,  1235,  1253,
    1271,  1289,  1310,  1316,  1325,  1331,  1340,  1346,  1355,  1361,
    1370,  1378,  1386,  1396,  1408,  1412,  1421,  1425,  1433,  1440,
    1448,  1452,  1461,  1465,  1474,  1478,  1484,  1493,  1497,  1503,
    1509,  1515,  1524,  1528,  1534,  1543,  1547,  1553,  1559,  1568,
    1572,  1577,  1585,  1589,  1593,  1597,  1601,  1608,  1617,  1621,
    1628,  1633,  1645,  1653,  1662,  1666,  1673,  1681
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
  "controller_state_conditional_statement", "simple_assignment_statement",
  "extended_assignment_statement", "member_assignment_statement",
  "property_statement", "function_iteration_statement",
  "event_iteration_statement", "emitter_state_iteration_statement",
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
      55,    56,    56,    57,    58,    58,    59,    59,    60,    60,
      61,    62,    62,    63,    63,    64,    64,    65,    66,    66,
      67,    68,    68,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    82,    83,    83,    83,    84,    84,    84,
      85,    85,    85,    86,    86,    86,    87,    88,    88,    88,
      88,    88,    88,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      95,    96,    97,    97,    98,    98,    99,    99,   100,   101,
     102,   102,   103,   103,   104,   104,   104,   105,   105,   105,
     105,   105,   106,   106,   106,   107,   107,   107,   107,   108,
     108,   108,   109,   109,   109,   109,   109,   110,   111,   111,
     112,   112,   113,   114,   115,   115,   116,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     5,     6,     6,     7,     1,
       2,     1,     2,     5,     1,     2,     5,     4,     1,     2,
       5,     2,     3,     1,     3,     1,     2,     5,     1,     2,
       4,     1,     2,     4,     2,     3,     2,     3,     2,     3,
       2,     3,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     7,     7,     5,     7,     7,
       5,     7,     7,     5,     7,     7,     4,     3,     3,     4,
       4,     4,     4,     6,     5,     5,     6,     6,     6,     6,
       4,     8,     3,     3,     4,     4,     4,     4,     8,     8,
       8,     8,     5,     5,     5,     5,     5,     5,     5,     5,
       3,     5,     6,     4,     1,     3,     1,     1,     4,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     1,     1,     1,     3,     2,     2,     3,
       1,     3,     1,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   182,     0,
       0,     1,     4,     0,     0,     0,    24,     0,    35,     0,
      41,     0,     0,     0,    21,     0,    28,     0,    38,    19,
       0,    25,     0,     0,    36,     0,     0,    15,    42,     0,
       0,     0,     0,     0,    20,    22,     0,     0,     0,    29,
       0,     0,     7,    39,     0,     0,     0,    17,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     9,
       0,     8,     0,     0,     0,     0,     0,   186,   187,     0,
       0,     0,     0,     0,   149,   150,   152,   154,   157,   162,
     165,   169,   174,   172,   173,   175,   184,   185,    18,     0,
      43,     0,     0,    27,     0,     0,     0,    13,    12,    10,
       0,     0,     0,     0,    40,     0,   170,   171,   183,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   177,     0,     0,     0,     0,     0,    50,
      92,     0,    58,    84,    85,    86,    87,    88,    89,    90,
      91,     0,   172,    31,     0,    33,     0,    37,   178,   180,
       0,    26,    14,    23,     0,    30,     0,     0,     0,    48,
       0,    56,    76,    77,    78,    79,    80,    81,    82,    83,
     172,   176,   151,   153,   155,   156,   160,   161,   158,   159,
     163,   164,   166,   167,   168,     0,     0,     0,     0,     0,
      51,    59,    93,     0,     0,     0,     0,     0,     0,     0,
       0,    32,     0,     0,     0,     0,    46,     0,    54,    69,
      70,    71,    72,    73,    74,    75,   172,   179,     0,     0,
       0,     0,     0,    44,     0,    52,    60,    61,    62,    63,
      64,    65,    66,    67,    68,   173,     0,     0,     0,    49,
      57,     0,     0,     0,     0,   140,     0,   107,   108,     0,
       0,     0,     0,     0,    34,     0,     0,     0,    47,    55,
     181,     0,     0,     0,     0,    45,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   143,     0,   138,   139,   103,
     141,   114,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,     0,   124,     0,   125,     0,
     126,     0,   127,     0,   120,   136,   137,   100,     0,   144,
     146,   147,     0,   116,   117,   118,   119,   113,   134,   135,
      97,   132,   133,    94,     0,     0,     0,     0,     0,     0,
     142,     0,   104,   105,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   145,    98,    99,    95,    96,     0,     0,
       0,     0,     0,   128,   129,   130,   131,   121
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    22,    23,    24,    15,
      16,    25,    26,   102,   154,    17,    18,    27,    28,    19,
      20,   165,   157,   114,   100,   234,   217,   170,   141,   235,
     218,   171,   142,   143,   237,   220,   173,   144,   145,   146,
     147,   240,   241,   223,   176,   148,   149,   150,   179,   358,
     359,   244,   151,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   133,   160,    93,    94,    95,    96,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -289
static const short int yypact[] =
{
       0,    -8,    -8,    20,     0,  -289,  -289,  -289,  -289,     1,
      15,  -289,  -289,    -8,    -8,    -8,  -289,    -8,  -289,   102,
    -289,    19,    -8,    -8,  -289,    -8,  -289,   125,  -289,  -289,
      43,  -289,    -8,   171,  -289,   174,    51,  -289,  -289,    63,
     160,    -8,    -8,   192,  -289,  -289,    -8,   197,    89,  -289,
     206,   114,  -289,  -289,   120,   170,   216,  -289,  -289,    53,
      83,   113,   121,   208,    -8,   217,   227,  -289,   247,  -289,
     231,  -289,   278,   154,    -8,   121,   134,  -289,  -289,   462,
     462,   462,    -8,   138,   161,   168,   291,   111,   275,   223,
    -289,  -289,  -289,   163,  -289,  -289,  -289,  -289,  -289,   184,
    -289,    73,   164,  -289,   235,   173,   248,  -289,  -289,  -289,
     191,   163,   199,   287,  -289,   249,  -289,  -289,  -289,  -289,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   462,   462,  -289,   169,   252,   254,    -8,   256,  -289,
    -289,   323,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,   259,   531,  -289,   289,  -289,   359,  -289,  -289,  -289,
     305,  -289,  -289,  -289,   373,  -289,   266,   280,   285,  -289,
     409,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
     281,  -289,   168,   291,   111,   111,   275,   275,   275,   275,
     223,   223,  -289,  -289,  -289,   462,   462,   462,   303,   462,
    -289,  -289,  -289,   311,   312,   462,   462,   462,   462,   462,
      -8,  -289,    -8,   288,   318,   319,  -289,   423,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,   546,  -289,   462,   321,
     324,   325,   326,  -289,   459,  -289,  -289,  -289,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,   371,   462,   462,   462,  -289,
    -289,   163,   327,   328,   337,  -289,   341,  -289,  -289,   313,
     344,   346,   350,   421,  -289,   462,   462,   462,  -289,  -289,
    -289,   462,   462,   462,   349,  -289,  -289,   358,   369,   465,
     468,   501,   504,   507,   374,   375,   376,   -29,   113,   113,
     113,   379,  -289,  -289,  -289,  -289,   380,   389,   462,   462,
     462,   462,   462,   391,   392,   393,   394,   398,   401,   408,
    -289,  -289,   462,   419,   462,   425,   462,   426,   462,   427,
     462,   428,   134,   134,   134,  -289,    -8,  -289,  -289,   351,
    -289,  -289,  -289,   429,   430,   437,   452,   453,   164,   164,
     164,   199,   199,   199,  -289,   372,  -289,   451,  -289,   455,
    -289,   458,  -289,   461,  -289,  -289,  -289,   478,    49,  -289,
    -289,   163,    27,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
     479,  -289,  -289,   502,   462,   462,   462,   462,   462,    75,
    -289,    -8,  -289,  -289,   105,   107,   482,   493,   494,   495,
     496,  -289,  -289,  -289,  -289,  -289,  -289,  -289,   497,   499,
     500,   503,   506,  -289,  -289,  -289,  -289,  -289
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -289,  -289,  -289,   526,  -289,  -289,  -289,   509,    34,  -289,
     527,   119,    86,   471,  -289,   538,   250,    92,    56,   132,
      69,  -272,  -288,  -287,  -261,  -289,  -289,  -289,  -289,   320,
     345,   396,   422,  -108,   179,   185,   189,   215,    -5,   -90,
    -289,  -289,  -289,  -289,  -289,  -289,   -98,   -88,  -156,  -289,
     198,  -289,   -25,  -289,   463,   457,   222,   137,   200,   -37,
    -289,   -67,   -61,  -289,    -1,  -145,  -289,  -289,  -289
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   105,     1,     2,   172,   325,   110,   243,    29,
       8,   326,    21,    30,    21,   177,    36,    44,    39,   245,
      11,    30,    48,   175,    51,   178,    54,   327,   328,   329,
      83,    36,    39,    13,    39,   355,   356,   357,   136,    63,
      48,    51,    54,   116,   117,    51,    54,    14,   219,    54,
     368,   369,   370,    40,   115,    39,   236,    45,   224,    99,
      61,    62,   172,    51,    54,    54,   222,    54,   225,   371,
     372,   373,   177,   111,   239,    45,   242,    55,   243,   159,
     175,   118,   178,    53,   380,    59,   168,   381,    38,   245,
      61,     8,   391,   192,   193,   194,   394,    60,   152,    53,
     155,   382,    38,    53,    38,    54,    53,   113,   174,   219,
     153,    49,   180,   396,    43,    47,   215,    50,   231,   224,
       8,    53,    53,    70,    53,    38,   236,   222,    49,   225,
     124,   125,    49,    65,    66,    37,   198,   156,    68,   164,
     152,    42,    46,     8,   239,    99,   242,    33,    72,    35,
      49,   221,   126,   127,    73,   226,   106,   101,    52,   238,
      64,    76,    53,   180,    56,   174,   113,    61,    62,   180,
     252,   253,   254,   119,   256,    74,    75,    76,     8,   251,
     259,   260,   261,   262,    83,   120,    77,    78,     8,     8,
     287,   121,     8,   134,   135,   136,   156,   137,   138,   104,
      77,    78,     8,   270,    57,   195,    79,    58,   161,   263,
       8,   264,   221,    80,    81,     8,   226,   139,    82,   140,
      79,   284,   285,   286,     8,    67,   163,    80,    81,   238,
      69,   164,    82,   180,     8,     8,    74,    75,    76,    71,
     303,   304,   305,   103,   104,     8,   306,   307,   308,    98,
     107,    77,    78,     8,   313,   315,   317,   319,   321,   360,
     108,   186,   187,   188,   189,     8,     8,    34,   130,   131,
     132,    79,   158,   333,   334,   335,   336,   337,    80,    81,
     109,   162,    34,    82,    75,    76,   181,   345,   196,   347,
     197,   349,   199,   351,   202,   353,   166,   167,   168,     8,
     137,   138,   246,    77,    78,     8,   203,   204,   205,   206,
     207,   208,   122,   123,   360,   209,   247,   104,   128,   129,
     169,   248,   140,    79,   265,   361,   211,   212,   190,   191,
      80,    81,   134,   135,   136,    82,   137,   138,   255,    77,
      78,     8,   227,   228,   184,   185,   257,   258,   292,   386,
     387,   388,   389,   390,   266,   267,   200,   271,   140,    79,
     272,   273,   274,   362,   288,   289,    80,    81,   213,   214,
     215,    82,   137,   138,   290,    77,    78,     8,   291,   293,
     361,   294,   229,   230,   231,   295,   309,   138,   232,    77,
      78,     8,   216,   310,   140,    79,   277,   278,   279,   280,
     281,   282,    80,    81,   311,   283,   233,    82,   140,    79,
     374,   322,   323,   324,   330,   331,    80,    81,   166,   167,
     168,    82,   137,   138,   332,    77,    78,     8,   338,   339,
     340,   341,   213,   214,   215,   342,   137,   138,   343,    77,
      78,     8,   249,   344,   140,    79,   296,   297,   298,   299,
     300,   301,    80,    81,   346,   302,   268,    82,   140,    79,
     348,   350,   352,   354,   363,   364,    80,    81,   229,   230,
     231,    82,   365,   138,   232,    77,    78,     8,    77,    78,
       8,    77,    78,     8,    77,    78,     8,   366,   367,   375,
     379,   384,   275,   376,   140,    79,   377,   312,    79,   378,
     314,    79,    80,    81,    79,    80,    81,    82,    80,    81,
      82,    80,    81,    82,   385,   398,    82,    77,    78,     8,
      77,    78,     8,    77,    78,     8,   399,   400,   401,   402,
      12,    41,   403,   316,   404,   405,   318,    79,   406,   320,
      79,   407,    31,    79,    80,    81,   112,    80,    81,    82,
      80,    81,    82,    32,   276,    82,   203,   204,   205,   206,
     207,   208,   269,   201,   397,   209,   250,   104,   392,   395,
     210,   203,   204,   205,   206,   207,   208,   383,   183,   393,
     209,     0,   104,   182
};

static const short int yycheck[] =
{
       1,     2,    63,     3,     4,   113,    35,    74,   164,    14,
      18,    40,    13,    14,    15,   113,    17,    22,    19,   164,
       0,    22,    23,   113,    25,   113,    27,   288,   289,   290,
      55,    32,    33,    32,    35,   322,   323,   324,    11,    40,
      41,    42,    43,    80,    81,    46,    47,    32,   156,    50,
     338,   339,   340,    34,    79,    56,   164,    23,   156,    32,
       7,     8,   170,    64,    65,    66,   156,    68,   156,   341,
     342,   343,   170,    74,   164,    41,   164,    34,   234,   104,
     170,    82,   170,    27,    35,    34,    11,    38,    19,   234,
       7,    18,   379,   130,   131,   132,   384,    34,    99,    43,
     101,   362,    33,    47,    35,   106,    50,    32,   113,   217,
      37,    25,   113,   385,    22,    23,    11,    25,    11,   217,
      18,    65,    66,    34,    68,    56,   234,   217,    42,   217,
      19,    20,    46,    41,    42,    33,   137,    32,    46,    32,
     141,    22,    23,    18,   234,    32,   234,    15,    34,    17,
      64,   156,    41,    42,    34,   156,    64,    36,    33,   164,
      41,     7,   106,   164,    32,   170,    32,     7,     8,   170,
     195,   196,   197,    35,   199,     5,     6,     7,    18,   180,
     205,   206,   207,   208,   209,    24,    16,    17,    18,    18,
     251,    23,    18,     9,    10,    11,    32,    13,    14,    36,
      16,    17,    18,   228,    33,    36,    36,    33,    35,   210,
      18,   212,   217,    43,    44,    18,   217,    33,    48,    35,
      36,   246,   247,   248,    18,    33,    35,    43,    44,   234,
      33,    32,    48,   234,    18,    18,     5,     6,     7,    33,
     265,   266,   267,    35,    36,    18,   271,   272,   273,    33,
      33,    16,    17,    18,   279,   280,   281,   282,   283,   326,
      33,   124,   125,   126,   127,    18,    18,    17,    45,    46,
      47,    36,    37,   298,   299,   300,   301,   302,    43,    44,
      33,    33,    32,    48,     6,     7,    37,   312,    36,   314,
      36,   316,    36,   318,    35,   320,     9,    10,    11,    18,
      13,    14,    36,    16,    17,    18,    25,    26,    27,    28,
      29,    30,    21,    22,   381,    34,    36,    36,    43,    44,
      33,    36,    35,    36,    36,   326,    37,    38,   128,   129,
      43,    44,     9,    10,    11,    48,    13,    14,    35,    16,
      17,    18,    37,    38,   122,   123,    35,    35,    35,   374,
     375,   376,   377,   378,    36,    36,    33,    36,    35,    36,
      36,    36,    36,    12,    37,    37,    43,    44,     9,    10,
      11,    48,    13,    14,    37,    16,    17,    18,    37,    35,
     381,    35,     9,    10,    11,    35,    37,    14,    15,    16,
      17,    18,    33,    35,    35,    36,    25,    26,    27,    28,
      29,    30,    43,    44,    35,    34,    33,    48,    35,    36,
      38,    37,    37,    37,    35,    35,    43,    44,     9,    10,
      11,    48,    13,    14,    35,    16,    17,    18,    37,    37,
      37,    37,     9,    10,    11,    37,    13,    14,    37,    16,
      17,    18,    33,    35,    35,    36,    25,    26,    27,    28,
      29,    30,    43,    44,    35,    34,    33,    48,    35,    36,
      35,    35,    35,    35,    35,    35,    43,    44,     9,    10,
      11,    48,    35,    14,    15,    16,    17,    18,    16,    17,
      18,    16,    17,    18,    16,    17,    18,    35,    35,    38,
      12,    12,    33,    38,    35,    36,    38,    32,    36,    38,
      32,    36,    43,    44,    36,    43,    44,    48,    43,    44,
      48,    43,    44,    48,    12,    33,    48,    16,    17,    18,
      16,    17,    18,    16,    17,    18,    33,    33,    33,    33,
       4,    22,    35,    32,    35,    35,    32,    36,    35,    32,
      36,    35,    15,    36,    43,    44,    75,    43,    44,    48,
      43,    44,    48,    15,   234,    48,    25,    26,    27,    28,
      29,    30,   217,   141,   385,    34,   170,    36,   379,   384,
      39,    25,    26,    27,    28,    29,    30,   362,   121,   381,
      34,    -1,    36,   120
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    50,    51,    52,    53,    54,    18,   113,
     113,     0,    52,    32,    32,    58,    59,    64,    65,    68,
      69,   113,    55,    56,    57,    60,    61,    66,    67,    87,
     113,    59,    64,    68,    65,    68,   113,    33,    69,   113,
      34,    56,    60,    66,    87,    57,    60,    66,   113,    61,
      66,   113,    33,    67,   113,    34,    68,    33,    33,    34,
      34,     7,     8,   113,    60,    66,    66,    33,    66,    33,
      34,    33,    34,    34,     5,     6,     7,    16,    17,    36,
      43,    44,    48,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   113,   114,   115,   116,   117,    33,    32,
      73,    36,    62,    35,    36,   111,    66,    33,    33,    33,
     110,   113,    62,    32,    72,   101,   108,   108,   113,    35,
      24,    23,    21,    22,    19,    20,    41,    42,    43,    44,
      45,    46,    47,   111,     9,    10,    11,    13,    14,    33,
      35,    77,    81,    82,    86,    87,    88,    89,    94,    95,
      96,   101,   113,    37,    63,   113,    32,    71,    37,   101,
     112,    35,    33,    35,    32,    70,     9,    10,    11,    33,
      76,    80,    82,    85,    87,    88,    93,    95,    96,    97,
     113,    37,   103,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   108,    36,    36,    36,   113,    36,
      33,    81,    35,    25,    26,    27,    28,    29,    30,    34,
      39,    37,    38,     9,    10,    11,    33,    75,    79,    82,
      84,    87,    88,    92,    95,    96,   113,    37,    38,     9,
      10,    11,    15,    33,    74,    78,    82,    83,    87,    88,
      90,    91,    96,    97,   100,   114,    36,    36,    36,    33,
      80,   113,   101,   101,   101,    35,   101,    35,    35,   101,
     101,   101,   101,   113,   113,    36,    36,    36,    33,    79,
     101,    36,    36,    36,    36,    33,    78,    25,    26,    27,
      28,    29,    30,    34,   101,   101,   101,   111,    37,    37,
      37,    37,    35,    35,    35,    35,    25,    26,    27,    28,
      29,    30,    34,   101,   101,   101,   101,   101,   101,    37,
      35,    35,    32,   101,    32,   101,    32,   101,    32,   101,
      32,   101,    37,    37,    37,    35,    40,    73,    73,    73,
      35,    35,    35,   101,   101,   101,   101,   101,    37,    37,
      37,    37,    37,    37,    35,   101,    35,   101,    35,   101,
      35,   101,    35,   101,    35,    72,    72,    72,    98,    99,
     110,   113,    12,    35,    35,    35,    35,    35,    71,    71,
      71,    70,    70,    70,    38,    38,    38,    38,    38,    12,
      35,    38,    73,    86,    12,    12,   101,   101,   101,   101,
     101,    72,    85,    99,    71,    84,    70,    83,    33,    33,
      33,    33,    33,    35,    35,    35,    35,    35
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
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[-1]));
		;}
    break;

  case 27:
#line 404 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 28:
#line 413 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 417 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 426 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 31:
#line 436 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 32:
#line 440 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 33:
#line 447 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 34:
#line 452 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 35:
#line 464 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 468 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 37:
#line 477 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 38:
#line 488 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 492 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 501 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 41:
#line 510 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 42:
#line 514 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 43:
#line 523 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 532 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 45:
#line 536 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 46:
#line 543 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 47:
#line 547 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 48:
#line 554 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 49:
#line 558 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 50:
#line 565 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 51:
#line 569 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 52:
#line 576 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 53:
#line 580 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 54:
#line 589 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 55:
#line 593 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 56:
#line 602 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 57:
#line 606 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 58:
#line 615 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 59:
#line 619 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 60:
#line 628 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 61:
#line 632 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 636 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 640 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 644 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 648 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 652 "BulletParser.y"
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
#line 667 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 671 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 675 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 679 "BulletParser.y"
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
#line 698 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 702 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 706 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 710 "BulletParser.y"
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
#line 733 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 737 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 741 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 745 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 749 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 753 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 757 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 761 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 768 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 93:
#line 772 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 94:
#line 779 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 95:
#line 785 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 96:
#line 792 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 97:
#line 802 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 98:
#line 808 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 99:
#line 815 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 100:
#line 825 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 101:
#line 831 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 102:
#line 838 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 103:
#line 848 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 104:
#line 854 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 105:
#line 861 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 106:
#line 871 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 107:
#line 880 "BulletParser.y"
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

  case 108:
#line 900 "BulletParser.y"
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

  case 109:
#line 920 "BulletParser.y"
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

  case 110:
#line 937 "BulletParser.y"
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

  case 111:
#line 954 "BulletParser.y"
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

  case 112:
#line 971 "BulletParser.y"
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

  case 113:
#line 991 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 114:
#line 998 "BulletParser.y"
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

  case 115:
#line 1019 "BulletParser.y"
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

  case 116:
#line 1040 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier + ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 117:
#line 1058 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier - ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 118:
#line 1076 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier * ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_MultiplyStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 119:
#line 1094 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			
			// create 'identifier / ' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_DivideStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Identifier, yylineno);
			id_node->setString((yyvsp[-5])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-3]));
		;}
    break;

  case 120:
#line 1115 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 121:
#line 1121 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 122:
#line 1128 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			// create 'identifier + 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-2])->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 123:
#line 1148 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			// create 'identifier + 1' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-2])->getStringData().c_str());
			
			YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
			v_node->setValue(1);

			add_node->setChild(0, id_node);
			add_node->setChild(1, v_node);
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 124:
#line 1168 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier +' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 125:
#line 1185 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier -' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 126:
#line 1202 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier *' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_MultiplyStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 127:
#line 1219 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			
			// create 'identifier /' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_DivideStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-3])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-1]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
		;}
    break;

  case 128:
#line 1236 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			
			// create 'identifier +' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_AddStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-7])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-4]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 129:
#line 1254 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			
			// create 'identifier -' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_SubtractStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-7])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-4]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 130:
#line 1272 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			
			// create 'identifier *' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_MultiplyStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-7])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-4]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 131:
#line 1290 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			
			// create 'identifier /' expression
			YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
			YYSTYPE add_node = AST->createNode(PT_DivideStatement, yylineno);
			
			YYSTYPE id_node = AST->createNode(PT_Property, yylineno);
			id_node->setString((yyvsp[-7])->getStringData().c_str());
			
			add_node->setChild(0, id_node);
			add_node->setChild(1, (yyvsp[-4]));
			ce_node->setChild(0, add_node);
			(yyval)->setChild(1, ce_node);
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 132:
#line 1311 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 133:
#line 1317 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 134:
#line 1326 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 135:
#line 1332 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 136:
#line 1341 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 137:
#line 1347 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 138:
#line 1356 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LoopStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 139:
#line 1362 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 140:
#line 1371 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1379 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1387 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1397 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 144:
#line 1409 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 145:
#line 1413 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 146:
#line 1422 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 147:
#line 1426 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 148:
#line 1434 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 149:
#line 1441 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 150:
#line 1449 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 151:
#line 1453 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 152:
#line 1462 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 153:
#line 1466 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 154:
#line 1475 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 155:
#line 1479 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 156:
#line 1485 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 157:
#line 1494 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 158:
#line 1498 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 159:
#line 1504 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 160:
#line 1510 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 161:
#line 1516 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 162:
#line 1525 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 163:
#line 1529 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 164:
#line 1535 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 165:
#line 1544 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 166:
#line 1548 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 167:
#line 1554 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 168:
#line 1560 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 169:
#line 1569 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 170:
#line 1573 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 171:
#line 1578 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 172:
#line 1586 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 173:
#line 1590 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 174:
#line 1594 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 175:
#line 1598 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 176:
#line 1602 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 177:
#line 1609 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 178:
#line 1618 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 179:
#line 1622 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 180:
#line 1629 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 181:
#line 1634 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 182:
#line 1646 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 183:
#line 1654 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 184:
#line 1663 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 185:
#line 1667 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 186:
#line 1674 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 187:
#line 1682 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3575 "bsBulletParser.cpp"

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


#line 1688 "BulletParser.y"


	
	

