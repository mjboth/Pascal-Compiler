/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parse.y"
     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 02 Aug 12   */

/* Copyright (c) 2012 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09 */
 
/*
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
  */


/* NOTE:   Copy your lexan.l lexical analyzer to this directory.      */

       /* To use:
                     make pars1y              has 1 shift/reduce conflict
                     pars1y                   execute the parser
                     i:=j .
                     ^D                       control-D to end input

                     pars1y                   execute the parser
                     begin i:=j; if i+j then x:=a+b*c else x:=a*b+c; k:=i end.
                     ^D

                     pars1y                   execute the parser
                     if x+y then if y+z then i:=j else k:=2.
                     ^D

           You may copy pars1.y to be parse.y and extend it for your
           assignment.  Then use   make parser   as above.
        */

        /* Yacc reports 1 shift/reduce conflict, due to the ELSE part of
           the IF statement, but Yacc's default resolves it in the right way.*/

#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;



/* Line 268 of yacc.c  */
#line 133 "y.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     STRING = 259,
     NUMBER = 260,
     PLUS = 261,
     MINUS = 262,
     TIMES = 263,
     DIVIDE = 264,
     ASSIGN = 265,
     EQ = 266,
     NE = 267,
     LT = 268,
     LE = 269,
     GE = 270,
     GT = 271,
     POINT = 272,
     DOT = 273,
     AND = 274,
     OR = 275,
     NOT = 276,
     DIV = 277,
     MOD = 278,
     IN = 279,
     COMMA = 280,
     SEMICOLON = 281,
     COLON = 282,
     LPAREN = 283,
     RPAREN = 284,
     LBRACKET = 285,
     RBRACKET = 286,
     DOTDOT = 287,
     ARRAY = 288,
     BEGINBEGIN = 289,
     CASE = 290,
     CONST = 291,
     DO = 292,
     DOWNTO = 293,
     ELSE = 294,
     END = 295,
     FILEFILE = 296,
     FOR = 297,
     FUNCTION = 298,
     GOTO = 299,
     IF = 300,
     LABEL = 301,
     NIL = 302,
     OF = 303,
     PACKED = 304,
     PROCEDURE = 305,
     PROGRAM = 306,
     RECORD = 307,
     REPEAT = 308,
     SET = 309,
     THEN = 310,
     TO = 311,
     TYPE = 312,
     UNTIL = 313,
     VAR = 314,
     WHILE = 315,
     WITH = 316
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING 259
#define NUMBER 260
#define PLUS 261
#define MINUS 262
#define TIMES 263
#define DIVIDE 264
#define ASSIGN 265
#define EQ 266
#define NE 267
#define LT 268
#define LE 269
#define GE 270
#define GT 271
#define POINT 272
#define DOT 273
#define AND 274
#define OR 275
#define NOT 276
#define DIV 277
#define MOD 278
#define IN 279
#define COMMA 280
#define SEMICOLON 281
#define COLON 282
#define LPAREN 283
#define RPAREN 284
#define LBRACKET 285
#define RBRACKET 286
#define DOTDOT 287
#define ARRAY 288
#define BEGINBEGIN 289
#define CASE 290
#define CONST 291
#define DO 292
#define DOWNTO 293
#define ELSE 294
#define END 295
#define FILEFILE 296
#define FOR 297
#define FUNCTION 298
#define GOTO 299
#define IF 300
#define LABEL 301
#define NIL 302
#define OF 303
#define PACKED 304
#define PROCEDURE 305
#define PROGRAM 306
#define RECORD 307
#define REPEAT 308
#define SET 309
#define THEN 310
#define TO 311
#define TYPE 312
#define UNTIL 313
#define VAR 314
#define WHILE 315
#define WITH 316




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 297 "y.tab.c"

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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  137

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    13,    17,    19,    24,    26,    30,    32,
      36,    38,    41,    42,    46,    48,    54,    59,    65,    70,
      76,    81,    85,    87,    91,    97,   104,   111,   116,   121,
     126,   129,   131,   133,   134,   139,   141,   143,   145,   147,
     151,   155,   157,   161,   165,   167,   169,   171,   173,   175,
     177,   181,   183,   187,   189,   192,   193,   197,   201,   205,
     207,   211,   213,   216,   220,   225,   227
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    51,     3,    28,    64,    29,    26,    65,
      74,    18,    -1,     3,    25,    64,    -1,     3,    -1,    46,
      69,    26,    66,    -1,    66,    -1,    36,    70,    67,    -1,
      67,    -1,    57,    71,    68,    -1,    68,    -1,    59,    72,
      -1,    -1,     5,    25,    69,    -1,     5,    -1,     3,    11,
       5,    26,    70,    -1,     3,    11,     5,    26,    -1,     3,
      11,     3,    26,    71,    -1,     3,    11,     3,    26,    -1,
      73,    27,     3,    26,    72,    -1,    73,    27,     3,    26,
      -1,     3,    25,    73,    -1,     3,    -1,    34,    74,    81,
      -1,    45,    84,    55,    74,    82,    -1,    42,    83,    38,
      84,    37,    74,    -1,    42,    83,    56,    84,    37,    74,
      -1,    60,    84,    37,    74,    -1,    53,    77,    58,    78,
      -1,    61,    80,    37,    74,    -1,    44,     5,    -1,    75,
      -1,    83,    -1,    -1,     3,    28,    76,    29,    -1,     3,
      -1,    84,    -1,     3,    -1,     4,    -1,    76,    25,    76,
      -1,    77,    26,    74,    -1,    74,    -1,     3,    79,     5,
      -1,     3,    79,     3,    -1,    11,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    16,    -1,    80,    25,     3,
      -1,     3,    -1,    26,    74,    81,    -1,    40,    -1,    39,
      74,    -1,    -1,     3,    10,    84,    -1,    84,     6,    85,
      -1,    84,     7,    85,    -1,    85,    -1,    85,     8,    86,
      -1,    86,    -1,     7,    86,    -1,    28,    84,    29,    -1,
       3,    28,    84,    29,    -1,     3,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    82,    83,    85,    86,    88,    89,    91,
      92,    94,    95,    97,    98,   100,   101,   103,   104,   106,
     107,   109,   110,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   124,   125,   127,   128,   129,   130,
     132,   133,   135,   136,   138,   139,   140,   141,   142,   143,
     145,   146,   148,   149,   151,   152,   154,   156,   157,   158,
     160,   161,   162,   164,   165,   166,   167
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "NUMBER", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "ASSIGN", "EQ", "NE", "LT", "LE", "GE", "GT",
  "POINT", "DOT", "AND", "OR", "NOT", "DIV", "MOD", "IN", "COMMA",
  "SEMICOLON", "COLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "DOTDOT", "ARRAY", "BEGINBEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE",
  "END", "FILEFILE", "FOR", "FUNCTION", "GOTO", "IF", "LABEL", "NIL", "OF",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "THEN",
  "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH", "$accept", "program",
  "idens", "lblock", "cblock", "tblock", "vblock", "ints", "con", "typ",
  "vars", "varsid", "statement", "procedid", "procedlp", "statelp",
  "compare", "cmpr", "varlp", "endpart", "endif", "assignment", "expr",
  "term", "factor", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    76,    76,    76,    76,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    84,    84,    84,
      85,    85,    85,    86,    86,    86,    86
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     9,     3,     1,     4,     1,     3,     1,     3,
       1,     2,     0,     3,     1,     5,     4,     5,     4,     5,
       4,     3,     1,     3,     5,     6,     6,     4,     4,     4,
       2,     1,     1,     0,     4,     1,     1,     1,     1,     3,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     2,     0,     3,     3,     3,     1,
       3,     1,     2,     3,     4,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     4,     0,     0,     0,
       3,    12,     0,     0,     0,     0,    33,     6,     8,    10,
       0,    12,    14,     0,     0,    12,    22,    11,     0,    35,
      33,     0,     0,     0,    33,     0,     0,     0,    31,    32,
       0,     7,     0,    12,     0,     9,     0,     0,     0,     0,
       0,     0,     0,    30,    65,    66,     0,     0,     0,    59,
      61,    41,     0,     0,    51,     0,     2,     0,    13,     5,
       0,    21,     0,    56,    65,    38,     0,    36,    33,    53,
      23,     0,     0,     0,    62,     0,     0,     0,    33,     0,
      33,     0,    33,     0,    33,    16,    18,    20,     0,    34,
       0,     0,     0,     0,    63,    57,    58,    55,    60,    40,
       0,    28,    27,    50,    29,    15,    17,    19,    39,    52,
      33,    33,    64,    33,    24,    44,    45,    46,    47,    48,
      49,     0,    25,    26,    54,    43,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    16,    17,    18,    19,    23,    21,    25,
      27,    28,    37,    38,    76,    62,   111,   131,    65,    80,
     124,    39,    77,    59,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -68
