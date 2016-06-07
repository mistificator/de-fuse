/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 27 "debugger/commandy.y"


#include <config.h>

#include <stdio.h>		/* Needed by NetBSD yacc */
#include <stdlib.h>
#include <string.h>

#include "debugger/debugger.h"
#include "debugger/debugger_internals.h"
#include "mempool.h"
#include "ui/ui.h"
#include "z80/z80.h"
#include "z80/z80_macros.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE


/* Line 371 of yacc.c  */
#line 88 "debugger/commandy.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_DEBUGGER_COMMANDY_H_INCLUDED
# define YY_YY_DEBUGGER_COMMANDY_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LOGICAL_OR = 258,
     LOGICAL_AND = 259,
     COMPARISON = 260,
     EQUALITY = 261,
     NEGATE = 262,
     BASE = 263,
     BREAK = 264,
     TBREAK = 265,
     CLEAR = 266,
     COMMANDS = 267,
     CONDITION = 268,
     CONTINUE = 269,
     DEBUGGER_DELETE = 270,
     DISASSEMBLE = 271,
     DEBUGGER_END = 272,
     EVENT = 273,
     EXIT = 274,
     FINISH = 275,
     IF = 276,
     DEBUGGER_IGNORE = 277,
     NEXT = 278,
     DEBUGGER_OUT = 279,
     PORT = 280,
     DEBUGGER_PRINT = 281,
     READ = 282,
     SET = 283,
     STEP = 284,
     TIME = 285,
     WRITE = 286,
     DEBUGGER_REGISTER = 287,
     NUMBER = 288,
     STRING = 289,
     VARIABLE = 290,
     DEBUGGER_ERROR = 291
   };
#endif
/* Tokens.  */
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
#define DEBUGGER_REGISTER 287
#define NUMBER 288
#define STRING 289
#define VARIABLE 290
#define DEBUGGER_ERROR 291



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 47 "debugger/commandy.y"


  int token;
  int reg;

  libspectrum_dword integer;
  char *string;

  debugger_breakpoint_type bptype;
  debugger_breakpoint_life bplife;
  struct { libspectrum_word mask, value; } port;
  struct { int source; int page; int offset; } location;

  debugger_expression* exp;



