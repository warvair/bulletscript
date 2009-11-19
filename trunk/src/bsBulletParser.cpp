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
     KEYWORD_DIE = 274,
     INTEGER = 275,
     REAL = 276,
     IDENTIFIER = 277,
     SYMBOL_LTE = 278,
     SYMBOL_GTE = 279,
     SYMBOL_EQ = 280,
     SYMBOL_NEQ = 281,
     SYMBOL_LOG_AND = 282,
     SYMBOL_LOG_OR = 283,
     SYMBOL_INC = 284,
     SYMBOL_DEC = 285,
     SYMBOL_ADD_A = 286,
     SYMBOL_SUB_A = 287,
     SYMBOL_MUL_A = 288,
     SYMBOL_DIV_A = 289,
     TOKEN_ERROR = 290
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
#define KEYWORD_DIE 274
#define INTEGER 275
#define REAL 276
#define IDENTIFIER 277
#define SYMBOL_LTE 278
#define SYMBOL_GTE 279
#define SYMBOL_EQ 280
#define SYMBOL_NEQ 281
#define SYMBOL_LOG_AND 282
#define SYMBOL_LOG_OR 283
#define SYMBOL_INC 284
#define SYMBOL_DEC 285
#define SYMBOL_ADD_A 286
#define SYMBOL_SUB_A 287
#define SYMBOL_MUL_A 288
#define SYMBOL_DIV_A 289
#define TOKEN_ERROR 290




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
#line 290 "bsBulletParser.cpp"

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
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  76
/* YYNRULES -- Number of rules. */
#define YYNRULES  218
/* YYNRULES -- Number of states. */
#define YYNSTATES  479

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    44,    51,     2,     2,
      40,    41,    49,    47,    42,    48,    52,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    39,
      45,    38,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      35
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
     373,   376,   382,   390,   398,   404,   412,   420,   426,   434,
     442,   448,   456,   464,   469,   473,   477,   482,   487,   492,
     497,   502,   511,   515,   519,   524,   529,   534,   539,   548,
     557,   566,   575,   580,   589,   593,   597,   602,   607,   612,
     617,   626,   635,   644,   653,   659,   665,   671,   677,   680,
     683,   687,   691,   697,   704,   709,   711,   715,   717,   719,
     724,   727,   731,   735,   740,   745,   747,   749,   753,   755,
     759,   761,   765,   769,   771,   775,   779,   783,   787,   789,
     793,   797,   799,   803,   807,   811,   813,   816,   819,   821,
     823,   825,   827,   829,   833,   836,   839,   843,   845,   849,
     851,   854,   859,   861,   864,   867,   869,   871,   873
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
      54,     0,    -1,    55,    -1,    56,    -1,    55,    56,    -1,
      57,    -1,    58,    -1,     4,   122,    36,    71,    37,    -1,
       4,   122,    36,    65,    71,    37,    -1,     4,   122,    36,
      60,    71,    37,    -1,     4,   122,    36,    60,    65,    71,
      37,    -1,     4,   122,    36,    59,    71,    37,    -1,     4,
     122,    36,    59,    65,    71,    37,    -1,     4,   122,    36,
      59,    60,    71,    37,    -1,     4,   122,    36,    59,    60,
      65,    71,    37,    -1,     3,   122,    36,    73,    37,    -1,
       3,   122,    36,    69,    73,    37,    -1,     3,   122,    36,
      62,    73,    37,    -1,     3,   122,    36,    62,    69,    73,
      37,    -1,     3,   122,    36,    59,    73,    37,    -1,     3,
     122,    36,    59,    69,    73,    37,    -1,     3,   122,    36,
      59,    62,    73,    37,    -1,     3,   122,    36,    59,    62,
      69,    73,    37,    -1,    92,    -1,    59,    92,    -1,    61,
      -1,    60,    61,    -1,   122,    38,     5,   119,    39,    -1,
      63,    -1,    62,    63,    -1,   122,    38,     4,   122,    39,
      -1,   122,    38,     4,   122,    40,    41,    39,    -1,   122,
      38,     4,   122,    40,    64,    41,    39,    -1,   125,    -1,
      64,    42,   125,    -1,    66,    -1,    65,    66,    -1,   122,
      38,     6,    67,    75,    -1,    40,    41,    -1,    40,    68,
      41,    -1,   122,    -1,    68,    42,   122,    -1,    70,    -1,
      69,    70,    -1,   122,    38,     8,    67,    76,    -1,    72,
      -1,    71,    72,    -1,   122,    38,     7,    77,    -1,    74,
      -1,    73,    74,    -1,   122,    38,     7,    78,    -1,    36,
      37,    -1,    36,    79,    37,    -1,    36,    37,    -1,    36,
      80,    37,    -1,    36,    37,    -1,    36,    81,    37,    -1,
      36,    37,    -1,    36,    82,    37,    -1,    83,    -1,    79,
      83,    -1,    84,    -1,    80,    84,    -1,    85,    -1,    81,
      85,    -1,    86,    -1,    82,    86,    -1,    87,    -1,    88,
      -1,    92,    -1,    93,    -1,    95,    -1,    96,    -1,   100,
      -1,   103,    -1,   104,    -1,   107,    -1,    87,    -1,    89,
      -1,    92,    -1,    93,    -1,    94,    -1,    97,    -1,   100,
      -1,   101,    -1,   102,    -1,   108,    -1,   109,    -1,    87,
      -1,    90,    -1,    92,    -1,    93,    -1,    98,    -1,   100,
      -1,   101,    -1,   103,    -1,   104,    -1,    87,    -1,    91,
      -1,    92,    -1,    93,    -1,    94,    -1,    99,    -1,   100,
      -1,   101,    -1,   102,    -1,   103,    -1,   108,    -1,   109,
      -1,    39,    -1,   110,    39,    -1,    15,    40,   110,    41,
      75,    -1,    15,    40,   110,    41,    75,    16,    75,    -1,
      15,    40,   110,    41,    75,    16,    88,    -1,    15,    40,
     110,    41,    76,    -1,    15,    40,   110,    41,    76,    16,
      76,    -1,    15,    40,   110,    41,    76,    16,    89,    -1,
      15,    40,   110,    41,    77,    -1,    15,    40,   110,    41,
      77,    16,    77,    -1,    15,    40,   110,    41,    77,    16,
      90,    -1,    15,    40,   110,    41,    78,    -1,    15,    40,
     110,    41,    78,    16,    78,    -1,    15,    40,   110,    41,
      78,    16,    91,    -1,   122,    38,   110,    39,    -1,   122,
      29,    39,    -1,   122,    30,    39,    -1,   122,    31,   110,
      39,    -1,   122,    32,   110,    39,    -1,   122,    33,   110,
      39,    -1,   122,    34,   110,    39,    -1,   124,    38,   110,
      39,    -1,   124,    38,    36,   110,    42,   110,    37,    39,
      -1,   124,    29,    39,    -1,   124,    30,    39,    -1,   124,
      31,   110,    39,    -1,   124,    32,   110,    39,    -1,   124,
      33,   110,    39,    -1,   124,    34,   110,    39,    -1,   124,
      31,    36,   110,    42,   110,    37,    39,    -1,   124,    32,
      36,   110,    42,   110,    37,    39,    -1,   124,    33,    36,
     110,    42,   110,    37,    39,    -1,   124,    34,    36,   110,
      42,   110,    37,    39,    -1,   123,    38,   110,    39,    -1,
     123,    38,    36,   110,    42,   110,    37,    39,    -1,   123,
      29,    39,    -1,   123,    30,    39,    -1,   123,    31,   110,
      39,    -1,   123,    32,   110,    39,    -1,   123,    33,   110,
      39,    -1,   123,    34,   110,    39,    -1,   123,    31,    36,
     110,    42,   110,    37,    39,    -1,   123,    32,    36,   110,
      42,   110,    37,    39,    -1,   123,    33,    36,   110,    42,
     110,    37,    39,    -1,   123,    34,    36,   110,    42,   110,
      37,    39,    -1,    12,    40,   110,    41,    75,    -1,    12,
      40,   110,    41,    76,    -1,    12,    40,   110,    41,    77,
      -1,    12,    40,   110,    41,    78,    -1,    13,    39,    -1,
      14,    39,    -1,    17,   122,    39,    -1,    17,   124,    39,
      -1,    18,    40,   110,    41,    39,    -1,   122,   122,   120,
      43,   105,    39,    -1,   122,   122,   120,    39,    -1,   106,
      -1,   105,    42,   106,    -1,   119,    -1,   122,    -1,    19,
      40,    41,    39,    -1,    19,    39,    -1,     9,   119,    39,
      -1,     9,   122,    39,    -1,    10,    44,   122,    39,    -1,
      11,    44,   122,    39,    -1,   111,    -1,   112,    -1,   111,
      28,   112,    -1,   113,    -1,   112,    27,   113,    -1,   114,
      -1,   113,    25,   114,    -1,   113,    26,   114,    -1,   115,
      -1,   114,    45,   115,    -1,   114,    46,   115,    -1,   114,
      23,   115,    -1,   114,    24,   115,    -1,   116,    -1,   115,
      47,   116,    -1,   115,    48,   116,    -1,   117,    -1,   116,
      49,   117,    -1,   116,    50,   117,    -1,   116,    51,   117,
      -1,   118,    -1,    47,   117,    -1,    48,   117,    -1,   122,
      -1,   123,    -1,   124,    -1,   119,    -1,   126,    -1,    40,
     110,    41,    -1,   122,   120,    -1,    40,    41,    -1,    40,
     121,    41,    -1,   110,    -1,   121,    42,   110,    -1,    22,
      -1,    44,   122,    -1,    44,   122,    52,   122,    -1,   126,
      -1,    47,   126,    -1,    48,   126,    -1,   127,    -1,   128,
      -1,    20,    -1,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   162,   162,   169,   173,   182,   186,   193,   204,   215,
     226,   237,   248,   259,   270,   284,   295,   306,   317,   328,
     339,   350,   361,   375,   379,   388,   392,   401,   410,   414,
     423,   429,   435,   445,   449,   458,   462,   471,   481,   485,
     492,   497,   509,   513,   522,   533,   537,   546,   555,   559,
     568,   577,   581,   588,   592,   599,   603,   610,   614,   621,
     625,   634,   638,   647,   651,   660,   664,   673,   677,   681,
     685,   689,   693,   697,   701,   705,   709,   716,   720,   724,
     728,   732,   736,   740,   744,   748,   752,   756,   763,   767,
     771,   775,   779,   783,   787,   791,   795,   802,   806,   810,
     814,   818,   822,   826,   830,   834,   838,   842,   846,   853,
     857,   864,   870,   877,   887,   893,   900,   910,   916,   923,
     933,   939,   946,   956,   965,   970,   975,   980,   985,   990,
     998,  1004,  1011,  1016,  1021,  1026,  1031,  1036,  1041,  1047,
    1053,  1059,  1068,  1074,  1081,  1086,  1091,  1096,  1101,  1106,
    1111,  1117,  1123,  1129,  1138,  1147,  1156,  1165,  1174,  1178,
    1185,  1193,  1201,  1209,  1219,  1231,  1235,  1244,  1248,  1256,
    1260,  1267,  1272,  1280,  1286,  1295,  1303,  1307,  1316,  1320,
    1329,  1333,  1339,  1348,  1352,  1358,  1364,  1370,  1379,  1383,
    1389,  1398,  1402,  1408,  1414,  1423,  1427,  1432,  1440,  1444,
    1448,  1452,  1456,  1460,  1467,  1476,  1480,  1487,  1492,  1504,
    1512,  1521,  1532,  1536,  1540,  1548,  1552,  1559,  1567
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
  "KEYWORD_GOTO", "KEYWORD_WAIT", "KEYWORD_DIE", "INTEGER", "REAL",
  "IDENTIFIER", "SYMBOL_LTE", "SYMBOL_GTE", "SYMBOL_EQ", "SYMBOL_NEQ",
  "SYMBOL_LOG_AND", "SYMBOL_LOG_OR", "SYMBOL_INC", "SYMBOL_DEC",
  "SYMBOL_ADD_A", "SYMBOL_SUB_A", "SYMBOL_MUL_A", "SYMBOL_DIV_A",
  "TOKEN_ERROR", "'{'", "'}'", "'='", "';'", "'('", "')'", "','", "':'",
  "'$'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'.'", "$accept",
  "script_file", "definition_list", "definition", "emitter_definition",
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
  "emit_statement", "controller_list", "controller_entry", "die_statement",
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
     285,   286,   287,   288,   289,   290,   123,   125,    61,    59,
      40,    41,    44,    58,    36,    60,    62,    43,    45,    42,
      47,    37,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    60,    60,    61,    62,    62,
      63,    63,    63,    64,    64,    65,    65,    66,    67,    67,
      68,    68,    69,    69,    70,    71,    71,    72,    73,    73,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    80,    80,    81,    81,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    87,
      87,    88,    88,    88,    89,    89,    89,    90,    90,    90,
      91,    91,    91,    92,    93,    93,    93,    93,    93,    93,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    96,    97,    98,    99,   100,   100,
     101,   102,   103,   104,   104,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   110,   111,   111,   112,   112,
     113,   113,   113,   114,   114,   114,   114,   114,   115,   115,
     115,   116,   116,   116,   116,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   119,   120,   120,   121,   121,   122,
     123,   124,   125,   125,   125,   126,   126,   127,   128
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
       2,     5,     7,     7,     5,     7,     7,     5,     7,     7,
       5,     7,     7,     4,     3,     3,     4,     4,     4,     4,
       4,     8,     3,     3,     4,     4,     4,     4,     8,     8,
       8,     8,     4,     8,     3,     3,     4,     4,     4,     4,
       8,     8,     8,     8,     5,     5,     5,     5,     2,     2,
       3,     3,     5,     6,     4,     1,     3,     1,     1,     4,
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
       0,     0,     0,     0,     2,     3,     5,     6,   209,     0,
       0,     1,     4,     0,     0,     0,     0,    28,     0,    42,
       0,    48,    23,     0,     0,     0,    25,     0,    35,     0,
      45,     0,     0,     0,     0,    24,    29,     0,     0,     0,
      43,     0,     0,    15,    49,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    36,     0,     0,     7,    46,     0,
       0,     0,     0,     0,    19,     0,    17,     0,    16,     0,
       0,     0,     0,     0,   217,   218,     0,     0,     0,     0,
       0,   175,   176,   178,   180,   183,   188,   191,   195,   201,
     198,   199,   200,   202,   215,   216,     0,     0,     0,    11,
       0,     9,     0,     8,     0,     0,     0,     0,     0,     0,
      21,    20,    18,     0,     0,    50,     0,     0,     0,   210,
     196,   197,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   204,     0,    13,
      12,    10,     0,     0,     0,     0,    47,    22,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
     109,     0,    65,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     0,   198,   200,    38,     0,
      40,     0,    44,   203,     0,   177,   179,   181,   182,   186,
     187,   184,   185,   189,   190,   192,   193,   194,   205,   207,
       0,    14,    27,     0,    37,     0,     0,     0,    55,     0,
      63,    88,    89,    90,    91,    92,    93,    94,    95,    96,
     198,     0,     0,     0,     0,    33,   212,     0,     0,     0,
       0,     0,   158,   159,     0,     0,     0,     0,     0,    58,
      66,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,     0,     0,     0,
      53,     0,    61,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   211,   206,     0,     0,     0,     0,
      51,     0,    59,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,   199,     0,     0,    56,    64,     0,    31,
     213,   214,     0,     0,   171,   172,     0,     0,     0,     0,
       0,   160,   161,     0,   124,   125,     0,     0,     0,     0,
     132,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,     0,     0,    54,    62,   208,     0,     0,
     170,     0,    52,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,    34,   173,   174,     0,     0,
       0,   126,   127,   128,   129,     0,   134,     0,   135,     0,
     136,     0,   137,     0,   130,     0,     0,     0,     0,     0,
     144,   145,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,     0,   157,   120,   162,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   169,     0,
     146,     0,   147,     0,   148,     0,   149,     0,   142,   156,
     117,     0,   165,   167,   168,     0,     0,     0,     0,     0,
       0,   155,   114,   154,   111,     0,     0,     0,     0,     0,
       0,   163,     0,   121,   122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,   119,   166,
     138,   139,   140,   141,   131,   115,   116,   112,   113,     0,
       0,     0,     0,     0,   150,   151,   152,   153,   143
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    15,    25,    26,    16,
      17,   224,    27,    28,   117,   179,    18,    19,    29,    30,
      20,    21,   204,   182,   146,   115,   281,   261,   209,   161,
     282,   262,   210,   162,   163,   284,   264,   212,   164,    22,
     166,   167,   287,   288,   268,   215,   168,   169,   170,   171,
     172,   219,   421,   422,   292,   173,   174,   175,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   137,   200,    90,
      91,    92,   225,    93,    94,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -317
