%{
#include <stdio.h>
#include <string.h>

int line_num = 1;
int column_num = 0;

void update_position(const char *text);
%}

IF                      if
L_PAREN                 "(" 
R_PAREN                 ")"
L_CURLY_BRACKET         "{"
R_CURLY_BRACKET         "}"
WHITESPACE              " "
IDENTIFIER              ([a-z]|[A-Z]|"_")+[a-zA-Z0-9_]*

%%

{IF}                                        { update_position(yytext); printf("IF\n"); }
{L_PAREN}                                   { update_position(yytext); printf("L_PAREN\n"); }
{R_PAREN}                                   { update_position(yytext); printf("R_PAREN\n"); }
{L_CURLY_BRACKET}                           { update_position(yytext); printf("L_CURLY_BRACKET\n");}
{R_CURLY_BRACKET}                           { update_position(yytext); printf("R_CURLY_BRACKET\n");}
{IDENTIFIER}                                { update_position(yytext); printf("IDENTIFIER(%s)\n", yytext);}
\n                                          { line_num++; column_num = 0; }
{WHITESPACE}                                { column_num++;}
.                                           { update_position(yytext); printf("error:lexical:%d:%d: %s\n", line_num, column_num, yytext); }

%%

void update_position(const char *text) {
    int len = strlen(text);
    column_num += len;
}

int yywrap() {
    return 1;
}

int main(void) {
    yylex();
    return 0;
}
