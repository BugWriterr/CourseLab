/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "zyp.y" /* yacc.c:339  */

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);

#line 78 "zyp.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "zyp.tab.h".  */
#ifndef YY_YY_ZYP_TAB_H_INCLUDED
# define YY_YY_ZYP_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    RELOP = 260,
    TYPE = 261,
    FLOAT = 262,
    CHAR = 263,
    STRING = 264,
    LP = 265,
    RP = 266,
    LC = 267,
    RC = 268,
    LB = 269,
    RB = 270,
    SEMI = 271,
    COMMA = 272,
    DOT = 273,
    PLUS = 274,
    MINUS = 275,
    STAR = 276,
    DIV = 277,
    ASSIGNOP = 278,
    AUTOPLUS = 279,
    AUTOMINUS = 280,
    PLUSASSIGNOP = 281,
    MINUSASSIGNOP = 282,
    STARASSIGNOP = 283,
    DIVASSIGNOP = 284,
    MODASSIGNOP = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    IF = 289,
    ELSE = 290,
    WHILE = 291,
    RETURN = 292,
    FOR = 293,
    SWITCH = 294,
    CASE = 295,
    COLON = 296,
    DEFAULT = 297,
    BREAK = 298,
    CONTINUE = 299,
    STRUCT = 300,
    ARRAYLIST = 301,
    ARRAY_VISIT = 302,
    STRUCTDEF = 303,
    STRUCTDEC = 304,
    STRUCT_NAME = 305,
    STRUCTVI = 306,
    VAR_STRUCT_DEF = 307,
    FOR_DEC = 308,
    ARGSLIST = 309,
    FOR_DEC1 = 310,
    FOR_DEC2 = 311,
    FOR_DEC3 = 312,
    EXT_DEF_LIST = 313,
    EXT_VAR_DEF = 314,
    FUNC_DEF = 315,
    FUNC_DEC = 316,
    EXT_DEC_LIST = 317,
    PARAM_LIST = 318,
    PARAM_DEC = 319,
    VAR_DEF = 320,
    DEC_LIST = 321,
    DEF_LIST = 322,
    COMP_STM = 323,
    STM_LIST = 324,
    EXP_STMT = 325,
    IF_THEN = 326,
    IF_THEN_ELSE = 327,
    FUNC_CALL = 328,
    ARGS = 329,
    FUNCTION = 330,
    PARAM = 331,
    ARG = 332,
    CALL = 333,
    LABEL = 334,
    GOTO = 335,
    JLT = 336,
    JLE = 337,
    JGT = 338,
    JGE = 339,
    EQ = 340,
    NEQ = 341,
    MOD = 342,
    UMINUS = 343,
    LOWER_THEN_ELSE = 344
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "zyp.y" /* yacc.c:355  */

	int    type_int;
        char   type_char[32];
	float  type_float;
	char   type_id[32];
        char   type_string[32];
	struct ASTNode *ptr;

