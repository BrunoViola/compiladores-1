%{
#include <stdio.h>
#include <string.h>

int line_num = 1;
int column_num = 0;

void update_position(const char *text);
int get_initial_position(const char *text);

%}

IF                      if
SEMICOLON               ";"
COMMA                   ","
COLON                   ":"
L_PAREN                 "(" 
R_PAREN                 ")"
L_CURLY_BRACKET         "{"
R_CURLY_BRACKET         "}"
L_SQUARE_BRACKET        "["
R_SQUARE_BRACKET        "]"
TERNARY_CONDITIONAL     "?"
NUMBER_SIGN             "#"
POINTER                 "->"
PRINTF                  printf
STRING                  \"([^\\"]|\\.)*\"
WHITESPACE              " "
TERMINATED_COMMENT      "//"(.)*
COMENTARIO_EM_BLOCO     "/*"(.|"\n")*"*/"
UNTERMINATED_COMMENT    "/*"(.|"\n")*
PLUS                    "+"
MINUS                   "-"
INC                     "++"
DEC                     "--"
NOT                     "!"
NOT_EQUAL               "!="
R_SHIFT                 ">>"
L_SHIFT                 "<<"
ADD_ASSIGN              "+="
MINUS_ASSIGN            "-="
NUM_OCTAL               0[1-7][0-7]*
NUM_INTEGER             [0-9]+
NUM_HEXA                0(x|X)[a-zA-Z0-9]+
IDENTIFIER              ([a-z]|[A-Z]|"_")+[a-zA-Z0-9_]*

%%

{IF}                                        { update_position(yytext); printf("IF\n"); }
{SEMICOLON}                                 { update_position(yytext); printf("SEMICOLON\n");}
{COMMA}                                     { update_position(yytext); printf("COMMA\n");}
{COLON}                                     { update_position(yytext); printf("COLON\n");}
{L_PAREN}                                   { update_position(yytext); printf("L_PAREN\n"); }
{R_PAREN}                                   { update_position(yytext); printf("R_PAREN\n"); }
{L_CURLY_BRACKET}                           { update_position(yytext); printf("L_CURLY_BRACKET\n");}
{R_CURLY_BRACKET}                           { update_position(yytext); printf("R_CURLY_BRACKET\n");}
{L_SQUARE_BRACKET}                          { update_position(yytext); printf("L_SQUARE_BRACKET\n");}
{R_SQUARE_BRACKET}                          { update_position(yytext); printf("R_SQUARE_BRACKET\n");}
{TERNARY_CONDITIONAL}                       { update_position(yytext); printf("TERNARY_CONDITIONAL\n");}
{NUMBER_SIGN}                               { update_position(yytext); printf("NUMBER_SIGN\n");}
{POINTER}                                   { update_position(yytext); printf("POINTER\n");}
{PRINTF}                                    { update_position(yytext); printf("PRINTF\n");}
{STRING}                                    { update_position(yytext); printf("STRING(%s)\n", yytext);}
{TERMINATED_COMMENT}                        { update_position(yytext);}
{COMENTARIO_EM_BLOCO}                       { update_position(yytext);}
{UNTERMINATED_COMMENT}                      { int init_col = get_initial_position(yytext); printf("error:lexical:%d:%d: unterminated comment\n", line_num, init_col); update_position(yytext);}
{PLUS}                                      { update_position(yytext); printf("PLUS\n");}
{MINUS}                                     { update_position(yytext); printf("MINUS\n");}
{INC}                                       { update_position(yytext); printf("INC\n");}
{DEC}                                       { update_position(yytext); printf("DEC\n");}
{NOT}                                       { update_position(yytext); printf("NOT\n");}
{NOT_EQUAL}                                 { update_position(yytext); printf("NOT_EQUAL\n");}
{L_SHIFT}                                   { update_position(yytext); printf("L_SHIFT\n");}
{R_SHIFT}                                   { update_position(yytext); printf("R_SHIFT\n");}
{ADD_ASSIGN}                                { update_position(yytext); printf("ADD_ASSIGN\n");}
{MINUS_ASSIGN}                              { update_position(yytext); printf("MINUS_ASSIGN\n");}
{NUM_OCTAL}                                 { update_position(yytext); printf("NUM_OCTAL(%s)\n", yytext);}
{NUM_INTEGER}                               { update_position(yytext); printf("NUM_INTEGER(%s)\n", yytext);}
{NUM_HEXA}                                  { update_position(yytext); printf("NUM_HEXA(%s)\n", yytext);}
{IDENTIFIER}                                { update_position(yytext); printf("IDENTIFIER(%s)\n", yytext);}
\n                                          { line_num++; column_num = 0; }
{WHITESPACE}                                { column_num++;}
.                                           { update_position(yytext); printf("error:lexical:%d:%d: %s\n", line_num, column_num, yytext); }

%%

void update_position(const char *text) {
    int len = strlen(text);
    column_num += len;
}

int get_initial_position(const char *text) {
    return column_num + 1;
}

int yywrap() {
    return 1;
}

int main(void) {
    yylex();
    return 0;
}
