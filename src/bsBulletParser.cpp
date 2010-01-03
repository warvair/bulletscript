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
     SYMBOL_LINK = 281,
     SYMBOL_LTE = 282,
     SYMBOL_GTE = 283,
     SYMBOL_EQ = 284,
     SYMBOL_NEQ = 285,
     SYMBOL_LOG_AND = 286,
     SYMBOL_LOG_OR = 287,
     SYMBOL_INC = 288,
     SYMBOL_DEC = 289,
     SYMBOL_ADD_A = 290,
     SYMBOL_SUB_A = 291,
     SYMBOL_MUL_A = 292,
     SYMBOL_DIV_A = 293,
     TOKEN_ERROR = 294
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
#define SYMBOL_LINK 281
#define SYMBOL_LTE 282
#define SYMBOL_GTE 283
#define SYMBOL_EQ 284
#define SYMBOL_NEQ 285
#define SYMBOL_LOG_AND 286
#define SYMBOL_LOG_OR 287
#define SYMBOL_INC 288
#define SYMBOL_DEC 289
#define SYMBOL_ADD_A 290
#define SYMBOL_SUB_A 291
#define SYMBOL_MUL_A 292
#define SYMBOL_DIV_A 293
#define TOKEN_ERROR 294




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
	"SYMBOL_LINK",						"->",
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
	for (int i = 0; i < 72; i += 2)
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
#line 354 "bsBulletParser.cpp"

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
#define YYLAST   832

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  81
/* YYNRULES -- Number of rules. */
#define YYNRULES  229
/* YYNRULES -- Number of states. */
#define YYNSTATES  503

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    48,    55,     2,     2,
      44,    45,    53,    51,    46,    52,    56,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    41,
      49,    40,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
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
     751,   755,   758,   762,   766,   771,   776,   778,   780,   784,
     786,   790,   792,   796,   800,   802,   806,   810,   814,   818,
     820,   824,   828,   830,   834,   838,   842,   844,   847,   850,
     852,   854,   856,   858,   860,   864,   867,   870,   874,   876,
     880,   882,   885,   890,   892,   895,   898,   900,   902,   904
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      58,     0,    -1,    61,    -1,    59,    61,    -1,    60,    -1,
      59,    60,    -1,   131,    40,     3,   134,    41,    -1,    62,
      -1,    61,    62,    -1,    63,    -1,    64,    -1,     5,   131,
      42,    77,    43,    -1,     5,   131,    42,    71,    77,    43,
      -1,     5,   131,    42,    66,    77,    43,    -1,     5,   131,
      42,    66,    71,    77,    43,    -1,     5,   131,    42,    65,
      77,    43,    -1,     5,   131,    42,    65,    71,    77,    43,
      -1,     5,   131,    42,    65,    66,    77,    43,    -1,     5,
     131,    42,    65,    66,    71,    77,    43,    -1,     4,   131,
      42,    79,    43,    -1,     4,   131,    42,    75,    79,    43,
      -1,     4,   131,    42,    68,    79,    43,    -1,     4,   131,
      42,    68,    75,    79,    43,    -1,     4,   131,    42,    65,
      79,    43,    -1,     4,   131,    42,    65,    75,    79,    43,
      -1,     4,   131,    42,    65,    68,    79,    43,    -1,     4,
     131,    42,    65,    68,    75,    79,    43,    -1,    98,    -1,
      65,    98,    -1,    67,    -1,    66,    67,    -1,   131,    40,
       6,   128,    41,    -1,    69,    -1,    68,    69,    -1,   131,
      40,     5,   131,    41,    -1,   131,    40,     5,   131,    44,
      70,    45,    41,    -1,   134,    -1,    70,    46,   134,    -1,
      72,    -1,    71,    72,    -1,   131,    40,     7,    73,    81,
      -1,    44,    45,    -1,    44,    74,    45,    -1,   131,    -1,
      74,    46,   131,    -1,    76,    -1,    75,    76,    -1,   131,
      40,     9,    73,    82,    -1,    78,    -1,    77,    78,    -1,
     131,    40,     8,    83,    -1,    80,    -1,    79,    80,    -1,
     131,    40,     8,    84,    -1,    42,    43,    -1,    42,    85,
      43,    -1,    42,    43,    -1,    42,    86,    43,    -1,    42,
      43,    -1,    42,    87,    43,    -1,    42,    43,    -1,    42,
      88,    43,    -1,    89,    -1,    85,    89,    -1,    90,    -1,
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
      -1,   118,    -1,    41,    -1,   119,    41,    -1,    16,    44,
     119,    45,    81,    -1,    16,    44,   119,    45,    81,    17,
      81,    -1,    16,    44,   119,    45,    81,    17,    94,    -1,
      16,    44,   119,    45,    82,    -1,    16,    44,   119,    45,
      82,    17,    82,    -1,    16,    44,   119,    45,    82,    17,
      95,    -1,    16,    44,   119,    45,    83,    -1,    16,    44,
     119,    45,    83,    17,    83,    -1,    16,    44,   119,    45,
      83,    17,    96,    -1,    16,    44,   119,    45,    84,    -1,
      16,    44,   119,    45,    84,    17,    84,    -1,    16,    44,
     119,    45,    84,    17,    97,    -1,   131,    40,   119,    41,
      -1,   131,    33,    41,    -1,   131,    34,    41,    -1,   131,
      35,   119,    41,    -1,   131,    36,   119,    41,    -1,   131,
      37,   119,    41,    -1,   131,    38,   119,    41,    -1,   133,
      40,   119,    41,    -1,   133,    40,    42,   119,    46,   119,
      43,    41,    -1,   133,    33,    41,    -1,   133,    34,    41,
      -1,   133,    35,   119,    41,    -1,   133,    36,   119,    41,
      -1,   133,    37,   119,    41,    -1,   133,    38,   119,    41,
      -1,   133,    35,    42,   119,    46,   119,    43,    41,    -1,
     133,    36,    42,   119,    46,   119,    43,    41,    -1,   133,
      37,    42,   119,    46,   119,    43,    41,    -1,   133,    38,
      42,   119,    46,   119,    43,    41,    -1,   132,    40,   119,
      41,    -1,   132,    40,    42,   119,    46,   119,    43,    41,
      -1,   132,    33,    41,    -1,   132,    34,    41,    -1,   132,
      35,   119,    41,    -1,   132,    36,   119,    41,    -1,   132,
      37,   119,    41,    -1,   132,    38,   119,    41,    -1,   132,
      35,    42,   119,    46,   119,    43,    41,    -1,   132,    36,
      42,   119,    46,   119,    43,    41,    -1,   132,    37,    42,
     119,    46,   119,    43,    41,    -1,   132,    38,    42,   119,
      46,   119,    43,    41,    -1,    13,    44,   119,    45,    81,
      -1,    13,    44,   119,    45,    82,    -1,    13,    44,   119,
      45,    83,    -1,    13,    44,   119,    45,    84,    -1,    14,
      41,    -1,    15,    41,    -1,    18,   131,    41,    -1,    18,
     133,    41,    -1,    19,    44,   119,    45,    41,    -1,    20,
      41,    -1,    20,    44,    70,    45,    41,    -1,    21,    41,
      -1,    21,    44,    70,    45,    41,    -1,   131,   131,   129,
      47,   113,    41,    -1,   131,   131,   129,    41,    -1,   114,
      -1,   113,    46,   114,    -1,   128,    -1,   131,    -1,   115,
      -1,   131,    26,   132,    -1,    22,    41,    -1,    10,   128,
      41,    -1,    10,   131,    41,    -1,    11,    48,   131,    41,
      -1,    12,    48,   131,    41,    -1,   120,    -1,   121,    -1,
     120,    32,   121,    -1,   122,    -1,   121,    31,   122,    -1,
     123,    -1,   122,    29,   123,    -1,   122,    30,   123,    -1,
     124,    -1,   123,    49,   124,    -1,   123,    50,   124,    -1,
     123,    27,   124,    -1,   123,    28,   124,    -1,   125,    -1,
     124,    51,   125,    -1,   124,    52,   125,    -1,   126,    -1,
     125,    53,   126,    -1,   125,    54,   126,    -1,   125,    55,
     126,    -1,   127,    -1,    51,   126,    -1,    52,   126,    -1,
     131,    -1,   132,    -1,   133,    -1,   128,    -1,   135,    -1,
      44,   119,    45,    -1,   131,   129,    -1,    44,    45,    -1,
      44,   130,    45,    -1,   119,    -1,   130,    46,   119,    -1,
      25,    -1,    48,   131,    -1,    48,   131,    56,   131,    -1,
     135,    -1,    51,   135,    -1,    52,   135,    -1,   136,    -1,
     137,    -1,    23,    -1,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   222,   222,   226,   234,   238,   247,   256,   260,   269,
     273,   280,   291,   302,   313,   324,   335,   346,   357,   371,
     382,   393,   404,   415,   426,   437,   448,   462,   466,   475,
     479,   488,   497,   501,   510,   516,   526,   530,   539,   543,
     552,   562,   566,   573,   578,   590,   594,   603,   614,   618,
     627,   636,   640,   649,   658,   662,   669,   673,   680,   684,
     691,   695,   702,   706,   715,   719,   728,   732,   741,   745,
     754,   758,   762,   766,   770,   774,   778,   782,   786,   790,
     797,   801,   805,   809,   813,   817,   821,   825,   829,   833,
     837,   841,   845,   852,   856,   860,   864,   868,   872,   876,
     880,   884,   891,   895,   899,   903,   907,   911,   915,   919,
     923,   927,   931,   935,   939,   946,   950,   957,   963,   970,
     980,   986,   993,  1003,  1009,  1016,  1026,  1032,  1039,  1049,
    1058,  1063,  1068,  1073,  1078,  1083,  1091,  1097,  1104,  1109,
    1114,  1119,  1124,  1129,  1134,  1140,  1146,  1152,  1161,  1167,
    1174,  1179,  1184,  1189,  1194,  1199,  1204,  1210,  1216,  1222,
    1231,  1240,  1249,  1258,  1267,  1271,  1278,  1286,  1294,  1302,
    1306,  1313,  1317,  1325,  1335,  1347,  1351,  1360,  1364,  1369,
    1376,  1385,  1392,  1397,  1405,  1411,  1420,  1428,  1432,  1441,
    1445,  1454,  1458,  1464,  1473,  1477,  1483,  1489,  1495,  1504,
    1508,  1514,  1523,  1527,  1533,  1539,  1548,  1552,  1557,  1565,
    1569,  1573,  1577,  1581,  1585,  1592,  1601,  1605,  1612,  1617,
    1629,  1637,  1646,  1657,  1661,  1665,  1673,  1677,  1684,  1692
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
  "IDENTIFIER", "SYMBOL_LINK", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ",
  "SYMBOL_NEQ", "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC",
  "SYMBOL_DEC", "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A",
  "SYMBOL_DIV_A", "TOKEN_ERROR", "'='", "';'", "'{'", "'}'", "'('", "')'",
  "','", "':'", "'$'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'.'", "$accept", "script_file", "constantdef_list", "constantdef",
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
  "controller_list", "controller_entry", "anchor_link", "die_statement",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      61,    59,   123,   125,    40,    41,    44,    58,    36,    60,
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
       3,     2,     3,     3,     4,     4,     1,     1,     3,     1,
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
     175,   179,   177,   178,     0,     0,     0,     0,     0,     0,
     161,   120,   172,   160,   117,     0,     0,     0,     0,     0,
       0,   173,     0,     0,   127,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   124,   125,
     176,     0,   180,   144,   145,   146,   147,   137,   121,   122,
     118,   119,     0,     0,     0,     0,     0,   221,   156,   157,
     158,   159,   149
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    10,    22,    32,
      33,    23,    24,   237,    34,    35,   131,   195,    25,    26,
      36,    37,    27,    28,   220,   198,   160,   129,   298,   276,
     225,   176,   299,   277,   226,   177,   178,   301,   279,   228,
     179,    29,   181,   182,   304,   305,   283,   231,   183,   184,
     185,   186,   187,   188,   288,   235,   439,   440,   441,   309,
     189,   190,   191,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   151,   216,   106,   107,   108,   238,   109,    45,
      46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -370