#line 217 "zyp.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_ZYP_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 248 "zyp.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   693

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   344

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    71,    71,    77,    78,    80,    81,    82,    83,    87,
      90,   101,   112,   117,   118,   124,   126,   127,   130,   131,
     137,   138,   144,   145,   148,   149,   151,   154,   156,   157,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   175,
     178,   179,   180,   182,   183,   185,   186,   187,   189,   190,
     191,   193,   194,   195,   197,   198,   200,   201,   206,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   246,   250,
     254,   257,   262,   266,   267
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "RELOP", "TYPE", "FLOAT",
  "CHAR", "STRING", "LP", "RP", "LC", "RC", "LB", "RB", "SEMI", "COMMA",
  "DOT", "PLUS", "MINUS", "STAR", "DIV", "ASSIGNOP", "AUTOPLUS",
  "AUTOMINUS", "PLUSASSIGNOP", "MINUSASSIGNOP", "STARASSIGNOP",
  "DIVASSIGNOP", "MODASSIGNOP", "AND", "OR", "NOT", "IF", "ELSE", "WHILE",
  "RETURN", "FOR", "SWITCH", "CASE", "COLON", "DEFAULT", "BREAK",
  "CONTINUE", "STRUCT", "ARRAYLIST", "ARRAY_VISIT", "STRUCTDEF",
  "STRUCTDEC", "STRUCT_NAME", "STRUCTVI", "VAR_STRUCT_DEF", "FOR_DEC",
  "ARGSLIST", "FOR_DEC1", "FOR_DEC2", "FOR_DEC3", "EXT_DEF_LIST",
  "EXT_VAR_DEF", "FUNC_DEF", "FUNC_DEC", "EXT_DEC_LIST", "PARAM_LIST",
  "PARAM_DEC", "VAR_DEF", "DEC_LIST", "DEF_LIST", "COMP_STM", "STM_LIST",
  "EXP_STMT", "IF_THEN", "IF_THEN_ELSE", "FUNC_CALL", "ARGS", "FUNCTION",
  "PARAM", "ARG", "CALL", "LABEL", "GOTO", "JLT", "JLE", "JGT", "JGE",
  "EQ", "NEQ", "MOD", "UMINUS", "LOWER_THEN_ELSE", "$accept", "program",
  "ExtDefList", "ExtDef", "Specifier", "StructSpecifier", "StructName",
  "StructNameNotNUll", "ExtDecList", "VarDec", "ARRAY", "FuncDec",
  "VarList", "ParamDec", "CompSt", "StmList", "Stmt", "FORDEC", "FORDEC1",
  "FORDEC2", "FORDEC3", "DefList", "Def", "DecList", "Dec", "Exp",
  "ARGSLISTS", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344
};
# endif

