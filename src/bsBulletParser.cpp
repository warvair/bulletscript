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
#define YYLAST   813

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  81
/* YYNRULES -- Number of rules. */
#define YYNRULES  229
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
       2,     2,     2,     2,     2,     2,    48,    55,    47,     2,
      43,    44,    53,    51,    45,    52,    56,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    40,
      49,    39,    50,     2,     2,     2,     2,     2,     2,     2,
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
     751,   754,   757,   761,   765,   770,   775,   777,   779,   783,
     785,   789,   791,   795,   799,   801,   805,   809,   813,   817,
     819,   823,   827,   829,   833,   837,   841,   843,   846,   849,
     851,   853,   855,   857,   859,   863,   866,   869,   873,   875,
     879,   881,   884,   889,   891,   894,   897,   899,   901,   903
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      58,     0,    -1,    61,    -1,    59,    61,    -1,    60,    -1,
      59,    60,    -1,   131,    39,     3,   134,    40,    -1,    62,
      -1,    61,    62,    -1,    63,    -1,    64,    -1,     5,   131,
      41,    77,    42,    -1,     5,   131,    41,    71,    77,    42,
      -1,     5,   131,    41,    66,    77,    42,    -1,     5,   131,
      41,    66,    71,    77,    42,    -1,     5,   131,    41,    65,
      77,    42,    -1,     5,   131,    41,    65,    71,    77,    42,
      -1,     5,   131,    41,    65,    66,    77,    42,    -1,     5,
     131,    41,    65,    66,    71,    77,    42,    -1,     4,   131,
      41,    79,    42,    -1,     4,   131,    41,    75,    79,    42,
      -1,     4,   131,    41,    68,    79,    42,    -1,     4,   131,
      41,    68,    75,    79,    42,    -1,     4,   131,    41,    65,
      79,    42,    -1,     4,   131,    41,    65,    75,    79,    42,
      -1,     4,   131,    41,    65,    68,    79,    42,    -1,     4,
     131,    41,    65,    68,    75,    79,    42,    -1,    98,    -1,
      65,    98,    -1,    67,    -1,    66,    67,    -1,   131,    39,
       6,   128,    40,    -1,    69,    -1,    68,    69,    -1,   131,
      39,     5,   131,    40,    -1,   131,    39,     5,   131,    43,
      70,    44,    40,    -1,   134,    -1,    70,    45,   134,    -1,
      72,    -1,    71,    72,    -1,   131,    39,     7,    73,    81,
      -1,    43,    44,    -1,    43,    74,    44,    -1,   131,    -1,
      74,    45,   131,    -1,    76,    -1,    75,    76,    -1,   131,
      39,     9,    73,    82,    -1,    78,    -1,    77,    78,    -1,
     131,    39,     8,    83,    -1,    80,    -1,    79,    80,    -1,
     131,    39,     8,    84,    -1,    41,    42,    -1,    41,    85,
      42,    -1,    41,    42,    -1,    41,    86,    42,    -1,    41,
      42,    -1,    41,    87,    42,    -1,    41,    42,    -1,    41,
      88,    42,    -1,    89,    -1,    85,    89,    -1,    90,    -1,
      86,    90,    -1,    91,    -1,    87,    91,    -1,    92,    -1,
      88,    92,    -1,    93,    -1,    94,    -1,    98,    -1,    99,
      -1,   101,    -1,   102,    -1,   106,    -1,   109,    -1,   112,
      -1,   116,    -1,    93,    -1,    95,    -1,    98,    -1,    99,
      -1,   100,    -1,   103,    -1,   106,    -1,   107,    -1,   108,
      -1,   117,    -1,   110,    -1,   111,    -1,   118,    -1,    93,
      -1,    96,    -1,    98,    -1,    99,    -1,   104,    -1,   106,
      -1,   107,    -1,   109,    -1,   112,    -1,    93,    -1,    97,
      -1,    98,    -1,    99,    -1,   100,    -1,   105,    -1,   106,
      -1,   107,    -1,   108,    -1,   109,    -1,   110,    -1,   117,
      -1,   118,    -1,    40,    -1,   119,    40,    -1,    16,    43,
     119,    44,    81,    -1,    16,    43,   119,    44,    81,    17,
      81,    -1,    16,    43,   119,    44,    81,    17,    94,    -1,
      16,    43,   119,    44,    82,    -1,    16,    43,   119,    44,
      82,    17,    82,    -1,    16,    43,   119,    44,    82,    17,
      95,    -1,    16,    43,   119,    44,    83,    -1,    16,    43,
     119,    44,    83,    17,    83,    -1,    16,    43,   119,    44,
      83,    17,    96,    -1,    16,    43,   119,    44,    84,    -1,
      16,    43,   119,    44,    84,    17,    84,    -1,    16,    43,
     119,    44,    84,    17,    97,    -1,   131,    39,   119,    40,
      -1,   131,    32,    40,    -1,   131,    33,    40,    -1,   131,
      34,   119,    40,    -1,   131,    35,   119,    40,    -1,   131,
      36,   119,    40,    -1,   131,    37,   119,    40,    -1,   133,
      39,   119,    40,    -1,   133,    39,    41,   119,    45,   119,
      42,    40,    -1,   133,    32,    40,    -1,   133,    33,    40,
      -1,   133,    34,   119,    40,    -1,   133,    35,   119,    40,
      -1,   133,    36,   119,    40,    -1,   133,    37,   119,    40,
      -1,   133,    34,    41,   119,    45,   119,    42,    40,    -1,
     133,    35,    41,   119,    45,   119,    42,    40,    -1,   133,
      36,    41,   119,    45,   119,    42,    40,    -1,   133,    37,
      41,   119,    45,   119,    42,    40,    -1,   132,    39,   119,
      40,    -1,   132,    39,    41,   119,    45,   119,    42,    40,
      -1,   132,    32,    40,    -1,   132,    33,    40,    -1,   132,
      34,   119,    40,    -1,   132,    35,   119,    40,    -1,   132,
      36,   119,    40,    -1,   132,    37,   119,    40,    -1,   132,
      34,    41,   119,    45,   119,    42,    40,    -1,   132,    35,
      41,   119,    45,   119,    42,    40,    -1,   132,    36,    41,
     119,    45,   119,    42,    40,    -1,   132,    37,    41,   119,
      45,   119,    42,    40,    -1,    13,    43,   119,    44,    81,
      -1,    13,    43,   119,    44,    82,    -1,    13,    43,   119,
      44,    83,    -1,    13,    43,   119,    44,    84,    -1,    14,
      40,    -1,    15,    40,    -1,    18,   131,    40,    -1,    18,
     133,    40,    -1,    19,    43,   119,    44,    40,    -1,    20,
      40,    -1,    20,    43,    70,    44,    40,    -1,    21,    40,
      -1,    21,    43,    70,    44,    40,    -1,   131,   131,   129,
      46,   113,    40,    -1,   131,   131,   129,    40,    -1,   114,
      -1,   113,    45,   114,    -1,   128,    -1,   131,    -1,   115,
      -1,    47,   131,    -1,    22,    40,    -1,    10,   128,    40,
      -1,    10,   131,    40,    -1,    11,    48,   131,    40,    -1,
      12,    48,   131,    40,    -1,   120,    -1,   121,    -1,   120,
      31,   121,    -1,   122,    -1,   121,    30,   122,    -1,   123,
      -1,   122,    28,   123,    -1,   122,    29,   123,    -1,   124,
      -1,   123,    49,   124,    -1,   123,    50,   124,    -1,   123,
      26,   124,    -1,   123,    27,   124,    -1,   125,    -1,   124,
      51,   125,    -1,   124,    52,   125,    -1,   126,    -1,   125,
      53,   126,    -1,   125,    54,   126,    -1,   125,    55,   126,
      -1,   127,    -1,    51,   126,    -1,    52,   126,    -1,   131,
      -1,   132,    -1,   133,    -1,   128,    -1,   135,    -1,    43,
     119,    44,    -1,   131,   129,    -1,    43,    44,    -1,    43,
     130,    44,    -1,   119,    -1,   130,    45,   119,    -1,    25,
      -1,    48,   131,    -1,    48,   131,    56,   131,    -1,   135,
      -1,    51,   135,    -1,    52,   135,    -1,   136,    -1,   137,
      -1,    23,    -1,    24,    -1
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
    1374,  1383,  1390,  1395,  1403,  1409,  1418,  1426,  1430,  1439,
    1443,  1452,  1456,  1462,  1471,  1475,  1481,  1487,  1493,  1502,
    1506,  1512,  1521,  1525,  1531,  1537,  1546,  1550,  1555,  1563,
    1567,  1571,  1575,  1579,  1583,  1590,  1599,  1603,  1610,  1615,
    1627,  1635,  1644,  1655,  1659,  1663,  1671,  1675,  1682,  1690
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
  "'&'", "'$'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'.'",
  "$accept", "script_file", "constantdef_list", "constantdef",
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
  "controller_list", "controller_entry", "anchor", "die_statement",
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
      59,   123,   125,    40,    41,    44,    58,    38,    36,    60,
      62,    43,    45,    42,    47,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    57,    58,    58,    59,    59,    60,    61,    61,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    66,
      66,    67,    68,    68,    69,    69,    70,    70,    71,    71,
      72,    73,    73,    74,    74,    75,    75,    76,    77,    77,
      78,    79,    79,    80,    81,    81,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94,    94,
      95,    95,    95,    96,    96,    96,    97,    97,    97,    98,
      99,    99,    99,    99,    99,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     102,   103,   104,   105,   106,   106,   107,   108,   109,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   114,
     115,   116,   117,   117,   118,   118,   119,   120,   120,   121,
     121,   122,   122,   122,   123,   123,   123,   123,   123,   124,
     124,   124,   125,   125,   125,   125,   126,   126,   126,   127,
     127,   127,   127,   127,   127,   128,   129,   129,   130,   130,
     131,   132,   133,   134,   134,   134,   135,   135,   136,   137
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
       2,     2,     3,     3,     4,     4,     1,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     1,
       1,     1,     1,     1,     3,     2,     2,     3,     1,     3,
       1,     2,     4,     1,     2,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,   220,     0,     0,     4,     2,     7,     9,
      10,     0,     0,     0,     1,     5,     3,     8,     0,     0,
       0,     0,     0,     0,    32,     0,    45,     0,    51,    27,
       0,     0,     0,    29,     0,    38,     0,    48,     0,   228,
     229,     0,     0,     0,   223,   226,   227,     0,     0,     0,
      28,    33,     0,     0,     0,    46,     0,     0,    19,    52,
       0,     0,     0,     0,     0,    30,     0,     0,     0,    39,
       0,     0,    11,    49,     0,     0,   224,   225,     6,     0,
       0,     0,    23,     0,    21,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   186,   187,   189,
     191,   194,   199,   202,   206,   212,   209,   210,   211,   213,
       0,     0,     0,    15,     0,    13,     0,    12,     0,     0,
       0,     0,     0,     0,    25,    24,    22,     0,     0,    53,
       0,     0,     0,   221,   207,   208,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,    17,    16,    14,     0,     0,     0,     0,
      50,    26,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,    60,     0,    68,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,     0,   209,   211,    41,     0,    43,     0,    47,   214,
       0,   188,   190,   192,   193,   197,   198,   195,   196,   200,
     201,   203,   204,   205,   216,   218,     0,    18,    31,     0,
      40,     0,     0,     0,    58,     0,    66,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   209,     0,    36,     0,
       0,     0,     0,     0,   164,   165,     0,     0,     0,     0,
       0,   169,     0,    61,    69,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,    56,     0,    64,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    90,    91,    89,
      92,   222,   217,     0,     0,     0,     0,    54,     0,    62,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
     210,     0,     0,    59,    67,     0,     0,     0,   182,   183,
       0,     0,     0,     0,     0,   166,   167,     0,     0,   130,
     131,     0,     0,     0,     0,   138,   139,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
     171,     0,    57,    65,   219,     0,     0,   181,    55,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    37,   184,   185,     0,     0,     0,     0,   132,   133,
     134,   135,     0,   140,     0,   141,     0,   142,     0,   143,
       0,   136,     0,     0,     0,     0,     0,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,     0,   163,   126,   168,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
     153,     0,   154,     0,   155,     0,   148,   162,   123,     0,
       0,   175,   179,   177,   178,     0,     0,     0,     0,     0,
       0,   161,   120,   172,   160,   117,     0,     0,     0,     0,
       0,     0,   180,   173,     0,   127,   128,     0,     0,     0,
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
     185,   186,   187,   188,   288,   235,   440,   441,   442,   309,
     189,   190,   191,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   151,   216,   106,   107,   108,   238,   109,    45,
      46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -386
