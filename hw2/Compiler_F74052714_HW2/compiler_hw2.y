/*	Definition section */
%{
#include <stdio.h>
#include <string.h>
#include <libgen.h>

struct Symbol
{
    int index;
    char* name;
    char* kind;
    char* type;
    int scope;
    char* attributes[5];
    int attributes_count;
};

struct Symbol symbolTable[20];
struct Symbol tempSymbol;

int current_count = 0;

extern int yylineno;
extern int yylex();
extern void yyerror(char *s);
extern FILE *yyout;
extern FILE *yyin;
extern char* yytext;   // Get current token from lex
extern char buf[1024];  // Get current code line from lex
FILE* myfile;

/* Symbol table function - you can add new function if needed. */
int lookup_symbol(char* name);
void create_symbol();
void insert_symbol(int scope_id , char* name, char* find, char* type);
void dump_symbol(int scope);
void reset_temp_symbol();
void reset_local_symbol();
void split(char **arr, char *str, const char *del);

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char* string;
}
/*190511*/
%token WHILE RETURN BREAK CONTINUE
%token VOID INT FLOAT BOOL STRING
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN
%token ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP
%token INC_OP DEC_OP
%token EQ_OP NE_OP LE_OP GE_OP
%token LEFT_OP RIGHT_OP
%token CPP_COMMENTS C_COMMENTS

/* Token without return */
%token PRINT 
%token IF ELSE FOR ELSE_IF
%token <string> ID
%token SEMICOLON

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STRING_LITERAL

/* Nonterminal with return, which need to sepcify type */
%type <string> direct_declarator
%type <string> declarator
%type <string> declaration_specifiers
%type <string> type_specifier
%type <string> init_declarator_list
%type <string> unary_expression
%type <string> postfix_expression

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

primary_expression
    : ID
    | constant
    | string
    | '(' expression ')'
;

constant
    : I_CONST
    | F_CONST
;

postfix_expression
    : primary_expression
    | postfix_expression '[' expression ']'
    | postfix_expression '(' ')'
    {
        int checker = lookup_symbol(strdup($1));
        if(!checker)
        {
            yyerror("Undeclared <function name>");
        }
    }
    | postfix_expression '(' argument_expression_list ')'
    {
        int checker = lookup_symbol(strdup($1));
        if(!checker)
        {
            yyerror("Undeclared function <function name>");
        }
    }
    | postfix_expression '.' ID
    | postfix_expression INC_OP
    | postfix_expression DEC_OP
    | '(' type_name ')' '{' initializer_list '}'
    | '(' type_name ')' '{' initializer_list ',' '}'
;

argument_expression_list
    : assignment_expression
    | argument_expression_list ',' assignment_expression
;

unary_expression
    : postfix_expression
    | INC_OP unary_expression
    | DEC_OP unary_expression
    | unary_operator cast_expression
;

unary_operator
    : '&'
    | '*'
    | '+'
    | '-'
    | '~'
    | '!'
;

cast_expression
    : unary_expression
    | '(' type_name ')' cast_expression
;

multiplicative_expression
    : cast_expression
    | multiplicative_expression MUL_OP cast_expression
    | multiplicative_expression DIV_OP cast_expression
    | multiplicative_expression MOD_OP cast_expression
;
additive_expression
    : multiplicative_expression
    | additive_expression ADD_OP multiplicative_expression
    | additive_expression SUB_OP multiplicative_expression
;

shift_expression
    :additive_expression
    | shift_expression LEFT_OP additive_expression
    | shift_expression RIGHT_OP additive_expression
;

relational_expression
    : shift_expression
    | relational_expression '<' shift_expression
    | relational_expression '>' shift_expression
    | relational_expression LE_OP shift_expression
    | relational_expression GE_OP shift_expression
;

equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression
    | equality_expression NE_OP relational_expression
;

logical_and_expression
    : equality_expression
    | logical_and_expression AND_OP equality_expression
;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression
;

conditional_expression
    : logical_or_expression
;

assignment_expression
    : conditional_expression
    | unary_expression assignment_operator assignment_expression
    {
        int checker = lookup_symbol(strdup($1));
        if(!checker)
        {
            yyerror("Undeclared variable <variable_name>");
        }
    }
;

assignment_operator
    : '='
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
;

expression
    : assignment_expression
    | expression ',' assignment_expression
;

constant_expression
    : conditional_expression
;

declaration
    : declaration_specifiers SEMICOLON
    | declaration_specifiers init_declarator_list SEMICOLON
    {
        int checker = lookup_symbol(strdup($2));
        if(checker)
        {
            yyerror("Redeclared variable <variable_name>");
        }
        else
        {
            insert_symbol(1, strdup($2), "variable", strdup($1));
        }
    }
;

declaration_specifiers
    : type_specifier declaration_specifiers
    | type_specifier