#define YYPACT_NINF -78

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define YYTABLE_NINF -49

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      42,   -10,   -78,    17,    31,   -78,    42,    74,    36,   -78,
       6,    44,    18,   -78,   -78,    86,   -78,    66,    85,    72,
     -78,    49,    91,    83,    88,   -78,    93,    87,   660,   -78,
     -78,   108,   495,   -78,    97,    18,    98,   103,   495,   660,
     660,    18,   -78,   108,   107,   102,   -78,    89,   -78,   -78,
     -78,   660,   660,   660,   660,   660,   660,   128,   -78,   -78,
     584,   -78,   104,   -78,   -78,   -78,   438,   438,   -78,   -78,
     -78,   115,   622,   -78,   156,   199,   109,   110,   106,    67,
      67,   106,   660,    91,   122,   660,   660,   660,   660,   660,
     -78,   -78,   660,   660,   660,   660,   660,   660,   660,   660,
     541,   118,   119,   660,   120,   116,   121,   -78,   123,   584,
     228,   -78,   -78,   -78,   124,   -78,   660,   -78,   114,   176,
     -78,   -78,    -8,    -8,    67,    67,    14,    14,    14,    14,
      14,    14,   188,   456,    67,   660,   660,   269,    70,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   126,   298,   339,   -78,
     -78,    18,   130,   641,   146,   660,   -78,   584,   584,   147,
     584,   -78,   660,   368,   -78,   129,   -78,   -78,   -78,   -78,
     410,   -78,   584,   660,   -78,   -78
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    10,    13,     0,     2,     0,     0,     0,     9,
      15,     0,     0,     1,     4,    18,     7,     0,    16,     0,
       8,     0,    18,     0,    56,    12,    54,     0,     0,    19,
       5,     0,     0,     6,     0,     0,     0,     0,     0,     0,
       0,     0,    23,     0,     0,    24,    84,    82,    85,    83,
      86,     0,     0,     0,     0,     0,     0,     0,    90,    17,
      28,    50,     0,    52,    11,    49,    58,    57,    55,    26,
      22,     0,     0,    87,     0,    94,    90,     0,    78,    73,
      74,    79,     0,    20,     0,     0,     0,     0,     0,     0,
      75,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,    28,
       0,    51,    25,    81,     0,    77,     0,    89,    92,    67,
      21,    88,    68,    69,    70,    71,    59,    60,    61,    62,
      63,    64,    65,    66,    72,     0,     0,     0,     0,    37,
      36,    27,    29,    30,    80,    93,     0,     0,     0,    32,
      42,     0,     0,     0,     0,     0,    91,     0,     0,     0,
       0,    44,    47,     0,    40,    33,    35,    41,    38,    39,
      45,    43,     0,    47,    34,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -78,   -78,   133,   -78,     2,     9,   -78,   -78,   111,    46,
     -43,   -78,    73,   -78,   149,    56,   -77,   -78,   -78,   -78,
      -7,    -1,   -78,   -34,   -78,   -28,   -49,   -67
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    35,    23,    11,    12,    17,    24,
      29,    19,    44,    45,   107,   108,   109,   152,   153,   162,
     169,    60,    38,    25,    26,   110,    58,    77
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    62,     7,    76,    73,   114,     9,    68,     7,     8,
      84,    66,    67,    87,    88,     8,    90,    91,   -14,    82,
      37,    10,    22,    74,    75,    78,    79,    80,    81,    43,
      36,    13,    84,    85,    86,    87,    88,    65,    90,    91,
     120,    36,    -3,     1,    75,    97,    98,    36,     2,   145,
      34,    76,    20,    18,   119,     2,    21,   122,   123,   124,
     125,   126,   -48,     3,   127,   128,   129,   130,   131,   132,
     133,   134,    75,    43,    22,   137,     2,    18,    15,    99,
     165,   166,    30,   168,    32,    84,   150,     3,    75,    69,
      16,    90,    91,     2,     3,   174,    27,   156,    42,    72,
      28,    99,    31,    28,   154,    28,    39,   147,   148,    36,
      41,    40,    22,    61,    63,     3,    64,   159,    70,    71,
     111,     2,   117,   118,    84,   163,   121,    75,   135,   136,
     138,   146,   139,    82,   170,   144,   141,   140,   155,    14,
     151,   160,    59,    83,   112,   170,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    82,   164,   167,   172,   142,   175,   115,    33,     0,
       0,     0,     0,     0,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,    82,    84,    85,    86,    87,    88,     0,
      90,    91,     0,     0,    82,     0,    84,    85,    86,    87,
      88,     0,    90,    91,     0,    99,   116,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   143,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   149,    99,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    82,     0,     0,     0,     0,     0,   157,
       0,     0,     0,     0,     0,    99,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,     0,    99,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   171,    99,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   173,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,    84,    85,    86,    87,
      88,    82,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,    84,    85,    86,    87,    88,     0,
      90,    91,     0,     0,     0,     0,     0,    97,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    99,   -48,   -48,
       0,     2,   -48,   -48,   -48,   -48,     0,   -48,   -48,     0,
       0,     0,     0,     0,     0,   -48,     0,     0,     0,   -48,
     -48,     0,     0,     0,     0,    99,     0,     0,   -48,   -48,
       0,   -48,   -48,   -48,     0,     0,     0,     0,   -48,   -48,
       3,     0,    34,    99,    46,    47,     0,     2,    48,    49,
      50,    51,     0,    52,   -48,     0,     0,     0,     0,     0,
       0,    53,     0,     0,     0,    54,    55,     0,     0,     0,
       0,     0,     0,     0,    56,   -48,     0,   -48,   -48,   -48,
       0,     0,     0,     0,   -48,   -48,     3,    46,    47,     0,
       0,    48,    49,    50,    51,     0,   100,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,     0,    56,   101,     0,
     102,   103,   104,     0,     0,    46,    47,   105,   106,    48,
      49,    50,    51,   113,    52,     0,     0,     0,     0,     0,
       0,     0,    53,     0,    46,    47,    54,    55,    48,    49,
      50,    51,     0,    52,     0,    56,     0,   161,     0,     0,
       0,    53,     0,    46,    47,    54,    55,    48,    49,    50,
      51,     0,    52,     0,    56,     0,     0,     0,     0,     0,
      53,     0,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,    56
};