/* Line 387 of yacc.c  */
#line 221 "debugger/commandy.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_DEBUGGER_COMMANDY_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 249 "debugger/commandy.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  44
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,     2,
      46,    47,    42,    40,     2,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    37,     2,     2,     2,     2,     2,
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
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    12,    15,    20,    26,
      31,    38,    45,    48,    54,    58,    60,    62,    65,    68,
      70,    72,    76,    78,    82,    85,    89,    93,    97,    99,
     101,   103,   104,   106,   108,   110,   114,   116,   122,   124,
     126,   127,   130,   131,   133,   134,   136,   138,   140,   142,
     144,   148,   152,   155,   158,   161,   165,   169,   173,   177,
     181,   185,   189,   193,   197,   201,   205,   207,   210
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    -1,    52,    -1,     1,    -1,    51,    44,
      52,    -1,     8,    61,    -1,    53,    54,    56,    58,    -1,
      53,    25,    57,    55,    58,    -1,    53,    30,    61,    58,
      -1,    53,    18,    34,    45,    34,    58,    -1,    53,    18,
      34,    45,    42,    58,    -1,    11,    59,    -1,    12,    61,
      44,    63,    17,    -1,    13,    33,    60,    -1,    14,    -1,
      15,    -1,    15,    61,    -1,    16,    61,    -1,    19,    -1,
      20,    -1,    22,    33,    61,    -1,    23,    -1,    24,    61,
      33,    -1,    26,    61,    -1,    28,    33,    61,    -1,    28,
      32,    61,    -1,    28,    35,    61,    -1,    29,    -1,     9,
      -1,    10,    -1,    -1,    27,    -1,    31,    -1,    61,    -1,
      61,    45,    61,    -1,    59,    -1,    34,    45,    61,    45,
      61,    -1,    27,    -1,    31,    -1,    -1,    21,    62,    -1,
      -1,    61,    -1,    -1,    62,    -1,    62,    -1,    33,    -1,
      32,    -1,    35,    -1,    46,    62,    47,    -1,    48,    62,
      49,    -1,    40,    62,    -1,    41,    62,    -1,     7,    62,
      -1,    62,    40,    62,    -1,    62,    41,    62,    -1,    62,
      42,    62,    -1,    62,    43,    62,    -1,    62,     6,    62,
      -1,    62,     5,    62,    -1,    62,    39,    62,    -1,    62,
      38,    62,    -1,    62,    37,    62,    -1,    62,     4,    62,
      -1,    62,     3,    62,    -1,    64,    -1,    63,    64,    -1,
      34,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   148,   149,   150,   153,   154,   158,   163,
     167,   171,   175,   176,   177,   180,   181,   182,   183,   184,
     185,   186,   189,   190,   191,   192,   193,   194,   195,   198,
     199,   202,   203,   204,   207,   208,   211,   212,   224,   225,
     228,   229,   232,   233,   236,   237,   240,   243,   246,   249,
     252,   253,   257,   258,   262,   266,   270,   274,   278,   282,
     286,   290,   294,   298,   302,   308,   316,   317,   322
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOGICAL_OR", "LOGICAL_AND",
  "COMPARISON", "EQUALITY", "NEGATE", "BASE", "BREAK", "TBREAK", "CLEAR",
  "COMMANDS", "CONDITION", "CONTINUE", "DEBUGGER_DELETE", "DISASSEMBLE",
  "DEBUGGER_END", "EVENT", "EXIT", "FINISH", "IF", "DEBUGGER_IGNORE",
  "NEXT", "DEBUGGER_OUT", "PORT", "DEBUGGER_PRINT", "READ", "SET", "STEP",
  "TIME", "WRITE", "DEBUGGER_REGISTER", "NUMBER", "STRING", "VARIABLE",
  "DEBUGGER_ERROR", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'",
  "'\\n'", "':'", "'('", "')'", "'['", "']'", "$accept", "input",
  "command", "breakpointlife", "breakpointtype", "breakpointport",
  "breakpointlocation", "portbreakpointtype", "optionalcondition",
  "numberorpc", "expressionornull", "number", "expression",
  "debuggercommands", "debuggercommand", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   124,    94,    38,
      43,    45,    42,    47,    10,    58,    40,    41,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    53,
      53,    54,    54,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     3,     2,     4,     5,     4,
       6,     6,     2,     5,     3,     1,     1,     2,     2,     1,
       1,     3,     1,     3,     2,     3,     3,     3,     1,     1,
       1,     0,     1,     1,     1,     3,     1,     5,     1,     1,
       0,     2,     0,     1,     0,     1,     1,     1,     1,     1,
       3,     3,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,    29,    30,    42,     0,     0,    15,    16,
       0,    19,    20,     0,    22,     0,     0,     0,    28,     0,
       3,    31,     0,    48,    47,    49,     0,     0,     0,     0,
       6,    46,    12,    43,     0,    44,    17,    18,     0,     0,
      24,     0,     0,     0,     1,     0,     0,     0,    32,     0,
      33,    42,    54,    52,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      45,    21,    23,    26,    25,    27,     5,     0,    38,    39,
       0,    40,     0,    40,    36,    50,    51,    65,    64,    60,
      59,    63,    62,    61,    55,    56,    57,    58,     0,     0,
      66,     0,    40,    34,     0,     9,     0,     7,    68,    13,
      67,    40,    40,     8,     0,    41,     0,    10,    11,    35,
       0,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    19,    20,    21,    51,   102,    83,    80,   105,    32,
      69,    33,    31,    99,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -79
