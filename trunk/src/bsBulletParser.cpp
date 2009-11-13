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
#line 284 "bsBulletParser.cpp"

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
#define YYLAST   776

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  73
/* YYNRULES -- Number of rules. */
#define YYNRULES  206
/* YYNRULES -- Number of states. */
#define YYNSTATES  456

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
     155,   161,   169,   178,   180,   184,   186,   189,   195,   198,
     202,   204,   208,   210,   213,   219,   221,   224,   229,   231,
     234,   239,   242,   246,   249,   253,   256,   260,   263,   267,
     269,   272,   274,   277,   279,   282,   284,   287,   289,   291,
     293,   295,   297,   299,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   321,   323,   325,   327,   329,   331,
     333,   335,   337,   339,   341,   343,   345,   347,   349,   351,
     353,   355,   357,   359,   361,   363,   366,   372,   380,   388,
     394,   402,   410,   416,   424,   432,   438,   446,   454,   459,
     463,   467,   472,   477,   482,   487,   492,   501,   505,   509,
     514,   519,   524,   529,   538,   547,   556,   565,   570,   579,
     583,   587,   592,   597,   602,   607,   616,   625,   634,   643,
     649,   655,   661,   667,   670,   673,   677,   683,   690,   695,
     697,   701,   703,   705,   710,   712,   714,   718,   720,   724,
     726,   730,   734,   736,   740,   744,   748,   752,   754,   758,
     762,   764,   768,   772,   776,   778,   781,   784,   786,   788,
     790,   792,   796,   799,   802,   806,   808,   812,   814,   817,
     822,   824,   827,   830,   832,   834,   836
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      51,     0,    -1,    52,    -1,    53,    -1,    52,    53,    -1,
      54,    -1,    55,    -1,     4,   116,    33,    68,    34,    -1,
       4,   116,    33,    62,    68,    34,    -1,     4,   116,    33,
      57,    68,    34,    -1,     4,   116,    33,    57,    62,    68,
      34,    -1,     4,   116,    33,    56,    68,    34,    -1,     4,
     116,    33,    56,    62,    68,    34,    -1,     4,   116,    33,
      56,    57,    68,    34,    -1,     4,   116,    33,    56,    57,
      62,    68,    34,    -1,     3,   116,    33,    70,    34,    -1,
       3,   116,    33,    66,    70,    34,    -1,     3,   116,    33,
      59,    70,    34,    -1,     3,   116,    33,    59,    66,    70,
      34,    -1,     3,   116,    33,    56,    70,    34,    -1,     3,
     116,    33,    56,    66,    70,    34,    -1,     3,   116,    33,
      56,    59,    70,    34,    -1,     3,   116,    33,    56,    59,
      66,    70,    34,    -1,    89,    -1,    56,    89,    -1,    58,
      -1,    57,    58,    -1,   116,    35,     5,   113,    36,    -1,
      60,    -1,    59,    60,    -1,   116,    35,     4,   116,    36,
      -1,   116,    35,     4,   116,    37,    38,    36,    -1,   116,
      35,     4,   116,    37,    61,    38,    36,    -1,   119,    -1,
      61,    39,   119,    -1,    63,    -1,    62,    63,    -1,   116,
      35,     6,    64,    72,    -1,    37,    38,    -1,    37,    65,
      38,    -1,   116,    -1,    65,    39,   116,    -1,    67,    -1,
      66,    67,    -1,   116,    35,     8,    64,    73,    -1,    69,
      -1,    68,    69,    -1,   116,    35,     7,    74,    -1,    71,
      -1,    70,    71,    -1,   116,    35,     7,    75,    -1,    33,
      34,    -1,    33,    76,    34,    -1,    33,    34,    -1,    33,
      77,    34,    -1,    33,    34,    -1,    33,    78,    34,    -1,
      33,    34,    -1,    33,    79,    34,    -1,    80,    -1,    76,
      80,    -1,    81,    -1,    77,    81,    -1,    82,    -1,    78,
      82,    -1,    83,    -1,    79,    83,    -1,    84,    -1,    85,
      -1,    89,    -1,    90,    -1,    92,    -1,    93,    -1,    97,
      -1,    99,    -1,   100,    -1,   103,    -1,    84,    -1,    86,
      -1,    89,    -1,    90,    -1,    91,    -1,    94,    -1,    97,
      -1,    98,    -1,    99,    -1,    84,    -1,    87,    -1,    89,
      -1,    90,    -1,    95,    -1,    97,    -1,    98,    -1,    99,
      -1,   100,    -1,    84,    -1,    88,    -1,    89,    -1,    90,
      -1,    91,    -1,    96,    -1,    97,    -1,    98,    -1,    99,
      -1,    36,    -1,   104,    36,    -1,    12,    37,   104,    38,
      72,    -1,    12,    37,   104,    38,    72,    13,    72,    -1,
      12,    37,   104,    38,    72,    13,    85,    -1,    12,    37,
     104,    38,    73,    -1,    12,    37,   104,    38,    73,    13,
      73,    -1,    12,    37,   104,    38,    73,    13,    86,    -1,
      12,    37,   104,    38,    74,    -1,    12,    37,   104,    38,
      74,    13,    74,    -1,    12,    37,   104,    38,    74,    13,
      87,    -1,    12,    37,   104,    38,    75,    -1,    12,    37,
     104,    38,    75,    13,    75,    -1,    12,    37,   104,    38,
      75,    13,    88,    -1,   116,    35,   104,    36,    -1,   116,
      26,    36,    -1,   116,    27,    36,    -1,   116,    28,   104,
      36,    -1,   116,    29,   104,    36,    -1,   116,    30,   104,
      36,    -1,   116,    31,   104,    36,    -1,   118,    35,   104,
      36,    -1,   118,    35,    33,   104,    39,   104,    34,    36,
      -1,   118,    26,    36,    -1,   118,    27,    36,    -1,   118,
      28,   104,    36,    -1,   118,    29,   104,    36,    -1,   118,
      30,   104,    36,    -1,   118,    31,   104,    36,    -1,   118,
      28,    33,   104,    39,   104,    34,    36,    -1,   118,    29,
      33,   104,    39,   104,    34,    36,    -1,   118,    30,    33,
     104,    39,   104,    34,    36,    -1,   118,    31,    33,   104,
      39,   104,    34,    36,    -1,   117,    35,   104,    36,    -1,
     117,    35,    33,   104,    39,   104,    34,    36,    -1,   117,
      26,    36,    -1,   117,    27,    36,    -1,   117,    28,   104,
      36,    -1,   117,    29,   104,    36,    -1,   117,    30,   104,
      36,    -1,   117,    31,   104,    36,    -1,   117,    28,    33,
     104,    39,   104,    34,    36,    -1,   117,    29,    33,   104,
      39,   104,    34,    36,    -1,   117,    30,    33,   104,    39,
     104,    34,    36,    -1,   117,    31,    33,   104,    39,   104,
      34,    36,    -1,     9,    37,   104,    38,    72,    -1,     9,
      37,   104,    38,    73,    -1,     9,    37,   104,    38,    74,
      -1,     9,    37,   104,    38,    75,    -1,    10,    36,    -1,
      11,    36,    -1,    14,   116,    36,    -1,    15,    37,   104,
      38,    36,    -1,   116,   116,   114,    40,   101,    36,    -1,
     116,   116,   114,    36,    -1,   102,    -1,   101,    39,   102,
      -1,   113,    -1,   116,    -1,    16,    37,    38,    36,    -1,
     105,    -1,   106,    -1,   105,    25,   106,    -1,   107,    -1,
     106,    24,   107,    -1,   108,    -1,   107,    22,   108,    -1,
     107,    23,   108,    -1,   109,    -1,   108,    41,   109,    -1,
     108,    42,   109,    -1,   108,    20,   109,    -1,   108,    21,
     109,    -1,   110,    -1,   109,    43,   110,    -1,   109,    44,
     110,    -1,   111,    -1,   110,    45,   111,    -1,   110,    46,
     111,    -1,   110,    47,   111,    -1,   112,    -1,    43,   111,
      -1,    44,   111,    -1,   116,    -1,   117,    -1,   113,    -1,
     120,    -1,    37,   104,    38,    -1,   116,   114,    -1,    37,
      38,    -1,    37,   115,    38,    -1,   104,    -1,   115,    39,
     104,    -1,    19,    -1,    48,   116,    -1,    48,   116,    49,
     116,    -1,   120,    -1,    43,   120,    -1,    44,   120,    -1,
     121,    -1,   122,    -1,    17,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   159,   159,   166,   170,   179,   183,   190,   201,   212,
     223,   234,   245,   256,   267,   281,   292,   303,   314,   325,
     336,   347,   358,   372,   376,   385,   389,   398,   407,   411,
     420,   426,   432,   442,   446,   455,   459,   468,   478,   482,
     489,   494,   506,   510,   519,   530,   534,   543,   552,   556,
     565,   574,   578,   585,   589,   596,   600,   607,   611,   618,
     622,   631,   635,   644,   648,   657,   661,   670,   674,   678,
     682,   686,   690,   694,   698,   702,   706,   713,   717,   721,
     725,   729,   733,   737,   741,   745,   752,   756,   760,   764,
     768,   772,   776,   780,   784,   791,   795,   799,   803,   807,
     811,   815,   819,   823,   830,   834,   841,   847,   854,   864,
     870,   877,   887,   893,   900,   910,   916,   923,   933,   942,
     947,   952,   957,   962,   967,   975,   981,   988,   993,   998,
    1003,  1008,  1013,  1018,  1024,  1030,  1036,  1045,  1051,  1058,
    1063,  1068,  1073,  1078,  1083,  1088,  1094,  1100,  1106,  1115,
    1124,  1133,  1142,  1151,  1155,  1162,  1170,  1178,  1188,  1200,
    1204,  1213,  1217,  1225,  1232,  1240,  1244,  1253,  1257,  1266,
    1270,  1276,  1285,  1289,  1295,  1301,  1307,  1316,  1320,  1326,
    1335,  1339,  1345,  1351,  1360,  1364,  1369,  1377,  1381,  1385,
    1389,  1393,  1400,  1409,  1413,  1420,  1425,  1437,  1445,  1454,
    1465,  1469,  1473,  1481,  1485,  1492,  1500
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
  "emitter_variable_arg_list", "function_list", "function",
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
  "goto_statement", "wait_statement", "fire_statement", "controller_list",
  "controller_entry", "die_statement", "constant_expression",
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
      60,    60,    60,    61,    61,    62,    62,    63,    64,    64,
      65,    65,    66,    66,    67,    68,    68,    69,    70,    70,
      71,    72,    72,    73,    73,    74,    74,    75,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    84,    85,    85,    85,    86,
      86,    86,    87,    87,    87,    88,    88,    88,    89,    90,
      90,    90,    90,    90,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      94,    95,    96,    97,    97,    98,    99,   100,   100,   101,
     101,   102,   102,   103,   104,   105,   105,   106,   106,   107,
     107,   107,   108,   108,   108,   108,   108,   109,   109,   109,
     110,   110,   110,   110,   111,   111,   111,   112,   112,   112,
     112,   112,   113,   114,   114,   115,   115,   116,   117,   118,
     119,   119,   119,   120,   120,   121,   122
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
       1,     1,     1,     1,     1,     2,     5,     7,     7,     5,
       7,     7,     5,     7,     7,     5,     7,     7,     4,     3,
       3,     4,     4,     4,     4,     4,     8,     3,     3,     4,
       4,     4,     4,     8,     8,     8,     8,     4,     8,     3,
       3,     4,     4,     4,     4,     8,     8,     8,     8,     5,
       5,     5,     5,     2,     2,     3,     5,     6,     4,     1,
       3,     1,     1,     4,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     2,     2,     1,     1,     1,
       1,     3,     2,     2,     3,     1,     3,     1,     2,     4,
       1,     2,     2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   197,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    42,
       0,    48,    23,     0,     0,     0,    25,     0,    35,     0,
      45,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      43,     0,     0,    15,    49,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    36,     0,     0,     7,    46,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   205,   206,     0,     0,     0,     0,
       0,   164,   165,   167,   169,   172,   177,   180,   184,   189,
     187,   188,   190,   203,   204,     0,     0,     0,    11,     0,
       9,     0,     8,     0,     0,     0,     0,     0,     0,    21,
      20,    18,     0,     0,    50,     0,     0,     0,   185,   186,
     198,   118,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,    13,    12,
      10,     0,     0,     0,     0,    47,    22,    30,     0,     0,
       0,     0,     0,     0,     0,    57,   104,     0,     0,    65,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     0,
     187,     0,    38,     0,    40,     0,    44,   191,   166,   168,
     170,   171,   175,   176,   173,   174,   178,   179,   181,   182,
     183,   193,   195,     0,    14,    27,     0,    37,     0,     0,
      55,     0,    63,    86,    87,    88,    89,    90,    91,    92,
      93,    94,   187,     0,     0,     0,     0,    33,   200,     0,
     153,   154,     0,     0,     0,   198,    58,    66,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,     0,     0,    53,     0,    61,
      77,    78,    79,    80,    81,    82,    83,    84,    85,   194,
       0,     0,     0,     0,    51,     0,    59,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,   188,     0,     0,
      56,    64,     0,    31,   201,   202,     0,     0,     0,     0,
     155,     0,     0,   119,   120,     0,     0,     0,     0,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,     0,    54,    62,   196,     0,     0,     0,
      52,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,    34,     0,     0,     0,   199,   121,   122,
     123,   124,     0,   129,     0,   130,     0,   131,     0,   132,
       0,   125,     0,     0,     0,     0,     0,   139,   140,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,   152,   115,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163,     0,   141,     0,   142,
       0,   143,     0,   144,     0,   137,   151,   112,     0,   159,
     161,   162,     0,     0,     0,     0,     0,     0,   150,   109,
     149,   106,     0,     0,     0,     0,     0,     0,   157,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   160,   133,   134,   135,
     136,   126,   110,   111,   107,   108,     0,     0,     0,     0,
       0,   145,   146,   147,   148,   138
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,   216,    27,    28,   116,   173,    18,    19,    29,    30,
      20,    21,   197,   176,   145,   114,   265,   248,   201,   158,
     266,   249,   202,   159,   160,   268,   251,   204,   161,    22,
     163,   164,   271,   272,   255,   207,   165,   166,   167,   168,
     211,   398,   399,   276,   169,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   136,   193,    90,    91,   171,   217,
      92,    93,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -361
