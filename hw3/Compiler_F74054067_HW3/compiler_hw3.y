/*	Definition section */
%{

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

%}

%union {
	int i_val;
    double f_val;
	char string[696];
}

/* Token without return */
%token ADD SUB MUL DIV MOD INC DEC
%token MT LT MTE LTE EQ NE
%token AND OR NOT
%token LB RB LCB RCB LSB RSB COMMA QUOTA
%token PRINT IF ELSE FOR WHILE
%token RET CONT BREAK
%token NEWLINE SEMICOLON

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST TRUE FALSE
%token <f_val> F_CONST
%token <string> STR_CONST
%token <string> ID
%token <string> INT FLOAT BOOL STRING VOID
%token <string> ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN

/* Nonterminal with return, which need to sepcify type */
%type <string> type
%type <f_val> initializer
%type <f_val> val
%type <f_val> expression_stat expr
%type <f_val> assignment_expr
%type <f_val> conditional_expr logical_or_expr logical_and_expr relational_expr
%type <f_val> additive_expr multiplicative_expr
%type <f_val> cast_expr unary_expr
%type <f_val> postfix_expr primary_expr
%type <string> opassign_operator opassign_operand

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
	| NEWLINE
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

;

declaration
    : type ID ASGN initializer SEMICOLON
		{			
			if(lookup_symbol($2, SCOPE, symbol_num) != -2)
			{	
				char tmp[32];
				if(SCOPE==0)
				{
					insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, -1);
					gencode_function(".field public static ");
                    gencode_function($2);
                    gencode_function(" ");
					if(strcmp($1,"int")==0){
                        gencode_function("I = ");
                        sprintf(tmp, "%d\n", (int)$4);
                        gencode_function(tmp);
					}else if(strcmp($1, "float")==0){
						gencode_function("F = ");
                        sprintf(tmp, "%f\n", (double)$4);
                        gencode_function(tmp);
					}else if(strcmp($1, "bool")==0){
						gencode_function("Z = ");
                        sprintf(tmp, "%d\n", (int)$4);
                        gencode_function(tmp);
					}	
				}
				else
				{
					if(func_flag==1)
					{
						insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, func_reg);
						if(strcmp($1,"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)$4);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "float")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)$4);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "bool")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)$4);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						++func_reg;
					}
					else
					{	
						insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, reg);
						if(strcmp($1,"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)$4);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "float")==0)
						{	

							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)$4);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "bool")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)$4);
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
				error_type(2,"Redeclared variable",$2);
			}
		}
	| type ID ASGN STR_CONST SEMICOLON
		{			
			if(lookup_symbol($2, SCOPE, symbol_num) != -2)
			{
				char tmp[32];
				if(SCOPE==0)
				{
					insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, -1);
					if(strcmp($1,"string")==0)
					{	
						gencode_function(".field public static ");
                        gencode_function($2);
                        gencode_function(" ");
                        gencode_function("Ljava/lang/String; = ");
                        sprintf(tmp, "\"%s\"", $4);
                        gencode_function(tmp);
                        gencode_function("\n");	
					}
				}
				else
				{
					if(func_flag == 1)
					{
						insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, func_reg);
						if(strcmp($1,"string")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "\"%s\"\n", $4);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);	
						}
						++func_reg;
					}
					else
					{
						insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, reg);
						if(strcmp($1,"string")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "\"%s\"\n", $4);
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
				error_type(2,"Redeclared variable",$2);
			}
		}
   	| type ID SEMICOLON
		{			
			if(lookup_symbol($2, SCOPE, symbol_num) != -2)
			{
				char tmp[32];
				if(SCOPE==0)
				{
					insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, -1);
					gencode_function(".field public static ");
                    gencode_function($2);
                    gencode_function(" ");
					if(strcmp($1,"int")==0)
						gencode_function("I\n");
					else if(strcmp($1, "float")==0)
						gencode_function("F\n");
					else if(strcmp($1, "bool")==0)
						gencode_function("Z\n");
					else if(strcmp($1, "void")==0)
						gencode_function("V\n");
					else if(strcmp($1, "string")==0)
						gencode_function("Ljava/lang/String;\n");
				}
				else
				{
					if(func_flag == 1)
					{
						insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, func_reg);
						if(strcmp($1,"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "float")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "bool")==0)
						{
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", func_reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "string")==0)
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
						insert_symbol(symbol_num, $2, "variable", $1, SCOPE, NULL, 0, reg);
						if(strcmp($1,"int")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "float")==0)
						{	
							gencode_function("\tldc ");
							sprintf(tmp, "%f\n", (double)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "bool")==0)
						{
							gencode_function("\tldc ");
							sprintf(tmp, "%d\n", (int)0);
							gencode_function(tmp);
							gencode_function("\tistore ");
							sprintf(tmp, "%d\n", reg);
							gencode_function(tmp);
						}
						else if(strcmp($1, "string")==0)
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
				error_type(2,"Redeclared variable",$2);
			}
		}
		
	| type ID LB parameter_list RB SEMICOLON
		{			
			int lookup_result = lookup_symbol($2, SCOPE, symbol_num);
			if(lookup_result == -2 ||  (lookup_result >= 0 && symbol_table[lookup_result]->forward==1))
			{
				error_type(2,"Redeclared function",$2);
			}

			/* Dont't insert parameters to table when function declaration */
			for(int i=0; i<param_num; ++i)
			{
				memset(symbol_table[param_index[i]], 0, sizeof(struct symbol));
				symbol_table[param_index[i]]->scope = -1;
			}
			symbol_num -= param_num;
			param_num = 0;
		
			lookup_result = lookup_symbol($2, SCOPE, symbol_num);
			/* Insert funcion */
			if(lookup_result != -2 && lookup_result < 0)
			{
				char temp[256] = {0};
				strncpy(temp,params,strlen(params)-2);
				insert_symbol(symbol_num, $2, "function", $1, SCOPE, temp, 1, -1);
				++symbol_num;
			}
			else if(lookup_result>=0 && symbol_table[lookup_result]->forward==2)
			{
				char temp[256] = {0};
				strncpy(temp,params,strlen(params)-2);
	
				if(strcmp($1, symbol_table[lookup_result]->data_type)!=0)
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
	| type ID LB RB SEMICOLON
		{			
			int lookup_result = lookup_symbol($2, SCOPE, symbol_num);
			if(lookup_result == -2 || (lookup_result >= 0 && symbol_table[lookup_result]->forward==1))
			{
				error_type(2,"Redeclared function",$2);
			}
			else if(lookup_result!=-2 && lookup_result<0)
			{
				insert_symbol(symbol_num, $2, "function", $1, SCOPE, NULL, 1, -1);
				++symbol_num;
			}
			else if(lookup_result>=0 && symbol_table[lookup_result]->forward==2)
			{
				if(strcmp($1, symbol_table[lookup_result]->data_type)!=0)
				{
					error_type(3,"function return type does not match","");
				}
				else if(strlen(symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
				}
	
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
	: conditional_expr	{ $$ = $1; }
	| ID ASGN assignment_expr
		{
			char tmp[32];
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",$1);
			}
			else
			{
				int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{
					fprintf(file, "\tputstatic compiler_hw3/%s ", $1);  // putstatic -> stored
					char type[10] = {0};
					strcpy(type, get_type($1, SCOPE, symbol_num));
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
	| opassign_operand opassign_operator assignment_expr
		{
			char tmp[32];
			if(operand_type == 'I' || operand_type == 'Z')
			{	
				if(strcmp($2, "+=")==0)
					gencode_function("\tiadd\n");
				else if(strcmp($2, "-=")==0)
					gencode_function("\tisub\n");
				else if(strcmp($2, "*=")==0)
					gencode_function("\timul\n");
				else if(strcmp($2, "/=")==0)
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
						gencode_function("\tidiv\n");
				}
				else if(strcmp($2, "%=")==0)
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
						gencode_function("\tirem\n");
				}
			}
			else if(operand_type == 'F')
			{
				if(strcmp($2, "+=")==0)
					gencode_function("\tfadd\n");
				else if(strcmp($2, "-=")==0)
					gencode_function("\tfsub\n");
				else if(strcmp($2, "*=")==0)
					gencode_function("\tfmul\n");
				else if(strcmp($2, "/=")==0)
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
						gencode_function("\tfdiv\n");
				}
				else if(strcmp($2, "%=")==0)
					error_type(3,"Modulo operator(%) with floating point operands","");
			}
				
			int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
			if(reg==-1)		// global variable
			{
				fprintf(file, "\tputstatic compiler_hw3/%s ", $1);
				char type[10] = {0};
				strcpy(type, get_type($1, SCOPE, symbol_num));
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
;

opassign_operand
	: ID
		{
			strcpy($$, $1);
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",$1);
			}
			else
			{
				char tmp[32];
				int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					char type[10] = {0};
					strcpy(type, get_type($1, SCOPE, symbol_num));
					gencode_function("\tgetstatic compiler_hw3/");	// getstatic -> loaded
					sprintf(tmp,"%s ", $1);
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
;

opassign_operator
	: ADDASGN	{ strcpy($$,"+="); }
	| SUBASGN	{ strcpy($$, "-="); }
	| MULASGN	{ strcpy($$, "*="); }
	| DIVASGN	{ strcpy($$, "/="); }
	| MODASGN	{ strcpy($$, "%="); }
;

conditional_expr
	: logical_or_expr	{ $$ = $1; }
;

logical_or_expr
	: logical_and_expr	{ $$ = $1; }
	| logical_or_expr OR logical_and_expr
;

logical_and_expr
	: relational_expr	{ $$ = $1; }
	| logical_and_expr AND relational_expr
;

relational_expr
	: additive_expr	{ $$ = $1; }
	| relational_operand EQ relational_operand
		{
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'E';
		}
	| relational_operand NE relational_operand
		{
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'N';
		}
	| relational_operand LT relational_operand
		{
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F')
				gencode_function("\tfsub\n");
			relation_type = 'l';
		}
	| relational_operand MT relational_operand
		{
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'm';
		}
	| relational_operand LTE relational_operand
		{
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'L';
		}
	| relational_operand MTE relational_operand
		{
			if(operand_type == 'I')
				gencode_function("\tisub\n");
			else if(operand_type == 'F'){
				gencode_function("\tfsub\n");
				gencode_function("\tf2i\n");
			}
			relation_type = 'M';
		}
;

relational_operand
	: I_CONST
		{
			char tmp[32];
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			gencode_function("\tldc ");
			sprintf(tmp,"%d\n",$1);
			gencode_function(tmp);
			operand_type = 'I';
		}
	| F_CONST
		{
			char tmp[32];
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}
			gencode_function("\tldc ");
			sprintf(tmp,"%f\n",$1);
			gencode_function(tmp);
			operand_type = 'F';
		}
	| TRUE
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
	| FALSE
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
	| ID
		{
			if(if_end_flag[SCOPE-1]==1)
			{
				fprintf(file, "\tgoto EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
				fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
				if_end_flag[SCOPE-1] = 0; 
			}

			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",$1);
			}
			else
			{
				char tmp[32];
				int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					char type[10] = {0};
					strcpy(type, get_type($1, SCOPE, symbol_num));
					gencode_function("\tgetstatic compiler_hw3/");
					sprintf(tmp,"%s ",$1);
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
;

additive_expr
	: multiplicative_expr	{ $$ = $1; }
	| additive_expr ADD multiplicative_expr
		{
			$$ = $1 + $3;
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
	| additive_expr SUB multiplicative_expr
		{
			$$ = $1 - $3;
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
;

multiplicative_expr
	: cast_expr	{ $$ = $1; }
	| multiplicative_expr MUL cast_expr
		{
			$$ = $1 * $3;
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
	| multiplicative_expr DIV cast_expr
		{
			if(zero_flag==1)
			{
				error_type(3,"devided by zero","");
			}
			else
			{
				$$ = $1 / $3;
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
	| multiplicative_expr MOD cast_expr
		{	
			switch(operand_type)
			{
				case 'I':
				{
					if(zero_flag==1)
						error_type(3,"devided by zero","");
					else
					{
						$$ = (int)$1 % (int)$3;
						gencode_function("\tirem\n");
					}
					break;
				}
				case 'F':  // float cannot do mod
					error_type(3,"Modulo operator(%) with floating point operands","");
					break;
			}
		}
;

cast_expr
	: unary_expr	{ $$ = $1; } 
	| LB type RB cast_expr
;

unary_expr
	: postfix_expr	{ $$ = $1; }
	| unary_operator cast_expr
;

unary_operator
	: ADD
	| SUB
	| NOT
;

postfix_expr
	: primary_expr	{ $$ = $1; }
	| ID LB RB
		{
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{	
				error_type(2,"Undeclared function",$1);
			}
			else
			{
				fprintf(file, "\tinvokestatic compiler_hw3/%s()", $1);
				char type[10] = {0};
				strcpy(type, get_type($1,SCOPE,symbol_num));
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
	| ID LB argument_list RB
		{
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared function",$1);
			}
			else
			{
				fprintf(file, "\tinvokestatic compiler_hw3/%s(", $1);
				char temp[256] = {0};
				strcpy(temp, get_attribute($1, SCOPE, symbol_num));
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
				strcpy(type, get_type($1,SCOPE,symbol_num));
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
	| ID INC
		{
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",$1);
			}
			else
			{
				char tmp[32];
				int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					fprintf(file, "\tgetstatic compiler_hw3/%s I\n", $1);	// loaded
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
					fprintf(file, "\tputstatic compiler_hw3/%s I\n", $1);	// stored
				}
				else	// local variable
				{
					gencode_function("\tistore ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
			}
		}
	| ID DEC
		{
			char tmp[32];
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",$1);
			}
			else
			{
				int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					fprintf(file, "\tgetstatic compiler_hw3/%s I\n", $1);
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
					fprintf(file, "\tputstatic compiler_hw3/%s I\n", $1);
				}
				else	// local variable
				{
					gencode_function("\tistore ");
					sprintf(tmp,"%d\n",reg);
					gencode_function(tmp);
				}
			}
		}
;

primary_expr
	: val	{ $$ = $1;  }
	| LB expr RB
;

compound_stat
	: IF LB expr RB LCB
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
	| RCB ELSE IF LB expr RB LCB
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
	| RCB ELSE LCB
		{
			dump_flag = 1;
			add_scope = 1;
			
			if_end_flag[SCOPE-1] = 0;
			fprintf(file, "\tgoto  EXIT%d_%d\n", SCOPE-1, if_num[SCOPE-1]);
			fprintf(file, "END%d_%d_%d:\n", SCOPE-1, if_num[SCOPE-1], if_branch_num[SCOPE-1]);
		}
	| while LB expr RB LCB
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
	| type ID LB parameter_list RB LCB
		{
			int lookup_result = lookup_symbol($2, SCOPE, symbol_num);
			if(lookup_result == -1 || lookup_result == -3)	// If function undeclared, insert it and its parameters
			{
				func_flag = 1;
				char temp[256]= {0};
				strncpy(temp,params,strlen(params)-2);
				insert_symbol(symbol_num, $2, "function", $1, SCOPE, temp, 2, -1);
				++symbol_num;
				memset(params,0,sizeof(params));
				
				fprintf(file, ".method public static %s(",$2);
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
				if(strcmp($1,"int")==0)
				{
					return_type = 'I';
					gencode_function(")I\n");
				}
				else if(strcmp($1,"float")==0)
				{
					return_type = 'F';
					gencode_function(")F\n");
				}
				else if(strcmp($1,"bool")==0)
				{
					return_type = 'Z';
					gencode_function(")Z\n");
				}
				else if(strcmp($1, "string")==0)
				{
					return_type = 's';
					gencode_function(")Ljava/lang/String;\n");
				}
				else if(strcmp($1, "void")==0)
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

				if(strcmp($1, symbol_table[lookup_result]->data_type) != 0)
				{
					error_type(3,"function return type does not match","");
					if(strcmp($1,"int")==0)
						return_type = 'I';
					else if(strcmp($1,"float")==0)
						return_type = 'F';
					else if(strcmp($1,"bool")==0)
						return_type = 'Z';
					else if(strcmp($1, "string")==0)
						return_type = 's';
					else if(strcmp($1, "void")==0)
						return_type = 'V';
				}
				else if(strcmp(temp,symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
					if(strcmp($1,"int")==0)
						return_type = 'I';
					else if(strcmp($1,"float")==0)
						return_type = 'F';
					else if(strcmp($1,"bool")==0)
						return_type = 'Z';	
					else if(strcmp($1, "string")==0)
						return_type = 's';
					else if(strcmp($1, "void")==0)
						return_type = 'V';
				}
				else 
				{
					if(symbol_table[lookup_result]->attribute==NULL)
					{
						strcpy(symbol_table[lookup_result]->attribute, temp);
						memset(params,0,sizeof(params));
					}
	
					fprintf(file, ".method public static %s(",$2);
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
					if(strcmp($1,"int")==0)
					{
						return_type = 'I';
						gencode_function(")I\n");
					}
					else if(strcmp($1,"float")==0)
					{
						return_type = 'F';
						gencode_function(")F\n");
					}
					else if(strcmp($1,"bool")==0)
					{
						return_type = 'Z';
						gencode_function(")Z\n");
					}	
					else if(strcmp($1, "string")==0)
					{
						return_type = 's';
						gencode_function(")Ljava/lang/String;\n");
					}
					else if(strcmp($1, "void")==0)
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
				error_type(2,"Redeclared function",$2);
			}
	
			++SCOPE;
	}
	| type ID LB RB LCB
		{
			int lookup_result = lookup_symbol($2, SCOPE, symbol_num); 
			if(lookup_result == -1 || lookup_result == -3)
			{
				func_flag = 1;
				insert_symbol(symbol_num, $2, "function", $1, SCOPE, NULL, 2, -1);
				++symbol_num;

				if(strcmp($2,"main")==0)
				{
					gencode_function(".method public static main([Ljava/lang/String;)V\n");
					gencode_function(".limit stack 50\n");
					gencode_function(".limit locals 50\n");
					if(strcmp($1,"int")==0)
						return_type = 'I';
					else if(strcmp($1,"float")==0)
						return_type = 'F';
					else if(strcmp($1,"bool")==0)
						return_type = 'Z';
					else if(strcmp($1, "string")==0)
						return_type = 's';
					else if(strcmp($1, "void")==0)
						return_type = 'V';	
				}
				else
				{
					fprintf(file, ".method public static %s()", $2);
					if(strcmp($1,"int")==0)
					{
						return_type = 'I';
						gencode_function(")I\n");
					}
					else if(strcmp($1,"float")==0)
					{
						return_type = 'F';
						gencode_function(")F\n");
					}
					else if(strcmp($1,"bool")==0)
					{
						return_type = 'Z';
						gencode_function(")Z\n");
					}
					else if(strcmp($1, "string")==0)
					{
						return_type = 's';
						gencode_function(")Ljava/lang/String;\n");
					}
					else if(strcmp($1, "void")==0)
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
				if(strcmp($1, symbol_table[lookup_result]->data_type)!=0)
				{
					error_type(3,"function return type does not match","");
					if(strcmp($1,"int")==0)
						return_type = 'I';
					else if(strcmp($1,"float")==0)
						return_type = 'F';
					else if(strcmp($1,"bool")==0)
						return_type = 'Z';
					else if(strcmp($1, "string")==0)
						return_type = 's';
					else if(strcmp($1, "void")==0)
						return_type = 'V';
				}
				else if(strlen(symbol_table[lookup_result]->attribute)!=0)
				{
					error_type(3,"function formal parameter is not the same","");
					if(strcmp($1,"int")==0)
						return_type = 'I';
					else if(strcmp($1,"float")==0)
						return_type = 'F';
					else if(strcmp($1,"bool")==0)
						return_type = 'Z';
					else if(strcmp($1, "string")==0)
						return_type = 's';
					else if(strcmp($1, "void")==0)
						return_type = 'V';
				}
				else
				{
					if(strcmp($2,"main")==0)
					{
						gencode_function(".method public static main([Ljava/lang/String;)V\n");
						gencode_function(".limit stack 50\n");
						gencode_function(".limit locals 50\n");
						if(strcmp($1,"int")==0)
							return_type = 'I';
						else if(strcmp($1,"float")==0)
							return_type = 'F';
						else if(strcmp($1,"bool")==0)
							return_type = 'Z';
						else if(strcmp($1, "string")==0)
							return_type = 's';
						else if(strcmp($1, "void")==0)
							return_type = 'V';
					}
					else
					{
						fprintf(file, ".method public static %s()",$2);
						if(strcmp($1,"int")==0)
						{
							return_type = 'I';
							gencode_function("I\n");
						}
						else if(strcmp($1,"float")==0)
						{
							return_type = 'F';
							gencode_function("F\n");
						}
						else if(strcmp($1,"bool")==0)
						{
							return_type = 'Z';
							gencode_function("Z\n");
						}
						else if(strcmp($1, "string")==0)
						{
							return_type = 's';
							gencode_function("Ljava/lang/String;\n");
						}
						else if(strcmp($1, "void")==0)
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
				error_type(2,"Redeclared function",$2);
			}

			++SCOPE;
		}
	| RCB
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

;

while
	: WHILE
		{
			++while_num[SCOPE];
			while_exit_flag[SCOPE] = 1;
			fprintf(file, "LABEL_BEGIN%d_%d:\n", SCOPE, while_num[SCOPE]);
		}
;

jump_stat
	: CONT SEMICOLON
	| BREAK SEMICOLON
	| RET SEMICOLON
		{
			if(return_type == 'V')
				gencode_function("\treturn\n.end method\n");
			else
				error_type(3,"function return type does not match","");
			return_type = 0;
		}
	| RET expr SEMICOLON
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
;

print_func
	: PRINT LB I_CONST RB
		{
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp, "%d\n", $3);
			gencode_function(tmp);
			gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        	gencode_function("\tswap\n");
        	gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
		}
	| PRINT LB F_CONST RB
		{
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp, "%f\n", $3);
			gencode_function(tmp);
			gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        	gencode_function("\tswap\n");
        	gencode_function("\tinvokevirtual java/io/PrintStream/println(F)V\n");
		}
	| PRINT LB STR_CONST RB
		{
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp, "\"%s\"\n", $3);
			gencode_function(tmp);
			gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        	gencode_function("\tswap\n");
        	gencode_function("\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
		}
	| PRINT LB ID RB
		{
			if(lookup_symbol($3, SCOPE, symbol_num) == -1)
			{
				error_type(2,"Undeclared variable",$3);
			}
			else
			{
				int reg = get_register(symbol_table, $3, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{
					char tmp[32];
					char type[10] = {0};
					strcpy(type, get_type($3, SCOPE, symbol_num));
					if(strcmp(type,"int")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s I\n", $3);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
					}
					else if(strcmp(type,"float")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s F\n", $3);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(F)V\n");			
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s Z\n", $3);
						gencode_function(tmp);
						gencode_function("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        				gencode_function("\tswap\n");
        				gencode_function("\tinvokevirtual java/io/PrintStream/println(I)V\n");
					}
					else if(strcmp(type, "string")==0)
					{	
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp, "%s Ljava/lang/String;\n", $3);
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

;

initializer
	: ID
		{
			if(lookup_symbol($1, SCOPE, symbol_num) == -1)
				error_type(2,"Undeclared variable",$1);
	  	}
	| I_CONST	{ $$ = $1; }
	| F_CONST	{ $$ = $1; }
	| TRUE	{ $$ = 1; }
	| FALSE	{ $$ = 0; }
	| expr
;

parameter_list
	: parameter
	| parameter_list COMMA parameter
;

parameter
	: type ID
		{
			if(lookup_symbol($2, SCOPE+1, symbol_num) != -2)
			{
				insert_symbol(symbol_num, $2, "parameter", $1, SCOPE+1, NULL, 0, func_reg);
				strcat(params,$1);
				strcat(params,", ");
				param_index[param_num] = symbol_num;	// Record the index for removing later when function declaration
				
				if(strcmp($1,"int")==0)
				{
					func_reg_type[param_num] = 'I';
				}
				else if(strcmp($1,"float")==0)
				{		
					func_reg_type[param_num] = 'F';
				}
				else if(strcmp($1,"bool")==0)
				{	
					func_reg_type[param_num] = 'Z';
				}
				else if(strcmp($1, "string")==0)
				{	
					func_reg_type[param_num] = 's';
				}
				else if(strcmp($1, "void")==0)
				{	
					func_reg_type[param_num] = 'V';
				}
			
				++symbol_num;
				++param_num;
				++func_reg;
			}
			else
			{
				error_type(2,"Redeclared variable",$2);
				strcat(params,$1);
				strcat(params,", ");
			}
		}
;

argument_list
	: argument
	| argument_list COMMA argument
;

argument
	: expr
;

val
	: ID
		{
			int lookup_result = lookup_symbol($1, SCOPE, symbol_num);
			if(lookup_result == -1)
			{
				error_type(2,"Undeclared variable",$1);
			}
			else
			{
				int reg = get_register(symbol_table, $1, SCOPE, symbol_num);
				if(reg==-1)		// global variable
				{	
					char tmp[32];
					char type[10] = {0};
					strcpy(type, get_type($1, SCOPE, symbol_num));
					if(strcmp(type,"int")==0)
					{
						if(operand_type==0 || operand_type=='I')
						{
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s I\n", $1);
							gencode_function(tmp);
							operand_type = 'I';
						}
						else if(operand_type == 'F')
						{
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s I\n", $1);
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
							sprintf(tmp,"%s F\n", $1);
							gencode_function(tmp);
							operand_type = 'F';
						}
						else if(operand_type == 0 || operand_type =='F')
						{
							gencode_function("\tgetstatic compiler_hw3/");
							sprintf(tmp,"%s F\n", $1);
							gencode_function(tmp);
							operand_type = 'F';
						}					
					}
					else if(strcmp(type,"bool")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp,"%s Z\n", $1);
						gencode_function(tmp);
						operand_type = 'Z';
					}
					else if(strcmp(type, "string")==0)
					{
						gencode_function("\tgetstatic compiler_hw3/");
						sprintf(tmp,"%s Ljava/lang/String;\n", $1);
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
	| I_CONST	
		{	
			char tmp[32];
			if(operand_type==0 || operand_type=='I')
			{
				$$ = (int)$1;
				gencode_function("\tldc ");
				sprintf(tmp,"%d\n", (int)$1);
				gencode_function(tmp);
				operand_type = 'I';
			}
			else if(operand_type == 'F')
			{
				$$ = (double)$1;
				gencode_function("\tldc ");
				sprintf(tmp,"%d\n", (int)$1);
				gencode_function(tmp);

				gencode_function("\ti2f\n");
				operand_type = 'F';
			}
			if(zero_flag == 1)
				zero_flag = 0;
			if($$ == 0)
				zero_flag = 1;
		}
	| F_CONST
		{		
			char tmp[32];
			$$ = (double)$1;
			if(operand_type=='I')
			{
				gencode_function("\ti2f\n");

				gencode_function("\tldc ");
				sprintf(tmp,"%f\n", (double)$1);
				gencode_function(tmp);
				operand_type = 'F';
			}
			else if(operand_type==0 || operand_type =='F')
			{
				gencode_function("\tldc ");
				sprintf(tmp,"%f\n", (double)$1);
				gencode_function(tmp);
				operand_type = 'F';
			}
			if(zero_flag == 1)
				zero_flag = 0;
			if($$ == 0)
				zero_flag = 1;
		}
	| STR_CONST	
		{
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp,"\"%s\"\n", $1);
			gencode_function(tmp);
			operand_type = 's';
		}
	| TRUE	
		{	
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp,"%d\n", (int)1);
			gencode_function(tmp);
			$$ = (int)1;
			operand_type = 'Z';
		}
	| FALSE	
		{	
			char tmp[32];
			gencode_function("\tldc ");
			sprintf(tmp,"%d\n", (int)0);
			gencode_function(tmp);
			$$ = (int)0;
			operand_type = 'Z';
		}
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