static const yytype_int16 yypact[] =
{
      72,   -79,    82,   -79,   -79,    82,    82,   -30,   -79,    82,
      82,   -79,   -79,   -24,   -79,    82,    82,    11,   -79,     1,
     -79,   199,    82,   -79,   -79,   -79,    82,    82,    82,    82,
     -79,   130,   -79,   -79,   -33,    82,   -79,   -79,    82,    -8,
     -79,    82,    82,    82,   -79,   230,     3,   -15,   -79,    82,
     -79,   118,   -79,   -79,   -79,   102,    26,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,     4,   -79,
     130,   -79,   -79,   -79,   -79,   -79,   -79,   -19,   -79,   -79,
      82,     6,   -10,     6,   -79,   -79,   -79,   142,   149,   161,
     173,   155,   169,   194,   -25,   -25,   -79,   -79,     5,   -11,
     -79,   -32,     6,    -3,    82,   -79,    82,   -79,   -79,   -79,
     -79,     6,     6,   -79,    82,   130,    16,   -79,   -79,   -79,
      82,   -79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,   -79,    17,   -79,   -79,   -79,   -79,   -79,   -78,    19,
     -79,    -2,    -7,   -79,   -51
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int8 yytable[] =
{
      30,    44,   111,    35,    34,   107,   109,    36,    37,    38,
     112,    68,    78,    39,    40,    52,    79,    66,    67,    53,
      54,    55,    56,    98,   113,    72,   101,   104,    70,    57,
      58,    59,    60,   117,   118,   106,    71,    77,    98,    73,
      74,    75,   114,    41,    42,    45,    43,    81,   110,   108,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   120,    76,    61,    62,    63,    64,    65,    66,    67,
      84,     0,    -2,     1,     0,    86,     0,     0,   103,     0,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    22,
       0,    11,    12,     0,    13,    14,    15,   115,    16,     0,
      17,    18,     0,     0,   116,    57,    58,    59,    60,     0,
       0,     0,   119,     0,    23,    24,    -2,    25,   121,     0,
       0,     0,    26,    27,     0,    22,     0,     0,    28,     0,
      29,     0,     0,    57,    58,    59,    60,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    58,    59,    60,    85,
      23,    24,    82,    25,    59,    60,     0,     0,    26,    27,
      59,    60,     0,     0,    28,     0,    29,    61,    62,    63,
      64,    65,    66,    67,    59,    60,     0,     0,    59,    61,
      62,    63,    64,    65,    66,    67,    61,    62,    63,    64,
      65,    66,    67,    62,    63,    64,    65,    66,    67,    59,
      60,    64,    65,    66,    67,     0,     0,     0,    63,    64,
      65,    66,    67,    64,    65,    66,    67,    46,     0,     0,
       0,     0,     0,     0,    47,     0,    48,     0,     0,    49,
      50,     0,     0,     0,    64,    65,    66,    67,     2,     3,
       4,     5,     6,     7,     8,     9,    10,     0,     0,    11,
      12,     0,    13,    14,    15,     0,    16,     0,    17,    18
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       2,     0,    34,    33,     6,    83,    17,     9,    10,    33,
      42,    44,    27,    15,    16,    22,    31,    42,    43,    26,
      27,    28,    29,    34,   102,    33,    45,    21,    35,     3,
       4,     5,     6,   111,   112,    45,    38,    34,    34,    41,
      42,    43,    45,    32,    33,    44,    35,    49,    99,    44,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    45,    45,    37,    38,    39,    40,    41,    42,    43,
      51,    -1,     0,     1,    -1,    49,    -1,    -1,    80,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,     7,
      -1,    19,    20,    -1,    22,    23,    24,   104,    26,    -1,
      28,    29,    -1,    -1,   106,     3,     4,     5,     6,    -1,
      -1,    -1,   114,    -1,    32,    33,    44,    35,   120,    -1,
      -1,    -1,    40,    41,    -1,     7,    -1,    -1,    46,    -1,
      48,    -1,    -1,     3,     4,     5,     6,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,     4,     5,     6,    47,
      32,    33,    34,    35,     5,     6,    -1,    -1,    40,    41,
       5,     6,    -1,    -1,    46,    -1,    48,    37,    38,    39,
      40,    41,    42,    43,     5,     6,    -1,    -1,     5,    37,
      38,    39,    40,    41,    42,    43,    37,    38,    39,    40,
      41,    42,    43,    38,    39,    40,    41,    42,    43,     5,
       6,    40,    41,    42,    43,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    40,    41,    42,    43,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    30,
      31,    -1,    -1,    -1,    40,    41,    42,    43,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    22,    23,    24,    -1,    26,    -1,    28,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    19,    20,    22,    23,    24,    26,    28,    29,    51,
      52,    53,     7,    32,    33,    35,    40,    41,    46,    48,
      61,    62,    59,    61,    61,    33,    61,    61,    33,    61,
      61,    32,    33,    35,     0,    44,    18,    25,    27,    30,
      31,    54,    62,    62,    62,    62,    62,     3,     4,     5,
       6,    37,    38,    39,    40,    41,    42,    43,    44,    60,
      62,    61,    33,    61,    61,    61,    52,    34,    27,    31,
      57,    61,    34,    56,    59,    47,    49,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    34,    63,
      64,    45,    55,    61,    21,    58,    45,    58,    44,    17,
      64,    34,    42,    58,    45,    62,    61,    58,    58,    61,
      45,    61
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
      YYSIZE_T yyn = 0;
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

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
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 6:
/* Line 1792 of yacc.c  */
#line 153 "debugger/commandy.y"
    { debugger_output_base = (yyvsp[(2) - (2)].integer); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 154 "debugger/commandy.y"
    {
             debugger_breakpoint_add_address( (yyvsp[(2) - (4)].bptype), (yyvsp[(3) - (4)].location).source, (yyvsp[(3) - (4)].location).page, (yyvsp[(3) - (4)].location).offset,
                                              0, (yyvsp[(1) - (4)].bplife), (yyvsp[(4) - (4)].exp) );
	   }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 158 "debugger/commandy.y"
    {
	     int mask = (yyvsp[(4) - (5)].port).mask;
	     if( mask == 0 ) mask = ( (yyvsp[(4) - (5)].port).value < 0x100 ? 0x00ff : 0xffff );
	     debugger_breakpoint_add_port( (yyvsp[(3) - (5)].bptype), (yyvsp[(4) - (5)].port).value, mask, 0, (yyvsp[(1) - (5)].bplife), (yyvsp[(5) - (5)].exp) );
           }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 163 "debugger/commandy.y"
    {
	     debugger_breakpoint_add_time( DEBUGGER_BREAKPOINT_TYPE_TIME,
					   (yyvsp[(3) - (4)].integer), 0, (yyvsp[(1) - (4)].bplife), (yyvsp[(4) - (4)].exp) );
	   }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 167 "debugger/commandy.y"
    {
	     debugger_breakpoint_add_event( DEBUGGER_BREAKPOINT_TYPE_EVENT,
					    (yyvsp[(3) - (6)].string), (yyvsp[(5) - (6)].string), 0, (yyvsp[(1) - (6)].bplife), (yyvsp[(6) - (6)].exp) );
	   }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 171 "debugger/commandy.y"
    {
	     debugger_breakpoint_add_event( DEBUGGER_BREAKPOINT_TYPE_EVENT,
					    (yyvsp[(3) - (6)].string), "*", 0, (yyvsp[(1) - (6)].bplife), (yyvsp[(6) - (6)].exp) );
	   }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 175 "debugger/commandy.y"
    { debugger_breakpoint_clear( (yyvsp[(2) - (2)].integer) ); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 176 "debugger/commandy.y"
    { debugger_breakpoint_set_commands( (yyvsp[(2) - (5)].integer), (yyvsp[(4) - (5)].string) ); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 177 "debugger/commandy.y"
    {
	     debugger_breakpoint_set_condition( (yyvsp[(2) - (3)].integer), (yyvsp[(3) - (3)].exp) );
           }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 180 "debugger/commandy.y"
    { debugger_run(); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 181 "debugger/commandy.y"
    { debugger_breakpoint_remove_all(); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 182 "debugger/commandy.y"
    { debugger_breakpoint_remove( (yyvsp[(2) - (2)].integer) ); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 183 "debugger/commandy.y"
    { ui_debugger_disassemble( (yyvsp[(2) - (2)].integer) ); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 184 "debugger/commandy.y"
    { debugger_exit_emulator(); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 185 "debugger/commandy.y"
    { debugger_breakpoint_exit(); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 186 "debugger/commandy.y"
    {
	     debugger_breakpoint_ignore( (yyvsp[(2) - (3)].integer), (yyvsp[(3) - (3)].integer) );
	   }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 189 "debugger/commandy.y"
    { debugger_next(); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 190 "debugger/commandy.y"
    { debugger_port_write( (yyvsp[(2) - (3)].integer), (yyvsp[(3) - (3)].integer) ); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 191 "debugger/commandy.y"
    { printf( "0x%x\n", (yyvsp[(2) - (2)].integer) ); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 192 "debugger/commandy.y"
    { debugger_poke( (yyvsp[(2) - (3)].integer), (yyvsp[(3) - (3)].integer) ); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 193 "debugger/commandy.y"
    { debugger_register_set( (yyvsp[(2) - (3)].reg), (yyvsp[(3) - (3)].integer) ); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 194 "debugger/commandy.y"
    { debugger_variable_set( (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].integer) ); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 195 "debugger/commandy.y"
    { debugger_step(); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 198 "debugger/commandy.y"
    { (yyval.bplife) = DEBUGGER_BREAKPOINT_LIFE_PERMANENT; }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 199 "debugger/commandy.y"
    { (yyval.bplife) = DEBUGGER_BREAKPOINT_LIFE_ONESHOT; }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 202 "debugger/commandy.y"
    { (yyval.bptype) = DEBUGGER_BREAKPOINT_TYPE_EXECUTE; }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 203 "debugger/commandy.y"
    { (yyval.bptype) = DEBUGGER_BREAKPOINT_TYPE_READ; }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 204 "debugger/commandy.y"
    { (yyval.bptype) = DEBUGGER_BREAKPOINT_TYPE_WRITE; }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 207 "debugger/commandy.y"
    { (yyval.port).mask = 0; (yyval.port).value = (yyvsp[(1) - (1)].integer); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 208 "debugger/commandy.y"
    { (yyval.port).mask = (yyvsp[(1) - (3)].integer); (yyval.port).value = (yyvsp[(3) - (3)].integer); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 211 "debugger/commandy.y"
    { (yyval.location).source = memory_source_any; (yyval.location).offset = (yyvsp[(1) - (1)].integer); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 212 "debugger/commandy.y"
    {
                        (yyval.location).source = memory_source_find( (yyvsp[(1) - (5)].string) );
                        if( (yyval.location).source == -1 ) {
                          char buffer[80];
                          snprintf( buffer, 80, "unknown memory source \"%s\"", (yyvsp[(1) - (5)].string) );
                          yyerror( buffer );
                          YYERROR;
                        }
                        (yyval.location).page = (yyvsp[(3) - (5)].integer);
                        (yyval.location).offset = (yyvsp[(5) - (5)].integer);
                      }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 224 "debugger/commandy.y"
    { (yyval.bptype) = DEBUGGER_BREAKPOINT_TYPE_PORT_READ; }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 225 "debugger/commandy.y"
    { (yyval.bptype) = DEBUGGER_BREAKPOINT_TYPE_PORT_WRITE; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 228 "debugger/commandy.y"
    { (yyval.exp) = NULL; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 229 "debugger/commandy.y"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 232 "debugger/commandy.y"
    { (yyval.integer) = PC; }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 233 "debugger/commandy.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 236 "debugger/commandy.y"
    { (yyval.exp) = NULL; }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 237 "debugger/commandy.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 240 "debugger/commandy.y"
    { (yyval.integer) = debugger_expression_evaluate( (yyvsp[(1) - (1)].exp) ); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 243 "debugger/commandy.y"
    { (yyval.exp) = debugger_expression_new_number( (yyvsp[(1) - (1)].integer), debugger_memory_pool );
		       if( !(yyval.exp) ) YYABORT;
		     }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 246 "debugger/commandy.y"
    { (yyval.exp) = debugger_expression_new_register( (yyvsp[(1) - (1)].reg), debugger_memory_pool );
			 if( !(yyval.exp) ) YYABORT;
		       }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 249 "debugger/commandy.y"
    { (yyval.exp) = debugger_expression_new_variable( (yyvsp[(1) - (1)].string), debugger_memory_pool );
			 if( !(yyval.exp) ) YYABORT;
		       }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 252 "debugger/commandy.y"
    { (yyval.exp) = (yyvsp[(2) - (3)].exp); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 253 "debugger/commandy.y"
    {
                (yyval.exp) = debugger_expression_new_unaryop( DEBUGGER_TOKEN_DEREFERENCE, (yyvsp[(2) - (3)].exp), debugger_memory_pool );
                if( !(yyval.exp) ) YYABORT;
              }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 257 "debugger/commandy.y"
    { (yyval.exp) = (yyvsp[(2) - (2)].exp); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 258 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_unaryop( '-', (yyvsp[(2) - (2)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 262 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_unaryop( (yyvsp[(1) - (2)].token), (yyvsp[(2) - (2)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 266 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '+', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 270 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '-', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 274 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '*', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 278 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '/', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 282 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( (yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 286 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( (yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 290 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '&', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 294 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '^', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 298 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop( '|', (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 302 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop(
		  DEBUGGER_TOKEN_LOGICAL_AND, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool
                );
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 308 "debugger/commandy.y"
    {
	        (yyval.exp) = debugger_expression_new_binaryop(
		  DEBUGGER_TOKEN_LOGICAL_OR, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), debugger_memory_pool
		);
		if( !(yyval.exp) ) YYABORT;
	      }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 316 "debugger/commandy.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 317 "debugger/commandy.y"
    {
                      (yyval.string) = mempool_new( debugger_memory_pool, char, strlen( (yyvsp[(1) - (2)].string) ) + strlen( (yyvsp[(2) - (2)].string) ) + 2 );
                      sprintf( (yyval.string), "%s\n%s", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string) );
                    }
    break;


/* Line 1792 of yacc.c  */
#line 2032 "debugger/commandy.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 324 "debugger/commandy.y"