static const short int yypact[] =
{
     185,    -8,    -8,    16,   185,  -361,  -361,  -361,  -361,    22,
      38,  -361,  -361,    -8,    -8,    -8,    -8,  -361,    -8,  -361,
     111,  -361,  -361,    28,    -8,    -8,  -361,    -8,  -361,   167,
    -361,    46,    -8,    -8,   174,  -361,  -361,    -8,   179,    58,
    -361,   188,    70,  -361,  -361,    76,   173,    -8,    -8,   214,
    -361,    -8,   227,    83,  -361,   233,    90,  -361,  -361,    93,
     321,    -8,   238,   264,  -361,   266,  -361,   286,  -361,   242,
     127,    -8,   104,   123,  -361,  -361,   728,   728,   728,    -8,
     112,   151,   160,   232,   130,   252,   303,  -361,  -361,  -361,
     157,  -361,  -361,  -361,  -361,    -8,   270,   273,  -361,   283,
    -361,   361,  -361,   377,   205,    -8,   123,   181,   299,  -361,
    -361,  -361,   363,   379,  -361,    84,   199,   207,  -361,  -361,
    -361,  -361,   728,   728,   728,   728,   728,   728,   728,   728,
     728,   728,   728,   728,   728,   293,  -361,   300,  -361,  -361,
    -361,   235,   157,   229,   419,  -361,  -361,  -361,   222,   236,
     240,   248,   269,    -8,   278,  -361,  -361,    -8,   432,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,   289,
     316,   351,  -361,   364,  -361,   472,  -361,  -361,   160,   232,
     130,   130,   252,   252,   252,   252,   303,   303,  -361,  -361,
    -361,  -361,  -361,   366,  -361,  -361,   485,  -361,   292,   295,
    -361,   525,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,   251,   318,   389,   389,   381,  -361,  -361,   728,
    -361,  -361,   728,   320,   728,   311,  -361,  -361,  -361,   326,
     334,   728,   728,   728,   728,   728,   349,   356,   586,   599,
     620,   632,   641,  -361,    -8,   298,   315,  -361,   538,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
     728,   350,   358,   380,  -361,   578,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,   731,   728,   728,
    -361,  -361,   157,  -361,  -361,  -361,   365,   115,   376,   383,
    -361,   386,    -8,  -361,  -361,   396,   399,   409,   412,  -361,
    -361,   728,   416,   728,   418,   728,   421,   728,   422,   728,
     423,  -361,   728,   728,  -361,  -361,  -361,   728,   728,   426,
    -361,  -361,   424,   425,   653,   674,   686,   695,   707,   427,
     433,    47,  -361,  -361,   104,   104,   434,  -361,  -361,  -361,
    -361,  -361,   435,  -361,   438,  -361,   439,  -361,   440,  -361,
     446,  -361,   450,   454,   455,   460,   436,  -361,  -361,   728,
     437,   728,   463,   728,   469,   728,   471,   728,   474,   181,
     181,  -361,    -8,  -361,   498,  -361,   728,   728,   728,   728,
     728,   199,   199,   229,   229,  -361,   473,  -361,   475,  -361,
     478,  -361,   479,  -361,   484,  -361,  -361,   500,   -31,  -361,
    -361,   157,    10,   490,   491,   492,   493,   496,  -361,   518,
    -361,   519,   728,   728,   728,   728,   728,    88,  -361,    -8,
    -361,  -361,   502,   505,   509,   510,   515,   107,   163,   520,
     524,   526,   529,   530,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,   531,   534,   535,   540,
     541,  -361,  -361,  -361,  -361,  -361
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -361,  -361,  -361,   561,  -361,  -361,   552,   554,   -22,   564,
      37,  -361,     5,    -7,   477,  -361,   187,   136,   158,    30,
     226,    79,  -260,  -343,  -360,  -267,  -361,  -361,  -361,  -361,
     319,   332,   384,   441,  -110,   164,   171,   183,   189,     3,
     -99,  -171,  -361,  -361,  -361,  -361,  -361,   -95,  -109,   -86,
    -190,  -361,   182,  -361,    -4,  -361,   480,   483,   301,    97,
     309,    31,  -361,  -103,   325,  -361,    -1,  -175,  -361,   322,
    -141,  -361,  -361
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   141,    50,   254,   418,   275,   218,   419,   396,
     397,     8,    23,    31,    23,    39,    11,    42,    35,    45,
      54,   277,   152,    31,    53,    50,    56,    35,    59,    48,
      51,    39,    42,    45,   203,   209,    42,    45,   408,   409,
      45,    54,    80,   113,    54,   206,    53,    56,    59,   208,
      56,    59,    95,    36,    59,    13,    80,   434,   210,    58,
      42,    45,    45,    46,    45,   250,   257,   373,   374,    36,
     112,    14,   117,   284,   285,   275,   253,   254,   120,    58,
     256,    60,    58,   371,   442,    58,   267,   372,    54,   258,
     277,   203,   209,    67,    56,    59,    59,   270,    59,    44,
     199,   273,   206,     8,   142,    69,   208,    45,   118,   119,
     274,    70,   170,    44,   174,   210,   162,    44,   101,   246,
      44,   144,   172,   410,   411,   103,    58,    58,   104,    58,
       8,   192,    74,    75,    72,   420,    59,   113,   250,   257,
     175,    44,    44,   212,    44,    43,   218,   205,   121,   253,
     126,   127,   223,   256,    40,   267,   225,   170,   214,   215,
     115,   162,   258,   188,   189,   190,   270,    58,   444,    40,
     273,   128,   129,    40,   170,   262,   122,    71,   252,   274,
      72,    73,    49,    52,   123,    55,     8,    44,     1,     2,
      74,    75,     8,     8,   135,   212,   196,    40,     8,   269,
     212,    57,    33,    37,   205,    96,    97,     8,    64,    99,
      76,   282,   107,    66,   144,   288,    77,    78,   289,    61,
     291,    79,    68,   182,   183,   184,   185,   295,   296,   297,
     298,    80,   175,     8,   302,   304,   306,   308,   310,    74,
      75,    34,    38,   311,    41,   177,     8,   170,    98,    72,
      73,   252,     8,   137,   124,   125,   316,     8,    62,    63,
     213,   100,   196,    65,   212,   214,   215,   102,   269,   400,
       8,   195,   109,   219,   329,   330,   220,   229,   230,   231,
     232,   233,   234,     8,   221,     8,   235,   108,   135,     8,
      71,   337,     8,    72,    73,   130,   131,   342,   110,   344,
     111,   346,     8,   348,   138,   350,   222,   139,   352,   353,
      74,    75,     8,   354,   355,   224,   400,   140,     8,     8,
     360,   362,   364,   366,   368,   228,   105,   106,   107,   278,
      76,   191,   279,   146,   194,   312,    77,    78,    74,    75,
       8,    79,   229,   230,   231,   232,   233,   234,   132,   133,
     134,   235,   313,   135,   283,   386,   290,   388,    76,   390,
     292,   392,   293,   394,    77,    78,   105,   106,   107,    79,
     294,   401,   403,   404,   405,   406,   407,   236,   237,   238,
     239,   240,   241,   106,   107,   299,   242,   317,   149,   150,
     151,   152,   300,   153,   154,   318,    74,    75,     8,   147,
     148,   332,   243,   244,   259,   260,    74,    75,   429,   430,
     431,   432,   433,   155,   334,   156,    76,   319,   401,   286,
     287,   335,    77,    78,   336,   180,   181,   157,   198,   150,
     151,   199,   338,   153,   154,   339,    74,    75,     8,   186,
     187,   149,   150,   151,   152,   340,   153,   154,   341,    74,
      75,     8,   343,   200,   345,   156,    76,   347,   349,   351,
     357,   358,    77,    78,   356,   369,   226,    79,   156,    76,
     375,   370,   385,   387,   376,    77,    78,   377,   378,   379,
     157,   245,   150,   151,   246,   380,   153,   154,   381,    74,
      75,     8,   382,   383,   261,   150,   151,   262,   384,   389,
     154,   263,    74,    75,     8,   391,   247,   393,   156,    76,
     395,   402,   412,   417,   413,    77,    78,   414,   415,   264,
     157,   156,    76,   416,   422,   423,   424,   425,    77,    78,
     426,   427,   428,    79,   198,   150,   151,   199,   437,   153,
     154,   438,    74,    75,     8,   439,   440,   245,   150,   151,
     246,   441,   153,   154,   446,    74,    75,     8,   447,   280,
     448,   156,    76,   449,   450,    12,    24,   451,    77,    78,
     452,   453,   314,    79,   156,    76,   454,   455,    47,    32,
     315,    77,    78,   143,   321,   281,   157,   261,   150,   151,
     262,   421,   445,   154,   263,    74,    75,     8,   443,   227,
     435,   436,   178,    74,    75,     8,   179,   331,     0,   333,
       0,     0,   320,     0,   156,    76,    74,    75,     8,   301,
       0,    77,    78,    76,     0,     0,    79,     0,     0,    77,
      78,     0,   303,     0,    79,     0,    76,    74,    75,     8,
       0,     0,    77,    78,     0,     0,     0,    79,     0,    74,
      75,     8,     0,   305,     0,     0,     0,    76,    74,    75,
       8,     0,     0,    77,    78,   307,     0,     0,    79,    76,
      74,    75,     8,     0,   309,    77,    78,     0,    76,     0,
      79,     0,     0,     0,    77,    78,   359,     0,     0,    79,
      76,    74,    75,     8,     0,     0,    77,    78,     0,     0,
       0,    79,     0,    74,    75,     8,     0,   361,     0,     0,
       0,    76,    74,    75,     8,     0,     0,    77,    78,   363,
       0,     0,    79,    76,    74,    75,     8,     0,   365,    77,
      78,     0,    76,     0,    79,     0,     0,     0,    77,    78,
     367,     0,     0,    79,    76,    74,    75,     8,     0,     0,
      77,    78,     0,     0,     0,    79,     0,   322,   323,   324,
     325,   326,   327,     0,     0,    76,   328,     0,     0,     0,
       0,    77,    78,     0,     0,     0,    79
};

