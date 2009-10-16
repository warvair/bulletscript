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
     KEYWORD_UNIT = 258,
     KEYWORD_GUN = 259,
     KEYWORD_ENABLE = 260,
     KEYWORD_DISABLE = 261,
     KEYWORD_EVENT = 262,
     KEYWORD_BULLET = 263,
     KEYWORD_AREA = 264,
     KEYWORD_ARC = 265,
     KEYWORD_SPLINE = 266,
     KEYWORD_LOOP = 267,
     KEYWORD_IF = 268,
     KEYWORD_ELSE = 269,
     KEYWORD_GOTO = 270,
     KEYWORD_WAIT = 271,
     KEYWORD_SET = 272,
     KEYWORD_AFFECTORS = 273,
     KEYWORD_BASE = 274,
     KEYWORD_CENTRE = 275,
     INTEGER = 276,
     REAL = 277,
     IDENTIFIER = 278,
     SYMBOL_LTE = 279,
     SYMBOL_GTE = 280,
     SYMBOL_EQ = 281,
     SYMBOL_NEQ = 282,
     SYMBOL_LOG_AND = 283,
     SYMBOL_LOG_OR = 284,
     TOKEN_ERROR = 285
   };
#endif
/* Tokens.  */
#define KEYWORD_UNIT 258
#define KEYWORD_GUN 259
#define KEYWORD_ENABLE 260
#define KEYWORD_DISABLE 261
#define KEYWORD_EVENT 262
#define KEYWORD_BULLET 263
#define KEYWORD_AREA 264
#define KEYWORD_ARC 265
#define KEYWORD_SPLINE 266
#define KEYWORD_LOOP 267
#define KEYWORD_IF 268
#define KEYWORD_ELSE 269
#define KEYWORD_GOTO 270
#define KEYWORD_WAIT 271
#define KEYWORD_SET 272
#define KEYWORD_AFFECTORS 273
#define KEYWORD_BASE 274
#define KEYWORD_CENTRE 275
#define INTEGER 276
#define REAL 277
#define IDENTIFIER 278
#define SYMBOL_LTE 279
#define SYMBOL_GTE 280
#define SYMBOL_EQ 281
#define SYMBOL_NEQ 282
#define SYMBOL_LOG_AND 283
#define SYMBOL_LOG_OR 284
#define TOKEN_ERROR 285




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



