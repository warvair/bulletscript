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
#define YYLAST   949

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  82
/* YYNRULES -- Number of rules. */
#define YYNRULES  246
/* YYNRULES -- Number of states. */
#define YYNSTATES  588

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
       2,     2,     2,     2,     2,     2,    47,    55,    49,     2,
      43,    44,    54,    52,    45,    53,    56,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    42,
      50,    41,    51,     2,     2,     2,     2,     2,     2,     2,
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
     196,   200,   202,   205,   211,   213,   216,   221,   228,   230,
     233,   238,   245,   248,   252,   255,   259,   262,   266,   269,
     273,   275,   278,   280,   283,   285,   288,   290,   293,   295,
     297,   299,   302,   304,   306,   308,   310,   312,   314,   316,
     318,   320,   323,   325,   327,   329,   331,   333,   335,   337,
     339,   341,   343,   345,   347,   349,   351,   354,   356,   358,
     360,   362,   364,   366,   368,   370,   373,   375,   377,   379,
     381,   383,   385,   387,   389,   391,   393,   395,   397,   400,
     406,   414,   422,   428,   436,   444,   450,   458,   466,   472,
     480,   488,   493,   496,   499,   503,   507,   511,   515,   520,
     529,   533,   537,   542,   547,   552,   557,   566,   575,   584,
     593,   598,   607,   611,   615,   620,   625,   630,   635,   644,
     653,   662,   671,   673,   677,   679,   685,   694,   706,   712,
     721,   733,   739,   748,   760,   766,   775,   787,   790,   793,
     797,   801,   807,   810,   816,   821,   829,   832,   838,   843,
     851,   858,   863,   865,   869,   871,   873,   875,   878,   881,
     885,   889,   894,   899,   901,   903,   907,   909,   913,   915,
     919,   923,   925,   929,   933,   937,   941,   943,   947,   951,
     953,   957,   961,   965,   967,   970,   973,   975,   977,   979,
     981,   983,   987,   990,   993,   997,   999,  1003,  1005,  1008,
    1013,  1015,  1018,  1021,  1023,  1025,  1027
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      58,     0,    -1,    59,    -1,    60,    -1,    59,    60,    -1,
      61,    -1,    62,    -1,     4,   132,    39,    75,    40,    -1,
       4,   132,    39,    69,    75,    40,    -1,     4,   132,    39,
      64,    75,    40,    -1,     4,   132,    39,    64,    69,    75,
      40,    -1,     4,   132,    39,    63,    75,    40,    -1,     4,
     132,    39,    63,    69,    75,    40,    -1,     4,   132,    39,
      63,    64,    75,    40,    -1,     4,   132,    39,    63,    64,
      69,    75,    40,    -1,     3,   132,    39,    77,    40,    -1,
       3,   132,    39,    73,    77,    40,    -1,     3,   132,    39,
      66,    77,    40,    -1,     3,   132,    39,    66,    73,    77,
      40,    -1,     3,   132,    39,    63,    77,    40,    -1,     3,
     132,    39,    63,    73,    77,    40,    -1,     3,   132,    39,
      63,    66,    77,    40,    -1,     3,   132,    39,    63,    66,
      73,    77,    40,    -1,    96,    -1,    63,    96,    -1,    65,
      -1,    64,    65,    -1,   132,    41,     5,   129,    42,    -1,
      67,    -1,    66,    67,    -1,   132,    41,     4,   132,    42,
      -1,   132,    41,     4,   132,    43,    68,    44,    42,    -1,
     135,    -1,    68,    45,   135,    -1,    70,    -1,    69,    70,
      -1,   132,    41,     6,    71,    79,    -1,    43,    44,    -1,
      43,    72,    44,    -1,   132,    -1,    72,    45,   132,    -1,
      74,    -1,    73,    74,    -1,   132,    41,     8,    71,    80,
      -1,    76,    -1,    75,    76,    -1,   132,    41,     7,    81,
      -1,   132,    41,     7,    46,   137,    81,    -1,    78,    -1,
      77,    78,    -1,   132,    41,     7,    82,    -1,   132,    41,
       7,    46,   137,    82,    -1,    39,    40,    -1,    39,    83,
      40,    -1,    39,    40,    -1,    39,    84,    40,    -1,    39,
      40,    -1,    39,    85,    40,    -1,    39,    40,    -1,    39,
      86,    40,    -1,    87,    -1,    83,    87,    -1,    88,    -1,
      84,    88,    -1,    89,    -1,    85,    89,    -1,    90,    -1,
      86,    90,    -1,    91,    -1,    92,    -1,    96,    -1,    97,
      42,    -1,    99,    -1,   101,    -1,   105,    -1,   108,    -1,
     113,    -1,   117,    -1,    91,    -1,    93,    -1,    96,    -1,
      97,    42,    -1,    98,    -1,   102,    -1,   105,    -1,   106,
      -1,   107,    -1,   118,    -1,   109,    -1,   110,    -1,   111,
      -1,   112,    -1,   119,    -1,    91,    -1,    94,    -1,    96,
      -1,    97,    42,    -1,   103,    -1,   105,    -1,   106,    -1,
     108,    -1,   113,    -1,    91,    -1,    95,    -1,    96,    -1,
      97,    42,    -1,    98,    -1,   104,    -1,   105,    -1,   106,
      -1,   107,    -1,   108,    -1,   109,    -1,   110,    -1,   112,
      -1,   118,    -1,   119,    -1,    42,    -1,   120,    42,    -1,
      16,    43,   120,    44,    79,    -1,    16,    43,   120,    44,
      79,    17,    79,    -1,    16,    43,   120,    44,    79,    17,
      92,    -1,    16,    43,   120,    44,    80,    -1,    16,    43,
     120,    44,    80,    17,    80,    -1,    16,    43,   120,    44,
      80,    17,    93,    -1,    16,    43,   120,    44,    81,    -1,
      16,    43,   120,    44,    81,    17,    81,    -1,    16,    43,
     120,    44,    81,    17,    94,    -1,    16,    43,   120,    44,
      82,    -1,    16,    43,   120,    44,    82,    17,    82,    -1,
      16,    43,   120,    44,    82,    17,    95,    -1,   132,    41,
     120,    42,    -1,   132,    32,    -1,   132,    33,    -1,   132,
      34,   120,    -1,   132,    35,   120,    -1,   132,    36,   120,
      -1,   132,    37,   120,    -1,   134,    41,   120,    42,    -1,
     134,    41,    39,   120,    45,   120,    40,    42,    -1,   134,
      32,    42,    -1,   134,    33,    42,    -1,   134,    34,   120,
      42,    -1,   134,    35,   120,    42,    -1,   134,    36,   120,
      42,    -1,   134,    37,   120,    42,    -1,   134,    34,    39,
     120,    45,   120,    40,    42,    -1,   134,    35,    39,   120,
      45,   120,    40,    42,    -1,   134,    36,    39,   120,    45,
     120,    40,    42,    -1,   134,    37,    39,   120,    45,   120,
      40,    42,    -1,   133,    41,   120,    42,    -1,   133,    41,
      39,   120,    45,   120,    40,    42,    -1,   133,    32,    42,
      -1,   133,    33,    42,    -1,   133,    34,   120,    42,    -1,
     133,    35,   120,    42,    -1,   133,    36,   120,    42,    -1,
     133,    37,   120,    42,    -1,   133,    34,    39,   120,    45,
     120,    40,    42,    -1,   133,    35,    39,   120,    45,   120,
      40,    42,    -1,   133,    36,    39,   120,    45,   120,    40,
      42,    -1,   133,    37,    39,   120,    45,   120,    40,    42,
      -1,   120,    -1,   132,    41,   120,    -1,    97,    -1,    12,
      43,   120,    44,    79,    -1,    13,    43,    42,   120,    42,
     100,    44,    79,    -1,    13,    43,   132,    41,   120,    42,
     120,    42,   100,    44,    79,    -1,    12,    43,   120,    44,
      80,    -1,    13,    43,    42,   120,    42,   100,    44,    80,
      -1,    13,    43,   132,    41,   120,    42,   120,    42,   100,
      44,    80,    -1,    12,    43,   120,    44,    81,    -1,    13,
      43,    42,   120,    42,   100,    44,    81,    -1,    13,    43,
     132,    41,   120,    42,   120,    42,   100,    44,    81,    -1,
      12,    43,   120,    44,    82,    -1,    13,    43,    42,   120,
      42,   100,    44,    82,    -1,    13,    43,   132,    41,   120,
      42,   120,    42,   100,    44,    82,    -1,    14,    42,    -1,
      15,    42,    -1,    18,   132,    42,    -1,    18,   134,    42,
      -1,    19,    43,   120,    44,    42,    -1,    20,    42,    -1,
      20,    43,    68,    44,    42,    -1,    20,    47,   132,    42,
      -1,    20,    47,   132,    43,    68,    44,    42,    -1,    21,
      42,    -1,    21,    43,    68,    44,    42,    -1,    21,    47,
     132,    42,    -1,    21,    47,   132,    43,    68,    44,    42,
      -1,   132,   132,   130,    48,   114,    42,    -1,   132,   132,
     130,    42,    -1,   115,    -1,   114,    45,   115,    -1,   129,
      -1,   132,    -1,   116,    -1,    49,   132,    -1,    22,    42,
      -1,     9,   129,    42,    -1,     9,   132,    42,    -1,    10,
      47,   132,    42,    -1,    11,    47,   132,    42,    -1,   121,
      -1,   122,    -1,   121,    31,   122,    -1,   123,    -1,   122,
      30,   123,    -1,   124,    -1,   123,    28,   124,    -1,   123,
      29,   124,    -1,   125,    -1,   124,    50,   125,    -1,   124,
      51,   125,    -1,   124,    26,   125,    -1,   124,    27,   125,
      -1,   126,    -1,   125,    52,   126,    -1,   125,    53,   126,
      -1,   127,    -1,   126,    54,   127,    -1,   126,    46,   127,
      -1,   126,    55,   127,    -1,   128,    -1,    52,   127,    -1,
      53,   127,    -1,   132,    -1,   133,    -1,   134,    -1,   129,
      -1,   136,    -1,    43,   120,    44,    -1,   132,   130,    -1,
      43,    44,    -1,    43,   131,    44,    -1,   120,    -1,   131,
      45,   120,    -1,    25,    -1,    47,   132,    -1,    47,   132,
      56,   132,    -1,   136,    -1,    52,   136,    -1,    53,   136,
      -1,   137,    -1,   138,    -1,    23,    -1,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   224,   224,   231,   235,   244,   248,   255,   266,   277,
     288,   299,   310,   321,   332,   346,   357,   368,   379,   390,
     401,   412,   423,   437,   441,   450,   454,   463,   472,   476,
     485,   491,   501,   505,   514,   518,   527,   537,   541,   548,
     553,   565,   569,   578,   589,   593,   602,   608,   618,   622,
     631,   637,   647,   651,   658,   662,   669,   673,   680,   684,
     691,   695,   704,   708,   717,   721,   730,   734,   743,   747,
     751,   755,   759,   763,   767,   771,   775,   779,   786,   790,
     794,   798,   802,   806,   810,   814,   818,   822,   826,   830,
     834,   838,   842,   849,   853,   857,   861,   865,   869,   873,
     877,   881,   888,   892,   896,   900,   904,   908,   912,   916,
     920,   924,   928,   932,   936,   940,   944,   951,   955,   962,
     968,   975,   985,   991,   998,  1008,  1014,  1021,  1031,  1037,
    1044,  1054,  1063,  1068,  1073,  1078,  1083,  1088,  1096,  1102,
    1109,  1114,  1119,  1124,  1129,  1134,  1139,  1145,  1151,  1157,
    1166,  1172,  1179,  1184,  1189,  1194,  1199,  1204,  1209,  1215,
    1221,  1227,  1236,  1240,  1246,  1253,  1259,  1267,  1283,  1289,
    1297,  1313,  1319,  1327,  1343,  1349,  1357,  1373,  1377,  1384,
    1392,  1400,  1408,  1412,  1420,  1425,  1434,  1438,  1446,  1451,
    1460,  1470,  1482,  1486,  1495,  1499,  1504,  1511,  1520,  1527,
    1532,  1540,  1546,  1555,  1563,  1567,  1576,  1580,  1589,  1593,
    1599,  1608,  1612,  1618,  1624,  1630,  1639,  1643,  1649,  1658,
    1662,  1668,  1674,  1683,  1687,  1692,  1700,  1704,  1708,  1712,
    1716,  1720,  1727,  1736,  1740,  1747,  1752,  1764,  1772,  1781,
    1792,  1796,  1800,  1808,  1812,  1819,  1827
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
  "'}'", "'='", "';'", "'('", "')'", "','", "'/'", "'$'", "':'", "'&'",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'%'", "'.'", "$accept",
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
  "suspend_statement", "member_suspend_statement", "signal_statement",
  "member_signal_statement", "emit_statement", "controller_list",
  "controller_entry", "anchor", "die_statement", "raise_statement",
  "enable_statement", "constant_expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "primary_expression", "function_call", "function_call_arguments",
  "argument_expression_list", "identifier", "property", "emitter_member",
  "signed_constant", "unsigned_constant", "constant_integer",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   123,
     125,    61,    59,    40,    41,    44,    47,    36,    58,    38,
      60,    62,    43,    45,    42,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    91,    92,
      92,    92,    93,    93,    93,    94,    94,    94,    95,    95,
      95,    96,    97,    97,    97,    97,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   101,   101,   101,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   105,   105,   106,
     107,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   114,   114,   115,   115,   115,   116,   117,   118,
     118,   119,   119,   120,   121,   121,   122,   122,   123,   123,
     123,   124,   124,   124,   124,   124,   125,   125,   125,   126,
     126,   126,   126,   127,   127,   127,   128,   128,   128,   128,
     128,   128,   129,   130,   130,   131,   131,   132,   133,   134,
     135,   135,   135,   136,   136,   137,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     6,     6,
       7,     6,     7,     7,     8,     5,     6,     6,     7,     6,
       7,     7,     8,     1,     2,     1,     2,     5,     1,     2,
       5,     8,     1,     3,     1,     2,     5,     2,     3,     1,
       3,     1,     2,     5,     1,     2,     4,     6,     1,     2,
       4,     6,     2,     3,     2,     3,     2,     3,     2,     3,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       7,     7,     5,     7,     7,     5,     7,     7,     5,     7,
       7,     4,     2,     2,     3,     3,     3,     3,     4,     8,
       3,     3,     4,     4,     4,     4,     8,     8,     8,     8,
       4,     8,     3,     3,     4,     4,     4,     4,     8,     8,
       8,     8,     1,     3,     1,     5,     8,    11,     5,     8,
      11,     5,     8,    11,     5,     8,    11,     2,     2,     3,
       3,     5,     2,     5,     4,     7,     2,     5,     4,     7,
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
       0,     0,     0,     0,     2,     3,     5,     6,   237,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    41,
       0,    48,    23,     0,     0,     0,    25,     0,    34,     0,
      44,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      42,     0,     0,    15,    49,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    35,     0,     0,     7,    45,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   245,   246,     0,     0,     0,     0,
       0,   203,   204,   206,   208,   211,   216,   219,   223,   229,
     226,   227,   228,   230,   243,   244,     0,     0,     0,    11,
       0,     9,     0,     8,     0,     0,     0,     0,     0,     0,
      21,    20,    18,     0,     0,     0,    50,     0,     0,     0,
     238,   224,   225,   131,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   232,     0,
      13,    12,    10,     0,     0,     0,     0,     0,    46,    22,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,   117,     0,    66,   102,   103,
     104,     0,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,   226,   228,     0,    37,     0,    39,
       0,    43,   231,     0,   205,   207,   209,   210,   214,   215,
     212,   213,   217,   218,   221,   220,   222,   233,   235,     0,
      14,    27,     0,    36,     0,     0,     0,     0,    56,     0,
      64,    93,    94,    95,     0,    97,    98,    99,   100,   101,
     226,     0,     0,     0,     0,    32,   240,     0,     0,     0,
       0,     0,     0,   177,   178,     0,     0,     0,     0,     0,
     182,     0,     0,     0,    59,    67,   105,   118,   132,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    38,     0,     0,     0,     0,     0,    54,
       0,    62,    78,    79,    80,     0,    82,    83,    84,    85,
      86,    88,    89,    90,    91,    87,    92,   239,   234,     0,
       0,     0,     0,     0,    52,     0,    60,    68,    69,    70,
       0,    72,    73,    74,    75,    76,    77,   227,     0,     0,
       0,    57,    65,    96,     0,    47,   241,   242,     0,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,   179,
     180,     0,     0,     0,     0,   134,   135,   136,   137,   140,
     141,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    40,     0,     0,     0,   186,     0,    55,    63,    81,
     236,     0,     0,     0,   198,    53,    61,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    33,   201,   202,     0,     0,     0,     0,     0,     0,
     184,     0,   188,     0,     0,   142,     0,   143,     0,   144,
       0,   145,     0,   138,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   191,
       0,   174,     0,     0,   128,   181,   183,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   154,     0,   155,     0,   156,     0,
     157,     0,   150,   171,     0,     0,   125,     0,     0,   192,
     196,   194,   195,   164,     0,   162,   226,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   168,     0,     0,   122,
     187,   165,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,   197,   190,     0,     0,     0,     0,   129,
     130,   185,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   193,   175,   163,     0,   146,   147,   148,
     149,   139,     0,     0,   123,   124,     0,     0,   120,   121,
       0,     0,     0,     0,     0,   172,     0,     0,   169,     0,
     166,     0,   158,   159,   160,   161,   151,     0,     0,     0,
       0,     0,   176,     0,     0,   173,   170,   167
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,   234,    27,    28,   118,   188,    18,    19,    29,    30,
      20,    21,   213,   191,   148,   116,   305,   280,   219,   166,
     306,   281,   220,   167,   168,   308,   283,   222,   169,    22,
     483,   172,   311,   484,   312,   287,   225,   173,   174,   175,
     176,   177,   178,   179,   293,   180,   229,   478,   479,   480,
     316,   181,   182,   183,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   138,   209,    90,    91,    92,   235,    93,
      94,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -446
