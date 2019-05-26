/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>
%}

/* Define regular expression label */

letter [a-zA-Z]
digit [0-9]
id {letter}+({letter}|{digit})*
number {digit}+

/* Rules section */
%%

"+" 	{ printf("%s \t ADD \n", yytext); }
"-"		{ printf("%s \t SUB \n", yytext); }
{id}	{ printf("%s \t ID \n", yytext); }
\n			{;}

%%

/*	C Code section */
int yywrap(void)
{
    return 1;
}

int main(int argc,char *argv[])
{
	yyin = fopen(argv[1],"r");
	yylex();

	return 0;
}
