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
     KEYWORD_WHILE = 264,
     KEYWORD_BREAK = 265,
     KEYWORD_CONTINUE = 266,
     KEYWORD_IF = 267,
     KEYWORD_ELSE = 268,
     KEYWORD_GOTO = 269,
     KEYWORD_WAIT = 270,
     KEYWORD_DIE = 271,
     INTEGER = 272,
     REAL = 273,
     IDENTIFIER = 274,
     SYMBOL_LTE = 275,
     SYMBOL_GTE = 276,
     SYMBOL_EQ = 277,
     SYMBOL_NEQ = 278,
     SYMBOL_LOG_AND = 279,
     SYMBOL_LOG_OR = 280,
     SYMBOL_INC = 281,
     SYMBOL_DEC = 282,
     SYMBOL_ADD_A = 283,
     SYMBOL_SUB_A = 284,
     SYMBOL_MUL_A = 285,
     SYMBOL_DIV_A = 286,
     TOKEN_ERROR = 287
   };
#endif
/* Tokens.  */
#define KEYWORD_CONTROLLER 258
#define KEYWORD_EMITTER 259
#define KEYWORD_AFFECTOR 260
#define KEYWORD_FUNCTION 261
#define KEYWORD_STATE 262
#define KEYWORD_EVENT 263
#define KEYWORD_WHILE 264
#define KEYWORD_BREAK 265
#define KEYWORD_CONTINUE 266
#define KEYWORD_IF 267
#define KEYWORD_ELSE 268
#define KEYWORD_GOTO 269
#define KEYWORD_WAIT 270
#define KEYWORD_DIE 271
#define INTEGER 272
#define REAL 273
#define IDENTIFIER 274
#define SYMBOL_LTE 275
#define SYMBOL_GTE 276
#define SYMBOL_EQ 277
#define SYMBOL_NEQ 278
#define SYMBOL_LOG_AND 279
#define SYMBOL_LOG_OR 280
#define SYMBOL_INC 281
#define SYMBOL_DEC 282
#define SYMBOL_ADD_A 283
#define SYMBOL_SUB_A 284
#define SYMBOL_MUL_A 285
#define SYMBOL_DIV_A 286
#define TOKEN_ERROR 287




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

void generate_affector_list(YYSTYPE parentNode, YYSTYPE affNode)
{
	if (affNode->getType() == PT_AffectorDecl)
	{
		// Create a PT_AffectorDeclList and make affNode the child of it.
		YYSTYPE newChild = AST->createNode(PT_AffectorDeclList, affNode->getLine());
		newChild->setChild(0, affNode);
		parentNode->setChild(PT_EmitterAffectorNode, newChild);
	}
	else
	{
		parentNode->setChild(PT_EmitterAffectorNode, affNode);
	}
}

void generate_member_list(YYSTYPE parentNode, YYSTYPE memNode, int nodeId)
{
	if (memNode->getType() == PT_AssignStatement)
	{
		// Create a PT_MemberList and make memNode the child of it.
		YYSTYPE newChild = AST->createNode(PT_MemberList, memNode->getLine());
		newChild->setChild(0, memNode);
		parentNode->setChild(nodeId, newChild);
	}
	else
	{
		parentNode->setChild(nodeId, memNode);
	}
}

void generate_emitter_list(YYSTYPE parentNode, YYSTYPE emitNode)
{
	if (emitNode->getType() == PT_Emitter)
	{
		// Create a PT_EmitterList and make emitNode the child of it.
		YYSTYPE newChild = AST->createNode(PT_EmitterList, emitNode->getLine());
		newChild->setChild(0, emitNode);
		parentNode->setChild(PT_ControllerEmitterNode, newChild);
	}
	else
	{
		parentNode->setChild(PT_EmitterAffectorNode, emitNode);
	}
}

void generate_assignment_expr(int nodeType, int idType, YYSTYPE parentNode, YYSTYPE idNode, YYSTYPE exprNode)
{
	parentNode->setChild(0, idNode);
	YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
	YYSTYPE expr_node = AST->createNode(nodeType, yylineno);
				
	YYSTYPE id_node = AST->createNode(idType, yylineno);
	id_node->setString(idNode->getStringData().c_str());
				
	expr_node->setChild(0, id_node);
	expr_node->setChild(1, exprNode);
	ce_node->setChild(0, expr_node);
	parentNode->setChild(1, ce_node);
}