static const short int yypact[] =
{
      89,   -20,   -20,    63,    89,  -446,  -446,  -446,  -446,   -21,
      42,  -446,  -446,   -20,   -20,   -20,   -20,  -446,   -20,  -446,
     -15,  -446,  -446,   129,   -20,   -20,  -446,   -20,  -446,   185,
    -446,   142,   -20,   -20,   195,  -446,  -446,   -20,   206,   182,
    -446,   207,   186,  -446,  -446,   192,   270,   -20,   -20,   235,
    -446,   -20,   246,   214,  -446,   272,   221,  -446,  -446,   225,
     282,   -20,   284,   291,  -446,   301,  -446,   403,  -446,   242,
     123,   -20,   132,    96,  -446,  -446,   422,   -20,   422,   422,
     211,   241,   250,   322,   264,   342,    36,  -446,  -446,  -446,
     249,  -446,  -446,  -446,  -446,  -446,   -20,   305,   307,  -446,
     329,  -446,   398,  -446,   415,   289,   -20,    96,   135,   330,
    -446,  -446,  -446,   394,   366,   277,  -446,    28,   263,   300,
     316,  -446,  -446,  -446,   422,   422,   422,   422,   422,   422,
     422,   422,   422,   422,   422,   422,   422,   296,  -446,   348,
    -446,  -446,  -446,   286,   249,   294,   739,   277,  -446,  -446,
    -446,    65,   -20,   306,   309,   320,   331,   341,   357,   371,
     144,   380,   216,   384,  -446,  -446,   635,  -446,  -446,  -446,
    -446,   396,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,   400,   674,   898,   401,  -446,   399,  -446,
     680,  -446,  -446,   -20,   250,   322,   264,   264,   342,   342,
     342,   342,    36,    36,  -446,  -446,  -446,  -446,  -446,   427,
    -446,  -446,   781,  -446,   408,   412,   417,   -20,  -446,   795,
    -446,  -446,  -446,  -446,   416,  -446,  -446,  -446,  -446,  -446,
     598,   425,   443,   443,   440,  -446,  -446,   450,   452,   -20,
     -20,   422,   155,  -446,  -446,   422,   -20,   469,   481,   422,
    -446,    65,   -20,   -20,  -446,  -446,  -446,  -446,  -446,  -446,
     422,   422,   422,   422,   422,   483,   485,   377,   410,   463,
     466,   536,  -446,  -446,   -20,   439,   486,   490,   350,  -446,
     725,  -446,  -446,  -446,  -446,   498,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,   422,
     499,   500,   501,   509,  -446,   837,  -446,  -446,  -446,  -446,
     510,  -446,  -446,  -446,  -446,  -446,  -446,   908,   422,   160,
     422,  -446,  -446,  -446,   249,  -446,  -446,  -446,   512,    65,
    -446,  -446,   513,   514,   497,   422,   516,   522,   316,  -446,
    -446,   523,   453,   457,   461,  -446,  -446,  -446,  -446,  -446,
    -446,   422,   527,   422,   530,   422,   531,   422,   532,   422,
     534,  -446,   422,   162,   422,  -446,    65,  -446,  -446,  -446,
    -446,   422,   165,   422,  -446,  -446,  -446,  -446,   535,   538,
     539,   572,   844,   869,   876,   537,   422,   544,   543,    80,
    -446,  -446,  -446,  -446,   401,   548,   422,   401,   551,   556,
    -446,    65,  -446,    65,   555,  -446,   562,  -446,   564,  -446,
     565,  -446,   567,  -446,   557,   422,   575,   569,   476,   573,
     422,   577,   576,  -446,  -446,   422,   579,   422,   580,   422,
     585,   422,   586,   422,   594,   425,   595,   422,   425,  -446,
      30,  -446,   422,   596,   623,  -446,  -446,   487,   491,   422,
     422,   422,   422,   422,   263,   600,   422,   263,   610,   294,
     615,   422,   294,   616,  -446,   617,  -446,   619,  -446,   620,
    -446,   622,  -446,  -446,   422,   627,   653,   -20,   179,  -446,
    -446,  -446,   249,  -446,   628,  -446,   870,   422,   115,   629,
     631,   634,   636,   639,   640,   641,  -446,   422,   642,   666,
    -446,  -446,   422,   643,   669,   422,   422,   422,   422,   422,
     655,   422,   125,  -446,  -446,    30,   401,   422,   660,  -446,
    -446,  -446,  -446,   670,   671,   672,   676,   677,   681,   422,
     136,   682,   422,   145,   657,   684,   688,   689,   690,   425,
     679,  -446,  -446,  -446,  -446,  -446,   422,  -446,  -446,  -446,
    -446,  -446,   263,   700,  -446,  -446,   294,   702,  -446,  -446,
     705,   714,   717,   718,   719,  -446,   422,   687,  -446,   422,
    -446,   422,  -446,  -446,  -446,  -446,  -446,   722,   401,   726,
     727,   425,  -446,   263,   294,  -446,  -446,  -446
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -446,  -446,  -446,   712,  -446,  -446,   755,   749,   147,   759,
     212,  -243,    59,    18,   668,  -446,   104,   224,   152,    98,
     266,   202,  -421,  -427,  -229,  -180,  -446,  -446,  -446,  -446,
     471,   503,   561,   618,  -112,   252,   257,   276,   302,    -4,
     -79,  -151,  -446,  -445,  -446,  -446,  -446,  -446,   -75,  -125,
    -148,  -139,  -146,  -134,  -446,  -132,  -203,  -446,   274,  -446,
    -446,  -131,  -113,    97,  -446,   675,   673,   381,   297,   405,
     134,  -446,  -103,   477,  -446,    -1,  -196,   -92,   473,  -147,
     -72,  -446
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   325,   143,   236,     8,   272,   228,   342,   315,
       8,    35,    23,    31,    23,    39,   317,    42,    13,    45,
      35,   227,   185,    31,    53,    43,    56,   496,    59,   510,
     499,    39,    42,    45,   221,   171,    42,    45,   501,   286,
      45,   504,   290,   186,   291,    54,    53,    56,    59,   237,
      56,    59,   528,     8,    59,     8,   292,   531,   294,   295,
      42,    45,    45,    11,    45,   289,    54,   224,   248,    54,
     113,   226,   187,   314,   185,   231,   120,   296,   282,   477,
     228,    14,   134,    48,    51,   326,   327,   171,    74,    75,
     135,   136,     1,     2,   227,    56,    59,    59,   185,    59,
     307,   567,   315,   554,   236,   144,    96,   221,    45,   317,
     170,   285,   558,   184,    54,   288,   189,   232,   233,    33,
      37,   577,   439,   418,   579,   568,   580,    58,   440,   286,
      72,   159,   290,   310,   291,   570,    61,   313,    59,   117,
     224,   216,   223,    80,   226,   230,   292,    58,   294,   295,
      58,   238,   277,    58,   114,   289,   586,    80,   447,   247,
     448,   302,   170,   587,   146,   184,   314,   296,   282,     8,
      46,   114,    50,   119,   146,   190,    49,    52,   115,    55,
       8,   147,   236,    60,   212,     8,   284,     8,   185,   184,
       8,   246,   297,   307,    50,    58,    58,   335,    58,    97,
      98,   285,   386,   100,   415,   288,   473,   420,   309,   476,
       8,   230,   121,   122,   441,   223,   247,   444,   230,   236,
       8,   514,    44,    67,   515,    57,   310,    69,    36,   324,
     313,     8,     8,    70,   208,    64,    44,    58,   332,   333,
      44,   336,    40,    44,    36,   338,    66,    68,   139,    72,
      73,   343,   344,   123,   236,   102,   236,    40,   250,   251,
       8,    40,   104,   252,    44,    44,   105,    44,   204,   205,
     206,     8,   124,   361,    71,    99,   284,    72,    73,   184,
     125,    34,    38,   541,    41,    40,   101,   106,   107,   108,
     128,   129,   137,    74,    75,     8,   108,     8,    62,    63,
      74,   309,   190,    65,   230,    74,    75,     8,   519,     8,
     565,    44,   103,    76,   130,   131,     8,    77,   387,    74,
      75,     8,    78,    79,   110,    76,     8,   109,   211,    77,
       8,   111,     8,   212,    78,    79,   544,   481,   334,    76,
     207,   112,   337,    77,   192,   140,   341,   141,    78,    79,
     126,   127,   585,   239,     8,     8,   240,   345,   346,   347,
     348,    80,   416,   241,   352,   354,   356,   358,   360,   142,
     149,   421,   193,     8,   242,   152,   153,   154,   155,   156,
     157,   158,   159,   243,   160,   161,   162,   163,   210,    74,
      75,     8,   365,   366,   132,   133,   370,   253,   582,   244,
      74,    75,     8,   106,   107,   108,   164,    71,   165,    76,
      72,    73,   481,    77,   245,   385,   351,   388,    78,    79,
      76,   107,   108,   249,    77,   198,   199,   200,   201,    78,
      79,   253,   395,    74,    75,     8,   150,   151,   256,   482,
     114,   486,   257,   273,   274,    74,    75,     8,   404,   353,
     406,   318,   408,    76,   410,   319,   412,    77,   323,   414,
     320,   417,    78,    79,   146,    76,    74,    75,   419,    77,
     422,   298,   299,   486,    78,    79,   513,   426,   428,   430,
     432,   434,   362,   436,   328,   329,    74,    75,     8,    74,
      75,     8,   330,   443,   331,   137,   486,   399,   329,   400,
     401,   486,   355,   402,   403,   357,    76,   196,   197,    76,
      77,   339,   455,    77,   482,    78,    79,   460,    78,    79,
     458,   329,   463,   340,   465,   349,   467,   350,   469,   363,
     471,   489,   329,   364,   475,   490,   329,   202,   203,   485,
     369,   394,   371,   372,   373,   486,   491,   492,   493,   494,
     495,   374,   377,   498,   390,   392,   393,   396,   503,    74,
      75,     8,    74,    75,     8,   486,   397,   398,   486,   405,
     486,   485,   407,   409,   411,   359,   413,   423,   425,    76,
     424,   435,    76,    77,   518,   437,    77,   438,    78,    79,
     442,    78,    79,   445,   485,    74,    75,     8,   446,   485,
     449,   454,   534,   535,   536,   537,   538,   450,   540,   451,
     452,   427,   453,   457,   545,    76,   456,   459,   461,    77,
     462,   464,   466,     8,    78,    79,   553,   468,   470,   557,
     258,   259,   260,   261,   262,   263,   472,   474,   487,   264,
     488,   137,   497,   485,   152,   153,   154,   155,   156,   157,
     158,   159,   500,   160,   161,   162,   163,   502,    74,    75,
       8,   505,   506,   485,   507,   508,   485,   509,   485,   511,
     512,   521,   516,   522,   523,   254,   524,   165,    76,   525,
     526,   527,    77,   530,   529,   532,   533,    78,    79,   152,
     153,   154,   275,   276,   157,   158,   277,   560,   160,   539,
     162,   278,   546,    74,    75,     8,   258,   259,   260,   261,
     262,   263,   547,   548,   549,   264,    12,   137,   550,   551,
     279,   566,   165,    76,   561,   552,   556,    77,   562,   563,
     564,   578,    78,    79,   152,   153,   154,   275,   276,   157,
     158,   277,   569,   160,   571,   162,   278,   572,    74,    75,
       8,   214,   215,   157,   158,   216,   573,   217,   161,   574,
     575,   576,    74,    75,     8,   367,   581,   165,    76,    24,
     583,   584,    77,    47,    32,   145,   376,    78,    79,   218,
     322,   165,    76,   368,   255,   559,    77,   555,   542,   543,
     520,    78,    79,   300,   301,   157,   158,   302,   195,   194,
     161,   389,   391,   303,    74,    75,     8,   214,   215,   157,
     158,   216,     0,   217,   161,     0,     0,     0,    74,    75,
       8,   304,     0,   165,    76,     0,     0,     0,    77,     0,
       0,     0,     0,    78,    79,   321,     0,   165,    76,     0,
       0,     0,    77,     0,     0,     0,     0,    78,    79,   300,
     301,   157,   158,   302,     0,     0,   161,     0,     0,   303,
      74,    75,     8,     0,     0,     0,     0,    74,    75,     8,
       0,     0,     0,     0,     0,     0,     0,   375,     0,   165,
      76,     0,     0,   429,    77,     0,     0,    76,     0,    78,
      79,    77,    74,    75,     8,     0,    78,    79,     0,    74,
      75,     8,   258,   259,   260,   261,   262,   263,   431,     0,
       0,   517,    76,   137,     0,   433,    77,     0,     0,    76,
       0,    78,    79,    77,     0,     0,     0,     0,    78,    79,
     265,   266,   267,   268,   269,   270,     0,     0,     0,   271,
     378,   379,   380,   381,   382,   383,     0,     0,     0,   384
};

