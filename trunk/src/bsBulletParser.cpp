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
     KEYWORD_RAISE = 264,
     KEYWORD_ENABLE = 265,
     KEYWORD_DISABLE = 266,
     KEYWORD_WHILE = 267,
     KEYWORD_BREAK = 268,
     KEYWORD_CONTINUE = 269,
     KEYWORD_IF = 270,
     KEYWORD_ELSE = 271,
     KEYWORD_GOTO = 272,
     KEYWORD_WAIT = 273,
     KEYWORD_SUSPEND = 274,
     KEYWORD_SIGNAL = 275,
     KEYWORD_DIE = 276,
     INTEGER = 277,
     REAL = 278,
     IDENTIFIER = 279,
     SYMBOL_LTE = 280,
     SYMBOL_GTE = 281,
     SYMBOL_EQ = 282,
     SYMBOL_NEQ = 283,
     SYMBOL_LOG_AND = 284,
     SYMBOL_LOG_OR = 285,
     SYMBOL_INC = 286,
     SYMBOL_DEC = 287,
     SYMBOL_ADD_A = 288,
     SYMBOL_SUB_A = 289,
     SYMBOL_MUL_A = 290,
     SYMBOL_DIV_A = 291,
     TOKEN_ERROR = 292
   };
#endif
/* Tokens.  */
#define KEYWORD_CONTROLLER 258
#define KEYWORD_EMITTER 259
#define KEYWORD_AFFECTOR 260
#define KEYWORD_FUNCTION 261
#define KEYWORD_STATE 262
#define KEYWORD_EVENT 263
#define KEYWORD_RAISE 264
#define KEYWORD_ENABLE 265
#define KEYWORD_DISABLE 266
#define KEYWORD_WHILE 267
#define KEYWORD_BREAK 268
#define KEYWORD_CONTINUE 269
#define KEYWORD_IF 270
#define KEYWORD_ELSE 271
#define KEYWORD_GOTO 272
#define KEYWORD_WAIT 273
#define KEYWORD_SUSPEND 274
#define KEYWORD_SIGNAL 275
#define KEYWORD_DIE 276
#define INTEGER 277
#define REAL 278
#define IDENTIFIER 279
#define SYMBOL_LTE 280
#define SYMBOL_GTE 281
#define SYMBOL_EQ 282
#define SYMBOL_NEQ 283
#define SYMBOL_LOG_AND 284
#define SYMBOL_LOG_OR 285
#define SYMBOL_INC 286
#define SYMBOL_DEC 287
#define SYMBOL_ADD_A 288
#define SYMBOL_SUB_A 289
#define SYMBOL_MUL_A 290
#define SYMBOL_DIV_A 291
#define TOKEN_ERROR 292




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
	AST->addError(yylineno, a_msg);
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
	if (idType == PT_EmitterMember)
	{
		id_node->setString(idNode->getStringData().c_str());
		id_node->setChild(0, idNode->getChild(0));
	}
	else
	{
		id_node->setString(idNode->getStringData().c_str());
	}
				
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
	if (nodeType == PT_EmitterMember)
	{
		id_node->setString(idNode->getStringData().c_str());
		id_node->setChild(0, idNode->getChild(0));
	}
	else
	{
		id_node->setString(idNode->getStringData().c_str());
	}	
	
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
#line 294 "bsBulletParser.cpp"

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
#define YYLAST   794

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  78
/* YYNRULES -- Number of rules. */
#define YYNRULES  225
/* YYNRULES -- Number of states. */
#define YYNSTATES  494

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    46,    53,     2,     2,
      42,    43,    51,    49,    44,    50,    54,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    41,
      47,    40,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    20,    27,
      34,    42,    49,    57,    65,    74,    80,    87,    94,   102,
     109,   117,   125,   134,   136,   139,   141,   144,   150,   152,
     155,   161,   169,   178,   180,   184,   186,   189,   195,   198,
     202,   204,   208,   210,   213,   219,   221,   224,   229,   231,
     234,   239,   242,   246,   249,   253,   256,   260,   263,   267,
     269,   272,   274,   277,   279,   282,   284,   287,   289,   291,
     293,   295,   297,   299,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   321,   323,   325,   327,   329,   331,
     333,   335,   337,   339,   341,   343,   345,   347,   349,   351,
     353,   355,   357,   359,   361,   363,   365,   367,   369,   371,
     373,   375,   377,   379,   382,   388,   396,   404,   410,   418,
     426,   432,   440,   448,   454,   462,   470,   475,   479,   483,
     488,   493,   498,   503,   508,   517,   521,   525,   530,   535,
     540,   545,   554,   563,   572,   581,   586,   595,   599,   603,
     608,   613,   618,   623,   632,   641,   650,   659,   665,   671,
     677,   683,   686,   689,   693,   697,   703,   706,   712,   715,
     721,   728,   733,   735,   739,   741,   743,   748,   751,   755,
     759,   764,   769,   771,   773,   777,   779,   783,   785,   789,
     793,   795,   799,   803,   807,   811,   813,   817,   821,   823,
     827,   831,   835,   837,   840,   843,   845,   847,   849,   851,
     853,   857,   860,   863,   867,   869,   873,   875,   878,   883,
     885,   888,   891,   893,   895,   897
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      56,     0,    -1,    57,    -1,    58,    -1,    57,    58,    -1,
      59,    -1,    60,    -1,     4,   126,    38,    73,    39,    -1,
       4,   126,    38,    67,    73,    39,    -1,     4,   126,    38,
      62,    73,    39,    -1,     4,   126,    38,    62,    67,    73,
      39,    -1,     4,   126,    38,    61,    73,    39,    -1,     4,
     126,    38,    61,    67,    73,    39,    -1,     4,   126,    38,
      61,    62,    73,    39,    -1,     4,   126,    38,    61,    62,
      67,    73,    39,    -1,     3,   126,    38,    75,    39,    -1,
       3,   126,    38,    71,    75,    39,    -1,     3,   126,    38,
      64,    75,    39,    -1,     3,   126,    38,    64,    71,    75,
      39,    -1,     3,   126,    38,    61,    75,    39,    -1,     3,
     126,    38,    61,    71,    75,    39,    -1,     3,   126,    38,
      61,    64,    75,    39,    -1,     3,   126,    38,    61,    64,
      71,    75,    39,    -1,    94,    -1,    61,    94,    -1,    63,
      -1,    62,    63,    -1,   126,    40,     5,   123,    41,    -1,
      65,    -1,    64,    65,    -1,   126,    40,     4,   126,    41,
      -1,   126,    40,     4,   126,    42,    43,    41,    -1,   126,
      40,     4,   126,    42,    66,    43,    41,    -1,   129,    -1,
      66,    44,   129,    -1,    68,    -1,    67,    68,    -1,   126,
      40,     6,    69,    77,    -1,    42,    43,    -1,    42,    70,
      43,    -1,   126,    -1,    70,    44,   126,    -1,    72,    -1,
      71,    72,    -1,   126,    40,     8,    69,    78,    -1,    74,
      -1,    73,    74,    -1,   126,    40,     7,    79,    -1,    76,
      -1,    75,    76,    -1,   126,    40,     7,    80,    -1,    38,
      39,    -1,    38,    81,    39,    -1,    38,    39,    -1,    38,
      82,    39,    -1,    38,    39,    -1,    38,    83,    39,    -1,
      38,    39,    -1,    38,    84,    39,    -1,    85,    -1,    81,
      85,    -1,    86,    -1,    82,    86,    -1,    87,    -1,    83,
      87,    -1,    88,    -1,    84,    88,    -1,    89,    -1,    90,
      -1,    94,    -1,    95,    -1,    97,    -1,    98,    -1,   102,
      -1,   105,    -1,   108,    -1,   111,    -1,    89,    -1,    91,
      -1,    94,    -1,    95,    -1,    96,    -1,    99,    -1,   102,
      -1,   103,    -1,   104,    -1,   112,    -1,   106,    -1,   107,
      -1,   113,    -1,    89,    -1,    92,    -1,    94,    -1,    95,
      -1,   100,    -1,   102,    -1,   103,    -1,   105,    -1,   108,
      -1,    89,    -1,    93,    -1,    94,    -1,    95,    -1,    96,
      -1,   101,    -1,   102,    -1,   103,    -1,   104,    -1,   105,
      -1,   106,    -1,   112,    -1,   113,    -1,    41,    -1,   114,
      41,    -1,    15,    42,   114,    43,    77,    -1,    15,    42,
     114,    43,    77,    16,    77,    -1,    15,    42,   114,    43,
      77,    16,    90,    -1,    15,    42,   114,    43,    78,    -1,
      15,    42,   114,    43,    78,    16,    78,    -1,    15,    42,
     114,    43,    78,    16,    91,    -1,    15,    42,   114,    43,
      79,    -1,    15,    42,   114,    43,    79,    16,    79,    -1,
      15,    42,   114,    43,    79,    16,    92,    -1,    15,    42,
     114,    43,    80,    -1,    15,    42,   114,    43,    80,    16,
      80,    -1,    15,    42,   114,    43,    80,    16,    93,    -1,
     126,    40,   114,    41,    -1,   126,    31,    41,    -1,   126,
      32,    41,    -1,   126,    33,   114,    41,    -1,   126,    34,
     114,    41,    -1,   126,    35,   114,    41,    -1,   126,    36,
     114,    41,    -1,   128,    40,   114,    41,    -1,   128,    40,
      38,   114,    44,   114,    39,    41,    -1,   128,    31,    41,
      -1,   128,    32,    41,    -1,   128,    33,   114,    41,    -1,
     128,    34,   114,    41,    -1,   128,    35,   114,    41,    -1,
     128,    36,   114,    41,    -1,   128,    33,    38,   114,    44,
     114,    39,    41,    -1,   128,    34,    38,   114,    44,   114,
      39,    41,    -1,   128,    35,    38,   114,    44,   114,    39,
      41,    -1,   128,    36,    38,   114,    44,   114,    39,    41,
      -1,   127,    40,   114,    41,    -1,   127,    40,    38,   114,
      44,   114,    39,    41,    -1,   127,    31,    41,    -1,   127,
      32,    41,    -1,   127,    33,   114,    41,    -1,   127,    34,
     114,    41,    -1,   127,    35,   114,    41,    -1,   127,    36,
     114,    41,    -1,   127,    33,    38,   114,    44,   114,    39,
      41,    -1,   127,    34,    38,   114,    44,   114,    39,    41,
      -1,   127,    35,    38,   114,    44,   114,    39,    41,    -1,
     127,    36,    38,   114,    44,   114,    39,    41,    -1,    12,
      42,   114,    43,    77,    -1,    12,    42,   114,    43,    78,
      -1,    12,    42,   114,    43,    79,    -1,    12,    42,   114,
      43,    80,    -1,    13,    41,    -1,    14,    41,    -1,    17,
     126,    41,    -1,    17,   128,    41,    -1,    18,    42,   114,
      43,    41,    -1,    19,    41,    -1,    19,    42,    66,    43,
      41,    -1,    20,    41,    -1,    20,    42,    66,    43,    41,
      -1,   126,   126,   124,    45,   109,    41,    -1,   126,   126,
     124,    41,    -1,   110,    -1,   109,    44,   110,    -1,   123,
      -1,   126,    -1,    21,    42,    43,    41,    -1,    21,    41,
      -1,     9,   123,    41,    -1,     9,   126,    41,    -1,    10,
      46,   126,    41,    -1,    11,    46,   126,    41,    -1,   115,
      -1,   116,    -1,   115,    30,   116,    -1,   117,    -1,   116,
      29,   117,    -1,   118,    -1,   117,    27,   118,    -1,   117,
      28,   118,    -1,   119,    -1,   118,    47,   119,    -1,   118,
      48,   119,    -1,   118,    25,   119,    -1,   118,    26,   119,
      -1,   120,    -1,   119,    49,   120,    -1,   119,    50,   120,
      -1,   121,    -1,   120,    51,   121,    -1,   120,    52,   121,
      -1,   120,    53,   121,    -1,   122,    -1,    49,   121,    -1,
      50,   121,    -1,   126,    -1,   127,    -1,   128,    -1,   123,
      -1,   130,    -1,    42,   114,    43,    -1,   126,   124,    -1,
      42,    43,    -1,    42,   125,    43,    -1,   114,    -1,   125,
      44,   114,    -1,    24,    -1,    46,   126,    -1,    46,   126,
      54,   126,    -1,   130,    -1,    49,   130,    -1,    50,   130,
      -1,   131,    -1,   132,    -1,    22,    -1,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   164,   164,   171,   175,   184,   188,   195,   206,   217,
     228,   239,   250,   261,   272,   286,   297,   308,   319,   330,
     341,   352,   363,   377,   381,   390,   394,   403,   412,   416,
     425,   431,   437,   447,   451,   460,   464,   473,   483,   487,
     494,   499,   511,   515,   524,   535,   539,   548,   557,   561,
     570,   579,   583,   590,   594,   601,   605,   612,   616,   623,
     627,   636,   640,   649,   653,   662,   666,   675,   679,   683,
     687,   691,   695,   699,   703,   707,   711,   718,   722,   726,
     730,   734,   738,   742,   746,   750,   754,   758,   762,   766,
     773,   777,   781,   785,   789,   793,   797,   801,   805,   812,
     816,   820,   824,   828,   832,   836,   840,   844,   848,   852,
     856,   860,   867,   871,   878,   884,   891,   901,   907,   914,
     924,   930,   937,   947,   953,   960,   970,   979,   984,   989,
     994,   999,  1004,  1012,  1018,  1025,  1030,  1035,  1040,  1045,
    1050,  1055,  1061,  1067,  1073,  1082,  1088,  1095,  1100,  1105,
    1110,  1115,  1120,  1125,  1131,  1137,  1143,  1152,  1161,  1170,
    1179,  1188,  1192,  1199,  1207,  1215,  1223,  1227,  1234,  1238,
    1246,  1256,  1268,  1272,  1281,  1285,  1293,  1297,  1304,  1309,
    1317,  1323,  1332,  1340,  1344,  1353,  1357,  1366,  1370,  1376,
    1385,  1389,  1395,  1401,  1407,  1416,  1420,  1426,  1435,  1439,
    1445,  1451,  1460,  1464,  1469,  1477,  1481,  1485,  1489,  1493,
    1497,  1504,  1513,  1517,  1524,  1529,  1541,  1549,  1558,  1569,
    1573,  1577,  1585,  1589,  1596,  1604
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_CONTROLLER", "KEYWORD_EMITTER",
  "KEYWORD_AFFECTOR", "KEYWORD_FUNCTION", "KEYWORD_STATE", "KEYWORD_EVENT",
  "KEYWORD_RAISE", "KEYWORD_ENABLE", "KEYWORD_DISABLE", "KEYWORD_WHILE",
  "KEYWORD_BREAK", "KEYWORD_CONTINUE", "KEYWORD_IF", "KEYWORD_ELSE",
  "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_SUSPEND", "KEYWORD_SIGNAL",
  "KEYWORD_DIE", "INTEGER", "REAL", "IDENTIFIER", "SYMBOL_LTE",
  "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ", "SYMBOL_LOG_AND",
  "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC", "SYMBOL_ADD_A",
  "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'",
  "'}'", "'='", "';'", "'('", "')'", "','", "':'", "'$'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'.'", "$accept", "script_file",
  "definition_list", "definition", "emitter_definition",
  "controller_definition", "member_list", "affector_list",
  "affector_declaration", "emitter_list", "emitter", "constant_arg_list",
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
  "goto_statement", "member_goto_statement", "wait_statement",
  "suspend_statement", "signal_statement", "emit_statement",
  "controller_list", "controller_entry", "die_statement",
  "raise_statement", "enable_statement", "constant_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "primary_expression",
  "function_call", "function_call_arguments", "argument_expression_list",
  "identifier", "property", "emitter_member", "signed_constant",
  "unsigned_constant", "constant_integer", "constant_real", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   123,   125,
      61,    59,    40,    41,    44,    58,    36,    60,    62,    43,
      45,    42,    47,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    62,    62,    63,    64,    64,
      65,    65,    65,    66,    66,    67,    67,    68,    69,    69,
      70,    70,    71,    71,    72,    73,    73,    74,    75,    75,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    89,    89,    90,    90,    90,    91,    91,    91,
      92,    92,    92,    93,    93,    93,    94,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    98,    99,   100,
     101,   102,   102,   103,   104,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   114,   115,   115,   116,   116,   117,   117,   117,
     118,   118,   118,   118,   118,   119,   119,   119,   120,   120,
     120,   120,   121,   121,   121,   122,   122,   122,   122,   122,
     122,   123,   124,   124,   125,   125,   126,   127,   128,   129,
     129,   129,   130,   130,   131,   132
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     5,     6,     6,     7,     6,
       7,     7,     8,     1,     2,     1,     2,     5,     1,     2,
       5,     7,     8,     1,     3,     1,     2,     5,     2,     3,
       1,     3,     1,     2,     5,     1,     2,     4,     1,     2,
       4,     2,     3,     2,     3,     2,     3,     2,     3,     1,
       2,     1,     2,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     7,     7,     5,     7,     7,
       5,     7,     7,     5,     7,     7,     4,     3,     3,     4,
       4,     4,     4,     4,     8,     3,     3,     4,     4,     4,
       4,     8,     8,     8,     8,     4,     8,     3,     3,     4,
       4,     4,     4,     8,     8,     8,     8,     5,     5,     5,
       5,     2,     2,     3,     3,     5,     2,     5,     2,     5,
       6,     4,     1,     3,     1,     1,     4,     2,     3,     3,
       4,     4,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     1,     1,     1,     1,     1,
       3,     2,     2,     3,     1,     3,     1,     2,     4,     1,
       2,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   216,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    42,
       0,    48,    23,     0,     0,     0,    25,     0,    35,     0,
      45,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      43,     0,     0,    15,    49,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    36,     0,     0,     7,    46,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   224,   225,     0,     0,     0,     0,
       0,   182,   183,   185,   187,   190,   195,   198,   202,   208,
     205,   206,   207,   209,   222,   223,     0,     0,     0,    11,
       0,     9,     0,     8,     0,     0,     0,     0,     0,     0,
      21,    20,    18,     0,     0,    50,     0,     0,     0,   217,
     203,   204,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   211,     0,    13,
      12,    10,     0,     0,     0,     0,    47,    22,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,   112,     0,    65,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   205,   207,
      38,     0,    40,     0,    44,   210,     0,   184,   186,   188,
     189,   193,   194,   191,   192,   196,   197,   199,   200,   201,
     212,   214,     0,    14,    27,     0,    37,     0,     0,     0,
      55,     0,    63,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   205,     0,     0,     0,     0,    33,   219,     0,
       0,     0,     0,     0,   161,   162,     0,     0,     0,     0,
       0,   166,     0,    58,    66,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,     0,     0,     0,     0,    53,     0,    61,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    87,    88,    86,
      89,   218,   213,     0,     0,     0,     0,    51,     0,    59,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     206,     0,     0,    56,    64,     0,    31,   220,   221,     0,
       0,   178,   179,     0,     0,     0,     0,     0,   163,   164,
       0,     0,   127,   128,     0,     0,     0,     0,   135,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,   168,     0,    54,    62,   215,     0,     0,
     177,     0,    52,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,    34,   180,   181,     0,     0,
       0,     0,   129,   130,   131,   132,     0,   137,     0,   138,
       0,   139,     0,   140,     0,   133,     0,     0,     0,     0,
       0,     0,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   171,     0,   160,   123,
     165,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   176,     0,   149,     0,   150,     0,   151,     0,
     152,     0,   145,   159,   120,     0,   172,   174,   175,     0,
       0,     0,     0,     0,     0,   158,   117,   169,   157,   114,
       0,     0,     0,     0,     0,     0,   170,     0,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   173,   141,   142,   143,   144,   134,
     118,   119,   115,   116,     0,     0,     0,     0,     0,   153,
     154,   155,   156,   146
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,   226,    27,    28,   117,   181,    18,    19,    29,    30,
      20,    21,   206,   184,   146,   115,   288,   266,   211,   162,
     289,   267,   212,   163,   164,   291,   269,   214,   165,    22,
     167,   168,   294,   295,   273,   217,   169,   170,   171,   172,
     173,   174,   278,   221,   435,   436,   299,   175,   176,   177,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   137,
     202,    90,    91,    92,   227,    93,    94,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -344
