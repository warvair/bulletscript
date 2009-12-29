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
     KEYWORD_CONSTANT = 258,
     KEYWORD_CONTROLLER = 259,
     KEYWORD_EMITTER = 260,
     KEYWORD_AFFECTOR = 261,
     KEYWORD_FUNCTION = 262,
     KEYWORD_STATE = 263,
     KEYWORD_EVENT = 264,
     KEYWORD_RAISE = 265,
     KEYWORD_ENABLE = 266,
     KEYWORD_DISABLE = 267,
     KEYWORD_WHILE = 268,
     KEYWORD_BREAK = 269,
     KEYWORD_CONTINUE = 270,
     KEYWORD_IF = 271,
     KEYWORD_ELSE = 272,
     KEYWORD_GOTO = 273,
     KEYWORD_WAIT = 274,
     KEYWORD_SUSPEND = 275,
     KEYWORD_SIGNAL = 276,
     KEYWORD_DIE = 277,
     INTEGER = 278,
     REAL = 279,
     IDENTIFIER = 280,
     SYMBOL_LTE = 281,
     SYMBOL_GTE = 282,
     SYMBOL_EQ = 283,
     SYMBOL_NEQ = 284,
     SYMBOL_LOG_AND = 285,
     SYMBOL_LOG_OR = 286,
     SYMBOL_INC = 287,
     SYMBOL_DEC = 288,
     SYMBOL_ADD_A = 289,
     SYMBOL_SUB_A = 290,
     SYMBOL_MUL_A = 291,
     SYMBOL_DIV_A = 292,
     TOKEN_ERROR = 293
   };
#endif
/* Tokens.  */
#define KEYWORD_CONSTANT 258
#define KEYWORD_CONTROLLER 259
#define KEYWORD_EMITTER 260
#define KEYWORD_AFFECTOR 261
#define KEYWORD_FUNCTION 262
#define KEYWORD_STATE 263
#define KEYWORD_EVENT 264
#define KEYWORD_RAISE 265
#define KEYWORD_ENABLE 266
#define KEYWORD_DISABLE 267
#define KEYWORD_WHILE 268
#define KEYWORD_BREAK 269
#define KEYWORD_CONTINUE 270
#define KEYWORD_IF 271
#define KEYWORD_ELSE 272
#define KEYWORD_GOTO 273
#define KEYWORD_WAIT 274
#define KEYWORD_SUSPEND 275
#define KEYWORD_SIGNAL 276
#define KEYWORD_DIE 277
#define INTEGER 278
#define REAL 279
#define IDENTIFIER 280
#define SYMBOL_LTE 281
#define SYMBOL_GTE 282
#define SYMBOL_EQ 283
#define SYMBOL_NEQ 284
#define SYMBOL_LOG_AND 285
#define SYMBOL_LOG_OR 286
#define SYMBOL_INC 287
#define SYMBOL_DEC 288
#define SYMBOL_ADD_A 289
#define SYMBOL_SUB_A 290
#define SYMBOL_MUL_A 291
#define SYMBOL_DIV_A 292
#define TOKEN_ERROR 293




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

static const String gs_tokens[] = {
	"KEYWORD_CONSTANT",					"constant",
	"KEYWORD_CONTROLLER",				"controller",
	"KEYWORD_EMITTER",					"emitter",
	"KEYWORD_AFFECTOR",					"affector",
	"KEYWORD_FUNCTION",					"function",
	"KEYWORD_STATE",					"state",
	"KEYWORD_EVENT",					"event",
	"KEYWORD_RAISE",					"raise",
	"KEYWORD_ENABLE",					"enable",
	"KEYWORD_DISABLE",					"disable",
	"KEYWORD_WHILE",					"while",
	"KEYWORD_BREAK",					"break",
	"KEYWORD_CONTINUE",					"continue",
	"KEYWORD_IF",						"if",
	"KEYWORD_GOTO",						"goto",
	"KEYWORD_WAIT",						"wait",	
	"KEYWORD_ELSE",						"else",
	"KEYWORD_SUSPEND",					"suspend",
	"KEYWORD_SIGNAL",					"signal",
	"KEYWORD_DIE",						"die",
	"INTEGER",							"integral value",
	"REAL",								"value",
	"IDENTIFIER",						"identifier",
	"SYMBOL_LTE",						"<=",
	"SYMBOL_GTE",						">=",
	"SYMBOL_EQ",						"==",
	"SYMBOL_NEQ",						"!=",
	"SYMBOL_LOG_AND",					"&&",
	"SYMBOL_LOG_OR",					"||",
	"SYMBOL_INC",						"++",
	"SYMBOL_DEC",						"--",
	"SYMBOL_ADD_A",						"+=",
	"SYMBOL_SUB_A",						"-=",
	"SYMBOL_MUL_A",						"*=",
	"SYMBOL_DIV_A",						"/=",
};

void replaceVerboseTokens(String& a_string)
{
	for (int i = 0; i < 70; i += 2)
	{
		int startPos = (int) a_string.find(gs_tokens[i]);
		if (startPos < 0)
			continue;

		size_t count = gs_tokens[i].length();

		a_string.replace(startPos, count, gs_tokens[i + 1]);
	}
}

