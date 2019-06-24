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
#line 2 "compiler_hw3.y" /* yacc.c:339  */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define BUF_SIZE 256

extern int yylineno;
extern int yylex();
extern char *yytext; // Get current token from lex
extern char buf[BUF_SIZE]; // Get current code line from lex
extern char* yytext;   // Get current token from lex

int SCOPE = 0;
int symbol_num = 0;
int err_flag = 0;	/* 0: no error;  
					   1: syntatic error; 
					   2: Re-declarations and un-declaration variables / functions;  
					   3: Arithmetic error or Function error
					*/
char err_message[50]  = {0};
char err_symbol[BUF_SIZE] = {0};
char params[BUF_SIZE] = {0};	// parameters's type
int param_index[50] = {0};
int param_num = 0;
int dump_flag = 0;
int add_scope = 0;	// if = 1, the increment will be cancel out, so no need to decrease SCOPE	

int func_flag = 0;	// enter function
int func_reg = 0;	// number of variables in function definition
char func_reg_type[50] = {0}; // type of parameters in the form of jasmin type descriptoir
char return_type = 0;
int reg = 0;
char reg_type[50][10] = {0};
char operand_type = 0;	// operand type
char relation_type = 0;

int if_num[50] = {0};	// number of if in each scope
int if_branch_num[50] = {0};	// number of branches in current if in each scope
int if_end_flag[50] = {0};	// whether current branch should be ended later
int if_exit_flag[50] = {0};	// whether current if should exit later
int while_num[50] = {0};	// number of while in each scope
int while_exit_flag[50] = {0};	// whether current while should exit later
int zero_flag = 0;

FILE *file; // To generate .j file for Jasmin

/* symbol table struct */
struct symbol{
	int index;
	char name[256];
	char kind[10];
	char data_type[10];
	int scope;
	char attribute[256];
	int forward;
	int reg;
}**symbol_table;

/* error functions */
void yyerror(char *s);
void semantic_error();
void error_type(int flag, char *type, char *symbol);

/* symbol table functions */
int lookup_symbol(char *name, int scope, int symbol_num);
void create_symbol(int entry_num);
void insert_symbol(int index, char *name, char *kind, char *data_type, int scope, char *attribute, int forward, int reg);
void dump_symbol();

/* get info */
char* get_type(char *name, int scope, int symbol_num);
char* get_attribute(char *name, int scope, int symbol_num);
int get_register(struct symbol **table, char *name, int scope, int symbol_num);

/* code generation functions, just an example! */
void gencode_function(char* code);


#line 149 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    MOD = 262,
    INC = 263,
    DEC = 264,
    MT = 265,
    LT = 266,
    MTE = 267,
    LTE = 268,
    EQ = 269,
    NE = 270,
    AND = 271,
    OR = 272,
    NOT = 273,
    LB = 274,
    RB = 275,
    LCB = 276,
    RCB = 277,
    LSB = 278,
    RSB = 279,
    COMMA = 280,
    QUOTA = 281,
    PRINT = 282,
    IF = 283,
    ELSE = 284,
    FOR = 285,
    WHILE = 286,
    RET = 287,
    CONT = 288,
    BREAK = 289,
    NEWLINE = 290,
    SEMICOLON = 291,
    I_CONST = 292,
    TRUE = 293,
    FALSE = 294,
    F_CONST = 295,
    STR_CONST = 296,
    ID = 297,
    INT = 298,
    FLOAT = 299,
    BOOL = 300,
    STRING = 301,
    VOID = 302,
    ASGN = 303,
    ADDASGN = 304,
    SUBASGN = 305,
    MULASGN = 306,
    DIVASGN = 307,
    MODASGN = 308
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define MOD 262
#define INC 263
#define DEC 264
#define MT 265
#define LT 266
#define MTE 267
#define LTE 268
#define EQ 269
#define NE 270
#define AND 271
#define OR 272
#define NOT 273
#define LB 274
#define RB 275
#define LCB 276
#define RCB 277
#define LSB 278
#define RSB 279
#define COMMA 280
#define QUOTA 281
#define PRINT 282
#define IF 283
#define ELSE 284
#define FOR 285
#define WHILE 286
#define RET 287
#define CONT 288
#define BREAK 289
#define NEWLINE 290
#define SEMICOLON 291
#define I_CONST 292
#define TRUE 293
#define FALSE 294
#define F_CONST 295
#define STR_CONST 296
#define ID 297
#define INT 298
#define FLOAT 299
#define BOOL 300
#define STRING 301
#define VOID 302
#define ASGN 303
#define ADDASGN 304
#define SUBASGN 305
#define MULASGN 306
#define DIVASGN 307
#define MODASGN 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 85 "compiler_hw3.y" /* yacc.c:355  */

	int i_val;
    double f_val;
	char string[696];

#line 301 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 318 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   128,   132,   133,   134,   135,   136,   137,
     166,   266,   323,   434,   478,   507,   508,   512,   513,   517,
     518,   611,   729,   805,   806,   807,   808,   809,   813,   817,
     818,   822,   823,   827,   828,   838,   848,   856,   866,   876,
     889,   903,   917,   928,   939,  1009,  1010,  1023,  1039,  1040,
    1053,  1073,  1096,  1097,  1101,  1102,  1106,  1107,  1108,  1112,
    1113,  1152,  1218,  1253,  1291,  1292,  1296,  1339,  1384,  1393,
    1434,  1588,  1738,  1763,  1772,  1773,  1774,  1782,  1821,  1831,
    1841,  1851,  1948,  1953,  1954,  1955,  1956,  1957,  1961,  1962,
    1966,  2010,  2011,  2015,  2019,  2140,  2166,  2191,  2199,  2208,
    2222,  2223,  2224,  2225,  2226
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "MOD", "INC",
  "DEC", "MT", "LT", "MTE", "LTE", "EQ", "NE", "AND", "OR", "NOT", "LB",
  "RB", "LCB", "RCB", "LSB", "RSB", "COMMA", "QUOTA", "PRINT", "IF",
  "ELSE", "FOR", "WHILE", "RET", "CONT", "BREAK", "NEWLINE", "SEMICOLON",
  "I_CONST", "TRUE", "FALSE", "F_CONST", "STR_CONST", "ID", "INT", "FLOAT",
  "BOOL", "STRING", "VOID", "ASGN", "ADDASGN", "SUBASGN", "MULASGN",
  "DIVASGN", "MODASGN", "$accept", "program", "stat", "declaration",
  "expression_stat", "expr", "assignment_expr", "opassign_operand",
  "opassign_operator", "conditional_expr", "logical_or_expr",
  "logical_and_expr", "relational_expr", "relational_operand",
  "additive_expr", "multiplicative_expr", "cast_expr", "unary_expr",
  "unary_operator", "postfix_expr", "primary_expr", "compound_stat",
  "while", "jump_stat", "print_func", "initializer", "parameter_list",
  "parameter", "argument_list", "argument", "val", "type", YY_NULLPTR
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
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -42

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-42)))

