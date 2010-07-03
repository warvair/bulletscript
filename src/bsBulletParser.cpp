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
     KEYWORD_WHILE = 265,
     KEYWORD_FOR = 266,
     KEYWORD_BREAK = 267,
     KEYWORD_CONTINUE = 268,
     KEYWORD_IF = 269,
     KEYWORD_ELSE = 270,
     KEYWORD_GOTO = 271,
     KEYWORD_WAIT = 272,
     KEYWORD_SUSPEND = 273,
     KEYWORD_SIGNAL = 274,
     KEYWORD_DIE = 275,
     INTEGER = 276,
     REAL = 277,
     IDENTIFIER = 278,
     SYMBOL_LTE = 279,
     SYMBOL_GTE = 280,
     SYMBOL_EQ = 281,
     SYMBOL_NEQ = 282,
     SYMBOL_LOG_AND = 283,
     SYMBOL_LOG_OR = 284,
     SYMBOL_INC = 285,
     SYMBOL_DEC = 286,
     SYMBOL_ADD_A = 287,
     SYMBOL_SUB_A = 288,
     SYMBOL_MUL_A = 289,
     SYMBOL_DIV_A = 290,
     TOKEN_ERROR = 291
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
#define KEYWORD_WHILE 265
#define KEYWORD_FOR 266
#define KEYWORD_BREAK 267
#define KEYWORD_CONTINUE 268
#define KEYWORD_IF 269
#define KEYWORD_ELSE 270
#define KEYWORD_GOTO 271
#define KEYWORD_WAIT 272
#define KEYWORD_SUSPEND 273
#define KEYWORD_SIGNAL 274
#define KEYWORD_DIE 275
#define INTEGER 276
#define REAL 277
#define IDENTIFIER 278
#define SYMBOL_LTE 279
#define SYMBOL_GTE 280
#define SYMBOL_EQ 281
#define SYMBOL_NEQ 282
#define SYMBOL_LOG_AND 283
#define SYMBOL_LOG_OR 284
#define SYMBOL_INC 285
#define SYMBOL_DEC 286
#define SYMBOL_ADD_A 287
#define SYMBOL_SUB_A 288
#define SYMBOL_MUL_A 289
#define SYMBOL_DIV_A 290
#define TOKEN_ERROR 291




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

static ParseTree* AST = ParseTree::instancePtr();

static const String gs_tokens[] = {
	"KEYWORD_CONTROLLER",				"controller",
	"KEYWORD_EMITTER",					"emitter",
	"KEYWORD_AFFECTOR",					"affector",
	"KEYWORD_FUNCTION",					"function",
	"KEYWORD_STATE",					"state",
	"KEYWORD_EVENT",					"event",
	"KEYWORD_RAISE",					"raise",
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
	for (int i = 0; i < 66; i += 2)
	{
		int startPos = (int) a_string.find(gs_tokens[i]);
		if (startPos < 0)
			continue;

		size_t count = gs_tokens[i].length();

		a_string.replace(startPos, count, gs_tokens[i + 1]);
	}
}

void yyerror(char* a_msg)
{
	String msgString = a_msg;
	replaceVerboseTokens(msgString);

	AST->addError(yylineno, msgString);
}

void rearrange_emitter_objects(YYSTYPE rootNode, YYSTYPE objNode)
{
	if (!objNode)
		return;
		
	// Go through objNode, and add any members, affectors, functions and states
	// to the list on the correct child node of rootNode
	int nodeType = objNode->getType();
	
	int rootChildren[] = {PT_EmitterAffectorNode, PT_EmitterFunctionNode, 
		PT_EmitterStateNode, PT_EmitterMemberNode};
		
	if (nodeType == PT_MemberDecl || nodeType == PT_AffectorDecl ||
		nodeType == PT_FunctionDecl || nodeType == PT_StateDecl)
	{
		int rootNodeType = rootChildren[(nodeType - PT_AffectorDecl) / 2];
		int declNodeType = nodeType - 1;
		
		YYSTYPE subNode = rootNode->getChild(rootNodeType);
		
		if (!subNode)
		{
			rootNode->setChild(rootNodeType, objNode);
		}
		else
		{
			YYSTYPE curNode = subNode;
			subNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(0, curNode);
			
			YYSTYPE newNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(1, newNode);
			newNode->setChild(0, objNode);
			
			rootNode->setChild(rootNodeType, subNode);
		}
		
		return;
	}
	
	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		rearrange_emitter_objects(rootNode, objNode->getChild(i));
}