;

init_declarator_list
    : init_declarator
    | init_declarator_list ',' init_declarator
;

init_declarator
    : declarator '=' initializer
    | declarator
;

type_specifier
    : VOID
    | INT
    | FLOAT
    | BOOL
    | STRING
;

string
    : STRING_LITERAL
;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    | type_specifier
;

declarator
    : direct_declarator
;

direct_declarator
    : ID
    | '(' declarator ')'
    | direct_declarator '[' ']'
    | direct_declarator '[' '*' ']'
    | direct_declarator '[' assignment_expression ']'
    | direct_declarator '(' parameter_type_list ')'
    | direct_declarator '(' ')'
    | direct_declarator '(' ID_list ')'
;

parameter_type_list
    : parameter_list
;

parameter_list
    : parameter_declaration
    | parameter_list ',' parameter_declaration
;

parameter_declaration
    : declaration_specifiers declarator
    {
        insert_symbol(1, strdup($2), "parameter", strdup($1));
        symbolTable[current_count - 1].scope = 1;
    }
    | declaration_specifiers abstract_declarator
    | declaration_specifiers
;

ID_list
    : ID
    | ID_list ',' ID
;

type_name
    : specifier_qualifier_list abstract_declarator
    | specifier_qualifier_list
;

abstract_declarator
    : direct_abstract_declarator
;

direct_abstract_declarator
    : '(' abstract_declarator ')'
    | '[' ']'
    | '[' '*' ']'
    | '[' assignment_expression ']'
    | direct_abstract_declarator '[' ']'
    | direct_abstract_declarator '[' '*' ']'
    | direct_abstract_declarator '[' assignment_expression ']'
    | '(' ')'
    | '(' parameter_type_list ')'
    | direct_abstract_declarator '(' ')'
    | direct_abstract_declarator '(' parameter_type_list ')'
;

initializer
    : '{' initializer_list '}'
    | '{' initializer_list ',' '}'
    | assignment_expression
;

initializer_list
    : designation initializer
    | initializer
    | initializer_list ',' designation initializer
    | initializer_list ',' initializer
;

designation
    : designator_list '='
;

designator_list
    : designator
    | designator_list designator
;

designator
    : '[' constant_expression ']'
    | '.' ID
;

statement
    : compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | PRINT '(' ID ')' SEMICOLON
    | PRINT '(' string ')' SEMICOLON
    | CPP_COMMENTS
;

compound_statement
    : '{' '}'
    | '{' block_item_list '}'
;

block_item_list
    : block_item
    | block_item_list block_item
;

block_item
    : declaration 
    {
        symbolTable[current_count - 1].scope++;
    }
    | statement
;

expression_statement
    : SEMICOLON
    | expression SEMICOLON
;

selection_statement
    : IF '(' expression ')' statement ELSE statement
    | IF '(' expression ')' statement
    | IF '(' expression ')' statement ELSE_IF '(' expression ')' statement ELSE statement
;

iteration_statement
    : WHILE '(' expression ')' statement
    | FOR '(' expression_statement expression_statement ')' statement
    | FOR '(' expression_statement expression_statement expression ')' statement
    | FOR '(' declaration expression_statement ')' statement
    | FOR '(' declaration expression_statement expression ')' statement
;

jump_statement
    : CONTINUE SEMICOLON
    | BREAK SEMICOLON
    | RETURN SEMICOLON
    | RETURN expression SEMICOLON
;

program
    : external_declaration
    | program external_declaration
;

external_declaration
    : function_definition
    | declaration
;

function_definition
    : declaration_specifiers declarator declaration_list compound_statement
    {
        int checker = lookup_symbol(strdup($2));
        if(checker)
        {
            yyerror("Redeclared function <function_name>");
        }
        else
        {
            insert_symbol(0, strdup($2), "function", strdup($1));
            symbolTable[current_count - 1].scope = 0;

            int current_attributes = 0;

            for(int i = 0; i < current_count; i++)
            {
                if(strcmp(symbolTable[i].kind, "parameter") == 0)
                {
                    symbolTable[current_count - 1].attributes[current_attributes] = symbolTable[i].type;
                    current_attributes++;
                }
            }
            symbolTable[current_count - 1].attributes_count = current_attributes;
        }
        dump_symbol(1);
        reset_local_symbol();
    }
    | declaration_specifiers declarator compound_statement 
    {
        int checker = lookup_symbol(strdup($2));
        if(checker)
        {
            yyerror("Redeclared function <function_name>");
        }
        else
        {
            insert_symbol(0, strdup($2), "function", strdup($1));
            symbolTable[current_count - 1].scope = 0;

            int current_attributes = 0;

            for(int i = 0; i < current_count; i++)
            {
                if(strcmp(symbolTable[i].kind, "parameter") == 0)
                {
                    symbolTable[current_count - 1].attributes[current_attributes] = symbolTable[i].type;
                    current_attributes++;
                }
            }
            symbolTable[current_count - 1].attributes_count = current_attributes;
        }
        dump_symbol(1);
        reset_local_symbol();
    }