static const short int yypact[] =
{
     220,    -8,    -8,    25,   220,  -344,  -344,  -344,  -344,    19,
      28,  -344,  -344,    -8,    -8,    -8,    -8,  -344,    -8,  -344,
       3,  -344,  -344,   -10,    -8,    -8,  -344,    -8,  -344,   109,
    -344,    51,    -8,    -8,   178,  -344,  -344,    -8,   181,    62,
    -344,   187,    79,  -344,  -344,    87,   246,    -8,    -8,   189,
    -344,    -8,   195,    89,  -344,   219,    98,  -344,  -344,   107,
     293,    -8,   237,   242,  -344,   243,  -344,   303,  -344,   294,
      61,    -8,   138,   136,  -344,  -344,   469,    -8,   469,   469,
     173,   176,   228,   286,   238,   291,   356,  -344,  -344,  -344,
     174,  -344,  -344,  -344,  -344,  -344,    -8,   250,   269,  -344,
     273,  -344,   327,  -344,   354,   264,    -8,   136,   211,   279,
    -344,  -344,  -344,   287,   405,  -344,    77,   235,   232,   223,
    -344,  -344,  -344,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   469,   469,   328,  -344,   281,  -344,
    -344,  -344,   239,   174,   245,   545,  -344,  -344,  -344,   120,
      -8,   248,   260,   280,   283,   285,   302,    47,   321,   331,
    -344,  -344,   448,  -344,  -344,  -344,  -344,  -344,  -344,  -344,
    -344,  -344,  -344,  -344,  -344,  -344,  -344,   295,   322,   744,
    -344,   332,  -344,   490,  -344,  -344,    -8,   228,   286,   238,
     238,   291,   291,   291,   291,   356,   356,  -344,  -344,  -344,
    -344,  -344,   336,  -344,  -344,   584,  -344,   323,   339,    -8,
    -344,   597,  -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,
    -344,  -344,   444,   343,   377,   377,   389,  -344,  -344,   347,
     394,    -8,    -8,   469,  -344,  -344,   469,    -8,   351,   372,
     469,  -344,   229,  -344,  -344,  -344,   380,   384,   469,   469,
     469,   469,   469,   390,   404,   344,   388,   641,   646,   675,
    -344,    -8,   408,   422,   407,  -344,   532,  -344,  -344,  -344,
    -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,
    -344,  -344,  -344,   469,   427,   441,   411,  -344,   636,  -344,
    -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,
     754,   469,   469,  -344,  -344,   174,  -344,  -344,  -344,   447,
     229,  -344,  -344,   465,   467,   326,   442,   223,  -344,  -344,
     477,   430,  -344,  -344,   480,   481,   482,   483,  -344,  -344,
     469,   484,   469,   485,   469,   486,   469,   487,   469,   489,
    -344,   469,   469,  -344,   229,  -344,  -344,  -344,   469,   469,
    -344,   491,  -344,  -344,   492,   494,   680,   685,   714,   719,
     724,   495,   505,    14,  -344,  -344,  -344,  -344,   138,   138,
     496,   509,  -344,  -344,  -344,  -344,   517,  -344,   520,  -344,
     521,  -344,   522,  -344,   526,  -344,   510,   529,   438,   533,
     534,   538,  -344,  -344,   469,   539,   469,   542,   469,   544,
     469,   547,   469,   548,   211,   211,  -344,    -8,  -344,   559,
    -344,  -344,   469,   469,   469,   469,   469,   235,   235,   549,
     245,   245,  -344,   556,  -344,   557,  -344,   560,  -344,   569,
    -344,   572,  -344,  -344,   576,   171,  -344,  -344,   174,     6,
     554,   564,   578,   579,   583,  -344,   608,  -344,  -344,   611,
     469,   469,   469,   469,   469,    92,  -344,    -8,  -344,  -344,
     587,   588,   590,   591,   594,   145,   153,   598,   601,   602,
     603,   605,  -344,  -344,  -344,  -344,  -344,  -344,  -344,  -344,
    -344,  -344,  -344,  -344,   604,   612,   614,   615,   620,  -344,
    -344,  -344,  -344,  -344
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -344,  -344,  -344,   648,  -344,  -344,   652,   638,    93,   656,
     177,  -240,   110,    63,   565,  -344,   165,   166,   208,    54,
     157,   133,  -343,  -301,  -319,  -294,  -344,  -344,  -344,  -344,
     379,   410,   462,   512,  -142,   214,   216,   234,   254,    -4,
    -138,  -179,  -344,  -344,  -344,  -344,  -344,  -111,  -127,  -177,
    -123,  -174,  -344,  -176,  -344,   244,  -344,  -145,  -140,   -11,
    -344,   571,   581,   370,   268,   385,    53,  -344,   -98,   395,
    -344,    -1,  -166,  -104,   396,  -144,  -344,  -344
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   321,   213,   272,   228,   276,   216,   142,   277,
     179,    35,    23,    31,    23,    39,     8,    42,   219,    45,
      35,   156,   220,    31,    53,    11,    56,     8,    59,   298,
      46,    39,    42,    45,   218,    80,    42,    45,   279,   300,
      45,   268,    43,   280,   114,   271,    53,    56,    59,    80,
      56,    59,   229,   239,    59,   406,   275,    13,   179,   407,
      42,    45,    45,   290,    45,   118,    14,   293,    72,   213,
     113,     8,   274,   216,   408,   409,   119,   448,   449,   179,
     307,   308,   297,    58,   219,   433,   434,   272,   220,   276,
      54,    60,   277,   237,   296,    56,    59,    59,   228,    59,
     218,     8,    67,    58,   388,   143,    58,   208,    45,    58,
     166,    54,   298,   178,    54,   182,   445,   446,    50,    69,
     180,   279,   300,   482,   268,   201,   280,    70,   271,   102,
     145,   120,   121,     8,    48,    51,   472,    59,   104,   275,
      50,   215,    74,    75,   222,   458,   290,   105,    57,   230,
     293,    58,    58,    44,    58,   274,   238,    96,   166,    54,
     263,   178,   179,   223,   480,   297,   228,    44,   285,   224,
     225,    44,    34,    38,    44,    41,   114,   296,   116,   270,
      33,    37,   178,   183,    40,   281,   197,   198,   199,    62,
      63,   205,    58,    36,    65,    44,    44,    61,    44,    40,
     228,   292,     8,    40,   222,     8,   123,   215,   238,    36,
     222,     8,   456,     8,   122,   457,   136,    64,   109,     8,
      66,   305,   315,     1,     2,   316,    68,    40,    99,   320,
     313,   314,    49,    52,   101,    55,   317,   324,   325,   326,
     327,    80,    44,     8,   331,   333,   335,   337,   339,   145,
      71,    74,    75,    72,    73,    97,    98,   124,   103,   100,
     340,     8,   270,   127,   128,   178,     8,     8,    74,    75,
       8,   108,   347,   183,     8,   185,   110,   186,   224,   225,
     204,   111,   112,   205,   292,   129,   130,   222,    76,   139,
     361,   362,    77,     8,   231,    78,    79,     8,   106,   107,
     108,    72,    73,     8,   138,     8,   232,    71,   140,   437,
      72,    73,   141,   125,   126,    74,    75,     8,   147,   376,
     203,   378,   233,   380,   234,   382,   235,   384,   148,   149,
     386,   387,   106,   107,   108,    76,   245,   389,   390,    77,
     131,   132,    78,    79,   236,   395,   397,   399,   401,   403,
      74,    75,     8,   246,   247,   248,   249,   250,   251,   437,
     107,   108,   252,   240,   136,   301,    74,    75,     8,   368,
      76,   200,   241,   242,    77,   260,   261,    78,    79,   282,
     283,   302,   330,   423,   306,   425,    76,   427,   311,   429,
      77,   431,   318,    78,    79,   191,   192,   193,   194,    74,
      75,   440,   441,   442,   443,   444,   438,   133,   134,   135,
      74,    75,     8,   319,   150,   151,   152,   153,   154,   155,
     156,   322,   157,   158,   159,   323,   332,    74,    75,     8,
      76,   328,   309,   310,    77,   312,   136,    78,    79,   467,
     468,   469,   470,   471,   160,   329,   161,    76,   343,   344,
     341,    77,   350,   351,    78,    79,   438,   150,   151,   152,
     153,   154,   155,   156,   342,   157,   158,   159,     8,   348,
      74,    75,     8,   371,   310,   246,   247,   248,   249,   250,
     251,   419,   310,   349,   252,   369,   136,   243,   364,   161,
      76,    74,    75,     8,    77,   189,   190,    78,    79,   150,
     151,   152,   262,   154,   155,   263,   366,   157,   367,   159,
     264,    76,    74,    75,     8,    77,   195,   196,    78,    79,
     370,   372,   373,   374,   375,   377,   379,   381,   383,   265,
     385,   161,    76,   392,   391,   393,    77,   410,   404,    78,
      79,   150,   151,   152,   262,   154,   155,   263,   405,   157,
     411,   159,   264,   417,    74,    75,     8,   207,   154,   155,
     208,   412,   209,   158,   413,   414,   415,    74,    75,     8,
     416,   345,   418,   161,    76,   439,   420,   421,    77,   422,
     424,    78,    79,   426,   210,   428,   161,    76,   430,   432,
     447,    77,   455,   460,    78,    79,   284,   154,   155,   285,
     450,   451,   158,   461,   452,   286,    74,    75,     8,   207,
     154,   155,   208,   453,   209,   158,   454,   462,   463,    74,
      75,     8,   464,   287,   465,   161,    76,   466,   475,   476,
      77,   477,   478,    78,    79,   479,   303,   484,   161,    76,
     485,   486,   487,    77,   488,   489,    78,    79,   284,   154,
     155,   285,    12,   490,   158,   491,   492,   286,    74,    75,
       8,   493,    47,    74,    75,     8,    24,   353,    74,    75,
       8,    32,   144,   304,   244,   352,   346,   161,    76,   334,
     483,   481,    77,    76,   336,    78,    79,    77,    76,   473,
      78,    79,    77,   459,   187,    78,    79,    74,    75,     8,
     363,   474,    74,    75,     8,   188,   365,    74,    75,     8,
       0,     0,     0,   338,     0,     0,     0,    76,   394,     0,
       0,    77,    76,   396,    78,    79,    77,    76,     0,    78,
      79,    77,     0,     0,    78,    79,    74,    75,     8,     0,
       0,    74,    75,     8,     0,     0,    74,    75,     8,     0,
       0,     0,   398,     0,     0,     0,    76,   400,     0,     0,
      77,    76,   402,    78,    79,    77,    76,     0,    78,    79,
      77,     0,     0,    78,    79,   253,   254,   255,   256,   257,
     258,     0,     0,     0,   259,   354,   355,   356,   357,   358,
     359,     0,     0,     0,   360
};