void rearrange_controller_objects(YYSTYPE rootNode, YYSTYPE objNode)
{
	if (!objNode)
		return;

	// Go through objNode, and add any members, emitter members, events and states
	// to the list on the correct child node of rootNode
	int nodeType = objNode->getType();
	
	int rootChildren[] = {PT_ControllerStateNode, PT_ControllerMemberNode, 
		PT_ControllerEmitterNode, PT_ControllerEventNode};
		
	if (nodeType == PT_MemberDecl || nodeType == PT_StateDecl ||
		nodeType == PT_EventDecl || nodeType == PT_EmitterMemberDecl)
	{
		int rootNodeType = rootChildren[(nodeType - PT_StateDecl) / 2];
		int declNodeType = nodeType - 1;
		
		YYSTYPE subNode = rootNode->getChild(rootNodeType);
		
		if (!subNode)
		{
			rootNode->setChild(rootNodeType, objNode);
		}
		else
		{
			YYSTYPE curNode = subNode;
			subNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(0, curNode);
			
			YYSTYPE newNode = AST->createNode(declNodeType, objNode->getLine());
			subNode->setChild(1, newNode);
			newNode->setChild(0, objNode);
			
			rootNode->setChild(rootNodeType, subNode);
		}
		
		return;
	}
	
	for (int i = 0; i < ParseTreeNode::MAX_CHILDREN; ++i)
		rearrange_controller_objects(rootNode, objNode->getChild(i));
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
#line 392 "bsBulletParser.cpp"

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
#define YYLAST   828

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  80
/* YYNRULES -- Number of rules. */
#define YYNRULES  229
/* YYNRULES -- Number of states. */
#define YYNSTATES  526

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    45,    53,    47,     2,
      41,    42,    52,    50,    43,    51,    54,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    40,
      48,    39,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    20,    22,
      24,    26,    28,    30,    33,    39,    41,    43,    45,    47,
      49,    52,    54,    60,    66,    75,    77,    81,    83,    87,
      93,    96,   100,   102,   106,   112,   117,   124,   129,   136,
     139,   143,   146,   150,   153,   157,   160,   164,   166,   169,
     171,   174,   176,   179,   181,   184,   186,   188,   190,   193,
     195,   197,   199,   201,   203,   205,   207,   209,   211,   214,
     216,   218,   220,   222,   224,   226,   228,   230,   232,   234,
     236,   238,   240,   243,   245,   247,   249,   251,   253,   255,
     257,   259,   262,   264,   266,   268,   270,   272,   274,   276,
     278,   280,   282,   284,   287,   293,   301,   309,   315,   323,
     331,   337,   345,   353,   359,   367,   375,   380,   383,   386,
     390,   394,   398,   402,   407,   416,   420,   424,   429,   434,
     439,   444,   453,   462,   471,   480,   485,   494,   498,   502,
     507,   512,   517,   522,   531,   540,   549,   558,   560,   564,
     566,   572,   581,   593,   599,   608,   620,   626,   635,   647,
     653,   662,   674,   677,   680,   684,   688,   694,   697,   703,
     708,   716,   719,   725,   730,   738,   745,   750,   752,   756,
     758,   760,   762,   765,   768,   772,   776,   778,   780,   784,
     786,   790,   792,   796,   800,   802,   806,   810,   814,   818,
     820,   824,   828,   830,   834,   838,   842,   844,   847,   850,
     852,   854,   856,   858,   860,   864,   867,   870,   874,   876,
     880,   882,   885,   890,   892,   895,   898,   900,   902,   904
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      56,     0,    -1,    57,    -1,    58,    -1,    57,    58,    -1,
      59,    -1,    62,    -1,     4,   128,    37,    61,    38,    -1,
      65,    -1,    66,    -1,    70,    -1,    74,    -1,    60,    -1,
      61,    60,    -1,     3,   128,    37,    64,    38,    -1,    65,
      -1,    67,    -1,    73,    -1,    75,    -1,    63,    -1,    64,
      63,    -1,    93,    -1,   128,    39,     5,   125,    40,    -1,
     128,    39,     4,   128,    40,    -1,   128,    39,     4,   128,
      41,    68,    42,    40,    -1,   131,    -1,    68,    43,   131,
      -1,   132,    -1,    69,    43,   132,    -1,   128,    39,     6,
      71,    76,    -1,    41,    42,    -1,    41,    72,    42,    -1,
     128,    -1,    72,    43,   128,    -1,   128,    39,     8,    71,
      77,    -1,   128,    39,     7,    78,    -1,   128,    39,     7,
      44,   133,    78,    -1,   128,    39,     7,    79,    -1,   128,
      39,     7,    44,   133,    79,    -1,    37,    38,    -1,    37,
      80,    38,    -1,    37,    38,    -1,    37,    81,    38,    -1,
      37,    38,    -1,    37,    82,    38,    -1,    37,    38,    -1,
      37,    83,    38,    -1,    84,    -1,    80,    84,    -1,    85,
      -1,    81,    85,    -1,    86,    -1,    82,    86,    -1,    87,
      -1,    83,    87,    -1,    88,    -1,    89,    -1,    93,    -1,
      94,    40,    -1,    96,    -1,    98,    -1,   102,    -1,   105,
      -1,   110,    -1,   114,    -1,    88,    -1,    90,    -1,    93,
      -1,    94,    40,    -1,    95,    -1,    99,    -1,   102,    -1,
     103,    -1,   104,    -1,   115,    -1,   106,    -1,   107,    -1,
     108,    -1,   109,    -1,    88,    -1,    91,    -1,    93,    -1,
      94,    40,    -1,   100,    -1,   102,    -1,   103,    -1,   105,
      -1,   110,    -1,    88,    -1,    92,    -1,    93,    -1,    94,
      40,    -1,    95,    -1,   101,    -1,   102,    -1,   103,    -1,
     104,    -1,   105,    -1,   106,    -1,   107,    -1,   109,    -1,
     115,    -1,    40,    -1,   116,    40,    -1,    14,    41,   116,
      42,    76,    -1,    14,    41,   116,    42,    76,    15,    76,
      -1,    14,    41,   116,    42,    76,    15,    89,    -1,    14,
      41,   116,    42,    77,    -1,    14,    41,   116,    42,    77,
      15,    77,    -1,    14,    41,   116,    42,    77,    15,    90,
      -1,    14,    41,   116,    42,    78,    -1,    14,    41,   116,
      42,    78,    15,    78,    -1,    14,    41,   116,    42,    78,
      15,    91,    -1,    14,    41,   116,    42,    79,    -1,    14,
      41,   116,    42,    79,    15,    79,    -1,    14,    41,   116,
      42,    79,    15,    92,    -1,   128,    39,   116,    40,    -1,
     128,    30,    -1,   128,    31,    -1,   128,    32,   116,    -1,
     128,    33,   116,    -1,   128,    34,   116,    -1,   128,    35,
     116,    -1,   130,    39,   116,    40,    -1,   130,    39,    37,
     116,    43,   116,    38,    40,    -1,   130,    30,    40,    -1,
     130,    31,    40,    -1,   130,    32,   116,    40,    -1,   130,
      33,   116,    40,    -1,   130,    34,   116,    40,    -1,   130,
      35,   116,    40,    -1,   130,    32,    37,   116,    43,   116,
      38,    40,    -1,   130,    33,    37,   116,    43,   116,    38,
      40,    -1,   130,    34,    37,   116,    43,   116,    38,    40,
      -1,   130,    35,    37,   116,    43,   116,    38,    40,    -1,
     129,    39,   116,    40,    -1,   129,    39,    37,   116,    43,
     116,    38,    40,    -1,   129,    30,    40,    -1,   129,    31,
      40,    -1,   129,    32,   116,    40,    -1,   129,    33,   116,
      40,    -1,   129,    34,   116,    40,    -1,   129,    35,   116,
      40,    -1,   129,    32,    37,   116,    43,   116,    38,    40,
      -1,   129,    33,    37,   116,    43,   116,    38,    40,    -1,
     129,    34,    37,   116,    43,   116,    38,    40,    -1,   129,
      35,    37,   116,    43,   116,    38,    40,    -1,   116,    -1,
     128,    39,   116,    -1,    94,    -1,    10,    41,   116,    42,
      76,    -1,    11,    41,    40,   116,    40,    97,    42,    76,
      -1,    11,    41,   128,    39,   116,    40,   116,    40,    97,
      42,    76,    -1,    10,    41,   116,    42,    77,    -1,    11,
      41,    40,   116,    40,    97,    42,    77,    -1,    11,    41,
     128,    39,   116,    40,   116,    40,    97,    42,    77,    -1,
      10,    41,   116,    42,    78,    -1,    11,    41,    40,   116,
      40,    97,    42,    78,    -1,    11,    41,   128,    39,   116,
      40,   116,    40,    97,    42,    78,    -1,    10,    41,   116,
      42,    79,    -1,    11,    41,    40,   116,    40,    97,    42,
      79,    -1,    11,    41,   128,    39,   116,    40,   116,    40,
      97,    42,    79,    -1,    12,    40,    -1,    13,    40,    -1,
      16,   128,    40,    -1,    16,   130,    40,    -1,    17,    41,
     116,    42,    40,    -1,    18,    40,    -1,    18,    41,    69,
      42,    40,    -1,    18,    45,   128,    40,    -1,    18,    45,
     128,    41,    69,    42,    40,    -1,    19,    40,    -1,    19,
      41,    69,    42,    40,    -1,    19,    45,   128,    40,    -1,
      19,    45,   128,    41,    69,    42,    40,    -1,   128,   128,
     126,    46,   111,    40,    -1,   128,   128,   126,    40,    -1,
     112,    -1,   111,    43,   112,    -1,   125,    -1,   128,    -1,
     113,    -1,    47,   128,    -1,    20,    40,    -1,     9,   125,
      40,    -1,     9,   128,    40,    -1,   117,    -1,   118,    -1,
     117,    29,   118,    -1,   119,    -1,   118,    28,   119,    -1,
     120,    -1,   119,    26,   120,    -1,   119,    27,   120,    -1,
     121,    -1,   120,    48,   121,    -1,   120,    49,   121,    -1,
     120,    24,   121,    -1,   120,    25,   121,    -1,   122,    -1,
     121,    50,   122,    -1,   121,    51,   122,    -1,   123,    -1,
     122,    52,   123,    -1,   122,    44,   123,    -1,   122,    53,
     123,    -1,   124,    -1,    50,   123,    -1,    51,   123,    -1,
     128,    -1,   129,    -1,   130,    -1,   125,    -1,   132,    -1,
      41,   116,    42,    -1,   128,   126,    -1,    41,    42,    -1,
      41,   127,    42,    -1,   116,    -1,   127,    43,   116,    -1,
      23,    -1,    45,   128,    -1,    45,   128,    54,   128,    -1,
     132,    -1,    50,   132,    -1,    51,   132,    -1,   133,    -1,
     134,    -1,    21,    -1,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   263,   263,   270,   274,   283,   287,   294,   306,   310,
     314,   318,   325,   329,   338,   350,   354,   358,   362,   369,
     373,   382,   390,   399,   405,   415,   419,   428,   432,   441,
     451,   455,   462,   467,   479,   489,   495,   505,   511,   521,
     525,   532,   536,   543,   547,   554,   558,   565,   569,   578,
     582,   591,   595,   604,   608,   617,   621,   625,   629,   633,
     637,   641,   645,   649,   653,   660,   664,   668,   672,   676,
     680,   684,   688,   692,   696,   700,   704,   708,   712,   719,
     723,   727,   731,   735,   739,   743,   747,   751,   758,   762,
     766,   770,   774,   778,   782,   786,   790,   794,   798,   802,
     806,   810,   817,   821,   828,   834,   841,   851,   857,   864,
     874,   880,   887,   897,   903,   910,   920,   929,   934,   939,
     944,   949,   954,   962,   968,   975,   980,   985,   990,   995,
    1000,  1005,  1011,  1017,  1023,  1032,  1038,  1045,  1050,  1055,
    1060,  1065,  1070,  1075,  1081,  1087,  1093,  1102,  1106,  1112,
    1119,  1125,  1133,  1149,  1155,  1163,  1179,  1185,  1193,  1209,
    1215,  1223,  1239,  1243,  1250,  1258,  1266,  1274,  1278,  1286,
    1291,  1300,  1304,  1312,  1317,  1326,  1336,  1348,  1352,  1361,
    1365,  1370,  1377,  1386,  1393,  1398,  1406,  1414,  1418,  1427,
    1431,  1440,  1444,  1450,  1459,  1463,  1469,  1475,  1481,  1490,
    1494,  1500,  1509,  1513,  1519,  1525,  1534,  1538,  1543,  1551,
    1555,  1559,  1563,  1567,  1571,  1578,  1587,  1591,  1598,  1603,
    1615,  1623,  1632,  1643,  1647,  1651,  1659,  1663,  1670,  1678
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_CONTROLLER", "KEYWORD_EMITTER",
  "KEYWORD_AFFECTOR", "KEYWORD_FUNCTION", "KEYWORD_STATE", "KEYWORD_EVENT",
  "KEYWORD_RAISE", "KEYWORD_WHILE", "KEYWORD_FOR", "KEYWORD_BREAK",
  "KEYWORD_CONTINUE", "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_GOTO",
  "KEYWORD_WAIT", "KEYWORD_SUSPEND", "KEYWORD_SIGNAL", "KEYWORD_DIE",
  "INTEGER", "REAL", "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ",
  "SYMBOL_NEQ", "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC",
  "SYMBOL_DEC", "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A",
  "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'", "'}'", "'='", "';'", "'('", "')'",
  "','", "'/'", "'$'", "':'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'%'", "'.'", "$accept", "script_file", "definition_list", "definition",
  "emitter_definition", "emitter_object_declaration",
  "emitter_object_declaration_list", "controller_definition",
  "controller_object_declaration", "controller_object_declaration_list",
  "member_declaration", "affector_declaration",
  "emitter_member_declaration", "signed_constant_arg_list",
  "unsigned_constant_arg_list", "function", "function_arguments",
  "argument_list", "event", "emitter_state", "controller_state",
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
  "constant_expression", "logical_or_expression", "logical_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
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
     285,   286,   287,   288,   289,   290,   291,   123,   125,    61,
      59,    40,    41,    44,    47,    36,    58,    38,    60,    62,
      43,    45,    42,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    60,    60,
      60,    60,    61,    61,    62,    63,    63,    63,    63,    64,
      64,    65,    66,    67,    67,    68,    68,    69,    69,    70,
      71,    71,    72,    72,    73,    74,    74,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    88,    89,    89,    89,    90,    90,    90,
      91,    91,    91,    92,    92,    92,    93,    94,    94,    94,
      94,    94,    94,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    97,    97,    97,
      98,    98,    98,    99,    99,    99,   100,   100,   100,   101,
     101,   101,   102,   102,   103,   104,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   112,   113,   114,   115,   115,   116,   117,   117,   118,
     118,   119,   119,   119,   120,   120,   120,   120,   120,   121,
     121,   121,   122,   122,   122,   122,   123,   123,   123,   124,
     124,   124,   124,   124,   124,   125,   126,   126,   127,   127,
     128,   129,   130,   131,   131,   131,   132,   132,   133,   134
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     5,     1,     1,
       1,     1,     1,     2,     5,     1,     1,     1,     1,     1,
       2,     1,     5,     5,     8,     1,     3,     1,     3,     5,
       2,     3,     1,     3,     5,     4,     6,     4,     6,     2,
       3,     2,     3,     2,     3,     2,     3,     1,     2,     1,
       2,     1,     2,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     7,     7,     5,     7,     7,
       5,     7,     7,     5,     7,     7,     4,     2,     2,     3,
       3,     3,     3,     4,     8,     3,     3,     4,     4,     4,
       4,     8,     8,     8,     8,     4,     8,     3,     3,     4,
       4,     4,     4,     8,     8,     8,     8,     1,     3,     1,
       5,     8,    11,     5,     8,    11,     5,     8,    11,     5,
       8,    11,     2,     2,     3,     3,     5,     2,     5,     4,
       7,     2,     5,     4,     7,     6,     4,     1,     3,     1,
       1,     1,     2,     2,     3,     3,     1,     1,     3,     1,
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
       0,     0,     0,     0,     2,     3,     5,     6,   220,     0,
       0,     1,     4,     0,     0,    19,     0,    15,    16,    17,
      18,    21,     0,    12,     0,     8,     9,    10,    11,     0,
      14,    20,     0,     7,    13,     0,     0,     0,     0,   228,
     229,     0,     0,     0,     0,     0,   186,   187,   189,   191,
     194,   199,   202,   206,   212,   209,   210,   211,   213,   226,
     227,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,   221,   207,   208,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
       0,     0,     0,     0,     0,    35,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,   102,
       0,    53,    88,    89,    90,     0,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,     0,   209,   211,     0,
      30,     0,    32,     0,    34,   214,     0,   188,   190,   192,
     193,   197,   198,   195,   196,   200,   201,   204,   203,   205,
     216,   218,     0,    22,     0,    29,     0,     0,     0,     0,
      43,     0,    51,    79,    80,    81,     0,    83,    84,    85,
      86,    87,   209,     0,     0,     0,     0,    25,   223,     0,
       0,     0,     0,   162,   163,     0,     0,     0,     0,     0,
     167,     0,     0,     0,    46,    54,    91,   103,   117,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    31,     0,     0,     0,     0,     0,    41,
       0,    49,    65,    66,    67,     0,    69,    70,    71,    72,
      73,    75,    76,    77,    78,    74,   222,   217,     0,     0,
       0,     0,     0,    39,     0,    47,    55,    56,    57,     0,
      59,    60,    61,    62,    63,    64,   210,     0,     0,     0,
      44,    52,    82,     0,    36,   224,   225,     0,     0,   184,
     185,     0,     0,     0,     0,     0,   164,   165,     0,     0,
      27,     0,     0,   119,   120,   121,   122,   125,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,   171,     0,    42,    50,    68,   219,     0,
       0,     0,   183,    40,    48,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,    26,
       0,     0,     0,     0,     0,     0,     0,   169,     0,   173,
       0,     0,   127,     0,   128,     0,   129,     0,   130,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     137,   138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,     0,   159,     0,
       0,   113,   166,   168,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   139,     0,   140,     0,   141,     0,   142,     0,
     135,   156,     0,     0,   110,     0,     0,   177,   181,   179,
     180,   149,     0,   147,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   107,   172,   150,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   175,     0,     0,     0,     0,   114,   115,   170,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   111,
     112,   178,   160,   148,     0,   131,   132,   133,   134,   124,
       0,     0,   108,   109,     0,     0,   105,   106,     0,     0,
       0,     0,     0,   157,     0,     0,   154,     0,   151,     0,
     143,   144,   145,   146,   136,     0,     0,     0,     0,     0,
     161,     0,     0,   158,   155,   152
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,    23,    24,     7,    15,    16,
      17,    26,    18,   176,   279,    27,    69,   131,    19,    28,
      20,   155,   134,    95,    67,   244,   220,   161,   110,   245,
     221,   162,   111,   112,   247,   223,   164,   113,    21,   421,
     116,   250,   422,   251,   227,   167,   117,   118,   119,   120,
     121,   122,   123,   233,   124,   171,   416,   417,   418,   255,
     125,   126,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    89,   152,    55,    56,    57,   177,    58,    59,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -384
static const short int yypact[] =
{
     183,    42,    42,    70,   183,  -384,  -384,  -384,  -384,    67,
     101,  -384,  -384,    42,    42,  -384,    93,  -384,  -384,  -384,
    -384,  -384,   108,  -384,   106,  -384,  -384,  -384,  -384,   113,
    -384,  -384,   176,  -384,  -384,   254,    42,    90,   118,  -384,
    -384,   100,    42,   100,   100,   109,   148,   162,   167,    27,
     151,   110,  -384,  -384,  -384,   138,  -384,  -384,  -384,  -384,
    -384,    42,   118,    99,   188,   507,   185,  -384,    39,   172,
     169,   161,  -384,  -384,  -384,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   241,  -384,
     178,   138,   193,   650,   185,  -384,  -384,   153,    42,   206,
     208,   218,   244,   229,    13,   240,   116,   242,  -384,  -384,
     550,  -384,  -384,  -384,  -384,   249,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,   253,   414,   739,   269,
    -384,   194,  -384,   593,  -384,  -384,    42,   162,   167,    27,
      27,   151,   151,   151,   151,   110,   110,  -384,  -384,  -384,
    -384,  -384,   202,  -384,   324,  -384,   276,   278,   280,    42,
    -384,   692,  -384,  -384,  -384,  -384,   283,  -384,  -384,  -384,
    -384,  -384,   428,   288,   230,   230,   211,  -384,  -384,   287,
     215,   100,     9,  -384,  -384,   100,    42,   290,   292,   100,
    -384,   230,    42,    42,  -384,  -384,  -384,  -384,  -384,  -384,
     100,   100,   100,   100,   100,   299,   303,   257,   336,   386,
     533,   576,  -384,  -384,    42,   307,   315,   319,   155,  -384,
     636,  -384,  -384,  -384,  -384,   321,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,   100,   325,
     326,   327,   330,  -384,   706,  -384,  -384,  -384,  -384,   331,
    -384,  -384,  -384,  -384,  -384,  -384,   771,   100,    46,   100,
    -384,  -384,  -384,   138,  -384,  -384,  -384,   332,   153,  -384,
    -384,   337,   100,   341,   340,   161,  -384,  -384,   342,   223,
    -384,   227,   231,  -384,  -384,  -384,  -384,  -384,  -384,   100,
     345,   100,   349,   100,   350,   100,   352,   100,   356,  -384,
     100,    68,   100,  -384,   230,  -384,  -384,  -384,  -384,   100,
      73,   100,  -384,  -384,  -384,  -384,   358,   360,   713,   738,
     745,   770,   777,   361,   100,   363,   362,   136,  -384,  -384,
     269,   366,   100,   269,   372,   373,   230,  -384,   230,  -384,
     230,   374,  -384,   381,  -384,   383,  -384,   385,  -384,   389,
    -384,   387,   100,   376,   391,   268,   393,   100,   377,   396,
    -384,  -384,   100,   400,   100,   401,   100,   402,   100,   410,
     100,   417,   288,   424,   100,   288,  -384,    -5,  -384,   100,
     425,   439,  -384,  -384,  -384,   271,   273,   100,   100,   100,
     100,   100,   172,   430,   100,   172,   432,   193,   433,   100,
     193,   436,  -384,   438,  -384,   441,  -384,   442,  -384,   444,
    -384,  -384,   100,   454,   453,    42,     0,  -384,  -384,  -384,
     138,  -384,   440,  -384,   458,   100,    10,   455,   456,   462,
     464,   466,   467,   469,  -384,   100,   470,   494,  -384,  -384,
     100,   471,   497,   100,   100,   100,   100,   100,   472,   100,
      16,  -384,  -384,    -5,   269,   100,   473,  -384,  -384,  -384,
    -384,   482,   487,   491,   492,   493,   495,   100,    20,   499,
     100,    34,   496,   498,   501,   504,   505,   288,   506,  -384,
    -384,  -384,  -384,  -384,   100,  -384,  -384,  -384,  -384,  -384,
     172,   509,  -384,  -384,   193,   510,  -384,  -384,   511,   513,
     525,   535,   536,  -384,   100,   502,  -384,   100,  -384,   100,
    -384,  -384,  -384,  -384,  -384,   537,   269,   538,   539,   288,
    -384,   172,   193,  -384,  -384,  -384
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -384,  -384,  -384,   573,  -384,   558,  -384,  -384,   569,  -384,
      86,  -384,  -384,  -384,  -210,  -384,   524,  -384,  -384,  -384,
    -384,  -383,  -366,  -165,  -125,  -384,  -384,  -384,  -384,   343,
     369,   431,   483,   -74,   123,   128,   158,   184,   -56,   -55,
    -113,  -384,  -367,  -384,  -384,  -384,  -384,   -72,   -87,  -108,
     -71,  -106,  -105,  -384,  -102,  -151,  -384,   165,  -384,  -384,
    -100,    31,  -384,   544,   546,   196,   143,   213,    82,  -384,
     -59,   357,  -384,    -1,  -149,   -54,   355,   -90,   -50,  -384
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,    90,   254,   212,   256,   169,   178,   264,   114,
     115,   128,    22,    29,   439,    22,   129,   442,     8,   163,
     226,   168,   170,    29,   103,   230,   434,   231,   232,   437,
     158,   234,     8,   235,   217,    64,     8,   165,   166,   179,
     452,    71,   415,   453,   173,   448,   229,    65,   241,   272,
     188,    79,    80,    93,   114,   115,   128,   133,   186,   222,
      91,   228,     8,    45,   127,     8,    45,   132,   466,     8,
      11,   154,    70,   469,   169,    81,    82,   224,   225,   128,
     246,   130,   252,   253,   265,   266,   324,   163,   496,   168,
     170,     8,   172,   254,   355,   256,     8,   180,   248,   249,
      25,   280,   492,   187,    13,   165,   166,   226,   352,   127,
      25,   508,   230,   357,   231,   232,     8,   505,   234,   151,
     235,    39,    40,     8,   506,    72,    73,    65,   385,     8,
     386,    30,   127,   229,    66,   236,    93,   515,    14,   525,
     517,    41,   518,    94,    33,    42,   222,    32,   228,    74,
      43,    44,    35,   172,    85,   524,   190,   191,   187,    68,
     172,   192,    86,    87,   224,   225,   128,   147,   148,   149,
     246,   263,   252,   253,    39,    40,   376,    75,   178,    88,
      36,   273,   377,    37,    38,   275,     1,     2,   248,   249,
      76,   281,   282,    77,    78,   303,   304,    39,    40,     8,
     193,    83,    84,   174,   175,   378,    39,   411,   381,   133,
     414,   135,   271,   299,   280,   136,   274,    41,   153,   127,
     278,    42,   141,   142,   143,   144,    43,    44,    96,    97,
     154,   283,   284,   285,   286,    45,   213,   214,   290,   292,
     294,   296,   298,   172,   237,   238,   384,   181,   280,   182,
     280,    39,    40,   267,   268,   270,    88,   325,   183,    61,
      62,    63,    39,    40,     8,   335,   336,   337,   338,   308,
     185,   339,   340,   139,   140,    39,    40,     8,    39,    40,
       8,   189,    41,   150,   184,   479,    42,   193,   323,   196,
     326,    43,    44,   197,   289,    41,   145,   146,    41,    42,
     353,   457,    42,   331,    43,    44,    65,    43,    44,   358,
     396,   336,   503,   427,   336,   428,   336,   257,   419,   258,
     341,   259,   343,   262,   345,    93,   347,   269,   349,   482,
     276,   351,   277,   354,   239,   240,   101,   102,   241,   287,
     356,   105,   359,   288,   242,    39,    40,     8,   300,   363,
     365,   367,   369,   371,   523,   373,   301,    39,    40,     8,
     302,   307,   243,   380,   109,    41,   309,   310,   311,    42,
     312,   315,   328,   291,    43,    44,   420,    41,   424,   330,
     332,    42,   333,   393,   334,   342,    43,    44,   398,   344,
     346,   520,   348,   401,   419,   403,   350,   405,   360,   407,
     361,   409,   374,   372,   375,   413,   379,    39,    40,     8,
     423,   424,   382,   383,   451,   394,   399,   387,   429,   430,
     431,   432,   433,   293,   388,   436,   389,    41,   390,   392,
     441,    42,   391,   395,   424,   397,    43,    44,   400,   424,
     402,   404,   406,   423,   198,   199,   200,   201,   202,   203,
     408,     8,   420,   204,   426,    88,   456,   410,   198,   199,
     200,   201,   202,   203,   412,   425,   423,   204,   450,    88,
     435,   423,   438,   440,   472,   473,   474,   475,   476,   443,
     478,   444,   454,   424,   445,   446,   483,   447,   198,   199,
     200,   201,   202,   203,   449,   459,   460,   455,   491,    88,
     461,   495,   462,   424,   463,   464,   424,   465,   424,   468,
     467,   470,   471,   484,   477,   423,    98,    99,   100,   101,
     102,   103,   485,   104,   105,   106,   107,   486,    39,    40,
       8,   487,   488,   489,   498,   423,   499,   490,   423,   500,
     423,   494,   501,   502,   516,   108,   504,   109,    41,   507,
     509,   510,    42,   511,    39,    40,     8,    43,    44,    98,
      99,   100,   101,   102,   103,   512,   104,   105,   106,   107,
     295,    39,    40,     8,    41,   513,   514,    12,    42,   519,
     521,   522,    34,    43,    44,    31,    92,   314,   194,   306,
     109,    41,   261,   195,   497,    42,   493,    39,    40,     8,
      43,    44,    98,   215,   216,   101,   102,   217,   480,   104,
     458,   106,   218,   297,    39,    40,     8,    41,   481,   137,
     327,    42,   138,   329,     0,     0,    43,    44,     0,     0,
       0,   219,     0,   109,    41,     0,     0,     0,    42,     0,
       0,     0,     0,    43,    44,    98,   215,   216,   101,   102,
     217,     0,   104,     0,   106,   218,     0,    39,    40,     8,
     156,   157,   101,   102,   158,     0,   159,   105,     0,     0,
       0,    39,    40,     8,   305,     0,   109,    41,     0,     0,
       0,    42,     0,     0,     0,     0,    43,    44,   160,     0,
     109,    41,     0,     0,     0,    42,     0,     0,     0,     0,
      43,    44,   156,   157,   101,   102,   158,     0,   159,   105,
       0,     0,     0,    39,    40,     8,   239,   240,   101,   102,
     241,     0,     0,   105,     0,     0,   242,    39,    40,     8,
     260,     0,   109,    41,    39,    40,     8,    42,     0,     0,
       0,     0,    43,    44,   313,     0,   109,    41,     0,     0,
     362,    42,     0,     0,    41,     0,    43,    44,    42,    39,
      40,     8,     0,    43,    44,     0,    39,    40,     8,   205,
     206,   207,   208,   209,   210,   364,     0,     0,   211,    41,
       0,     0,   366,    42,     0,     0,    41,     0,    43,    44,
      42,    39,    40,     8,     0,    43,    44,     0,    39,    40,
       8,   316,   317,   318,   319,   320,   321,   368,     0,     0,
     322,    41,     0,     0,   370,    42,     0,     0,    41,     0,
      43,    44,    42,     0,     0,     0,     0,    43,    44
};

static const short int yycheck[] =
{
       1,     2,    61,   154,   129,   154,    93,    97,   173,    65,
      65,    65,    13,    14,   397,    16,    66,   400,    23,    93,
     133,    93,    93,    24,    14,   133,   392,   133,   133,   395,
      14,   133,    23,   133,    14,    36,    23,    93,    93,    98,
      40,    42,    47,    43,    94,   412,   133,    37,    14,    40,
     104,    24,    25,    37,   110,   110,   110,    37,    45,   133,
      61,   133,    23,    32,    65,    23,    35,    68,   435,    23,
       0,    37,    41,   440,   161,    48,    49,   133,   133,   133,
     154,    42,   154,   154,   174,   175,    40,   161,   471,   161,
     161,    23,    93,   244,   304,   244,    23,    98,   154,   154,
      14,   191,   468,   104,    37,   161,   161,   220,    40,   110,
      24,   494,   220,    40,   220,   220,    23,   484,   220,    88,
     220,    21,    22,    23,   490,    43,    44,    37,   338,    23,
     340,    38,   133,   220,    44,   136,    37,   504,    37,   522,
     507,    41,   509,    44,    38,    45,   220,    39,   220,    40,
      50,    51,    39,   154,    44,   521,    40,    41,   159,    41,
     161,    45,    52,    53,   220,   220,   220,    85,    86,    87,
     244,   172,   244,   244,    21,    22,    40,    29,   268,    41,
       4,   182,    46,     7,     8,   186,     3,     4,   244,   244,
      28,   192,   193,    26,    27,    40,    41,    21,    22,    23,
      45,    50,    51,    50,    51,   330,    21,   372,   333,    37,
     375,    42,   181,   214,   304,    54,   185,    41,    40,   220,
     189,    45,    79,    80,    81,    82,    50,    51,    40,    41,
      37,   200,   201,   202,   203,   204,    42,    43,   207,   208,
     209,   210,   211,   244,    42,    43,   336,    41,   338,    41,
     340,    21,    22,    42,    43,    40,    41,   258,    40,     5,
       6,     7,    21,    22,    23,    42,    43,    40,    41,   238,
      41,    40,    41,    77,    78,    21,    22,    23,    21,    22,
      23,    41,    41,    42,    40,   450,    45,    45,   257,    40,
     259,    50,    51,    40,    37,    41,    83,    84,    41,    45,
     301,   426,    45,   272,    50,    51,    37,    50,    51,   310,
      42,    43,   477,    42,    43,    42,    43,    41,   377,    41,
     289,    41,   291,    40,   293,    37,   295,    40,   297,   454,
      40,   300,    40,   302,    10,    11,    12,    13,    14,    40,
     309,    17,   311,    40,    20,    21,    22,    23,    41,   318,
     319,   320,   321,   322,   519,   324,    41,    21,    22,    23,
      41,    40,    38,   332,    40,    41,    41,    41,    41,    45,
      40,    40,    40,    37,    50,    51,   377,    41,   379,    42,
      39,    45,    42,   352,    42,    40,    50,    51,   357,    40,
      40,   516,    40,   362,   453,   364,    40,   366,    40,   368,
      40,   370,    39,    42,    42,   374,    40,    21,    22,    23,
     379,   412,    40,    40,   415,    39,    39,    43,   387,   388,
     389,   390,   391,    37,    43,   394,    43,    41,    43,    42,
     399,    45,    43,    42,   435,    42,    50,    51,    42,   440,
      40,    40,    40,   412,    30,    31,    32,    33,    34,    35,
      40,    23,   453,    39,    15,    41,   425,    40,    30,    31,
      32,    33,    34,    35,    40,    40,   435,    39,    15,    41,
      40,   440,    40,    40,   443,   444,   445,   446,   447,    43,
     449,    43,    42,   484,    43,    43,   455,    43,    30,    31,
      32,    33,    34,    35,    40,    40,    40,    39,   467,    41,
      38,   470,    38,   504,    38,    38,   507,    38,   509,    15,
      40,    40,    15,    40,    42,   484,     9,    10,    11,    12,
      13,    14,    40,    16,    17,    18,    19,    40,    21,    22,
      23,    40,    40,    40,    38,   504,    38,    42,   507,    38,
     509,    42,    38,    38,    42,    38,    40,    40,    41,    40,
      40,    40,    45,    40,    21,    22,    23,    50,    51,     9,
      10,    11,    12,    13,    14,    40,    16,    17,    18,    19,
      37,    21,    22,    23,    41,    40,    40,     4,    45,    42,
      42,    42,    24,    50,    51,    16,    62,   244,    38,   220,
      40,    41,   161,   110,   471,    45,   468,    21,    22,    23,
      50,    51,     9,    10,    11,    12,    13,    14,   450,    16,
     426,    18,    19,    37,    21,    22,    23,    41,   453,    75,
     263,    45,    76,   268,    -1,    -1,    50,    51,    -1,    -1,
      -1,    38,    -1,    40,    41,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    50,    51,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    18,    19,    -1,    21,    22,    23,
      10,    11,    12,    13,    14,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    38,    -1,    40,    41,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    50,    51,    38,    -1,
      40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      50,    51,    10,    11,    12,    13,    14,    -1,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    10,    11,    12,    13,
      14,    -1,    -1,    17,    -1,    -1,    20,    21,    22,    23,
      38,    -1,    40,    41,    21,    22,    23,    45,    -1,    -1,
      -1,    -1,    50,    51,    38,    -1,    40,    41,    -1,    -1,
      37,    45,    -1,    -1,    41,    -1,    50,    51,    45,    21,
      22,    23,    -1,    50,    51,    -1,    21,    22,    23,    30,
      31,    32,    33,    34,    35,    37,    -1,    -1,    39,    41,
      -1,    -1,    37,    45,    -1,    -1,    41,    -1,    50,    51,
      45,    21,    22,    23,    -1,    50,    51,    -1,    21,    22,
      23,    30,    31,    32,    33,    34,    35,    37,    -1,    -1,
      39,    41,    -1,    -1,    37,    45,    -1,    -1,    41,    -1,
      50,    51,    45,    -1,    -1,    -1,    -1,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    56,    57,    58,    59,    62,    23,   128,
     128,     0,    58,    37,    37,    63,    64,    65,    67,    73,
      75,    93,   128,    60,    61,    65,    66,    70,    74,   128,
      38,    63,    39,    38,    60,    39,     4,     7,     8,    21,
      22,    41,    45,    50,    51,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   128,   129,   130,   132,   133,
     134,     5,     6,     7,   128,    37,    44,    79,    41,    71,
     116,   128,   123,   123,    40,    29,    28,    26,    27,    24,
      25,    48,    49,    50,    51,    44,    52,    53,    41,   126,
     125,   128,    71,    37,    44,    78,    40,    41,     9,    10,
      11,    12,    13,    14,    16,    17,    18,    19,    38,    40,
      83,    87,    88,    92,    93,    94,    95,   101,   102,   103,
     104,   105,   106,   107,   109,   115,   116,   128,   130,   133,
      42,    72,   128,    37,    77,    42,    54,   118,   119,   120,
     120,   121,   121,   121,   121,   122,   122,   123,   123,   123,
      42,   116,   127,    40,    37,    76,    10,    11,    14,    16,
      38,    82,    86,    88,    91,    93,    94,   100,   102,   103,
     105,   110,   128,   133,    50,    51,    68,   131,   132,   125,
     128,    41,    41,    40,    40,    41,    45,   128,   130,    41,
      40,    41,    45,    45,    38,    87,    40,    40,    30,    31,
      32,    33,    34,    35,    39,    30,    31,    32,    33,    34,
      35,    39,    79,    42,    43,    10,    11,    14,    19,    38,
      81,    85,    88,    90,    93,    94,    95,    99,   102,   103,
     104,   106,   107,   108,   109,   115,   128,    42,    43,    10,
      11,    14,    20,    38,    80,    84,    88,    89,    93,    94,
      96,    98,   102,   105,   110,   114,   129,    41,    41,    41,
      38,    86,    40,   128,    78,   132,   132,    42,    43,    40,
      40,   116,    40,   128,   116,   128,    40,    40,   116,    69,
     132,   128,   128,   116,   116,   116,   116,    40,    40,    37,
     116,    37,   116,    37,   116,    37,   116,    37,   116,   128,
      41,    41,    41,    40,    41,    38,    85,    40,   116,    41,
      41,    41,    40,    38,    84,    40,    30,    31,    32,    33,
      34,    35,    39,   116,    40,   128,   116,   126,    40,   131,
      42,   116,    39,    42,    42,    42,    43,    40,    41,    40,
      41,   116,    40,   116,    40,   116,    40,   116,    40,   116,
      40,   116,    40,   128,   116,    69,   116,    40,   128,   116,
      40,    40,    37,   116,    37,   116,    37,   116,    37,   116,
      37,   116,    42,   116,    39,    42,    40,    46,    79,    40,
     116,    79,    40,    40,   132,    69,    69,    43,    43,    43,
      43,    43,    42,   116,    39,    42,    42,    42,   116,    39,
      42,   116,    40,   116,    40,   116,    40,   116,    40,   116,
      40,    78,    40,   116,    78,    47,   111,   112,   113,   125,
     128,    94,    97,   116,   128,    40,    15,    42,    42,   116,
     116,   116,   116,   116,    77,    40,   116,    77,    40,    76,
      40,   116,    76,    43,    43,    43,    43,    43,    97,    40,
      15,   128,    40,    43,    42,    39,   116,    79,    92,    40,
      40,    38,    38,    38,    38,    38,    97,    40,    15,    97,
      40,    15,   116,   116,   116,   116,   116,    42,   116,    78,
      91,   112,    79,   116,    40,    40,    40,    40,    40,    40,
      42,   116,    77,    90,    42,   116,    76,    89,    38,    38,
      38,    38,    38,    78,    40,    97,    77,    40,    76,    40,
      40,    40,    40,    40,    40,    97,    42,    97,    97,    42,
      79,    42,    42,    78,    77,    76
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
#line 264 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 271 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 275 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 284 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 288 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 295 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterDefinition, yylineno);
			(yyval)->setString((yyvsp[-3])->getStringData().c_str());			
			delete (yyvsp[-3]);

			// Now rearrange members, affectors, functions and states into correct nodes.
			rearrange_emitter_objects((yyval), (yyvsp[-1]));
		;}
    break;

  case 8:
#line 307 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 9:
#line 311 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 10:
#line 315 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 11:
#line 319 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 12:
#line 326 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 13:
#line 330 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterObjectList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 14:
#line 339 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerDefinition, yylineno);
			(yyval)->setString((yyvsp[-3])->getStringData().c_str());
			delete (yyvsp[-3]);

			// Now rearrange members, affectors, functions and states into correct nodes.
			rearrange_controller_objects((yyval), (yyvsp[-1]));
		;}
    break;

  case 15:
