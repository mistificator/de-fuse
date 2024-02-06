/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_DEBUGGER_COMMANDY_H_INCLUDED
# define YY_YY_DEBUGGER_COMMANDY_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LOGICAL_OR = 258,              /* LOGICAL_OR  */
    LOGICAL_AND = 259,             /* LOGICAL_AND  */
    COMPARISON = 260,              /* COMPARISON  */
    EQUALITY = 261,                /* EQUALITY  */
    NEGATE = 262,                  /* NEGATE  */
    BASE = 263,                    /* BASE  */
    BREAK = 264,                   /* BREAK  */
    TBREAK = 265,                  /* TBREAK  */
    CLEAR = 266,                   /* CLEAR  */
    COMMANDS = 267,                /* COMMANDS  */
    CONDITION = 268,               /* CONDITION  */
    CONTINUE = 269,                /* CONTINUE  */
    DEBUGGER_DELETE = 270,         /* DEBUGGER_DELETE  */
    DISASSEMBLE = 271,             /* DISASSEMBLE  */
    DEBUGGER_END = 272,            /* DEBUGGER_END  */
    EVENT = 273,                   /* EVENT  */
    EXIT = 274,                    /* EXIT  */
    FINISH = 275,                  /* FINISH  */
    IF = 276,                      /* IF  */
    DEBUGGER_IGNORE = 277,         /* DEBUGGER_IGNORE  */
    NEXT = 278,                    /* NEXT  */
    DEBUGGER_OUT = 279,            /* DEBUGGER_OUT  */
    PORT = 280,                    /* PORT  */
    DEBUGGER_PRINT = 281,          /* DEBUGGER_PRINT  */
    READ = 282,                    /* READ  */
    SET = 283,                     /* SET  */
    STEP = 284,                    /* STEP  */
    TIME = 285,                    /* TIME  */
    WRITE = 286,                   /* WRITE  */
    NUMBER = 287,                  /* NUMBER  */
    STRING = 288,                  /* STRING  */
    VARIABLE = 289,                /* VARIABLE  */
    DEBUGGER_ERROR = 290           /* DEBUGGER_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LOGICAL_OR 258
#define LOGICAL_AND 259
#define COMPARISON 260
#define EQUALITY 261
#define NEGATE 262
#define BASE 263
#define BREAK 264
#define TBREAK 265
#define CLEAR 266
#define COMMANDS 267
#define CONDITION 268
#define CONTINUE 269
#define DEBUGGER_DELETE 270
#define DISASSEMBLE 271
#define DEBUGGER_END 272
#define EVENT 273
#define EXIT 274
#define FINISH 275
#define IF 276
#define DEBUGGER_IGNORE 277
#define NEXT 278
#define DEBUGGER_OUT 279
#define PORT 280
#define DEBUGGER_PRINT 281
#define READ 282
#define SET 283
#define STEP 284
#define TIME 285
#define WRITE 286
#define NUMBER 287
#define STRING 288
#define VARIABLE 289
#define DEBUGGER_ERROR 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "debugger/commandy.y"


  int token;

  libspectrum_dword integer;
  char *string;

  debugger_breakpoint_type bptype;
  debugger_breakpoint_life bplife;
  struct { libspectrum_word mask, value; } port;
  struct { int source; int page; int offset; } location;

  debugger_expression* exp;


#line 153 "debugger/commandy.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_DEBUGGER_COMMANDY_H_INCLUDED  */
