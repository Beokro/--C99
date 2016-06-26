/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BOOL = 258,
     CHAR = 259,
     INT = 260,
     FLOAT = 261,
     DOUBLE = 262,
     SHORT = 263,
     UNSIGNED = 264,
     SIGNED = 265,
     VOID = 266,
     CONST = 267,
     STRING = 268,
     LONG = 269,
     SWITCH = 270,
     BREAK = 271,
     ENUM = 272,
     CASE = 273,
     CONTINUE = 274,
     GOTO = 275,
     SIZEOF = 276,
     DEFAULT = 277,
     STRUCT = 278,
     INCLUDE = 279,
     DO = 280,
     TYPEDEF = 281,
     IF = 282,
     FOR = 283,
     ELSE = 284,
     WHILE = 285,
     RETURN = 286,
     NULLX = 287,
     TRUE = 288,
     FALSE = 289,
     STRINGV = 290,
     ID = 291,
     CHARV = 292,
     NUMBER = 293,
     ORASSIGN = 294,
     XORASSIGN = 295,
     ANDASSIGN = 296,
     SRASSIGN = 297,
     SLASSIGN = 298,
     REMASSIGN = 299,
     DIVASSIGN = 300,
     TIMESASSIGN = 301,
     MINUSASSIGN = 302,
     ADDASSIGN = 303,
     OR = 304,
     AND = 305,
     NEQ = 306,
     EQ = 307,
     GE = 308,
     LE = 309,
     SL = 310,
     SR = 311,
     MINUSMINUS = 312,
     ADDADD = 313,
     SECOND = 314,
     ARROW = 315,
     FIRST = 316
   };
#endif
/* Tokens.  */
#define BOOL 258
#define CHAR 259
#define INT 260
#define FLOAT 261
#define DOUBLE 262
#define SHORT 263
#define UNSIGNED 264
#define SIGNED 265
#define VOID 266
#define CONST 267
#define STRING 268
#define LONG 269
#define SWITCH 270
#define BREAK 271
#define ENUM 272
#define CASE 273
#define CONTINUE 274
#define GOTO 275
#define SIZEOF 276
#define DEFAULT 277
#define STRUCT 278
#define INCLUDE 279
#define DO 280
#define TYPEDEF 281
#define IF 282
#define FOR 283
#define ELSE 284
#define WHILE 285
#define RETURN 286
#define NULLX 287
#define TRUE 288
#define FALSE 289
#define STRINGV 290
#define ID 291
#define CHARV 292
#define NUMBER 293
#define ORASSIGN 294
#define XORASSIGN 295
#define ANDASSIGN 296
#define SRASSIGN 297
#define SLASSIGN 298
#define REMASSIGN 299
#define DIVASSIGN 300
#define TIMESASSIGN 301
#define MINUSASSIGN 302
#define ADDASSIGN 303
#define OR 304
#define AND 305
#define NEQ 306
#define EQ 307
#define GE 308
#define LE 309
#define SL 310
#define SR 311
#define MINUSMINUS 312
#define ADDADD 313
#define SECOND 314
#define ARROW 315
#define FIRST 316




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

