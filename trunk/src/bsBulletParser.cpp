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
     KEYWORD_FOR = 268,
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
#define KEYWORD_FOR 268
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
	"KEYWORD_FOR",						"for",
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
		
		YYSTYPE id_name_node = AST->createNode(PT_Identifier, yylineno);
		id_name_node->setString(idNode->getChild(0)->getStringData().c_str());

		id_node->setChild(0, id_name_node);
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
#line 355 "bsBulletParser.cpp"

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
#define YYLAST   915

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  80
/* YYNRULES -- Number of rules. */
#define YYNRULES  236
/* YYNRULES -- Number of states. */
#define YYNSTATES  563

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
       2,     2,     2,     2,     2,     2,     2,     2,    46,    42,
      49,    41,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
       0,     0,     3,     5,     7,    10,    12,    14,    20,    27,
      34,    42,    49,    57,    65,    74,    80,    87,    94,   102,
     109,   117,   125,   134,   136,   139,   141,   144,   150,   152,
     155,   161,   170,   172,   176,   178,   181,   187,   190,   194,
     196,   200,   202,   205,   211,   213,   216,   221,   223,   226,
     231,   234,   238,   241,   245,   248,   252,   255,   259,   261,
     264,   266,   269,   271,   274,   276,   279,   281,   283,   285,
     288,   290,   292,   294,   296,   298,   300,   302,   304,   306,
     309,   311,   313,   315,   317,   319,   321,   323,   325,   327,
     329,   331,   333,   336,   338,   340,   342,   344,   346,   348,
     350,   352,   355,   357,   359,   361,   363,   365,   367,   369,
     371,   373,   375,   378,   384,   392,   400,   406,   414,   422,
     428,   436,   444,   450,   458,   466,   471,   474,   477,   481,
     485,   489,   493,   498,   507,   511,   515,   520,   525,   530,
     535,   544,   553,   562,   571,   576,   585,   589,   593,   598,
     603,   608,   613,   622,   631,   640,   649,   651,   655,   657,
     663,   672,   684,   690,   699,   711,   717,   726,   738,   744,
     753,   765,   768,   771,   775,   779,   785,   788,   794,   797,
     803,   810,   815,   817,   821,   823,   825,   827,   830,   833,
     837,   841,   846,   851,   853,   855,   859,   861,   865,   867,
     871,   875,   877,   881,   885,   889,   893,   895,   899,   903,
     905,   909,   913,   917,   919,   922,   925,   927,   929,   931,
     933,   935,   939,   942,   945,   949,   951,   955,   957,   960,
     965,   967,   970,   973,   975,   977,   979
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      58,     0,    -1,    59,    -1,    60,    -1,    59,    60,    -1,
      61,    -1,    62,    -1,     4,   130,    39,    75,    40,    -1,
       4,   130,    39,    69,    75,    40,    -1,     4,   130,    39,
      64,    75,    40,    -1,     4,   130,    39,    64,    69,    75,
      40,    -1,     4,   130,    39,    63,    75,    40,    -1,     4,
     130,    39,    63,    69,    75,    40,    -1,     4,   130,    39,
      63,    64,    75,    40,    -1,     4,   130,    39,    63,    64,
      69,    75,    40,    -1,     3,   130,    39,    77,    40,    -1,
       3,   130,    39,    73,    77,    40,    -1,     3,   130,    39,
      66,    77,    40,    -1,     3,   130,    39,    66,    73,    77,
      40,    -1,     3,   130,    39,    63,    77,    40,    -1,     3,
     130,    39,    63,    73,    77,    40,    -1,     3,   130,    39,
      63,    66,    77,    40,    -1,     3,   130,    39,    63,    66,
      73,    77,    40,    -1,    96,    -1,    63,    96,    -1,    65,
      -1,    64,    65,    -1,   130,    41,     5,   127,    42,    -1,
      67,    -1,    66,    67,    -1,   130,    41,     4,   130,    42,
      -1,   130,    41,     4,   130,    43,    68,    44,    42,    -1,
     133,    -1,    68,    45,   133,    -1,    70,    -1,    69,    70,
      -1,   130,    41,     6,    71,    79,    -1,    43,    44,    -1,
      43,    72,    44,    -1,   130,    -1,    72,    45,   130,    -1,
      74,    -1,    73,    74,    -1,   130,    41,     8,    71,    80,
      -1,    76,    -1,    75,    76,    -1,   130,    41,     7,    81,
      -1,    78,    -1,    77,    78,    -1,   130,    41,     7,    82,
      -1,    39,    40,    -1,    39,    83,    40,    -1,    39,    40,
      -1,    39,    84,    40,    -1,    39,    40,    -1,    39,    85,
      40,    -1,    39,    40,    -1,    39,    86,    40,    -1,    87,
      -1,    83,    87,    -1,    88,    -1,    84,    88,    -1,    89,
      -1,    85,    89,    -1,    90,    -1,    86,    90,    -1,    91,
      -1,    92,    -1,    96,    -1,    97,    42,    -1,    99,    -1,
     101,    -1,   105,    -1,   108,    -1,   111,    -1,   115,    -1,
      91,    -1,    93,    -1,    96,    -1,    97,    42,    -1,    98,
      -1,   102,    -1,   105,    -1,   106,    -1,   107,    -1,   116,
      -1,   109,    -1,   110,    -1,   117,    -1,    91,    -1,    94,
      -1,    96,    -1,    97,    42,    -1,   103,    -1,   105,    -1,
     106,    -1,   108,    -1,   111,    -1,    91,    -1,    95,    -1,
      96,    -1,    97,    42,    -1,    98,    -1,   104,    -1,   105,
      -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,   116,
      -1,   117,    -1,    42,    -1,   118,    42,    -1,    16,    43,
     118,    44,    79,    -1,    16,    43,   118,    44,    79,    17,
      79,    -1,    16,    43,   118,    44,    79,    17,    92,    -1,
      16,    43,   118,    44,    80,    -1,    16,    43,   118,    44,
      80,    17,    80,    -1,    16,    43,   118,    44,    80,    17,
      93,    -1,    16,    43,   118,    44,    81,    -1,    16,    43,
     118,    44,    81,    17,    81,    -1,    16,    43,   118,    44,
      81,    17,    94,    -1,    16,    43,   118,    44,    82,    -1,
      16,    43,   118,    44,    82,    17,    82,    -1,    16,    43,
     118,    44,    82,    17,    95,    -1,   130,    41,   118,    42,
      -1,   130,    32,    -1,   130,    33,    -1,   130,    34,   118,
      -1,   130,    35,   118,    -1,   130,    36,   118,    -1,   130,
      37,   118,    -1,   132,    41,   118,    42,    -1,   132,    41,
      39,   118,    45,   118,    40,    42,    -1,   132,    32,    42,
      -1,   132,    33,    42,    -1,   132,    34,   118,    42,    -1,
     132,    35,   118,    42,    -1,   132,    36,   118,    42,    -1,
     132,    37,   118,    42,    -1,   132,    34,    39,   118,    45,
     118,    40,    42,    -1,   132,    35,    39,   118,    45,   118,
      40,    42,    -1,   132,    36,    39,   118,    45,   118,    40,
      42,    -1,   132,    37,    39,   118,    45,   118,    40,    42,
      -1,   131,    41,   118,    42,    -1,   131,    41,    39,   118,
      45,   118,    40,    42,    -1,   131,    32,    42,    -1,   131,
      33,    42,    -1,   131,    34,   118,    42,    -1,   131,    35,
     118,    42,    -1,   131,    36,   118,    42,    -1,   131,    37,
     118,    42,    -1,   131,    34,    39,   118,    45,   118,    40,
      42,    -1,   131,    35,    39,   118,    45,   118,    40,    42,
      -1,   131,    36,    39,   118,    45,   118,    40,    42,    -1,
     131,    37,    39,   118,    45,   118,    40,    42,    -1,   118,
      -1,   130,    41,   118,    -1,    97,    -1,    12,    43,   118,
      44,    79,    -1,    13,    43,    42,   118,    42,   100,    44,
      79,    -1,    13,    43,   130,    41,   118,    42,   118,    42,
     100,    44,    79,    -1,    12,    43,   118,    44,    80,    -1,
      13,    43,    42,   118,    42,   100,    44,    80,    -1,    13,
      43,   130,    41,   118,    42,   118,    42,   100,    44,    80,
      -1,    12,    43,   118,    44,    81,    -1,    13,    43,    42,
     118,    42,   100,    44,    81,    -1,    13,    43,   130,    41,
     118,    42,   118,    42,   100,    44,    81,    -1,    12,    43,
     118,    44,    82,    -1,    13,    43,    42,   118,    42,   100,
      44,    82,    -1,    13,    43,   130,    41,   118,    42,   118,
      42,   100,    44,    82,    -1,    14,    42,    -1,    15,    42,
      -1,    18,   130,    42,    -1,    18,   132,    42,    -1,    19,
      43,   118,    44,    42,    -1,    20,    42,    -1,    20,    43,
      68,    44,    42,    -1,    21,    42,    -1,    21,    43,    68,
      44,    42,    -1,   130,   130,   128,    46,   112,    42,    -1,
     130,   130,   128,    42,    -1,   113,    -1,   112,    45,   113,
      -1,   127,    -1,   130,    -1,   114,    -1,    47,   130,    -1,
      22,    42,    -1,     9,   127,    42,    -1,     9,   130,    42,
      -1,    10,    48,   130,    42,    -1,    11,    48,   130,    42,
      -1,   119,    -1,   120,    -1,   119,    31,   120,    -1,   121,
      -1,   120,    30,   121,    -1,   122,    -1,   121,    28,   122,
      -1,   121,    29,   122,    -1,   123,    -1,   122,    49,   123,
      -1,   122,    50,   123,    -1,   122,    26,   123,    -1,   122,
      27,   123,    -1,   124,    -1,   123,    51,   124,    -1,   123,
      52,   124,    -1,   125,    -1,   124,    53,   125,    -1,   124,
      54,   125,    -1,   124,    55,   125,    -1,   126,    -1,    51,
     125,    -1,    52,   125,    -1,   130,    -1,   131,    -1,   132,
      -1,   127,    -1,   134,    -1,    43,   118,    44,    -1,   130,
     128,    -1,    43,    44,    -1,    43,   129,    44,    -1,   118,
      -1,   129,    45,   118,    -1,    25,    -1,    48,   130,    -1,
      48,   130,    56,   130,    -1,   134,    -1,    51,   134,    -1,
      52,   134,    -1,   135,    -1,   136,    -1,    23,    -1,    24,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   224,   224,   231,   235,   244,   248,   255,   266,   277,
     288,   299,   310,   321,   332,   346,   357,   368,   379,   390,
     401,   412,   423,   437,   441,   450,   454,   463,   472,   476,
     485,   491,   501,   505,   514,   518,   527,   537,   541,   548,
     553,   565,   569,   578,   589,   593,   602,   611,   615,   624,
     633,   637,   644,   648,   655,   659,   666,   670,   677,   681,
     690,   694,   703,   707,   716,   720,   729,   733,   737,   741,
     745,   749,   753,   757,   761,   765,   772,   776,   780,   784,
     788,   792,   796,   800,   804,   808,   812,   816,   820,   827,
     831,   835,   839,   843,   847,   851,   855,   859,   866,   870,
     874,   878,   882,   886,   890,   894,   898,   902,   906,   910,
     914,   921,   925,   932,   938,   945,   955,   961,   968,   978,
     984,   991,  1001,  1007,  1014,  1024,  1033,  1038,  1043,  1048,
    1053,  1058,  1066,  1072,  1079,  1084,  1089,  1094,  1099,  1104,
    1109,  1115,  1121,  1127,  1136,  1142,  1149,  1154,  1159,  1164,
    1169,  1174,  1179,  1185,  1191,  1197,  1206,  1210,  1216,  1223,
    1229,  1237,  1253,  1259,  1267,  1283,  1289,  1297,  1313,  1319,
    1327,  1343,  1347,  1354,  1362,  1370,  1378,  1382,  1389,  1393,
    1401,  1411,  1423,  1427,  1436,  1440,  1445,  1452,  1461,  1468,
    1473,  1481,  1487,  1496,  1504,  1508,  1517,  1521,  1530,  1534,
    1540,  1549,  1553,  1559,  1565,  1571,  1580,  1584,  1590,  1599,
    1603,  1609,  1615,  1624,  1628,  1633,  1641,  1645,  1649,  1653,
    1657,  1661,  1668,  1677,  1681,  1688,  1693,  1705,  1713,  1722,
    1733,  1737,  1741,  1749,  1753,  1760,  1768
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
  "KEYWORD_FOR", "KEYWORD_BREAK", "KEYWORD_CONTINUE", "KEYWORD_IF",
  "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_SUSPEND",
  "KEYWORD_SIGNAL", "KEYWORD_DIE", "INTEGER", "REAL", "IDENTIFIER",
  "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ", "SYMBOL_LOG_AND",
  "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC", "SYMBOL_ADD_A",
  "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'",
  "'}'", "'='", "';'", "'('", "')'", "','", "':'", "'&'", "'$'", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'.'", "$accept",
  "script_file", "definition_list", "definition", "emitter_definition",
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
  "function_selection_statement", "event_selection_statement",
  "emitter_state_selection_statement",
  "controller_state_selection_statement", "simple_assignment_statement",
  "extended_assignment_statement", "emitter_member_statement",
  "property_statement", "for_update_statement",
  "function_iteration_statement", "event_iteration_statement",
  "emitter_state_iteration_statement",
  "controller_state_iteration_statement", "jump_statement",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   123,
     125,    61,    59,    40,    41,    44,    58,    38,    36,    60,
      62,    43,    45,    42,    47,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    75,    76,    77,    77,    78,
      79,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    91,    91,    92,    92,    92,    93,    93,    93,    94,
      94,    94,    95,    95,    95,    96,    97,    97,    97,    97,
      97,    97,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,   100,   100,   100,   101,
     101,   101,   102,   102,   102,   103,   103,   103,   104,   104,
     104,   105,   105,   106,   107,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   113,   114,   115,   116,
     116,   117,   117,   118,   119,   119,   120,   120,   121,   121,
     121,   122,   122,   122,   122,   122,   123,   123,   123,   124,
     124,   124,   124,   125,   125,   125,   126,   126,   126,   126,
     126,   126,   127,   128,   128,   129,   129,   130,   131,   132,
     133,   133,   133,   134,   134,   135,   136
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     5,     6,     6,     7,     6,
       7,     7,     8,     1,     2,     1,     2,     5,     1,     2,
       5,     8,     1,     3,     1,     2,     5,     2,     3,     1,
       3,     1,     2,     5,     1,     2,     4,     1,     2,     4,
       2,     3,     2,     3,     2,     3,     2,     3,     1,     2,
       1,     2,     1,     2,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     7,     7,     5,     7,     7,     5,
       7,     7,     5,     7,     7,     4,     2,     2,     3,     3,
       3,     3,     4,     8,     3,     3,     4,     4,     4,     4,
       8,     8,     8,     8,     4,     8,     3,     3,     4,     4,
       4,     4,     8,     8,     8,     8,     1,     3,     1,     5,
       8,    11,     5,     8,    11,     5,     8,    11,     5,     8,
      11,     2,     2,     3,     3,     5,     2,     5,     2,     5,
       6,     4,     1,     3,     1,     1,     1,     2,     2,     3,
       3,     4,     4,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     2,     2,     1,     1,     1,     1,
       1,     3,     2,     2,     3,     1,     3,     1,     2,     4,
       1,     2,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   227,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    41,
       0,    47,    23,     0,     0,     0,    25,     0,    34,     0,
      44,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      42,     0,     0,    15,    48,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    35,     0,     0,     7,    45,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   235,   236,     0,     0,     0,     0,
       0,   193,   194,   196,   198,   201,   206,   209,   213,   219,
     216,   217,   218,   220,   233,   234,     0,     0,     0,    11,
       0,     9,     0,     8,     0,     0,     0,     0,     0,     0,
      21,    20,    18,     0,     0,    49,     0,     0,     0,   228,
     214,   215,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   222,     0,    13,
      12,    10,     0,     0,     0,     0,    46,    22,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,   111,     0,    64,    98,    99,   100,     0,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,   216,
     218,    37,     0,    39,     0,    43,   221,     0,   195,   197,
     199,   200,   204,   205,   202,   203,   207,   208,   210,   211,
     212,   223,   225,     0,    14,    27,     0,    36,     0,     0,
       0,     0,    54,     0,    62,    89,    90,    91,     0,    93,
      94,    95,    96,    97,   216,     0,     0,     0,    32,   230,
       0,     0,     0,     0,     0,     0,   171,   172,     0,     0,
       0,     0,     0,   176,     0,    57,    65,   101,   112,   126,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,     0,     0,    52,
       0,    60,    76,    77,    78,     0,    80,    81,    82,    83,
      84,    86,    87,    85,    88,   229,   224,     0,     0,     0,
       0,     0,    50,     0,    58,    66,    67,    68,     0,    70,
      71,    72,    73,    74,    75,   217,     0,     0,     0,    55,
      63,    92,     0,   231,   232,     0,     0,   189,   190,     0,
       0,     0,     0,     0,     0,     0,   173,   174,     0,     0,
     128,   129,   130,   131,   134,   135,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,     0,     0,     0,
     178,     0,    53,    61,    79,   226,     0,     0,     0,   188,
      51,    59,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    33,   191,   192,     0,
       0,     0,     0,     0,     0,     0,   136,     0,   137,     0,
     138,     0,   139,     0,   132,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     181,     0,   168,     0,     0,   122,   175,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,     0,   149,     0,   150,     0,   151,
       0,   144,   165,     0,     0,   119,     0,     0,   182,   186,
     184,   185,   158,     0,   156,   216,     0,     0,     0,     0,
       0,     0,     0,   162,     0,     0,   116,   179,   159,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
     187,   180,     0,     0,     0,     0,   123,   124,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   121,   183,   169,
     157,     0,   140,   141,   142,   143,   133,     0,     0,   117,
     118,     0,     0,   114,   115,     0,     0,     0,     0,     0,
     166,     0,     0,   163,     0,   160,     0,   152,   153,   154,
     155,   145,     0,     0,     0,     0,     0,   170,     0,     0,
     167,   164,   161
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,   227,    27,    28,   117,   182,    18,    19,    29,    30,
      20,    21,   207,   185,   146,   115,   293,   270,   213,   163,
     294,   271,   214,   164,   165,   296,   273,   216,   166,    22,
     462,   169,   299,   463,   300,   277,   219,   170,   171,   172,
     173,   174,   175,   282,   223,   457,   458,   459,   304,   176,
     177,   178,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   137,   203,    90,    91,    92,   228,    93,    94,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -368
