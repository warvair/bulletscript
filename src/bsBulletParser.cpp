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
     KEYWORD_BREAK = 266,
     KEYWORD_CONTINUE = 267,
     KEYWORD_IF = 268,
     KEYWORD_ELSE = 269,
     KEYWORD_GOTO = 270,
     KEYWORD_WAIT = 271,
     KEYWORD_DIE = 272,
     INTEGER = 273,
     REAL = 274,
     IDENTIFIER = 275,
     SYMBOL_LTE = 276,
     SYMBOL_GTE = 277,
     SYMBOL_EQ = 278,
     SYMBOL_NEQ = 279,
     SYMBOL_LOG_AND = 280,
     SYMBOL_LOG_OR = 281,
     SYMBOL_INC = 282,
     SYMBOL_DEC = 283,
     SYMBOL_ADD_A = 284,
     SYMBOL_SUB_A = 285,
     SYMBOL_MUL_A = 286,
     SYMBOL_DIV_A = 287,
     TOKEN_ERROR = 288
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
#define KEYWORD_BREAK 266
#define KEYWORD_CONTINUE 267
#define KEYWORD_IF 268
#define KEYWORD_ELSE 269
#define KEYWORD_GOTO 270
#define KEYWORD_WAIT 271
#define KEYWORD_DIE 272
#define INTEGER 273
#define REAL 274
#define IDENTIFIER 275
#define SYMBOL_LTE 276
#define SYMBOL_GTE 277
#define SYMBOL_EQ 278
#define SYMBOL_NEQ 279
#define SYMBOL_LOG_AND 280
#define SYMBOL_LOG_OR 281
#define SYMBOL_INC 282
#define SYMBOL_DEC 283
#define SYMBOL_ADD_A 284
#define SYMBOL_SUB_A 285
#define SYMBOL_MUL_A 286
#define SYMBOL_DIV_A 287
#define TOKEN_ERROR 288




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
#line 286 "bsBulletParser.cpp"

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
#define YYLAST   779

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  75
/* YYNRULES -- Number of rules. */
#define YYNRULES  212
/* YYNRULES -- Number of states. */
#define YYNSTATES  466

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    49,    48,     2,     2,
      38,    39,    46,    44,    40,    45,    50,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    37,
      42,    36,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
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
     353,   355,   357,   359,   361,   363,   365,   367,   369,   372,
     378,   386,   394,   400,   408,   416,   422,   430,   438,   444,
     452,   460,   465,   469,   473,   478,   483,   488,   493,   498,
     507,   511,   515,   520,   525,   530,   535,   544,   553,   562,
     571,   576,   585,   589,   593,   598,   603,   608,   613,   622,
     631,   640,   649,   655,   661,   667,   673,   676,   679,   683,
     687,   693,   700,   705,   707,   711,   713,   715,   720,   724,
     726,   728,   732,   734,   738,   740,   744,   748,   750,   754,
     758,   762,   766,   768,   772,   776,   778,   782,   786,   790,
     792,   795,   798,   800,   802,   804,   806,   808,   812,   815,
     818,   822,   824,   828,   830,   833,   838,   840,   843,   846,
     848,   850,   852
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      52,     0,    -1,    53,    -1,    54,    -1,    53,    54,    -1,
      55,    -1,    56,    -1,     4,   119,    34,    69,    35,    -1,
       4,   119,    34,    63,    69,    35,    -1,     4,   119,    34,
      58,    69,    35,    -1,     4,   119,    34,    58,    63,    69,
      35,    -1,     4,   119,    34,    57,    69,    35,    -1,     4,
     119,    34,    57,    63,    69,    35,    -1,     4,   119,    34,
      57,    58,    69,    35,    -1,     4,   119,    34,    57,    58,
      63,    69,    35,    -1,     3,   119,    34,    71,    35,    -1,
       3,   119,    34,    67,    71,    35,    -1,     3,   119,    34,
      60,    71,    35,    -1,     3,   119,    34,    60,    67,    71,
      35,    -1,     3,   119,    34,    57,    71,    35,    -1,     3,
     119,    34,    57,    67,    71,    35,    -1,     3,   119,    34,
      57,    60,    71,    35,    -1,     3,   119,    34,    57,    60,
      67,    71,    35,    -1,    90,    -1,    57,    90,    -1,    59,
      -1,    58,    59,    -1,   119,    36,     5,   116,    37,    -1,
      61,    -1,    60,    61,    -1,   119,    36,     4,   119,    37,
      -1,   119,    36,     4,   119,    38,    39,    37,    -1,   119,
      36,     4,   119,    38,    62,    39,    37,    -1,   122,    -1,
      62,    40,   122,    -1,    64,    -1,    63,    64,    -1,   119,
      36,     6,    65,    73,    -1,    38,    39,    -1,    38,    66,
      39,    -1,   119,    -1,    66,    40,   119,    -1,    68,    -1,
      67,    68,    -1,   119,    36,     8,    65,    74,    -1,    70,
      -1,    69,    70,    -1,   119,    36,     7,    75,    -1,    72,
      -1,    71,    72,    -1,   119,    36,     7,    76,    -1,    34,
      35,    -1,    34,    77,    35,    -1,    34,    35,    -1,    34,
      78,    35,    -1,    34,    35,    -1,    34,    79,    35,    -1,
      34,    35,    -1,    34,    80,    35,    -1,    81,    -1,    77,
      81,    -1,    82,    -1,    78,    82,    -1,    83,    -1,    79,
      83,    -1,    84,    -1,    80,    84,    -1,    85,    -1,    86,
      -1,    90,    -1,    91,    -1,    93,    -1,    94,    -1,    98,
      -1,   101,    -1,   102,    -1,   105,    -1,    85,    -1,    87,
      -1,    90,    -1,    91,    -1,    92,    -1,    95,    -1,    98,
      -1,    99,    -1,   100,    -1,   106,    -1,    85,    -1,    88,
      -1,    90,    -1,    91,    -1,    96,    -1,    98,    -1,    99,
      -1,   101,    -1,   102,    -1,    85,    -1,    89,    -1,    90,
      -1,    91,    -1,    92,    -1,    97,    -1,    98,    -1,    99,
      -1,   100,    -1,   101,    -1,   106,    -1,    37,    -1,   107,
      37,    -1,    13,    38,   107,    39,    73,    -1,    13,    38,
     107,    39,    73,    14,    73,    -1,    13,    38,   107,    39,
      73,    14,    86,    -1,    13,    38,   107,    39,    74,    -1,
      13,    38,   107,    39,    74,    14,    74,    -1,    13,    38,
     107,    39,    74,    14,    87,    -1,    13,    38,   107,    39,
      75,    -1,    13,    38,   107,    39,    75,    14,    75,    -1,
      13,    38,   107,    39,    75,    14,    88,    -1,    13,    38,
     107,    39,    76,    -1,    13,    38,   107,    39,    76,    14,
      76,    -1,    13,    38,   107,    39,    76,    14,    89,    -1,
     119,    36,   107,    37,    -1,   119,    27,    37,    -1,   119,
      28,    37,    -1,   119,    29,   107,    37,    -1,   119,    30,
     107,    37,    -1,   119,    31,   107,    37,    -1,   119,    32,
     107,    37,    -1,   121,    36,   107,    37,    -1,   121,    36,
      34,   107,    40,   107,    35,    37,    -1,   121,    27,    37,
      -1,   121,    28,    37,    -1,   121,    29,   107,    37,    -1,
     121,    30,   107,    37,    -1,   121,    31,   107,    37,    -1,
     121,    32,   107,    37,    -1,   121,    29,    34,   107,    40,
     107,    35,    37,    -1,   121,    30,    34,   107,    40,   107,
      35,    37,    -1,   121,    31,    34,   107,    40,   107,    35,
      37,    -1,   121,    32,    34,   107,    40,   107,    35,    37,
      -1,   120,    36,   107,    37,    -1,   120,    36,    34,   107,
      40,   107,    35,    37,    -1,   120,    27,    37,    -1,   120,
      28,    37,    -1,   120,    29,   107,    37,    -1,   120,    30,
     107,    37,    -1,   120,    31,   107,    37,    -1,   120,    32,
     107,    37,    -1,   120,    29,    34,   107,    40,   107,    35,
      37,    -1,   120,    30,    34,   107,    40,   107,    35,    37,
      -1,   120,    31,    34,   107,    40,   107,    35,    37,    -1,
     120,    32,    34,   107,    40,   107,    35,    37,    -1,    10,
      38,   107,    39,    73,    -1,    10,    38,   107,    39,    74,
      -1,    10,    38,   107,    39,    75,    -1,    10,    38,   107,
      39,    76,    -1,    11,    37,    -1,    12,    37,    -1,    15,
     119,    37,    -1,    15,   121,    37,    -1,    16,    38,   107,
      39,    37,    -1,   119,   119,   117,    41,   103,    37,    -1,
     119,   119,   117,    37,    -1,   104,    -1,   103,    40,   104,
      -1,   116,    -1,   119,    -1,    17,    38,    39,    37,    -1,
       9,   116,    37,    -1,   108,    -1,   109,    -1,   108,    26,
     109,    -1,   110,    -1,   109,    25,   110,    -1,   111,    -1,
     110,    23,   111,    -1,   110,    24,   111,    -1,   112,    -1,
     111,    42,   112,    -1,   111,    43,   112,    -1,   111,    21,
     112,    -1,   111,    22,   112,    -1,   113,    -1,   112,    44,
     113,    -1,   112,    45,   113,    -1,   114,    -1,   113,    46,
     114,    -1,   113,    47,   114,    -1,   113,    48,   114,    -1,
     115,    -1,    44,   114,    -1,    45,   114,    -1,   119,    -1,
     120,    -1,   121,    -1,   116,    -1,   123,    -1,    38,   107,
      39,    -1,   119,   117,    -1,    38,    39,    -1,    38,   118,
      39,    -1,   107,    -1,   118,    40,   107,    -1,    20,    -1,
      49,   119,    -1,    49,   119,    50,   119,    -1,   123,    -1,
      44,   123,    -1,    45,   123,    -1,   124,    -1,   125,    -1,
      18,    -1,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   160,   160,   167,   171,   180,   184,   191,   202,   213,
     224,   235,   246,   257,   268,   282,   293,   304,   315,   326,
     337,   348,   359,   373,   377,   386,   390,   399,   408,   412,
     421,   427,   433,   443,   447,   456,   460,   469,   479,   483,
     490,   495,   507,   511,   520,   531,   535,   544,   553,   557,
     566,   575,   579,   586,   590,   597,   601,   608,   612,   619,
     623,   632,   636,   645,   649,   658,   662,   671,   675,   679,
     683,   687,   691,   695,   699,   703,   707,   714,   718,   722,
     726,   730,   734,   738,   742,   746,   750,   757,   761,   765,
     769,   773,   777,   781,   785,   789,   796,   800,   804,   808,
     812,   816,   820,   824,   828,   832,   836,   843,   847,   854,
     860,   867,   877,   883,   890,   900,   906,   913,   923,   929,
     936,   946,   955,   960,   965,   970,   975,   980,   988,   994,
    1001,  1006,  1011,  1016,  1021,  1026,  1031,  1037,  1043,  1049,
    1058,  1064,  1071,  1076,  1081,  1086,  1091,  1096,  1101,  1107,
    1113,  1119,  1128,  1137,  1146,  1155,  1164,  1168,  1175,  1183,
    1191,  1199,  1209,  1221,  1225,  1234,  1238,  1246,  1253,  1261,
    1269,  1273,  1282,  1286,  1295,  1299,  1305,  1314,  1318,  1324,
    1330,  1336,  1345,  1349,  1355,  1364,  1368,  1374,  1380,  1389,
    1393,  1398,  1406,  1410,  1414,  1418,  1422,  1426,  1433,  1442,
    1446,  1453,  1458,  1470,  1478,  1487,  1498,  1502,  1506,  1514,
    1518,  1525,  1533
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEYWORD_CONTROLLER", "KEYWORD_EMITTER",
  "KEYWORD_AFFECTOR", "KEYWORD_FUNCTION", "KEYWORD_STATE", "KEYWORD_EVENT",
  "KEYWORD_RAISE", "KEYWORD_WHILE", "KEYWORD_BREAK", "KEYWORD_CONTINUE",
  "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_GOTO", "KEYWORD_WAIT",
  "KEYWORD_DIE", "INTEGER", "REAL", "IDENTIFIER", "SYMBOL_LTE",
  "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ", "SYMBOL_LOG_AND",
  "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC", "SYMBOL_ADD_A",
  "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A", "TOKEN_ERROR", "'{'",
  "'}'", "'='", "';'", "'('", "')'", "','", "':'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'$'", "'.'", "$accept", "script_file",
  "definition_list", "definition", "emitter_definition",
  "controller_definition", "member_list", "affector_list",
  "affector_declaration", "emitter_list", "emitter",
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
  "goto_statement", "member_goto_statement", "wait_statement",
  "fire_statement", "controller_list", "controller_entry", "die_statement",
  "raise_statement", "constant_expression", "logical_or_expression",
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
     285,   286,   287,   288,   123,   125,    61,    59,    40,    41,
      44,    58,    60,    62,    43,    45,    42,    47,    37,    36,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    58,    58,    59,    60,    60,
      61,    61,    61,    62,    62,    63,    63,    64,    65,    65,
      66,    66,    67,    67,    68,    69,    69,    70,    71,    71,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    85,    85,    86,
      86,    86,    87,    87,    87,    88,    88,    88,    89,    89,
      89,    90,    91,    91,    91,    91,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    94,    95,    96,    97,    98,    98,    99,   100,
     101,   102,   102,   103,   103,   104,   104,   105,   106,   107,
     108,   108,   109,   109,   110,   110,   110,   111,   111,   111,
     111,   111,   112,   112,   112,   113,   113,   113,   113,   114,
     114,   114,   115,   115,   115,   115,   115,   115,   116,   117,
     117,   118,   118,   119,   120,   121,   122,   122,   122,   123,
     123,   124,   125
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       7,     7,     5,     7,     7,     5,     7,     7,     5,     7,
       7,     4,     3,     3,     4,     4,     4,     4,     4,     8,
       3,     3,     4,     4,     4,     4,     8,     8,     8,     8,
       4,     8,     3,     3,     4,     4,     4,     4,     8,     8,
       8,     8,     5,     5,     5,     5,     2,     2,     3,     3,
       5,     6,     4,     1,     3,     1,     1,     4,     3,     1,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     1,     1,     1,     1,     1,     3,     2,     2,
       3,     1,     3,     1,     2,     4,     1,     2,     2,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,   203,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    42,
       0,    48,    23,     0,     0,     0,    25,     0,    35,     0,
      45,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      43,     0,     0,    15,    49,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    36,     0,     0,     7,    46,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   211,   212,     0,     0,     0,     0,
       0,   169,   170,   172,   174,   177,   182,   185,   189,   195,
     192,   193,   194,   196,   209,   210,     0,     0,     0,    11,
       0,     9,     0,     8,     0,     0,     0,     0,     0,     0,
      21,    20,    18,     0,     0,    50,     0,     0,     0,   190,
     191,   204,   121,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   198,     0,    13,
      12,    10,     0,     0,     0,     0,    47,    22,    30,     0,
       0,     0,     0,     0,     0,     0,     0,    57,   107,     0,
      65,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,   192,   194,    38,     0,    40,     0,    44,
     197,     0,   171,   173,   175,   176,   180,   181,   178,   179,
     183,   184,   186,   187,   188,   199,   201,     0,    14,    27,
       0,    37,     0,     0,     0,    55,     0,    63,    87,    88,
      89,    90,    91,    92,    93,    94,    95,   192,     0,     0,
       0,     0,    33,   206,     0,     0,   156,   157,     0,     0,
       0,     0,     0,    58,    66,   108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,     0,     0,     0,    53,     0,    61,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,   205,   200,     0,
       0,     0,     0,    51,     0,    59,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,   193,     0,     0,    56,
      64,     0,    31,   207,   208,     0,     0,   168,     0,     0,
       0,   158,   159,     0,   122,   123,     0,     0,     0,     0,
     130,   131,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,     0,     0,    54,    62,   202,     0,     0,
       0,    52,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    34,     0,     0,     0,   124,   125,
     126,   127,     0,   132,     0,   133,     0,   134,     0,   135,
       0,   128,     0,     0,     0,     0,     0,   142,   143,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   162,     0,   155,   118,   160,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   167,     0,   144,     0,   145,
       0,   146,     0,   147,     0,   140,   154,   115,     0,   163,
     165,   166,     0,     0,     0,     0,     0,     0,   153,   112,
     152,   109,     0,     0,     0,     0,     0,     0,   161,     0,
     119,   120,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,   117,   164,   136,   137,   138,
     139,   129,   113,   114,   110,   111,     0,     0,     0,     0,
       0,   148,   149,   150,   151,   141
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,   221,    27,    28,   117,   176,    18,    19,    29,    30,
      20,    21,   201,   179,   146,   115,   274,   255,   206,   159,
     275,   256,   207,   160,   161,   277,   258,   209,   162,    22,
     164,   165,   280,   281,   262,   212,   166,   167,   168,   169,
     170,   216,   408,   409,   285,   171,   172,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   137,   197,    90,    91,
      92,   222,    93,    94,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -307