#define YYTABLE_NINF -87

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -42,    28,   -42,   -42,   -42,   -42,   104,   -26,   -13,    -7,
     -42,   149,   -16,    13,   -42,   -42,    99,   114,   279,   285,
     -42,    86,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
      15,   -42,   184,   -42,    41,    87,   -42,   291,    85,   208,
     -42,   -42,   161,   -42,   -42,   -42,    96,   -42,   -42,   -42,
      64,   -18,   110,    65,   120,   201,   -42,    66,   -42,   -42,
     -42,   -42,   155,   201,   201,   -42,   -42,   -42,   -42,   -42,
     -42,   201,   207,   207,   276,   276,   276,   276,   276,   276,
     161,   161,   161,   161,   161,   -42,   -42,   -42,   -42,     0,
     -42,   201,   -15,   -42,   161,   -42,   113,   136,   143,   150,
     162,    32,   -42,   -42,   115,   146,   -42,   -42,   -42,   -42,
     260,    87,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   208,   208,   -42,   -42,   -42,   152,
      -9,   -42,   213,   -42,   201,   -42,   -42,   -42,   -42,   148,
     -42,   201,   163,     8,   156,   -42,   164,     3,    12,   246,
     252,   172,    68,   115,   173,   158,   -42,   -42,   -42,   -42,
     -42,     9,   240,   -42,   -42,   -42,   197,   -42,   -42,   -42,
     -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,    56,    57,    58,     0,    72,     0,     0,
      73,     0,     0,     0,     9,    15,    95,    98,    99,    96,
      97,    94,   100,   101,   102,   103,   104,     2,     4,     5,
       0,    17,     0,    19,    28,    29,    31,     0,    33,    45,
      48,    52,     0,    54,    59,     6,     0,     7,     8,    64,
       0,     0,     0,     0,     0,     0,    76,     0,    74,    75,
      62,    63,     0,     0,     0,    16,    23,    24,    25,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,    98,    99,    96,    94,
      55,     0,     0,    65,     0,    68,     0,     0,     0,     0,
       0,     0,    77,    60,    93,     0,    91,    20,    18,    21,
      94,    30,    32,    40,    42,    43,    41,    44,    37,    36,
      39,    38,    34,    35,    46,    47,    49,    50,    51,     0,
       0,    12,     0,    53,     0,    78,    79,    80,    81,     0,
      61,     0,     0,     0,     0,    88,     0,    95,    98,    99,
      96,    97,    94,    87,     0,     0,    66,    92,    69,    71,
      14,     0,     0,    90,    11,    10,     0,    70,    13,    89,
      67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -42,   -42,   -42,   -42,   -42,    -1,    21,   -42,   -42,   -42,
     -42,   151,   154,   233,   -42,    74,   -41,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,    59,   -42,    81,
     -42,   206
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    27,    28,    29,   104,    31,    32,    71,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,   154,   144,   145,   105,   106,
      49,   146
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    90,    93,    53,   130,    51,    54,    64,    60,    61,
      57,   143,    55,   -40,   -40,   -40,   -40,   -40,   -40,    62,
      58,   131,   -42,   -42,   -42,   -42,   -42,   -42,     2,   159,
     167,     3,     4,   132,    22,    23,    24,    25,    26,   -83,
      64,   126,   127,   128,   160,   168,     5,     6,   -85,    59,
       7,    65,   139,   133,   101,     8,     9,    64,    72,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    60,    61,   -44,   -44,
     -44,   -44,   -44,   -44,   107,   108,    95,    62,    80,    81,
     129,    64,   109,    96,    60,    61,   -44,   -44,   -44,   -44,
     -44,   -44,   102,    73,   -82,    62,    92,     3,     4,   -40,
     -40,   -40,   -40,   -40,   -40,    91,    63,   -22,   -22,   -22,
     -22,   -22,     5,     6,   -42,   -42,   -42,   -42,   -42,   -42,
      94,   153,   134,   155,    63,   -22,   -22,   -22,   -22,   -22,
      64,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     3,     4,   124,   125,   135,    97,     3,     4,
      98,    99,   100,   136,     3,     4,   140,     5,     6,   156,
     137,   141,   142,     5,     6,   103,   161,    64,   166,     5,
       6,   162,   138,    64,   158,    56,    16,    17,    18,    19,
      20,    21,    16,    17,    18,    19,    20,    21,    85,    86,
      87,    88,    20,    89,     3,     4,   163,    50,   164,   165,
       3,     4,    52,    82,    83,    84,     3,     4,   170,     5,
       6,   169,   157,   111,     0,     5,     6,   112,     0,     0,
       0,     5,     6,    66,    67,    68,    69,    70,    16,    17,
      18,    19,    20,    21,    16,    17,    18,    19,    20,   110,
     147,   148,   149,   150,   151,   152,   -43,   -43,   -43,   -43,
     -43,   -43,   -41,   -41,   -41,   -41,   -41,   -41,    60,    61,
     -44,   -44,   -44,   -44,   -44,   -44,     0,     0,     0,    62,
       0,     0,   -86,    22,    23,    24,    25,    26,   -84,   -43,
     -43,   -43,   -43,   -43,   -43,   -41,   -41,   -41,   -41,   -41,
     -41,    74,    75,    76,    77,    78,    79,   118,   119,   120,
     121,   122,   123,   113,   114,   115,   116,     0,   117
};