void yyerror (char *a_msg)
{
	String msgString = a_msg;
	replaceVerboseTokens(msgString);

	AST->addError(yylineno, msgString);
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
#line 351 "bsBulletParser.cpp"

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   827

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  80
/* YYNRULES -- Number of rules. */
#define YYNRULES  228
/* YYNRULES -- Number of states. */
#define YYNSTATES  501

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    47,    54,     2,     2,
      43,    44,    52,    50,    45,    51,    55,    53,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    40,
      48,    39,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    19,    21,    24,
      26,    28,    34,    41,    48,    56,    63,    71,    79,    88,
      94,   101,   108,   116,   123,   131,   139,   148,   150,   153,
     155,   158,   164,   166,   169,   175,   184,   186,   190,   192,
     195,   201,   204,   208,   210,   214,   216,   219,   225,   227,
     230,   235,   237,   240,   245,   248,   252,   255,   259,   262,
     266,   269,   273,   275,   278,   280,   283,   285,   288,   290,
     293,   295,   297,   299,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   321,   323,   325,   327,   329,   331,
     333,   335,   337,   339,   341,   343,   345,   347,   349,   351,
     353,   355,   357,   359,   361,   363,   365,   367,   369,   371,
     373,   375,   377,   379,   381,   383,   385,   388,   394,   402,
     410,   416,   424,   432,   438,   446,   454,   460,   468,   476,
     481,   485,   489,   494,   499,   504,   509,   514,   523,   527,
     531,   536,   541,   546,   551,   560,   569,   578,   587,   592,
     601,   605,   609,   614,   619,   624,   629,   638,   647,   656,
     665,   671,   677,   683,   689,   692,   695,   699,   703,   709,
     712,   718,   721,   727,   734,   739,   741,   745,   747,   749,
     751,   754,   758,   762,   767,   772,   774,   776,   780,   782,
     786,   788,   792,   796,   798,   802,   806,   810,   814,   816,
     820,   824,   826,   830,   834,   838,   840,   843,   846,   848,
     850,   852,   854,   856,   860,   863,   866,   870,   872,   876,
     878,   881,   886,   888,   891,   894,   896,   898,   900
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      57,     0,    -1,    60,    -1,    58,    60,    -1,    59,    -1,
      58,    59,    -1,   129,    39,     3,   132,    40,    -1,    61,
      -1,    60,    61,    -1,    62,    -1,    63,    -1,     5,   129,
      41,    76,    42,    -1,     5,   129,    41,    70,    76,    42,
      -1,     5,   129,    41,    65,    76,    42,    -1,     5,   129,
      41,    65,    70,    76,    42,    -1,     5,   129,    41,    64,
      76,    42,    -1,     5,   129,    41,    64,    70,    76,    42,
      -1,     5,   129,    41,    64,    65,    76,    42,    -1,     5,
     129,    41,    64,    65,    70,    76,    42,    -1,     4,   129,
      41,    78,    42,    -1,     4,   129,    41,    74,    78,    42,
      -1,     4,   129,    41,    67,    78,    42,    -1,     4,   129,
      41,    67,    74,    78,    42,    -1,     4,   129,    41,    64,
      78,    42,    -1,     4,   129,    41,    64,    74,    78,    42,
      -1,     4,   129,    41,    64,    67,    78,    42,    -1,     4,
     129,    41,    64,    67,    74,    78,    42,    -1,    97,    -1,
      64,    97,    -1,    66,    -1,    65,    66,    -1,   129,    39,
       6,   126,    40,    -1,    68,    -1,    67,    68,    -1,   129,
      39,     5,   129,    40,    -1,   129,    39,     5,   129,    43,
      69,    44,    40,    -1,   132,    -1,    69,    45,   132,    -1,
      71,    -1,    70,    71,    -1,   129,    39,     7,    72,    80,
      -1,    43,    44,    -1,    43,    73,    44,    -1,   129,    -1,
      73,    45,   129,    -1,    75,    -1,    74,    75,    -1,   129,
      39,     9,    72,    81,    -1,    77,    -1,    76,    77,    -1,
     129,    39,     8,    82,    -1,    79,    -1,    78,    79,    -1,
     129,    39,     8,    83,    -1,    41,    42,    -1,    41,    84,
      42,    -1,    41,    42,    -1,    41,    85,    42,    -1,    41,
      42,    -1,    41,    86,    42,    -1,    41,    42,    -1,    41,
      87,    42,    -1,    88,    -1,    84,    88,    -1,    89,    -1,
      85,    89,    -1,    90,    -1,    86,    90,    -1,    91,    -1,
      87,    91,    -1,    92,    -1,    93,    -1,    97,    -1,    98,
      -1,   100,    -1,   101,    -1,   105,    -1,   108,    -1,   111,
      -1,   114,    -1,    92,    -1,    94,    -1,    97,    -1,    98,
      -1,    99,    -1,   102,    -1,   105,    -1,   106,    -1,   107,
      -1,   115,    -1,   109,    -1,   110,    -1,   116,    -1,    92,
      -1,    95,    -1,    97,    -1,    98,    -1,   103,    -1,   105,
      -1,   106,    -1,   108,    -1,   111,    -1,    92,    -1,    96,
      -1,    97,    -1,    98,    -1,    99,    -1,   104,    -1,   105,
      -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,   115,
      -1,   116,    -1,    40,    -1,   117,    40,    -1,    16,    43,
     117,    44,    80,    -1,    16,    43,   117,    44,    80,    17,
      80,    -1,    16,    43,   117,    44,    80,    17,    93,    -1,
      16,    43,   117,    44,    81,    -1,    16,    43,   117,    44,
      81,    17,    81,    -1,    16,    43,   117,    44,    81,    17,
      94,    -1,    16,    43,   117,    44,    82,    -1,    16,    43,
     117,    44,    82,    17,    82,    -1,    16,    43,   117,    44,
      82,    17,    95,    -1,    16,    43,   117,    44,    83,    -1,
      16,    43,   117,    44,    83,    17,    83,    -1,    16,    43,
     117,    44,    83,    17,    96,    -1,   129,    39,   117,    40,
      -1,   129,    32,    40,    -1,   129,    33,    40,    -1,   129,
      34,   117,    40,    -1,   129,    35,   117,    40,    -1,   129,
      36,   117,    40,    -1,   129,    37,   117,    40,    -1,   131,
      39,   117,    40,    -1,   131,    39,    41,   117,    45,   117,
      42,    40,    -1,   131,    32,    40,    -1,   131,    33,    40,
      -1,   131,    34,   117,    40,    -1,   131,    35,   117,    40,
      -1,   131,    36,   117,    40,    -1,   131,    37,   117,    40,
      -1,   131,    34,    41,   117,    45,   117,    42,    40,    -1,
     131,    35,    41,   117,    45,   117,    42,    40,    -1,   131,
      36,    41,   117,    45,   117,    42,    40,    -1,   131,    37,
      41,   117,    45,   117,    42,    40,    -1,   130,    39,   117,
      40,    -1,   130,    39,    41,   117,    45,   117,    42,    40,
      -1,   130,    32,    40,    -1,   130,    33,    40,    -1,   130,
      34,   117,    40,    -1,   130,    35,   117,    40,    -1,   130,
      36,   117,    40,    -1,   130,    37,   117,    40,    -1,   130,
      34,    41,   117,    45,   117,    42,    40,    -1,   130,    35,
      41,   117,    45,   117,    42,    40,    -1,   130,    36,    41,
     117,    45,   117,    42,    40,    -1,   130,    37,    41,   117,
      45,   117,    42,    40,    -1,    13,    43,   117,    44,    80,
      -1,    13,    43,   117,    44,    81,    -1,    13,    43,   117,
      44,    82,    -1,    13,    43,   117,    44,    83,    -1,    14,
      40,    -1,    15,    40,    -1,    18,   129,    40,    -1,    18,
     131,    40,    -1,    19,    43,   117,    44,    40,    -1,    20,
      40,    -1,    20,    43,    69,    44,    40,    -1,    21,    40,
      -1,    21,    43,    69,    44,    40,    -1,   129,   129,   127,
      46,   112,    40,    -1,   129,   129,   127,    40,    -1,   113,
      -1,   112,    45,   113,    -1,   126,    -1,   129,    -1,   130,
      -1,    22,    40,    -1,    10,   126,    40,    -1,    10,   129,
      40,    -1,    11,    47,   129,    40,    -1,    12,    47,   129,
      40,    -1,   118,    -1,   119,    -1,   118,    31,   119,    -1,
     120,    -1,   119,    30,   120,    -1,   121,    -1,   120,    28,
     121,    -1,   120,    29,   121,    -1,   122,    -1,   121,    48,
     122,    -1,   121,    49,   122,    -1,   121,    26,   122,    -1,
     121,    27,   122,    -1,   123,    -1,   122,    50,   123,    -1,
     122,    51,   123,    -1,   124,    -1,   123,    52,   124,    -1,
     123,    53,   124,    -1,   123,    54,   124,    -1,   125,    -1,
      50,   124,    -1,    51,   124,    -1,   129,    -1,   130,    -1,
     131,    -1,   126,    -1,   133,    -1,    43,   117,    44,    -1,
     129,   127,    -1,    43,    44,    -1,    43,   128,    44,    -1,
     117,    -1,   128,    45,   117,    -1,    25,    -1,    47,   129,
      -1,    47,   129,    55,   129,    -1,   133,    -1,    50,   133,
      -1,    51,   133,    -1,   134,    -1,   135,    -1,    23,    -1,
      24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   220,   220,   224,   232,   236,   245,   254,   258,   267,
     271,   278,   289,   300,   311,   322,   333,   344,   355,   369,
     380,   391,   402,   413,   424,   435,   446,   460,   464,   473,
     477,   486,   495,   499,   508,   514,   524,   528,   537,   541,
     550,   560,   564,   571,   576,   588,   592,   601,   612,   616,
     625,   634,   638,   647,   656,   660,   667,   671,   678,   682,
     689,   693,   700,   704,   713,   717,   726,   730,   739,   743,
     752,   756,   760,   764,   768,   772,   776,   780,   784,   788,
     795,   799,   803,   807,   811,   815,   819,   823,   827,   831,
     835,   839,   843,   850,   854,   858,   862,   866,   870,   874,
     878,   882,   889,   893,   897,   901,   905,   909,   913,   917,
     921,   925,   929,   933,   937,   944,   948,   955,   961,   968,
     978,   984,   991,  1001,  1007,  1014,  1024,  1030,  1037,  1047,
    1056,  1061,  1066,  1071,  1076,  1081,  1089,  1095,  1102,  1107,
    1112,  1117,  1122,  1127,  1132,  1138,  1144,  1150,  1159,  1165,
    1172,  1177,  1182,  1187,  1192,  1197,  1202,  1208,  1214,  1220,
    1229,  1238,  1247,  1256,  1265,  1269,  1276,  1284,  1292,  1300,
    1304,  1311,  1315,  1323,  1333,  1345,  1349,  1358,  1362,  1367,
    1374,  1381,  1386,  1394,  1400,  1409,  1417,  1421,  1430,  1434,
    1443,  1447,  1453,  1462,  1466,  1472,  1478,  1484,  1493,  1497,
    1503,  1512,  1516,  1522,  1528,  1537,  1541,  1546,  1554,  1558,
    1562,  1566,  1570,  1574,  1581,  1590,  1594,  1601,  1606,  1618,
    1626,  1635,  1646,  1650,  1654,  1662,  1666,  1673,  1681
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_CONSTANT", "KEYWORD_CONTROLLER",
  "KEYWORD_EMITTER", "KEYWORD_AFFECTOR", "KEYWORD_FUNCTION",
  "KEYWORD_STATE", "KEYWORD_EVENT", "KEYWORD_RAISE", "KEYWORD_ENABLE",
  "KEYWORD_DISABLE", "KEYWORD_WHILE", "KEYWORD_BREAK", "KEYWORD_CONTINUE",
  "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT",
  "KEYWORD_SUSPEND", "KEYWORD_SIGNAL", "KEYWORD_DIE", "INTEGER", "REAL",
  "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ",
  "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC",
  "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A",
  "TOKEN_ERROR", "'='", "';'", "'{'", "'}'", "'('", "')'", "','", "':'",
  "'$'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'.'", "$accept",
  "script_file", "constantdef_list", "constantdef", "definition_list",
  "definition", "emitter_definition", "controller_definition",
  "member_list", "affector_list", "affector_declaration", "emitter_list",
  "emitter", "constant_arg_list", "function_list", "function",
  "function_arguments", "argument_list", "event_list", "event",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,    61,
      59,   123,   125,    40,    41,    44,    58,    36,    60,    62,
      43,    45,    42,    47,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    56,    57,    57,    58,    58,    59,    60,    60,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    72,    72,    73,    73,    74,    74,    75,    76,    76,
      77,    78,    78,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    92,    93,    93,    93,
      94,    94,    94,    95,    95,    95,    96,    96,    96,    97,
      98,    98,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     101,   102,   103,   104,   105,   105,   106,   107,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   113,
     114,   115,   115,   116,   116,   117,   118,   118,   119,   119,
     120,   120,   120,   121,   121,   121,   121,   121,   122,   122,
     122,   123,   123,   123,   123,   124,   124,   124,   125,   125,
     125,   125,   125,   125,   126,   127,   127,   128,   128,   129,
     130,   131,   132,   132,   132,   133,   133,   134,   135
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     2,     5,     1,     2,     1,
       1,     5,     6,     6,     7,     6,     7,     7,     8,     5,
       6,     6,     7,     6,     7,     7,     8,     1,     2,     1,
       2,     5,     1,     2,     5,     8,     1,     3,     1,     2,
       5,     2,     3,     1,     3,     1,     2,     5,     1,     2,
       4,     1,     2,     4,     2,     3,     2,     3,     2,     3,
       2,     3,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     5,     7,     7,
       5,     7,     7,     5,     7,     7,     5,     7,     7,     4,
       3,     3,     4,     4,     4,     4,     4,     8,     3,     3,
       4,     4,     4,     4,     8,     8,     8,     8,     4,     8,
       3,     3,     4,     4,     4,     4,     8,     8,     8,     8,
       5,     5,     5,     5,     2,     2,     3,     3,     5,     2,
       5,     2,     5,     6,     4,     1,     3,     1,     1,     1,
       2,     3,     3,     4,     4,     1,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     1,     3,     2,     2,     3,     1,     3,     1,
       2,     4,     1,     2,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,   219,     0,     0,     4,     2,     7,     9,
      10,     0,     0,     0,     1,     5,     3,     8,     0,     0,
       0,     0,     0,     0,    32,     0,    45,     0,    51,    27,
       0,     0,     0,    29,     0,    38,     0,    48,     0,   227,
     228,     0,     0,     0,   222,   225,   226,     0,     0,     0,
      28,    33,     0,     0,     0,    46,     0,     0,    19,    52,
       0,     0,     0,     0,     0,    30,     0,     0,     0,    39,
       0,     0,    11,    49,     0,     0,   223,   224,     6,     0,
       0,     0,    23,     0,    21,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   185,   186,   188,
     190,   193,   198,   201,   205,   211,   208,   209,   210,   212,
       0,     0,     0,    15,     0,    13,     0,    12,     0,     0,
       0,     0,     0,     0,    25,    24,    22,     0,     0,    53,
       0,     0,     0,   220,   206,   207,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   214,     0,    17,    16,    14,     0,     0,     0,     0,
      50,    26,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,    60,     0,    68,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,     0,   208,   210,    41,     0,    43,     0,    47,   213,
       0,   187,   189,   191,   192,   196,   197,   194,   195,   199,
     200,   202,   203,   204,   215,   217,     0,    18,    31,     0,
      40,     0,     0,     0,    58,     0,    66,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   208,     0,    36,     0,
       0,     0,     0,     0,   164,   165,     0,     0,     0,     0,
       0,   169,     0,    61,    69,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,    56,     0,    64,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    90,    91,    89,
      92,   221,   216,     0,     0,     0,     0,    54,     0,    62,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
     209,     0,     0,    59,    67,     0,     0,     0,   181,   182,
       0,     0,     0,     0,     0,   166,   167,     0,     0,   130,
     131,     0,     0,     0,     0,   138,   139,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
     171,     0,    57,    65,   218,     0,     0,   180,    55,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    37,   183,   184,     0,     0,     0,     0,   132,   133,
     134,   135,     0,   140,     0,   141,     0,   142,     0,   143,
       0,   136,     0,     0,     0,     0,     0,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,     0,   163,   126,   168,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
     153,     0,   154,     0,   155,     0,   148,   162,   123,     0,
       0,   175,   177,   178,   179,     0,     0,     0,     0,     0,
       0,   161,   120,   172,   160,   117,     0,     0,     0,     0,
       0,     0,   220,   173,     0,   127,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   124,
     125,   176,   144,   145,   146,   147,   137,   121,   122,   118,
     119,     0,     0,     0,     0,     0,   156,   157,   158,   159,
     149
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    10,    22,    32,
      33,    23,    24,   237,    34,    35,   131,   195,    25,    26,
      36,    37,    27,    28,   220,   198,   160,   129,   298,   276,
     225,   176,   299,   277,   226,   177,   178,   301,   279,   228,
     179,    29,   181,   182,   304,   305,   283,   231,   183,   184,
     185,   186,   187,   188,   288,   235,   440,   441,   309,   189,
     190,   191,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   151,   216,   106,   107,   108,   238,   109,    45,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -360
static const short int yypact[] =
{
     223,   -11,   -11,  -360,    35,   223,  -360,   309,  -360,  -360,
    -360,    20,    28,    67,  -360,  -360,   309,  -360,    58,   -11,
     -11,   167,   -11,   -11,  -360,   -11,  -360,   128,  -360,  -360,
     105,   -11,   -11,  -360,   -11,  -360,   156,  -360,   133,  -360,
    -360,   296,   296,   146,  -360,  -360,  -360,   -11,   -11,   201,
    -360,  -360,   -11,   204,   145,  -360,   212,   183,  -360,  -360,
     192,   333,   -11,   -11,   219,  -360,   -11,   220,   199,  -360,
     224,   231,  -360,  -360,   245,   384,  -360,  -360,  -360,   -11,
     225,   238,  -360,   239,  -360,   370,  -360,   402,   187,   -11,
     236,   263,   293,   -11,   293,   293,   257,   297,   258,   385,
     161,   382,   347,  -360,  -360,  -360,   287,  -360,  -360,  -360,
     -11,   240,   244,  -360,   248,  -360,   430,  -360,   433,   327,
     -11,   263,   305,   250,  -360,  -360,  -360,    55,   405,  -360,
      -1,   307,   306,   282,  -360,  -360,  -360,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   293,   293,   293,
     209,  -360,   254,  -360,  -360,  -360,   312,   287,   313,   544,
    -360,  -360,  -360,   167,   -11,   321,   326,   334,   341,   348,
     343,   -21,   379,    86,  -360,  -360,   447,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,   386,   290,   483,  -360,   398,  -360,   489,  -360,  -360,
     -11,   258,   385,   161,   161,   382,   382,   382,   382,   347,
     347,  -360,  -360,  -360,  -360,  -360,   406,  -360,  -360,   583,
    -360,   401,   403,   -11,  -360,   596,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,   443,   409,  -360,   441,
     342,   -11,   -11,   293,  -360,  -360,   293,   -11,   445,   448,
     293,  -360,   167,  -360,  -360,  -360,   453,   466,   293,   293,
     293,   293,   293,   468,   471,   346,   640,   669,   674,   703,
    -360,   -11,   426,   478,   355,  -360,   531,  -360,  -360,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,  -360,  -360,   293,   490,   492,   494,  -360,   635,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
     491,   293,   293,  -360,  -360,   287,   497,   167,  -360,  -360,
     498,   508,   506,   509,   282,  -360,  -360,   517,   429,  -360,
    -360,   524,   525,   526,   530,  -360,  -360,   293,   532,   293,
     535,   293,   536,   293,   537,   293,   539,  -360,   293,   293,
    -360,   167,  -360,  -360,  -360,   293,   293,  -360,  -360,  -360,
     540,   543,   708,   737,   742,   771,   776,   541,   545,   228,
    -360,  -360,  -360,  -360,   236,   236,   548,   550,  -360,  -360,
    -360,  -360,   404,  -360,   547,  -360,   555,  -360,   556,  -360,
     558,  -360,   549,   560,   439,   569,   572,  -360,  -360,   293,
     577,   293,   578,   293,   582,   293,   584,   293,   587,   305,
     305,  -360,    99,  -360,   611,  -360,  -360,   293,   293,   293,
     293,   293,   307,   307,   589,   313,   313,   586,  -360,   590,
    -360,   592,  -360,   595,  -360,   597,  -360,  -360,   615,   -11,
     190,  -360,  -360,   287,  -360,    72,   599,   602,   603,   610,
     613,  -360,   636,  -360,  -360,   639,   293,   293,   293,   293,
     293,   134,  -360,  -360,    99,  -360,  -360,   621,   622,   626,
     627,   628,   142,   144,   629,   630,   631,   632,   634,  -360,
    -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,  -360,
    -360,   644,   648,   649,   655,   656,  -360,  -360,  -360,  -360,
    -360
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -360,  -360,  -360,   664,   665,    90,  -360,  -360,   659,   670,
       9,   658,    10,  -242,    69,    24,   579,  -360,    94,   115,
     111,    68,   114,   251,  -257,  -350,  -359,  -330,  -360,  -360,
    -360,  -360,   407,   427,   477,   528,  -151,   233,   235,   247,
     264,    96,  -143,  -185,  -360,  -360,  -360,  -360,  -360,  -120,
    -122,  -184,  -141,  -182,  -360,  -191,  -360,   249,  -360,  -157,
    -155,   -54,  -360,   574,   576,   352,   218,   350,    54,  -360,
    -109,   408,  -360,     0,  -213,  -111,   -18,   -12,  -360,  -360
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
      11,    12,    13,    43,     3,    11,   310,    96,   227,    44,
     328,   156,   282,   286,     3,   287,   230,   193,   234,    30,
      38,    96,    30,    54,     3,    57,   247,    60,   308,    76,
      77,    38,    68,    51,    71,    14,    74,   233,   132,   232,
     289,    65,   290,   194,   413,   414,   278,    54,    57,    60,
     437,   438,    57,    60,   281,   239,    60,    51,    69,    18,
     249,    21,    68,    71,    74,   193,    71,    74,   300,    19,
      74,    65,   451,   452,   227,   285,   303,   284,   307,    57,
      60,    60,   230,    60,   234,   310,   193,    69,   170,   127,
      69,   282,   286,   133,   287,   162,   215,    17,   163,   306,
      63,    66,   479,   233,    73,   232,    17,   308,    20,   394,
      71,    74,    74,   128,    74,   465,    48,    52,    50,   289,
     157,   290,   487,    60,     3,   278,   251,    50,   192,   252,
     196,   110,    73,   281,    69,    73,    49,    53,    73,    56,
      55,    79,    64,    67,    61,    70,   439,   300,   134,   135,
     222,    44,    74,     3,   285,   303,   284,   307,   273,   236,
     295,    80,    81,    55,   240,   193,    83,    55,   454,   455,
      58,   248,    75,   111,   112,   159,   192,   114,   306,    73,
      73,     3,    73,   197,    85,   219,    78,   141,   142,   322,
      39,    40,   323,   123,    55,    90,   327,   192,    72,   444,
     291,   211,   212,   213,   331,   332,   333,   334,    96,   143,
     144,   338,   340,   342,   344,   346,   489,    41,    42,   236,
      73,   152,    87,   248,   180,   236,     3,     1,     2,     3,
     463,    88,    39,    40,     3,   464,   315,     3,   116,   354,
      44,   320,   321,    82,     3,     3,    84,   324,     3,     3,
       3,   444,    92,   214,    86,   229,    93,   367,   368,    94,
      95,   113,   115,     3,     3,     3,   117,   124,   411,     3,
     118,   347,   180,     3,   412,     3,   192,   128,    59,     3,
     125,   126,   153,   382,   119,   384,   154,   386,   138,   388,
     155,   390,   161,   280,   392,   393,   217,   136,   236,   371,
      59,   395,   396,   442,    59,    44,   130,    59,   400,   402,
     404,   406,   408,     1,     2,   302,    39,    40,     3,    39,
      40,   229,   256,   257,   258,   259,   260,   261,   137,   262,
     150,    59,    59,   150,    59,   122,    92,   200,    89,    44,
      93,    90,    91,    94,    95,   427,   159,   429,   197,   431,
     199,   433,   218,   435,   219,   442,    39,    40,     3,   205,
     206,   207,   208,   446,   447,   448,   449,   450,   241,    39,
      40,     3,   280,   242,    59,    89,    92,   243,    90,    91,
      93,   244,   319,    94,    95,   150,   246,   337,   245,    92,
     120,   121,   122,    93,   302,   350,    94,    95,   351,   147,
     148,   149,   474,   475,   476,   477,   478,    39,    40,     3,
      90,    91,   443,   139,   140,   164,   165,   166,   167,   168,
     169,   170,   250,   171,   172,   173,   255,    92,    39,    40,
       3,    93,   145,   146,    94,    95,   120,   121,   122,   462,
     121,   122,   270,   271,   311,   174,   312,   175,    92,   417,
     292,   293,    93,   316,   317,    94,    95,   164,   165,   166,
     167,   168,   169,   170,   443,   171,   172,   173,     3,   348,
      39,    40,     3,   377,   317,   256,   257,   258,   259,   260,
     261,   318,   262,   424,   317,   325,   150,   174,   326,   253,
      92,   203,   204,   329,    93,   209,   210,    94,    95,   164,
     165,   166,   272,   168,   169,   273,   330,   171,   335,   173,
     274,   336,    39,    40,     3,   263,   264,   265,   266,   267,
     268,   349,   269,   360,   361,   362,   363,   364,   365,   174,
     366,   275,    92,   355,   357,   356,    93,   370,   372,    94,
      95,   164,   165,   166,   272,   168,   169,   273,   373,   171,
     374,   173,   274,   375,    39,    40,     3,   221,   168,   169,
     222,   376,   223,   172,   378,   379,   380,    39,    40,     3,
     381,   174,   383,   352,    92,   385,   387,   389,    93,   391,
     397,    94,    95,   398,   174,   409,   224,    92,   415,   410,
     416,    93,   418,   422,    94,    95,   294,   168,   169,   295,
     419,   420,   172,   421,   423,   296,    39,    40,     3,   221,
     168,   169,   222,   425,   223,   172,   426,   428,   430,    39,
      40,     3,   432,   174,   434,   297,    92,   436,   445,   453,
      93,   456,   461,    94,    95,   457,   174,   458,   313,    92,
     459,   467,   460,    93,   468,   469,    94,    95,   294,   168,
     169,   295,   470,   472,   172,   471,   473,   296,    39,    40,
       3,   482,   483,    39,    40,     3,   484,   485,   486,    15,
      16,   491,   492,   493,   494,   174,   495,   358,    92,    31,
      47,   339,    93,    92,   496,    94,    95,    93,   497,   498,
      94,    95,    39,    40,     3,   499,   500,    39,    40,     3,
     158,    62,   314,   353,   254,   359,   490,   488,   480,   466,
     341,   201,    92,   481,   202,   343,    93,    92,     0,    94,
      95,    93,     0,   369,    94,    95,    39,    40,     3,     0,
       0,    39,    40,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   345,     0,    92,     0,     0,   399,
      93,    92,     0,    94,    95,    93,     0,     0,    94,    95,
      39,    40,     3,     0,     0,    39,    40,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   401,     0,
      92,     0,     0,   403,    93,    92,     0,    94,    95,    93,
       0,     0,    94,    95,    39,    40,     3,     0,     0,    39,
      40,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   405,     0,    92,     0,     0,   407,    93,    92,
       0,    94,    95,    93,     0,     0,    94,    95
};

static const short int yycheck[] =
{
       0,     1,     2,    21,    25,     5,   219,    61,   159,    21,
     252,   120,   197,   197,    25,   197,   159,   128,   159,    19,
      20,    75,    22,    23,    25,    25,    47,    27,   219,    41,
      42,    31,    32,    23,    34,     0,    36,   159,    92,   159,
     197,    32,   197,    44,   374,   375,   197,    47,    48,    49,
     409,   410,    52,    53,   197,   164,    56,    47,    34,    39,
     171,     3,    62,    63,    64,   176,    66,    67,   219,    41,
      70,    62,   422,   423,   225,   197,   219,   197,   219,    79,
      80,    81,   225,    83,   225,   298,   197,    63,    16,    89,
      66,   276,   276,    93,   276,    40,   150,     7,    43,   219,
      31,    32,   461,   225,    36,   225,    16,   298,    41,   351,
     110,   111,   112,    41,   114,   445,    22,    23,    22,   276,
     120,   276,   472,   123,    25,   276,    40,    31,   128,    43,
     130,    62,    64,   276,   110,    67,    22,    23,    70,    25,
      25,    47,    31,    32,    39,    34,    47,   298,    94,    95,
      16,   163,   152,    25,   276,   298,   276,   298,    16,   159,
      16,    47,    48,    48,   164,   276,    52,    52,   425,   426,
      42,   171,    39,    62,    63,    41,   176,    66,   298,   111,
     112,    25,   114,    41,    39,    41,    40,    26,    27,   243,
      23,    24,   246,    79,    79,     8,   250,   197,    42,   412,
     200,   147,   148,   149,   258,   259,   260,   261,   262,    48,
      49,   265,   266,   267,   268,   269,   473,    50,    51,   219,
     152,   110,    39,   223,   128,   225,    25,     4,     5,    25,
      40,    39,    23,    24,    25,    45,   236,    25,    39,   293,
     252,   241,   242,    42,    25,    25,    42,   247,    25,    25,
      25,   464,    43,    44,    42,   159,    47,   311,   312,    50,
      51,    42,    42,    25,    25,    25,    42,    42,    40,    25,
      39,   271,   176,    25,    46,    25,   276,    41,    27,    25,
      42,    42,    42,   337,    39,   339,    42,   341,    30,   343,
      42,   345,    42,   197,   348,   349,    42,    40,   298,   317,
      49,   355,   356,   412,    53,   317,    43,    56,   362,   363,
     364,   365,   366,     4,     5,   219,    23,    24,    25,    23,
      24,   225,    32,    33,    34,    35,    36,    37,    31,    39,
      43,    80,    81,    43,    83,     8,    43,    55,     5,   351,
      47,     8,     9,    50,    51,   399,    41,   401,    41,   403,
      44,   405,    40,   407,    41,   464,    23,    24,    25,   141,
     142,   143,   144,   417,   418,   419,   420,   421,    47,    23,
      24,    25,   276,    47,   123,     5,    43,    43,     8,     9,
      47,    40,    40,    50,    51,    43,    43,    41,    40,    43,
       6,     7,     8,    47,   298,    40,    50,    51,    43,    52,
      53,    54,   456,   457,   458,   459,   460,    23,    24,    25,
       8,     9,   412,    28,    29,    10,    11,    12,    13,    14,
      15,    16,    43,    18,    19,    20,    40,    43,    23,    24,
      25,    47,    50,    51,    50,    51,     6,     7,     8,   439,
       7,     8,    44,    45,    43,    40,    43,    42,    43,    45,
      44,    45,    47,    44,    45,    50,    51,    10,    11,    12,
      13,    14,    15,    16,   464,    18,    19,    20,    25,    43,
      23,    24,    25,    44,    45,    32,    33,    34,    35,    36,
      37,    40,    39,    44,    45,    40,    43,    40,    40,    42,
      43,   139,   140,    40,    47,   145,   146,    50,    51,    10,
      11,    12,    13,    14,    15,    16,    40,    18,    40,    20,
      21,    40,    23,    24,    25,    32,    33,    34,    35,    36,
      37,    43,    39,    32,    33,    34,    35,    36,    37,    40,
      39,    42,    43,    43,    40,    43,    47,    40,    40,    50,
      51,    10,    11,    12,    13,    14,    15,    16,    40,    18,
      44,    20,    21,    44,    23,    24,    25,    13,    14,    15,
      16,    44,    18,    19,    40,    40,    40,    23,    24,    25,
      40,    40,    40,    42,    43,    40,    40,    40,    47,    40,
      40,    50,    51,    40,    40,    44,    42,    43,    40,    44,
      40,    47,    45,    44,    50,    51,    13,    14,    15,    16,
      45,    45,    19,    45,    44,    22,    23,    24,    25,    13,
      14,    15,    16,    44,    18,    19,    44,    40,    40,    23,
      24,    25,    40,    40,    40,    42,    43,    40,    17,    40,
      47,    45,    17,    50,    51,    45,    40,    45,    42,    43,
      45,    42,    45,    47,    42,    42,    50,    51,    13,    14,
      15,    16,    42,    17,    19,    42,    17,    22,    23,    24,
      25,    40,    40,    23,    24,    25,    40,    40,    40,     5,
       5,    42,    42,    42,    42,    40,    42,    42,    43,    20,
      22,    41,    47,    43,    40,    50,    51,    47,    40,    40,
      50,    51,    23,    24,    25,    40,    40,    23,    24,    25,
     121,    31,   225,   276,   176,   298,   473,   472,   461,   445,
      41,   137,    43,   464,   138,    41,    47,    43,    -1,    50,
      51,    47,    -1,   315,    50,    51,    23,    24,    25,    -1,
      -1,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    43,    -1,    -1,    41,
      47,    43,    -1,    50,    51,    47,    -1,    -1,    50,    51,
      23,    24,    25,    -1,    -1,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      43,    -1,    -1,    41,    47,    43,    -1,    50,    51,    47,
      -1,    -1,    50,    51,    23,    24,    25,    -1,    -1,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    43,    -1,    -1,    41,    47,    43,
      -1,    50,    51,    47,    -1,    -1,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     5,    25,    57,    58,    59,    60,    61,    62,
      63,   129,   129,   129,     0,    59,    60,    61,    39,    41,
      41,     3,    64,    67,    68,    74,    75,    78,    79,    97,
     129,    64,    65,    66,    70,    71,    76,    77,   129,    23,
      24,    50,    51,   132,   133,   134,   135,    67,    74,    78,
      97,    68,    74,    78,   129,    75,    78,   129,    42,    79,
     129,    39,    65,    70,    76,    66,    70,    76,   129,    71,
      76,   129,    42,    77,   129,    39,   133,   133,    40,    74,
      78,    78,    42,    78,    42,    39,    42,    39,    39,     5,
       8,     9,    43,    47,    50,    51,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   129,   130,   131,   133,
      70,    76,    76,    42,    76,    42,    39,    42,    39,    39,
       6,     7,     8,    78,    42,    42,    42,   129,    41,    83,
      43,    72,   117,   129,   124,   124,    40,    31,    30,    28,
      29,    26,    27,    48,    49,    50,    51,    52,    53,    54,
      43,   127,    76,    42,    42,    42,   126,   129,    72,    41,
      82,    42,    40,    43,    10,    11,    12,    13,    14,    15,
      16,    18,    19,    20,    40,    42,    87,    91,    92,    96,
      97,    98,    99,   104,   105,   106,   107,   108,   109,   115,
     116,   117,   129,   131,    44,    73,   129,    41,    81,    44,
      55,   119,   120,   121,   121,   122,   122,   122,   122,   123,
     123,   124,   124,   124,    44,   117,   128,    42,    40,    41,
      80,    13,    16,    18,    42,    86,    90,    92,    95,    97,
      98,   103,   105,   106,   108,   111,   129,    69,   132,   126,
     129,    47,    47,    43,    40,    40,    43,    47,   129,   131,
      43,    40,    43,    42,    91,    40,    32,    33,    34,    35,
      36,    37,    39,    32,    33,    34,    35,    36,    37,    39,
      44,    45,    13,    16,    21,    42,    85,    89,    92,    94,
      97,    98,    99,   102,   105,   106,   107,   109,   110,   115,
     116,   129,    44,    45,    13,    16,    22,    42,    84,    88,
      92,    93,    97,    98,   100,   101,   105,   108,   111,   114,
     130,    43,    43,    42,    90,   129,    44,    45,    40,    40,
     129,   129,   117,   117,   129,    40,    40,   117,    69,    40,
      40,   117,   117,   117,   117,    40,    40,    41,   117,    41,
     117,    41,   117,    41,   117,    41,   117,   129,    43,    43,
      40,    43,    42,    89,   117,    43,    43,    40,    42,    88,
      32,    33,    34,    35,    36,    37,    39,   117,   117,   127,
      40,   132,    40,    40,    44,    44,    44,    44,    40,    40,
      40,    40,   117,    40,   117,    40,   117,    40,   117,    40,
     117,    40,   117,   117,    69,   117,   117,    40,    40,    41,
     117,    41,   117,    41,   117,    41,   117,    41,   117,    44,
      44,    40,    46,    83,    83,    40,    40,    45,    45,    45,
      45,    45,    44,    44,    44,    44,    44,   117,    40,   117,
      40,   117,    40,   117,    40,   117,    40,    82,    82,    47,
     112,   113,   126,   129,   130,    17,   117,   117,   117,   117,
     117,    81,    81,    40,    80,    80,    45,    45,    45,    45,
      45,    17,   129,    40,    45,    83,    96,    42,    42,    42,
      42,    42,    17,    17,   117,   117,   117,   117,   117,    82,
      95,   113,    40,    40,    40,    40,    40,    81,    94,    80,
      93,    42,    42,    42,    42,    42,    40,    40,    40,    40,
      40
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
#line 221 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 225 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
			AST->getRootNode()->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 4:
#line 233 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 5:
#line 237 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 6:
#line 246 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 255 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 8:
#line 259 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 9:
#line 268 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 10:
#line 272 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 11:
#line 279 "BulletParser.y"
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

  case 12:
#line 290 "BulletParser.y"
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

  case 13:
#line 301 "BulletParser.y"
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

  case 14:
#line 312 "BulletParser.y"
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

  case 15:
#line 323 "BulletParser.y"
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

  case 16:
#line 334 "BulletParser.y"
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

  case 17:
#line 345 "BulletParser.y"
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

  case 18:
#line 356 "BulletParser.y"
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

  case 19:
#line 370 "BulletParser.y"
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

  case 20:
#line 381 "BulletParser.y"
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

  case 21:
#line 392 "BulletParser.y"
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

  case 22:
#line 403 "BulletParser.y"
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

  case 23:
#line 414 "BulletParser.y"
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

  case 24:
#line 425 "BulletParser.y"
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

  case 25:
#line 436 "BulletParser.y"
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

  case 26:
#line 447 "BulletParser.y"
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

  case 27:
#line 461 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 28:
#line 465 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 29:
#line 474 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 30:
#line 478 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 31:
#line 487 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 32:
#line 496 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 33:
#line 500 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 34:
#line 509 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 35:
#line 515 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 36:
#line 525 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 37:
#line 529 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 38:
#line 538 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 542 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 551 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 41:
#line 561 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 42:
#line 565 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 43:
#line 572 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 44:
#line 577 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 45:
#line 589 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 593 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 602 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 48:
#line 613 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 617 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 626 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 635 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 52:
#line 639 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 53:
#line 648 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 54:
#line 657 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 55:
#line 661 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 56:
#line 668 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 57:
#line 672 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 58:
#line 679 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 59:
#line 683 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 60:
#line 690 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 61:
#line 694 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 62:
#line 701 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 705 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 64:
#line 714 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 718 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 66:
#line 727 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 731 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 68:
#line 740 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 744 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 70:
#line 753 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 757 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 761 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 765 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 769 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 773 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 777 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 781 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 785 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 789 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 796 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 800 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 804 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 808 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 812 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 816 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 820 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 824 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 828 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 832 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 836 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 840 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 844 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 851 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 855 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 859 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 863 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 867 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 871 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 875 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 879 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 883 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 890 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 894 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 898 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 902 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 906 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 910 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 914 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 918 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 922 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 926 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 112:
#line 930 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 113:
#line 934 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 114:
#line 938 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 115:
#line 945 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 116:
#line 949 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 117:
#line 956 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 118:
#line 962 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 119:
#line 969 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 120:
#line 979 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 121:
#line 985 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 122:
#line 992 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 123:
#line 1002 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 124:
#line 1008 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 125:
#line 1015 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 126:
#line 1025 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 127:
#line 1031 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 128:
#line 1038 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 129:
#line 1048 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 130:
#line 1057 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 131:
#line 1062 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 132:
#line 1067 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1072 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 134:
#line 1077 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 135:
#line 1082 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 136:
#line 1090 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 137:
#line 1096 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 138:
#line 1103 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 139:
#line 1108 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 140:
#line 1113 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1118 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 142:
#line 1123 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1128 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 144:
#line 1133 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 145:
#line 1139 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 146:
#line 1145 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1151 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 148:
#line 1160 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 149:
#line 1166 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 150:
#line 1173 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 151:
#line 1178 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 152:
#line 1183 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 153:
#line 1188 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 154:
#line 1193 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 155:
#line 1198 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 156:
#line 1203 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 157:
#line 1209 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 158:
#line 1215 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 159:
#line 1221 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 160:
#line 1230 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 161:
#line 1239 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 162:
#line 1248 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 163:
#line 1257 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 164:
#line 1266 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 165:
#line 1270 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 166:
#line 1277 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 167:
#line 1285 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 168:
#line 1293 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 169:
#line 1301 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
		;}
    break;

  case 170:
#line 1305 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 171:
#line 1312 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
		;}
    break;

  case 172:
#line 1316 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 173:
#line 1324 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 174:
#line 1334 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 175:
#line 1346 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 176:
#line 1350 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 177:
#line 1359 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 178:
#line 1363 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 179:
#line 1368 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 180:
#line 1375 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 181:
#line 1382 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 182:
#line 1387 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 183:
#line 1395 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 184:
#line 1401 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 185:
#line 1410 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 186:
#line 1418 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 187:
#line 1422 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 188:
#line 1431 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 189:
#line 1435 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 190:
#line 1444 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 191:
#line 1448 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 192:
#line 1454 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1463 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 194:
#line 1467 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 195:
#line 1473 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1479 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 197:
#line 1485 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1494 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 199:
#line 1498 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 200:
#line 1504 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 201:
#line 1513 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 202:
#line 1517 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 203:
#line 1523 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1529 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1538 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 206:
#line 1542 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 207:
#line 1547 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1555 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 209:
#line 1559 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1563 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 211:
#line 1567 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 212:
#line 1571 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 213:
#line 1575 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 214:
#line 1582 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 215:
#line 1591 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 216:
#line 1595 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 217:
#line 1602 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 218:
#line 1607 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 219:
#line 1619 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 220:
#line 1627 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 221:
#line 1636 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 222:
#line 1647 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 223:
#line 1651 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 224:
#line 1655 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 225:
#line 1663 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 226:
#line 1667 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 227:
#line 1674 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 228:
#line 1682 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3791 "bsBulletParser.cpp"

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


	
	