static const short int yypact[] =
{
     217,    15,    15,    41,   217,  -307,  -307,  -307,  -307,    35,
      42,  -307,  -307,    15,    15,    15,    15,  -307,    15,  -307,
     -10,  -307,  -307,    45,    15,    15,  -307,    15,  -307,    52,
    -307,    58,    15,    15,   107,  -307,  -307,    15,   118,    88,
    -307,   192,    94,  -307,  -307,   116,   245,    15,    15,   197,
    -307,    15,   198,   126,  -307,   239,   140,  -307,  -307,   143,
     333,    15,   247,   258,  -307,   268,  -307,    99,  -307,   223,
     160,    15,    80,   150,  -307,  -307,   242,   242,   242,    15,
     158,   174,   183,   324,   301,   224,   209,  -307,  -307,  -307,
     188,  -307,  -307,  -307,  -307,  -307,    15,   279,   284,  -307,
     292,  -307,   402,  -307,   352,   227,    15,   150,   190,   322,
    -307,  -307,  -307,   270,   380,  -307,   -12,   214,   240,  -307,
    -307,   250,  -307,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   257,  -307,   326,  -307,
    -307,  -307,   273,   188,   271,   488,  -307,  -307,  -307,   253,
      15,   278,   281,   287,   299,     9,   303,  -307,  -307,   421,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,   313,   721,   733,  -307,   336,  -307,   434,  -307,
    -307,    15,   183,   324,   301,   301,   224,   224,   224,   224,
     209,   209,  -307,  -307,  -307,  -307,  -307,   340,  -307,  -307,
     528,  -307,   316,   331,    15,  -307,   541,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,   374,   330,   395,
     395,   387,  -307,  -307,   351,   242,  -307,  -307,   242,    15,
     360,   379,   242,  -307,  -307,  -307,   398,   401,   242,   242,
     242,   242,   242,   405,   411,   311,   589,   602,   623,   635,
    -307,    15,   335,   373,  -307,   475,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   242,
     417,   419,   424,  -307,   581,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,   743,   242,   242,  -307,
    -307,   188,  -307,  -307,  -307,   426,   196,  -307,   425,   428,
     250,  -307,  -307,   429,  -307,  -307,   436,   437,   438,   439,
    -307,  -307,   242,   440,   242,   443,   242,   444,   242,   445,
     242,   452,  -307,   242,   242,  -307,  -307,  -307,   242,   242,
     453,  -307,  -307,   454,   459,   644,   656,   677,   689,   698,
     458,   463,   131,  -307,  -307,    80,    80,   468,  -307,  -307,
    -307,  -307,   469,  -307,   471,  -307,   474,  -307,   476,  -307,
     477,  -307,   479,   482,   483,   489,   478,  -307,  -307,   242,
     490,   242,   492,   242,   493,   242,   494,   242,   497,   190,
     190,  -307,    15,  -307,   521,  -307,   242,   242,   242,   242,
     242,   214,   214,   271,   271,  -307,   496,  -307,   502,  -307,
     503,  -307,   509,  -307,   510,  -307,  -307,   544,   106,  -307,
    -307,   188,    21,   520,   527,   529,   532,   533,  -307,   555,
    -307,   556,   242,   242,   242,   242,   242,    75,  -307,    15,
    -307,  -307,   534,   537,   538,   543,   545,    78,    87,   546,
     548,   549,   552,   553,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,   558,   559,   565,   566,
     567,  -307,  -307,  -307,  -307,  -307
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -307,  -307,  -307,   585,  -307,  -307,   591,   582,    19,   595,
       6,  -307,   159,    -6,   504,  -307,   166,   186,   162,    73,
     132,    98,  -237,  -306,  -287,  -293,  -307,  -307,  -307,  -307,
     338,   358,   408,   456,   -89,   179,   187,   201,   219,    -4,
     -80,  -176,  -307,  -307,  -307,  -307,  -307,   -77,  -139,  -175,
    -129,  -191,  -307,   200,  -307,  -171,    -3,  -307,   512,   508,
     325,   235,   329,    57,  -307,  -101,   346,  -307,    -1,  -170,
     -96,   343,  -145,  -307,  -307
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   261,   265,   223,   142,   214,   266,     8,   284,
       8,    35,    23,    31,    23,    39,   215,    42,   174,    45,
      35,    54,    36,    31,    53,    43,    56,   175,    59,     8,
     286,    39,    42,    45,   154,     8,    42,    45,    36,   264,
      45,    11,    54,    80,    50,    54,    53,    56,    59,   224,
      56,    59,   383,   384,    59,   114,   208,    80,   229,   231,
      42,    45,    45,   174,    45,   211,    50,   214,   213,    13,
     113,   283,     8,   118,   293,   294,    14,   215,   121,   261,
     265,    46,   174,   284,   266,   418,   419,    57,   203,   257,
      54,   253,   406,   407,    60,    56,    59,    59,   260,    59,
     271,   263,    58,    71,   286,   143,    72,    73,    45,   145,
     163,   276,   178,   173,   114,   177,   264,   208,    44,   430,
     279,   200,    58,   282,    67,    58,   211,     8,    58,   213,
      69,   452,    44,   196,   119,   120,    44,    59,     8,    44,
     444,   210,    64,   428,   217,   283,   429,    34,    38,   143,
      41,   223,    70,    66,   230,   163,   420,   421,   173,   174,
      44,    44,   102,    44,    62,    63,   257,    72,   381,    65,
      58,    58,   382,    58,   259,   260,   104,   173,   263,   105,
     267,    33,    37,    48,    51,   276,    49,    52,   116,    55,
     192,   193,   194,   109,   279,   122,   278,   282,    61,   217,
     123,   454,   210,   230,    40,   217,    96,    44,   124,    97,
      98,    58,     8,   100,    74,    75,   291,     8,     8,    40,
       1,     2,   298,    40,   145,   299,   136,    68,   300,   303,
      72,    73,    99,   101,   108,   306,   307,   308,   309,    80,
     219,   220,   313,   315,   317,   319,   321,    40,   178,    71,
     322,   259,    72,    73,   173,   133,   134,   135,   138,     8,
      74,    75,     8,    74,    75,     8,   327,     8,   131,   132,
     278,    74,    75,   217,   103,    74,    75,     8,     8,   180,
      76,   410,   110,    76,   340,   341,    77,    78,     8,    77,
      78,    79,   218,   111,    79,    76,   195,   219,   220,     8,
     181,    77,    78,   112,     8,   200,    79,   148,   149,   352,
     199,   354,     8,   356,   139,   358,   225,   360,   226,   140,
     362,   363,   127,   128,   227,   364,   365,   141,   410,    74,
      75,     8,   370,   372,   374,   376,   378,   228,   106,   107,
     108,   232,     8,   129,   130,   312,     8,   125,   126,    76,
     235,    74,    75,     8,   287,    77,    78,   147,   107,   108,
      79,   198,   186,   187,   188,   189,   396,   292,   398,   288,
     400,    76,   402,   323,   404,   250,   251,    77,    78,   268,
     269,   411,    79,   413,   414,   415,   416,   417,   297,   150,
     151,   152,   153,   154,     8,   155,   156,   301,    74,    75,
       8,   236,   237,   238,   239,   240,   241,   106,   107,   108,
     242,   324,   136,    74,    75,   157,   302,   158,    76,   439,
     440,   441,   442,   443,    77,    78,   295,   296,   411,    79,
     150,   151,   152,   153,   154,   304,   155,   156,   305,    74,
      75,     8,   310,   150,   252,   152,   153,   253,   311,   155,
     184,   185,    74,    75,     8,   328,   233,   329,   158,    76,
     190,   191,   330,   343,   345,    77,    78,   346,   347,   254,
      79,   158,    76,   348,   349,   350,   351,   353,    77,    78,
     355,   357,   359,    79,   150,   252,   152,   153,   253,   361,
     155,   367,   366,    74,    75,     8,   368,   379,   202,   152,
     153,   203,   380,   204,   156,   385,    74,    75,     8,   386,
     325,   387,   158,    76,   388,   395,   389,   390,   391,    77,
      78,   392,   393,   205,    79,   158,    76,   397,   394,   399,
     401,   403,    77,    78,   405,   412,   422,    79,   270,   152,
     153,   271,   423,   424,   156,   272,    74,    75,     8,   425,
     426,   202,   152,   153,   203,   432,   204,   156,   427,    74,
      75,     8,   433,   273,   434,   158,    76,   435,   436,   437,
     438,   447,    77,    78,   448,   449,   289,    79,   158,    76,
     450,   456,   451,   457,   458,    77,    78,   459,   460,    12,
      79,   270,   152,   153,   271,   461,   462,   156,   272,    74,
      75,     8,   463,   464,   465,    24,    47,    74,    75,     8,
      32,   144,   332,   326,   290,   234,   331,   455,   158,    76,
      74,    75,     8,   314,   453,    77,    78,    76,   445,   446,
      79,   431,   183,    77,    78,   182,   316,   342,    79,   344,
      76,    74,    75,     8,     0,     0,    77,    78,     0,     0,
       0,    79,     0,    74,    75,     8,     0,   318,     0,     0,
       0,    76,    74,    75,     8,     0,     0,    77,    78,   320,
       0,     0,    79,    76,    74,    75,     8,     0,   369,    77,
      78,     0,    76,     0,    79,     0,     0,     0,    77,    78,
     371,     0,     0,    79,    76,    74,    75,     8,     0,     0,
      77,    78,     0,     0,     0,    79,     0,    74,    75,     8,
       0,   373,     0,     0,     0,    76,    74,    75,     8,     0,
       0,    77,    78,   375,     0,     0,    79,    76,     0,     0,
       0,     0,   377,    77,    78,     0,    76,     0,    79,     0,
       0,     0,    77,    78,     0,     0,     0,    79,   236,   237,
     238,   239,   240,   241,     0,     0,     0,   242,     0,   136,
     243,   244,   245,   246,   247,   248,     0,     0,     0,   249,
     333,   334,   335,   336,   337,   338,     0,     0,     0,   339
};