static const short int yypact[] =
{
     183,    13,    13,    21,   183,  -317,  -317,  -317,  -317,    19,
      39,  -317,  -317,    13,    13,    13,    13,  -317,    13,  -317,
     185,  -317,  -317,    64,    13,    13,  -317,    13,  -317,   187,
    -317,    71,    13,    13,   188,  -317,  -317,    13,   193,    73,
    -317,   204,   146,  -317,  -317,   153,   274,    13,    13,   209,
    -317,    13,   213,   166,  -317,   221,   189,  -317,  -317,   207,
     269,    13,   222,   230,  -317,   251,  -317,   328,  -317,   210,
     172,    13,   160,   239,  -317,  -317,   349,    13,   349,   349,
     208,   264,   288,   228,   105,   281,   341,  -317,  -317,  -317,
     270,  -317,  -317,  -317,  -317,  -317,    13,   265,   283,  -317,
     305,  -317,   440,  -317,   331,   242,    13,   239,   304,   309,
    -317,  -317,  -317,   322,   422,  -317,   159,   342,   278,   272,
    -317,  -317,  -317,   349,   349,   349,   349,   349,   349,   349,
     349,   349,   349,   349,   349,   349,   192,  -317,   338,  -317,
    -317,  -317,   335,   270,   359,   286,  -317,  -317,  -317,   141,
      13,   354,   356,   364,   376,   390,   398,     5,   420,  -317,
    -317,   462,  -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,
    -317,  -317,  -317,  -317,  -317,   424,   708,   392,  -317,   307,
    -317,   476,  -317,  -317,    13,   288,   228,   105,   105,   281,
     281,   281,   281,   341,   341,  -317,  -317,  -317,  -317,  -317,
     367,  -317,  -317,   528,  -317,   425,   427,    13,  -317,   565,
    -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,
     696,   429,   362,   362,   370,  -317,  -317,   439,   388,    13,
      13,   349,  -317,  -317,   349,    13,   442,   453,   349,  -317,
    -317,  -317,   455,   456,   349,   349,   349,   349,   349,   461,
     464,   332,   337,   366,   586,   607,  -317,    13,   465,   467,
    -317,   516,  -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,
    -317,  -317,  -317,  -317,  -317,  -317,   349,   468,   471,   409,
    -317,   577,  -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,
    -317,  -317,  -317,   720,   349,   349,  -317,  -317,   270,  -317,
    -317,  -317,   473,   150,  -317,  -317,   475,   478,   423,   463,
     272,  -317,  -317,   477,  -317,  -317,   480,   482,   483,   493,
    -317,  -317,   349,   495,   349,   496,   349,   500,   349,   505,
     349,   506,  -317,   349,   349,  -317,  -317,  -317,   349,   349,
    -317,   510,  -317,  -317,   513,   515,   616,   637,   646,   667,
     676,   517,   518,    29,  -317,  -317,  -317,  -317,   160,   160,
     522,  -317,  -317,  -317,  -317,   520,  -317,   524,  -317,   527,
    -317,   529,  -317,   531,  -317,   533,   540,   543,   547,   554,
    -317,  -317,   349,   555,   349,   561,   349,   562,   349,   564,
     349,   571,   304,   304,  -317,    13,  -317,   541,  -317,   349,
     349,   349,   349,   349,   342,   342,   359,   359,  -317,   569,
    -317,   573,  -317,   576,  -317,   578,  -317,   581,  -317,  -317,
     603,     2,  -317,  -317,   270,    70,   594,   595,   598,   602,
     604,  -317,   624,  -317,   626,   349,   349,   349,   349,   349,
      83,  -317,    13,  -317,  -317,   605,   606,   609,   610,   611,
     106,   132,   625,   628,   632,   633,   634,  -317,  -317,  -317,
    -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,  -317,   614,
     622,   635,   636,   639,  -317,  -317,  -317,  -317,  -317
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -317,  -317,  -317,   566,  -317,  -317,   658,   652,    34,   631,
     169,  -317,    79,    -9,   572,  -317,   158,    -8,   107,    78,
     205,   102,  -316,  -287,  -292,  -301,  -317,  -317,  -317,  -317,
     399,   430,   474,   534,  -136,   241,   249,   260,   276,    -4,
    -115,  -179,  -317,  -317,  -317,  -317,  -317,   -89,  -138,  -178,
    -129,  -169,  -317,   262,  -317,  -177,  -175,    17,  -317,   579,
     582,   325,   156,   326,    60,  -317,   -98,   407,  -317,    -1,
    -165,   -92,   405,  -144,  -317,  -317
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
       9,    10,   267,   271,   272,   226,   273,   217,   142,   211,
      40,    35,    23,    31,    23,    39,   218,    42,    54,    45,
      35,    11,   177,    31,    53,    40,    56,     8,    59,    40,
     214,    39,    42,    45,   291,     8,    42,    45,   293,    54,
      45,   441,    54,   270,   442,   263,    53,    56,    59,   235,
      56,    59,   227,    40,    59,    13,   216,   396,   397,    50,
      42,    45,    45,    80,    45,   237,   266,   283,   394,   177,
     113,   217,   395,   211,   290,    14,   119,    80,   300,   301,
     218,    50,   267,   271,   272,   156,   273,    54,   286,   177,
     433,   434,   269,   118,   214,    56,    59,    59,   206,    59,
     419,   420,    46,    48,    51,   143,   114,    58,    45,    60,
     165,    67,   291,   176,   289,   180,   293,   431,   432,   145,
     216,   259,    44,   270,   443,   263,    96,    58,   127,   128,
      58,    49,    52,    58,    55,   467,    44,    59,   120,   121,
      44,   213,   181,    44,   220,   283,   266,   278,   457,   228,
     129,   130,   290,   199,    97,    98,   236,   165,   100,   226,
     176,    74,    75,   465,    44,    44,   286,    44,   203,   177,
      74,    75,   269,    33,    37,    58,    58,   265,    58,    72,
     176,     8,   221,   274,    69,    36,     1,     2,   222,   223,
      61,    70,   289,   195,   196,   197,   114,   222,   223,   285,
     178,    36,   220,   138,   102,   213,   236,     8,   220,     8,
       8,    44,    74,    75,     8,     8,    58,    72,    73,   298,
      34,    38,    43,    41,    57,    64,     8,   104,   306,   307,
      66,     8,    76,   198,   310,     8,    77,    62,    63,    78,
      79,    68,    65,     8,     8,   105,    99,   122,   308,   108,
     101,   309,     8,   125,   126,   313,   332,   265,   103,   110,
     176,   316,   317,   318,   319,    80,   109,   111,   323,   325,
     327,   329,   331,     8,   106,   107,   108,   285,    71,   116,
     220,    72,    73,   189,   190,   191,   192,     8,   112,    74,
      75,     8,   123,   337,    74,    75,     8,   423,   205,   154,
     155,   206,   139,   207,   158,     8,    74,    75,     8,    76,
     136,   351,   352,    77,    76,   124,    78,    79,    77,   183,
     140,    78,    79,   208,   184,   160,    76,     8,   131,   132,
      77,     8,    71,    78,    79,    72,    73,   107,   108,   365,
     145,   367,   141,   369,   423,   371,   147,   373,   256,   257,
     375,   376,    74,    75,     8,   377,   378,    74,    75,     8,
       8,   148,   149,   383,   385,   387,   389,   391,   322,    74,
      75,     8,    76,   324,   202,   201,    77,    76,   181,    78,
      79,    77,    74,    75,    78,    79,    74,    75,     8,    76,
     133,   134,   135,    77,   424,   203,    78,    79,   229,   409,
     230,   411,   326,   413,   231,   415,    76,   417,   275,   276,
      77,   302,   303,    78,    79,   232,   426,   427,   428,   429,
     430,   249,   250,   251,   252,   253,   254,   305,   136,   233,
     255,   150,   151,   152,   153,   154,   155,   156,   234,   157,
     158,   424,    74,    75,     8,   106,   107,   108,   340,   341,
     187,   188,   452,   453,   454,   455,   456,   193,   194,   159,
     238,   160,    76,   241,   358,   294,    77,   295,   299,    78,
      79,   150,   151,   152,   153,   154,   155,   156,   304,   157,
     158,   311,    74,    75,     8,   150,   151,   152,   258,   154,
     155,   259,   312,   157,   314,   315,    74,    75,     8,   239,
     320,   160,    76,   321,   359,   333,    77,   334,   338,    78,
      79,   339,   354,   260,   356,   160,    76,   357,   360,   361,
      77,   362,   363,    78,    79,   150,   151,   152,   258,   154,
     155,   259,   364,   157,   366,   368,    74,    75,     8,   370,
     277,   154,   155,   278,   372,   374,   158,   279,    74,    75,
       8,   379,   380,   335,   381,   160,    76,   425,   392,   393,
      77,   398,   399,    78,    79,   280,   400,   160,    76,   401,
      12,   402,    77,   403,   404,    78,    79,   205,   154,   155,
     206,   405,   207,   158,   406,    74,    75,     8,   407,   277,
     154,   155,   278,   408,   410,   158,   279,    74,    75,     8,
     412,   414,   296,   416,   160,    76,    74,    75,     8,    77,
     418,   435,    78,    79,   342,   436,   160,    76,   437,   440,
     438,    77,   328,   439,    78,    79,    76,    74,    75,     8,
      77,   445,   446,    78,    79,   447,    74,    75,     8,   448,
     450,   449,   451,   330,   460,   461,    32,    76,   462,   463,
     464,    77,   382,   474,    78,    79,    76,    74,    75,     8,
      77,   475,   469,    78,    79,   470,    74,    75,     8,   471,
     472,   473,    24,   384,   476,   477,    47,    76,   478,   144,
     343,    77,   386,   297,    78,    79,    76,    74,    75,     8,
      77,   336,   468,    78,    79,   240,    74,    75,     8,   466,
     458,   444,   185,   388,   459,   353,   186,    76,   355,     0,
       0,    77,   390,     0,    78,    79,    76,     0,     8,     0,
      77,     0,     0,    78,    79,   242,   243,   244,   245,   246,
     247,     0,     0,     0,   248,     0,   136,   242,   243,   244,
     245,   246,   247,     0,     0,     0,   248,     0,   136,   344,
     345,   346,   347,   348,   349,     0,     0,     0,   350
};