static const yytype_int16 yycheck[] =
{
      28,    35,     0,    52,    47,    72,    16,    41,     6,     0,
      18,    39,    40,    21,    22,     6,    24,    25,    12,     5,
      21,     4,     4,    51,    52,    53,    54,    55,    56,    27,
      21,     0,    18,    19,    20,    21,    22,    38,    24,    25,
      83,    32,     0,     1,    72,    31,    32,    38,     6,   116,
       1,   100,    16,     7,    82,     6,    12,    85,    86,    87,
      88,    89,    13,    45,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    71,     4,   103,     6,    31,     4,    87,
     157,   158,    16,   160,    12,    18,    16,    45,   116,    43,
      16,    24,    25,     6,    45,   172,    10,   146,    11,    10,
      14,    87,    17,    14,   138,    14,    23,   135,   136,   100,
      17,    23,     4,    16,    16,    45,    13,   151,    11,    17,
      16,     6,    13,    13,    18,   153,     4,   155,    10,    10,
      10,    17,    16,     5,   162,    11,    13,    16,    12,     6,
     138,    11,    31,    15,    71,   173,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     5,    16,    16,    35,   109,   173,    11,    19,    -1,
      -1,    -1,    -1,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    -1,     5,    18,    19,    20,    21,    22,    -1,
      24,    25,    -1,    -1,     5,    -1,    18,    19,    20,    21,
      22,    -1,    24,    25,    -1,    87,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    87,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,     5,    -1,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    87,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    87,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    87,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    18,    19,    20,    21,
      22,     5,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    18,    19,    20,    21,    22,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    87,     3,     4,
      -1,     6,     7,     8,     9,    10,    -1,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    87,    -1,    -1,    33,    34,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,     1,    87,     3,     4,    -1,     6,     7,     8,
       9,    10,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,     3,     4,    -1,
      -1,     7,     8,     9,    10,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      36,    37,    38,    -1,    -1,     3,     4,    43,    44,     7,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,     3,     4,    24,    25,     7,     8,
       9,    10,    -1,    12,    -1,    33,    -1,    16,    -1,    -1,
      -1,    20,    -1,     3,     4,    24,    25,     7,     8,     9,
      10,    -1,    12,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    45,    91,    92,    93,    94,    95,    16,
       4,    96,    97,     0,    92,     4,    16,    98,    99,   101,
      16,    12,     4,    95,    99,   113,   114,    10,    14,   100,
      16,    17,    12,   104,     1,    94,    95,   111,   112,    23,
      23,    17,    11,    94,   102,   103,     3,     4,     7,     8,
       9,    10,    12,    20,    24,    25,    33,   115,   116,    98,
     111,    16,   113,    16,    13,   111,   115,   115,   113,    99,
      11,    17,    10,   100,   115,   115,   116,   117,   115,   115,
     115,   115,     5,    15,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    87,
      12,    34,    36,    37,    38,    43,    44,   104,   105,   106,
     115,    16,   102,    11,   117,    11,    17,    13,    13,   115,
     100,     4,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,    10,    10,   115,    10,    16,
      16,    13,   105,    16,    11,   117,    17,   115,   115,    16,
      16,    94,   107,   108,   113,    12,   116,    11,    11,   113,
      11,    16,   109,   115,    16,   106,   106,    16,   106,   110,
     115,    16,    35,    17,   106,   110
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    92,    93,    93,    93,    93,    93,
      94,    95,    95,    96,    96,    97,    98,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   103,   104,   105,   105,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   107,
     108,   108,   108,   109,   109,   110,   110,   110,   111,   111,
     111,   112,   112,   112,   113,   113,   114,   114,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   116,   116,   117,   117
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     2,     2,
       1,     5,     3,     0,     1,     1,     1,     3,     1,     2,
       3,     4,     4,     3,     1,     3,     2,     4,     0,     2,
       2,     1,     3,     5,     7,     5,     2,     2,     5,     3,
       2,     3,     1,     2,     1,     1,     3,     0,     0,     2,
       2,     3,     2,     0,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     3,     2,     2,
       4,     3,     1,     1,     1,     1,     1,     2,     3,     3,
       1,     5,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex ();
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
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 72 "zyp.y" /* yacc.c:1646  */
    { 
                display((yyvsp[0].ptr),0); 
                semantic_Analysis0((yyvsp[0].ptr));
                }
#line 1665 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 77 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1671 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 78 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,EXT_DEF_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1677 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 80 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,EXT_VAR_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));;}
#line 1683 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 81 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(3,FUNC_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1689 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 82 "zyp.y" /* yacc.c:1646  */
    {}
#line 1695 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 84 "zyp.y" /* yacc.c:1646  */
    {
                (yyval.ptr)=mknode(1,VAR_STRUCT_DEF,yylineno,(yyvsp[-1].ptr));
        }
#line 1703 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 87 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1709 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 91 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,TYPE,yylineno);
        strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));
        if(strcmp((yyvsp[0].type_id),"int")==0) (yyval.ptr)->type=INT;
        else if(strcmp((yyvsp[0].type_id),"float")==0) (yyval.ptr)->type=FLOAT;
        else if(strcmp((yyvsp[0].type_id),"char")==0) (yyval.ptr)->type=CHAR;
        else if(strcmp((yyvsp[0].type_id),"string")==0) (yyval.ptr)->type=STRING;
        }