void generate_inc_expr(int value, int nodeType, YYSTYPE parentNode, YYSTYPE idNode)
{
	parentNode->setChild(0, idNode);
	YYSTYPE ce_node = AST->createNode(PT_ConstantExpression, yylineno);
	
	YYSTYPE inc_node = 0;
	if (value == 1)
		inc_node = AST->createNode(PT_AddStatement, yylineno);
	else if (value == -1)
		inc_node = AST->createNode(PT_SubtractStatement, yylineno);
	
	YYSTYPE id_node = AST->createNode(nodeType, yylineno);
	id_node->setString(idNode->getStringData().c_str());
	
	YYSTYPE v_node = AST->createNode(PT_Constant, yylineno);
	v_node->setValue(1);

	inc_node->setChild(0, id_node);
	inc_node->setChild(1, v_node);
	ce_node->setChild(0, inc_node);
	parentNode->setChild(1, ce_node);
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
#line 268 "bsBulletParser.cpp"

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
#define YYLAST   758

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  71
/* YYNRULES -- Number of rules. */
#define YYNRULES  199
/* YYNRULES -- Number of states. */
#define YYNSTATES  442

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    48,    47,     2,     2,
      37,    38,    45,    43,    39,    44,    49,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    36,
      41,    35,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    20,    27,
      34,    42,    49,    57,    65,    74,    80,    87,    94,   102,
     109,   117,   125,   134,   136,   139,   141,   144,   150,   152,
     155,   161,   163,   166,   172,   175,   179,   181,   185,   187,
     190,   196,   198,   201,   206,   208,   211,   216,   219,   223,
     226,   230,   233,   237,   240,   244,   246,   249,   251,   254,
     256,   259,   261,   264,   266,   268,   270,   272,   274,   276,
     278,   280,   282,   284,   286,   288,   290,   292,   294,   296,
     298,   300,   302,   304,   306,   308,   310,   312,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   343,   349,   357,   365,   371,   379,   387,   393,
     401,   409,   415,   423,   431,   436,   440,   444,   449,   454,
     459,   464,   469,   478,   482,   486,   491,   496,   501,   506,
     515,   524,   533,   542,   547,   556,   560,   564,   569,   574,
     579,   584,   593,   602,   611,   620,   626,   632,   638,   644,
     647,   650,   654,   660,   667,   672,   674,   678,   680,   682,
     687,   689,   691,   695,   697,   701,   703,   707,   711,   713,
     717,   721,   725,   729,   731,   735,   739,   741,   745,   749,
     753,   755,   758,   761,   763,   765,   767,   769,   773,   776,
     779,   783,   785,   789,   791,   794,   799,   801,   803,   805
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      51,     0,    -1,    52,    -1,    53,    -1,    52,    53,    -1,
      54,    -1,    55,    -1,     4,   115,    33,    67,    34,    -1,
       4,   115,    33,    61,    67,    34,    -1,     4,   115,    33,
      57,    67,    34,    -1,     4,   115,    33,    57,    61,    67,
      34,    -1,     4,   115,    33,    56,    67,    34,    -1,     4,
     115,    33,    56,    61,    67,    34,    -1,     4,   115,    33,
      56,    57,    67,    34,    -1,     4,   115,    33,    56,    57,
      61,    67,    34,    -1,     3,   115,    33,    69,    34,    -1,
       3,   115,    33,    65,    69,    34,    -1,     3,   115,    33,
      59,    69,    34,    -1,     3,   115,    33,    59,    65,    69,
      34,    -1,     3,   115,    33,    56,    69,    34,    -1,     3,
     115,    33,    56,    65,    69,    34,    -1,     3,   115,    33,
      56,    59,    69,    34,    -1,     3,   115,    33,    56,    59,
      65,    69,    34,    -1,    88,    -1,    56,    88,    -1,    58,
      -1,    57,    58,    -1,   115,    35,     5,   112,    36,    -1,
      60,    -1,    59,    60,    -1,   115,    35,     4,   112,    36,
      -1,    62,    -1,    61,    62,    -1,   115,    35,     6,    63,
      71,    -1,    37,    38,    -1,    37,    64,    38,    -1,   115,
      -1,    64,    39,   115,    -1,    66,    -1,    65,    66,    -1,
     115,    35,     8,    63,    72,    -1,    68,    -1,    67,    68,
      -1,   115,    35,     7,    73,    -1,    70,    -1,    69,    70,
      -1,   115,    35,     7,    74,    -1,    33,    34,    -1,    33,
      75,    34,    -1,    33,    34,    -1,    33,    76,    34,    -1,
      33,    34,    -1,    33,    77,    34,    -1,    33,    34,    -1,
      33,    78,    34,    -1,    79,    -1,    75,    79,    -1,    80,
      -1,    76,    80,    -1,    81,    -1,    77,    81,    -1,    82,
      -1,    78,    82,    -1,    83,    -1,    84,    -1,    88,    -1,
      89,    -1,    91,    -1,    92,    -1,    96,    -1,    98,    -1,
      99,    -1,   102,    -1,    83,    -1,    85,    -1,    88,    -1,
      89,    -1,    90,    -1,    93,    -1,    96,    -1,    97,    -1,
      98,    -1,    83,    -1,    86,    -1,    88,    -1,    89,    -1,
      94,    -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,
      83,    -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,
      95,    -1,    96,    -1,    97,    -1,    98,    -1,    36,    -1,
     103,    36,    -1,    12,    37,   103,    38,    71,    -1,    12,
      37,   103,    38,    71,    13,    71,    -1,    12,    37,   103,
      38,    71,    13,    84,    -1,    12,    37,   103,    38,    72,
      -1,    12,    37,   103,    38,    72,    13,    72,    -1,    12,
      37,   103,    38,    72,    13,    85,    -1,    12,    37,   103,
      38,    73,    -1,    12,    37,   103,    38,    73,    13,    73,
      -1,    12,    37,   103,    38,    73,    13,    86,    -1,    12,
      37,   103,    38,    74,    -1,    12,    37,   103,    38,    74,
      13,    74,    -1,    12,    37,   103,    38,    74,    13,    87,
      -1,   115,    35,   103,    36,    -1,   115,    26,    36,    -1,
     115,    27,    36,    -1,   115,    28,   103,    36,    -1,   115,
      29,   103,    36,    -1,   115,    30,   103,    36,    -1,   115,
      31,   103,    36,    -1,   117,    35,   103,    36,    -1,   117,
      35,    33,   103,    39,   103,    34,    36,    -1,   117,    26,
      36,    -1,   117,    27,    36,    -1,   117,    28,   103,    36,
      -1,   117,    29,   103,    36,    -1,   117,    30,   103,    36,
      -1,   117,    31,   103,    36,    -1,   117,    28,    33,   103,
      39,   103,    34,    36,    -1,   117,    29,    33,   103,    39,
     103,    34,    36,    -1,   117,    30,    33,   103,    39,   103,
      34,    36,    -1,   117,    31,    33,   103,    39,   103,    34,
      36,    -1,   116,    35,   103,    36,    -1,   116,    35,    33,
     103,    39,   103,    34,    36,    -1,   116,    26,    36,    -1,
     116,    27,    36,    -1,   116,    28,   103,    36,    -1,   116,
      29,   103,    36,    -1,   116,    30,   103,    36,    -1,   116,
      31,   103,    36,    -1,   116,    28,    33,   103,    39,   103,
      34,    36,    -1,   116,    29,    33,   103,    39,   103,    34,
      36,    -1,   116,    30,    33,   103,    39,   103,    34,    36,
      -1,   116,    31,    33,   103,    39,   103,    34,    36,    -1,
       9,    37,   103,    38,    71,    -1,     9,    37,   103,    38,
      72,    -1,     9,    37,   103,    38,    73,    -1,     9,    37,
     103,    38,    74,    -1,    10,    36,    -1,    11,    36,    -1,
      14,   115,    36,    -1,    15,    37,   103,    38,    36,    -1,
     115,   115,   113,    40,   100,    36,    -1,   115,   115,   113,
      36,    -1,   101,    -1,   100,    39,   101,    -1,   112,    -1,
     115,    -1,    16,    37,    38,    36,    -1,   104,    -1,   105,
      -1,   104,    25,   105,    -1,   106,    -1,   105,    24,   106,
      -1,   107,    -1,   106,    22,   107,    -1,   106,    23,   107,
      -1,   108,    -1,   107,    41,   108,    -1,   107,    42,   108,
      -1,   107,    20,   108,    -1,   107,    21,   108,    -1,   109,
      -1,   108,    43,   109,    -1,   108,    44,   109,    -1,   110,
      -1,   109,    45,   110,    -1,   109,    46,   110,    -1,   109,
      47,   110,    -1,   111,    -1,    43,   110,    -1,    44,   110,
      -1,   115,    -1,   116,    -1,   112,    -1,   118,    -1,    37,
     103,    38,    -1,   115,   113,    -1,    37,    38,    -1,    37,
     114,    38,    -1,   103,    -1,   114,    39,   103,    -1,    19,
      -1,    48,   115,    -1,    48,   115,    49,   115,    -1,   119,
      -1,   120,    -1,    17,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   143,   143,   150,   154,   163,   167,   174,   185,   196,
     207,   218,   229,   240,   251,   265,   276,   287,   298,   309,
     320,   331,   342,   356,   360,   369,   373,   382,   391,   395,
     404,   413,   417,   426,   436,   440,   447,   452,   464,   468,
     477,   488,   492,   501,   510,   514,   523,   532,   536,   543,
     547,   554,   558,   565,   569,   576,   580,   589,   593,   602,
     606,   615,   619,   628,   632,   636,   640,   644,   648,   652,
     656,   660,   664,   671,   675,   679,   683,   687,   691,   695,
     699,   703,   710,   714,   718,   722,   726,   730,   734,   738,
     742,   749,   753,   757,   761,   765,   769,   773,   777,   781,
     788,   792,   799,   805,   812,   822,   828,   835,   845,   851,
     858,   868,   874,   881,   891,   900,   905,   910,   915,   920,
     925,   933,   939,   942,   945,   948,   951,   954,   957,   960,
     963,   966,   969,   975,   981,   988,   993,   998,  1003,  1008,
    1013,  1018,  1024,  1030,  1036,  1045,  1054,  1063,  1072,  1081,
    1085,  1092,  1100,  1108,  1118,  1130,  1134,  1143,  1147,  1155,
    1162,  1170,  1174,  1183,  1187,  1196,  1200,  1206,  1215,  1219,
    1225,  1231,  1237,  1246,  1250,  1256,  1265,  1269,  1275,  1281,
    1290,  1294,  1299,  1307,  1311,  1315,  1319,  1323,  1330,  1339,
    1343,  1350,  1355,  1367,  1375,  1384,  1395,  1399,  1406,  1414
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_CONTROLLER", "KEYWORD_EMITTER",
  "KEYWORD_AFFECTOR", "KEYWORD_FUNCTION", "KEYWORD_STATE", "KEYWORD_EVENT",
  "KEYWORD_WHILE", "KEYWORD_BREAK", "KEYWORD_CONTINUE", "KEYWORD_IF",
  "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_DIE", "INTEGER",
  "REAL", "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ",
  "SYMBOL_NEQ", "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC",
  "SYMBOL_DEC", "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A",
  "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'", "'}'", "'='", "';'", "'('", "')'",
  "','", "':'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'$'",
  "'.'", "$accept", "script_file", "definition_list", "definition",
  "emitter_definition", "controller_definition", "member_list",
  "affector_list", "affector_declaration", "emitter_list", "emitter",
  "function_list", "function", "function_arguments", "argument_list",
  "event_list", "event", "emitter_state_list", "emitter_state",
  "controller_state_list", "controller_state",
  "function_compound_statement", "event_compound_statement",
  "emitter_state_compound_statement",
  "controller_state_compound_statement", "function_statement_list",
  "event_statement_list", "emitter_state_statement_list",
  "controller_state_statement_list", "function_statement",
  "event_statement", "emitter_state_statement",
  "controller_state_statement", "expression_statement",
  "function_conditional_statement", "event_conditional_statement",
  "emitter_state_conditional_statement",
  "controller_state_conditional_statement", "simple_assignment_statement",
  "extended_assignment_statement", "emitter_member_statement",
  "property_statement", "function_iteration_statement",
  "event_iteration_statement", "emitter_state_iteration_statement",
  "controller_state_iteration_statement", "flow_statement",
  "goto_statement", "wait_statement", "fire_statement", "controller_list",
  "controller_entry", "die_statement", "constant_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression",
  "function_call", "function_call_arguments", "argument_expression_list",
  "identifier", "property", "emitter_member", "constant",
  "constant_integer", "constant_real", 0
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
     285,   286,   287,   123,   125,    61,    59,    40,    41,    44,
      58,    60,    62,    43,    45,    42,    47,    37,    36,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    57,    57,    58,    59,    59,
      60,    61,    61,    62,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      83,    83,    84,    84,    84,    85,    85,    85,    86,    86,
      86,    87,    87,    87,    88,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    93,    94,    95,    96,
      96,    97,    98,    99,    99,   100,   100,   101,   101,   102,
     103,   104,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   107,   107,   108,   108,   108,   109,   109,   109,   109,
     110,   110,   110,   111,   111,   111,   111,   111,   112,   113,
     113,   114,   114,   115,   116,   117,   118,   118,   119,   120
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     5,     6,     6,     7,     6,
       7,     7,     8,     1,     2,     1,     2,     5,     1,     2,
       5,     1,     2,     5,     2,     3,     1,     3,     1,     2,
       5,     1,     2,     4,     1,     2,     4,     2,     3,     2,
       3,     2,     3,     2,     3,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     5,     7,     7,     5,     7,     7,     5,     7,
       7,     5,     7,     7,     4,     3,     3,     4,     4,     4,
       4,     4,     8,     3,     3,     4,     4,     4,     4,     8,
       8,     8,     8,     4,     8,     3,     3,     4,     4,     4,
       4,     8,     8,     8,     8,     5,     5,     5,     5,     2,
       2,     3,     5,     6,     4,     1,     3,     1,     1,     4,
       1,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     1,     1,     1,     1,     3,     2,     2,
       3,     1,     3,     1,     2,     4,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   193,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    38,
       0,    44,    23,     0,     0,     0,    25,     0,    31,     0,
      41,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      39,     0,     0,    15,    45,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    32,     0,     0,     7,    42,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   198,   199,     0,     0,     0,     0,
       0,   160,   161,   163,   165,   168,   173,   176,   180,   185,
     183,   184,   186,   196,   197,     0,     0,     0,    11,     0,
       9,     0,     8,     0,     0,     0,     0,     0,     0,    21,
      20,    18,     0,     0,     0,    46,     0,     0,     0,   181,
     182,   194,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   188,     0,    13,
      12,    10,     0,     0,     0,    43,    22,    30,     0,     0,
       0,     0,     0,     0,    53,   100,     0,     0,    61,    91,
      92,    93,    94,    95,    96,    97,    98,    99,     0,   183,
       0,    34,     0,    36,     0,    40,   187,   162,   164,   166,
     167,   171,   172,   169,   170,   174,   175,   177,   178,   179,
     189,   191,     0,    14,    27,     0,    33,     0,     0,    51,
       0,    59,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   183,     0,   149,   150,     0,     0,     0,   194,    54,
      62,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
      49,     0,    57,    73,    74,    75,    76,    77,    78,    79,
      80,    81,   190,     0,     0,     0,     0,    47,     0,    55,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     184,     0,     0,    52,    60,     0,     0,     0,   151,     0,
       0,   115,   116,     0,     0,     0,     0,   123,   124,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,    50,    58,   192,     0,     0,     0,    48,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   195,   117,   118,   119,   120,     0,   125,
       0,   126,     0,   127,     0,   128,     0,   121,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   154,     0,   148,
     111,   152,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,     0,   137,     0,   138,     0,   139,     0,   140,
       0,   133,   147,   108,     0,   155,   157,   158,     0,     0,
       0,     0,     0,     0,   146,   105,   145,   102,     0,     0,
       0,     0,     0,     0,   153,     0,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   110,   156,   129,   130,   131,   132,   122,   106,   107,
     103,   104,     0,     0,     0,     0,     0,   141,   142,   143,
     144,   134
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,    27,    28,   117,   172,    18,    19,    29,    30,    20,
      21,   196,   175,   145,   115,   258,   241,   200,   157,   259,
     242,   201,   158,   159,   261,   244,   203,   160,    22,   162,
     163,   264,   265,   248,   206,   164,   165,   166,   167,   210,
     384,   385,   269,   168,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   137,   192,    90,    91,   170,    92,    93,
      94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -327
static const short int yypact[] =
{
     180,    -9,    -9,    30,   180,  -327,  -327,  -327,  -327,    25,
      66,  -327,  -327,    -9,    -9,    -9,    -9,  -327,    -9,  -327,
      58,  -327,  -327,    75,    -9,    -9,  -327,    -9,  -327,   119,
    -327,    93,    -9,    -9,   128,  -327,  -327,    -9,   145,   110,
    -327,   146,   124,  -327,  -327,   132,   281,    -9,    -9,   147,
    -327,    -9,   151,   141,  -327,   167,   155,  -327,  -327,   162,
     347,    -9,   169,   170,  -327,   183,  -327,   307,  -327,   230,
     228,    -9,   188,    98,  -327,  -327,   710,   710,   710,    -9,
     164,   223,   207,   294,   100,   292,   213,  -327,  -327,  -327,
     232,  -327,  -327,  -327,  -327,    -9,   192,   199,  -327,   208,
    -327,   302,  -327,   333,   270,    -9,    98,   247,   222,  -327,
    -327,  -327,   248,   232,   388,  -327,   -16,   257,   254,  -327,
    -327,  -327,  -327,   710,   710,   710,   710,   710,   710,   710,
     710,   710,   710,   710,   710,   710,   206,  -327,   249,  -327,
    -327,  -327,   277,   286,   401,  -327,  -327,  -327,   290,   295,
     297,   300,    -9,   337,  -327,  -327,    -9,   441,  -327,  -327,
    -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,   339,   275,
     332,  -327,   303,  -327,   454,  -327,  -327,   207,   294,   100,
     100,   292,   292,   292,   292,   213,   213,  -327,  -327,  -327,
    -327,  -327,   310,  -327,  -327,   494,  -327,   341,   348,  -327,
     507,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,   236,   710,  -327,  -327,   710,   340,   710,   338,  -327,
    -327,  -327,   350,   352,   710,   710,   710,   710,   710,   353,
     356,   568,   581,   602,   614,   623,  -327,    -9,   357,   359,
    -327,   547,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,  -327,  -327,   710,   364,   371,   372,  -327,   560,  -327,
    -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,
     342,   710,   710,  -327,  -327,   232,   355,   376,  -327,   379,
      -9,  -327,  -327,   385,   387,   390,   391,  -327,  -327,   710,
     392,   710,   393,   710,   394,   710,   397,   710,   398,  -327,
     710,   710,  -327,  -327,  -327,   710,   710,   402,  -327,  -327,
     403,   405,   635,   656,   668,   677,   689,   404,   408,   -20,
     188,   188,   407,  -327,  -327,  -327,  -327,  -327,   409,  -327,
     415,  -327,   418,  -327,   422,  -327,   423,  -327,   429,   432,
     436,   438,   411,  -327,  -327,   710,   443,   710,   444,   710,
     445,   710,   446,   710,   447,   247,   247,  -327,    -9,  -327,
     473,  -327,   710,   710,   710,   710,   710,   257,   257,   286,
     286,  -327,   448,  -327,   453,  -327,   455,  -327,   456,  -327,
     457,  -327,  -327,   480,    97,  -327,  -327,   232,     6,   465,
     466,   467,   474,   481,  -327,   501,  -327,   510,   710,   710,
     710,   710,   710,    57,  -327,    -9,  -327,  -327,   471,   484,
     491,   493,   496,    94,   117,   499,   500,   502,   505,   506,
    -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,  -327,   509,   511,   512,   513,   516,  -327,  -327,  -327,
    -327,  -327
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -327,  -327,  -327,   531,  -327,  -327,   532,   529,     9,   539,
     102,    28,    -6,   461,  -327,   142,    79,   144,   123,   214,
      46,  -326,  -265,  -273,  -315,  -327,  -327,  -327,  -327,   305,
     319,   368,   416,  -119,   160,   175,   177,   194,   -13,  -109,
    -167,  -327,  -327,  -327,  -327,  -327,   -95,  -115,   -81,  -187,
    -327,   184,  -327,   -19,  -327,   469,   478,   225,   193,   224,
     -10,  -327,   -67,   318,  -327,    -1,  -186,  -327,  -327,  -327,
    -327
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,    35,     8,   112,   359,   360,   247,   268,   270,
       8,    35,    23,    31,    23,    39,   357,    42,   151,    45,
     358,    54,   171,    31,    53,   202,    56,    80,    59,   208,
      11,    39,    42,    45,    50,   205,    42,    45,   142,   114,
      45,    80,    54,   396,   397,    54,    53,    56,    59,   207,
      56,    59,    48,    51,    59,   243,    50,   118,    13,   250,
      42,    45,    45,   209,    45,   246,    44,   119,   120,   198,
     113,   268,   270,   406,   247,    95,   260,     8,   121,   249,
      44,   202,   382,   383,    44,   208,   263,    44,   430,    54,
     144,   205,    43,   251,    56,    59,    59,    40,    59,    14,
     266,   161,   394,   395,   113,   207,   239,    45,    44,    44,
      46,    44,    40,   169,   267,   173,    40,   191,    36,   209,
     127,   128,   243,   187,   188,   189,   250,   174,    60,   255,
     420,   204,   246,   404,    36,   116,   405,    59,     8,   260,
      40,   129,   130,   211,   161,    67,   249,     8,   428,   263,
     195,   216,    58,    57,    44,   218,   169,    33,    37,    69,
     251,   245,    64,   266,     8,     8,     8,    70,    49,    52,
       8,    55,    58,   169,    61,    58,   101,   267,    58,    66,
      68,    98,   262,     1,     2,   100,     8,   204,     8,     8,
     103,    96,    97,   276,   211,    99,   277,   104,   279,   211,
     122,   102,     8,   109,   110,   283,   284,   285,   286,    80,
     275,     8,   290,   292,   294,   296,   298,   111,     8,    58,
      58,   114,    58,    74,    75,     8,   139,     8,   245,    34,
      38,   124,    41,   140,   304,    72,   299,    72,    73,   138,
     169,     8,   141,    76,   190,   262,    62,    63,   123,    77,
      78,    65,   317,   318,    79,     8,   146,   211,   133,   134,
     135,    58,   222,   223,   224,   225,   226,   227,     8,   136,
     328,   228,   330,   136,   332,   108,   334,   107,   336,   323,
     144,   338,   339,   193,   147,    71,   340,   341,    72,    73,
     174,   386,   176,   346,   348,   350,   352,   354,    74,    75,
       8,   222,   223,   224,   225,   226,   227,   105,   106,   107,
     228,    71,   136,   194,    72,    73,   125,   126,    76,   195,
     181,   182,   183,   184,    77,    78,   372,   212,   374,    79,
     376,   213,   378,   214,   380,   131,   132,   215,   386,   106,
     107,   236,   237,   389,   390,   391,   392,   393,   252,   253,
     179,   180,   105,   106,   107,   185,   186,   387,   229,   230,
     231,   232,   233,   234,    74,    75,     8,   235,   310,   311,
     312,   313,   314,   315,   217,   221,   278,   316,   271,   415,
     416,   417,   418,   419,    76,   272,   281,   280,   282,   287,
      77,    78,   288,   320,   300,    79,   301,   148,   149,   150,
     151,   305,   152,   153,   387,    74,    75,     8,   306,   307,
     197,   149,   150,   198,   321,   152,   153,   322,    74,    75,
       8,   324,   154,   325,   155,    76,   326,   327,   329,   331,
     333,    77,    78,   335,   337,   199,   156,   155,    76,   343,
     342,   344,   355,   361,    77,    78,   356,   371,   362,    79,
     148,   149,   150,   151,   363,   152,   153,   364,    74,    75,
       8,   365,   366,   238,   149,   150,   239,   367,   152,   153,
     368,    74,    75,     8,   369,   219,   370,   155,    76,   373,
     375,   377,   379,   381,    77,    78,   388,   398,   240,   156,
     155,    76,   399,   403,   400,   401,   402,    77,    78,   408,
     409,   410,   156,   254,   149,   150,   255,   423,   411,   153,
     256,    74,    75,     8,   413,   412,   197,   149,   150,   198,
     424,   152,   153,   414,    74,    75,     8,   425,   257,   426,
     155,    76,   427,   432,   433,    12,   434,    77,    78,   435,
     436,   273,    79,   155,    76,   437,    24,   438,   439,   440,
      77,    78,   441,    47,    32,    79,   238,   149,   150,   239,
     303,   152,   153,   309,    74,    75,     8,   143,   274,   254,
     149,   150,   255,   220,   431,   153,   256,    74,    75,     8,
     421,   302,   407,   155,    76,    74,    75,     8,   429,   422,
      77,    78,   177,   319,   308,   156,   155,    76,    74,    75,
       8,   289,   178,    77,    78,    76,     0,     0,    79,     0,
       0,    77,    78,     0,   291,     0,    79,     0,    76,    74,
      75,     8,     0,     0,    77,    78,     0,     0,     0,    79,
       0,    74,    75,     8,     0,   293,     0,     0,     0,    76,
      74,    75,     8,     0,     0,    77,    78,   295,     0,     0,
      79,    76,    74,    75,     8,     0,   297,    77,    78,     0,
      76,     0,    79,     0,     0,     0,    77,    78,   345,     0,
       0,    79,    76,    74,    75,     8,     0,     0,    77,    78,
       0,     0,     0,    79,     0,    74,    75,     8,     0,   347,
       0,     0,     0,    76,    74,    75,     8,     0,     0,    77,
      78,   349,     0,     0,    79,    76,    74,    75,     8,     0,
     351,    77,    78,     0,    76,     0,    79,     0,     0,     0,
      77,    78,   353,     0,     0,    79,    76,    74,    75,     8,
       0,     0,    77,    78,     0,     0,     0,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,     0,     0,
       0,     0,     0,    77,    78,     0,     0,     0,    79
};

static const short int yycheck[] =
{
       1,     2,    15,    19,    71,   320,   321,   174,   195,   195,
      19,    24,    13,    14,    15,    16,    36,    18,    12,    20,
      40,    27,    38,    24,    25,   144,    27,    46,    29,   144,
       0,    32,    33,    34,    25,   144,    37,    38,   105,    33,
      41,    60,    48,   369,   370,    51,    47,    48,    49,   144,
      51,    52,    24,    25,    55,   174,    47,    76,    33,   174,
      61,    62,    63,   144,    65,   174,    20,    77,    78,    12,
      71,   258,   258,   388,   241,    47,   195,    19,    79,   174,
      34,   200,   355,   356,    38,   200,   195,    41,   414,    95,
      33,   200,    34,   174,    95,    96,    97,    18,    99,    33,
     195,   114,   367,   368,   105,   200,    12,   108,    62,    63,
      35,    65,    33,   114,   195,   116,    37,   136,    16,   200,
      20,    21,   241,   133,   134,   135,   241,    33,    35,    12,
     403,   144,   241,    36,    32,    37,    39,   138,    19,   258,
      61,    41,    42,   144,   157,    35,   241,    19,   413,   258,
      33,   152,    29,    34,   108,   156,   157,    15,    16,    35,
     241,   174,    34,   258,    19,    19,    19,    35,    24,    25,
      19,    27,    49,   174,    32,    52,    35,   258,    55,    34,
      34,    34,   195,     3,     4,    34,    19,   200,    19,    19,
      35,    47,    48,   212,   195,    51,   215,    35,   217,   200,
      36,    34,    19,    34,    34,   224,   225,   226,   227,   228,
     211,    19,   231,   232,   233,   234,   235,    34,    19,    96,
      97,    33,    99,    17,    18,    19,    34,    19,   241,    15,
      16,    24,    18,    34,   253,     7,   237,     7,     8,    95,
     241,    19,    34,    37,    38,   258,    32,    33,    25,    43,
      44,    37,   271,   272,    48,    19,    34,   258,    45,    46,
      47,   138,    26,    27,    28,    29,    30,    31,    19,    37,
     289,    35,   291,    37,   293,    61,   295,     7,   297,   280,
      33,   300,   301,    34,    36,     4,   305,   306,     7,     8,
      33,   358,    38,   312,   313,   314,   315,   316,    17,    18,
      19,    26,    27,    28,    29,    30,    31,     5,     6,     7,
      35,     4,    37,    36,     7,     8,    22,    23,    37,    33,
     127,   128,   129,   130,    43,    44,   345,    37,   347,    48,
     349,    36,   351,    36,   353,    43,    44,    37,   405,     6,
       7,    38,    39,   362,   363,   364,   365,   366,    38,    39,
     125,   126,     5,     6,     7,   131,   132,   358,    26,    27,
      28,    29,    30,    31,    17,    18,    19,    35,    26,    27,
      28,    29,    30,    31,    37,    36,    36,    35,    37,   398,
     399,   400,   401,   402,    37,    37,    36,    49,    36,    36,
      43,    44,    36,    38,    37,    48,    37,     9,    10,    11,
      12,    37,    14,    15,   405,    17,    18,    19,    37,    37,
       9,    10,    11,    12,    38,    14,    15,    38,    17,    18,
      19,    36,    34,    36,    36,    37,    36,    36,    36,    36,
      36,    43,    44,    36,    36,    34,    48,    36,    37,    36,
      38,    36,    38,    36,    43,    44,    38,    36,    39,    48,
       9,    10,    11,    12,    39,    14,    15,    39,    17,    18,
      19,    39,    39,     9,    10,    11,    12,    38,    14,    15,
      38,    17,    18,    19,    38,    34,    38,    36,    37,    36,
      36,    36,    36,    36,    43,    44,    13,    39,    34,    48,
      36,    37,    39,    13,    39,    39,    39,    43,    44,    34,
      34,    34,    48,     9,    10,    11,    12,    36,    34,    15,
      16,    17,    18,    19,    13,    34,     9,    10,    11,    12,
      36,    14,    15,    13,    17,    18,    19,    36,    34,    36,
      36,    37,    36,    34,    34,     4,    34,    43,    44,    34,
      34,    34,    48,    36,    37,    36,    14,    36,    36,    36,
      43,    44,    36,    24,    15,    48,     9,    10,    11,    12,
     241,    14,    15,   258,    17,    18,    19,   106,   200,     9,
      10,    11,    12,   157,   414,    15,    16,    17,    18,    19,
     403,    34,   388,    36,    37,    17,    18,    19,   413,   405,
      43,    44,   123,   275,    34,    48,    36,    37,    17,    18,
      19,    33,   124,    43,    44,    37,    -1,    -1,    48,    -1,
      -1,    43,    44,    -1,    33,    -1,    48,    -1,    37,    17,
      18,    19,    -1,    -1,    43,    44,    -1,    -1,    -1,    48,
      -1,    17,    18,    19,    -1,    33,    -1,    -1,    -1,    37,
      17,    18,    19,    -1,    -1,    43,    44,    33,    -1,    -1,
      48,    37,    17,    18,    19,    -1,    33,    43,    44,    -1,
      37,    -1,    48,    -1,    -1,    -1,    43,    44,    33,    -1,
      -1,    48,    37,    17,    18,    19,    -1,    -1,    43,    44,
      -1,    -1,    -1,    48,    -1,    17,    18,    19,    -1,    33,
      -1,    -1,    -1,    37,    17,    18,    19,    -1,    -1,    43,
      44,    33,    -1,    -1,    48,    37,    17,    18,    19,    -1,
      33,    43,    44,    -1,    37,    -1,    48,    -1,    -1,    -1,
      43,    44,    33,    -1,    -1,    48,    37,    17,    18,    19,
      -1,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    51,    52,    53,    54,    55,    19,   115,
     115,     0,    53,    33,    33,    56,    59,    60,    65,    66,
      69,    70,    88,   115,    56,    57,    58,    61,    62,    67,
      68,   115,    59,    65,    69,    88,    60,    65,    69,   115,
      66,    69,   115,    34,    70,   115,    35,    57,    61,    67,
      58,    61,    67,   115,    62,    67,   115,    34,    68,   115,
      35,    65,    69,    69,    34,    69,    34,    35,    34,    35,
      35,     4,     7,     8,    17,    18,    37,    43,    44,    48,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     115,   116,   118,   119,   120,    61,    67,    67,    34,    67,
      34,    35,    34,    35,    35,     5,     6,     7,    69,    34,
      34,    34,   112,   115,    33,    74,    37,    63,   103,   110,
     110,   115,    36,    25,    24,    22,    23,    20,    21,    41,
      42,    43,    44,    45,    46,    47,    37,   113,    67,    34,
      34,    34,   112,    63,    33,    73,    34,    36,     9,    10,
      11,    12,    14,    15,    34,    36,    48,    78,    82,    83,
      87,    88,    89,    90,    95,    96,    97,    98,   103,   115,
     117,    38,    64,   115,    33,    72,    38,   105,   106,   107,
     107,   108,   108,   108,   108,   109,   109,   110,   110,   110,
      38,   103,   114,    34,    36,    33,    71,     9,    12,    34,
      77,    81,    83,    86,    88,    89,    94,    96,    97,    98,
      99,   115,    37,    36,    36,    37,   115,    37,   115,    34,
      82,    36,    26,    27,    28,    29,    30,    31,    35,    26,
      27,    28,    29,    30,    31,    35,    38,    39,     9,    12,
      34,    76,    80,    83,    85,    88,    89,    90,    93,    96,
      97,    98,    38,    39,     9,    12,    16,    34,    75,    79,
      83,    84,    88,    89,    91,    92,    96,    98,    99,   102,
     116,    37,    37,    34,    81,   115,   103,   103,    36,   103,
      49,    36,    36,   103,   103,   103,   103,    36,    36,    33,
     103,    33,   103,    33,   103,    33,   103,    33,   103,   115,
      37,    37,    34,    80,   103,    37,    37,    37,    34,    79,
      26,    27,    28,    29,    30,    31,    35,   103,   103,   113,
      38,    38,    38,   115,    36,    36,    36,    36,   103,    36,
     103,    36,   103,    36,   103,    36,   103,    36,   103,   103,
     103,   103,    38,    36,    36,    33,   103,    33,   103,    33,
     103,    33,   103,    33,   103,    38,    38,    36,    40,    74,
      74,    36,    39,    39,    39,    39,    39,    38,    38,    38,
      38,    36,   103,    36,   103,    36,   103,    36,   103,    36,
     103,    36,    73,    73,   100,   101,   112,   115,    13,   103,
     103,   103,   103,   103,    72,    72,    71,    71,    39,    39,
      39,    39,    39,    13,    36,    39,    74,    87,    34,    34,
      34,    34,    34,    13,    13,   103,   103,   103,   103,   103,
      73,    86,   101,    36,    36,    36,    36,    36,    72,    85,
      71,    84,    34,    34,    34,    34,    34,    36,    36,    36,
      36,    36
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
#line 144 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 151 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 155 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 164 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 168 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 175 "BulletParser.y"
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
#line 186 "BulletParser.y"
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
#line 197 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			generate_affector_list((yyval), (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterMemberNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 10:
#line 208 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			generate_affector_list((yyval), (yyvsp[-3]));
			(yyval)->setChild(PT_EmitterMemberNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 11:
#line 219 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			generate_member_list((yyval), (yyvsp[-2]), PT_EmitterMemberNode);
			(yyval)->setChild(PT_EmitterAffectorNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 12:
#line 230 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);

			generate_member_list((yyval), (yyvsp[-3]), PT_EmitterMemberNode);
			(yyval)->setChild(PT_EmitterAffectorNode, 0);
			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 13:
#line 241 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			generate_member_list((yyval), (yyvsp[-3]), PT_EmitterMemberNode);
			generate_affector_list((yyval), (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterFunctionNode, 0);
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 14:
#line 252 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-6])->getStringData().c_str());			
			delete (yyvsp[-6]);

			generate_member_list((yyval), (yyvsp[-4]), PT_EmitterMemberNode);
			generate_affector_list((yyval), (yyvsp[-3]));
			(yyval)->setChild(PT_EmitterFunctionNode, (yyvsp[-2]));
			(yyval)->setChild(PT_EmitterStateNode, (yyvsp[-1]));
		;}
    break;

  case 15:
#line 266 "BulletParser.y"
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
#line 277 "BulletParser.y"
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
#line 288 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());			
			delete (yyvsp[-4]);
			
			generate_emitter_list((yyval), (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerMemberNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, 0);
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 18:
#line 299 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			generate_emitter_list((yyval), (yyvsp[-3]));
			(yyval)->setChild(PT_ControllerMemberNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 19:
#line 310 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);

			generate_member_list((yyval), (yyvsp[-2]), PT_ControllerMemberNode);
			(yyval)->setChild(PT_ControllerEmitterNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, 0);
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 20:
#line 321 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			generate_member_list((yyval), (yyvsp[-3]), PT_ControllerMemberNode);
			(yyval)->setChild(PT_ControllerEmitterNode, 0);
			(yyval)->setChild(PT_ControllerEventNode, (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 21:
#line 332 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-5])->getStringData().c_str());			
			delete (yyvsp[-5]);
			
			generate_member_list((yyval), (yyvsp[-3]), PT_ControllerMemberNode);
			generate_emitter_list((yyval), (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerEventNode, 0);
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 22:
#line 343 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-6])->getStringData().c_str());			
			delete (yyvsp[-6]);
			
			generate_member_list((yyval), (yyvsp[-4]), PT_ControllerMemberNode);
			generate_emitter_list((yyval), (yyvsp[-3]));
			(yyval)->setChild(PT_ControllerEventNode, (yyvsp[-2]));
			(yyval)->setChild(PT_ControllerStateNode, (yyvsp[-1]));
		;}
    break;

  case 23:
#line 357 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 361 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 370 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 374 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 383 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 28:
#line 392 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 396 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 405 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 31:
#line 414 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 32:
#line 418 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 33:
#line 427 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 34:
#line 437 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 35:
#line 441 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 36:
#line 448 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 37:
#line 453 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 38:
#line 465 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 469 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 478 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 41:
#line 489 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 42:
#line 493 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 43:
#line 502 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 511 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 45:
#line 515 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 46:
#line 524 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 533 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 48:
#line 537 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 49:
#line 544 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 50:
#line 548 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 51:
#line 555 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 52:
#line 559 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 53:
#line 566 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 54:
#line 570 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 55:
#line 577 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 56:
#line 581 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 57:
#line 590 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 58:
#line 594 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 59:
#line 603 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 607 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 61:
#line 616 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 620 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 629 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 633 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 637 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 641 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 645 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 649 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 653 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 657 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 661 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 665 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 672 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 676 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 680 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 684 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 688 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 692 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 696 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 700 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 704 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 711 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 715 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 719 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 723 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 727 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 731 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 735 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 739 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 743 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 750 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 754 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 758 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 762 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 766 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 770 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 774 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 778 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 782 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 789 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 101:
#line 793 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 102:
#line 800 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 103:
#line 806 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 104:
#line 813 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 105:
#line 823 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 106:
#line 829 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 107:
#line 836 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 108:
#line 846 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 109:
#line 852 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 110:
#line 859 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 111:
#line 869 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 112:
#line 875 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 113:
#line 882 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 114:
#line 892 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 115:
#line 901 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 116:
#line 906 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 117:
#line 911 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 118:
#line 916 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 119:
#line 921 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 120:
#line 926 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 121:
#line 934 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 122:
#line 940 "BulletParser.y"
    {
		;}
    break;

  case 123:
#line 943 "BulletParser.y"
    {
		;}
    break;

  case 124:
#line 946 "BulletParser.y"
    {
		;}
    break;

  case 125:
#line 949 "BulletParser.y"
    {
		;}
    break;

  case 126:
#line 952 "BulletParser.y"
    {
		;}
    break;

  case 127:
#line 955 "BulletParser.y"
    {
		;}
    break;

  case 128:
#line 958 "BulletParser.y"
    {
		;}
    break;

  case 129:
#line 961 "BulletParser.y"
    {
		;}
    break;

  case 130:
#line 964 "BulletParser.y"
    {
		;}
    break;

  case 131:
#line 967 "BulletParser.y"
    {
		;}
    break;

  case 132:
#line 970 "BulletParser.y"
    {
		;}
    break;

  case 133:
#line 976 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 134:
#line 982 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 135:
#line 989 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 136:
#line 994 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 137:
#line 999 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 138:
#line 1004 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 139:
#line 1009 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 140:
#line 1014 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1019 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1025 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 143:
#line 1031 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 144:
#line 1037 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 145:
#line 1046 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 146:
#line 1055 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 147:
#line 1064 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 148:
#line 1073 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 149:
#line 1082 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 150:
#line 1086 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 151:
#line 1093 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 152:
#line 1101 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 153:
#line 1109 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 154:
#line 1119 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 155:
#line 1131 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 156:
#line 1135 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 157:
#line 1144 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 158:
#line 1148 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 159:
#line 1156 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 160:
#line 1163 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 161:
#line 1171 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 162:
#line 1175 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 163:
#line 1184 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 164:
#line 1188 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 165:
#line 1197 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 166:
#line 1201 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 167:
#line 1207 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 168:
#line 1216 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 169:
#line 1220 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 170:
#line 1226 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 171:
#line 1232 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 172:
#line 1238 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 173:
#line 1247 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 174:
#line 1251 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 175:
#line 1257 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 176:
#line 1266 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 177:
#line 1270 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 178:
#line 1276 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 179:
#line 1282 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 180:
#line 1291 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 181:
#line 1295 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 182:
#line 1300 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 183:
#line 1308 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 184:
#line 1312 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 185:
#line 1316 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 186:
#line 1320 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 187:
#line 1324 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 188:
#line 1331 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 189:
#line 1340 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 190:
#line 1344 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 191:
#line 1351 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 192:
#line 1356 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 193:
#line 1368 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 194:
#line 1376 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 195:
#line 1385 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1396 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 197:
#line 1400 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 198:
#line 1407 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 199:
#line 1415 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3397 "bsBulletParser.cpp"

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


#line 1421 "BulletParser.y"


	
	

