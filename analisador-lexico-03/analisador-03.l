ACTION1	(aba)+
ACTION2	(a(b*)a)
ACTION3	(a|b)

%%
{ACTION1}		{printf("%s (action 1)\n", yytext);}
{ACTION2}		{printf("%s (action 2)\n", yytext);}
{ACTION3}		{printf("%s (action 3)\n", yytext);}
.                   {printf("%s error\n", yytext); }

%%
/* Recomendável declarar sempre função yywrap() */
int yywrap()
{
    return 1;
}

int main(void)
{
    yylex();
    return 0;
}
