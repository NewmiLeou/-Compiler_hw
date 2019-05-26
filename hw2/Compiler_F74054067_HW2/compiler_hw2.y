/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int yylineno;
extern int yylex();
void yyerror(char *s);
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

int symbol_num = 0;
int scope = 0;

int err_type = 0;	/* 0 : No error 
					   1 : syntatic 
					   2 : semantic */
char err_message[50];
char err_symbol[256];

char parameter[256];
int param_index[69];
int param_num = 0;

int dumpFlag = 0;  /* 0 : no dump ; 1 : dump */  
int scopeFlag = 0;  /* 1 : add scope */

int if_num = 0;
int lcb = 0;

/* symbol table's struct */
struct symbol{
	int index;
	char name[256];
	char entry_type[10];
	char data_type[10];
	int scope_level;
	char attribute[256];
	int exist;
}**symbol_table;

/* Symbol table function - you can add new function if needed. */
int lookup_symbol(char *name, int scope_level, int symbol_num);
void create_symbol(int num);
void insert_symbol(int index, char *name, char *entry_type, char *data_type, int scope_level, char *param, int existFlag);
void dump_symbol(int symbol_num, int scope);

void semantic_error();
void error(int type, char *message, char *symbol);

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char string[256];
}

/* Token without return */
%token PRINT 
%token IF ELSE FOR WHILE
%token SEMICOLON
%token ADD SUB MUL DIV MOD INC DEC
%token MT LT MTE LTE EQ NE
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN
%token AND OR NOT
%token LB RB LCB RCB LSB RSB COMMA QUOTA
%token TRUE FALSE
%token COMMENTLINE NEWLINE
%token RET CONT BREAK

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST
%token <string> INT FLOAT BOOL STRING VOID 
%token <string> ID

/* Nonterminal with return, which need to sepcify type */
%type <string> type

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : program stat
    |
;

stat
    : declaration
	| expression_stat
	| compound_stat 
	| jump_stat
    | print_func
	| COMMENTLINE
	| NEWLINE
		{ 
			if(strlen(buf) < 1)
				printf("%d:\n",yylineno);
			else
				printf("%d: %s\n", yylineno, buf); 
			if(err_type == 2){	
				semantic_error();
			}
			if(dumpFlag == 1){
				dump_symbol(symbol_num,scope);
				if(scopeFlag == 0)
					scope--;
				dumpFlag = 0;
				scopeFlag = 0;
			}
			memset(buf, 0, sizeof(buf));  // clear the buf
		}

;

declaration
    : type ID ASGN initializer
		{			
			if(lookup_symbol($2, scope, symbol_num) != -2){
				insert_symbol(symbol_num, $2, "variable", $1, scope, NULL, 0);
				symbol_num++;
			}
			else 
				error(2,"Redeclared variable",$2);
		}
    | type ID
		{			
			if(lookup_symbol($2, scope, symbol_num) != -2){
				insert_symbol(symbol_num, $2, "variable", $1, scope, NULL,0);
				symbol_num++;
			}
			else
				error(2,"Redeclared variable",$2);
		}
	| type ID LB parameter_list RB
		{			
			int lookup = lookup_symbol($2, scope, symbol_num);
			if(lookup == -2 || lookup >= 0)
				error(2,"Redeclared function",$2);

			for(int i=0; i<param_num; i++){
				memset(symbol_table[param_index[i]], 0, sizeof(struct symbol));
				symbol_table[param_index[i]]->scope_level = -1;
			}
			symbol_num = symbol_num - param_num;
			param_num = 0;
		
			if(lookup != -2 && lookup < 0){
				char temp[256] = {0};
				strncpy(temp,parameter,strlen(parameter)-2);
				insert_symbol(symbol_num, $2, "function", $1, scope, temp,1);
				symbol_num++;
			}
			memset(parameter,0,sizeof(parameter));
		}
	| type ID LB RB
		{			
			int lookup = lookup_symbol($2, scope, symbol_num);
			if(lookup == -2 || lookup >= 0)
				error(2,"Redeclared function",$2);
			else{
				insert_symbol(symbol_num, $2, "function", $1, scope, NULL,1);
				symbol_num++;
			}
		}

;

expression_stat
	: SEMICOLON
	| expr SEMICOLON
;

expr
	: assignment_expr
	| expr COMMA assignment_expr
;

assignment_expr
	: conditional_expr
	| unary_expr assignment_operator assignment_expr
;

