/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>

	int codeline = 0;
	int commentline = 0;
	void count(char* str);
%}

 /* Define regular expression label */

letter [a-zA-Z]
digit [0-9]
id {letter}+({letter}|{digit})*
number {digit}+
float {digit}+"."{digit}+
string \".+\"
whitespace [ \t]+


 /* Rules section */
%%

"+"		{ printf("%s \t ADD\n", yytext); }
"-"		{ printf("%s \t SUB\n", yytext); }
"*"		{ printf("%s \t MUL\n", yytext); }
"/"		{ printf("%s \t DIV\n", yytext); }
"%"		{ printf("%s \t MOD\n", yytext); }
"++"	{ printf("%s \t INC\n", yytext); }
"--"	{ printf("%s \t DEC\n", yytext); }
">"		{ printf("%s \t MT\n", yytext); }
"<"		{ printf("%s \t LT\n", yytext); }
">="	{ printf("%s \t MTE\n", yytext); }
"<="	{ printf("%s \t LTE\n", yytext); }
"=="	{ printf("%s \t EQ\n", yytext); }
"!="	{ printf("%s \t NE\n", yytext); }
"="		{ printf("%s \t ASGN\n", yytext); }
"+="	{ printf("%s \t ADDASGN\n", yytext); }
"-="	{ printf("%s \t SUBASGN\n", yytext); }
"*="	{ printf("%s \t MULASGN\n", yytext); }
"/="	{ printf("%s \t DIVASGN\n", yytext); }
"%="	{ printf("%s \t MODASGN\n", yytext); }
"&&"	{ printf("%s \t AND\n", yytext); }
"||"	{ printf("%s \t OR\n", yytext); }
"!"		{ printf("%s \t NOT\n", yytext); }
"("		{ printf("%s \t LB\n", yytext); }
")"		{ printf("%s \t RB\n", yytext); }
"{"		{ printf("%s \t LCB\n", yytext); }
"}"		{ printf("%s \t RCB\n", yytext); }
"["		{ printf("%s \t LSB\n", yytext); }
"]"		{ printf("%s \t RSB\n", yytext); }
","		{ printf("%s \t COMMA\n", yytext); }
";"		{ printf("%s \t SEMICOLON\n", yytext); }
"\""		{ printf("%s \t QUOTA\n", yytext); }
"print"	{ printf("%s \t PRINT\n", yytext); }
"if"	{ printf("%s \t IF\n", yytext); }
"else"	{ printf("%s \t ELSE\n", yytext); }
"for"	{ printf("%s \t FOR\n", yytext); }
"while"	{ printf("%s \t WHILE\n", yytext); }
"string" { printf("%s \t STRING\n", yytext); }
"int"	{ printf("%s \t INT\n", yytext); }
"float"	{ printf("%s \t FLOAT\n", yytext); }
"void"	{ printf("%s \t VOID\n", yytext); }
"bool"	{ printf("%s \t BOOL\n", yytext); }
"true"	{ printf("%s \t TRUE\n", yytext); }
"false"	{ printf("%s \t FALSE\n", yytext); }
"return" { printf("%s \t RET\n", yytext); }
"continue" { printf("%s \t CONT\n", yytext); }
"break"	{ printf("%s \t BREAK\n", yytext); }

{number} { printf("%s \t I_CONST\n", yytext); }
{float}	{ printf("%s \t F_CONST\n", yytext); }
{string} {
			printf("\" \t QUOTA\n");
            yytext = &yytext[1];
            yytext[strlen(yytext)-1] = '\0';
            printf("%s \t STR_CONST\n", yytext);
			printf("\" \t QUOTA\n");
		 }
{id}	{ printf("%s \t ID\n", yytext); }

{whitespace} { }

\n			{ codeline++;}

"//".*	{ 
			printf("%s \t C++ Comment\n", yytext); 
			commentline++;		
		}

"/*"([^*]|\n|"*"+[^/])*"*"+"/" 	{ 
              	printf("%s \t C Comment\n", yytext);
				count(yytext);
			}

			

%%

/*	C Code section */
int yywrap(void){
    return 1;
}

int main(int argc,char *argv[])
{
	yyin = fopen(argv[1],"r");
	yylex();
	printf("\nParse over, the line number is %d.\n\n", codeline);
	printf("comment: %d lines\n\n", commentline);

	return 0;
}

void count(char* str){
	while(str = strstr(str,"\n")){
		codeline++;
        commentline++;
        str++;
    }
    commentline++;
}