#line 1721 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 102 "zyp.y" /* yacc.c:1646  */
    {
                        if((yyvsp[-3].ptr))
                        {
                                (yyval.ptr)=mknode(2,STRUCTDEF,yylineno,(yyvsp[-3].ptr),(yyvsp[-1].ptr));
                                strcpy((yyval.ptr)->type_id,(yyvsp[-3].ptr)->type_id);
                        }
                        else 
                        (yyval.ptr)=mknode(1,STRUCTDEF,yylineno,(yyvsp[-1].ptr));
                        
                }
#line 1736 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 113 "zyp.y" /* yacc.c:1646  */
    {
                        (yyval.ptr)=mknode(2,STRUCTDEC,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));
                }
#line 1744 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1750 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 119 "zyp.y" /* yacc.c:1646  */
    {
                        (yyval.ptr)=mknode(0,STRUCT_NAME,yylineno);
                        strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));
                }
#line 1759 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 124 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,STRUCT_NAME,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1765 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 126 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1771 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 127 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,EXT_DEC_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1777 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 130 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1783 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 132 "zyp.y" /* yacc.c:1646  */
    {
                (yyval.ptr)=mknode(1,ARRAYLIST,yylineno,(yyvsp[0].ptr));
                strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));
        }
#line 1792 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 137 "zyp.y" /* yacc.c:1646  */
    { (yyval.ptr)=(yyvsp[-1].ptr);}
#line 1798 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "zyp.y" /* yacc.c:1646  */
    {
                (yyval.ptr)=mknode(2,ARRAYLIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));
        }
#line 1806 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 144 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FUNC_DEC,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 1812 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 145 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,FUNC_DEC,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-2].type_id));(yyval.ptr)->ptr[0]=NULL;}
#line 1818 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 148 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,PARAM_LIST,yylineno,(yyvsp[0].ptr));}
#line 1824 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 149 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PARAM_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1830 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 151 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PARAM_DEC,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1836 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 154 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,COMP_STM,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1842 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 156 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL; }
#line 1848 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 157 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STM_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1854 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 161 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,EXP_STMT,yylineno,(yyvsp[-1].ptr));}
#line 1860 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 162 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1866 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 163 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,RETURN,yylineno,(yyvsp[-1].ptr));}
#line 1872 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 164 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,IF_THEN,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1878 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 165 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(3,IF_THEN_ELSE,yylineno,(yyvsp[-4].ptr),(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1884 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 166 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,WHILE,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1890 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 167 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,CONTINUE,yylineno);strcpy((yyval.ptr)->type_id,"CONTINUE");}
#line 1896 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 168 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,BREAK,yylineno);strcpy((yyval.ptr)->type_id,"BREAK");}
#line 1902 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 170 "zyp.y" /* yacc.c:1646  */
    {
              (yyval.ptr)=mknode(2,FOR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));
              strcpy((yyval.ptr)->type_id,"FOR");
      }
#line 1911 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 175 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(3,FOR_DEC,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"FOR_DEC");}
#line 1917 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 178 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FOR_DEC1,yylineno,(yyvsp[-1].ptr));}
#line 1923 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 179 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,FOR_DEC1,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1929 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 180 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1935 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 182 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FOR_DEC2,yylineno,(yyvsp[-1].ptr));}
#line 1941 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 183 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1947 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 185 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FOR_DEC3,yylineno,(yyvsp[0].ptr));}
#line 1953 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 186 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,FOR_DEC3,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1959 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 187 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1965 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 189 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL; }
#line 1971 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 190 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DEF_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1977 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 191 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=NULL;}
#line 1983 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 193 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,VAR_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1989 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 194 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,VAR_STRUCT_DEF,yylineno,(yyvsp[-1].ptr));}
#line 1995 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 197 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,DEC_LIST,yylineno,(yyvsp[0].ptr));}
#line 2001 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 198 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DEC_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 2007 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 200 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 2013 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 202 "zyp.y" /* yacc.c:1646  */
    {
               (yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));
               strcpy((yyval.ptr)->type_id,"=");
        }