static const short int yypact[] =
{
     241,   -19,   -19,  -386,    14,   241,  -386,   354,  -386,  -386,
    -386,   -15,    -6,    18,  -386,  -386,   354,  -386,    58,   -19,
     -19,   158,   -19,   -19,  -386,   -19,  -386,   145,  -386,  -386,
      56,   -19,   -19,  -386,   -19,  -386,   149,  -386,    69,  -386,
    -386,   384,   384,    77,  -386,  -386,  -386,   -19,   -19,   192,
    -386,  -386,   -19,   212,   102,  -386,   223,   105,  -386,  -386,
     136,   309,   -19,   -19,   228,  -386,   -19,   236,   138,  -386,
     238,   140,  -386,  -386,   151,   367,  -386,  -386,  -386,   -19,
     239,   242,  -386,   248,  -386,   317,  -386,   405,   180,   -19,
     157,   160,   208,   -19,   208,   208,   198,   231,   247,   388,
     194,   380,   331,  -386,  -386,  -386,   225,  -386,  -386,  -386,
     -19,   271,   282,  -386,   294,  -386,   392,  -386,   433,   274,
     -19,   160,   245,   295,  -386,  -386,  -386,   103,   410,  -386,
     123,   251,   244,   260,  -386,  -386,  -386,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     345,  -386,   298,  -386,  -386,  -386,   264,   225,   290,   554,
    -386,  -386,  -386,   158,   -19,   287,   300,   299,   310,   314,
     313,   114,   319,   257,  -386,  -386,   455,  -386,  -386,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,
    -386,   342,   344,   449,  -386,   398,  -386,   498,  -386,  -386,
     -19,   247,   388,   194,   194,   380,   380,   380,   380,   331,
     331,  -386,  -386,  -386,  -386,  -386,   415,  -386,  -386,   585,
    -386,   328,   352,   -19,  -386,   598,  -386,  -386,  -386,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,   412,   432,  -386,   361,
     301,   -19,   -19,   208,  -386,  -386,   208,   -19,   369,   371,
     208,  -386,   158,  -386,  -386,  -386,   387,   396,   208,   208,
     208,   208,   208,   414,   423,   635,   641,   671,   677,   683,
    -386,   -19,   395,   429,   303,  -386,   541,  -386,  -386,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,
    -386,  -386,  -386,   208,   444,   459,   475,  -386,   629,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,
     457,   208,   208,  -386,  -386,   225,   477,   158,  -386,  -386,
     480,   486,   483,   484,   260,  -386,  -386,   485,   456,  -386,
    -386,   490,   491,   492,   493,  -386,  -386,   208,   494,   208,
     495,   208,   496,   208,   497,   208,   499,  -386,   208,   208,
    -386,   158,  -386,  -386,  -386,   208,   208,  -386,  -386,  -386,
     502,   503,   713,   719,   725,   755,   761,   500,   501,   182,
    -386,  -386,  -386,  -386,   157,   157,   507,   508,  -386,  -386,
    -386,  -386,   293,  -386,   454,  -386,   513,  -386,   515,  -386,
     518,  -386,   527,   530,   460,   531,   532,  -386,  -386,   208,
     540,   208,   542,   208,   545,   208,   546,   208,   547,   245,
     245,  -386,   -21,  -386,   571,  -386,  -386,   208,   208,   208,
     208,   208,   251,   251,   550,   290,   290,   558,  -386,   570,
    -386,   573,  -386,   574,  -386,   575,  -386,  -386,   578,   -19,
     190,  -386,  -386,  -386,   225,    28,   549,   582,   584,   587,
     588,  -386,   614,  -386,  -386,   615,   208,   208,   208,   208,
     208,    57,  -386,  -386,   -21,  -386,  -386,   594,   595,   599,
     607,   616,    88,   142,   613,   619,   620,   621,   625,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,
    -386,   617,   628,   630,   633,   634,  -386,  -386,  -386,  -386,
    -386
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -386,  -386,  -386,   670,   674,    90,  -386,  -386,   665,   657,
      83,   668,    10,  -242,   104,    24,   576,  -386,   171,   101,
     106,    49,   227,   146,  -385,  -322,  -359,  -303,  -386,  -386,
    -386,  -386,   393,   422,   474,   528,  -151,   230,   233,   249,
     266,    96,  -143,  -185,  -386,  -386,  -386,  -386,  -386,  -120,
    -122,  -184,  -141,  -182,  -386,  -191,  -386,   252,  -386,  -386,
    -155,  -154,   -54,  -386,   572,   577,   385,   186,   311,    37,
    -386,  -109,   402,  -386,     0,  -174,  -111,   -18,   -12,  -386,
    -386
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
      11,    12,    13,    43,     3,    11,     3,    96,   227,    44,
     328,   156,   282,   286,    14,   287,   230,   193,   234,    30,
      38,    96,    30,    54,    18,    57,   439,    60,   308,    76,
      77,    38,    68,    51,    71,    19,    74,   233,   132,   232,
     454,   455,   289,   290,   170,   310,   278,    54,    57,    60,
     437,   438,    57,    60,   281,   239,    60,    51,    69,    20,
     249,    21,    68,    71,    74,   193,    71,    74,   300,   128,
      74,   413,   414,   222,   227,   285,   303,   284,   307,    57,
      60,    60,   230,    60,   234,    73,   193,    69,   489,   127,
      69,   282,   286,   133,   287,    61,   215,    17,   159,   306,
     451,   452,   479,   233,   273,   232,    17,   308,    75,   394,
      71,    74,    74,    73,    74,    65,    73,    78,    50,    73,
     157,   289,   290,    60,   310,   278,    55,    50,   192,   197,
     196,   134,   135,   281,    69,    63,    66,    64,    67,     3,
      70,    85,   465,   162,    87,    65,   163,   300,     3,    55,
     487,    44,    74,    55,   285,   303,   284,   307,   295,   236,
      73,    73,   247,    73,   240,   193,   110,   194,   111,   112,
       3,   248,   114,    59,     3,    88,   192,   116,   306,   118,
      55,    39,    40,   219,   211,   212,   213,    58,    90,   322,
     119,    72,   323,    48,    52,    59,   327,   192,   128,    59,
     291,    73,    59,   130,   331,   332,   333,   334,    96,    41,
      42,   338,   340,   342,   344,   346,   152,     3,    79,   236,
     141,   142,   411,   248,   180,   236,    59,    59,   412,    59,
     463,    39,    40,     3,    82,   464,   315,     3,   136,   354,
      44,   320,   321,   143,   144,     1,     2,   324,     3,    49,
      53,    92,    56,     3,    84,   229,    93,   367,   368,    94,
      95,     3,   137,     3,     3,    86,     3,     3,   150,    59,
     113,   347,   180,     3,    80,    81,   192,   138,   115,    83,
     117,   124,   122,   382,   125,   384,   159,   386,   199,   388,
     126,   390,   197,   280,   392,   393,     3,   251,   236,   371,
     252,   395,   396,   443,   218,    44,   123,     3,   400,   402,
     404,   406,   408,   153,    89,   302,   200,    90,    91,     3,
       3,   229,    89,     3,   154,    90,    91,   205,   206,   207,
     208,   219,    39,    40,     3,   241,   155,   161,   417,    44,
     217,   319,   243,   350,   150,   427,   351,   429,   242,   431,
     244,   433,    92,   435,   245,   443,   246,    93,     1,     2,
      94,    95,   250,   446,   447,   448,   449,   450,    39,    40,
       3,   311,   280,   120,   121,   122,   256,   257,   258,   259,
     260,   261,   255,   262,   147,   148,   149,   150,    92,   214,
      39,    40,     3,    93,   302,   312,    94,    95,   120,   121,
     122,   318,   474,   475,   476,   477,   478,    39,    40,   325,
      92,   326,   444,    90,    91,    93,   139,   140,    94,    95,
     164,   165,   166,   167,   168,   169,   170,   329,   171,   172,
     173,   145,   146,    39,    40,     3,   330,     3,   348,   462,
     121,   122,   270,   271,   256,   257,   258,   259,   260,   261,
     174,   262,   175,    92,   335,   150,   209,   210,    93,   292,
     293,    94,    95,   336,   444,   164,   165,   166,   167,   168,
     169,   170,   349,   171,   172,   173,   316,   317,    39,    40,
       3,   263,   264,   265,   266,   267,   268,   355,   269,   360,
     361,   362,   363,   364,   365,   174,   366,   253,    92,   418,
     377,   317,   356,    93,   424,   317,    94,    95,   164,   165,
     166,   272,   168,   169,   273,   357,   171,   370,   173,   274,
     372,    39,    40,     3,   203,   204,   373,   374,   375,   376,
     378,   379,   380,   381,   383,   385,   387,   389,   174,   391,
     275,    92,   397,   398,   409,   410,    93,   415,   416,    94,
      95,   164,   165,   166,   272,   168,   169,   273,   419,   171,
     420,   173,   274,   421,    39,    40,     3,   221,   168,   169,
     222,   422,   223,   172,   423,   425,   426,    39,    40,     3,
     428,   174,   430,   352,    92,   432,   434,   436,   445,    93,
     453,   467,    94,    95,   174,   461,   224,    92,   294,   168,
     169,   295,    93,   456,   172,    94,    95,   296,    39,    40,
       3,   221,   168,   169,   222,   457,   223,   172,   458,   459,
     460,    39,    40,     3,   468,   174,   469,   297,    92,   470,
     471,   472,   473,    93,   482,   483,    94,    95,   174,   484,
     313,    92,   294,   168,   169,   295,    93,   485,   172,    94,
      95,   296,    39,    40,     3,   491,   486,   496,    39,    40,
       3,   492,   493,   494,    39,    40,     3,   495,   497,   174,
     498,   358,    92,   499,   500,    15,   337,    93,    92,    16,
      94,    95,   339,    93,    92,    31,    94,    95,    62,    93,
      47,   359,    94,    95,    39,    40,     3,   158,   353,   314,
      39,    40,     3,   490,   254,   488,    39,    40,     3,   201,
     480,   466,   341,     0,    92,   202,   481,   369,   343,    93,
      92,     0,    94,    95,   345,    93,    92,     0,    94,    95,
       0,    93,     0,     0,    94,    95,    39,    40,     3,     0,
       0,     0,    39,    40,     3,     0,     0,     0,    39,    40,
       3,     0,     0,     0,   399,     0,    92,     0,     0,     0,
     401,    93,    92,     0,    94,    95,   403,    93,    92,     0,
      94,    95,     0,    93,     0,     0,    94,    95,    39,    40,
       3,     0,     0,     0,    39,    40,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   405,     0,    92,     0,
       0,     0,   407,    93,    92,     0,    94,    95,     0,    93,
       0,     0,    94,    95
};

