/*	Definition section */
%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex
char errbuff[256];
int SCOPE = 0;

typedef struct symbol{
    char name[30];
    char kind[15];
    char type[8];
    int scope;
    char attribute[30];
    struct symbol* next;
}symbol;
symbol *head = NULL;
/* Symbol table function - you can add new function if needed. */

symbol* create_symbol(char name[], char kind[], char type[], int scope, char attribute[]);
void insert_symbol(symbol* new_symbol);
int lookup_symbol(char name[], int scope, char kind[]);
void dump_symbol();
void print_symbol(symbol *p);
void print_all();

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char string[100];
}

/* Token without return */
%token ADD SUB MUL DEV MOD INC DEC
%token MT LT MTE LTE EQ NE
%token ASGN ADDASGN SUBASGN MULASGN DEVASGN MODASGN
%token AND OR NOT
%token PRINT 
%token IF ELSE FOR WHILE
%token SEMICOLON
%token LB RB LCB RCB LSB RSB COMMA
%token INT FLOAT VOID BOOL STRING
%token TRUE FALSE RET


/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST
%token <string> ID

/* Nonterminal with return, which need to sepcify type */
%type <string> type
%type <string> parameter_list
/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : program external_declaration
    | external_declaration
;

external_declaration
    : function_definition 
    | function_declaration
    | declaration
;

function_definition
    : type ID LB RB compound_stmt {
        if(lookup_symbol($2,SCOPE,"") == 0){
            symbol *new_symbol = create_symbol($2,"function",$1,SCOPE,"");
            insert_symbol(new_symbol);
        }
    }
    | type ID LB parameter_list RB compound_stmt {
        if(lookup_symbol($2,SCOPE,"") == 0){
            symbol *new_symbol = create_symbol($2,"function",$1,SCOPE,$4);
            insert_symbol(new_symbol);
        }
    }
;
function_declaration
    : type ID LB RB SEMICOLON {
        if(lookup_symbol($2,SCOPE,"") == 1){
            char s[50] = "";
            strcat(s,"Redeclared function ");
            strcat(s,$2);
            strcpy(errbuff,s);
        } else {
            symbol *new_symbol = create_symbol($2,"function",$1,SCOPE,"");
            insert_symbol(new_symbol);
        }
    }
    | type ID LB parameter_list RB SEMICOLON {
        if(lookup_symbol($2,SCOPE,"") == 1){
            char s[50] = "";
            strcat(s,"Redeclared function ");
            strcat(s,$2);
            strcpy(errbuff,s);
        } else {
            symbol *new_symbol = create_symbol($2,"function",$1,SCOPE,$4);
            insert_symbol(new_symbol);
        }
    }
    
;
stmt_list
    : stmt
    | stmt_list stmt
;
stmt
    : compound_stmt
    | expr_stmt
    | selection_stmt
    | iteration_stmt
    | jump_stmt
    | print_func
    | declaration_list
;
compound_stmt
    : lcb rcb
    | lcb stmt_list rcb
    | lcb declaration_list rcb
    | lcb declaration_list stmt_list rcb
;
lcb
    : LCB { SCOPE++; }
;
rcb
    : RCB { SCOPE--; }
;
expr_stmt
    : SEMICOLON
    | expr SEMICOLON
;
selection_stmt
    : IF LB expr RB stmt
    | IF LB expr RB stmt ELSE stmt
;
iteration_stmt
    : WHILE LB expr RB stmt
    | FOR LB expr_stmt expr_stmt RB stmt
    | FOR LB expr_stmt expr_stmt expr RB stmt
;
jump_stmt
    : RET SEMICOLON
    | RET expr SEMICOLON
;

declaration_list
    : declaration
    | declaration_list declaration
;

