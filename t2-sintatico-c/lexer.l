%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <sintatico.tab.h>

int line_num = 1;
int column_num = 0;
int first = 1;

void update_position(const char *text);
int get_initial_position(const char *text);
void print_string_token(const char *text);
void verify_warning(const char * text);
void print_quebra();

%}

VOID                    void
INT                     int
CHAR                    char
RETURN                  return
BREAK                   break
SWITCH                  switch
CASE                    case
DEFAULT                 default
DO                      do
WHILE                   while
FOR                     for
IF                      if
ELSE                    else
TYPEDEF                 typedef
STRUCT                  struct
MULTIPLY                "*"
DIV                     "/"
REMAINDER               "%"
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
SCANF                   scanf
DEFINE                  define
EXIT                    exit
STRING                  \"([^\\"]|\\.)*\"
WHITESPACE              " "
TERMINATED_COMMENT      "//"(.)*
COMENTARIO_EM_BLOCO     "/*"([^*]|\*+[^*/])*"*/"
UNTERMINATED_COMMENT    "/*"([^*]|\*+[^/*])*
PLUS                    "+"
MINUS                   "-"
INC                     "++"
DEC                     "--"
BITWISE_AND             "&"
BITWISE_OR              "|"
BITWISE_NOT             "~"
BITWISE_XOR             "^"
NOT                     "!"
LOGICAL_AND             "&&"
LOGICAL_OR              "||"
EQUAL                   "=="
NOT_EQUAL               "!="
LESS_THAN               "<"
GREATER_THAN            ">"
LESS_EQUAL              "<="
GREATER_EQUAL           ">="
R_SHIFT                 ">>"
L_SHIFT                 "<<"
ASSIGN                  "="
ADD_ASSIGN              "+="
MINUS_ASSIGN            "-="
NUM_OCTAL               0[1-7][0-7]*
NUM_INTEGER             [0-9]+
NUM_HEXA                0(x|X)[a-zA-Z0-9]+
CHARACTER               "\'"[^\n]"\'"
BARRAINVERTIDA          "\'""\\"[abfnrtv\\'"?0]"\'"
IDENTIFIER              ([a-z]|[A-Z]|"_")+[a-zA-Z0-9_]*

%%
{VOID}                                      { update_position(yytext); print_quebra(); printf("VOID"); return VOID; }
{INT}                                       { update_position(yytext); print_quebra(); printf("INT"); return INT; }
{CHAR}                                      { update_position(yytext); print_quebra(); printf("CHAR"); return CHAR; }
{RETURN}                                    { update_position(yytext); print_quebra(); printf("RETURN"); return RETURN; }
{BREAK}                                     { update_position(yytext); print_quebra(); printf("BREAK"); return BREAK; }
{SWITCH}                                    { update_position(yytext); print_quebra(); printf("SWITCH"); return SWITCH; }
{CASE}                                      { update_position(yytext); print_quebra(); printf("CASE"); return CASE; }
{DEFAULT}                                   { update_position(yytext); print_quebra(); printf("DEFAULT"); return DEFAULT; }
{DO}                                        { update_position(yytext); print_quebra(); printf("DO"); return DO; }
{WHILE}                                     { update_position(yytext); print_quebra(); printf("WHILE"); return WHILE; }
{FOR}                                       { update_position(yytext); print_quebra(); printf("FOR"); return FOR; }
{IF}                                        { update_position(yytext); print_quebra(); printf("IF"); return IF; }
{ELSE}                                      { update_position(yytext); print_quebra(); printf("ELSE"); return ELSE; }
{TYPEDEF}                                   { update_position(yytext); print_quebra(); printf("TYPEDEF"); return TYPEDEF; }
{STRUCT}                                    { update_position(yytext); print_quebra(); printf("STRUCT"); return STRUCT; }
{MULTIPLY}                                  { update_position(yytext); print_quebra(); printf("MULTIPLY"); return MULTIPLY; }
{DIV}                                       { update_position(yytext); print_quebra(); printf("DIV"); return DIV; }
{REMAINDER}                                 { update_position(yytext); print_quebra(); printf("REMAINDER"); return REMAINDER; }
{SEMICOLON}                                 { update_position(yytext); print_quebra(); printf("SEMICOLON"); return SEMICOLON; }
{COMMA}                                     { update_position(yytext); print_quebra(); printf("COMMA"); return COMMA; }
{COLON}                                     { update_position(yytext); print_quebra(); printf("COLON"); return COLON; }
{L_PAREN}                                   { update_position(yytext); print_quebra(); printf("L_PAREN"); return L_PAREN; }
{R_PAREN}                                   { update_position(yytext); print_quebra(); printf("R_PAREN"); return R_PAREN; }
{L_CURLY_BRACKET}                           { update_position(yytext); print_quebra(); printf("L_CURLY_BRACKET"); return L_CURLY_BRACKET; }
{R_CURLY_BRACKET}                           { update_position(yytext); print_quebra(); printf("R_CURLY_BRACKET"); return R_CURLY_BRACKET; }
{L_SQUARE_BRACKET}                          { update_position(yytext); print_quebra(); printf("L_SQUARE_BRACKET"); return L_SQUARE_BRACKET; }
{R_SQUARE_BRACKET}                          { update_position(yytext); print_quebra(); printf("R_SQUARE_BRACKET"); return R_SQUARE_BRACKET; }
{TERNARY_CONDITIONAL}                       { update_position(yytext); print_quebra(); printf("TERNARY_CONDITIONAL"); return TERNARY_CONDITIONAL; }
{NUMBER_SIGN}                               { update_position(yytext); print_quebra(); printf("NUMBER_SIGN"); return NUMBER_SIGN; }
{POINTER}                                   { update_position(yytext); print_quebra(); printf("POINTER"); return POINTER; }
{PRINTF}                                    { update_position(yytext); print_quebra(); printf("PRINTF"); return PRINTF; }
{SCANF}                                     { update_position(yytext); print_quebra(); printf("SCANF"); return SCANF; }
{DEFINE}                                    { update_position(yytext); print_quebra(); printf("DEFINE"); return DEFINE; }
{EXIT}                                      { update_position(yytext); print_quebra(); printf("EXIT"); return EXIT; }
{STRING}                                    { update_position(yytext); print_quebra(); print_string_token(yytext); return STRING; }
{TERMINATED_COMMENT}                        { update_position(yytext); return TERMINATED_COMMENT; }
{COMENTARIO_EM_BLOCO}                       { verify_warning(yytext); update_position(yytext); return COMENTARIO_EM_BLOCO; }
{UNTERMINATED_COMMENT}                      { int init_col = get_initial_position(yytext); print_quebra(); printf("error:lexical:%d:%d: unterminated comment", line_num, init_col); update_position(yytext); return UNTERMINATED_COMMENT; }
{PLUS}                                      { update_position(yytext); print_quebra(); printf("PLUS"); return PLUS; }
{MINUS}                                     { update_position(yytext); print_quebra(); printf("MINUS"); return MINUS; }
{INC}                                       { update_position(yytext); print_quebra(); printf("INC"); return INC; }
{DEC}                                       { update_position(yytext); print_quebra(); printf("DEC"); return DEC; }
{BITWISE_AND}                               { update_position(yytext); print_quebra(); printf("BITWISE_AND"); return BITWISE_AND; }
{BITWISE_OR}                                { update_position(yytext); print_quebra(); printf("BITWISE_OR"); return BITWISE_OR; }
{BITWISE_NOT}                               { update_position(yytext); print_quebra(); printf("BITWISE_NOT"); return BITWISE_NOT; }
{BITWISE_XOR}                               { update_position(yytext); print_quebra(); printf("BITWISE_XOR"); return BITWISE_XOR; }
{NOT}                                       { update_position(yytext); print_quebra(); printf("NOT"); return NOT; }
{LOGICAL_AND}                               { update_position(yytext); print_quebra(); printf("LOGICAL_AND"); return LOGICAL_AND; }
{LOGICAL_OR}                                { update_position(yytext); print_quebra(); printf("LOGICAL_OR"); return LOGICAL_OR; }
{EQUAL}                                     { update_position(yytext); print_quebra(); printf("EQUAL"); return EQUAL; }
{NOT_EQUAL}                                 { update_position(yytext); print_quebra(); printf("NOT_EQUAL"); return NOT_EQUAL; }
{LESS_THAN}                                 { update_position(yytext); print_quebra(); printf("LESS_THAN"); return LESS_THAN; }
{GREATER_THAN}                              { update_position(yytext); print_quebra(); printf("GREATER_THAN"); return GREATER_THAN; }
{LESS_EQUAL}                                { update_position(yytext); print_quebra(); printf("LESS_EQUAL"); return LESS_EQUAL; }
{GREATER_EQUAL}                             { update_position(yytext); print_quebra(); printf("GREATER_EQUAL"); return GREATER_EQUAL; }
{L_SHIFT}                                   { update_position(yytext); print_quebra(); printf("L_SHIFT"); return L_SHIFT; }
{R_SHIFT}                                   { update_position(yytext); print_quebra(); printf("R_SHIFT"); return R_SHIFT; }
{ASSIGN}                                    { update_position(yytext); print_quebra(); printf("ASSIGN"); return ASSIGN; }
{ADD_ASSIGN}                                { update_position(yytext); print_quebra(); printf("ADD_ASSIGN"); return ADD_ASSIGN; }
{MINUS_ASSIGN}                              { update_position(yytext); print_quebra(); printf("MINUS_ASSIGN"); return MINUS_ASSIGN; }
{NUM_OCTAL}                                 { update_position(yytext); print_quebra(); printf("NUM_OCTAL(%s)", yytext); return NUM_OCTAL; }
{NUM_INTEGER}                               { update_position(yytext); print_quebra(); printf("NUM_INTEGER(%s)", yytext); return NUM_INTEGER; }
{NUM_HEXA}                                  { update_position(yytext); print_quebra(); printf("NUM_HEXA(%s)", yytext); return NUM_HEXA; }
{IDENTIFIER}                                { int init_col = get_initial_position(yytext); update_position(yytext); print_quebra(); if(column_num <= 255) { printf("IDENTIFIER(%s)", yytext); return IDENTIFIER; } else { printf("error:lexical:%d:%d: identifier too long", line_num, init_col); return IDENTIFIER_TOO_LONG; } }
\n                                          { line_num++; column_num = 0; }
{WHITESPACE}                                { column_num++; }
{CHARACTER}                                 { update_position(yytext); print_quebra(); printf("CHARACTER(%c)", yytext[1]); return CHARACTER; }
{BARRAINVERTIDA}                            { update_position(yytext); print_quebra(); printf("CHARACTER(%c%c)", yytext[1], yytext[2]); return BARRAINVERTIDA; }

.                                           { update_position(yytext);print_quebra(); printf("error:lexical:%d:%d: %s", line_num, column_num, yytext); }

%%

void update_position(const char *text) {
    int len = strlen(text);
    for(int i=0; i<len; i++) {
        if(text[i] == '\n') {
            line_num++;
            column_num = 0;
        }else {
            column_num++;
        }
    }
}

int get_initial_position(const char *text) {
    return column_num + 1;
}

void print_string_token(const char *text) {
    char buffer[strlen(text) - 1];
    strncpy(buffer, text + 1, strlen(text) - 2);
    buffer[strlen(text) - 2] = '\0';
    printf("STRING(%s)", buffer);
}

void verify_warning(const char * text){
    int len = strlen(text);
    int count = 0;
    int colum=0;
    int line = line_num;
    for(int i=0; i<len; i++){
        colum++;
        if(text[i]=='\n'){
            colum = 0;
            line++;
        }
        if(text[i]=='/' && text[i+1]=='*' && text[i+2]=='/'){
            count--;
        }else if(text[i-1]!='/' && text[i]=='/' && text[i+1]=='*'){
            count++;
            i++;
            if(count>1) printf("\nwarning:%d:%d: '/*' within block comment", line, colum);
            colum++;
        } else if(text[i]=='*' && text[i+1]=='/'){
            count--;
        }
    }
    count=0;
}

void print_quebra(){
    if (first == 0){
        printf("\n");
    }else{
        first = 0;
    }
}

int main(void) {
    yylex();
    return 0;
}