static const short int yypact[] =
{
     165,   -11,   -11,  -370,    84,   165,  -370,   353,  -370,  -370,
    -370,    55,    96,   116,  -370,  -370,   353,  -370,   114,   -11,
     -11,   178,   -11,   -11,  -370,   -11,  -370,   -15,  -370,  -370,
     180,   -11,   -11,  -370,   -11,  -370,    88,  -370,   184,  -370,
    -370,   338,   338,   137,  -370,  -370,  -370,   -11,   -11,   150,
    -370,  -370,   -11,   155,   195,  -370,   218,   197,  -370,  -370,
     211,   308,   -11,   -11,   219,  -370,   -11,   220,   225,  -370,
     221,   228,  -370,  -370,   233,   365,  -370,  -370,  -370,   -11,
     223,   224,  -370,   229,  -370,   272,  -370,   366,   179,   -11,
     168,   174,   775,   -11,   775,   775,   237,   252,   251,   355,
     167,   348,   393,  -370,  -370,  -370,   246,  -370,  -370,  -370,
     -11,   245,   250,  -370,   254,  -370,   447,  -370,   399,   284,
     -11,   174,   277,   279,  -370,  -370,  -370,   147,   408,  -370,
      14,   283,   269,   265,  -370,  -370,  -370,   775,   775,   775,
     775,   775,   775,   775,   775,   775,   775,   775,   775,   775,
     208,  -370,   281,  -370,  -370,  -370,   293,   246,   294,   552,
    -370,  -370,  -370,   178,   -11,   321,   334,   306,   356,   409,
     381,   131,   396,   274,  -370,  -370,   453,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,   420,   304,   358,  -370,   369,  -370,   496,  -370,  -370,
     -11,   251,   355,   167,   167,   348,   348,   348,   348,   393,
     393,  -370,  -370,  -370,  -370,  -370,   384,  -370,  -370,   592,
    -370,   426,   440,   -11,  -370,   605,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,   343,   412,  -370,   444,
     282,   -11,   -11,   775,  -370,  -370,   775,   -11,   445,   446,
     775,  -370,   178,  -370,  -370,  -370,   448,   449,   775,   775,
     775,   775,   775,   450,   451,   650,   680,   685,   696,   718,
    -370,   -11,   454,   455,   302,  -370,   539,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,   775,   456,   458,   452,  -370,   645,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
     401,   775,   775,  -370,  -370,   246,   462,   178,  -370,  -370,
     472,   474,   443,   473,   265,  -370,  -370,   477,   429,  -370,
    -370,   482,   483,   484,   485,  -370,  -370,   775,   486,   775,
     487,   775,   488,   775,   489,   775,   490,  -370,   775,   775,
    -370,   178,  -370,  -370,  -370,   775,   775,  -370,  -370,  -370,
     491,   492,   729,   734,   764,   769,   780,   493,   497,   193,
    -370,  -370,  -370,  -370,   168,   168,   494,   495,  -370,  -370,
    -370,  -370,   499,  -370,   500,  -370,   510,  -370,   512,  -370,
     515,  -370,   498,   524,   434,   527,   528,  -370,  -370,   775,
     533,   775,   537,   775,   538,   775,   540,   775,   543,   277,
     277,  -370,   -11,  -370,   478,  -370,  -370,   775,   775,   775,
     775,   775,   283,   283,   544,   294,   294,   542,  -370,   546,
    -370,   548,  -370,   551,  -370,   553,  -370,  -370,   517,    80,
    -370,  -370,  -370,   177,    19,   555,   558,   559,   566,   567,
    -370,   569,  -370,  -370,   572,   775,   775,   775,   775,   775,
      35,  -370,   -11,   564,  -370,  -370,   581,   584,   585,   586,
     590,   102,   111,   570,   589,   591,   594,   595,  -370,  -370,
    -370,   -11,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,   598,   600,   601,   604,   606,  -370,  -370,  -370,
    -370,  -370,  -370
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -370,  -370,  -370,   536,   646,   170,  -370,  -370,   630,   621,
      92,   632,    75,  -248,    11,    -8,   534,  -370,   138,    67,
      73,    70,   120,   247,  -263,  -322,  -369,  -287,  -370,  -370,
    -370,  -370,   364,   387,   441,   501,  -151,   199,   194,   212,
     232,   110,  -147,  -186,  -370,  -370,  -370,  -370,  -370,  -143,
    -126,  -182,  -150,  -179,  -370,  -190,  -370,   216,  -370,  -370,
    -167,  -160,   -54,  -370,   545,   541,   271,   301,   337,    79,
    -370,  -107,   368,  -370,     0,  -213,  -111,   -18,     3,  -370,
    -370
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
      11,    12,    13,    43,   328,    11,   310,    96,   227,   234,
       3,   282,   230,   156,     3,   286,   232,   193,   287,    30,
      38,    96,    30,    54,    44,    57,    69,    60,    58,   308,
     289,    38,    68,   233,    71,   170,    74,   290,   132,     3,
     437,   438,    63,    66,    76,    77,   278,    54,    57,    60,
     281,   222,    57,    60,   284,    69,    60,   239,    69,   194,
     249,   128,    68,    71,    74,   193,    71,    74,   300,   307,
      74,   285,   303,   110,   227,   234,   306,   159,   230,    57,
      60,    60,   232,    60,    14,   310,   193,   413,   414,   127,
     282,   478,    55,   133,   286,    18,   215,   287,    51,   233,
     450,   451,    69,   394,    64,    67,    73,    70,   308,   289,
      71,    74,    74,     3,    74,    55,   290,    21,   273,    55,
     157,   461,    51,    60,    65,   278,   462,   295,   192,   281,
     196,    72,    50,   284,    73,   111,   112,    73,    19,   114,
      73,    50,    49,    53,   197,    56,    55,   300,   307,   488,
     285,   303,    74,   219,    65,   306,     3,   464,    20,   236,
      48,    52,   453,   454,   240,   193,    44,    80,    81,     1,
       2,   248,    83,   134,   135,     3,   192,    17,    78,   247,
       3,    73,    73,   152,    73,    79,    17,    90,   162,   322,
       3,   163,   323,    82,   141,   142,   327,   192,    84,   123,
     291,    39,    40,   463,   331,   332,   333,   334,    96,   490,
     128,   338,   340,   342,   344,   346,   143,   144,   130,   236,
      61,   150,    73,   248,    75,   236,   211,   212,   213,    41,
      42,    39,    40,     3,   411,    85,   315,    87,   180,   354,
     412,   320,   321,     3,     3,     3,     3,   324,     3,     3,
     482,    88,    92,   214,     3,    44,    93,   367,   368,    94,
      95,    86,   113,   115,   117,   116,   124,   125,   118,   229,
       3,   347,   126,   119,    59,     3,   192,    89,   136,     3,
      90,    91,   138,   382,   137,   384,   180,   386,   153,   388,
     150,   390,   122,   154,   392,   393,    59,   155,   236,   371,
      59,   395,   396,    59,     3,   442,     3,   280,   400,   402,
     404,   406,   408,    89,   199,   251,    90,    91,   252,   159,
      44,   200,   161,   319,   217,   197,   150,    59,    59,   302,
      59,    39,    40,     3,   218,   229,   219,   256,   257,   258,
     259,   260,   261,   350,   262,   427,   351,   429,   150,   431,
     243,   433,    92,   435,    44,   442,    93,     1,     2,    94,
      95,    39,    40,   445,   446,   447,   448,   449,     3,   241,
      59,   120,   121,   122,    90,    91,   256,   257,   258,   259,
     260,   261,   242,   262,   139,   140,   280,   150,    39,    40,
       3,   263,   264,   265,   266,   267,   268,   244,   269,   145,
     146,   473,   474,   475,   476,   477,   121,   122,   302,    92,
     203,   204,   443,    93,   270,   271,    94,    95,   164,   165,
     166,   167,   168,   169,   170,   246,   171,   172,   173,   292,
     293,    39,    40,     3,   360,   361,   362,   363,   364,   365,
     250,   366,   205,   206,   207,   208,   147,   148,   149,   174,
     245,   175,    92,   120,   121,   122,    93,   316,   317,    94,
      95,   255,   443,   164,   165,   166,   167,   168,   169,   170,
     311,   171,   172,   173,   377,   317,    39,    40,     3,   424,
     317,   497,   209,   210,   312,   318,   325,   326,   374,   329,
     330,   335,   336,   357,   174,   444,   253,    92,   348,   349,
     355,    93,   356,   370,    94,    95,   164,   165,   166,   272,
     168,   169,   273,   372,   171,   373,   173,   274,   375,    39,
      40,     3,   376,   378,   379,   380,   381,   383,   385,   387,
     389,   391,   397,   398,   460,   415,   416,   174,   409,   275,
      92,    15,   410,   422,    93,   417,   418,    94,    95,   164,
     165,   166,   272,   168,   169,   273,   419,   171,   420,   173,
     274,   421,    39,    40,     3,   221,   168,   169,   222,   423,
     223,   172,   425,   426,   428,    39,    40,     3,   430,   432,
     174,   434,   352,    92,   436,   452,   471,    93,   455,   472,
      94,    95,   456,   174,   457,   224,    92,   458,   466,   459,
      93,   467,   468,    94,    95,   294,   168,   169,   295,   469,
     470,   172,   481,   492,   296,    39,    40,     3,   221,   168,
     169,   222,   483,   223,   172,   484,   485,   486,    39,    40,
       3,   487,   493,   174,   494,   297,    92,   495,   496,   498,
      93,   499,   500,    94,    95,   501,   174,   502,   313,    92,
      31,    16,    62,    93,    47,   158,    94,    95,   294,   168,
     169,   295,   359,   353,   172,   489,   314,   296,    39,    40,
       3,   491,   479,    39,    40,     3,   465,   254,   480,   202,
       0,     0,   201,   369,     0,     0,   174,     0,   358,    92,
       0,     0,   337,    93,    92,     0,    94,    95,    93,     0,
       0,    94,    95,    39,    40,     3,     0,     0,    39,    40,
       3,     0,     0,     0,     0,     0,     0,     0,     0,    39,
      40,     3,   339,     0,    92,     0,     0,   341,    93,    92,
       0,    94,    95,    93,     0,     0,    94,    95,   343,     0,
      92,    39,    40,     3,    93,     0,     0,    94,    95,     0,
       0,     0,    39,    40,     3,     0,     0,    39,    40,     3,
     345,     0,    92,     0,     0,     0,    93,     0,     0,    94,
      95,   399,     0,    92,     0,     0,   401,    93,    92,     0,
      94,    95,    93,     0,     0,    94,    95,    39,    40,     3,
       0,     0,    39,    40,     3,     0,     0,     0,    39,    40,
       3,     0,     0,    39,    40,     3,   403,     0,    92,     0,
       0,   405,    93,    92,     0,    94,    95,    93,     0,    92,
      94,    95,   407,    93,    92,     0,    94,    95,    93,     0,
       0,    94,    95
};