declaration
    : type ID ASGN initializer SEMICOLON{
        if(lookup_symbol($2,SCOPE,"") == 1){
            char s[50] = "";
            strcat(s,"Redeclared variable ");
            strcat(s,$2);
            strcpy(errbuff,s);
        } else {
            symbol *new_symbol = create_symbol($2,"variable",$1,SCOPE,"");
            insert_symbol(new_symbol);
        }
    }
    | type ID SEMICOLON {
        if(lookup_symbol($2,SCOPE,"") == 1){
            char s[50] = "";
            strcat(s,"Redeclared variable ");
            strcat(s,$2);
            strcpy(errbuff,s);
        }else {
            symbol *new_symbol = create_symbol($2,"variable",$1,SCOPE,"");
            insert_symbol(new_symbol);
        }
    }
;

initializer
    : assignment_expr
;

assignment_expr
    : unary_expr assignment_operator assignment_expr
    | conditional_expr
;

conditional_expr
    : equality_expr
;

equality_expr
    : relational_expr
    | equality_expr EQ relational_expr
    | equality_expr NE relational_expr
;

relational_expr
    : add_expr
    | relational_expr MT add_expr
    | relational_expr LT add_expr
    | relational_expr MTE add_expr
    | relational_expr LTE add_expr
;

add_expr
    : mul_expr
    | add_expr ADD mul_expr
    | add_expr SUB mul_expr
;

mul_expr
    : unary_expr
    | mul_expr MUL unary_expr
    | mul_expr DEV unary_expr
    | mul_expr MOD unary_expr
;

unary_expr
    : postfix_expr
    | INC unary_expr
    | DEC unary_expr
    | ADD unary_expr
    | SUB unary_expr
;

postfix_expr
    : primary_expr
    | postfix_expr INC
    | postfix_expr DEC
    | ID LB RB {
        int ss = SCOPE;
        int boolval = 0;
        for(; ss >= 0; ss--){
            if(lookup_symbol($1,ss,"function") == 1){
                boolval = 1;
                break;
            }
        }
        if(boolval == 0){
            char s[50] = "";
            strcat(s,"Undeclared function ");
            strcat(s,$1);
            strcpy(errbuff,s);
        }
    }
    | ID LB argument_expr_list RB {
        int ss = SCOPE;
        int boolval = 0;
        for(; ss >= 0; ss--){
            if(lookup_symbol($1,ss,"function") == 1){
                boolval = 1;
                break;
            }
        }
        if(boolval == 0){
            char s[50] = "";
            strcat(s,"Undeclared function ");
            strcat(s,$1);
            strcpy(errbuff,s);
        }
    }
;

argument_expr_list
    : assignment_expr
    | argument_expr_list COMMA assignment_expr
;
primary_expr
    : ID {
        int ss = SCOPE;
        int boolval = 0;
        for(; ss >= 0; ss--){
            if(lookup_symbol($1,ss,"") == 1){
                boolval = 1;
                break;
            }
        }
        if(boolval == 0){
            char s[50] = "";
            strcat(s,"Undeclared variable ");
            strcat(s,$1);
            strcpy(errbuff,s);
        }
    }
    | I_CONST
    | F_CONST
    | STR_CONST
    | TRUE
    | FALSE
    | LB expr RB
;
expr
    : assignment_expr
    | expr COMMA assignment_expr
;
assignment_operator
    : ASGN
    | ADDASGN
    | SUBASGN
    | MULASGN
    | DEVASGN
    | MODASGN
;
type
    : INT       { strcpy($$, "int"); }
    | FLOAT     { strcpy($$, "float"); }
    | BOOL      { strcpy($$, "bool"); }
    | STRING    { strcpy($$, "string"); }
    | VOID      { strcpy($$, "void"); }
;

parameter_list
    : parameter_list COMMA type ID {
        if(lookup_symbol($4,SCOPE+1,"parameter") == 1){
            char s[50] = "";
            strcat(s,"Redeclared variable ");
            strcat(s,$4);
            strcpy(errbuff,s);
        }else {
            symbol *new_symbol = create_symbol($4,"parameter",$3,SCOPE+1,"");
            insert_symbol(new_symbol);
            strcpy($$,$1);
            strcat($$,", ");
            strcat($$,$3);
        }
    }
    | type ID {
        if(lookup_symbol($2,SCOPE+1,"parameter") == 1){
            char s[50] = "";
            strcat(s,"Redeclared variable ");
            strcat(s,$2);
            strcpy(errbuff,s);
        }else {
            symbol *new_symbol = create_symbol($2,"parameter",$1,SCOPE+1,"");
            insert_symbol(new_symbol);
            strcpy($$,$1);
        }
    }