#line 2022 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 207 "zyp.y" /* yacc.c:1646  */
    {
                (yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));
                strcpy((yyval.ptr)->type_id,"=");
        }
#line 2031 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 213 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"=");}
#line 2037 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 214 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PLUSASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"PLUSASSIGNOP");}
#line 2043 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 215 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,MINUSASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MINUSASSIGNOP");}
#line 2049 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 216 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STARASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"STARASSIGNOP");}
#line 2055 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 217 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DIVASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DIVASSIGNOP");}
#line 2061 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 218 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,MODASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MODASSIGNOP");}
#line 2067 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 219 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,AND,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"AND");}
#line 2073 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 220 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,OR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"OR");}
#line 2079 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 221 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,RELOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 2085 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 222 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,PLUS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"PLUS");}
#line 2091 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 223 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,MINUS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MINUS");}
#line 2097 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 224 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,STAR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"STAR");}
#line 2103 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 225 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DIV");}
#line 2109 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 226 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,MOD,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MOD");}
#line 2115 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 227 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,AUTOPLUS,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id, "LPAUTOPLUS");}
#line 2121 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 228 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,AUTOMINUS,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id, "LPAUTOMINUS");}
#line 2127 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 229 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,AUTOPLUS,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id, "RPAUTOPLUS");}
#line 2133 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 230 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,AUTOMINUS,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,"RPAUTOMINUS");}
#line 2139 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 232 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[-1].ptr);}
#line 2145 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 233 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,UMINUS,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"UMINUS");}
#line 2151 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 234 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,NOT,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"NOT");}
#line 2157 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 235 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,FUNC_CALL,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 2163 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 236 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,FUNC_CALL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-2].type_id));}
#line 2169 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 237 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 2175 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 238 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,CHAR,yylineno);strcpy((yyval.ptr)->type_char,(yyvsp[0].type_char));(yyval.ptr)->type=CHAR;}
#line 2181 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 239 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[0].type_int);(yyval.ptr)->type=INT;}
#line 2187 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 240 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,FLOAT,yylineno);(yyval.ptr)->type_float=(yyvsp[0].type_float);(yyval.ptr)->type=FLOAT;}
#line 2193 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 241 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(0,STRING,yylineno);strcpy((yyval.ptr)->type_string,(yyvsp[0].type_string));}
#line 2199 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 242 "zyp.y" /* yacc.c:1646  */
    {
                         (yyval.ptr)=mknode(1,ARRAY_VISIT,yylineno,(yyvsp[0].ptr));
                         strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));
                        }
#line 2208 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 246 "zyp.y" /* yacc.c:1646  */
    {
                                (yyval.ptr)=mknode(1,STRUCTVI,yylineno,(yyvsp[-2].ptr));
                                strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));
                       }
#line 2217 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 251 "zyp.y" /* yacc.c:1646  */
    {
                                (yyval.ptr)=(yyvsp[-1].ptr);
                        }
#line 2225 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 254 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 2231 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 258 "zyp.y" /* yacc.c:1646  */
    {
                (yyval.ptr)=mknode(2,ARGSLIST,yylineno,(yyvsp[-3].ptr),(yyvsp[0].ptr));
                
        }
#line 2240 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 263 "zyp.y" /* yacc.c:1646  */
    {
                (yyval.ptr)=mknode(1,ARGSLIST,yylineno,(yyvsp[-1].ptr));
        }
#line 2248 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 266 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(2,ARGS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 2254 "zyp.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 267 "zyp.y" /* yacc.c:1646  */
    {(yyval.ptr)=mknode(1,ARGS,yylineno,(yyvsp[0].ptr));}
#line 2260 "zyp.tab.c" /* yacc.c:1646  */
    break;


#line 2264 "zyp.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 270 "zyp.y" /* yacc.c:1906  */


int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
	return 0;
}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