static const yytype_int8 yypact[] =
{
     -16,    24,    71,    51,   -68,    81,    61,    58,    81,    63,
     -68,   -18,    89,    90,    91,    94,     8,   -68,   -68,   -68,
      95,    26,    80,    82,    96,    50,    85,   -68,    84,    -3,
       8,   109,   108,    60,     8,    60,   111,    97,   -68,   -68,
     112,   -68,    90,    13,   113,   -68,    94,   115,    60,    19,
      -9,   110,   -24,   -68,    93,   -68,    54,    60,    -4,   114,
     -68,   -68,   -21,     3,   -68,    41,   -68,    98,   -68,   -68,
      99,   -68,   100,    38,    52,   -68,     4,    38,     8,   -68,
     -68,    60,    60,    60,   -68,    67,    60,    60,     8,    54,
       8,   116,     8,   120,     8,    89,    91,    94,    19,   -68,
      -9,     6,     9,    69,   -68,   114,   114,    92,   -68,   -68,
      88,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   102,   -68,
       8,     8,   -68,     8,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,    33,   -68,   -68,   -68,   -68,   -68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   121,   -68,    87,   107,   117,   101,    37,    39,
      36,   103,   -30,   -68,    40,   -68,   -68,   -68,   -68,    34,
     -68,   105,   -27,   -67,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -38
static const yytype_int16 yytable[] =
{
      50,    84,    86,    87,    61,    90,    58,    48,    63,    86,
      87,    29,    86,    87,    81,    86,    87,    78,    12,   105,
     106,    73,    74,    75,    55,    49,    56,     3,    13,    98,
      85,    79,    82,    99,   108,     1,   135,    91,   136,    14,
      92,    15,    30,   120,    86,    87,   121,    57,   100,    12,
      31,    88,    32,    33,   101,   102,   103,    54,   107,    55,
     109,    34,   112,    54,   114,    55,    93,    56,    35,    36,
      14,     4,    15,    86,    87,    86,    87,   -37,    94,     5,
      83,   -37,    57,    14,     6,    15,     8,     9,    57,    11,
     132,   133,    20,   134,    24,    22,   104,    26,   122,   125,
     126,   127,   128,   129,   130,    42,    40,    44,    43,    15,
      46,    47,    51,    53,    64,    66,    70,    67,    72,   110,
      48,    83,    89,   113,    95,    96,    97,    98,    41,    10,
      69,   123,   115,   117,   119,   116,    52,     0,   118,     0,
       0,     0,    45,    68,     0,     0,     0,     0,     0,    71
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-68))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      30,    56,     6,     7,    34,    26,    33,    10,    35,     6,
       7,     3,     6,     7,    38,     6,     7,    26,    36,    86,
      87,    48,     3,     4,     5,    28,     7,     3,    46,    25,
      57,    40,    56,    29,    89,    51,     3,    58,     5,    57,
      37,    59,    34,    37,     6,     7,    37,    28,    78,    36,
      42,    55,    44,    45,    81,    82,    83,     3,    88,     5,
      90,    53,    92,     3,    94,     5,    25,     7,    60,    61,
      57,     0,    59,     6,     7,     6,     7,    25,    37,    28,
      28,    29,    28,    57,     3,    59,    25,    29,    28,    26,
     120,   121,     3,   123,     3,     5,    29,     3,    29,    11,
      12,    13,    14,    15,    16,    25,    11,    11,    26,    59,
      25,    27,     3,     5,     3,    18,     3,     5,     3,     3,
      10,    28,     8,     3,    26,    26,    26,    25,    21,     8,
      43,    39,    95,    97,   100,    96,    31,    -1,    98,    -1,
      -1,    -1,    25,    42,    -1,    -1,    -1,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    63,     3,     0,    28,     3,    64,    25,    29,
      64,    26,    36,    46,    57,    59,    65,    66,    67,    68,
       3,    70,     5,    69,     3,    71,     3,    72,    73,     3,
      34,    42,    44,    45,    53,    60,    61,    74,    75,    83,
      11,    67,    25,    26,    11,    68,    25,    27,    10,    28,
      74,     3,    83,     5,     3,     5,     7,    28,    84,    85,
      86,    74,    77,    84,     3,    80,    18,     5,    69,    66,
       3,    73,     3,    84,     3,     4,    76,    84,    26,    40,
      81,    38,    56,    28,    86,    84,     6,     7,    55,     8,
      26,    58,    37,    25,    37,    26,    26,    26,    25,    29,
      74,    84,    84,    84,    29,    85,    85,    74,    86,    74,
       3,    78,    74,     3,    74,    70,    71,    72,    76,    81,
      37,    37,    29,    39,    82,    11,    12,    13,    14,    15,
      16,    79,    74,    74,    74,     3,     5
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
        case 2:

/* Line 1806 of yacc.c  */
#line 80 "parse.y"
    { makeprogram((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(8) - (9)])); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 82 "parse.y"
    { (yyval) = cons((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 83 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 85 "parse.y"
    { (yyval) = (yyvsp[(4) - (4)]); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 86 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 88 "parse.y"
    { (yyval) = (yyvsp[(3) - (3)]);}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 89 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 91 "parse.y"
    { (yyval) = (yyvsp[(3) - (3)]);}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 92 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 100 "parse.y"
    { instconst((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)])); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 101 "parse.y"
    { instconst((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 106 "parse.y"
    { instvars((yyvsp[(1) - (5)]), (yyvsp[(3) - (5)])); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 107 "parse.y"
    { instvars((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 109 "parse.y"
    { (yyval) = cons((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 110 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 112 "parse.y"
    { (yyval) = makeprogn((yyvsp[(1) - (3)]),cons((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]))); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 113 "parse.y"
    { (yyval) = makeif((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 114 "parse.y"
    { (yyval) = makefor(-1,(yyvsp[(1) - (6)]),(yyvsp[(2) - (6)]),(yyvsp[(3) - (6)]),(yyvsp[(4) - (6)]),(yyvsp[(5) - (6)]),(yyvsp[(6) - (6)])); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 115 "parse.y"
    { (yyval) = makefor( 1,(yyvsp[(1) - (6)]),(yyvsp[(2) - (6)]),(yyvsp[(3) - (6)]),(yyvsp[(4) - (6)]),(yyvsp[(5) - (6)]),(yyvsp[(6) - (6)])); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 117 "parse.y"
    { (yyval) = makerepeat((yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)])); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 124 "parse.y"
    { (yyval) = makefuncall(talloc(), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 127 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 128 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 129 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 130 "parse.y"
    { (yyval) = cons((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 132 "parse.y"
    { (yyval) = cons((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 133 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 135 "parse.y"
    { (yyval) = binop((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 136 "parse.y"
    { (yyval) = binop((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 138 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 139 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 140 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 141 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 142 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 143 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 148 "parse.y"
    { (yyval) = cons((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 149 "parse.y"
    { (yyval) = NULL; }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 151 "parse.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 152 "parse.y"
    { (yyval) = NULL; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 154 "parse.y"
    { (yyval) = binop((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 156 "parse.y"
    { (yyval) = binop((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 157 "parse.y"
    { (yyval) = binop((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 158 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 160 "parse.y"
    { (yyval) = binop((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 161 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 162 "parse.y"
    { (yyval) = unaryop((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 164 "parse.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 165 "parse.y"
    { (yyval) = makefuncall(talloc(), (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));  }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 166 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 167 "parse.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;



/* Line 1806 of yacc.c  */
#line 1995 "y.tab.c"
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 2067 of yacc.c  */
#line 170 "parse.y"


/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG         31             /* set bits here for debugging, 0 = off  */
#define DB_CONS        1             /* bit to trace cons */
#define DB_BINOP       2             /* bit to trace binop */
#define DB_MAKEPROGRAM 3             /* bit to trace makeprogram */
#define DB_MAKEIF      4             /* bit to trace makeif */
#define DB_MAKELABEL   5             /* bit to trace makelabel */
#define DB_MAKEFOR     6             /* bit to trace makefor */
#define DB_MAKEFUNCALL 7             /* bit to trace makefuncall */
#define DB_MAKEPROGN   8             /* bit to trace makeprogn */
#define DB_MAKEFLOAT   9             /* bit to trace makefloat */
#define DB_MAKEFIX    10             /* bit to trace makefix */
#define DB_COPYTOK    11             /* bit to trace copytok */
#define DB_MAKEGOTO   12             /* bit to trace makegoto */
#define DB_MAKEREPEAT 13             /* bit to trace makerepeat */
#define DB_INSTCONST  14             /* bit to trace instconst */
#define DB_INSTVARS   15             /* bit to trace instvars */
#define DB_PARSERES   16             /* bit to trace parseresult */
#define DB_UNARYOP    17             /* bit to trace unaryop */

#define WORDSIZE   4             /* alignment size in address units (bytes)  */
#define ALIGNSIZE 16             /* record/array alignment size    */

 int labelnumber = 0;  /* sequential counter for internal label numbers */

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */
TOKEN makeprogram (TOKEN name, TOKEN args, TOKEN statements)
  {  TOKEN prog = talloc();
     prog->tokentype = OPERATOR;
     prog->whichval = PROGRAMOP;
     prog->operands = name;

     parseresult = prog;

     cons(name, cons(makeprogn(talloc(), args), statements));
     
     if (DEBUG & DB_MAKEPROGRAM)
       { printf("makeprogram\n");
         dbugprinttok(name); 
         dbugprinttok(args);
         dbugprinttok(statements);
       };
     return prog;
  }
TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item); 
         dbugprinttok(list);
       };
    return item;
  }

TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { 
    /* link operands to operator       */
    SYMBOL lsym = searchst(lhs->stringval);
    TOKEN ltok = copytok(lhs);
    if(lsym != NULL)
    { if(lsym->kind == CONSTSYM)
      { ltok->tokentype = NUMBERTOK;
        ltok->datatype = lsym->basicdt;
        switch(ltok->datatype)
        {  case INTEGER: ltok->intval = lsym->constval.intnum; break;
           case REAL: ltok->realval = lsym->constval.realnum; break;
        }
      }
    }  
    

    /* link second operand to first    */
    SYMBOL rsym = searchst(rhs->stringval);
    TOKEN rtok = copytok(rhs);
    if(rsym != NULL)
    { if(rsym->kind == CONSTSYM)
      { rtok->tokentype = NUMBERTOK;
        rtok->datatype = rsym->basicdt;
        switch(rtok->datatype)
        {  case INTEGER: rtok->intval = rsym->constval.intnum; break;
           case REAL: rtok->realval = rsym->constval.realnum; break;
        }
      }
    }

    if(op->whichval != ASSIGNOP)
    {
      /*the following converts one operand to match the datatype of the other if one is a float*/
      /*both tokens are NUMBERTOK*/
      if(lsym == NULL && rsym == NULL)
      {  if((ltok->datatype == REAL || rtok->datatype == REAL) && ltok->datatype != rtok->datatype)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }
      /*both tokens are IDENTIFIER symbols*/
      if(lsym != NULL && rsym != NULL)
      { if((lsym->basicdt == REAL || rsym->basicdt == REAL) && lsym->basicdt != rsym->basicdt)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }
      /*one token is a symbol, the other a number*/
      if(lsym != NULL && rsym == NULL)
      { if((lsym->basicdt == REAL || rtok->datatype == REAL) && lsym->basicdt != rtok->datatype)
        { if(lsym->basicdt == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }
      if(lsym == NULL && rsym != NULL)
      { if((ltok->datatype == REAL || rsym->basicdt == REAL) && ltok->datatype != rsym->basicdt)
        { if(ltok->datatype == INTEGER) ltok = makefloat(ltok);
          else rtok = makefloat(rtok);
        }
      }

      ltok->link = rtok;
    }
    //if op is an ASSIGNOP
    //lhs is a symbol
    else if(lsym != NULL)
    {
      //assign FIXOP
      //rhs is a symbol
      if(rsym != NULL)
      { if(rsym->basicdt == REAL && lsym->basicdt == INTEGER) ltok->link = makefix(rtok);
        else ltok->link = rtok;
      }
      //rhs is a NUMBERTOK
      else if(rtok->datatype == REAL && lsym->basicdt == INTEGER)
      { ltok->link = makefix(rtok);
      }
      else ltok->link = rtok;
    }
    //both lhs and rhs are of the same type
    else ltok->link = rtok;

                 
    op->operands = ltok;

    //sets the datatype of the operator the largest datatype of its operands
    if(rtok->datatype > ltok->datatype)
      op->datatype = rtok->datatype;
    else op->datatype = ltok->datatype;   


    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    return op;
  }

TOKEN unaryop(TOKEN op, TOKEN lhs)
  { op->operands = lhs;
    lhs->link = NULL;
    if (DEBUG & DB_UNARYOP)
    { printf("unaryop\n");
      dbugprinttok(op);
      dbugprinttok(lhs);
    }
    return op;
  }

TOKEN makefloat(TOKEN tok)
  { TOKEN flt = talloc();
    if(tok->tokentype == IDENTIFIERTOK)
    { flt->tokentype = OPERATOR;
      flt->whichval = FLOATOP;
      unaryop(flt, tok);
    }

    else if(tok->tokentype == NUMBERTOK)
    { flt->tokentype = NUMBERTOK;
      flt->datatype = REAL;
      flt->realval = (float)tok->intval;
    }

    if(DEBUG & DB_MAKEFLOAT) 
    {  printf("makefloat\n");
       dbugprinttok(tok);
    }
  return flt;
  }

TOKEN makefix(TOKEN tok)
  { TOKEN fix = talloc();
    fix->tokentype = OPERATOR;
    fix->whichval = FIXOP;
    fix->operands = tok;
    if(DEBUG & DB_MAKEFIX) 
    {  printf("makefix\n");
       dbugprinttok(tok);
    }
    return fix;
  }

TOKEN copytok(TOKEN origtok)
  { TOKEN cpy = origtok;
    if(DEBUG & DB_COPYTOK)
    {  printf("copytok\n");
       dbugprinttok(origtok);
    }
    return cpy;
  }

TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;
     tok->whichval = IFOP;
     if (elsepart != NULL) elsepart->link = NULL;
     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }

TOKEN makelabel()
  { TOKEN lbl = talloc();
    TOKEN n = talloc();
    lbl->tokentype = OPERATOR;
    lbl->whichval = LABELOP;
    n->tokentype = NUMBERTOK;
    n->datatype = INTEGER;
    n->intval = labelnumber++;
    lbl->operands = n;
    if (DEBUG & DB_MAKELABEL)
       { printf("makelabel\n");
         dbugprinttok(lbl);
         dbugprinttok(n);
       };
    return lbl;
  }

TOKEN makegoto(int label)
  {  TOKEN go2 = talloc();
     TOKEN num = talloc();
     go2->tokentype = OPERATOR;
     go2->whichval = GOTOOP;
     num->tokentype = NUMBERTOK;
     num->datatype = INTEGER;
     num->intval = label;
     go2->operands = num;
     if (DEBUG & DB_MAKEGOTO)
       { printf("makegoto\n");
         dbugprinttok(go2);
         dbugprinttok(num);
       };
     return go2;
  }


TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr)
  {  TOKEN go2 = makegoto(labelnumber);
     TOKEN iftok =makeif(tokb, expr, cons(makeprogn(talloc(), NULL), talloc()), go2);


     makeprogn(tok, cons(makelabel(), statements));

     TOKEN linked = statements;
     while(linked->link != NULL) linked = linked->link;
     cons(linked, iftok);

     if (DEBUG & DB_MAKEREPEAT)
       { printf("makerepeat\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
         dbugprinttok(tokb);
         dbugprinttok(expr);
       };
     
     return tok;
  }

TOKEN makefor(int sign, TOKEN tok, TOKEN asg, TOKEN tokb, TOKEN endexpr,
              TOKEN tokc, TOKEN statement)
  { 
    //op will be the <= (or >=) value when the for-loop checks its argument after every loop
		TOKEN op = talloc();
    op->tokentype = OPERATOR;

    //increment will be the ":=" for the loop update
    TOKEN increment = talloc();
    increment->tokentype = OPERATOR;
    increment->whichval = ASSIGNOP;
    //one will just be a token of value one, for the increment
    TOKEN one = talloc();
    one->tokentype = NUMBERTOK;
    one->datatype = INTEGER;
    one->intval = 1;
    //increop will be nested in increment, will either be PLUSOP or MINUSOP
    TOKEN increop = talloc();
    increop->tokentype = OPERATOR;

		if(sign == -1)
    {  op->whichval = GEOP;
       increop->whichval = MINUSOP;
    }
    else
    {  op->whichval = LEOP;
       increop->whichval = PLUSOP;
    }

    TOKEN tmp = talloc();

    //to copy the initialized value
    TOKEN cpy1 = talloc();
    cpy1->tokentype = asg->operands->tokentype;
    cpy1->whichval = asg->operands->whichval;


    TOKEN cpy2 = talloc();
    cpy2->tokentype = asg->operands->tokentype;
    cpy2->whichval = asg->operands->whichval;


    TOKEN cpy3 = talloc();
    cpy3->tokentype = asg->operands->tokentype;
    cpy3->whichval = asg->operands->whichval;

    //the goto branch
    TOKEN go2 = makegoto(labelnumber);

    binop(op,cpy1,endexpr);
    binop(increment, cpy2, increop);
    binop(increop, cpy3, one);
    cons(increment, go2);

    makeprogn(tok, asg);
    makeprogn(tmp,cons(statement, increment));
    cons(asg, cons(makelabel(), makeif(tokb, op, tmp, NULL)));
    if (DEBUG & DB_MAKEFOR)
    { printf("makefor\n");
      dbugprinttok(tok);
      dbugprinttok(asg);
      dbugprinttok(tokb);
      dbugprinttok(endexpr);
      dbugprinttok(tokc);
      dbugprinttok(statement);
    };
    return tok;
  }

TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args)
  { tok->tokentype = OPERATOR;
    tok->whichval = FUNCALLOP;
    SYMBOL sym = searchins(fn->stringval);
    tok->datatype = sym->datatype->basicdt;
    tok->operands = fn;
    cons(fn, args);
    if (DEBUG & DB_MAKEFUNCALL)
    { printf("makefuncall\n");
      dbugprinttok(tok);
      dbugprinttok(fn);
      dbugprinttok(args);
    }
    return tok;
  }

void instconst(TOKEN idtok, TOKEN consttok)
  {  SYMBOL sym;

     sym = insertsym(idtok->stringval);
     sym->kind = CONSTSYM;
     sym->basicdt = consttok->datatype;
     switch(sym->basicdt)
     { case INTEGER: sym->constval.intnum = consttok->intval; break;
       case REAL: sym->constval.realnum = consttok->realval; break;
       case BOOLETYPE: sym->constval.intnum = consttok->intval; break;
     }

     if (DEBUG & DB_INSTCONST)
     { printf("instconst\n");
       dbugprinttok(idtok);
       dbugprinttok(consttok);
     }

  }

void instvars(TOKEN idlist, TOKEN typetok)
  {  SYMBOL sym, typ;
     typ = makesym(typetok->stringval);
     typ->kind = BASICTYPE;
     int align;

     switch(typetok->stringval[0])
     {
       case 'i': typ->basicdt = INTEGER; break;
       case 'r': typ->basicdt = REAL; break;
       case 's': typ->basicdt = STRINGTYPE; break;
       case 'b': typ->basicdt = BOOLETYPE; break;
     }
     typ->size = basicsizes[typ->basicdt];
     align = (typ->size > WORDSIZE) ? ALIGNSIZE : typ->size;

     while (idlist != NULL)
     {  sym = insertsym(idlist->stringval);
        sym->kind = VARSYM;
        sym->offset = wordaddress(blockoffs[blocknumber],align);
        sym->size = typ->size;
        blockoffs[blocknumber] = sym->offset + sym->size;
        sym->datatype = typ;
        sym->basicdt = typ->basicdt;
        idlist = idlist->link;
     }

     if (DEBUG & DB_INSTVARS)
     { printf("instvars\n");
       dbugprinttok(idlist);
       dbugprinttok(typetok);
     }
  }

int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
yyerror(s)
  char * s;
  { 
  fputs(s,stderr); putc('\n',stderr);
  }

main()
  { int res;
    initsyms();
    res = yyparse();
    printst();
    printf("yyparse result = %8d\n", res);
    if (DEBUG & DB_PARSERES) dbugprinttok(parseresult);
    ppexpr(parseresult);           /* Pretty-print the result tree */
  }