static const short int yycheck[] =
{
       1,     2,   181,   181,   181,   149,   181,   145,   106,   145,
      18,    15,    13,    14,    15,    16,   145,    18,    27,    20,
      24,     0,   114,    24,    25,    33,    27,    22,    29,    37,
     145,    32,    33,    34,   203,    22,    37,    38,   203,    48,
      41,    39,    51,   181,    42,   181,    47,    48,    49,    44,
      51,    52,   150,    61,    55,    36,   145,   358,   359,    25,
      61,    62,    63,    46,    65,   157,   181,   203,    39,   161,
      71,   209,    43,   209,   203,    36,    77,    60,   222,   223,
     209,    47,   261,   261,   261,    15,   261,    96,   203,   181,
     406,   407,   181,    76,   209,    96,    97,    98,    15,   100,
     392,   393,    38,    24,    25,   106,    36,    29,   109,    38,
     114,    38,   281,   114,   203,   116,   281,   404,   405,    36,
     209,    15,    20,   261,   425,   261,    47,    49,    23,    24,
      52,    24,    25,    55,    27,   451,    34,   138,    78,    79,
      38,   145,    36,    41,   145,   281,   261,    15,   440,   150,
      45,    46,   281,   136,    47,    48,   157,   161,    51,   303,
     161,    20,    21,   450,    62,    63,   281,    65,    36,   261,
      20,    21,   261,    15,    16,    97,    98,   181,   100,     7,
     181,    22,    41,   184,    38,    16,     3,     4,    47,    48,
      32,    38,   281,   133,   134,   135,    36,    47,    48,   203,
      41,    32,   203,    96,    38,   209,   207,    22,   209,    22,
      22,   109,    20,    21,    22,    22,   138,     7,     8,   220,
      15,    16,    37,    18,    37,    37,    22,    38,   229,   230,
      37,    22,    40,    41,   235,    22,    44,    32,    33,    47,
      48,    37,    37,    22,    22,    38,    37,    39,   231,     7,
      37,   234,    22,    25,    26,   238,   257,   261,    37,    37,
     261,   244,   245,   246,   247,   248,    61,    37,   251,   252,
     253,   254,   255,    22,     5,     6,     7,   281,     4,    40,
     281,     7,     8,   127,   128,   129,   130,    22,    37,    20,
      21,    22,    28,   276,    20,    21,    22,   395,    12,    13,
      14,    15,    37,    17,    18,    22,    20,    21,    22,    40,
      40,   294,   295,    44,    40,    27,    47,    48,    44,    41,
      37,    47,    48,    37,    52,    39,    40,    22,    47,    48,
      44,    22,     4,    47,    48,     7,     8,     6,     7,   322,
      36,   324,    37,   326,   442,   328,    37,   330,    41,    42,
     333,   334,    20,    21,    22,   338,   339,    20,    21,    22,
      22,    39,    40,   346,   347,   348,   349,   350,    36,    20,
      21,    22,    40,    36,    39,    37,    44,    40,    36,    47,
      48,    44,    20,    21,    47,    48,    20,    21,    22,    40,
      49,    50,    51,    44,   395,    36,    47,    48,    44,   382,
      44,   384,    36,   386,    40,   388,    40,   390,    41,    42,
      44,    41,    42,    47,    48,    39,   399,   400,   401,   402,
     403,    29,    30,    31,    32,    33,    34,    39,    40,    39,
      38,     9,    10,    11,    12,    13,    14,    15,    40,    17,
      18,   442,    20,    21,    22,     5,     6,     7,    39,    40,
     125,   126,   435,   436,   437,   438,   439,   131,   132,    37,
      40,    39,    40,    39,    41,    40,    44,    40,    39,    47,
      48,     9,    10,    11,    12,    13,    14,    15,    39,    17,
      18,    39,    20,    21,    22,     9,    10,    11,    12,    13,
      14,    15,    39,    17,    39,    39,    20,    21,    22,    37,
      39,    39,    40,    39,    41,    40,    44,    40,    40,    47,
      48,    40,    39,    37,    39,    39,    40,    39,    41,    39,
      44,    39,    39,    47,    48,     9,    10,    11,    12,    13,
      14,    15,    39,    17,    39,    39,    20,    21,    22,    39,
      12,    13,    14,    15,    39,    39,    18,    19,    20,    21,
      22,    41,    39,    37,    39,    39,    40,    16,    41,    41,
      44,    39,    42,    47,    48,    37,    42,    39,    40,    42,
       4,    42,    44,    42,    41,    47,    48,    12,    13,    14,
      15,    41,    17,    18,    41,    20,    21,    22,    41,    12,
      13,    14,    15,    39,    39,    18,    19,    20,    21,    22,
      39,    39,    37,    39,    39,    40,    20,    21,    22,    44,
      39,    42,    47,    48,    37,    42,    39,    40,    42,    16,
      42,    44,    36,    42,    47,    48,    40,    20,    21,    22,
      44,    37,    37,    47,    48,    37,    20,    21,    22,    37,
      16,    37,    16,    36,    39,    39,    15,    40,    39,    39,
      39,    44,    36,    39,    47,    48,    40,    20,    21,    22,
      44,    39,    37,    47,    48,    37,    20,    21,    22,    37,
      37,    37,    14,    36,    39,    39,    24,    40,    39,   107,
     281,    44,    36,   209,    47,    48,    40,    20,    21,    22,
      44,   261,   451,    47,    48,   161,    20,    21,    22,   450,
     440,   425,   123,    36,   442,   298,   124,    40,   303,    -1,
      -1,    44,    36,    -1,    47,    48,    40,    -1,    22,    -1,
      44,    -1,    -1,    47,    48,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    38,    -1,    40,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    38,    -1,    40,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,    54,    55,    56,    57,    58,    22,   122,
     122,     0,    56,    36,    36,    59,    62,    63,    69,    70,
      73,    74,    92,   122,    59,    60,    61,    65,    66,    71,
      72,   122,    62,    69,    73,    92,    63,    69,    73,   122,
      70,    73,   122,    37,    74,   122,    38,    60,    65,    71,
      61,    65,    71,   122,    66,    71,   122,    37,    72,   122,
      38,    69,    73,    73,    37,    73,    37,    38,    37,    38,
      38,     4,     7,     8,    20,    21,    40,    44,    47,    48,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     122,   123,   124,   126,   127,   128,    65,    71,    71,    37,
      71,    37,    38,    37,    38,    38,     5,     6,     7,    73,
      37,    37,    37,   122,    36,    78,    40,    67,   110,   122,
     117,   117,    39,    28,    27,    25,    26,    23,    24,    45,
      46,    47,    48,    49,    50,    51,    40,   120,    71,    37,
      37,    37,   119,   122,    67,    36,    77,    37,    39,    40,
       9,    10,    11,    12,    13,    14,    15,    17,    18,    37,
      39,    82,    86,    87,    91,    92,    93,    94,    99,   100,
     101,   102,   103,   108,   109,   110,   122,   124,    41,    68,
     122,    36,    76,    41,    52,   112,   113,   114,   114,   115,
     115,   115,   115,   116,   116,   117,   117,   117,    41,   110,
     121,    37,    39,    36,    75,    12,    15,    17,    37,    81,
      85,    87,    90,    92,    93,    98,   100,   101,   103,   104,
     122,    41,    47,    48,    64,   125,   126,   119,   122,    44,
      44,    40,    39,    39,    40,    44,   122,   124,    40,    37,
      86,    39,    29,    30,    31,    32,    33,    34,    38,    29,
      30,    31,    32,    33,    34,    38,    41,    42,    12,    15,
      37,    80,    84,    87,    89,    92,    93,    94,    97,   100,
     101,   102,   108,   109,   122,    41,    42,    12,    15,    19,
      37,    79,    83,    87,    88,    92,    93,    95,    96,   100,
     103,   104,   107,   123,    40,    40,    37,    85,   122,    39,
     126,   126,    41,    42,    39,    39,   122,   122,   110,   110,
     122,    39,    39,   110,    39,    39,   110,   110,   110,   110,
      39,    39,    36,   110,    36,   110,    36,   110,    36,   110,
      36,   110,   122,    40,    40,    37,    84,   110,    40,    40,
      39,    40,    37,    83,    29,    30,    31,    32,    33,    34,
      38,   110,   110,   120,    39,   125,    39,    39,    41,    41,
      41,    39,    39,    39,    39,   110,    39,   110,    39,   110,
      39,   110,    39,   110,    39,   110,   110,   110,   110,    41,
      39,    39,    36,   110,    36,   110,    36,   110,    36,   110,
      36,   110,    41,    41,    39,    43,    78,    78,    39,    42,
      42,    42,    42,    42,    41,    41,    41,    41,    39,   110,
      39,   110,    39,   110,    39,   110,    39,   110,    39,    77,
      77,   105,   106,   119,   122,    16,   110,   110,   110,   110,
     110,    76,    76,    75,    75,    42,    42,    42,    42,    42,
      16,    39,    42,    78,    91,    37,    37,    37,    37,    37,
      16,    16,   110,   110,   110,   110,   110,    77,    90,   106,
      39,    39,    39,    39,    39,    76,    89,    75,    88,    37,
      37,    37,    37,    37,    39,    39,    39,    39,    39
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
#line 163 "BulletParser.y"
    {
			AST->getRootNode()->setChild(0, (yyvsp[0]));
		;}
    break;

  case 3:
#line 170 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 4:
#line 174 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DefinitionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 5:
#line 183 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 6:
#line 187 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 7:
#line 194 "BulletParser.y"
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
#line 205 "BulletParser.y"
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
#line 216 "BulletParser.y"
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
#line 227 "BulletParser.y"
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
#line 238 "BulletParser.y"
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
#line 249 "BulletParser.y"
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
#line 260 "BulletParser.y"
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
#line 271 "BulletParser.y"
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
#line 285 "BulletParser.y"
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
#line 296 "BulletParser.y"
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
#line 307 "BulletParser.y"
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
#line 318 "BulletParser.y"
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
#line 329 "BulletParser.y"
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
#line 340 "BulletParser.y"
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
#line 351 "BulletParser.y"
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
#line 362 "BulletParser.y"
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
#line 376 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 24:
#line 380 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 25:
#line 389 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 26:
#line 393 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDeclList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 27:
#line 402 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AffectorDecl, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 28:
#line 411 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 29:
#line 415 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 30:
#line 424 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 31:
#line 430 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-6]));
			(yyval)->setChild(1, (yyvsp[-3]));
		;}
    break;

  case 32:
#line 436 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Emitter, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 33:
#line 446 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 34:
#line 450 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 35:
#line 459 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 36:
#line 463 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 37:
#line 472 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Function, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 38:
#line 482 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 39:
#line 486 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 40:
#line 493 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 41:
#line 498 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 42:
#line 510 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 43:
#line 514 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EventList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 44:
#line 523 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Event, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-1]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 45:
#line 534 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 46:
#line 538 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 47:
#line 547 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 48:
#line 556 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 49:
#line 560 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StateList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 50:
#line 569 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_State, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 51:
#line 578 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 52:
#line 582 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 53:
#line 589 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 54:
#line 593 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 55:
#line 600 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 56:
#line 604 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 57:
#line 611 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 58:
#line 615 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 59:
#line 622 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 60:
#line 626 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 61:
#line 635 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 62:
#line 639 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 63:
#line 648 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 64:
#line 652 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
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
			(yyval) = AST->createNode(PT_StatementList, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 67:
#line 674 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 68:
#line 678 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 69:
#line 682 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 70:
#line 686 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 71:
#line 690 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 72:
#line 694 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 73:
#line 698 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 74:
#line 702 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 75:
#line 706 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 76:
#line 710 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 77:
#line 717 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 78:
#line 721 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 79:
#line 725 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 80:
#line 729 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 81:
#line 733 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 82:
#line 737 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 83:
#line 741 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 84:
#line 745 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 85:
#line 749 "BulletParser.y"
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
#line 764 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 89:
#line 768 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 90:
#line 772 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 91:
#line 776 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 92:
#line 780 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 93:
#line 784 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 94:
#line 788 "BulletParser.y"
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
#line 803 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 98:
#line 807 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 99:
#line 811 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 100:
#line 815 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 101:
#line 819 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 102:
#line 823 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 103:
#line 827 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 104:
#line 831 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 105:
#line 835 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 106:
#line 839 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 107:
#line 843 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 108:
#line 847 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 109:
#line 854 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 110:
#line 858 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 111:
#line 865 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 112:
#line 871 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 113:
#line 878 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 114:
#line 888 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 115:
#line 894 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 116:
#line 901 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 117:
#line 911 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 118:
#line 917 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 119:
#line 924 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 120:
#line 934 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 121:
#line 940 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 122:
#line 947 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_IfStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-4]));
			(yyval)->setChild(1, (yyvsp[-2]));
			(yyval)->setChild(2, (yyvsp[0]));
		;}
    break;

  case 123:
#line 957 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 124:
#line 966 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 125:
#line 971 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_inc_expr(-1, PT_Identifier, (yyval), (yyvsp[-2]));
		;}
    break;

  case 126:
#line 976 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 127:
#line 981 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 128:
#line 986 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 129:
#line 991 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Identifier, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 130:
#line 999 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 131:
#line 1005 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 132:
#line 1012 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 133:
#line 1017 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_inc_expr(-1, PT_EmitterMember, (yyval), (yyvsp[-2]));
		;}
    break;

  case 134:
#line 1022 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 135:
#line 1027 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 136:
#line 1032 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 137:
#line 1037 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 138:
#line 1042 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 139:
#line 1048 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 140:
#line 1054 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 141:
#line 1060 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MemberAssignStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_EmitterMember, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 142:
#line 1069 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 143:
#line 1075 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-7]));
			(yyval)->setChild(1, (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 144:
#line 1082 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 145:
#line 1087 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_inc_expr(-1, PT_Property, (yyval), (yyvsp[-2]));
		;}
    break;

  case 146:
#line 1092 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 147:
#line 1097 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 148:
#line 1102 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 149:
#line 1107 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-3]), (yyvsp[-1]));
		;}
    break;

  case 150:
#line 1112 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_AddStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 151:
#line 1118 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_SubtractStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 152:
#line 1124 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_MultiplyStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 153:
#line 1130 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SetStatement, yylineno);
			generate_assignment_expr(PT_DivideStatement, PT_Property, (yyval), (yyvsp[-7]), (yyvsp[-4]));
			(yyval)->setChild(2, (yyvsp[-2]));
		;}
    break;

  case 154:
#line 1139 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 155:
#line 1148 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 156:
#line 1157 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 157:
#line 1166 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WhileStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 158:
#line 1175 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_BreakStatement, yylineno);
		;}
    break;

  case 159:
#line 1179 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ContinueStatement, yylineno);
		;}
    break;

  case 160:
#line 1186 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 161:
#line 1194 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GotoStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 162:
#line 1202 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_WaitStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
		;}
    break;

  case 163:
#line 1210 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-4])->getStringData().c_str());
			delete (yyvsp[-4]);
			
			(yyval)->setChild(0, (yyvsp[-5]));
			(yyval)->setChild(1, (yyvsp[-3]));
			(yyval)->setChild(3, (yyvsp[-1]));
		;}
    break;

  case 164:
#line 1220 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitStatement, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[-3]));
			(yyval)->setChild(1, (yyvsp[-1]));
		;}
    break;

  case 165:
#line 1232 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 166:
#line 1236 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ControllerList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 167:
#line 1245 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 168:
#line 1249 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
			(yyval)->_setType(PT_AffectorCall);
		;}
    break;

  case 169:
#line 1257 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 170:
#line 1261 "BulletParser.y"
    {	
			(yyval) = AST->createNode(PT_DieStatement, yylineno);
		;}
    break;

  case 171:
#line 1268 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 172:
#line 1273 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RaiseStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 173:
#line 1281 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("enable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 174:
#line 1287 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EnableStatement, yylineno);
			(yyval)->setString("disable");
			(yyval)->setChild(0, (yyvsp[-1]));
		;}
    break;

  case 175:
#line 1296 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_ConstantExpression, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 176:
#line 1304 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 177:
#line 1308 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalOr, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 178:
#line 1317 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 179:
#line 1321 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LogicalAnd, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 180:
#line 1330 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 181:
#line 1334 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 182:
#line 1340 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_NotEqualsStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 183:
#line 1349 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 184:
#line 1353 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 185:
#line 1359 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 186:
#line 1365 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_LessThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 187:
#line 1371 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_GreaterThanEqStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 188:
#line 1380 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 189:
#line 1384 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_AddStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 190:
#line 1390 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_SubtractStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 191:
#line 1399 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 192:
#line 1403 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_MultiplyStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 193:
#line 1409 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_DivideStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 194:
#line 1415 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_RemainderStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 195:
#line 1424 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 196:
#line 1428 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryPosStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 197:
#line 1433 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_UnaryNegStatement, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 198:
#line 1441 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 199:
#line 1445 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 200:
#line 1449 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 201:
#line 1453 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 202:
#line 1457 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 203:
#line 1461 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 204:
#line 1468 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCall, yylineno);
			(yyval)->setChild(0, (yyvsp[-1]));
			(yyval)->setChild(1, (yyvsp[0]));
		;}
    break;

  case 205:
#line 1477 "BulletParser.y"
    {
			(yyval) = 0;
		;}
    break;

  case 206:
#line 1481 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 207:
#line 1488 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArg, yylineno);
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 208:
#line 1493 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_FunctionCallArgList, yylineno);
			(yyval)->setChild(0, (yyvsp[-2]));
			
			YYSTYPE argNode = AST->createNode(PT_FunctionCallArg, yylineno);
			argNode->setChild (0, (yyvsp[0]));
			(yyval)->setChild(1, argNode);
		;}
    break;

  case 209:
#line 1505 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Identifier, yylineno);
			(yyval)->setString(yytext);
		;}
    break;

  case 210:
#line 1513 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Property, yylineno);
			(yyval)->setString((yyvsp[0])->getStringData().c_str());
			delete (yyvsp[0]);
		;}
    break;

  case 211:
#line 1522 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_EmitterMember, yylineno);
			(yyval)->setString((yyvsp[-2])->getStringData().c_str());
			delete (yyvsp[-2]);
			
			(yyval)->setChild(0, (yyvsp[0]));
		;}
    break;

  case 212:
#line 1533 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 213:
#line 1537 "BulletParser.y"
    {
			(yyval) = (yyvsp[-1]);
		;}
    break;

  case 214:
#line 1541 "BulletParser.y"
    {
			(yyvsp[0])->setValue(-((yyvsp[0])->getValueData()));
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 215:
#line 1549 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 216:
#line 1553 "BulletParser.y"
    {
			(yyval) = (yyvsp[0]);
		;}
    break;

  case 217:
#line 1560 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;

  case 218:
#line 1568 "BulletParser.y"
    {
			(yyval) = AST->createNode(PT_Constant, yylineno);
			(yyval)->setValue(atof(yytext));
		;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 3623 "bsBulletParser.cpp"

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


#line 1574 "BulletParser.y"


	
	