assignment_operator
	: ASGN
	| MULASGN
	| DIVASGN
	| MODASGN
	| ADDASGN
	| SUBASGN
;

conditional_expr
	: logical_or_expr
;

logical_or_expr
	: logical_and_expr
	| logical_or_expr OR logical_and_expr
;

logical_and_expr
	: relational_expr
	| logical_and_expr AND relational_expr
;

relational_expr
	: additive_expr
	| relational_expr EQ additive_expr
	| relational_expr NE additive_expr
	| relational_expr LT additive_expr
	| relational_expr MT additive_expr
	| relational_expr LTE additive_expr
	| relational_expr MTE additive_expr
;

additive_expr
	: multiplicative_expr
	| additive_expr ADD multiplicative_expr
	| additive_expr SUB multiplicative_expr
;

multiplicative_expr
	: cast_expr
	| multiplicative_expr MUL cast_expr
	| multiplicative_expr DIV cast_expr
	| multiplicative_expr MOD cast_expr
;

cast_expr
	: unary_expr
	| LB type RB cast_expr
;

unary_expr
	: postfix_expr
	| unary_operator cast_expr
;

unary_operator
	: ADD
	| SUB
	| NOT
;

postfix_expr
	: primary_expr
	| ID LB RB
		{
			if(lookup_symbol($1, scope, symbol_num) == -1)
				error(2,"Undeclared function",$1);
		}
	| ID LB argument_list RB
		{
			if(lookup_symbol($1, scope, symbol_num) == -1)
				error(2,"Undeclared function",$1);
		}	
	| postfix_expr INC
	| postfix_expr DEC

;

primary_expr
	: ID
		{
			if(lookup_symbol($1, scope , symbol_num) == -1)
				error(2,"Undeclared variable",$1);
		}
	| I_CONST
	| F_CONST
	| STR_CONST
	| TRUE
	| FALSE
	| LB expr RB
;

compound_stat
	: IF LB expr RB LCB
		{
			lcb++;
			if_num++;
			scope++;
		}
	| RCB ELSE IF LB expr RB LCB
		{
			if(lcb<1 || if_num<1)
				yyerror("syntax error");
			dumpFlag= 1;
			scopeFlag = 1;
		}
	| RCB ELSE LCB
		{
			dumpFlag = 1;
			scopeFlag = 1;
			if(lcb < 1 || if_num<1)
				yyerror("syntax error");
			if_num--; 
		}
	| WHILE LB expr RB LCB
		{
			lcb++;
			scope++;
		}
	| type ID LB parameter_list RB LCB
		{
			lcb++;
			int lookup = lookup_symbol($2, scope, symbol_num);
			if(lookup == -1 || lookup == -3){
				char temp[256] = {0};
				strncpy(temp,parameter,strlen(parameter)-2);
				insert_symbol(symbol_num, $2, "function", $1, scope, temp, 0);
				symbol_num++;
				memset(parameter,0,sizeof(parameter));

			}
			else if(lookup >= 0){
				if(symbol_table[lookup]->attribute ==NULL){
					char temp[256] = {0};
					strncpy(temp,parameter,strlen(parameter)-2);
					strcpy(symbol_table[lookup]->attribute, temp);
					memset(parameter,0,sizeof(parameter)); // clear the parameters
				}
			}
			else
				error(2,"Redeclared function",$2);
	
			scope++;
	}
	| type ID LB RB LCB
		{
			lcb++;
			int lookup = lookup_symbol($2, scope, symbol_num); 
			if(lookup == -1 || lookup == -3){
				insert_symbol(symbol_num, $2, "function", $1, scope, NULL,0);
				symbol_num++;
			}
			else if(lookup == -2)
				error(2,"Redeclared function",$2);

			scope++;
		}
	| RCB
		{	
			lcb--;
			if(lcb<0){
				yyerror("syntax error");
			}
			if_num = 0;
			dumpFlag = 1;
		}

;

jump_stat
	: CONT SEMICOLON
	| BREAK SEMICOLON
	| RET SEMICOLON
	| RET expr SEMICOLON
;

print_func
	: PRINT LB STR_CONST RB
	| PRINT LB ID RB
		{
			if(lookup_symbol($3, scope, symbol_num) == -1)
				error(2,"Undeclared variable",$3);
		}

;

initializer
	: I_CONST
	| F_CONST
	| STR_CONST	
	| TRUE
	| FALSE
	| ID
		{
			if(lookup_symbol($1, scope, symbol_num) == -1)
				error(2,"Undeclared variable",$1);
		}
	| expr