static const short int yycheck[] =
{
       1,     2,   242,   145,   183,   149,   183,   145,   106,   183,
     114,    15,    13,    14,    15,    16,    24,    18,   145,    20,
      24,    15,   145,    24,    25,     0,    27,    24,    29,   205,
      40,    32,    33,    34,   145,    46,    37,    38,   183,   205,
      41,   183,    39,   183,    38,   183,    47,    48,    49,    60,
      51,    52,   150,   157,    55,    41,   183,    38,   162,    45,
      61,    62,    63,   205,    65,    76,    38,   205,     7,   211,
      71,    24,   183,   211,   368,   369,    77,   420,   421,   183,
     224,   225,   205,    29,   211,   404,   405,   266,   211,   266,
      27,    40,   266,    46,   205,    96,    97,    98,   242,   100,
     211,    24,    40,    49,   344,   106,    52,    15,   109,    55,
     114,    48,   288,   114,    51,   116,   417,   418,    25,    40,
      43,   266,   288,   466,   266,   136,   266,    40,   266,    40,
      38,    78,    79,    24,    24,    25,   455,   138,    40,   266,
      47,   145,    22,    23,   145,   439,   288,    40,    39,   150,
     288,    97,    98,    20,   100,   266,   157,    47,   162,    96,
      15,   162,   266,    43,   465,   288,   310,    34,    15,    49,
      50,    38,    15,    16,    41,    18,    38,   288,    42,   183,
      15,    16,   183,    38,    18,   186,   133,   134,   135,    32,
      33,    38,   138,    16,    37,    62,    63,    32,    65,    33,
     344,   205,    24,    37,   205,    24,    30,   211,   209,    32,
     211,    24,    41,    24,    41,    44,    42,    39,    61,    24,
      39,   222,   233,     3,     4,   236,    39,    61,    39,   240,
     231,   232,    24,    25,    39,    27,   237,   248,   249,   250,
     251,   252,   109,    24,   255,   256,   257,   258,   259,    38,
       4,    22,    23,     7,     8,    47,    48,    29,    39,    51,
     261,    24,   266,    25,    26,   266,    24,    24,    22,    23,
      24,     7,   283,    38,    24,    43,    39,    54,    49,    50,
      41,    39,    39,    38,   288,    47,    48,   288,    42,    39,
     301,   302,    46,    24,    46,    49,    50,    24,     5,     6,
       7,     7,     8,    24,    96,    24,    46,     4,    39,   407,
       7,     8,    39,    27,    28,    22,    23,    24,    39,   330,
      39,   332,    42,   334,    41,   336,    41,   338,    41,    42,
     341,   342,     5,     6,     7,    42,    41,   348,   349,    46,
      49,    50,    49,    50,    42,   356,   357,   358,   359,   360,
      22,    23,    24,    31,    32,    33,    34,    35,    36,   457,
       6,     7,    40,    42,    42,    42,    22,    23,    24,    43,
      42,    43,    41,    42,    46,    43,    44,    49,    50,    43,
      44,    42,    38,   394,    41,   396,    42,   398,    41,   400,
      46,   402,    41,    49,    50,   127,   128,   129,   130,    22,
      23,   412,   413,   414,   415,   416,   407,    51,    52,    53,
      22,    23,    24,    41,     9,    10,    11,    12,    13,    14,
      15,    41,    17,    18,    19,    41,    38,    22,    23,    24,
      42,    41,    43,    44,    46,    41,    42,    49,    50,   450,
     451,   452,   453,   454,    39,    41,    41,    42,    41,    42,
      42,    46,    41,    42,    49,    50,   457,     9,    10,    11,
      12,    13,    14,    15,    42,    17,    18,    19,    24,    42,
      22,    23,    24,    43,    44,    31,    32,    33,    34,    35,
      36,    43,    44,    42,    40,    43,    42,    39,    41,    41,
      42,    22,    23,    24,    46,   125,   126,    49,    50,     9,
      10,    11,    12,    13,    14,    15,    41,    17,    41,    19,
      20,    42,    22,    23,    24,    46,   131,   132,    49,    50,
      43,    41,    41,    41,    41,    41,    41,    41,    41,    39,
      41,    41,    42,    41,    43,    41,    46,    41,    43,    49,
      50,     9,    10,    11,    12,    13,    14,    15,    43,    17,
      41,    19,    20,    43,    22,    23,    24,    12,    13,    14,
      15,    44,    17,    18,    44,    44,    44,    22,    23,    24,
      44,    39,    43,    41,    42,    16,    43,    43,    46,    41,
      41,    49,    50,    41,    39,    41,    41,    42,    41,    41,
      41,    46,    16,    39,    49,    50,    12,    13,    14,    15,
      44,    44,    18,    39,    44,    21,    22,    23,    24,    12,
      13,    14,    15,    44,    17,    18,    44,    39,    39,    22,
      23,    24,    39,    39,    16,    41,    42,    16,    41,    41,
      46,    41,    41,    49,    50,    41,    39,    39,    41,    42,
      39,    39,    39,    46,    39,    41,    49,    50,    12,    13,
      14,    15,     4,    41,    18,    41,    41,    21,    22,    23,
      24,    41,    24,    22,    23,    24,    14,   288,    22,    23,
      24,    15,   107,   211,   162,    39,   266,    41,    42,    38,
     466,   465,    46,    42,    38,    49,    50,    46,    42,   455,
      49,    50,    46,   439,   123,    49,    50,    22,    23,    24,
     305,   457,    22,    23,    24,   124,   310,    22,    23,    24,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    42,    38,    -1,
      -1,    46,    42,    38,    49,    50,    46,    42,    -1,    49,
      50,    46,    -1,    -1,    49,    50,    22,    23,    24,    -1,
      -1,    22,    23,    24,    -1,    -1,    22,    23,    24,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    42,    38,    -1,    -1,
      46,    42,    38,    49,    50,    46,    42,    -1,    49,    50,
      46,    -1,    -1,    49,    50,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    56,    57,    58,    59,    60,    24,   126,
     126,     0,    58,    38,    38,    61,    64,    65,    71,    72,
      75,    76,    94,   126,    61,    62,    63,    67,    68,    73,
      74,   126,    64,    71,    75,    94,    65,    71,    75,   126,
      72,    75,   126,    39,    76,   126,    40,    62,    67,    73,
      63,    67,    73,   126,    68,    73,   126,    39,    74,   126,
      40,    71,    75,    75,    39,    75,    39,    40,    39,    40,
      40,     4,     7,     8,    22,    23,    42,    46,    49,    50,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     126,   127,   128,   130,   131,   132,    67,    73,    73,    39,
      73,    39,    40,    39,    40,    40,     5,     6,     7,    75,
      39,    39,    39,   126,    38,    80,    42,    69,   114,   126,
     121,   121,    41,    30,    29,    27,    28,    25,    26,    47,
      48,    49,    50,    51,    52,    53,    42,   124,    73,    39,
      39,    39,   123,   126,    69,    38,    79,    39,    41,    42,
       9,    10,    11,    12,    13,    14,    15,    17,    18,    19,
      39,    41,    84,    88,    89,    93,    94,    95,    96,   101,
     102,   103,   104,   105,   106,   112,   113,   114,   126,   128,
      43,    70,   126,    38,    78,    43,    54,   116,   117,   118,
     118,   119,   119,   119,   119,   120,   120,   121,   121,   121,
      43,   114,   125,    39,    41,    38,    77,    12,    15,    17,
      39,    83,    87,    89,    92,    94,    95,   100,   102,   103,
     105,   108,   126,    43,    49,    50,    66,   129,   130,   123,
     126,    46,    46,    42,    41,    41,    42,    46,   126,   128,
      42,    41,    42,    39,    88,    41,    31,    32,    33,    34,
      35,    36,    40,    31,    32,    33,    34,    35,    36,    40,
      43,    44,    12,    15,    20,    39,    82,    86,    89,    91,
      94,    95,    96,    99,   102,   103,   104,   106,   107,   112,
     113,   126,    43,    44,    12,    15,    21,    39,    81,    85,
      89,    90,    94,    95,    97,    98,   102,   105,   108,   111,
     127,    42,    42,    39,    87,   126,    41,   130,   130,    43,
      44,    41,    41,   126,   126,   114,   114,   126,    41,    41,
     114,    66,    41,    41,   114,   114,   114,   114,    41,    41,
      38,   114,    38,   114,    38,   114,    38,   114,    38,   114,
     126,    42,    42,    41,    42,    39,    86,   114,    42,    42,
      41,    42,    39,    85,    31,    32,    33,    34,    35,    36,
      40,   114,   114,   124,    41,   129,    41,    41,    43,    43,
      43,    43,    41,    41,    41,    41,   114,    41,   114,    41,
     114,    41,   114,    41,   114,    41,   114,   114,    66,   114,
     114,    43,    41,    41,    38,   114,    38,   114,    38,   114,
      38,   114,    38,   114,    43,    43,    41,    45,    80,    80,
      41,    41,    44,    44,    44,    44,    44,    43,    43,    43,
      43,    43,    41,   114,    41,   114,    41,   114,    41,   114,
      41,   114,    41,    79,    79,   109,   110,   123,   126,    16,
     114,   114,   114,   114,   114,    78,    78,    41,    77,    77,
      44,    44,    44,    44,    44,    16,    41,    44,    80,    93,
      39,    39,    39,    39,    39,    16,    16,   114,   114,   114,
     114,   114,    79,    92,   110,    41,    41,    41,    41,    41,
      78,    91,    77,    90,    39,    39,    39,    39,    39,    41,
      41,    41,    41,    41
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
#line 165 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 172 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 176 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 185 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 189 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 196 "BulletParser.y"
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
#line 207 "BulletParser.y"
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
#line 218 "BulletParser.y"
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
#line 229 "BulletParser.y"
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
#line 240 "BulletParser.y"
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
#line 251 "BulletParser.y"
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
#line 262 "BulletParser.y"
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
#line 273 "BulletParser.y"
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
#line 287 "BulletParser.y"
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
#line 298 "BulletParser.y"
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
#line 309 "BulletParser.y"
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
#line 320 "BulletParser.y"
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
#line 331 "BulletParser.y"
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
#line 342 "BulletParser.y"
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
#line 353 "BulletParser.y"
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
#line 364 "BulletParser.y"
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
#line 378 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 382 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 391 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 395 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 404 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
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
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 426 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 31:
#line 432 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-3]));
		;}
    break;

  case 32:
#line 438 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 33:
#line 448 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 34:
#line 452 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 35:
#line 461 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 465 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 37:
#line 474 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 38:
#line 484 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 39:
#line 488 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 40:
#line 495 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 41:
#line 500 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 42:
#line 512 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 516 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 525 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 45:
#line 536 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 540 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 549 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 48:
#line 558 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 562 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 571 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 580 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 52:
#line 584 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 53:
#line 591 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 54:
#line 595 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 55:
#line 602 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 56:
#line 606 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 57:
#line 613 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 58:
#line 617 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 59:
#line 624 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 628 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 61:
#line 637 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 641 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 650 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 654 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 65:
#line 663 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 667 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 67:
#line 676 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 680 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 684 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 688 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 692 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 696 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 700 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 704 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 708 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 712 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 719 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 723 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 727 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 731 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 735 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 739 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 743 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 747 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 751 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 755 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 759 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 763 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 767 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 774 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 778 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 782 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 786 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 790 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 794 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 798 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 802 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 806 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 813 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 817 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 821 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 825 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 829 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 833 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 837 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 841 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 845 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 849 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 853 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 857 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 861 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 112:
#line 868 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 113:
#line 872 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 114:
#line 879 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 115:
#line 885 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 116:
#line 892 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 117:
#line 902 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 118:
#line 908 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 119:
#line 915 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 120:
#line 925 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 121:
#line 931 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 122:
#line 938 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 123:
#line 948 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 124:
#line 954 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 125:
#line 961 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 126:
#line 971 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 127:
#line 980 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 128:
#line 985 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 129:
#line 990 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 130:
#line 995 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 131:
#line 1000 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 132:
#line 1005 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1013 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 134:
#line 1019 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 135:
#line 1026 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 136:
#line 1031 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 137:
#line 1036 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 138:
#line 1041 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 139:
#line 1046 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 140:
#line 1051 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1056 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1062 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 143:
#line 1068 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 144:
#line 1074 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 145:
#line 1083 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 146:
#line 1089 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1096 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 148:
#line 1101 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 149:
#line 1106 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 150:
#line 1111 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 151:
#line 1116 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 152:
#line 1121 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 153:
#line 1126 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 154:
#line 1132 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 155:
#line 1138 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 156:
#line 1144 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 157:
#line 1153 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 158:
#line 1162 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 159:
#line 1171 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 160:
#line 1180 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 161:
#line 1189 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 162:
#line 1193 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 163:
#line 1200 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 164:
#line 1208 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 165:
#line 1216 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 166:
#line 1224 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
		;}
    break;

  case 167:
#line 1228 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 168:
#line 1235 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
		;}
    break;

  case 169:
#line 1239 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 170:
#line 1247 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 171:
#line 1257 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 172:
#line 1269 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 173:
#line 1273 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 174:
#line 1282 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 175:
#line 1286 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 176:
#line 1294 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 177:
#line 1298 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 178:
#line 1305 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 179:
#line 1310 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 180:
#line 1318 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 181:
#line 1324 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 182:
#line 1333 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 183:
#line 1341 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 184:
#line 1345 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 185:
#line 1354 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 186:
#line 1358 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1367 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 188:
#line 1371 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 189:
#line 1377 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 190:
#line 1386 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 191:
#line 1390 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 192:
#line 1396 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1402 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1408 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 195:
#line 1417 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 196:
#line 1421 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 197:
#line 1427 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1436 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 199:
#line 1440 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 200:
#line 1446 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 201:
#line 1452 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 202:
#line 1461 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 203:
#line 1465 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1470 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1478 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 206:
#line 1482 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1486 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 208:
#line 1490 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 209:
#line 1494 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1498 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 211:
#line 1505 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 212:
#line 1514 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 213:
#line 1518 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 214:
#line 1525 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 215:
#line 1530 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 216:
#line 1542 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 217:
#line 1550 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 218:
#line 1559 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 219:
#line 1570 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 220:
#line 1574 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 221:
#line 1578 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 222:
#line 1586 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 223:
#line 1590 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 224:
#line 1597 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 225:
#line 1605 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3700 "bsBulletParser.cpp"

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


#line 1611 "BulletParser.y"


	
	

