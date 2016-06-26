/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

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




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp"

    #include <cstdio>
    #include <cstdlib>

    #define YYDEBUG 1

    int yylex(void);
    void yyerror(const char *);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 238 "parser.cpp"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
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
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1306

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNRULES -- Number of states.  */
#define YYNSTATES  286

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    79,     2,     2,    68,    55,     2,
      72,    73,    66,    64,    39,    65,    76,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    82,
      58,    40,    59,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    75,    54,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,    53,    81,     2,     2,     2,     2,
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
      35,    36,    37,    38,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    56,    57,    60,    61,
      62,    63,    69,    70,    71,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    13,    15,    17,
      19,    26,    33,    43,    46,    47,    49,    51,    58,    66,
      70,    71,    74,    75,    82,    90,    95,    96,    99,   100,
     103,   104,   107,   108,   110,   112,   117,   122,   130,   142,
     150,   158,   170,   179,   190,   192,   195,   198,   201,   204,
     206,   208,   210,   212,   217,   218,   222,   226,   230,   234,
     238,   242,   246,   250,   254,   258,   262,   266,   270,   274,
     278,   282,   286,   290,   294,   298,   302,   306,   310,   314,
     318,   322,   326,   330,   334,   336,   339,   341,   345,   349,
     351,   355,   358,   361,   364,   367,   370,   373,   375,   378,
     382,   386,   388,   390,   392,   394,   396,   400,   402,   404,
     406,   408,   410,   412,   414,   416,   419,   422,   425,   427,
     430,   433,   436,   439,   442,   445,   448,   451,   455,   459,
     462,   463,   467,   468,   472,   473,   478
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      86,     0,    -1,    87,    -1,    87,    88,    -1,    -1,    94,
      -1,    97,    -1,    90,    -1,    93,    -1,    89,    -1,    24,
      58,    36,    76,    36,    59,    -1,    24,    79,    36,    76,
      36,    79,    -1,   111,    36,    72,   114,    73,    80,    91,
     105,    81,    -1,    91,    92,    -1,    -1,    90,    -1,   103,
      -1,    23,    36,    80,    96,    81,    82,    -1,    17,    36,
      80,    36,    95,    81,    82,    -1,    39,    36,    95,    -1,
      -1,    96,    97,    -1,    -1,   111,    36,   110,    99,    98,
      82,    -1,    12,   111,    36,   110,    99,    98,    82,    -1,
      39,    36,    99,    98,    -1,    -1,    40,   106,    -1,    -1,
     100,   103,    -1,    -1,   101,   102,    -1,    -1,   103,    -1,
     105,    -1,   108,    40,   106,    82,    -1,   108,    40,    35,
      82,    -1,   108,    40,    36,    72,   112,    73,    82,    -1,
      27,    72,   106,    73,    80,   101,    81,    29,    80,   101,
      81,    -1,    27,    72,   106,    73,    80,   101,    81,    -1,
      30,    72,   106,    73,    80,   100,    81,    -1,    28,    72,
     103,    82,   106,    82,   103,    73,    80,   100,    81,    -1,
      25,    80,   100,    81,    30,    72,   106,    73,    -1,    15,
      72,   106,    73,    80,   104,    22,    83,   100,    81,    -1,
      16,    -1,   107,    70,    -1,   107,    69,    -1,    70,   107,
      -1,    69,   107,    -1,    19,    -1,    93,    -1,    94,    -1,
      97,    -1,   104,    18,    83,   100,    -1,    -1,    31,   106,
      82,    -1,   106,    66,   106,    -1,   106,    67,   106,    -1,
     106,    64,   106,    -1,   106,    65,   106,    -1,   106,    57,
     106,    -1,   106,    60,   106,    -1,   106,    61,   106,    -1,
     106,    56,   106,    -1,   106,    59,   106,    -1,   106,    58,
     106,    -1,   106,    55,   106,    -1,   106,    54,   106,    -1,
     106,    53,   106,    -1,   106,    68,   106,    -1,   106,    52,
     106,    -1,   106,    51,   106,    -1,   106,    63,   106,    -1,
     106,    62,   106,    -1,   106,    43,   106,    -1,   106,    42,
     106,    -1,   106,    41,   106,    -1,   106,    45,   106,    -1,
     106,    44,   106,    -1,   106,    48,   106,    -1,   106,    47,
     106,    -1,   106,    46,   106,    -1,   106,    50,   106,    -1,
     106,    49,   106,    -1,   107,    -1,    36,   110,    -1,    36,
      -1,    36,    76,    36,    -1,    36,    77,    36,    -1,   109,
      -1,    72,   106,    73,    -1,    84,   106,    -1,    66,   106,
      -1,    65,   106,    -1,    64,   106,    -1,    55,   108,    -1,
      36,   110,    -1,    36,    -1,    66,    36,    -1,    36,    77,
      36,    -1,    36,    76,    36,    -1,    38,    -1,    37,    -1,
      33,    -1,    34,    -1,    32,    -1,    74,   106,    75,    -1,
       3,    -1,     5,    -1,     4,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    14,    -1,    14,    14,    -1,    23,
      36,    -1,    17,    36,    -1,    13,    -1,     3,    66,    -1,
       5,    66,    -1,     4,    66,    -1,     8,    66,    -1,     9,
      66,    -1,    10,    66,    -1,    11,    66,    -1,    14,    66,
      -1,    14,    14,    66,    -1,    23,    36,    66,    -1,   106,
     113,    -1,    -1,    39,   106,   113,    -1,    -1,   111,    36,
     115,    -1,    -1,    39,   111,    36,   115,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    33,    33,    36,    37,    40,    41,    42,    43,    44,
      47,    48,    53,    56,    57,    60,    61,    65,    68,    71,
      72,    75,    76,    79,    80,    83,    84,    87,    88,    91,
      92,    94,    95,    98,    99,   102,   104,   106,   108,   110,
     112,   114,   116,   118,   120,   122,   124,   126,   128,   130,
     132,   134,   136,   139,   140,   145,   150,   152,   154,   156,
     158,   160,   162,   164,   166,   168,   170,   172,   174,   176,
     178,   180,   182,   184,   186,   188,   190,   192,   194,   196,
     198,   200,   202,   204,   206,   211,   213,   215,   217,   219,
     221,   223,   225,   227,   229,   231,   235,   237,   239,   241,
     243,   247,   249,   251,   253,   255,   259,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   293,
     295,   299,   301,   306,   308,   313,   315
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "CHAR", "INT", "FLOAT", "DOUBLE",
  "SHORT", "UNSIGNED", "SIGNED", "VOID", "CONST", "STRING", "LONG",
  "SWITCH", "BREAK", "ENUM", "CASE", "CONTINUE", "GOTO", "SIZEOF",
  "DEFAULT", "STRUCT", "INCLUDE", "DO", "TYPEDEF", "IF", "FOR", "ELSE",
  "WHILE", "RETURN", "NULLX", "TRUE", "FALSE", "STRINGV", "ID", "CHARV",
  "NUMBER", "','", "'='", "ORASSIGN", "XORASSIGN", "ANDASSIGN", "SRASSIGN",
  "SLASSIGN", "REMASSIGN", "DIVASSIGN", "TIMESASSIGN", "MINUSASSIGN",
  "ADDASSIGN", "OR", "AND", "'|'", "'^'", "'&'", "NEQ", "EQ", "'<'", "'>'",
  "GE", "LE", "SL", "SR", "'+'", "'-'", "'*'", "'/'", "'%'", "MINUSMINUS",
  "ADDADD", "SECOND", "'('", "')'", "'['", "']'", "'.'", "ARROW", "FIRST",
  "'\"'", "'{'", "'}'", "';'", "':'", "'!'", "$accept", "s", "outermosts",
  "outermost", "include", "procedure", "procedureContents",
  "procedureContent", "structDefine", "enumDefine", "idPrime", "decls",
  "decl", "declFollow", "optionAssign", "stmts", "stmtsCanReturn",
  "stmtCanReturn", "stmt", "cases", "returnStmt", "exprs", "term", "lhs",
  "literal", "sbarket", "type", "arguments", "argumentsPrime", "parameter",
  "parameterPrime", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,    44,
      61,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   124,    94,    38,   306,   307,    60,    62,
     308,   309,   310,   311,    43,    45,    42,    47,    37,   312,
     313,   314,    40,    41,    91,    93,    46,   315,   316,    34,
     123,   125,    59,    58,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    88,    88,    88,
      89,    89,    90,    91,    91,    92,    92,    93,    94,    95,
      95,    96,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   104,   104,   105,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   108,   108,   108,   108,
     108,   109,   109,   109,   109,   109,   110,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   114,   114,   115,   115
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       6,     6,     9,     2,     0,     1,     1,     6,     7,     3,
       0,     2,     0,     6,     7,     4,     0,     2,     0,     2,
       0,     2,     0,     1,     1,     4,     4,     7,    11,     7,
       7,    11,     8,    10,     1,     2,     2,     2,     2,     1,
       1,     1,     1,     4,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     2,     3,
       3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     2,
       0,     3,     0,     3,     0,     4,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,   107,   109,   108,   110,   111,   112,
     113,     0,   118,   114,     0,     0,     0,     3,     9,     7,
       8,     5,     6,     0,   119,   121,   120,   122,   123,   124,
     125,     0,     0,     0,   115,   126,   117,   116,     0,     0,
       0,   117,   116,     0,   127,     0,   128,    22,     0,     0,
     134,     0,    28,    28,    20,     0,     0,     0,     0,     0,
     105,   103,   104,    86,   102,   101,     0,     0,     0,     0,
       0,     0,     0,    84,    89,     0,    26,    26,     0,     0,
       0,    21,     0,     0,     0,   136,     0,     0,     0,    85,
      97,     0,    95,    94,    93,    92,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,    27,     0,     0,
       0,    20,     0,    17,     0,    10,    11,     0,   133,    14,
      87,    88,     0,     0,    96,    98,    90,    76,    75,    74,
      78,    77,    81,    80,    79,    83,    82,    71,    70,    68,
      67,    66,    63,    60,    65,    64,    61,    62,    73,    72,
      58,    59,    56,    57,    69,    28,    23,    24,    19,    18,
       0,     0,   100,    99,    26,   136,     0,    44,    49,     0,
       0,     0,     0,     0,    86,     0,     0,     0,    15,    13,
      50,    51,    52,    16,     0,     0,     0,    25,   135,     0,
      30,     0,     0,     0,     0,     0,     0,    85,    86,    48,
      47,    12,    46,    45,     0,     0,     0,     0,     0,     0,
      55,    87,    88,     0,    86,     0,     0,     0,    29,     0,
       0,     0,    36,   130,    35,    54,     0,    32,     0,    30,
     132,     0,     0,     0,     0,     0,     0,     0,   129,     0,
       0,     0,     0,    39,    31,    33,    34,     0,    40,   132,
      37,    30,    30,    42,     0,     0,   131,    53,     0,    32,
      30,    43,     0,     0,    38,    41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    17,    18,    19,   181,   199,   200,   201,
      79,    55,   202,   129,    76,   226,   254,   264,   238,   252,
     266,    95,    73,   206,    74,    89,    82,   251,   258,    59,
     138
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -237
static const yytype_int16 yypact[] =
{
    -237,    11,   236,  -237,   -40,   -34,   -32,   -26,    13,    20,
      33,   318,  -237,    17,   -21,    67,   -50,  -237,  -237,  -237,
    -237,  -237,  -237,    83,  -237,  -237,  -237,  -237,  -237,  -237,
    -237,    86,   105,   107,    81,  -237,    75,   -62,   121,   123,
     -60,  -237,    90,    87,  -237,   130,  -237,  -237,    91,    92,
     318,   782,   129,   129,   131,    84,   138,   139,   142,   106,
    -237,  -237,  -237,     8,  -237,  -237,   -33,   782,   782,   782,
     782,   782,   993,  -237,  -237,   782,   141,   141,   154,   110,
     111,  -237,   158,   136,   117,   159,   119,   161,   164,  -237,
      77,   165,  -237,  -237,  -237,  -237,  1028,  -237,   782,   782,
     782,   782,   782,   782,   782,   782,   782,   782,   782,   782,
     782,   782,   782,   782,   782,   782,   782,   782,   782,   782,
     782,   782,   782,   782,   782,   782,  -237,  1221,   182,   140,
     144,   131,   147,  -237,    87,  -237,  -237,   318,  -237,  -237,
    -237,  -237,   184,   185,  -237,  -237,  -237,  1221,  1221,  1221,
    1221,  1221,  1221,  1221,  1221,  1221,  1221,  1238,   350,   426,
     507,   588,    66,    66,   120,   120,   120,   120,    72,    72,
     -45,   -45,  -237,  -237,  -237,   129,  -237,  -237,  -237,  -237,
     188,   364,  -237,  -237,   141,   159,   163,  -237,  -237,   162,
     171,   179,   180,   782,   -35,   823,   782,   782,  -237,  -237,
    -237,  -237,  -237,  -237,   173,    41,   216,  -237,  -237,   782,
    -237,   782,   769,   782,   867,   221,   222,   223,   -31,  -237,
    -237,  -237,  -237,  -237,    80,  1061,   441,  1094,   186,  1127,
    -237,   227,   231,   191,    28,   909,   181,   232,  -237,   194,
     782,   195,  -237,   782,  -237,  -237,   204,  -237,   951,  -237,
    1193,   205,   -12,   782,   200,   769,   523,   782,  -237,   197,
     199,   206,  1160,   248,  -237,  -237,  -237,   207,  -237,  1193,
    -237,  -237,  -237,  -237,   203,   208,  -237,   769,   605,  -237,
    -237,  -237,   282,   687,  -237,  -237
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -237,  -237,  -237,  -237,  -237,   122,  -237,  -237,   298,   300,
     175,  -237,    23,   -75,   -52,  -236,    25,  -237,  -174,  -237,
     127,   -51,  -106,   245,  -237,   -13,    26,  -237,    48,  -237,
     145
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -101
static const yytype_int16 yytable[] =
{
      72,    77,   130,    90,    46,   -97,   260,   203,    38,   -98,
     261,     3,    50,   256,    51,    36,    93,    94,    47,    96,
      97,   123,   124,   125,   127,    22,    24,    52,    23,    39,
      53,    34,    25,    91,    26,   277,   278,    33,   228,    51,
      27,   215,   216,    51,   283,    87,    88,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   205,    58,   144,    81,    28,
     265,   267,    51,    35,    87,    88,    29,     4,     5,     6,
     219,   220,     7,     8,     9,    10,    11,    12,    13,    30,
     243,    31,    51,    37,    87,    88,   205,    32,   265,   207,
     222,   223,    60,    61,    62,   233,   234,    64,    65,    40,
     205,    52,    41,   184,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    66,   121,   122,   123,   124,
     125,    42,   214,    43,    67,    68,    69,    44,   205,   205,
     205,    51,    70,   142,   143,    45,    46,    48,   225,    49,
     227,    51,   229,   180,    71,    80,    54,    56,    57,    75,
      78,   205,   205,   235,    83,    84,   205,   205,    85,    86,
     128,   217,   119,   120,   121,   122,   123,   124,   125,   248,
     131,   132,   250,   133,   134,   135,   136,   140,   137,   139,
     141,   145,   262,     4,     5,     6,   269,    23,     7,     8,
       9,    10,    11,    12,    13,   186,   187,    14,   175,   188,
     182,   183,   176,    15,   185,   189,   177,   190,   191,   179,
     192,   193,    60,    61,    62,   209,   194,    64,    65,     4,
       5,     6,   210,   211,     7,     8,     9,    10,    11,    12,
      13,   212,   213,    14,   221,    66,   224,   231,   232,    15,
      16,   245,   246,   -96,    67,    68,   195,  -100,   240,   196,
     197,   -99,    70,   242,   247,   249,   253,   274,   259,   270,
     275,   263,   271,   279,    71,     4,     5,     6,   280,   272,
       7,     8,     9,    10,    11,    12,    13,   186,   187,    14,
      20,   188,    21,   198,   282,    15,   178,   189,   204,   190,
     191,    92,   192,   193,    60,    61,    62,   276,   194,    64,
      65,     4,     5,     6,     0,     0,     7,     8,     9,    10,
     208,    12,    13,     0,     0,    31,     0,    66,     0,     0,
       0,    32,     0,     0,     0,     0,    67,    68,   195,     0,
       0,   196,   197,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,   284,     0,     0,    71,     4,     5,     6,
       0,     0,     7,     8,     9,    10,    11,    12,    13,   186,
     187,    14,     0,   188,     0,     0,     0,    15,     0,   189,
       0,   190,   191,     0,   192,   193,    60,    61,    62,     0,
     194,    64,    65,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    66,
       0,     0,     0,     0,     0,     0,     0,     0,    67,    68,
     195,     0,     0,   196,   197,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     4,     5,     6,     0,    71,     7,
       8,     9,    10,    11,    12,    13,   186,   187,    14,     0,
     188,     0,     0,     0,    15,     0,   189,     0,   190,   191,
       0,   192,     0,    60,    61,    62,     0,   194,    64,    65,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,    66,     0,     0,     0,
       0,     0,     0,     0,     0,    67,    68,   195,     0,     0,
     196,   197,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,   237,     0,     0,    71,     4,     5,     6,     0,
       0,     7,     8,     9,    10,    11,    12,    13,   186,   187,
      14,     0,   188,     0,     0,     0,    15,     0,   189,     0,
     190,   191,     0,   192,     0,    60,    61,    62,     0,   194,
      64,    65,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,    66,     0,
       0,     0,     0,     0,     0,     0,     0,    67,    68,   195,
       0,     0,   196,   197,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,   268,     0,     0,    71,     4,     5,
       6,     0,     0,     7,     8,     9,    10,    11,    12,    13,
     186,   187,    14,     0,   188,     0,     0,     0,    15,     0,
     189,     0,   190,   191,     0,   192,     0,    60,    61,    62,
       0,   194,    64,    65,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
      66,     0,     0,     0,     0,     0,     0,     0,     0,    67,
      68,   195,     0,     0,   196,   197,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,   281,     0,     0,    71,
       4,     5,     6,     0,     0,     7,     8,     9,    10,    11,
      12,    13,   186,   187,    14,     0,   188,     0,     0,     0,
      15,     0,   189,     0,   190,   191,     0,   192,     0,    60,
      61,    62,     0,   194,    64,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,     0,     0,     0,     0,
       0,    67,    68,   195,     0,     0,   196,   197,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,   285,     0,
       0,    71,     4,     5,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,   186,   187,    14,     0,   188,     0,
       0,     0,    15,     0,   189,     0,   190,   191,     0,   192,
       0,    60,    61,    62,     0,   194,    64,    65,     0,     0,
       0,     0,     0,     0,    60,    61,    62,     0,    63,    64,
      65,     0,     0,     0,    66,     0,     0,     0,     0,     0,
       0,     0,     0,    67,    68,   195,     0,    66,   196,   197,
       0,    70,     0,     0,     0,     0,    67,    68,    69,     0,
       0,     0,     0,    71,    70,    60,    61,    62,     0,   218,
      64,    65,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
       0,     0,     0,     0,     0,     0,     0,    67,    68,    69,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   244,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   255,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,   126,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,   146,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,   236,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,   239,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
     241,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,   257,   273,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125
};

static const yytype_int16 yycheck[] =
{
      51,    53,    77,    36,    66,    40,    18,   181,    58,    40,
      22,     0,    72,   249,    74,    36,    67,    68,    80,    70,
      71,    66,    67,    68,    75,     2,    66,    40,     2,    79,
      43,    14,    66,    66,    66,   271,   272,    11,   212,    74,
      66,    76,    77,    74,   280,    76,    77,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   181,    50,    90,    55,    66,
     254,   255,    74,    66,    76,    77,    66,     3,     4,     5,
     196,   197,     8,     9,    10,    11,    12,    13,    14,    66,
      72,    17,    74,    36,    76,    77,   212,    23,   282,   184,
      69,    70,    32,    33,    34,    35,    36,    37,    38,    36,
     226,   134,    36,   175,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    55,    64,    65,    66,    67,
      68,    36,   193,    36,    64,    65,    66,    66,   254,   255,
     256,    74,    72,    76,    77,    80,    66,    36,   209,    36,
     211,    74,   213,   137,    84,    81,    36,    76,    76,    40,
      39,   277,   278,   224,    36,    36,   282,   283,    36,    73,
      39,   194,    62,    63,    64,    65,    66,    67,    68,   240,
      36,    81,   243,    82,    36,    59,    79,    36,    39,    80,
      36,    36,   253,     3,     4,     5,   257,   181,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    36,    19,
      36,    36,    82,    23,    36,    25,    82,    27,    28,    82,
      30,    31,    32,    33,    34,    72,    36,    37,    38,     3,
       4,     5,    80,    72,     8,     9,    10,    11,    12,    13,
      14,    72,    72,    17,    81,    55,    40,    36,    36,    23,
      24,    80,    30,    40,    64,    65,    66,    40,    82,    69,
      70,    40,    72,    82,    80,    80,    72,    29,    73,    82,
      73,    81,    83,    80,    84,     3,     4,     5,    80,    83,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
       2,    19,     2,   181,   279,    23,   131,    25,   181,    27,
      28,    66,    30,    31,    32,    33,    34,   269,    36,    37,
      38,     3,     4,     5,    -1,    -1,     8,     9,    10,    11,
     185,    13,    14,    -1,    -1,    17,    -1,    55,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,
      -1,    69,    70,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    84,     3,     4,     5,
      -1,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    -1,    -1,    23,    -1,    25,
      -1,    27,    28,    -1,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    -1,    -1,    69,    70,    -1,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,    84,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      19,    -1,    -1,    -1,    23,    -1,    25,    -1,    27,    28,
      -1,    30,    -1,    32,    33,    34,    -1,    36,    37,    38,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,    -1,
      69,    70,    -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    84,     3,     4,     5,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    -1,    -1,    23,    -1,    25,    -1,
      27,    28,    -1,    30,    -1,    32,    33,    34,    -1,    36,
      37,    38,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    69,    70,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    84,     3,     4,
       5,    -1,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    19,    -1,    -1,    -1,    23,    -1,
      25,    -1,    27,    28,    -1,    30,    -1,    32,    33,    34,
      -1,    36,    37,    38,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    -1,    -1,    69,    70,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    84,
       3,     4,     5,    -1,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    -1,    -1,    -1,
      23,    -1,    25,    -1,    27,    28,    -1,    30,    -1,    32,
      33,    34,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    -1,    -1,    69,    70,    -1,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    84,     3,     4,     5,    -1,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    -1,
      -1,    -1,    23,    -1,    25,    -1,    27,    28,    -1,    30,
      -1,    32,    33,    34,    -1,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    -1,    36,    37,
      38,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    -1,    55,    69,    70,
      -1,    72,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,
      -1,    -1,    -1,    84,    72,    32,    33,    34,    -1,    36,
      37,    38,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    73,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    73,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    73,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      73,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    39,    73,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    86,    87,     0,     3,     4,     5,     8,     9,    10,
      11,    12,    13,    14,    17,    23,    24,    88,    89,    90,
      93,    94,    97,   111,    66,    66,    66,    66,    66,    66,
      66,    17,    23,   111,    14,    66,    36,    36,    58,    79,
      36,    36,    36,    36,    66,    80,    66,    80,    36,    36,
      72,    74,   110,   110,    36,    96,    76,    76,   111,   114,
      32,    33,    34,    36,    37,    38,    55,    64,    65,    66,
      72,    84,   106,   107,   109,    40,    99,    99,    39,    95,
      81,    97,   111,    36,    36,    36,    73,    76,    77,   110,
      36,    66,   108,   106,   106,   106,   106,   106,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    75,   106,    39,    98,
      98,    36,    81,    82,    36,    59,    79,    39,   115,    80,
      36,    36,    76,    77,   110,    36,    73,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,    36,    82,    82,    95,    82,
     111,    91,    36,    36,    99,    36,    15,    16,    19,    25,
      27,    28,    30,    31,    36,    66,    69,    70,    90,    92,
      93,    94,    97,   103,   105,   107,   108,    98,   115,    72,
      80,    72,    72,    72,   106,    76,    77,   110,    36,   107,
     107,    81,    69,    70,    40,   106,   100,   106,   103,   106,
      82,    36,    36,    35,    36,   106,    73,    81,   103,    73,
      82,    73,    82,    72,    82,    80,    30,    80,   106,    80,
     106,   112,   104,    72,   101,    82,   100,    39,   113,    73,
      18,    22,   106,    81,   102,   103,   105,   103,    81,   106,
      82,    83,    83,    73,    29,    73,   113,   100,   100,    80,
      80,    81,   101,   100,    81,    81
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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
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
      int yychecklim = YYLAST - yyn + 1;
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
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
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
	}
      return yysize;
    }
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


/* Prevent warnings from -Wmissing-prototypes.  */

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
      
/* Line 1267 of yacc.c.  */
#line 1895 "parser.cpp"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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


#line 321 "parser.ypp"


/** You shall not pass!
 *  You should not  have to do or edit anything past this.
 */

extern int yylineno;

void yyerror(const char *s)
{
    fprintf(stderr, "%s at line %d\n", s, yylineno);
    return;
}