;

declaration_list
    : declaration
    | declaration_list declaration
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    // Initializer symbol tables
    create_symbol();

    // open a file handle to particular file:
    FILE *myfile = fopen(argv[1], "r");
    if(!myfile)
    {
        return -1;
    }

    // set lex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    char* filename = basename(strdup(argv[1]));
    char* split_str[2];
    split(split_str, filename, ".");
    
    char out_name[50] = "./output/";
    char* file = strdup(split_str[0]);
    strcat(out_name, file);
    strcat(out_name, ".out");
    yyout = fopen(out_name, "w");

    yyparse();
    dump_symbol(0);
	fprintf(yyout, "\nTotal lines: %d \n",yylineno);

    return 0;
}

void split(char **arr, char *str, const char *del)
{
    char *s = strtok(str, del);

    while(s != NULL)
    {
        *arr++ = s;
        s = strtok(NULL,del);
    }
}
void yyerror(char *s)
{
    fprintf(yyout, "\n|-----------------------------------------------|\n");
    fprintf(yyout, "| Error found in line %d: %s\n", yylineno, buf);
    fprintf(yyout, "| %s", s);
    fprintf(yyout, "\n|-----------------------------------------------|\n\n");
}

void create_symbol()
{
    for(int i = 0; i < 20; i++)
    {
        symbolTable[i].index = i;
        symbolTable[i].name = "";
        symbolTable[i].kind = "";
        symbolTable[i].type = "";
        symbolTable[i].scope = 0;
    }
}
void insert_symbol(int scope_id, char* name, char* kind, char* type)
{
    tempSymbol.name = name;
    tempSymbol.kind = kind;
    tempSymbol.type = type;
    tempSymbol.index = current_count;
    tempSymbol.scope = 0;
    symbolTable[current_count] = tempSymbol;
    current_count++;

    reset_temp_symbol();
}
int lookup_symbol(char* name)
{
    int exist = 0;
    for(int i = 0; i < current_count; i++)
    {
        if(strcmp(symbolTable[i].name, name) == 0)
        {
            exist = 1;
            break;
        }
    }
    return exist;
}
void reset_local_symbol()
{
    int delete_count = 0;
    for(int i = 0; i < current_count; i++)
    {
        if(symbolTable[i].scope > 0)
        {
            delete_count++;
            
            for(int j = i; j < current_count; j++)
            {
                symbolTable[j].name = symbolTable[j + 1].name;
                symbolTable[j].kind = symbolTable[j + 1].kind;
                symbolTable[j].type = symbolTable[j + 1].type;
                symbolTable[j].scope = symbolTable[j + 1].scope;
                for(int k = 0; k < symbolTable[j + 1].attributes_count; k++)
                {
                    symbolTable[j].attributes[k] = symbolTable[j + 1].attributes[k];
                }
                symbolTable[j].attributes_count = symbolTable[j + 1].attributes_count;
            }
            i = -1;
        }
    }
    current_count = current_count - delete_count;
}
void dump_symbol(int scope) 
{
    fprintf(yyout, "\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    int count = 0;
    for(int i = 0; i < current_count; i++)
    {
        if(scope == 0)
        {
            if(symbolTable[i].scope == 0)
            {
                char list_str[50] = "";
                for(int j = 0; j < symbolTable[i].attributes_count; j++)
                {
                    strcat(list_str, symbolTable[i].attributes[j]);
                    if(j != symbolTable[i].attributes_count - 1)
                    {
                        strcat(list_str, ",");
                    }
                }

                fprintf(yyout, "%-10d%-10s%-12s%-10s%-10d%-10s",
                    count,
                    symbolTable[i].name,
                    symbolTable[i].kind,
                    symbolTable[i].type,
                    symbolTable[i].scope,
                    list_str);
                fprintf(yyout, "\n");
                count++;
            }
        }
        else
        {
            if(symbolTable[i].scope != 0)
            {
                fprintf(yyout, "%-10d%-10s%-12s%-10s%-10d",
                    count,
                    symbolTable[i].name,
                    symbolTable[i].kind,
                    symbolTable[i].type,
                    symbolTable[i].scope);
                fprintf(yyout, "\n");
                count++;
            }
        }
    }
    fprintf(yyout, "\n");
}
void reset_temp_symbol()
{
    tempSymbol.type = "";
    tempSymbol.name = "";
    tempSymbol.kind = "";
    tempSymbol.scope = -1;
    for(int i = 0; i <tempSymbol.attributes_count; i++)
    {
        tempSymbol.attributes[i] = "";
    }
    tempSymbol.attributes_count = 0;
}