static const yytype_int16 yycheck[] =
{
       1,    42,    20,    29,    19,     6,    19,    25,     8,     9,
      11,    20,    19,    10,    11,    12,    13,    14,    15,    19,
      36,    36,    10,    11,    12,    13,    14,    15,     0,    21,
      21,     3,     4,    48,    43,    44,    45,    46,    47,    36,
      25,    82,    83,    84,    36,    36,    18,    19,    36,    36,
      22,    36,    20,    94,    55,    27,    28,    25,    17,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     8,     9,    10,    11,
      12,    13,    14,    15,    63,    64,    21,    19,     3,     4,
      91,    25,    71,    28,     8,     9,    10,    11,    12,    13,
      14,    15,    36,    16,    36,    19,    42,     3,     4,    10,
      11,    12,    13,    14,    15,    19,    48,    49,    50,    51,
      52,    53,    18,    19,    10,    11,    12,    13,    14,    15,
      20,   132,    19,   134,    48,    49,    50,    51,    52,    53,
      25,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     3,     4,    80,    81,    20,    37,     3,     4,
      40,    41,    42,    20,     3,     4,    20,    18,    19,    21,
      20,    25,    20,    18,    19,    20,    20,    25,    20,    18,
      19,    25,    20,    25,    21,    36,    37,    38,    39,    40,
      41,    42,    37,    38,    39,    40,    41,    42,    37,    38,
      39,    40,    41,    42,     3,     4,    42,     1,    36,    36,
       3,     4,     6,     5,     6,     7,     3,     4,    21,    18,
      19,   162,   141,    72,    -1,    18,    19,    73,    -1,    -1,
      -1,    18,    19,    49,    50,    51,    52,    53,    37,    38,
      39,    40,    41,    42,    37,    38,    39,    40,    41,    42,
      37,    38,    39,    40,    41,    42,    10,    11,    12,    13,
      14,    15,    10,    11,    12,    13,    14,    15,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    -1,    19,
      -1,    -1,    36,    43,    44,    45,    46,    47,    36,    10,
      11,    12,    13,    14,    15,    10,    11,    12,    13,    14,
      15,    10,    11,    12,    13,    14,    15,    74,    75,    76,
      77,    78,    79,    37,    38,    39,    40,    -1,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,     0,     3,     4,    18,    19,    22,    27,    28,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    56,    57,    58,
      59,    60,    61,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    84,
      85,    59,    85,    29,    19,    19,    36,    59,    36,    36,
       8,     9,    19,    48,    25,    36,    49,    50,    51,    52,
      53,    62,    17,    16,    10,    11,    12,    13,    14,    15,
       3,     4,     5,     6,     7,    37,    38,    39,    40,    42,
      70,    19,    42,    20,    20,    21,    28,    37,    40,    41,
      42,    59,    36,    20,    59,    82,    83,    60,    60,    60,
      42,    65,    66,    37,    38,    39,    40,    42,    67,    67,
      67,    67,    67,    67,    69,    69,    70,    70,    70,    59,
      19,    36,    48,    70,    19,    20,    20,    20,    20,    20,
      20,    25,    20,    20,    80,    81,    85,    37,    38,    39,
      40,    41,    42,    59,    79,    59,    21,    83,    21,    21,
      36,    20,    25,    42,    36,    36,    20,    21,    36,    81,
      21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    61,    62,    62,    62,    62,    62,    63,    64,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    67,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    73,
      73,    73,    73,    73,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    76,    77,    77,    77,    77,    78,    78,
      78,    78,    79,    79,    79,    79,    79,    79,    80,    80,
      81,    82,    82,    83,    84,    84,    84,    84,    84,    84,
      85,    85,    85,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       5,     5,     3,     6,     5,     1,     2,     1,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       3,     3,     1,     4,     1,     2,     1,     1,     1,     1,
       3,     4,     2,     2,     1,     3,     5,     7,     3,     5,
       6,     5,     1,     1,     2,     2,     2,     3,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
#line 138 "compiler_hw3.y" /* yacc.c:1646  */
    { 
			if(strlen(buf) < 1)	// If there is no code in the line, don't print the blank after line number 
				printf("%d:\n",yylineno);
			else
				printf("%d: %s\n", yylineno, buf); 
			if(err_flag == 2 || err_flag ==3)
				semantic_error();
			if(dump_flag == 1)
			{
				dump_symbol(symbol_num,SCOPE);
				if(add_scope==0)
					--SCOPE;
				dump_flag = 0;	// reset
				add_scope = 0;	// reset
				if(func_flag==1 && SCOPE==0)
					func_flag = 0;
			}
			if(func_flag==0)
				func_reg  = 0;
			memset(buf, 0, sizeof(buf));	// Clear buffer
			operand_type = 0;
			relation_type = 0;
			zero_flag = 0;
		}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 167 "compiler_hw3.y" /* yacc.c:1646  */
    {			
			if(lookup_symbol((yyvsp[-3].string), SCOPE, symbol_num) != -2)
			{	
				char tmp[32];
				if(SCOPE==0)
				{
					insert_symbol(symbol_num, (yyvsp[-3].string), "variable", (yyvsp[-4].string), SCOPE, NULL, 0, -1);
					gencode_function(".field public static ");
                    gencode_function((yyvsp[-3].string));
                    gencode_function(" ");
					if(strcmp((yyvsp[-4].string),"int")==0){
                        gencode_function("I = ");
                        sprintf(tmp, "%d\n", (int)(yyvsp[-1].f_val));
                        gencode_function(tmp);
					}else if(strcmp((yyvsp[-4].string), "float")==0){
						gencode_function("F = ");
                        sprintf(tmp, "%f\n", (double)(yyvsp[-1].f_val));
                        gencode_function(tmp);
					}else if(strcmp((yyvsp[-4].string), "bool")==0){
						gencode_function("Z = ");
                        sprintf(tmp, "%d\n", (int)(yyvsp[-1].f_val));
                        gencode_function(tmp);
					}	
				}
				else
				{
					if(func_flag==1)
					{
						insert_symbol(symbol_num, (yyvsp[-3].string), "variable", (yyvsp[-4].string), SCOPE, NULL, 0, func_reg);
						if(strcmp((yyvsp[-4].string),"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)(yyvsp[-1].f_val));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-4].string), "float")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)(yyvsp[-1].f_val));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-4].string), "bool")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)(yyvsp[-1].f_val));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						++func_reg;
					}
					else
					{	
						insert_symbol(symbol_num, (yyvsp[-3].string), "variable", (yyvsp[-4].string), SCOPE, NULL, 0, reg);
						if(strcmp((yyvsp[-4].string),"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)(yyvsp[-1].f_val));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-4].string), "float")==0)
						{	

							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)(yyvsp[-1].f_val));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-4].string), "bool")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)(yyvsp[-1].f_val));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						++reg;
					}
				}
				++symbol_num;
			}
			else 
			{
				error_type(2,"Redeclared variable",(yyvsp[-3].string));
			}
		}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 267 "compiler_hw3.y" /* yacc.c:1646  */
    {			
			if(lookup_symbol((yyvsp[-3].string), SCOPE, symbol_num) != -2)
			{
				char tmp[32];
				if(SCOPE==0)
				{
					insert_symbol(symbol_num, (yyvsp[-3].string), "variable", (yyvsp[-4].string), SCOPE, NULL, 0, -1);
					if(strcmp((yyvsp[-4].string),"string")==0)
					{	
						gencode_function(".field public static ");
                        gencode_function((yyvsp[-3].string));
                        gencode_function(" ");
                        gencode_function("Ljava/lang/String; = ");
                        sprintf(tmp, "\"%s\"", (yyvsp[-1].string));
                        gencode_function(tmp);
                        gencode_function("\n");	
					}
				}
				else
				{
					if(func_flag == 1)
					{
						insert_symbol(symbol_num, (yyvsp[-3].string), "variable", (yyvsp[-4].string), SCOPE, NULL, 0, func_reg);
						if(strcmp((yyvsp[-4].string),"string")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "\"%s\"\n", (yyvsp[-1].string));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);	
						}
						++func_reg;
					}
					else
					{
						insert_symbol(symbol_num, (yyvsp[-3].string), "variable", (yyvsp[-4].string), SCOPE, NULL, 0, reg);
						if(strcmp((yyvsp[-4].string),"string")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "\"%s\"\n", (yyvsp[-1].string));
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						++reg;
					}
				}
				++symbol_num;
			}
			else 
			{
				error_type(2,"Redeclared variable",(yyvsp[-3].string));
			}
		}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 324 "compiler_hw3.y" /* yacc.c:1646  */
    {			
			if(lookup_symbol((yyvsp[-1].string), SCOPE, symbol_num) != -2)
			{
				char tmp[32];
				if(SCOPE==0)
				{
					insert_symbol(symbol_num, (yyvsp[-1].string), "variable", (yyvsp[-2].string), SCOPE, NULL, 0, -1);
					gencode_function(".field public static ");
                    gencode_function((yyvsp[-1].string));
                    gencode_function(" ");
					if(strcmp((yyvsp[-2].string),"int")==0)
						gencode_function("I\n");
					else if(strcmp((yyvsp[-2].string), "float")==0)
						gencode_function("F\n");
					else if(strcmp((yyvsp[-2].string), "bool")==0)
						gencode_function("Z\n");
					else if(strcmp((yyvsp[-2].string), "void")==0)
						gencode_function("V\n");
					else if(strcmp((yyvsp[-2].string), "string")==0)
						gencode_function("Ljava/lang/String;\n");
				}
				else
				{
					if(func_flag == 1)
					{
						insert_symbol(symbol_num, (yyvsp[-1].string), "variable", (yyvsp[-2].string), SCOPE, NULL, 0, func_reg);
						if(strcmp((yyvsp[-2].string),"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-2].string), "float")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-2].string), "bool")==0)
						{
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-2].string), "string")==0)
						{	
							gencode_function("\tldc \"\"\n");
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						++func_reg;
					}
					else
					{
						insert_symbol(symbol_num, (yyvsp[-1].string), "variable", (yyvsp[-2].string), SCOPE, NULL, 0, reg);
						if(strcmp((yyvsp[-2].string),"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-2].string), "float")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-2].string), "bool")==0)
						{
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp((yyvsp[-2].string), "string")==0)
						{	
							gencode_function("\tldc \"\"\n");
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						++reg;
					}
				}
				++symbol_num;
			}
			else
			{
				error_type(2,"Redeclared variable",(yyvsp[-1].string));
			}
		}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 435 "compiler_hw3.y" /* yacc.c:1646  */
    {			
			int lookup_result = lookup_symbol((yyvsp[-4].string), SCOPE, symbol_num);
			if(lookup_result == -2 ||  (lookup_result >= 0 && symbol_table[lookup_result]->forward==1))
			{
				error_type(2,"Redeclared function",(yyvsp[-4].string));
			}

			/* Dont't insert parameters to table when function declaration */
			for(int i=0; i<param_num; ++i)
			{
				memset(symbol_table[param_index[i]], 0, sizeof(struct symbol));
				symbol_table[param_index[i]]->scope = -1;
			}
			symbol_num -= param_num;
			param_num = 0;
		
			lookup_result = lookup_symbol((yyvsp[-4].string), SCOPE, symbol_num);
			/* Insert funcion */
			if(lookup_result != -2 && lookup_result < 0)
			{
				char temp[256] = {0};
				strncpy(temp,params,strlen(params)-2);
				insert_symbol(symbol_num, (yyvsp[-4].string), "function", (yyvsp[-5].string), SCOPE, temp, 1, -1);
				++symbol_num;
			}
			else if(lookup_result>=0 && symbol_table[lookup_result]->forward==2)
			{
				char temp[256] = {0};
				strncpy(temp,params,strlen(params)-2);
	
				if(strcmp((yyvsp[-5].string), symbol_table[lookup_result]->data_type)!=0)
				{
					error_type(3,"function return type does not match","");
				}
				else if(strcmp(temp, symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
				}
	
			}
			memset(params,0,sizeof(params));
			memset(param_index,0,sizeof(param_index));
		}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 479 "compiler_hw3.y" /* yacc.c:1646  */
    {			
			int lookup_result = lookup_symbol((yyvsp[-3].string), SCOPE, symbol_num);
			if(lookup_result == -2 || (lookup_result >= 0 && symbol_table[lookup_result]->forward==1))
			{
				error_type(2,"Redeclared function",(yyvsp[-3].string));
			}
			else if(lookup_result!=-2 && lookup_result<0)
			{
				insert_symbol(symbol_num, (yyvsp[-3].string), "function", (yyvsp[-4].string), SCOPE, NULL, 1, -1);
				++symbol_num;
			}
			else if(lookup_result>=0 && symbol_table[lookup_result]->forward==2)
			{
				if(strcmp((yyvsp[-4].string), symbol_table[lookup_result]->data_type)!=0)
				{
					error_type(3,"function return type does not match","");
				}
				else if(strlen(symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
				}
	
			}
		}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 517 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 519 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			int lookup_result = lookup_symbol((yyvsp[-2].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[-2].string));
			}
			else
			{
				int reg = get_register(symbol_table, (yyvsp[-2].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{
					fprintf(file, "\tputstatic compiler_hw3/%s ", (yyvsp[-2].string));  // putstatic -> stored
					char type[10] = {0};
					strcpy(type, get_type((yyvsp[-2].string), SCOPE, symbol_num));
					if(strcmp(type,"int")==0)
					{
						gencode_function("I\n");
					}
					else if(strcmp(type,"float")==0)
					{
						gencode_function("F\n");
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("Z\n");
					}
					else if(strcmp(type, "string")==0)
					{	
						gencode_function("Ljava/lang/String;\n");	
					}
				}
				else	// local variable
				{
					if(strcmp(reg_type[reg],"int")==0)
					{
						if(operand_type == 'I')
						{
							gencode_function("\tistore ");
							sprintf(tmp,"%d\n",reg);
							gencode_function(tmp);
						}
						else if(operand_type == 'F')
						{
							gencode_function("\tf2i\n\tistore ");
							sprintf(tmp,"%d\n",reg);
							gencode_function(tmp);
						}
						else if(operand_type == 'Z')
						{
							gencode_function("\tistore ");
							sprintf(tmp,"%d\n",reg);
							gencode_function(tmp);
						}
					}
					else if(strcmp(reg_type[reg],"float")==0)
					{
						if(operand_type == 'F')
						{
							gencode_function("\tfstore ");
							sprintf(tmp,"%d\n",reg);
							gencode_function(tmp);
						}
						else if(operand_type == 'I')
						{
							gencode_function("\ti2f\n\tfstore ");
							sprintf(tmp,"%d\n",reg);
							gencode_function(tmp);
						}
						else if(operand_type == 'Z')
						{
							gencode_function("\ti2f\n\tfstore ");
							sprintf(tmp,"%d\n",reg);
							gencode_function(tmp);
						}
					}
					else if(strcmp(reg_type[reg],"bool")==0)
					{	
						gencode_function("\tistore ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);	
					}
					else if(strcmp(reg_type[reg], "string")==0)
					{	
						gencode_function("\tastore ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);	
					}
				}		
				operand_type = 0;
			}
		}
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 612 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			if(operand_type == 'I' || operand_type == 'Z')
			{	
				if(strcmp((yyvsp[-1].string), "+=")==0)
					gencode_function("\tiadd\n");
				else if(strcmp((yyvsp[-1].string), "-=")==0)
					gencode_function("\tisub\n");
				else if(strcmp((yyvsp[-1].string), "*=")==0)
					gencode_function("\timul\n");
				else if(strcmp((yyvsp[-1].string), "/=")==0)
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
						gencode_function("\tidiv\n");
				}
				else if(strcmp((yyvsp[-1].string), "%=")==0)
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
						gencode_function("\tirem\n");
				}
			}
			else if(operand_type == 'F')
			{
				if(strcmp((yyvsp[-1].string), "+=")==0)
					gencode_function("\tfadd\n");
				else if(strcmp((yyvsp[-1].string), "-=")==0)
					gencode_function("\tfsub\n");
				else if(strcmp((yyvsp[-1].string), "*=")==0)
					gencode_function("\tfmul\n");
				else if(strcmp((yyvsp[-1].string), "/=")==0)
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
						gencode_function("\tfdiv\n");
				}
				else if(strcmp((yyvsp[-1].string), "%=")==0)
					error_type(3,"Modulo operator(%) with floating point operands","");
			}
				
			int reg = get_register(symbol_table, (yyvsp[-2].string), SCOPE, symbol_num);
			if(reg==-1)		// global variable
			{
				fprintf(file, "\tputstatic compiler_hw3/%s ", (yyvsp[-2].string));
				char type[10] = {0};
				strcpy(type, get_type((yyvsp[-2].string), SCOPE, symbol_num));
				if(strcmp(type,"int")==0)
				{
					gencode_function("I\n");
				}
				else if(strcmp(type,"float")==0)
				{
					gencode_function("F\n");
				}
				else if(strcmp(type,"bool")==0)
				{
					gencode_function("Z\n");
				}
				else if(strcmp(type, "string")==0)
				{
					gencode_function("Ljava/lang/String;\n");	
				}
			}
			else	// local variable
			{
				if(strcmp(reg_type[reg],"int")==0)
				{
					if(operand_type=='I' || operand_type=='Z')
					{
						gencode_function("\tistore ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
					}
					else if(operand_type == 'F')
					{
						gencode_function("\tf2i\n\tistore ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
					}
				}
				else if(strcmp(reg_type[reg],"float")==0)
				{
					if(operand_type == 'F')
					{
						gencode_function("\tfstore ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
					}
					else if(operand_type=='I' || operand_type=='Z')
					{
						gencode_function("\ti2f\n\tfstore ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
					}
				}
				else if(strcmp(reg_type[reg],"bool")==0)
				{	
					gencode_function("\tistore ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);	
				}
				else if(strcmp(reg_type[reg], "string")==0)
				{	
					gencode_function("\tastore ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
			}
			operand_type = 0;
		}
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 730 "compiler_hw3.y" /* yacc.c:1646  */
    {
			strcpy((yyval.string), (yyvsp[0].string));
			int lookup_result = lookup_symbol((yyvsp[0].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[0].string));
			}
			else
			{
				char tmp[32];
				int reg = get_register(symbol_table, (yyvsp[0].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					char type[10] = {0};
					strcpy(type, get_type((yyvsp[0].string), SCOPE, symbol_num));
					gencode_function("\tgetstatic compiler_hw3/");	// getstatic -> loaded
					sprintf(tmp,"%s ", (yyvsp[0].string));
					gencode_function(tmp);
					if(strcmp(type,"int")==0)
					{
						gencode_function("I\n");
						operand_type = 'I';
					}
					else if(strcmp(type,"float")==0)
					{	
						gencode_function("F\n");
						operand_type = 'F';				
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("Z\n");
						operand_type = 'Z';
					}
					else if(strcmp(type, "string")==0)
					{
						gencode_function("Ljava/lang/String;\n");
						operand_type = 's';		
					}
				}
				else	// local variable
				{
					if(strcmp(reg_type[reg],"int")==0)
					{	
						gencode_function("\tiload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 'I';
					}
					else if(strcmp(reg_type[reg],"float")==0)
					{
						gencode_function("\tfload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 'F';
					}
					else if(strcmp(reg_type[reg],"bool")==0)
					{	
						gencode_function("\tiload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 'Z';
					}
					else if(strcmp(reg_type[reg], "string")==0)
					{	
						gencode_function("\taload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 's';
					}
				}
			}
		}
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 805 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string),"+="); }
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 806 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "-="); }
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 807 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "*="); }
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 808 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "/="); }
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 809 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "%="); }
#line 2262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 813 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 817 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 822 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 827 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 829 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'E';
		}
#line 2300 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 839 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'N';
		}
#line 2314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 849 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F')
				gencode_function("\tfsub\n");
			relation_type = 'l';
		}