;

print_func
    : PRINT LB ID RB SEMICOLON {
        int ss = SCOPE;
        int boolval = 0;
        for(; ss >= 0; ss--){
            if(lookup_symbol($3,ss,"") == 1){
                boolval = 1;
                break;
            }
        }
        if(boolval == 0){
            char s[50] = "";
            strcat(s,"Undeclared variable ");
            strcat(s,$3);
            strcpy(errbuff,s);
        }
    }
    | PRINT LB STR_CONST RB SEMICOLON
;

/* actions can be taken when meet the token or rule */
%%

/* C code section */
int main(int argc, char** argv)
{
    head = NULL;
    
    yylineno = 0;
    strcpy(buf,"");
    yyparse();

    return 0;
}

void yyerror(char *s)
{
    if(strcmp(s,"syntax error") == 0 && strlen(errbuff) >0)
    {
        printf("%d: %s\n", ++yylineno, buf); 
        yyerror(errbuff);
    }
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
    //print_all();
}

symbol* create_symbol(char name[], char kind[], char type[], int scope, char attribute[]) {
    symbol *new_symbol = (symbol*)malloc(sizeof(symbol));
    strcpy(new_symbol->name,name);
    strcpy(new_symbol->kind,kind);
    strcpy(new_symbol->type,type);
    new_symbol -> scope = scope;
    strcpy(new_symbol->attribute,attribute);
    new_symbol -> next = NULL;
    return new_symbol;
}
void insert_symbol(symbol* new_symbol) {
    if(head == NULL)
    {   
        head = new_symbol;
        return;
    }
    symbol *prev = NULL; 
    symbol *current = head; 
    while(current != NULL)
    {
        if(new_symbol->scope > current->scope)
            break;
        prev = current;
        current = current->next;
    }
    if(prev == NULL){
        new_symbol->next = current;
        head = new_symbol;
    } else {
        prev->next = new_symbol;
        new_symbol->next = current;
    }
}
int lookup_symbol(char name[], int scope, char kind[]) {
    symbol *first = head;
    int boolval = 0;
    for(; first != NULL; first = first -> next)
    {
        if(strcmp(kind,"") != 0){
            if(strcmp(name,first->name) == 0 && first->scope==scope && strcmp(kind,first->kind)==0 )
                boolval = 1;
        } else {
            if(strcmp(name,first->name) == 0 && first->scope==scope )
                boolval = 1;
        }        
    }
    return boolval;
}
void dump_symbol() {
    symbol *first = head;
    int boolval = 0;
    for(; first != NULL; first = first -> next)
    {
        if(first->scope==SCOPE)
            boolval = 1;
    }
    if(boolval == 1){
        printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
        int index = 0;
        symbol *current = head;
        while(current != NULL)
        {
            if(current->scope < SCOPE)
                break;
            else{
                if(strlen(current->attribute) == 0)
                    printf("%-10d%-10s%-12s%-10s%-10d\n",index, current->name, current->kind, current->type, current->scope);
                else
                    printf("%-10d%-10s%-12s%-10s%-10d%s\n",index, current->name, current->kind, current->type, current->scope, current->attribute);
                index++;
                head = current->next;
                free(current);
                current = head; 
            }
        }
        printf("\n");
    }   
}
void print_symbol(symbol *p) {
    printf("\n%-10s%-12s%-10s%-10d%-10s\n",
            p->name, p->kind, p->type, p->scope, p->attribute);
}
void print_all(){
    symbol *current = head;
    printf("\n%-10s%-12s%-10s%-10s%-10s\n\n",
            "Name", "Kind", "Type", "Scope", "Attribute");
    while(current != NULL)
    {
        print_symbol(current);
        current = current->next;
    }
}