static const short int yycheck[] =
{
       0,     1,     2,    21,   252,     5,   219,    61,   159,   159,
      25,   197,   159,   120,    25,   197,   159,   128,   197,    19,
      20,    75,    22,    23,    21,    25,    34,    27,    43,   219,
     197,    31,    32,   159,    34,    16,    36,   197,    92,    25,
     409,   410,    31,    32,    41,    42,   197,    47,    48,    49,
     197,    16,    52,    53,   197,    63,    56,   164,    66,    45,
     171,    42,    62,    63,    64,   176,    66,    67,   219,   219,
      70,   197,   219,    62,   225,   225,   219,    42,   225,    79,
      80,    81,   225,    83,     0,   298,   197,   374,   375,    89,
     276,   460,    25,    93,   276,    40,   150,   276,    23,   225,
     422,   423,   110,   351,    31,    32,    36,    34,   298,   276,
     110,   111,   112,    25,   114,    48,   276,     3,    16,    52,
     120,    41,    47,   123,    32,   276,    46,    16,   128,   276,
     130,    43,    22,   276,    64,    62,    63,    67,    42,    66,
      70,    31,    22,    23,    42,    25,    79,   298,   298,   471,
     276,   298,   152,    42,    62,   298,    25,   444,    42,   159,
      22,    23,   425,   426,   164,   276,   163,    47,    48,     4,
       5,   171,    52,    94,    95,    25,   176,     7,    41,    48,
      25,   111,   112,   110,   114,    47,    16,     8,    41,   243,
      25,    44,   246,    43,    27,    28,   250,   197,    43,    79,
     200,    23,    24,    26,   258,   259,   260,   261,   262,   472,
      42,   265,   266,   267,   268,   269,    49,    50,    44,   219,
      40,    44,   152,   223,    40,   225,   147,   148,   149,    51,
      52,    23,    24,    25,    41,    40,   236,    40,   128,   293,
      47,   241,   242,    25,    25,    25,    25,   247,    25,    25,
     463,    40,    44,    45,    25,   252,    48,   311,   312,    51,
      52,    43,    43,    43,    43,    40,    43,    43,    40,   159,
      25,   271,    43,    40,    27,    25,   276,     5,    41,    25,
       8,     9,    31,   337,    32,   339,   176,   341,    43,   343,
      44,   345,     8,    43,   348,   349,    49,    43,   298,   317,
      53,   355,   356,    56,    25,   412,    25,   197,   362,   363,
     364,   365,   366,     5,    45,    41,     8,     9,    44,    42,
     317,    56,    43,    41,    43,    42,    44,    80,    81,   219,
      83,    23,    24,    25,    41,   225,    42,    33,    34,    35,
      36,    37,    38,    41,    40,   399,    44,   401,    44,   403,
      44,   405,    44,   407,   351,   462,    48,     4,     5,    51,
      52,    23,    24,   417,   418,   419,   420,   421,    25,    48,
     123,     6,     7,     8,     8,     9,    33,    34,    35,    36,
      37,    38,    48,    40,    29,    30,   276,    44,    23,    24,
      25,    33,    34,    35,    36,    37,    38,    41,    40,    51,
      52,   455,   456,   457,   458,   459,     7,     8,   298,    44,
     139,   140,   412,    48,    45,    46,    51,    52,    10,    11,
      12,    13,    14,    15,    16,    44,    18,    19,    20,    45,
      46,    23,    24,    25,    33,    34,    35,    36,    37,    38,
      44,    40,   141,   142,   143,   144,    53,    54,    55,    41,
      41,    43,    44,     6,     7,     8,    48,    45,    46,    51,
      52,    41,   462,    10,    11,    12,    13,    14,    15,    16,
      44,    18,    19,    20,    45,    46,    23,    24,    25,    45,
      46,   481,   145,   146,    44,    41,    41,    41,    45,    41,
      41,    41,    41,    41,    41,    17,    43,    44,    44,    44,
      44,    48,    44,    41,    51,    52,    10,    11,    12,    13,
      14,    15,    16,    41,    18,    41,    20,    21,    45,    23,
      24,    25,    45,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    17,    41,    41,    41,    45,    43,
      44,     5,    45,    45,    48,    46,    46,    51,    52,    10,
      11,    12,    13,    14,    15,    16,    46,    18,    46,    20,
      21,    46,    23,    24,    25,    13,    14,    15,    16,    45,
      18,    19,    45,    45,    41,    23,    24,    25,    41,    41,
      41,    41,    43,    44,    41,    41,    17,    48,    46,    17,
      51,    52,    46,    41,    46,    43,    44,    46,    43,    46,
      48,    43,    43,    51,    52,    13,    14,    15,    16,    43,
      43,    19,    48,    43,    22,    23,    24,    25,    13,    14,
      15,    16,    41,    18,    19,    41,    41,    41,    23,    24,
      25,    41,    43,    41,    43,    43,    44,    43,    43,    41,
      48,    41,    41,    51,    52,    41,    41,    41,    43,    44,
      20,     5,    31,    48,    22,   121,    51,    52,    13,    14,
      15,    16,   298,   276,    19,   471,   225,    22,    23,    24,
      25,   472,   460,    23,    24,    25,   444,   176,   462,   138,
      -1,    -1,   137,   315,    -1,    -1,    41,    -1,    43,    44,
      -1,    -1,    42,    48,    44,    -1,    51,    52,    48,    -1,
      -1,    51,    52,    23,    24,    25,    -1,    -1,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    25,    42,    -1,    44,    -1,    -1,    42,    48,    44,
      -1,    51,    52,    48,    -1,    -1,    51,    52,    42,    -1,
      44,    23,    24,    25,    48,    -1,    -1,    51,    52,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    23,    24,    25,
      42,    -1,    44,    -1,    -1,    -1,    48,    -1,    -1,    51,
      52,    42,    -1,    44,    -1,    -1,    42,    48,    44,    -1,
      51,    52,    48,    -1,    -1,    51,    52,    23,    24,    25,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    23,    24,
      25,    -1,    -1,    23,    24,    25,    42,    -1,    44,    -1,
      -1,    42,    48,    44,    -1,    51,    52,    48,    -1,    44,
      51,    52,    42,    48,    44,    -1,    51,    52,    48,    -1,
      -1,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     5,    25,    58,    59,    60,    61,    62,    63,
      64,   131,   131,   131,     0,    60,    61,    62,    40,    42,
      42,     3,    65,    68,    69,    75,    76,    79,    80,    98,
     131,    65,    66,    67,    71,    72,    77,    78,   131,    23,
      24,    51,    52,   134,   135,   136,   137,    68,    75,    79,
      98,    69,    75,    79,   131,    76,    79,   131,    43,    80,
     131,    40,    66,    71,    77,    67,    71,    77,   131,    72,
      77,   131,    43,    78,   131,    40,   135,   135,    41,    75,
      79,    79,    43,    79,    43,    40,    43,    40,    40,     5,
       8,     9,    44,    48,    51,    52,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   131,   132,   133,   135,
      71,    77,    77,    43,    77,    43,    40,    43,    40,    40,
       6,     7,     8,    79,    43,    43,    43,   131,    42,    84,
      44,    73,   119,   131,   126,   126,    41,    32,    31,    29,
      30,    27,    28,    49,    50,    51,    52,    53,    54,    55,
      44,   129,    77,    43,    43,    43,   128,   131,    73,    42,
      83,    43,    41,    44,    10,    11,    12,    13,    14,    15,
      16,    18,    19,    20,    41,    43,    88,    92,    93,    97,
      98,    99,   100,   105,   106,   107,   108,   109,   110,   117,
     118,   119,   131,   133,    45,    74,   131,    42,    82,    45,
      56,   121,   122,   123,   123,   124,   124,   124,   124,   125,
     125,   126,   126,   126,    45,   119,   130,    43,    41,    42,
      81,    13,    16,    18,    43,    87,    91,    93,    96,    98,
      99,   104,   106,   107,   109,   112,   131,    70,   134,   128,
     131,    48,    48,    44,    41,    41,    44,    48,   131,   133,
      44,    41,    44,    43,    92,    41,    33,    34,    35,    36,
      37,    38,    40,    33,    34,    35,    36,    37,    38,    40,
      45,    46,    13,    16,    21,    43,    86,    90,    93,    95,
      98,    99,   100,   103,   106,   107,   108,   110,   111,   117,
     118,   131,    45,    46,    13,    16,    22,    43,    85,    89,
      93,    94,    98,    99,   101,   102,   106,   109,   112,   116,
     132,    44,    44,    43,    91,   131,    45,    46,    41,    41,
     131,   131,   119,   119,   131,    41,    41,   119,    70,    41,
      41,   119,   119,   119,   119,    41,    41,    42,   119,    42,
     119,    42,   119,    42,   119,    42,   119,   131,    44,    44,
      41,    44,    43,    90,   119,    44,    44,    41,    43,    89,
      33,    34,    35,    36,    37,    38,    40,   119,   119,   129,
      41,   134,    41,    41,    45,    45,    45,    45,    41,    41,
      41,    41,   119,    41,   119,    41,   119,    41,   119,    41,
     119,    41,   119,   119,    70,   119,   119,    41,    41,    42,
     119,    42,   119,    42,   119,    42,   119,    42,   119,    45,
      45,    41,    47,    84,    84,    41,    41,    46,    46,    46,
      46,    46,    45,    45,    45,    45,    45,   119,    41,   119,
      41,   119,    41,   119,    41,   119,    41,    83,    83,   113,
     114,   115,   128,   131,    17,   119,   119,   119,   119,   119,
      82,    82,    41,    81,    81,    46,    46,    46,    46,    46,
      17,    41,    46,    26,    84,    97,    43,    43,    43,    43,
      43,    17,    17,   119,   119,   119,   119,   119,    83,    96,
     114,    48,   132,    41,    41,    41,    41,    41,    82,    95,
      81,    94,    43,    43,    43,    43,    43,   131,    41,    41,
      41,    41,    41
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
#line 223 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 227 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
			AST->getRootNode()->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 4:
#line 235 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 5:
#line 239 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantDefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 6:
#line 248 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantDefinition, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 7:
#line 257 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 8:
#line 261 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 9:
#line 270 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 10:
#line 274 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 11:
#line 281 "BulletParser.y"
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
#line 292 "BulletParser.y"
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
#line 303 "BulletParser.y"
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
#line 314 "BulletParser.y"
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
#line 325 "BulletParser.y"
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
#line 336 "BulletParser.y"
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
#line 347 "BulletParser.y"
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
#line 358 "BulletParser.y"
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
#line 372 "BulletParser.y"
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
#line 383 "BulletParser.y"
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
#line 394 "BulletParser.y"
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
#line 405 "BulletParser.y"
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
#line 416 "BulletParser.y"
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
#line 427 "BulletParser.y"
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
#line 438 "BulletParser.y"
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
#line 449 "BulletParser.y"
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
#line 463 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 28:
#line 467 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 29:
#line 476 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 30:
#line 480 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 31:
#line 489 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 32:
#line 498 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 33:
#line 502 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 34:
#line 511 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 35:
#line 517 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 36:
#line 527 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 37:
#line 531 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 38:
#line 540 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 39:
#line 544 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 40:
#line 553 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 41:
#line 563 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 42:
#line 567 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 43:
#line 574 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 44:
#line 579 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 45:
#line 591 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 595 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 604 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 48:
#line 615 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 619 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 628 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 637 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 52:
#line 641 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 53:
#line 650 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 54:
#line 659 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 55:
#line 663 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 56:
#line 670 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 57:
#line 674 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 58:
#line 681 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 59:
#line 685 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 60:
#line 692 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 61:
#line 696 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 62:
#line 703 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 707 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 64:
#line 716 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 720 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 66:
#line 729 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 733 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 68:
#line 742 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 746 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 70:
#line 755 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 759 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 763 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 767 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 771 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 775 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 779 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 783 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 787 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 791 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 798 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 802 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 806 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 810 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 814 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 818 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 822 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 826 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 830 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 834 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 838 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 842 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 846 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 853 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 857 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 861 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 865 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 869 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 873 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 877 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 881 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 885 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 892 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 896 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 900 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 904 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 908 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 912 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 916 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 920 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 924 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 928 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 112:
#line 932 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 113:
#line 936 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 114:
#line 940 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 115:
#line 947 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 116:
#line 951 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 117:
#line 958 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 118:
#line 964 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 119:
#line 971 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 120:
#line 981 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 121:
#line 987 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 122:
#line 994 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 123:
#line 1004 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 124:
#line 1010 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 125:
#line 1017 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 126:
#line 1027 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 127:
#line 1033 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 128:
#line 1040 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 129:
#line 1050 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 130:
#line 1059 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 131:
#line 1064 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 132:
#line 1069 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1074 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 134:
#line 1079 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 135:
#line 1084 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 136:
#line 1092 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 137:
#line 1098 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 138:
#line 1105 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 139:
#line 1110 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 140:
#line 1115 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1120 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 142:
#line 1125 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1130 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 144:
#line 1135 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 145:
#line 1141 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 146:
#line 1147 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1153 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 148:
#line 1162 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 149:
#line 1168 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 150:
#line 1175 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 151:
#line 1180 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 152:
#line 1185 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 153:
#line 1190 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 154:
#line 1195 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 155:
#line 1200 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 156:
#line 1205 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 157:
#line 1211 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 158:
#line 1217 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 159:
#line 1223 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 160:
#line 1232 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 161:
#line 1241 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 162:
#line 1250 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 163:
#line 1259 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 164:
#line 1268 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 165:
#line 1272 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 166:
#line 1279 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 167:
#line 1287 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 168:
#line 1295 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 169:
#line 1303 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
		;}
    break;

  case 170:
#line 1307 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 171:
#line 1314 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
		;}
    break;

  case 172:
#line 1318 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 173:
#line 1326 "BulletParser.y"
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
#line 1336 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 175:
#line 1348 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 176:
#line 1352 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 177:
#line 1361 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 178:
#line 1365 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 179:
#line 1370 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 180:
#line 1377 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AnchorLink, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 181:
#line 1386 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 182:
#line 1393 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 183:
#line 1398 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 184:
#line 1406 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 185:
#line 1412 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 186:
#line 1421 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1429 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 188:
#line 1433 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 189:
#line 1442 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 190:
#line 1446 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 191:
#line 1455 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 192:
#line 1459 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1465 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1474 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 195:
#line 1478 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1484 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 197:
#line 1490 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1496 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 199:
#line 1505 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 200:
#line 1509 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 201:
#line 1515 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 202:
#line 1524 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 203:
#line 1528 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1534 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1540 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 206:
#line 1549 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1553 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1558 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 209:
#line 1566 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1570 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 211:
#line 1574 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 212:
#line 1578 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 213:
#line 1582 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 214:
#line 1586 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 215:
#line 1593 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 216:
#line 1602 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 217:
#line 1606 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 218:
#line 1613 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 219:
#line 1618 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 220:
#line 1630 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 221:
#line 1638 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 222:
#line 1647 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 223:
#line 1658 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 224:
#line 1662 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 225:
#line 1666 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 226:
#line 1674 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 227:
#line 1678 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 228:
#line 1685 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 229:
#line 1693 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3808 "bsBulletParser.cpp"

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


#line 1699 "BulletParser.y"


	
	