#line 2326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 857 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'm';
		}
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 867 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'L';
		}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 877 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'M';
		}
#line 2368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 890 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			gencode_function("\tldc ");
			sprintf(tmp,"%d\n",(yyvsp[0].i_val));
			gencode_function(tmp);
			operand_type = 'I';
		}
#line 2386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 904 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			gencode_function("\tldc ");
			sprintf(tmp,"%f\n",(yyvsp[0].f_val));
			gencode_function(tmp);
			operand_type = 'F';
		}
#line 2404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 918 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			gencode_function("\tldc 1\n");
			operand_type = 'Z';
		}
#line 2419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 929 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			gencode_function("\tldc 0\n");
			operand_type = 'Z';
		}
#line 2434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 940 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}

			int lookup_result = lookup_symbol((yyvsp[0].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[0].string));
			}
			else
			{
				char tmp[32];
				int reg = get_register(symbol_table, (yyvsp[0].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					char type[10] = {0};
					strcpy(type, get_type((yyvsp[0].string), SCOPE, symbol_num));
					gencode_function("\tgetstatic compiler_hw3/");
					sprintf(tmp,"%s ",(yyvsp[0].string));
					gencode_function(tmp);
					if(strcmp(type,"int")==0)
					{
						gencode_function("I\n");
						operand_type = 'I';
					}
					else if(strcmp(type,"float")==0)
					{	
						gencode_function("F\n");			
						operand_type = 'F';
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("Z\n");
						operand_type = 'Z';
					}
				}
				else	// local variable
				{
					if(strcmp(reg_type[reg],"int")==0)
					{	
						gencode_function("\tiload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 'I';
					}
					else if(strcmp(reg_type[reg],"float")==0)
					{
						gencode_function("\tfload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 'F';
					}
					else if(strcmp(reg_type[reg],"bool")==0)
					{
						gencode_function("\tiload ");
						sprintf(tmp,"%d\n",reg);
						gencode_function(tmp);
						operand_type = 'Z';
					}
				}
			}
		}
#line 2505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1009 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1011 "compiler_hw3.y" /* yacc.c:1646  */
    {
			(yyval.f_val) = (yyvsp[-2].f_val) + (yyvsp[0].f_val);
			switch(operand_type)
			{
				case 'I':
					gencode_function("\tiadd\n");
					break;
				case 'F':
					gencode_function("\tfadd\n");
					break;
			}
		}
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1024 "compiler_hw3.y" /* yacc.c:1646  */
    {
			(yyval.f_val) = (yyvsp[-2].f_val) - (yyvsp[0].f_val);
			switch(operand_type)
			{
				case 'I':
					gencode_function("\tisub\n");
					break;
				case 'F':
					gencode_function("\tfsub\n");
					break;
			}
		}
#line 2545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1039 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1041 "compiler_hw3.y" /* yacc.c:1646  */
    {
			(yyval.f_val) = (yyvsp[-2].f_val) * (yyvsp[0].f_val);
			switch(operand_type)
			{
				case 'I':
					gencode_function("\timul\n");
					break;
				case 'F':
					gencode_function("\tfmul\n");
					break;
			}
		}
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1054 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(zero_flag==1)
			{
				error_type(3,"devided by zero","");
			}
			else
			{
				(yyval.f_val) = (yyvsp[-2].f_val) / (yyvsp[0].f_val);
				switch(operand_type)
				{
					case 'I':
						gencode_function("\tidiv\n");
					break;
				case 'F':
					gencode_function("\tfdiv\n");
					break;
				}
			}
		}
#line 2592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1074 "compiler_hw3.y" /* yacc.c:1646  */
    {	
			switch(operand_type)
			{
				case 'I':
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
					{
						(yyval.f_val) = (int)(yyvsp[-2].f_val) % (int)(yyvsp[0].f_val);
						gencode_function("\tirem\n");
					}
					break;
				}
				case 'F':  // float cannot do mod
					error_type(3,"Modulo operator(%) with floating point operands","");
					break;
			}
		}
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1096 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1101 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1112 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 2634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1114 "compiler_hw3.y" /* yacc.c:1646  */
    {
			int lookup_result = lookup_symbol((yyvsp[-2].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{	
				error_type(2,"Undeclared function",(yyvsp[-2].string));
			}
			else
			{
				fprintf(file, "\tinvokestatic compiler_hw3/%s()", (yyvsp[-2].string));
				char type[10] = {0};
				strcpy(type, get_type((yyvsp[-2].string),SCOPE,symbol_num));
				if(strcmp(type, "int")==0)
				{
					gencode_function("I\n");
					operand_type = 'I';
				}
				else if(strcmp(type, "float")==0)
				{
					gencode_function("F\n");
					operand_type = 'F';
				}
				else if(strcmp(type, "bool")==0)
				{
					gencode_function("Z\n");
					operand_type = 'Z';
				}
				else if(strcmp(type, "void")==0)
				{
					gencode_function("V\n");
					operand_type = 'V';
				}
				else if(strcmp(type, "string")==0)
				{
					gencode_function("Ljava/lang/String;\n");
					operand_type = 's';
				}
			}
		}
#line 2677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1153 "compiler_hw3.y" /* yacc.c:1646  */
    {
			int lookup_result = lookup_symbol((yyvsp[-3].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared function",(yyvsp[-3].string));
			}
			else
			{
				fprintf(file, "\tinvokestatic compiler_hw3/%s(", (yyvsp[-3].string));
				char temp[256] = {0};
				strcpy(temp, get_attribute((yyvsp[-3].string), SCOPE, symbol_num));
				char *arg_type;
				arg_type = strtok(temp,", ");
				while(arg_type != NULL)
				{
					if(strcmp(arg_type, "int")==0)
					{
						gencode_function("I");
					}
					else if(strcmp(arg_type, "float")==0)
					{
						gencode_function("F");
					}
					else if(strcmp(arg_type, "bool")==0)
					{
						gencode_function("Z");
					}
					else if(strcmp(arg_type, "void")==0)
					{
						gencode_function("V");
					}
					else if(strcmp(arg_type, "string")==0)
					{
						gencode_function("Ljava/lang/String;");
					}

					arg_type = strtok(NULL, ", ");
				}
				fprintf(file, ")");

				char type[10] = {0};
				strcpy(type, get_type((yyvsp[-3].string),SCOPE,symbol_num));
				if(strcmp(type, "int")==0)
				{
					gencode_function("I\n");
				}
				else if(strcmp(type, "float")==0)
				{
					gencode_function("F\n");
				}
				else if(strcmp(type, "bool")==0)
				{
					gencode_function("Z\n");
				}
				else if(strcmp(type, "void")==0)
				{
					gencode_function("V\n");
				}
				else if(strcmp(type, "string")==0)
				{
					gencode_function("Ljava/lang/String;\n");
				}
			}

		}
#line 2747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1219 "compiler_hw3.y" /* yacc.c:1646  */
    {
			int lookup_result = lookup_symbol((yyvsp[-1].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[-1].string));
			}
			else
			{
				char tmp[32];
				int reg = get_register(symbol_table, (yyvsp[-1].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					fprintf(file, "\tgetstatic compiler_hw3/%s I\n", (yyvsp[-1].string));	// loaded
				}
				else	// local variable
				{
					gencode_function("\tiload ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
				gencode_function("\tldc 1\n\tiadd\n");

				if(reg==-1)		// global variable
				{	
					fprintf(file, "\tputstatic compiler_hw3/%s I\n", (yyvsp[-1].string));	// stored
				}
				else	// local variable
				{
					gencode_function("\tistore ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
			}
		}
#line 2786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1254 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			int lookup_result = lookup_symbol((yyvsp[-1].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[-1].string));
			}
			else
			{
				int reg = get_register(symbol_table, (yyvsp[-1].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					fprintf(file, "\tgetstatic compiler_hw3/%s I\n", (yyvsp[-1].string));
				}
				else	// local variable
				{
					gencode_function("\tiload ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
				gencode_function("\tldc 1\n\tisub\n");

				if(reg==-1)		// global variable
				{	
					fprintf(file, "\tputstatic compiler_hw3/%s I\n", (yyvsp[-1].string));
				}
				else	// local variable
				{
					gencode_function("\tistore ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
			}
		}
#line 2825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1291 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val);  }
#line 2831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1297 "compiler_hw3.y" /* yacc.c:1646  */
    {
			++SCOPE;
			++if_num[SCOPE-1];
			if_branch_num[SCOPE-1] = 1;
			if_end_flag[SCOPE-1] = 1;
			if_exit_flag[SCOPE-1] = 1;
			switch(relation_type)
			{
				case 'E':	//==
				{
					fprintf(file, "\tifeq LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'N':	//!=
				{
					fprintf(file, "\tifne LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'l':	//<
				{
					fprintf(file, "\tiflt LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'm':	//>
				{
					fprintf(file, "\tifgt LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'L':	//<=
				{
					fprintf(file, "\tifle LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'M':	//>=
				{
					fprintf(file, "\tifge LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
			}
			fprintf(file, "\tgoto END%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1],if_branch_num[SCOPE-1]);
			fprintf(file, "LABEL%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
		}
#line 2878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1340 "compiler_hw3.y" /* yacc.c:1646  */
    {
			dump_flag = 1;
			add_scope = 1;
			
			++if_branch_num[SCOPE-1];
			if_end_flag[SCOPE-1] = 1;
			switch(relation_type)
			{
				case 'E':	//==
				{
					fprintf(file, "\tifeq LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'N':	//!=
				{
					fprintf(file, "\tifne LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'l':	//<
				{
					fprintf(file, "\tiflt LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'm':	//>
				{
					fprintf(file, "\tifgt LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'L':	//<=
				{
					fprintf(file, "\tifle LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
				case 'M':	//>=
				{
					fprintf(file, "\tifge LABEL%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
					break;
				}
			}
			relation_type = 0;
			fprintf(file, "\tgoto END%d_%d_%d\n", SCOPE-1, if_num[SCOPE-1],if_branch_num[SCOPE-1]);
			fprintf(file, "LABEL%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);

		}
#line 2927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1385 "compiler_hw3.y" /* yacc.c:1646  */
    {
			dump_flag = 1;
			add_scope = 1;
			
			if_end_flag[SCOPE-1] = 0;
			fprintf(file, "\tgoto  EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
			fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
		}
#line 2940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1394 "compiler_hw3.y" /* yacc.c:1646  */
    {
			++SCOPE;
			
			switch(relation_type)
			{
				case 'E':
				{
					fprintf(file, "\tifeq LABEL_TRUE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
					break;
				}
				case 'N':
				{
					fprintf(file, "\tifne LABEL_TRUE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
					break;
				}
				case 'l':
				{
					fprintf(file, "\tiflt LABEL_TRUE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
					break;
				}
				case 'm':
				{
					fprintf(file, "\tifgt LABEL_TRUE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
					break;
				}
				case 'L':
				{
					fprintf(file, "\tifle LABEL_TRUE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
					break;
				}
				case 'M':
				{
					fprintf(file, "\tifge LABEL_TRUE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
					break;
				}
			}
			relation_type = 0;
			fprintf(file, "\tgoto LABEL_FALSE%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
			fprintf(file, "LABEL_TRUE%d_%d:\n", SCOPE-1, while_num[SCOPE-1]);
		}
#line 2985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1435 "compiler_hw3.y" /* yacc.c:1646  */
    {
			int lookup_result = lookup_symbol((yyvsp[-4].string), SCOPE, symbol_num);
			if(lookup_result == -1 || lookup_result == -3)	// If function undeclared, insert it and its parameters
			{
				func_flag = 1;
				char temp[256]= {0};
				strncpy(temp,params,strlen(params)-2);
				insert_symbol(symbol_num, (yyvsp[-4].string), "function", (yyvsp[-5].string), SCOPE, temp, 2, -1);
				++symbol_num;
				memset(params,0,sizeof(params));
				
				fprintf(file, ".method public static %s(",(yyvsp[-4].string));
				int i = 0;
				for(i=0; i<param_num;++i)
				{
					if(func_reg_type[i]=='I')
						gencode_function("I");
					else if(func_reg_type[i]=='F')
						gencode_function("F");
					else if(func_reg_type[i]=='Z')
						gencode_function("Z");
					else if(func_reg_type[i]=='s')
						gencode_function("Ljava/lang/String;");
					else if(func_reg_type[i]=='V')
						gencode_function("V");
				}
				if(strcmp((yyvsp[-5].string),"int")==0)
				{
					return_type = 'I';
					gencode_function(")I\n");
				}
				else if(strcmp((yyvsp[-5].string),"float")==0)
				{
					return_type = 'F';
					gencode_function(")F\n");
				}
				else if(strcmp((yyvsp[-5].string),"bool")==0)
				{
					return_type = 'Z';
					gencode_function(")Z\n");
				}
				else if(strcmp((yyvsp[-5].string), "string")==0)
				{
					return_type = 's';
					gencode_function(")Ljava/lang/String;\n");
				}
				else if(strcmp((yyvsp[-5].string), "void")==0)
				{
					return_type = 'V';
					gencode_function(")V\n");
				}
				gencode_function(".limit stack 50\n.limit locals 50\n");

				param_num = 0;
				func_reg = 0;
				memset(func_reg_type, 0, sizeof(func_reg_type));
			}
			else if(lookup_result >= 0 && symbol_table[lookup_result]->forward!=2)		// If function forward declared, insert its attribute
			{
				func_flag = 1;
				char temp[256] = {0};
				strncpy(temp,params,strlen(params)-2);

				if(strcmp((yyvsp[-5].string), symbol_table[lookup_result]->data_type) != 0)
				{
					error_type(3,"function return type does not match","");
					if(strcmp((yyvsp[-5].string),"int")==0)
						return_type = 'I';
					else if(strcmp((yyvsp[-5].string),"float")==0)
						return_type = 'F';
					else if(strcmp((yyvsp[-5].string),"bool")==0)
						return_type = 'Z';
					else if(strcmp((yyvsp[-5].string), "string")==0)
						return_type = 's';
					else if(strcmp((yyvsp[-5].string), "void")==0)
						return_type = 'V';
				}
				else if(strcmp(temp,symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
					if(strcmp((yyvsp[-5].string),"int")==0)
						return_type = 'I';
					else if(strcmp((yyvsp[-5].string),"float")==0)
						return_type = 'F';
					else if(strcmp((yyvsp[-5].string),"bool")==0)
						return_type = 'Z';	
					else if(strcmp((yyvsp[-5].string), "string")==0)
						return_type = 's';
					else if(strcmp((yyvsp[-5].string), "void")==0)
						return_type = 'V';
				}
				else 
				{
					if(symbol_table[lookup_result]->attribute==NULL)
					{
						strcpy(symbol_table[lookup_result]->attribute, temp);
						memset(params,0,sizeof(params));
					}
	
					fprintf(file, ".method public static %s(",(yyvsp[-4].string));
					int i = 0;
					for(i=0; i<param_num;++i)
					{
						if(func_reg_type[i]=='I')
							gencode_function("I");
						else if(func_reg_type[i]=='F')
							gencode_function("F");
						else if(func_reg_type[i]=='Z')
							gencode_function("Z");
						else if(func_reg_type[i]=='s')
							gencode_function("Ljava/lang/String;");
						else if(func_reg_type[i]=='V')
							gencode_function("V");
					}
					if(strcmp((yyvsp[-5].string),"int")==0)
					{
						return_type = 'I';
						gencode_function(")I\n");
					}
					else if(strcmp((yyvsp[-5].string),"float")==0)
					{
						return_type = 'F';
						gencode_function(")F\n");
					}
					else if(strcmp((yyvsp[-5].string),"bool")==0)
					{
						return_type = 'Z';
						gencode_function(")Z\n");
					}	
					else if(strcmp((yyvsp[-5].string), "string")==0)
					{
						return_type = 's';
						gencode_function(")Ljava/lang/String;\n");
					}
					else if(strcmp((yyvsp[-5].string), "void")==0)
					{
						return_type = 'V';
						gencode_function(")V\n");
					}
					gencode_function(".limit stack 50\n.limit locals 50\n");

					param_num = 0;
					func_reg = 0;
					memset(func_reg_type, 0, sizeof(func_reg_type));
				}
			}
			else
			{
				error_type(2,"Redeclared function",(yyvsp[-4].string));
			}
	
			++SCOPE;
	}
#line 3143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1589 "compiler_hw3.y" /* yacc.c:1646  */
    {
			int lookup_result = lookup_symbol((yyvsp[-3].string), SCOPE, symbol_num); 
			if(lookup_result == -1 || lookup_result == -3)
			{
				func_flag = 1;
				insert_symbol(symbol_num, (yyvsp[-3].string), "function", (yyvsp[-4].string), SCOPE, NULL, 2, -1);
				++symbol_num;

				if(strcmp((yyvsp[-3].string),"main")==0)
				{
					gencode_function(".method public static main([Ljava/lang/String;)V\n");
					gencode_function(".limit stack 50\n");
					gencode_function(".limit locals 50\n");
					if(strcmp((yyvsp[-4].string),"int")==0)
						return_type = 'I';
					else if(strcmp((yyvsp[-4].string),"float")==0)
						return_type = 'F';
					else if(strcmp((yyvsp[-4].string),"bool")==0)
						return_type = 'Z';
					else if(strcmp((yyvsp[-4].string), "string")==0)
						return_type = 's';
					else if(strcmp((yyvsp[-4].string), "void")==0)
						return_type = 'V';	
				}
				else
				{
					fprintf(file, ".method public static %s()", (yyvsp[-3].string));
					if(strcmp((yyvsp[-4].string),"int")==0)
					{
						return_type = 'I';
						gencode_function(")I\n");
					}
					else if(strcmp((yyvsp[-4].string),"float")==0)
					{
						return_type = 'F';
						gencode_function(")F\n");
					}
					else if(strcmp((yyvsp[-4].string),"bool")==0)
					{
						return_type = 'Z';
						gencode_function(")Z\n");
					}
					else if(strcmp((yyvsp[-4].string), "string")==0)
					{
						return_type = 's';
						gencode_function(")Ljava/lang/String;\n");
					}
					else if(strcmp((yyvsp[-4].string), "void")==0)
					{
						return_type = 'V';
						gencode_function(")V\n");
					}
					gencode_function(".limit stack 50\n.limit locals 50\n");
				}
				param_num = 0;
				func_reg = 0;
				memset(func_reg_type, 0, sizeof(func_reg_type));
			}
			else if(lookup_result >= 0 && symbol_table[lookup_result]->forward!=2)	// If function forward declared
			{
				func_flag = 1;
				if(strcmp((yyvsp[-4].string), symbol_table[lookup_result]->data_type)!=0)
				{
					error_type(3,"function return type does not match","");
					if(strcmp((yyvsp[-4].string),"int")==0)
						return_type = 'I';
					else if(strcmp((yyvsp[-4].string),"float")==0)
						return_type = 'F';
					else if(strcmp((yyvsp[-4].string),"bool")==0)
						return_type = 'Z';
					else if(strcmp((yyvsp[-4].string), "string")==0)
						return_type = 's';
					else if(strcmp((yyvsp[-4].string), "void")==0)
						return_type = 'V';
				}
				else if(strlen(symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
					if(strcmp((yyvsp[-4].string),"int")==0)
						return_type = 'I';
					else if(strcmp((yyvsp[-4].string),"float")==0)
						return_type = 'F';
					else if(strcmp((yyvsp[-4].string),"bool")==0)
						return_type = 'Z';
					else if(strcmp((yyvsp[-4].string), "string")==0)
						return_type = 's';
					else if(strcmp((yyvsp[-4].string), "void")==0)
						return_type = 'V';
				}
				else
				{
					if(strcmp((yyvsp[-3].string),"main")==0)
					{
						gencode_function(".method public static main([Ljava/lang/String;)V\n");
						gencode_function(".limit stack 50\n");
						gencode_function(".limit locals 50\n");
						if(strcmp((yyvsp[-4].string),"int")==0)
							return_type = 'I';
						else if(strcmp((yyvsp[-4].string),"float")==0)
							return_type = 'F';
						else if(strcmp((yyvsp[-4].string),"bool")==0)
							return_type = 'Z';
						else if(strcmp((yyvsp[-4].string), "string")==0)
							return_type = 's';
						else if(strcmp((yyvsp[-4].string), "void")==0)
							return_type = 'V';
					}
					else
					{
						fprintf(file, ".method public static %s()",(yyvsp[-3].string));
						if(strcmp((yyvsp[-4].string),"int")==0)
						{
							return_type = 'I';
							gencode_function("I\n");
						}
						else if(strcmp((yyvsp[-4].string),"float")==0)
						{
							return_type = 'F';
							gencode_function("F\n");
						}
						else if(strcmp((yyvsp[-4].string),"bool")==0)
						{
							return_type = 'Z';
							gencode_function("Z\n");
						}
						else if(strcmp((yyvsp[-4].string), "string")==0)
						{
							return_type = 's';
							gencode_function("Ljava/lang/String;\n");
						}
						else if(strcmp((yyvsp[-4].string), "void")==0)
						{
							return_type = 'V';
							gencode_function("V\n");
						}
						gencode_function(".limit stack 50\n.limit locals 50\n");
					}
					param_num = 0;
					func_reg = 0;
					memset(func_reg_type, 0, sizeof(func_reg_type));
				}
			}
			else 
			{
				error_type(2,"Redeclared function",(yyvsp[-3].string));
			}

			++SCOPE;
		}
#line 3297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1739 "compiler_hw3.y" /* yacc.c:1646  */
    {	
			dump_flag = 1;	// flag to indicate to dump_flag table when meet NEWLINE later
			if(if_end_flag[SCOPE-1] == 1)
			{
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			if(if_exit_flag[SCOPE-1] == 1)
			{
				fprintf(file, "EXIT%d_%d:\n", SCOPE-1, if_num[SCOPE-1]);
				if_exit_flag[SCOPE-1] = 0;
			}
			if(while_exit_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto LABEL_BEGIN%d_%d\n", SCOPE-1, while_num[SCOPE-1]);
				fprintf(file, "LABEL_FALSE%d_%d:\n", SCOPE-1, while_num[SCOPE-1]);
				while_exit_flag[SCOPE-1] = 0;
			}
		}
#line 3322 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1764 "compiler_hw3.y" /* yacc.c:1646  */
    {
			++while_num[SCOPE];
			while_exit_flag[SCOPE] = 1;
			fprintf(file, "LABEL_BEGIN%d_%d:\n", SCOPE, while_num[SCOPE]);
		}
#line 3332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1775 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(return_type == 'V')
				gencode_function("\treturn\n.end method\n");
			else
				error_type(3,"function return type does not match","");
			return_type = 0;
		}
#line 3344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1783 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(return_type == 'I')
			{	
				if(operand_type=='I')
					gencode_function("\tireturn\n.end method\n");
				else
					error_type(3,"function return type does not match","");
			}
			else if(return_type == 'F')
			{	
				if(operand_type=='F')
					gencode_function("\tfreturn\n.end method\n");
				else
					error_type(3,"function return type does not match","");
			}
			else if(return_type == 'Z')
			{	
				if(operand_type=='Z')
					gencode_function("\tireturn\n.end method\n");
				else
					error_type(3,"function return type does not match","");
			}
			else if(return_type == 's')
			{	
				if(operand_type=='s')
					gencode_function("\tareturn\n.end method\n");
				else
					error_type(3,"function return type does not match","");
			}
			else if(return_type == 'V')
			{
				error_type(3,"function return type does not match","");
			}
			return_type = 0;
		}
#line 3384 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1822 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp, "%d\n", (yyvsp[-1].i_val));
			gencode_function(tmp);
			gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        	gencode_function("\tswap\n");
        	gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
		}
#line 3398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1832 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp, "%f\n", (yyvsp[-1].f_val));
			gencode_function(tmp);
			gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        	gencode_function("\tswap\n");
        	gencode_function("\tinvokevirtual java/io/PrintStream/println(F)V\n");
		}
#line 3412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1842 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp, "\"%s\"\n", (yyvsp[-1].string));
			gencode_function(tmp);
			gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        	gencode_function("\tswap\n");
        	gencode_function("\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
		}
#line 3426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1852 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(lookup_symbol((yyvsp[-1].string), SCOPE, symbol_num) == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[-1].string));
			}
			else
			{
				int reg = get_register(symbol_table, (yyvsp[-1].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{
					char tmp[32];
					char type[10] = {0};
					strcpy(type, get_type((yyvsp[-1].string), SCOPE, symbol_num));
					if(strcmp(type,"int")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s I\n", (yyvsp[-1].string));
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
					}
					else if(strcmp(type,"float")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s F\n", (yyvsp[-1].string));
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(F)V\n");			
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s Z\n", (yyvsp[-1].string));
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
					}
					else if(strcmp(type, "string")==0)
					{	
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s Ljava/lang/String;\n", (yyvsp[-1].string));
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");	
					}
				}
				else	// local variable
				{
					char tmp[32];
					if(strcmp(reg_type[reg],"int")==0)
					{
						gencode_function("\tiload ");
						sprintf(tmp, "%d\n", reg);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
					}
					else if(strcmp(reg_type[reg],"float")==0)
					{
						gencode_function("\tfload ");
						sprintf(tmp, "%d\n", reg);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(F)V\n");
					}
					else if(strcmp(reg_type[reg],"bool")==0)
					{	
						gencode_function("\tiload ");
						sprintf(tmp, "%d\n", reg);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
					}
					else if(strcmp(reg_type[reg], "string")==0)
					{	
						gencode_function("\taload ");
						sprintf(tmp, "%d\n", reg);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");	
					}
				}
			}
		}
#line 3523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1949 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(lookup_symbol((yyvsp[0].string), SCOPE, symbol_num) == -1)
				error_type(2,"Undeclared variable",(yyvsp[0].string));
	  	}
#line 3532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1953 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].i_val); }
#line 3538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1954 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 3544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1955 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = 1; }
#line 3550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1956 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.f_val) = 0; }
#line 3556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1967 "compiler_hw3.y" /* yacc.c:1646  */
    {
			if(lookup_symbol((yyvsp[0].string), SCOPE+1, symbol_num) != -2)
			{
				insert_symbol(symbol_num, (yyvsp[0].string), "parameter", (yyvsp[-1].string), SCOPE+1, NULL, 0, func_reg);
				strcat(params,(yyvsp[-1].string));
				strcat(params,", ");
				param_index[param_num] = symbol_num;	// Record the index for removing later when function declaration
				
				if(strcmp((yyvsp[-1].string),"int")==0)
				{
					func_reg_type[param_num] = 'I';
				}
				else if(strcmp((yyvsp[-1].string),"float")==0)
				{		
					func_reg_type[param_num] = 'F';
				}
				else if(strcmp((yyvsp[-1].string),"bool")==0)
				{	
					func_reg_type[param_num] = 'Z';
				}
				else if(strcmp((yyvsp[-1].string), "string")==0)
				{	
					func_reg_type[param_num] = 's';
				}
				else if(strcmp((yyvsp[-1].string), "void")==0)
				{	
					func_reg_type[param_num] = 'V';
				}
			
				++symbol_num;
				++param_num;
				++func_reg;
			}
			else
			{
				error_type(2,"Redeclared variable",(yyvsp[0].string));
				strcat(params,(yyvsp[-1].string));
				strcat(params,", ");
			}
		}
#line 3601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 2020 "compiler_hw3.y" /* yacc.c:1646  */
    {
			int lookup_result = lookup_symbol((yyvsp[0].string), SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",(yyvsp[0].string));
			}
			else
			{
				int reg = get_register(symbol_table, (yyvsp[0].string), SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					char tmp[32];
					char type[10] = {0};
					strcpy(type, get_type((yyvsp[0].string), SCOPE, symbol_num));
					if(strcmp(type,"int")==0)
					{
						if(operand_type==0 || operand_type=='I')
						{
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s I\n", (yyvsp[0].string));
							gencode_function(tmp);
							operand_type = 'I';
						}
						else if(operand_type == 'F')
						{
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s I\n", (yyvsp[0].string));
							gencode_function(tmp);
							gencode_function("\ti2f\n");
							operand_type = 'F';
						}
					}
					else if(strcmp(type,"float")==0)
					{	
						if(operand_type=='I')
						{
							gencode_function("\ti2f\n");
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s F\n", (yyvsp[0].string));
							gencode_function(tmp);
							operand_type = 'F';
						}
						else if(operand_type == 0 || operand_type =='F')
						{
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s F\n", (yyvsp[0].string));
							gencode_function(tmp);
							operand_type = 'F';
						}					
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp,"%s Z\n", (yyvsp[0].string));
						gencode_function(tmp);
						operand_type = 'Z';
					}
					else if(strcmp(type, "string")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp,"%s Ljava/lang/String;\n", (yyvsp[0].string));
						gencode_function(tmp);	
						operand_type = 's';	
					}
				}
				else	// local variable
				{
					char tmp[32];
					if(strcmp(reg_type[reg],"int")==0)
					{	
						if(operand_type==0 || operand_type=='I')
						{
							gencode_function("\tiload ");
							sprintf(tmp,"%d\n", reg);
							gencode_function(tmp);
							operand_type = 'I';
						}
						else if(operand_type == 'F')
						{
							gencode_function("\tiload ");
							sprintf(tmp,"%d\n", reg);
							gencode_function(tmp);
							gencode_function("\ti2f\n");
							operand_type = 'F';
						}
					}
					else if(strcmp(reg_type[reg],"float")==0)
					{
						if(operand_type=='I')
						{
							gencode_function("\ti2f\n");
							gencode_function("\tfload ");
							sprintf(tmp,"%d\n", reg);
							gencode_function(tmp);
							operand_type = 'F';
						}
						else if(operand_type == 0 || operand_type == 'F')
						{
							gencode_function("\tfload ");
							sprintf(tmp,"%d\n", reg);
							gencode_function(tmp);
							operand_type = 'F';
						}
					}
					else if(strcmp(reg_type[reg],"bool")==0)
					{	
						gencode_function("\tiload ");
						sprintf(tmp,"%d\n", reg);
						gencode_function(tmp);
						operand_type = 'Z';
					}
					else if(strcmp(reg_type[reg], "string")==0)
					{	
						gencode_function("\taload ");
						sprintf(tmp,"%d\n", reg);
						gencode_function(tmp);
					}
				}
			}
		}
#line 3726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 2141 "compiler_hw3.y" /* yacc.c:1646  */
    {	
			char tmp[32];
			if(operand_type==0 || operand_type=='I')
			{
				(yyval.f_val) = (int)(yyvsp[0].i_val);
				gencode_function("\tldc ");
				sprintf(tmp,"%d\n", (int)(yyvsp[0].i_val));
				gencode_function(tmp);
				operand_type = 'I';
			}
			else if(operand_type == 'F')
			{
				(yyval.f_val) = (double)(yyvsp[0].i_val);
				gencode_function("\tldc ");
				sprintf(tmp,"%d\n", (int)(yyvsp[0].i_val));
				gencode_function(tmp);

				gencode_function("\ti2f\n");
				operand_type = 'F';
			}
			if(zero_flag == 1)
				zero_flag = 0;
			if((yyval.f_val) == 0)
				zero_flag = 1;
		}
#line 3756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 2167 "compiler_hw3.y" /* yacc.c:1646  */
    {		
			char tmp[32];
			(yyval.f_val) = (double)(yyvsp[0].f_val);
			if(operand_type=='I')
			{
				gencode_function("\ti2f\n");

				gencode_function("\tldc ");
				sprintf(tmp,"%f\n", (double)(yyvsp[0].f_val));
				gencode_function(tmp);
				operand_type = 'F';
			}
			else if(operand_type==0 || operand_type =='F')
			{
				gencode_function("\tldc ");
				sprintf(tmp,"%f\n", (double)(yyvsp[0].f_val));
				gencode_function(tmp);
				operand_type = 'F';
			}
			if(zero_flag == 1)
				zero_flag = 0;
			if((yyval.f_val) == 0)
				zero_flag = 1;
		}
#line 3785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 2192 "compiler_hw3.y" /* yacc.c:1646  */
    {
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp,"\"%s\"\n", (yyvsp[0].string));
			gencode_function(tmp);
			operand_type = 's';
		}
#line 3797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 2200 "compiler_hw3.y" /* yacc.c:1646  */
    {	
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp,"%d\n", (int)1);
			gencode_function(tmp);
			(yyval.f_val) = (int)1;
			operand_type = 'Z';
		}
#line 3810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 2209 "compiler_hw3.y" /* yacc.c:1646  */
    {	
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp,"%d\n", (int)0);
			gencode_function(tmp);
			(yyval.f_val) = (int)0;
			operand_type = 'Z';
		}
#line 3823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 2222 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "int"); }
#line 3829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 2223 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "float"); }
#line 3835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 2224 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "bool"); }
#line 3841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 2225 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "string"); }
#line 3847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 2226 "compiler_hw3.y" /* yacc.c:1646  */
    { strcpy((yyval.string), "void"); }
#line 3853 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3857 "y.tab.c" /* yacc.c:1646  */
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 2229 "compiler_hw3.y" /* yacc.c:1906  */


/* C code section */
int main(int argc, char** argv)
{
	memset(params,0,sizeof(params));  
	yylineno = 0;

    file = fopen("compiler_hw3.j","w");

    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n");

    yyparse();
	if(err_flag!=1)	// If no syntax error, dump_flag global symbol at the end
	{
		dump_symbol(symbol_num,0);
		printf("\nTotal lines: %d \n",yylineno);
    }
    fclose(file);
    return 0;
}

void yyerror(char *s)
{
	printf("%d: %s\n", ++yylineno, buf); 
	if(err_flag==2)
	{	
		semantic_error();
	}
	printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
	err_flag = 1;
	memset(buf,0,sizeof(buf));
}

void semantic_error()
{
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
	if(err_flag==2)
		printf("| %s %s", err_message, err_symbol);
	else if(err_flag==3)
		printf("| %s", err_message);
    printf("\n|-----------------------------------------------|\n\n");
	err_flag = 0;	// reset
}

/* set the error type */
void error_type(int flag, char *message, char *symbol)
{
	err_flag = flag;	/*  0: No error;  
					   		1: syntatic error; 
					   		2: Re-declarations and un-declaration variables / functions;  
					   		3: Arithmetic error or Function error
						*/
	strcpy(err_message, message);
	strcpy(err_symbol, symbol);
}

/* symbol table functions */
void create_symbol(int entry_num) 
{
	symbol_table = malloc(sizeof(struct symbol *) * entry_num);
}

void insert_symbol(int index, char *name, char *kind, char *data_type, int scope, char *attribute, int forward, int reg)
{
	if(index==0)
	{
		create_symbol(69);
	}
	struct symbol *entry = malloc(sizeof(struct symbol));
	symbol_table[index] = entry;
	symbol_table[index]->index = index;	
	strcpy(symbol_table[index]->name, name);
	strcpy(symbol_table[index]->kind, kind);
	strcpy(symbol_table[index]->data_type, data_type);
	symbol_table[index]->scope = scope;
	if(attribute!=NULL)
	{
		strncpy(symbol_table[index]->attribute, attribute,strlen(attribute));
	}
	symbol_table[index]->forward = forward;
	symbol_table[index]->reg = reg;
	if(reg>=0)
		strcpy(reg_type[reg], data_type);
}
	
int lookup_symbol(char *name, int scope, int symbol_num)
{
	for(int i=0; i<symbol_num; ++i)
	{
		if(strcmp(name, symbol_table[i]->name)==0 && symbol_table[i]->scope==scope)
		{
			if(symbol_table[i]->forward==1)
				return i;	//if the symbol is a function and it has been forward declared
			else
				return -2;	//if the symbol with same name and same SCOPE exists, so can't be redeclared;
		}
		else if(strcmp(name, symbol_table[i]->name)==0 && symbol_table[i]->scope<scope)
			return -3;	//if the symbol with same name exists, and it is in seeable SCOPE;
	}
	return -1;	//if the symbol with same name and same SCOPE doesn't exist, so can be inserted;
}

void dump_symbol(int symbol_num, int SCOPE) 
{
    int i,j;
	int insert = 0;
	for(i=0; i<symbol_num; ++i)
	{
		if(symbol_table[i]->scope==SCOPE)
		{
			insert = 1;
			break;
		}
	}
	if(insert==1)
	{
		printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           		"Index", "Name", "Kind", "Type", "SCOPE", "Attribute");
		for(i=0,j=0; i<symbol_num; ++i)
		{
			if(symbol_table[i]->scope==SCOPE)
			{
				printf("%-10d%-10s%-12s%-10s%-10d%-s\n", j, symbol_table[i]->name, symbol_table[i]->kind, symbol_table[i]->data_type, symbol_table[i]->scope,symbol_table[i]->attribute);
				++j;
				memset(symbol_table[i],0,sizeof(struct symbol));
				symbol_table[i]->scope = -1;
			}
		}
		printf("\n");
	}
}

char* get_type(char *name, int scope, int symbol_num)
{
	for(int i=0; i<symbol_num; ++i){
		if(strcmp(name, symbol_table[i]->name)==0 && symbol_table[i]->scope<=scope)
			return symbol_table[i]->data_type;
	}
	return 0;
}

char* get_attribute(char *name, int scope, int symbol_num)
{
	for(int i=0; i<symbol_num; ++i)
	{
		if(strcmp(name, symbol_table[i]->name)==0 && symbol_table[i]->scope<=scope)
			return symbol_table[i]->attribute;
	}
	return 0;
}

int get_register(struct symbol **table, char *name, int scope, int symbol_num)
{
	for(int i=0; i<symbol_num; ++i){
		if(strcmp(name, table[i]->name)==0 && table[i]->scope<=scope)
			return table[i]->reg;
	}
	return -1;
}

/* code generation functions */
void gencode_function(char* code) 
{
	fprintf(file,"%s",code);
}