static const short int yycheck[] =
{
       1,     2,   231,   106,   151,    25,   186,   146,   251,   212,
      25,    15,    13,    14,    15,    16,   212,    18,    39,    20,
      24,   146,   114,    24,    25,    40,    27,   454,    29,   474,
     457,    32,    33,    34,   146,   114,    37,    38,   459,   190,
      41,   462,   190,   115,   190,    27,    47,    48,    49,   152,
      51,    52,   497,    25,    55,    25,   190,   502,   190,   190,
      61,    62,    63,     0,    65,   190,    48,   146,   160,    51,
      71,   146,    44,   212,   166,   147,    77,   190,   190,    49,
     219,    39,    46,    24,    25,   232,   233,   166,    23,    24,
      54,    55,     3,     4,   219,    96,    97,    98,   190,   100,
     212,   546,   305,   530,   251,   106,    47,   219,   109,   305,
     114,   190,   533,   114,    96,   190,   117,    52,    53,    15,
      16,   566,    42,   366,   569,   552,   571,    29,    48,   280,
       7,    16,   280,   212,   280,   556,    32,   212,   139,    43,
     219,    16,   146,    46,   219,   146,   280,    49,   280,   280,
      52,   152,    16,    55,    39,   280,   583,    60,   401,   160,
     403,    16,   166,   584,    39,   166,   305,   280,   280,    25,
      41,    39,    25,    76,    39,    39,    24,    25,    46,    27,
      25,    46,   329,    41,    39,    25,   190,    25,   280,   190,
      25,    47,   193,   305,    47,    97,    98,    42,   100,    47,
      48,   280,    42,    51,    42,   280,   435,    42,   212,   438,
      25,   212,    78,    79,   394,   219,   217,   397,   219,   366,
      25,    42,    20,    41,    45,    40,   305,    41,    16,   230,
     305,    25,    25,    41,   137,    40,    34,   139,   239,   240,
      38,   242,    18,    41,    32,   246,    40,    40,    96,     7,
       8,   252,   253,    42,   401,    41,   403,    33,    42,    43,
      25,    37,    41,    47,    62,    63,    41,    65,   134,   135,
     136,    25,    31,   274,     4,    40,   280,     7,     8,   280,
      30,    15,    16,   512,    18,    61,    40,     5,     6,     7,
      26,    27,    43,    23,    24,    25,     7,    25,    32,    33,
      23,   305,    39,    37,   305,    23,    24,    25,   488,    25,
     539,   109,    40,    43,    50,    51,    25,    47,   319,    23,
      24,    25,    52,    53,    40,    43,    25,    61,    42,    47,
      25,    40,    25,    39,    52,    53,   516,   440,   241,    43,
      44,    40,   245,    47,    44,    40,   249,    40,    52,    53,
      28,    29,   581,    47,    25,    25,    47,   260,   261,   262,
     263,   264,   363,    43,   267,   268,   269,   270,   271,    40,
      40,   372,    56,    25,    43,     9,    10,    11,    12,    13,
      14,    15,    16,    42,    18,    19,    20,    21,    40,    23,
      24,    25,    42,    43,    52,    53,   299,    47,   578,    42,
      23,    24,    25,     5,     6,     7,    40,     4,    42,    43,
       7,     8,   515,    47,    43,   318,    39,   320,    52,    53,
      43,     6,     7,    43,    47,   128,   129,   130,   131,    52,
      53,    47,   335,    23,    24,    25,    42,    43,    42,   440,
      39,   442,    42,    44,    45,    23,    24,    25,   351,    39,
     353,    43,   355,    43,   357,    43,   359,    47,    42,   362,
      43,   364,    52,    53,    39,    43,    23,    24,   371,    47,
     373,    44,    45,   474,    52,    53,   477,   380,   381,   382,
     383,   384,    43,   386,    44,    45,    23,    24,    25,    23,
      24,    25,    42,   396,    42,    43,   497,    44,    45,    42,
      43,   502,    39,    42,    43,    39,    43,   126,   127,    43,
      47,    42,   415,    47,   515,    52,    53,   420,    52,    53,
      44,    45,   425,    42,   427,    42,   429,    42,   431,    43,
     433,    44,    45,    43,   437,    44,    45,   132,   133,   442,
      42,    44,    43,    43,    43,   546,   449,   450,   451,   452,
     453,    42,    42,   456,    42,    42,    42,    41,   461,    23,
      24,    25,    23,    24,    25,   566,    44,    44,   569,    42,
     571,   474,    42,    42,    42,    39,    42,    42,    39,    43,
      42,    44,    43,    47,   487,    41,    47,    44,    52,    53,
      42,    52,    53,    42,   497,    23,    24,    25,    42,   502,
      45,    44,   505,   506,   507,   508,   509,    45,   511,    45,
      45,    39,    45,    44,   517,    43,    41,    44,    41,    47,
      44,    42,    42,    25,    52,    53,   529,    42,    42,   532,
      32,    33,    34,    35,    36,    37,    42,    42,    42,    41,
      17,    43,    42,   546,     9,    10,    11,    12,    13,    14,
      15,    16,    42,    18,    19,    20,    21,    42,    23,    24,
      25,    45,    45,   566,    45,    45,   569,    45,   571,    42,
      17,    42,    44,    42,    40,    40,    40,    42,    43,    40,
      40,    40,    47,    17,    42,    42,    17,    52,    53,     9,
      10,    11,    12,    13,    14,    15,    16,    40,    18,    44,
      20,    21,    42,    23,    24,    25,    32,    33,    34,    35,
      36,    37,    42,    42,    42,    41,     4,    43,    42,    42,
      40,    42,    42,    43,    40,    44,    44,    47,    40,    40,
      40,    44,    52,    53,     9,    10,    11,    12,    13,    14,
      15,    16,    42,    18,    42,    20,    21,    42,    23,    24,
      25,    12,    13,    14,    15,    16,    42,    18,    19,    42,
      42,    42,    23,    24,    25,    40,    44,    42,    43,    14,
      44,    44,    47,    24,    15,   107,   305,    52,    53,    40,
     219,    42,    43,   280,   166,   533,    47,   530,   512,   515,
     488,    52,    53,    12,    13,    14,    15,    16,   125,   124,
      19,   324,   329,    22,    23,    24,    25,    12,    13,    14,
      15,    16,    -1,    18,    19,    -1,    -1,    -1,    23,    24,
      25,    40,    -1,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    52,    53,    40,    -1,    42,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    52,    53,    12,
      13,    14,    15,    16,    -1,    -1,    19,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,
      43,    -1,    -1,    39,    47,    -1,    -1,    43,    -1,    52,
      53,    47,    23,    24,    25,    -1,    52,    53,    -1,    23,
      24,    25,    32,    33,    34,    35,    36,    37,    39,    -1,
      -1,    41,    43,    43,    -1,    39,    47,    -1,    -1,    43,
      -1,    52,    53,    47,    -1,    -1,    -1,    -1,    52,    53,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    41,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    58,    59,    60,    61,    62,    25,   132,
     132,     0,    60,    39,    39,    63,    66,    67,    73,    74,
      77,    78,    96,   132,    63,    64,    65,    69,    70,    75,
      76,   132,    66,    73,    77,    96,    67,    73,    77,   132,
      74,    77,   132,    40,    78,   132,    41,    64,    69,    75,
      65,    69,    75,   132,    70,    75,   132,    40,    76,   132,
      41,    73,    77,    77,    40,    77,    40,    41,    40,    41,
      41,     4,     7,     8,    23,    24,    43,    47,    52,    53,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   133,   134,   136,   137,   138,    69,    75,    75,    40,
      75,    40,    41,    40,    41,    41,     5,     6,     7,    77,
      40,    40,    40,   132,    39,    46,    82,    43,    71,   120,
     132,   127,   127,    42,    31,    30,    28,    29,    26,    27,
      50,    51,    52,    53,    46,    54,    55,    43,   130,    75,
      40,    40,    40,   129,   132,    71,    39,    46,    81,    40,
      42,    43,     9,    10,    11,    12,    13,    14,    15,    16,
      18,    19,    20,    21,    40,    42,    86,    90,    91,    95,
      96,    97,    98,   104,   105,   106,   107,   108,   109,   110,
     112,   118,   119,   120,   132,   134,   137,    44,    72,   132,
      39,    80,    44,    56,   122,   123,   124,   124,   125,   125,
     125,   125,   126,   126,   127,   127,   127,    44,   120,   131,
      40,    42,    39,    79,    12,    13,    16,    18,    40,    85,
      89,    91,    94,    96,    97,   103,   105,   106,   108,   113,
     132,   137,    52,    53,    68,   135,   136,   129,   132,    47,
      47,    43,    43,    42,    42,    43,    47,   132,   134,    43,
      42,    43,    47,    47,    40,    90,    42,    42,    32,    33,
      34,    35,    36,    37,    41,    32,    33,    34,    35,    36,
      37,    41,    82,    44,    45,    12,    13,    16,    21,    40,
      84,    88,    91,    93,    96,    97,    98,   102,   105,   106,
     107,   109,   110,   111,   112,   118,   119,   132,    44,    45,
      12,    13,    16,    22,    40,    83,    87,    91,    92,    96,
      97,    99,   101,   105,   108,   113,   117,   133,    43,    43,
      43,    40,    89,    42,   132,    81,   136,   136,    44,    45,
      42,    42,   132,   132,   120,    42,   132,   120,   132,    42,
      42,   120,    68,   132,   132,   120,   120,   120,   120,    42,
      42,    39,   120,    39,   120,    39,   120,    39,   120,    39,
     120,   132,    43,    43,    43,    42,    43,    40,    88,    42,
     120,    43,    43,    43,    42,    40,    87,    42,    32,    33,
      34,    35,    36,    37,    41,   120,    42,   132,   120,   130,
      42,   135,    42,    42,    44,   120,    41,    44,    44,    44,
      42,    43,    42,    43,   120,    42,   120,    42,   120,    42,
     120,    42,   120,    42,   120,    42,   132,   120,    68,   120,
      42,   132,   120,    42,    42,    39,   120,    39,   120,    39,
     120,    39,   120,    39,   120,    44,   120,    41,    44,    42,
      48,    82,    42,   120,    82,    42,    42,    68,    68,    45,
      45,    45,    45,    45,    44,   120,    41,    44,    44,    44,
     120,    41,    44,   120,    42,   120,    42,   120,    42,   120,
      42,   120,    42,    81,    42,   120,    81,    49,   114,   115,
     116,   129,   132,    97,   100,   120,   132,    42,    17,    44,
      44,   120,   120,   120,   120,   120,    80,    42,   120,    80,
      42,    79,    42,   120,    79,    45,    45,    45,    45,    45,
     100,    42,    17,   132,    42,    45,    44,    41,   120,    82,
      95,    42,    42,    40,    40,    40,    40,    40,   100,    42,
      17,   100,    42,    17,   120,   120,   120,   120,   120,    44,
     120,    81,    94,   115,    82,   120,    42,    42,    42,    42,
      42,    42,    44,   120,    80,    93,    44,   120,    79,    92,
      40,    40,    40,    40,    40,    81,    42,   100,    80,    42,
      79,    42,    42,    42,    42,    42,    42,   100,    44,   100,
     100,    44,    82,    44,    44,    81,    80,    79
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
#line 609 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[0]));
			(yyval)->setChild(2, (yyvsp[-1]));
		;}
    break;

  case 48:
#line 619 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 623 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 632 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 638 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[0]));
			(yyval)->setChild(2, (yyvsp[-1]));
		;}
    break;

  case 52:
#line 648 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 53:
#line 652 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
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
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 61:
#line 696 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 62:
#line 705 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 63:
#line 709 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 64:
#line 718 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 722 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 66:
#line 731 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 735 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 68:
#line 744 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 748 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 752 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 756 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 72:
#line 760 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 764 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 768 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 772 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 776 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 780 "BulletParser.y"
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
#line 795 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 799 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 82:
#line 803 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 807 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 811 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 815 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 819 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 823 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 827 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 831 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 835 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 839 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 843 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 850 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 854 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 858 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 862 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 97:
#line 866 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 870 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 874 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 878 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 882 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 889 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 893 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 897 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 901 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 106:
#line 905 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 909 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 913 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 917 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 110:
#line 921 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 111:
#line 925 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 112:
#line 929 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 113:
#line 933 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 114:
#line 937 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 115:
#line 941 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 116:
#line 945 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 117:
#line 952 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 118:
#line 956 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 119:
#line 963 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 120:
#line 969 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 121:
#line 976 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 122:
#line 986 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 123:
#line 992 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 124:
#line 999 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 125:
#line 1009 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 126:
#line 1015 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 127:
#line 1022 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 128:
#line 1032 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 129:
#line 1038 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 130:
#line 1045 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 131:
#line 1055 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 132:
#line 1064 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1069 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-1]));
		;}
    break;

  case 134:
#line 1074 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 135:
#line 1079 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 136:
#line 1084 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 137:
#line 1089 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 138:
#line 1097 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 139:
#line 1103 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 140:
#line 1110 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 141:
#line 1115 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1120 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1125 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 144:
#line 1130 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 145:
#line 1135 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 146:
#line 1140 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1146 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 148:
#line 1152 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 149:
#line 1158 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 150:
#line 1167 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 151:
#line 1173 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 152:
#line 1180 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 153:
#line 1185 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 154:
#line 1190 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 155:
#line 1195 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 156:
#line 1200 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 157:
#line 1205 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 158:
#line 1210 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 159:
#line 1216 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 160:
#line 1222 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 161:
#line 1228 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 162:
#line 1237 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 163:
#line 1241 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 164:
#line 1247 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 165:
#line 1254 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 166:
#line 1260 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 167:
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

  case 168:
#line 1284 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 169:
#line 1290 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 170:
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

  case 171:
#line 1314 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 172:
#line 1320 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 173:
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

  case 174:
#line 1344 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 175:
#line 1350 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 176:
#line 1358 "BulletParser.y"
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

  case 177:
#line 1374 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 178:
#line 1378 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 179:
#line 1385 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 180:
#line 1393 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 181:
#line 1401 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 182:
#line 1409 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
		;}
    break;

  case 183:
#line 1413 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 184:
#line 1421 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 185:
#line 1426 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[-4]));
		;}
    break;

  case 186:
#line 1435 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
		;}
    break;

  case 187:
#line 1439 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 188:
#line 1447 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 189:
#line 1452 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[-4]));
		;}
    break;

  case 190:
#line 1461 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 191:
#line 1471 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 192:
#line 1483 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 193:
#line 1487 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1496 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 195:
#line 1500 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 196:
#line 1505 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 197:
#line 1512 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Anchor, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1521 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 199:
#line 1528 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 200:
#line 1533 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 201:
#line 1541 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 202:
#line 1547 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 203:
#line 1556 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1564 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 205:
#line 1568 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 206:
#line 1577 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1581 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1590 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 209:
#line 1594 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 210:
#line 1600 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 211:
#line 1609 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 212:
#line 1613 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 213:
#line 1619 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 214:
#line 1625 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 215:
#line 1631 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 216:
#line 1640 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 217:
#line 1644 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 218:
#line 1650 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 219:
#line 1659 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 220:
#line 1663 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 221:
#line 1669 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 222:
#line 1675 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 223:
#line 1684 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 224:
#line 1688 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 225:
#line 1693 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 226:
#line 1701 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 227:
#line 1705 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 228:
#line 1709 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 229:
#line 1713 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 230:
#line 1717 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 231:
#line 1721 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 232:
#line 1728 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 233:
#line 1737 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 234:
#line 1741 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 235:
#line 1748 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 236:
#line 1753 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 237:
#line 1765 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 238:
#line 1773 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 239:
#line 1782 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 240:
#line 1793 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 241:
#line 1797 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 242:
#line 1801 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 243:
#line 1809 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 244:
#line 1813 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 245:
#line 1820 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 246:
#line 1828 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 4055 "bsBulletParser.cpp"

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


#line 1834 "BulletParser.y"


	
	

