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
     KEYWORD_BULLET = 258,
     KEYWORD_AREA = 259,
     KEYWORD_SPLINE = 260,
     KEYWORD_REPEAT = 261,
     KEYWORD_IF = 262,
     KEYWORD_ELSE = 263,
     KEYWORD_GOTO = 264,
     KEYWORD_WAIT = 265,
     KEYWORD_SET = 266,
     KEYWORD_AFFECTORS = 267,
     KEYWORD_BASE = 268,
     KEYWORD_CENTRE = 269,
     INTEGER = 270,
     REAL = 271,
     IDENTIFIER = 272,
     SYMBOL_LTE = 273,
     SYMBOL_GTE = 274,
     SYMBOL_EQ = 275,
     SYMBOL_NEQ = 276,
     SYMBOL_LOG_AND = 277,
     SYMBOL_LOG_OR = 278,
     TOKEN_ERROR = 279
   };
#endif
/* Tokens.  */
#define KEYWORD_BULLET 258
#define KEYWORD_AREA 259
#define KEYWORD_SPLINE 260
#define KEYWORD_REPEAT 261
#define KEYWORD_IF 262
#define KEYWORD_ELSE 263
#define KEYWORD_GOTO 264
#define KEYWORD_WAIT 265
#define KEYWORD_SET 266
#define KEYWORD_AFFECTORS 267
#define KEYWORD_BASE 268
#define KEYWORD_CENTRE 269
#define INTEGER 270
#define REAL 271
#define IDENTIFIER 272
#define SYMBOL_LTE 273
#define SYMBOL_GTE 274
#define SYMBOL_EQ 275
#define SYMBOL_NEQ 276
#define SYMBOL_LOG_AND 277
#define SYMBOL_LOG_OR 278
#define TOKEN_ERROR 279




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