;

parameter_list
	: parameter
	| parameter_list COMMA parameter
;

parameter
	: type ID
		{
			if(lookup_symbol($2, scope+1, symbol_num) != -2){
				insert_symbol(symbol_num, $2, "parameter", $1, scope+1, NULL,0);
				strcat(parameter,$1);
				strcat(parameter,", ");

				param_index[param_num] = symbol_num;
				symbol_num++;
				param_num++;
			}
			else{
				error(2,"Redeclared variable",$2);
			}
		}
;

argument_list
	: argument
	| argument_list COMMA argument
;

argument
	: ID
		{
			if(lookup_symbol($1, scope, symbol_num) == -1){
				error(2,"Undeclared variable",$1);
			}
		}

	| expr
;

/* actions can be taken when meet the token or rule */
type
    : INT	{ strcpy($$, "int"); }
    | FLOAT { strcpy($$, "float"); } 
    | BOOL	{ strcpy($$, "bool"); } 
    | STRING	{ strcpy($$, "string"); }
    | VOID	{ strcpy($$, "void"); }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;
    yyparse();
	if(lcb>0 && err_type != 1){
		yyerror("syntax error");
	}
	if(err_type != 1){
		dump_symbol(symbol_num,0);
		printf("\nTotal lines: %d \n",yylineno);
    }
	return 0;
}

void error(int type, char *message, char *symbol)
{	
	err_type = type;
    strcpy(err_message, message);
    strcpy(err_symbol, symbol);
}

void yyerror(char *s)
{
	printf("%d: %s\n", ++yylineno, buf); 
	if(err_type == 2)
		semantic_error();
	printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
	err_type = 1;
	memset(buf,0,sizeof(buf));
}

void semantic_error()
{
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
	printf("| %s %s", err_message, err_symbol);
    printf("\n|-----------------------------------------------|\n\n");
	err_type = 0;
}

void create_symbol(int num) 
{
	symbol_table = malloc(sizeof(struct symbol *) * num);
}

void insert_symbol(int index, char *name, char *entry_type, char *data_type, int scope_level, char *parameter, int existFlag)
{
	if(index==0)
		create_symbol(69);
	struct symbol *entry = malloc(sizeof(struct symbol));
	symbol_table[index] = entry;
	symbol_table[index]->index = index;	
	strcpy(symbol_table[index]->name, name);
	strcpy(symbol_table[index]->entry_type, entry_type);
	strcpy(symbol_table[index]->data_type, data_type);
	symbol_table[index]->scope_level = scope_level;
	if(parameter!=NULL)
		strcpy(symbol_table[index]->attribute, parameter);
	symbol_table[index]->exist = existFlag;
}

int lookup_symbol(char *name, int scope_level, int symbol_num)
{
	for(int i=0; i<symbol_num; i++){
		if(strcmp(name, symbol_table[i]->name)==0 && symbol_table[i]->scope_level==scope_level){
			/* entry number : if the symbol is a function and it has been forward declared */
			if(symbol_table[i]->exist==1)
				return i;
			/* -2 : if the symbol with same name and same scope exists, so can't be redeclared; */
			else
				return -2;
		}
		/* -3 : if the symbol with same name exists, and it is in seeable scope; */
		else if(strcmp(name, symbol_table[i]->name)==0 && symbol_table[i]->scope_level<scope_level)
			return -3;
	}
	/* -1 : if the symbol with same name and same scope doesn't exist, so can be inserted; */
	return -1;
}

void dump_symbol(int symbol_num, int scope) 
{
    int i;
	int indexnum;
	int insertFlag = 0;
	for(i=0; i<symbol_num; i++){
		if(symbol_table[i]->scope_level == scope){
			insertFlag = 1;
			break;
		}
	}
	if(insertFlag==1){
		printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           		"Index", "Name", "Kind", "Type", "Scope", "Attribute");
		for(i=0,indexnum=0; i<symbol_num; i++){
			if(symbol_table[i]->scope_level == scope){
				printf("%-10d%-10s%-12s%-10s%-10d%-s\n", indexnum, symbol_table[i]->name, symbol_table[i]->entry_type, symbol_table[i]->data_type, symbol_table[i]->scope_level, symbol_table[i]->attribute);
				indexnum++;
				memset(symbol_table[i],0,sizeof(struct symbol));
				symbol_table[i]->scope_level = -1;  // set to initial
			}
		}
		printf("\n");
	}
}
