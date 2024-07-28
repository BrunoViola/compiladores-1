MAIS	"+"
MENOS	"-"
ID	[a-z]+[0-9]*
NUM	[0-9]+
REAL	[0-9]+"e"[+-]?[0-9]+
QUEBRADELINHA	[\n]

%%
{MAIS}			{printf("+\n");}
{MENOS}			{printf("-\n");}
{ID}			{printf("%s\n", yytext);}
{NUM}			{printf("%s\n", yytext);}
{REAL}			{printf("%s\n", yytext);}
{QUEBRADELINHA}		
.                   {printf("ERRO\n"); }

%%
int yywrap()
{
    return 1;
}

int main(void)
{
    yylex();
    return 0;
}