static const short int yypact[] =
{
     342,   -15,   -15,    93,   342,  -368,  -368,  -368,  -368,    79,
      83,  -368,  -368,   -15,   -15,   -15,   -15,  -368,   -15,  -368,
      94,  -368,  -368,    87,   -15,   -15,  -368,   -15,  -368,   100,
    -368,   117,   -15,   -15,   186,  -368,  -368,   -15,   205,   124,
    -368,   208,   144,  -368,  -368,   151,   287,   -15,   -15,   211,
    -368,   -15,   212,   173,  -368,   219,   187,  -368,  -368,   200,
     337,   -15,   228,   253,  -368,   276,  -368,   403,  -368,   333,
     199,   -15,   181,   221,  -368,  -368,   831,   -15,   831,   831,
      84,   223,   254,   329,   119,   349,   222,  -368,  -368,  -368,
     257,  -368,  -368,  -368,  -368,  -368,   -15,   289,   308,  -368,
     312,  -368,   302,  -368,   410,   295,   -15,   221,   282,   334,
    -368,  -368,  -368,   401,   541,  -368,    66,   288,   275,   293,
    -368,  -368,  -368,   831,   831,   831,   831,   831,   831,   831,
     831,   831,   831,   831,   831,   831,   280,  -368,   358,  -368,
    -368,  -368,   309,   257,   324,   687,  -368,  -368,  -368,     6,
     -15,   317,   319,   328,   336,   345,   348,   359,    31,   363,
     405,  -368,  -368,   585,  -368,  -368,  -368,  -368,   350,  -368,
    -368,  -368,  -368,  -368,  -368,  -368,  -368,  -368,   366,   623,
     864,  -368,   417,  -368,   629,  -368,  -368,   -15,   254,   329,
     119,   119,   349,   349,   349,   349,   222,   222,  -368,  -368,
    -368,  -368,  -368,   430,  -368,  -368,   728,  -368,   375,   378,
     387,   -15,  -368,   742,  -368,  -368,  -368,  -368,   391,  -368,
    -368,  -368,  -368,  -368,   493,   453,   453,   438,  -368,  -368,
     393,   445,   -15,   -15,   831,    10,  -368,  -368,   831,   -15,
     395,   397,   831,  -368,     6,  -368,  -368,  -368,  -368,  -368,
    -368,   831,   831,   831,   831,   831,   407,   425,   274,   330,
     380,   402,   441,  -368,   -15,   426,   436,   442,   454,  -368,
     673,  -368,  -368,  -368,  -368,   473,  -368,  -368,  -368,  -368,
    -368,  -368,  -368,  -368,  -368,  -368,  -368,   831,   474,   476,
     478,   481,  -368,   783,  -368,  -368,  -368,  -368,   482,  -368,
    -368,  -368,  -368,  -368,  -368,   874,   831,   147,   831,  -368,
    -368,  -368,   257,  -368,  -368,   489,     6,  -368,  -368,   491,
     495,   332,   831,   497,   498,   293,  -368,  -368,   500,   456,
    -368,  -368,  -368,  -368,  -368,  -368,   831,   499,   831,   504,
     831,   505,   831,   506,   831,   516,  -368,   831,   165,   831,
    -368,     6,  -368,  -368,  -368,  -368,   831,   179,   831,  -368,
    -368,  -368,  -368,   520,   521,   447,   563,   789,   819,   825,
     523,   831,   527,   526,    17,  -368,  -368,  -368,  -368,   181,
     529,   831,   181,   531,   533,   494,  -368,   532,  -368,   534,
    -368,   535,  -368,   537,  -368,   546,   831,   544,   547,   459,
     568,   831,   566,   569,  -368,  -368,   831,   536,   831,   574,
     831,   575,   831,   576,   831,   577,   282,   578,   831,   282,
    -368,    20,  -368,   831,   579,   559,  -368,  -368,   831,   831,
     831,   831,   831,   288,   580,   831,   288,   581,   324,   582,
     831,   324,   584,  -368,   586,  -368,   587,  -368,   589,  -368,
     590,  -368,  -368,   831,   588,   609,   -15,   204,  -368,  -368,
    -368,   257,  -368,   602,  -368,   852,   831,   131,   608,   611,
     621,   622,   625,  -368,   831,   626,   646,  -368,  -368,   831,
     628,   650,   831,   831,   831,   831,   831,   630,   831,   145,
    -368,  -368,    20,   181,   831,   631,  -368,  -368,   633,   634,
     636,   637,   648,   651,   831,   155,   660,   831,   161,   652,
     667,   668,   669,   674,   282,   675,  -368,  -368,  -368,  -368,
    -368,   831,  -368,  -368,  -368,  -368,  -368,   288,   676,  -368,
    -368,   324,   677,  -368,  -368,   678,   680,   681,   684,   686,
    -368,   831,   688,  -368,   831,  -368,   831,  -368,  -368,  -368,
    -368,  -368,   689,   181,   690,   692,   282,  -368,   288,   324,
    -368,  -368,  -368
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -368,  -368,  -368,   727,  -368,  -368,   723,   721,    53,   731,
     183,  -242,   107,    85,   641,  -368,    -7,   102,   171,   127,
     224,   209,  -357,  -367,  -339,  -340,  -368,  -368,  -368,  -368,
     466,   479,   549,   600,  -141,   256,   264,   283,   306,     3,
     -92,  -181,  -368,  -286,  -368,  -368,  -368,  -368,   -90,  -111,
    -164,  -138,  -163,  -368,  -195,  -368,   286,  -368,  -368,  -146,
    -140,    28,  -368,   654,   657,   383,   285,   374,     8,  -368,
    -101,   462,  -368,    -1,  -190,   -73,   467,  -143,  -368,  -368
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   329,   276,   215,   142,   229,   222,    33,    37,
       8,   303,    23,    31,    23,    39,   305,    42,    35,    45,
     280,   281,   168,    31,    53,    61,    56,    35,    59,    74,
      75,    39,    42,    45,   221,     8,    42,    45,   283,   422,
      45,   180,   425,   272,   284,     8,    53,    56,    59,   230,
      56,    59,   322,   218,    59,   220,     8,   225,   226,   420,
      42,    45,    45,   421,    45,   295,   473,   456,   302,   476,
     113,   168,   215,   279,    80,   222,   119,   452,    50,   239,
     455,   478,   313,   314,   481,   241,   120,   121,    80,   276,
     180,     8,   275,    11,   278,    56,    59,    59,   303,    59,
      50,   229,   221,   305,   118,   143,   280,   281,    45,   399,
     181,   180,    54,   179,   298,   183,   301,   167,    13,     8,
      40,   218,    14,   220,   283,     8,   122,   496,    46,   272,
     284,    48,    51,    54,    43,    40,    54,    59,   529,    40,
      57,   198,   199,   200,   224,   127,   128,   157,   217,   231,
     516,   533,   295,   519,    96,   302,    58,   240,    60,   279,
     543,   210,   179,    40,   202,    67,   167,   487,   129,   130,
     114,   267,     8,   229,   545,   540,    58,   290,   275,    58,
     278,    54,    58,   179,   145,    69,   285,   274,   503,   371,
       8,   561,    70,   506,   184,    49,    52,   180,    55,    36,
     206,   298,   562,   301,     8,   224,    72,   396,   229,   297,
     240,     8,   224,   557,   102,    36,   217,   560,    97,    98,
     114,   401,   100,   312,    58,    58,    64,    58,   104,    44,
       8,   319,   320,     8,   323,   542,     8,     8,   325,    34,
      38,   105,    41,    44,     8,    66,   491,    44,    68,   492,
      44,    99,   101,     8,   123,   552,    62,    63,   554,   103,
     555,    65,   321,   346,   116,    58,   324,   138,   110,   179,
     328,    44,    44,   274,    44,   133,   134,   135,     8,   330,
     331,   332,   333,    80,   124,   109,   337,   339,   341,   343,
     345,    71,   224,   111,    72,    73,   297,    74,    75,     8,
     136,     8,   108,    74,    75,     8,   372,   106,   107,   108,
      74,    75,     8,   336,     8,   355,   112,    76,    44,   186,
     460,   145,    77,    76,   201,    78,    79,   184,    77,   139,
      76,    78,    79,     8,   370,    77,   373,     8,    78,    79,
      72,    73,   106,   107,   108,     1,     2,   397,   140,   187,
     380,   205,   141,    74,    75,     8,   402,   125,   126,     8,
      74,    75,     8,   206,   385,   232,   387,   233,   389,   338,
     391,   234,   393,    76,   147,   395,   379,   398,    77,   235,
      76,    78,    79,     8,   400,    77,   403,   236,    78,    79,
     237,   460,   247,   407,   409,   411,   413,   415,   204,   417,
     131,   132,   238,    74,    75,     8,   242,    71,   248,   424,
      72,    73,   192,   193,   194,   195,   107,   108,   306,   340,
     461,   307,   465,    76,   434,    74,    75,     8,    77,   439,
     308,    78,    79,   311,   442,   317,   444,   326,   446,   327,
     448,   342,   450,   148,   149,    76,   454,   243,   244,   334,
      77,   464,   465,    78,    79,   490,   468,   469,   470,   471,
     472,   263,   264,   475,    74,    75,     8,   335,   480,   347,
      74,    75,     8,   465,   286,   287,    74,    75,   465,   348,
     344,   464,   315,   316,    76,   349,   406,   318,   136,    77,
      76,   461,    78,    79,   495,    77,   350,   351,    78,    79,
     384,   316,   464,   437,   316,   196,   197,   464,   190,   191,
     509,   510,   511,   512,   513,   354,   515,   356,     8,   357,
     465,   358,   520,   359,   362,   249,   250,   251,   252,   253,
     254,   375,   528,   377,   255,   532,   136,   378,   381,   428,
     465,   386,   382,   465,   383,   465,   388,   390,   392,   464,
     150,   151,   152,   153,   154,   155,   156,   157,   394,   158,
     159,   160,   404,   405,    74,    75,     8,   416,   418,   464,
     419,   423,   464,   426,   464,   427,   467,   429,   443,   430,
     431,   161,   432,   162,    76,   435,    74,    75,     8,    77,
     433,   436,    78,    79,   150,   151,   152,   153,   154,   155,
     156,   157,   408,   158,   159,   160,    76,   440,    74,    75,
       8,    77,   438,   441,    78,    79,   445,   447,   449,   451,
     453,   466,   474,   477,   479,   245,   489,   162,    76,   482,
     488,   483,   484,    77,   485,   486,    78,    79,   150,   151,
     152,   265,   266,   155,   156,   267,   493,   158,   498,   160,
     268,   499,    74,    75,     8,   249,   250,   251,   252,   253,
     254,   500,   501,   505,   255,   502,   136,   508,   504,   269,
     507,   162,    76,   521,   514,   522,   523,    77,   524,   525,
      78,    79,   150,   151,   152,   265,   266,   155,   156,   267,
     526,   158,   535,   160,   268,   527,    74,    75,     8,   208,
     209,   155,   156,   210,   531,   211,   159,   536,   537,   538,
      74,    75,     8,   352,   539,   162,    76,   541,   544,   546,
     547,    77,   548,   549,    78,    79,   550,   212,   551,   162,
      76,    12,   553,   556,   558,    77,   559,    24,    78,    79,
     288,   289,   155,   156,   290,    47,    32,   159,   144,   353,
     291,    74,    75,     8,   208,   209,   155,   156,   210,   361,
     211,   159,   310,   246,   534,    74,    75,     8,   292,   530,
     162,    76,   517,   497,   374,     0,    77,   188,   518,    78,
      79,   189,   309,   376,   162,    76,     0,     0,     0,     0,
      77,     0,     0,    78,    79,   288,   289,   155,   156,   290,
       0,     0,   159,     0,     0,   291,    74,    75,     8,     0,
       0,     0,    74,    75,     8,     0,     0,     0,     0,     0,
       0,     0,     0,   360,     0,   162,    76,     0,   410,     0,
       0,    77,    76,     0,    78,    79,     0,    77,     0,     0,
      78,    79,    74,    75,     8,     0,     0,     0,    74,    75,
       8,     0,     0,     0,    74,    75,     8,     0,   412,     0,
       0,     0,    76,     0,   414,     0,     0,    77,    76,     0,
      78,    79,     0,    77,    76,     0,    78,    79,     0,    77,
       0,     0,    78,    79,   249,   250,   251,   252,   253,   254,
       0,     0,     0,   494,     0,   136,   256,   257,   258,   259,
     260,   261,     0,     0,     0,   262,   363,   364,   365,   366,
     367,   368,     0,     0,     0,   369
};

