/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 15 "zyp.y" /* yacc.c:1909  */

	int    type_int;
        char   type_char[32];
	float  type_float;
	char   type_id[32];
        char   type_string[32];
	struct ASTNode *ptr;

#line 153 "zyp.tab.h" /* yacc.c:1909  */
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