static const short int yycheck[] =
{
       0,     1,     2,    21,    25,     5,    25,    61,   159,    21,
     252,   120,   197,   197,     0,   197,   159,   128,   159,    19,
      20,    75,    22,    23,    39,    25,    47,    27,   219,    41,
      42,    31,    32,    23,    34,    41,    36,   159,    92,   159,
     425,   426,   197,   197,    16,   219,   197,    47,    48,    49,
     409,   410,    52,    53,   197,   164,    56,    47,    34,    41,
     171,     3,    62,    63,    64,   176,    66,    67,   219,    41,
      70,   374,   375,    16,   225,   197,   219,   197,   219,    79,
      80,    81,   225,    83,   225,    36,   197,    63,   473,    89,
      66,   276,   276,    93,   276,    39,   150,     7,    41,   219,
     422,   423,   461,   225,    16,   225,    16,   298,    39,   351,
     110,   111,   112,    64,   114,    32,    67,    40,    22,    70,
     120,   276,   276,   123,   298,   276,    25,    31,   128,    41,
     130,    94,    95,   276,   110,    31,    32,    31,    32,    25,
      34,    39,   445,    40,    39,    62,    43,   298,    25,    48,
     472,   163,   152,    52,   276,   298,   276,   298,    16,   159,
     111,   112,    48,   114,   164,   276,    62,    44,    62,    63,
      25,   171,    66,    27,    25,    39,   176,    39,   298,    39,
      79,    23,    24,    41,   147,   148,   149,    42,     8,   243,
      39,    42,   246,    22,    23,    49,   250,   197,    41,    53,
     200,   152,    56,    43,   258,   259,   260,   261,   262,    51,
      52,   265,   266,   267,   268,   269,   110,    25,    47,   219,
      26,    27,    40,   223,   128,   225,    80,    81,    46,    83,
      40,    23,    24,    25,    42,    45,   236,    25,    40,   293,
     252,   241,   242,    49,    50,     4,     5,   247,    25,    22,
      23,    43,    25,    25,    42,   159,    48,   311,   312,    51,
      52,    25,    31,    25,    25,    42,    25,    25,    43,   123,
      42,   271,   176,    25,    47,    48,   276,    30,    42,    52,
      42,    42,     8,   337,    42,   339,    41,   341,    44,   343,
      42,   345,    41,   197,   348,   349,    25,    40,   298,   317,
      43,   355,   356,   412,    40,   317,    79,    25,   362,   363,
     364,   365,   366,    42,     5,   219,    56,     8,     9,    25,
      25,   225,     5,    25,    42,     8,     9,   141,   142,   143,
     144,    41,    23,    24,    25,    48,    42,    42,    45,   351,
      42,    40,    43,    40,    43,   399,    43,   401,    48,   403,
      40,   405,    43,   407,    40,   464,    43,    48,     4,     5,
      51,    52,    43,   417,   418,   419,   420,   421,    23,    24,
      25,    43,   276,     6,     7,     8,    32,    33,    34,    35,
      36,    37,    40,    39,    53,    54,    55,    43,    43,    44,
      23,    24,    25,    48,   298,    43,    51,    52,     6,     7,
       8,    40,   456,   457,   458,   459,   460,    23,    24,    40,
      43,    40,   412,     8,     9,    48,    28,    29,    51,    52,
      10,    11,    12,    13,    14,    15,    16,    40,    18,    19,
      20,    51,    52,    23,    24,    25,    40,    25,    43,   439,
       7,     8,    44,    45,    32,    33,    34,    35,    36,    37,
      40,    39,    42,    43,    40,    43,   145,   146,    48,    44,
      45,    51,    52,    40,   464,    10,    11,    12,    13,    14,
      15,    16,    43,    18,    19,    20,    44,    45,    23,    24,
      25,    32,    33,    34,    35,    36,    37,    43,    39,    32,
      33,    34,    35,    36,    37,    40,    39,    42,    43,    45,
      44,    45,    43,    48,    44,    45,    51,    52,    10,    11,
      12,    13,    14,    15,    16,    40,    18,    40,    20,    21,
      40,    23,    24,    25,   139,   140,    40,    44,    44,    44,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      42,    43,    40,    40,    44,    44,    48,    40,    40,    51,
      52,    10,    11,    12,    13,    14,    15,    16,    45,    18,
      45,    20,    21,    45,    23,    24,    25,    13,    14,    15,
      16,    44,    18,    19,    44,    44,    44,    23,    24,    25,
      40,    40,    40,    42,    43,    40,    40,    40,    17,    48,
      40,    42,    51,    52,    40,    17,    42,    43,    13,    14,
      15,    16,    48,    45,    19,    51,    52,    22,    23,    24,
      25,    13,    14,    15,    16,    45,    18,    19,    45,    45,
      45,    23,    24,    25,    42,    40,    42,    42,    43,    42,
      42,    17,    17,    48,    40,    40,    51,    52,    40,    40,
      42,    43,    13,    14,    15,    16,    48,    40,    19,    51,
      52,    22,    23,    24,    25,    42,    40,    40,    23,    24,
      25,    42,    42,    42,    23,    24,    25,    42,    40,    40,
      40,    42,    43,    40,    40,     5,    41,    48,    43,     5,
      51,    52,    41,    48,    43,    20,    51,    52,    31,    48,
      22,   298,    51,    52,    23,    24,    25,   121,   276,   225,
      23,    24,    25,   473,   176,   472,    23,    24,    25,   137,
     461,   445,    41,    -1,    43,   138,   464,   315,    41,    48,
      43,    -1,    51,    52,    41,    48,    43,    -1,    51,    52,
      -1,    48,    -1,    -1,    51,    52,    23,    24,    25,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    23,    24,
      25,    -1,    -1,    -1,    41,    -1,    43,    -1,    -1,    -1,
      41,    48,    43,    -1,    51,    52,    41,    48,    43,    -1,
      51,    52,    -1,    48,    -1,    -1,    51,    52,    23,    24,
      25,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    43,    -1,
      -1,    -1,    41,    48,    43,    -1,    51,    52,    -1,    48,
      -1,    -1,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     5,    25,    58,    59,    60,    61,    62,    63,
      64,   131,   131,   131,     0,    60,    61,    62,    39,    41,
      41,     3,    65,    68,    69,    75,    76,    79,    80,    98,
     131,    65,    66,    67,    71,    72,    77,    78,   131,    23,
      24,    51,    52,   134,   135,   136,   137,    68,    75,    79,
      98,    69,    75,    79,   131,    76,    79,   131,    42,    80,
     131,    39,    66,    71,    77,    67,    71,    77,   131,    72,
      77,   131,    42,    78,   131,    39,   135,   135,    40,    75,
      79,    79,    42,    79,    42,    39,    42,    39,    39,     5,
       8,     9,    43,    48,    51,    52,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   131,   132,   133,   135,
      71,    77,    77,    42,    77,    42,    39,    42,    39,    39,
       6,     7,     8,    79,    42,    42,    42,   131,    41,    84,
      43,    73,   119,   131,   126,   126,    40,    31,    30,    28,
      29,    26,    27,    49,    50,    51,    52,    53,    54,    55,
      43,   129,    77,    42,    42,    42,   128,   131,    73,    41,
      83,    42,    40,    43,    10,    11,    12,    13,    14,    15,
      16,    18,    19,    20,    40,    42,    88,    92,    93,    97,
      98,    99,   100,   105,   106,   107,   108,   109,   110,   117,
     118,   119,   131,   133,    44,    74,   131,    41,    82,    44,
      56,   121,   122,   123,   123,   124,   124,   124,   124,   125,
     125,   126,   126,   126,    44,   119,   130,    42,    40,    41,
      81,    13,    16,    18,    42,    87,    91,    93,    96,    98,
      99,   104,   106,   107,   109,   112,   131,    70,   134,   128,
     131,    48,    48,    43,    40,    40,    43,    48,   131,   133,
      43,    40,    43,    42,    92,    40,    32,    33,    34,    35,
      36,    37,    39,    32,    33,    34,    35,    36,    37,    39,
      44,    45,    13,    16,    21,    42,    86,    90,    93,    95,
      98,    99,   100,   103,   106,   107,   108,   110,   111,   117,
     118,   131,    44,    45,    13,    16,    22,    42,    85,    89,
      93,    94,    98,    99,   101,   102,   106,   109,   112,   116,
     132,    43,    43,    42,    91,   131,    44,    45,    40,    40,
     131,   131,   119,   119,   131,    40,    40,   119,    70,    40,
      40,   119,   119,   119,   119,    40,    40,    41,   119,    41,
     119,    41,   119,    41,   119,    41,   119,   131,    43,    43,
      40,    43,    42,    90,   119,    43,    43,    40,    42,    89,
      32,    33,    34,    35,    36,    37,    39,   119,   119,   129,
      40,   134,    40,    40,    44,    44,    44,    44,    40,    40,
      40,    40,   119,    40,   119,    40,   119,    40,   119,    40,
     119,    40,   119,   119,    70,   119,   119,    40,    40,    41,
     119,    41,   119,    41,   119,    41,   119,    41,   119,    44,
      44,    40,    46,    84,    84,    40,    40,    45,    45,    45,
      45,    45,    44,    44,    44,    44,    44,   119,    40,   119,
      40,   119,    40,   119,    40,   119,    40,    83,    83,    47,
     113,   114,   115,   128,   131,    17,   119,   119,   119,   119,
     119,    82,    82,    40,    81,    81,    45,    45,    45,    45,
      45,    17,   131,    40,    45,    84,    97,    42,    42,    42,
      42,    42,    17,    17,   119,   119,   119,   119,   119,    83,
      96,   114,    40,    40,    40,    40,    40,    82,    95,    81,
      94,    42,    42,    42,    42,    42,    40,    40,    40,    40,
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
			(yyval) = AST->createNode(PT_Anchor, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 181:
#line 1384 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 182:
#line 1391 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 183:
#line 1396 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 184:
#line 1404 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 185:
#line 1410 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 186:
#line 1419 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1427 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 188:
#line 1431 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 189:
#line 1440 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 190:
#line 1444 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 191:
#line 1453 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 192:
#line 1457 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1463 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1472 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 195:
#line 1476 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1482 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 197:
#line 1488 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1494 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 199:
#line 1503 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 200:
#line 1507 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 201:
#line 1513 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 202:
#line 1522 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 203:
#line 1526 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1532 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1538 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 206:
#line 1547 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1551 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1556 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 209:
#line 1564 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1568 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 211:
#line 1572 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 212:
#line 1576 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 213:
#line 1580 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 214:
#line 1584 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 215:
#line 1591 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 216:
#line 1600 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 217:
#line 1604 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 218:
#line 1611 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 219:
#line 1616 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 220:
#line 1628 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 221:
#line 1636 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 222:
#line 1645 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 223:
#line 1656 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 224:
#line 1660 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 225:
#line 1664 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 226:
#line 1672 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 227:
#line 1676 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 228:
#line 1683 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 229:
#line 1691 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3800 "bsBulletParser.cpp"

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


#line 1697 "BulletParser.y"


	
	

