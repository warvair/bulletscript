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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