#line 351 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 16:
#line 355 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 17:
#line 359 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 18:
#line 363 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 19:
#line 370 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 20:
#line 374 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerObjectList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 21:
#line 383 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_MemberDecl);
		;}
    break;

  case 22:
#line 391 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 23:
#line 400 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMemberDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 24:
#line 406 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMemberDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 25:
#line 416 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 420 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 429 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 28:
#line 433 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 29:
#line 442 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 30:
#line 452 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 31:
#line 456 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 32:
#line 463 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 33:
#line 468 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 34:
#line 480 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 35:
#line 490 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 36:
#line 496 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[0]));
			(yyval)->setChild(2, (yyvsp[-1]));
		;}
    break;

  case 37:
#line 506 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 38:
#line 512 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[0]));
			(yyval)->setChild(2, (yyvsp[-1]));
		;}
    break;

  case 39:
#line 522 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 40:
#line 526 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 41:
#line 533 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 42:
#line 537 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 43:
#line 544 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 44:
#line 548 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 45:
#line 555 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 46:
#line 559 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 47:
#line 566 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 48:
#line 570 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 49:
#line 579 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 50:
#line 583 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 592 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 52:
#line 596 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 53:
#line 605 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 54:
#line 609 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 55:
#line 618 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 56:
#line 622 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 57:
#line 626 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 58:
#line 630 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 59:
#line 634 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 638 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 61:
#line 642 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 646 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
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
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 65:
#line 661 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 665 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 67:
#line 669 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 673 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 69:
#line 677 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 681 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 685 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 689 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 693 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 697 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 701 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 705 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 709 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 713 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 720 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 724 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 728 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 732 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 83:
#line 736 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 740 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 744 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 748 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 752 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 759 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 763 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 767 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 771 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 92:
#line 775 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 779 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 783 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 787 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 791 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 795 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 799 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 803 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 807 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 811 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 818 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 103:
#line 822 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 104:
#line 829 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 105:
#line 835 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 106:
#line 842 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 107:
#line 852 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 108:
#line 858 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 109:
#line 865 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 110:
#line 875 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 111:
#line 881 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 112:
#line 888 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 113:
#line 898 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 114:
#line 904 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 115:
#line 911 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 116:
#line 921 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 117:
#line 930 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-1]));
		;}
    break;

  case 118:
#line 935 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-1]));
		;}
    break;

  case 119:
#line 940 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 120:
#line 945 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 121:
#line 950 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 122:
#line 955 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-2]), (yyvsp[0]));
		;}
    break;

  case 123:
#line 963 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 124:
#line 969 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 125:
#line 976 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 126:
#line 981 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 127:
#line 986 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 128:
#line 991 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 129:
#line 996 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 130:
#line 1001 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 131:
#line 1006 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 132:
#line 1012 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 133:
#line 1018 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 134:
#line 1024 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 135:
#line 1033 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 136:
#line 1039 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 137:
#line 1046 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 138:
#line 1051 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 139:
#line 1056 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 140:
#line 1061 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1066 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 142:
#line 1071 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1076 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 144:
#line 1082 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 145:
#line 1088 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 146:
#line 1094 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1103 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 148:
#line 1107 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 149:
#line 1113 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 150:
#line 1120 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 151:
#line 1126 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 152:
#line 1134 "BulletParser.y"
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

  case 153:
#line 1150 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 154:
#line 1156 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 155:
#line 1164 "BulletParser.y"
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

  case 156:
#line 1180 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 157:
#line 1186 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 158:
#line 1194 "BulletParser.y"
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

  case 159:
#line 1210 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 160:
#line 1216 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ForStatement, yylineno);
			
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
			(yyval)->setChild(3, (yyvsp[0]));			
		;}
    break;

  case 161:
#line 1224 "BulletParser.y"
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
#line 1240 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 163:
#line 1244 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 164:
#line 1251 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 165:
#line 1259 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 166:
#line 1267 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 167:
#line 1275 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
		;}
    break;

  case 168:
#line 1279 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 169:
#line 1287 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 170:
#line 1292 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SuspendStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[-4]));
		;}
    break;

  case 171:
#line 1301 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
		;}
    break;

  case 172:
#line 1305 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 173:
#line 1313 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 174:
#line 1318 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SignalStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[-4]));
		;}
    break;

  case 175:
#line 1327 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 176:
#line 1337 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 177:
#line 1349 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 178:
#line 1353 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 179:
#line 1362 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 180:
#line 1366 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 181:
#line 1371 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 182:
#line 1378 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Anchor, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 183:
#line 1387 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 184:
#line 1394 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 185:
#line 1399 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 186:
#line 1407 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1415 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 188:
#line 1419 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 189:
#line 1428 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 190:
#line 1432 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 191:
#line 1441 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 192:
#line 1445 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1451 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1460 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 195:
#line 1464 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1470 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 197:
#line 1476 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1482 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 199:
#line 1491 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 200:
#line 1495 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 201:
#line 1501 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 202:
#line 1510 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 203:
#line 1514 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 204:
#line 1520 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1526 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 206:
#line 1535 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1539 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1544 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 209:
#line 1552 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1556 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 211:
#line 1560 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 212:
#line 1564 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 213:
#line 1568 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 214:
#line 1572 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 215:
#line 1579 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 216:
#line 1588 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 217:
#line 1592 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 218:
#line 1599 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 219:
#line 1604 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 220:
#line 1616 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 221:
#line 1624 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 222:
#line 1633 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 223:
#line 1644 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 224:
#line 1648 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 225:
#line 1652 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 226:
#line 1660 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 227:
#line 1664 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 228:
#line 1671 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 229:
#line 1679 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3796 "bsBulletParser.cpp"

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


#line 1685 "BulletParser.y"


	
	