static const short int yycheck[] =
{
       1,     2,   178,   178,   149,   106,   145,   178,    20,   200,
      20,    15,    13,    14,    15,    16,   145,    18,   114,    20,
      24,    27,    16,    24,    25,    35,    27,    39,    29,    20,
     200,    32,    33,    34,    13,    20,    37,    38,    32,   178,
      41,     0,    48,    46,    25,    51,    47,    48,    49,   150,
      51,    52,   345,   346,    55,    34,   145,    60,    49,   155,
      61,    62,    63,   159,    65,   145,    47,   206,   145,    34,
      71,   200,    20,    76,   219,   220,    34,   206,    79,   255,
     255,    36,   178,   274,   255,   391,   392,    35,    13,   178,
      96,    13,   379,   380,    36,    96,    97,    98,   178,   100,
      13,   178,    29,     4,   274,   106,     7,     8,   109,    34,
     114,   200,    34,   114,    34,   116,   255,   206,    20,   412,
     200,    34,    49,   200,    36,    52,   206,    20,    55,   206,
      36,   437,    34,   136,    77,    78,    38,   138,    20,    41,
     427,   145,    35,    37,   145,   274,    40,    15,    16,   150,
      18,   296,    36,    35,   155,   159,   393,   394,   159,   255,
      62,    63,    36,    65,    32,    33,   255,     7,    37,    37,
      97,    98,    41,   100,   178,   255,    36,   178,   255,    36,
     181,    15,    16,    24,    25,   274,    24,    25,    38,    27,
     133,   134,   135,    61,   274,    37,   200,   274,    32,   200,
      26,   438,   206,   204,    18,   206,    47,   109,    25,    47,
      48,   138,    20,    51,    18,    19,   217,    20,    20,    33,
       3,     4,   225,    37,    34,   228,    38,    35,   229,   232,
       7,     8,    35,    35,     7,   238,   239,   240,   241,   242,
      44,    45,   245,   246,   247,   248,   249,    61,    34,     4,
     251,   255,     7,     8,   255,    46,    47,    48,    96,    20,
      18,    19,    20,    18,    19,    20,   269,    20,    44,    45,
     274,    18,    19,   274,    35,    18,    19,    20,    20,    39,
      38,   382,    35,    38,   287,   288,    44,    45,    20,    44,
      45,    49,    39,    35,    49,    38,    39,    44,    45,    20,
      50,    44,    45,    35,    20,    34,    49,    37,    38,   312,
      37,   314,    20,   316,    35,   318,    38,   320,    37,    35,
     323,   324,    21,    22,    37,   328,   329,    35,   429,    18,
      19,    20,   335,   336,   337,   338,   339,    38,     5,     6,
       7,    38,    20,    42,    43,    34,    20,    23,    24,    38,
      37,    18,    19,    20,    38,    44,    45,    35,     6,     7,
      49,    35,   127,   128,   129,   130,   369,    37,   371,    38,
     373,    38,   375,    38,   377,    39,    40,    44,    45,    39,
      40,   382,    49,   386,   387,   388,   389,   390,    37,     9,
      10,    11,    12,    13,    20,    15,    16,    37,    18,    19,
      20,    27,    28,    29,    30,    31,    32,     5,     6,     7,
      36,    38,    38,    18,    19,    35,    37,    37,    38,   422,
     423,   424,   425,   426,    44,    45,    39,    40,   429,    49,
       9,    10,    11,    12,    13,    37,    15,    16,    37,    18,
      19,    20,    37,     9,    10,    11,    12,    13,    37,    15,
     125,   126,    18,    19,    20,    38,    35,    38,    37,    38,
     131,   132,    38,    37,    39,    44,    45,    39,    39,    35,
      49,    37,    38,    37,    37,    37,    37,    37,    44,    45,
      37,    37,    37,    49,     9,    10,    11,    12,    13,    37,
      15,    37,    39,    18,    19,    20,    37,    39,    10,    11,
      12,    13,    39,    15,    16,    37,    18,    19,    20,    40,
      35,    40,    37,    38,    40,    37,    40,    40,    39,    44,
      45,    39,    39,    35,    49,    37,    38,    37,    39,    37,
      37,    37,    44,    45,    37,    14,    40,    49,    10,    11,
      12,    13,    40,    40,    16,    17,    18,    19,    20,    40,
      40,    10,    11,    12,    13,    35,    15,    16,    14,    18,
      19,    20,    35,    35,    35,    37,    38,    35,    35,    14,
      14,    37,    44,    45,    37,    37,    35,    49,    37,    38,
      37,    35,    37,    35,    35,    44,    45,    35,    35,     4,
      49,    10,    11,    12,    13,    37,    37,    16,    17,    18,
      19,    20,    37,    37,    37,    14,    24,    18,    19,    20,
      15,   107,   274,   255,   206,   159,    35,   438,    37,    38,
      18,    19,    20,    34,   437,    44,    45,    38,   427,   429,
      49,   412,   124,    44,    45,   123,    34,   291,    49,   296,
      38,    18,    19,    20,    -1,    -1,    44,    45,    -1,    -1,
      -1,    49,    -1,    18,    19,    20,    -1,    34,    -1,    -1,
      -1,    38,    18,    19,    20,    -1,    -1,    44,    45,    34,
      -1,    -1,    49,    38,    18,    19,    20,    -1,    34,    44,
      45,    -1,    38,    -1,    49,    -1,    -1,    -1,    44,    45,
      34,    -1,    -1,    49,    38,    18,    19,    20,    -1,    -1,
      44,    45,    -1,    -1,    -1,    49,    -1,    18,    19,    20,
      -1,    34,    -1,    -1,    -1,    38,    18,    19,    20,    -1,
      -1,    44,    45,    34,    -1,    -1,    49,    38,    -1,    -1,
      -1,    -1,    34,    44,    45,    -1,    38,    -1,    49,    -1,
      -1,    -1,    44,    45,    -1,    -1,    -1,    49,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    -1,    38,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    52,    53,    54,    55,    56,    20,   119,
     119,     0,    54,    34,    34,    57,    60,    61,    67,    68,
      71,    72,    90,   119,    57,    58,    59,    63,    64,    69,
      70,   119,    60,    67,    71,    90,    61,    67,    71,   119,
      68,    71,   119,    35,    72,   119,    36,    58,    63,    69,
      59,    63,    69,   119,    64,    69,   119,    35,    70,   119,
      36,    67,    71,    71,    35,    71,    35,    36,    35,    36,
      36,     4,     7,     8,    18,    19,    38,    44,    45,    49,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     119,   120,   121,   123,   124,   125,    63,    69,    69,    35,
      69,    35,    36,    35,    36,    36,     5,     6,     7,    71,
      35,    35,    35,   119,    34,    76,    38,    65,   107,   114,
     114,   119,    37,    26,    25,    23,    24,    21,    22,    42,
      43,    44,    45,    46,    47,    48,    38,   117,    69,    35,
      35,    35,   116,   119,    65,    34,    75,    35,    37,    38,
       9,    10,    11,    12,    13,    15,    16,    35,    37,    80,
      84,    85,    89,    90,    91,    92,    97,    98,    99,   100,
     101,   106,   107,   119,   121,    39,    66,   119,    34,    74,
      39,    50,   109,   110,   111,   111,   112,   112,   112,   112,
     113,   113,   114,   114,   114,    39,   107,   118,    35,    37,
      34,    73,    10,    13,    15,    35,    79,    83,    85,    88,
      90,    91,    96,    98,    99,   101,   102,   119,    39,    44,
      45,    62,   122,   123,   116,    38,    37,    37,    38,    49,
     119,   121,    38,    35,    84,    37,    27,    28,    29,    30,
      31,    32,    36,    27,    28,    29,    30,    31,    32,    36,
      39,    40,    10,    13,    35,    78,    82,    85,    87,    90,
      91,    92,    95,    98,    99,   100,   106,   119,    39,    40,
      10,    13,    17,    35,    77,    81,    85,    86,    90,    91,
      93,    94,    98,   101,   102,   105,   120,    38,    38,    35,
      83,   119,    37,   123,   123,    39,    40,    37,   107,   107,
     119,    37,    37,   107,    37,    37,   107,   107,   107,   107,
      37,    37,    34,   107,    34,   107,    34,   107,    34,   107,
      34,   107,   119,    38,    38,    35,    82,   107,    38,    38,
      38,    35,    81,    27,    28,    29,    30,    31,    32,    36,
     107,   107,   117,    37,   122,    39,    39,    39,    37,    37,
      37,    37,   107,    37,   107,    37,   107,    37,   107,    37,
     107,    37,   107,   107,   107,   107,    39,    37,    37,    34,
     107,    34,   107,    34,   107,    34,   107,    34,   107,    39,
      39,    37,    41,    76,    76,    37,    40,    40,    40,    40,
      40,    39,    39,    39,    39,    37,   107,    37,   107,    37,
     107,    37,   107,    37,   107,    37,    75,    75,   103,   104,
     116,   119,    14,   107,   107,   107,   107,   107,    74,    74,
      73,    73,    40,    40,    40,    40,    40,    14,    37,    40,
      76,    89,    35,    35,    35,    35,    35,    14,    14,   107,
     107,   107,   107,   107,    75,    88,   104,    37,    37,    37,
      37,    37,    74,    87,    73,    86,    35,    35,    35,    35,
      35,    37,    37,    37,    37,    37
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
#line 161 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 168 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 172 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 181 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 185 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 192 "BulletParser.y"
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
#line 203 "BulletParser.y"
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
#line 214 "BulletParser.y"
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
#line 225 "BulletParser.y"
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
#line 236 "BulletParser.y"
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
#line 247 "BulletParser.y"
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
#line 258 "BulletParser.y"
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
#line 269 "BulletParser.y"
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
#line 283 "BulletParser.y"
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
#line 294 "BulletParser.y"
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
#line 305 "BulletParser.y"
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
#line 316 "BulletParser.y"
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
#line 327 "BulletParser.y"
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
#line 338 "BulletParser.y"
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
#line 349 "BulletParser.y"
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
#line 360 "BulletParser.y"
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
#line 374 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 378 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 387 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 391 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 400 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 28:
#line 409 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 413 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 422 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 31:
#line 428 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-3]));
		;}
    break;

  case 32:
#line 434 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 33:
#line 444 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 34:
#line 448 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 35:
#line 457 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 461 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 37:
#line 470 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 38:
#line 480 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 39:
#line 484 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 40:
#line 491 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 41:
#line 496 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 42:
#line 508 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 512 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 521 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 45:
#line 532 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 536 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 545 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 48:
#line 554 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 558 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 567 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 576 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 52:
#line 580 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 53:
#line 587 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 54:
#line 591 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 55:
#line 598 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 56:
#line 602 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 57:
#line 609 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 58:
#line 613 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 59:
#line 620 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 624 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 61:
#line 633 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 637 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 646 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 650 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 65:
#line 659 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 66:
#line 663 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 67:
#line 672 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 676 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 680 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 684 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 688 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 692 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 696 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 700 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 704 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 708 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 715 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 719 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 723 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 727 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 731 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 735 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 739 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 743 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 747 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 86:
#line 751 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 87:
#line 758 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 88:
#line 762 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 766 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 770 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 774 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 778 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 782 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 786 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 95:
#line 790 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 96:
#line 797 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 97:
#line 801 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 805 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 809 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 813 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 817 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 821 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 825 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 829 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 833 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 837 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 844 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 108:
#line 848 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 109:
#line 855 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 110:
#line 861 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 111:
#line 868 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 112:
#line 878 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 113:
#line 884 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 114:
#line 891 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 115:
#line 901 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 116:
#line 907 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 117:
#line 914 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 118:
#line 924 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 119:
#line 930 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 120:
#line 937 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 121:
#line 947 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 122:
#line 956 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 123:
#line 961 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 124:
#line 966 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 125:
#line 971 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 126:
#line 976 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 127:
#line 981 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 128:
#line 989 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 129:
#line 995 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 130:
#line 1002 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 131:
#line 1007 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 132:
#line 1012 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 133:
#line 1017 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 134:
#line 1022 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 135:
#line 1027 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 136:
#line 1032 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 137:
#line 1038 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 138:
#line 1044 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 139:
#line 1050 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 140:
#line 1059 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 141:
#line 1065 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1072 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 143:
#line 1077 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 144:
#line 1082 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 145:
#line 1087 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 146:
#line 1092 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 147:
#line 1097 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 148:
#line 1102 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 149:
#line 1108 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 150:
#line 1114 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 151:
#line 1120 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 152:
#line 1129 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 153:
#line 1138 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 154:
#line 1147 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 155:
#line 1156 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 156:
#line 1165 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 157:
#line 1169 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 158:
#line 1176 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 159:
#line 1184 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 160:
#line 1192 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 161:
#line 1200 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 162:
#line 1210 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FireStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 163:
#line 1222 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 164:
#line 1226 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 165:
#line 1235 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 166:
#line 1239 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 167:
#line 1247 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 168:
#line 1254 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 169:
#line 1262 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 170:
#line 1270 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 171:
#line 1274 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 172:
#line 1283 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 173:
#line 1287 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 174:
#line 1296 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 175:
#line 1300 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 176:
#line 1306 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 177:
#line 1315 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 178:
#line 1319 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 179:
#line 1325 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 180:
#line 1331 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 181:
#line 1337 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 182:
#line 1346 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 183:
#line 1350 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 184:
#line 1356 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 185:
#line 1365 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 186:
#line 1369 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1375 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 188:
#line 1381 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 189:
#line 1390 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 190:
#line 1394 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 191:
#line 1399 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 192:
#line 1407 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 193:
#line 1411 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 194:
#line 1415 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 195:
#line 1419 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 196:
#line 1423 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 197:
#line 1427 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 198:
#line 1434 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 199:
#line 1443 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 200:
#line 1447 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 201:
#line 1454 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 202:
#line 1459 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 203:
#line 1471 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 204:
#line 1479 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 205:
#line 1488 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 206:
#line 1499 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 207:
#line 1503 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 208:
#line 1507 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 209:
#line 1515 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 210:
#line 1519 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 211:
#line 1526 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 212:
#line 1534 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3570 "bsBulletParser.cpp"

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


#line 1540 "BulletParser.y"


	
	