static const short int yycheck[] =
{
       1,     2,   244,   184,   145,   106,   149,   145,    15,    16,
      25,   206,    13,    14,    15,    16,   206,    18,    15,    20,
     184,   184,   114,    24,    25,    32,    27,    24,    29,    23,
      24,    32,    33,    34,   145,    25,    37,    38,   184,   379,
      41,   114,   382,   184,   184,    25,    47,    48,    49,   150,
      51,    52,    42,   145,    55,   145,    25,    51,    52,    42,
      61,    62,    63,    46,    65,   206,   433,    47,   206,   436,
      71,   163,   213,   184,    46,   213,    77,   416,    25,    48,
     419,   438,   225,   226,   441,   158,    78,    79,    60,   270,
     163,    25,   184,     0,   184,    96,    97,    98,   293,   100,
      47,   244,   213,   293,    76,   106,   270,   270,   109,   351,
      44,   184,    27,   114,   206,   116,   206,   114,    39,    25,
      18,   213,    39,   213,   270,    25,    42,   467,    41,   270,
     270,    24,    25,    48,    40,    33,    51,   138,   505,    37,
      40,   133,   134,   135,   145,    26,    27,    16,   145,   150,
     489,   508,   293,   493,    47,   293,    29,   158,    41,   270,
     527,    16,   163,    61,   136,    41,   163,   453,    49,    50,
      39,    16,    25,   316,   531,   514,    49,    16,   270,    52,
     270,    96,    55,   184,    39,    41,   187,   184,   474,    42,
      25,   558,    41,   479,    39,    24,    25,   270,    27,    16,
      39,   293,   559,   293,    25,   206,     7,    42,   351,   206,
     211,    25,   213,   553,    41,    32,   213,   556,    47,    48,
      39,    42,    51,   224,    97,    98,    40,   100,    41,    20,
      25,   232,   233,    25,   235,   521,    25,    25,   239,    15,
      16,    41,    18,    34,    25,    40,    42,    38,    40,    45,
      41,    40,    40,    25,    31,   541,    32,    33,   544,    40,
     546,    37,   234,   264,    43,   138,   238,    96,    40,   270,
     242,    62,    63,   270,    65,    53,    54,    55,    25,   251,
     252,   253,   254,   255,    30,    61,   258,   259,   260,   261,
     262,     4,   293,    40,     7,     8,   293,    23,    24,    25,
      43,    25,     7,    23,    24,    25,   307,     5,     6,     7,
      23,    24,    25,    39,    25,   287,    40,    43,   109,    44,
     421,    39,    48,    43,    44,    51,    52,    39,    48,    40,
      43,    51,    52,    25,   306,    48,   308,    25,    51,    52,
       7,     8,     5,     6,     7,     3,     4,   348,    40,    56,
     322,    42,    40,    23,    24,    25,   357,    28,    29,    25,
      23,    24,    25,    39,   336,    48,   338,    48,   340,    39,
     342,    43,   344,    43,    40,   347,    44,   349,    48,    43,
      43,    51,    52,    25,   356,    48,   358,    42,    51,    52,
      42,   492,    42,   365,   366,   367,   368,   369,    40,   371,
      51,    52,    43,    23,    24,    25,    43,     4,    42,   381,
       7,     8,   127,   128,   129,   130,     6,     7,    43,    39,
     421,    43,   423,    43,   396,    23,    24,    25,    48,   401,
      43,    51,    52,    42,   406,    42,   408,    42,   410,    42,
     412,    39,   414,    42,    43,    43,   418,    42,    43,    42,
      48,   423,   453,    51,    52,   456,   428,   429,   430,   431,
     432,    44,    45,   435,    23,    24,    25,    42,   440,    43,
      23,    24,    25,   474,    44,    45,    23,    24,   479,    43,
      39,   453,    44,    45,    43,    43,    39,    42,    43,    48,
      43,   492,    51,    52,   466,    48,    42,    43,    51,    52,
      44,    45,   474,    44,    45,   131,   132,   479,   125,   126,
     482,   483,   484,   485,   486,    42,   488,    43,    25,    43,
     521,    43,   494,    42,    42,    32,    33,    34,    35,    36,
      37,    42,   504,    42,    41,   507,    43,    42,    41,    45,
     541,    42,    44,   544,    44,   546,    42,    42,    42,   521,
       9,    10,    11,    12,    13,    14,    15,    16,    42,    18,
      19,    20,    42,    42,    23,    24,    25,    44,    41,   541,
      44,    42,   544,    42,   546,    42,    17,    45,    42,    45,
      45,    40,    45,    42,    43,    41,    23,    24,    25,    48,
      44,    44,    51,    52,     9,    10,    11,    12,    13,    14,
      15,    16,    39,    18,    19,    20,    43,    41,    23,    24,
      25,    48,    44,    44,    51,    52,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    40,    17,    42,    43,    45,
      42,    45,    45,    48,    45,    45,    51,    52,     9,    10,
      11,    12,    13,    14,    15,    16,    44,    18,    40,    20,
      21,    40,    23,    24,    25,    32,    33,    34,    35,    36,
      37,    40,    40,    17,    41,    40,    43,    17,    42,    40,
      42,    42,    43,    42,    44,    42,    42,    48,    42,    42,
      51,    52,     9,    10,    11,    12,    13,    14,    15,    16,
      42,    18,    40,    20,    21,    44,    23,    24,    25,    12,
      13,    14,    15,    16,    44,    18,    19,    40,    40,    40,
      23,    24,    25,    40,    40,    42,    43,    42,    42,    42,
      42,    48,    42,    42,    51,    52,    42,    40,    42,    42,
      43,     4,    44,    44,    44,    48,    44,    14,    51,    52,
      12,    13,    14,    15,    16,    24,    15,    19,   107,   270,
      22,    23,    24,    25,    12,    13,    14,    15,    16,   293,
      18,    19,   213,   163,   508,    23,    24,    25,    40,   505,
      42,    43,   489,   467,   312,    -1,    48,   123,   492,    51,
      52,   124,    40,   316,    42,    43,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    51,    52,    12,    13,    14,    15,    16,
      -1,    -1,    19,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    42,    43,    -1,    39,    -1,
      -1,    48,    43,    -1,    51,    52,    -1,    48,    -1,    -1,
      51,    52,    23,    24,    25,    -1,    -1,    -1,    23,    24,
      25,    -1,    -1,    -1,    23,    24,    25,    -1,    39,    -1,
      -1,    -1,    43,    -1,    39,    -1,    -1,    48,    43,    -1,
      51,    52,    -1,    48,    43,    -1,    51,    52,    -1,    48,
      -1,    -1,    51,    52,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    41,    -1,    43,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    41,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    58,    59,    60,    61,    62,    25,   130,
     130,     0,    60,    39,    39,    63,    66,    67,    73,    74,
      77,    78,    96,   130,    63,    64,    65,    69,    70,    75,
      76,   130,    66,    73,    77,    96,    67,    73,    77,   130,
      74,    77,   130,    40,    78,   130,    41,    64,    69,    75,
      65,    69,    75,   130,    70,    75,   130,    40,    76,   130,
      41,    73,    77,    77,    40,    77,    40,    41,    40,    41,
      41,     4,     7,     8,    23,    24,    43,    48,    51,    52,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     130,   131,   132,   134,   135,   136,    69,    75,    75,    40,
      75,    40,    41,    40,    41,    41,     5,     6,     7,    77,
      40,    40,    40,   130,    39,    82,    43,    71,   118,   130,
     125,   125,    42,    31,    30,    28,    29,    26,    27,    49,
      50,    51,    52,    53,    54,    55,    43,   128,    75,    40,
      40,    40,   127,   130,    71,    39,    81,    40,    42,    43,
       9,    10,    11,    12,    13,    14,    15,    16,    18,    19,
      20,    40,    42,    86,    90,    91,    95,    96,    97,    98,
     104,   105,   106,   107,   108,   109,   116,   117,   118,   130,
     132,    44,    72,   130,    39,    80,    44,    56,   120,   121,
     122,   122,   123,   123,   123,   123,   124,   124,   125,   125,
     125,    44,   118,   129,    40,    42,    39,    79,    12,    13,
      16,    18,    40,    85,    89,    91,    94,    96,    97,   103,
     105,   106,   108,   111,   130,    51,    52,    68,   133,   134,
     127,   130,    48,    48,    43,    43,    42,    42,    43,    48,
     130,   132,    43,    42,    43,    40,    90,    42,    42,    32,
      33,    34,    35,    36,    37,    41,    32,    33,    34,    35,
      36,    37,    41,    44,    45,    12,    13,    16,    21,    40,
      84,    88,    91,    93,    96,    97,    98,   102,   105,   106,
     107,   109,   110,   116,   117,   130,    44,    45,    12,    13,
      16,    22,    40,    83,    87,    91,    92,    96,    97,    99,
     101,   105,   108,   111,   115,   131,    43,    43,    43,    40,
      89,    42,   130,   134,   134,    44,    45,    42,    42,   130,
     130,   118,    42,   130,   118,   130,    42,    42,   118,    68,
     118,   118,   118,   118,    42,    42,    39,   118,    39,   118,
      39,   118,    39,   118,    39,   118,   130,    43,    43,    43,
      42,    43,    40,    88,    42,   118,    43,    43,    43,    42,
      40,    87,    42,    32,    33,    34,    35,    36,    37,    41,
     118,    42,   130,   118,   128,    42,   133,    42,    42,    44,
     118,    41,    44,    44,    44,   118,    42,   118,    42,   118,
      42,   118,    42,   118,    42,   118,    42,   130,   118,    68,
     118,    42,   130,   118,    42,    42,    39,   118,    39,   118,
      39,   118,    39,   118,    39,   118,    44,   118,    41,    44,
      42,    46,    82,    42,   118,    82,    42,    42,    45,    45,
      45,    45,    45,    44,   118,    41,    44,    44,    44,   118,
      41,    44,   118,    42,   118,    42,   118,    42,   118,    42,
     118,    42,    81,    42,   118,    81,    47,   112,   113,   114,
     127,   130,    97,   100,   118,   130,    42,    17,   118,   118,
     118,   118,   118,    80,    42,   118,    80,    42,    79,    42,
     118,    79,    45,    45,    45,    45,    45,   100,    42,    17,
     130,    42,    45,    44,    41,   118,    82,    95,    40,    40,
      40,    40,    40,   100,    42,    17,   100,    42,    17,   118,
     118,   118,   118,   118,    44,   118,    81,    94,   113,    82,
     118,    42,    42,    42,    42,    42,    42,    44,   118,    80,
      93,    44,   118,    79,    92,    40,    40,    40,    40,    40,
      81,    42,   100,    80,    42,    79,    42,    42,    42,    42,
      42,    42,   100,    44,   100,   100,    44,    82,    44,    44,
      81,    80,    79
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
#line 225 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 232 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 236 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 245 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 249 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 256 "BulletParser.y"
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
#line 267 "BulletParser.y"
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
#line 278 "BulletParser.y"
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
#line 289 "BulletParser.y"
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
#line 300 "BulletParser.y"
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
#line 311 "BulletParser.y"
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
#line 322 "BulletParser.y"
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
#line 333 "BulletParser.y"
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
#line 347 "BulletParser.y"
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
#line 358 "BulletParser.y"
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
#line 369 "BulletParser.y"
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
#line 380 "BulletParser.y"
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
#line 391 "BulletParser.y"
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
#line 402 "BulletParser.y"
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
#line 413 "BulletParser.y"
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
#line 424 "BulletParser.y"
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
#line 438 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 442 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 451 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 455 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 464 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 28:
#line 473 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 477 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 486 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 31:
#line 492 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 32:
#line 502 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 33:
#line 506 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 34:
#line 515 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 35:
#line 519 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 36:
#line 528 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 37:
#line 538 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 38:
#line 542 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 39:
#line 549 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 40:
#line 554 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 41:
#line 566 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 42:
#line 570 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 43:
#line 579 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 44:
#line 590 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 45:
#line 594 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 46:
#line 603 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 612 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 48:
#line 616 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 49:
#line 625 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 634 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 51:
#line 638 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 52:
#line 645 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 53:
#line 649 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 54:
#line 656 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 55:
#line 660 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 56:
#line 667 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 57:
#line 671 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 58:
#line 678 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 59:
#line 682 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 60:
#line 691 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 61:
#line 695 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 62:
#line 704 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 708 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 64:
#line 717 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 721 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 66:
#line 730 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 734 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 738 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 742 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 70:
#line 746 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 750 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 754 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 758 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 762 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 766 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 773 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 777 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 781 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 785 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 80:
#line 789 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 793 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 797 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 801 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 805 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 809 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 813 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 817 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 821 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 828 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 832 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 836 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 840 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 93:
#line 844 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 848 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 852 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 856 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 860 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 867 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 871 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 875 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 879 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 102:
#line 883 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 887 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 891 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 895 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 899 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 903 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 907 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 911 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 915 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 922 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 112:
#line 926 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 113:
#line 933 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 114:
#line 939 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 115:
#line 946 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 116:
#line 956 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 117:
#line 962 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 118:
#line 969 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 119:
#line 979 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 120:
#line 985 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 121:
#line 992 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 122:
#line 1002 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 123:
#line 1008 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 124:
#line 1015 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 125:
#line 1025 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 126:
#line 1034 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-1]));
		;}
    break;

  case 127:
#line 1039 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-1]));
		;}
    break;

  case 128:
#line 1044 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 129:
#line 1049 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 130:
#line 1054 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 131:
#line 1059 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 132:
#line 1067 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1073 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 134:
#line 1080 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 135:
#line 1085 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 136:
#line 1090 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 137:
#line 1095 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 138:
#line 1100 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 139:
#line 1105 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 140:
#line 1110 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 141:
#line 1116 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1122 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 143:
#line 1128 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 144:
#line 1137 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 145:
#line 1143 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 146:
#line 1150 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1155 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 148:
#line 1160 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 149:
#line 1165 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 150:
#line 1170 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 151:
#line 1175 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 152:
#line 1180 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 153:
#line 1186 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 154:
#line 1192 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 155:
#line 1198 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 156:
#line 1207 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 157:
#line 1211 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 158:
#line 1217 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 159:
#line 1224 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 160:
#line 1230 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 161:
#line 1238 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, (yyvsp[-8]));
			initExpr->setChild(1, (yyvsp[-6]));
			
			(yyval)->setChild(0, initExpr);
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 162:
#line 1254 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 163:
#line 1260 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 164:
#line 1268 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, (yyvsp[-8]));
			initExpr->setChild(1, (yyvsp[-6]));
			
			(yyval)->setChild(0, initExpr);
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 165:
#line 1284 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 166:
#line 1290 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 167:
#line 1298 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, (yyvsp[-8]));
			initExpr->setChild(1, (yyvsp[-6]));
			
			(yyval)->setChild(0, initExpr);
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 168:
#line 1314 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 169:
#line 1320 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 170:
#line 1328 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			YYSTYPE initExpr = AST->createNode(PT_AssignStatement, yylineno);
			initExpr->setChild(0, (yyvsp[-8]));
			initExpr->setChild(1, (yyvsp[-6]));
			
			(yyval)->setChild(0, initExpr);
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 171:
#line 1344 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 172:
#line 1348 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 173:
#line 1355 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 174:
#line 1363 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 175:
#line 1371 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 176:
#line 1379 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
		;}
    break;

  case 177:
#line 1383 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 178:
#line 1390 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
		;}
    break;

  case 179:
#line 1394 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 180:
#line 1402 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 181:
#line 1412 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 182:
#line 1424 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 183:
#line 1428 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 184:
#line 1437 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 185:
#line 1441 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 186:
#line 1446 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 187:
#line 1453 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Anchor, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 188:
#line 1462 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 189:
#line 1469 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 190:
#line 1474 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 191:
#line 1482 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 192:
#line 1488 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 193:
#line 1497 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1505 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 195:
#line 1509 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1518 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 197:
#line 1522 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1531 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 199:
#line 1535 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 200:
#line 1541 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 201:
#line 1550 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 202:
#line 1554 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 203:
#line 1560 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1566 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1572 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 206:
#line 1581 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1585 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1591 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 209:
#line 1600 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1604 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 211:
#line 1610 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 212:
#line 1616 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 213:
#line 1625 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 214:
#line 1629 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 215:
#line 1634 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 216:
#line 1642 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 217:
#line 1646 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 218:
#line 1650 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 219:
#line 1654 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 220:
#line 1658 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 221:
#line 1662 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 222:
#line 1669 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 223:
#line 1678 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 224:
#line 1682 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 225:
#line 1689 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 226:
#line 1694 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 227:
#line 1706 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 228:
#line 1714 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 229:
#line 1723 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 230:
#line 1734 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 231:
#line 1738 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 232:
#line 1742 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 233:
#line 1750 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 234:
#line 1754 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 235:
#line 1761 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 236:
#line 1769 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3950 "bsBulletParser.cpp"

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


#line 1775 "BulletParser.y"


	
	

