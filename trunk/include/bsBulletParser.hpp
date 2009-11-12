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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