static const short int yycheck[] =
{
       1,     2,   105,    25,   175,    36,   196,   148,    39,   369,
     370,    19,    13,    14,    15,    16,     0,    18,    15,    20,
      27,   196,    12,    24,    25,    47,    27,    24,    29,    24,
      25,    32,    33,    34,   144,   144,    37,    38,   381,   382,
      41,    48,    46,    33,    51,   144,    47,    48,    49,   144,
      51,    52,    47,    16,    55,    33,    60,   417,   144,    29,
      61,    62,    63,    35,    65,   175,   175,   334,   335,    32,
      71,    33,    76,   214,   215,   265,   175,   248,    79,    49,
     175,    35,    52,    36,   427,    55,   196,    40,    95,   175,
     265,   201,   201,    35,    95,    96,    97,   196,    99,    20,
      12,   196,   201,    19,   105,    35,   201,   108,    77,    78,
     196,    35,   113,    34,   115,   201,   113,    38,    35,    12,
      41,    33,    38,   383,   384,    35,    96,    97,    35,    99,
      19,   135,    17,    18,     7,   402,   137,    33,   248,   248,
      33,    62,    63,   144,    65,    34,   287,   144,    36,   248,
      20,    21,   153,   248,    18,   265,   157,   158,    43,    44,
      37,   158,   248,   132,   133,   134,   265,   137,   428,    33,
     265,    41,    42,    37,   175,    12,    25,     4,   175,   265,
       7,     8,    24,    25,    24,    27,    19,   108,     3,     4,
      17,    18,    19,    19,    37,   196,    33,    61,    19,   196,
     201,    34,    15,    16,   201,    47,    48,    19,    34,    51,
      37,   212,     7,    34,    33,   219,    43,    44,   222,    32,
     224,    48,    34,   126,   127,   128,   129,   231,   232,   233,
     234,   235,    33,    19,   238,   239,   240,   241,   242,    17,
      18,    15,    16,   244,    18,    38,    19,   248,    34,     7,
       8,   248,    19,    95,    22,    23,   260,    19,    32,    33,
      38,    34,    33,    37,   265,    43,    44,    34,   265,   372,
      19,    36,    34,    37,   278,   279,    36,    26,    27,    28,
      29,    30,    31,    19,    36,    19,    35,    61,    37,    19,
       4,   292,    19,     7,     8,    43,    44,   301,    34,   303,
      34,   305,    19,   307,    34,   309,    37,    34,   312,   313,
      17,    18,    19,   317,   318,    37,   419,    34,    19,    19,
     324,   325,   326,   327,   328,    36,     5,     6,     7,    37,
      37,    38,    37,    34,    34,    37,    43,    44,    17,    18,
      19,    48,    26,    27,    28,    29,    30,    31,    45,    46,
      47,    35,    37,    37,    36,   359,    36,   361,    37,   363,
      49,   365,    36,   367,    43,    44,     5,     6,     7,    48,
      36,   372,   376,   377,   378,   379,   380,    26,    27,    28,
      29,    30,    31,     6,     7,    36,    35,    37,     9,    10,
      11,    12,    36,    14,    15,    37,    17,    18,    19,    36,
      37,    36,    38,    39,    38,    39,    17,    18,   412,   413,
     414,   415,   416,    34,    38,    36,    37,    37,   419,    38,
      39,    38,    43,    44,    38,   124,   125,    48,     9,    10,
      11,    12,    36,    14,    15,    36,    17,    18,    19,   130,
     131,     9,    10,    11,    12,    36,    14,    15,    36,    17,
      18,    19,    36,    34,    36,    36,    37,    36,    36,    36,
      36,    36,    43,    44,    38,    38,    34,    48,    36,    37,
      36,    38,    36,    36,    39,    43,    44,    39,    39,    39,
      48,     9,    10,    11,    12,    39,    14,    15,    38,    17,
      18,    19,    38,    38,     9,    10,    11,    12,    38,    36,
      15,    16,    17,    18,    19,    36,    34,    36,    36,    37,
      36,    13,    39,    13,    39,    43,    44,    39,    39,    34,
      48,    36,    37,    39,    34,    34,    34,    34,    43,    44,
      34,    13,    13,    48,     9,    10,    11,    12,    36,    14,
      15,    36,    17,    18,    19,    36,    36,     9,    10,    11,
      12,    36,    14,    15,    34,    17,    18,    19,    34,    34,
      34,    36,    37,    34,    34,     4,    14,    36,    43,    44,
      36,    36,    34,    48,    36,    37,    36,    36,    24,    15,
     248,    43,    44,   106,   265,   201,    48,     9,    10,    11,
      12,   402,   428,    15,    16,    17,    18,    19,   427,   158,
     417,   419,   122,    17,    18,    19,   123,   282,    -1,   287,
      -1,    -1,    34,    -1,    36,    37,    17,    18,    19,    33,
      -1,    43,    44,    37,    -1,    -1,    48,    -1,    -1,    43,
      44,    -1,    33,    -1,    48,    -1,    37,    17,    18,    19,
      -1,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,    17,
      18,    19,    -1,    33,    -1,    -1,    -1,    37,    17,    18,
      19,    -1,    -1,    43,    44,    33,    -1,    -1,    48,    37,
      17,    18,    19,    -1,    33,    43,    44,    -1,    37,    -1,
      48,    -1,    -1,    -1,    43,    44,    33,    -1,    -1,    48,
      37,    17,    18,    19,    -1,    -1,    43,    44,    -1,    -1,
      -1,    48,    -1,    17,    18,    19,    -1,    33,    -1,    -1,
      -1,    37,    17,    18,    19,    -1,    -1,    43,    44,    33,
      -1,    -1,    48,    37,    17,    18,    19,    -1,    33,    43,
      44,    -1,    37,    -1,    48,    -1,    -1,    -1,    43,    44,
      33,    -1,    -1,    48,    37,    17,    18,    19,    -1,    -1,
      43,    44,    -1,    -1,    -1,    48,    -1,    26,    27,    28,
      29,    30,    31,    -1,    -1,    37,    35,    -1,    -1,    -1,
      -1,    43,    44,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    51,    52,    53,    54,    55,    19,   116,
     116,     0,    53,    33,    33,    56,    59,    60,    66,    67,
      70,    71,    89,   116,    56,    57,    58,    62,    63,    68,
      69,   116,    59,    66,    70,    89,    60,    66,    70,   116,
      67,    70,   116,    34,    71,   116,    35,    57,    62,    68,
      58,    62,    68,   116,    63,    68,   116,    34,    69,   116,
      35,    66,    70,    70,    34,    70,    34,    35,    34,    35,
      35,     4,     7,     8,    17,    18,    37,    43,    44,    48,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     116,   117,   120,   121,   122,    62,    68,    68,    34,    68,
      34,    35,    34,    35,    35,     5,     6,     7,    70,    34,
      34,    34,   116,    33,    75,    37,    64,   104,   111,   111,
     116,    36,    25,    24,    22,    23,    20,    21,    41,    42,
      43,    44,    45,    46,    47,    37,   114,    68,    34,    34,
      34,   113,   116,    64,    33,    74,    34,    36,    37,     9,
      10,    11,    12,    14,    15,    34,    36,    48,    79,    83,
      84,    88,    89,    90,    91,    96,    97,    98,    99,   104,
     116,   118,    38,    65,   116,    33,    73,    38,   106,   107,
     108,   108,   109,   109,   109,   109,   110,   110,   111,   111,
     111,    38,   104,   115,    34,    36,    33,    72,     9,    12,
      34,    78,    82,    84,    87,    89,    90,    95,    97,    98,
      99,   100,   116,    38,    43,    44,    61,   119,   120,    37,
      36,    36,    37,   116,    37,   116,    34,    83,    36,    26,
      27,    28,    29,    30,    31,    35,    26,    27,    28,    29,
      30,    31,    35,    38,    39,     9,    12,    34,    77,    81,
      84,    86,    89,    90,    91,    94,    97,    98,    99,    38,
      39,     9,    12,    16,    34,    76,    80,    84,    85,    89,
      90,    92,    93,    97,    99,   100,   103,   117,    37,    37,
      34,    82,   116,    36,   120,   120,    38,    39,   104,   104,
      36,   104,    49,    36,    36,   104,   104,   104,   104,    36,
      36,    33,   104,    33,   104,    33,   104,    33,   104,    33,
     104,   116,    37,    37,    34,    81,   104,    37,    37,    37,
      34,    80,    26,    27,    28,    29,    30,    31,    35,   104,
     104,   114,    36,   119,    38,    38,    38,   116,    36,    36,
      36,    36,   104,    36,   104,    36,   104,    36,   104,    36,
     104,    36,   104,   104,   104,   104,    38,    36,    36,    33,
     104,    33,   104,    33,   104,    33,   104,    33,   104,    38,
      38,    36,    40,    75,    75,    36,    39,    39,    39,    39,
      39,    38,    38,    38,    38,    36,   104,    36,   104,    36,
     104,    36,   104,    36,   104,    36,    74,    74,   101,   102,
     113,   116,    13,   104,   104,   104,   104,   104,    73,    73,
      72,    72,    39,    39,    39,    39,    39,    13,    36,    39,
      75,    88,    34,    34,    34,    34,    34,    13,    13,   104,
     104,   104,   104,   104,    74,    87,   102,    36,    36,    36,
      36,    36,    73,    86,    72,    85,    34,    34,    34,    34,
      34,    36,    36,    36,    36,    36
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
#line 160 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 167 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 171 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 180 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 184 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 191 "BulletParser.y"
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
#line 202 "BulletParser.y"
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
#line 213 "BulletParser.y"
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
#line 224 "BulletParser.y"
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
#line 235 "BulletParser.y"
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
#line 246 "BulletParser.y"
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
#line 257 "BulletParser.y"
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
#line 268 "BulletParser.y"
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
#line 282 "BulletParser.y"
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
#line 293 "BulletParser.y"
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
#line 304 "BulletParser.y"
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
#line 315 "BulletParser.y"
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
#line 326 "BulletParser.y"
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
#line 337 "BulletParser.y"
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
#line 348 "BulletParser.y"
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
#line 359 "BulletParser.y"
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
#line 373 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 377 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 386 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 390 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 399 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 28:
#line 408 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 412 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 421 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 31:
#line 427 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-3]));
		;}
    break;

  case 32:
#line 433 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 33:
#line 443 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 34:
#line 447 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 35:
#line 456 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 460 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 37:
#line 469 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 38:
#line 479 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 39:
#line 483 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 40:
#line 490 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 41:
#line 495 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 42:
#line 507 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 511 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 520 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 45:
#line 531 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 535 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 544 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 48:
#line 553 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 557 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 566 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 575 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 52:
#line 579 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 53:
#line 586 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 54:
#line 590 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 55:
#line 597 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 56:
#line 601 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 57:
#line 608 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 58:
#line 612 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 59:
#line 619 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 623 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
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
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 645 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 649 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 65:
#line 658 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 662 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 67:
#line 671 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 675 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 679 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 683 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 687 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 691 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 695 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 699 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 703 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 707 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 714 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 718 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 722 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 726 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 730 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 734 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 738 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 742 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 746 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 753 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 757 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 761 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 765 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 769 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 773 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 777 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 781 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 785 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 792 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 796 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 800 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 804 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 808 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 812 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 816 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 820 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 824 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 831 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 105:
#line 835 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 106:
#line 842 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 107:
#line 848 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 108:
#line 855 "BulletParser.y"
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
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 110:
#line 871 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 111:
#line 878 "BulletParser.y"
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
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 113:
#line 894 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 114:
#line 901 "BulletParser.y"
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
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 116:
#line 917 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 117:
#line 924 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 118:
#line 934 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 119:
#line 943 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 120:
#line 948 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 121:
#line 953 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 122:
#line 958 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 123:
#line 963 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 124:
#line 968 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 125:
#line 976 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 126:
#line 982 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 127:
#line 989 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 128:
#line 994 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 129:
#line 999 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 130:
#line 1004 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 131:
#line 1009 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 132:
#line 1014 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1019 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 134:
#line 1025 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 135:
#line 1031 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 136:
#line 1037 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 137:
#line 1046 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 138:
#line 1052 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 139:
#line 1059 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 140:
#line 1064 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 141:
#line 1069 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 142:
#line 1074 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1079 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 144:
#line 1084 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 145:
#line 1089 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 146:
#line 1095 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 147:
#line 1101 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 148:
#line 1107 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 149:
#line 1116 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 150:
#line 1125 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 151:
#line 1134 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 152:
#line 1143 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 153:
#line 1152 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 154:
#line 1156 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 155:
#line 1163 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 156:
#line 1171 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 157:
#line 1179 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 158:
#line 1189 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 159:
#line 1201 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 160:
#line 1205 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 161:
#line 1214 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 162:
#line 1218 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 163:
#line 1226 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 164:
#line 1233 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 165:
#line 1241 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 166:
#line 1245 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 167:
#line 1254 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 168:
#line 1258 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 169:
#line 1267 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 170:
#line 1271 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 171:
#line 1277 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 172:
#line 1286 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 173:
#line 1290 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 174:
#line 1296 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 175:
#line 1302 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 176:
#line 1308 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 177:
#line 1317 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 178:
#line 1321 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 179:
#line 1327 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 180:
#line 1336 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 181:
#line 1340 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 182:
#line 1346 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 183:
#line 1352 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 184:
#line 1361 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 185:
#line 1365 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 186:
#line 1370 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1378 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 188:
#line 1382 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 189:
#line 1386 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 190:
#line 1390 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 191:
#line 1394 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 192:
#line 1401 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1410 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 194:
#line 1414 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 195:
#line 1421 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 196:
#line 1426 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 197:
#line 1438 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 198:
#line 1446 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 199:
#line 1455 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 200:
#line 1466 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 201:
#line 1470 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 202:
#line 1474 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 203:
#line 1482 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 204:
#line 1486 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 205:
#line 1493 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 206:
#line 1501 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3512 "bsBulletParser.cpp"

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


#line 1507 "BulletParser.y"


	
	

