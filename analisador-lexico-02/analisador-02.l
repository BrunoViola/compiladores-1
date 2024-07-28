DIGIT [0-9]
ID [a-z][a-z0-9]*
WHITESPACE [ \t\r]+
COMMENT "--"[^\n]*
QUEBRADELINHA \n
IF	if

%%
{IF}			{printf("IF");}
{ID}                 { printf("%s ID\n", yytext); }
({DIGIT}+"."{DIGIT}*|{DIGIT}*"."{DIGIT}+)  { printf("%s REAL\n", yytext); }
{DIGIT}+            { printf("%s NUM\n", yytext); }
{COMMENT}           { printf("%s comment\n", yytext); }
{WHITESPACE}        { printf("white space\n"); }
{QUEBRADELINHA}     
.                   { printf("%s error\n", yytext); }

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
