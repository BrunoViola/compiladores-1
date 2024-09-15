%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include "sintatico.tab.h"

int line_num = 1;
int column_num = 0;
int first = 1;

char line_buffer[1024];  // Buffer para armazenar o conteúdo da linha atual

void add_to_line_buffer(char* text) {
    strncat(line_buffer, text, sizeof(line_buffer) - strlen(line_buffer) - 1);
}

void clear_line_buffer() {
    memset(line_buffer, 0, sizeof(line_buffer));
}

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
{VOID}                                      { update_position(yytext);  return VOID; }
{INT}                                       { update_position(yytext);  return INT; }
{CHAR}                                      { update_position(yytext);  return CHAR; }
{RETURN}                                    { update_position(yytext);  return RETURN; }
{BREAK}                                     { update_position(yytext);  return BREAK; }
{SWITCH}                                    { update_position(yytext);  return SWITCH; }
{CASE}                                      { update_position(yytext);  return CASE; }
{DEFAULT}                                   { update_position(yytext);  return DEFAULT; }
{DO}                                        { update_position(yytext);  return DO; }
{WHILE}                                     { update_position(yytext);  return WHILE; }
{FOR}                                       { update_position(yytext);  return FOR; }
{IF}                                        { update_position(yytext);  return IF; }
{ELSE}                                      { update_position(yytext);  return ELSE; }
{TYPEDEF}                                   { update_position(yytext);  return TYPEDEF; }
{STRUCT}                                    { update_position(yytext);  return STRUCT; }
{MULTIPLY}                                  { update_position(yytext);  return MULTIPLY; }
{DIV}                                       { update_position(yytext);  return DIV; }
{REMAINDER}                                 { update_position(yytext);  return REMAINDER; }
{SEMICOLON}                                 { update_position(yytext);  return SEMICOLON; }
{COMMA}                                     { update_position(yytext);  return COMMA; }
{COLON}                                     { update_position(yytext);  return COLON; }
{L_PAREN}                                   { update_position(yytext);  return L_PAREN; }
{R_PAREN}                                   { update_position(yytext);  return R_PAREN; }
{L_CURLY_BRACKET}                           { update_position(yytext);  return L_CURLY_BRACKET; }
{R_CURLY_BRACKET}                           { update_position(yytext);  return R_CURLY_BRACKET; }
{L_SQUARE_BRACKET}                          { update_position(yytext);  return L_SQUARE_BRACKET; }
{R_SQUARE_BRACKET}                          { update_position(yytext);  return R_SQUARE_BRACKET; }
{TERNARY_CONDITIONAL}                       { update_position(yytext);  return TERNARY_CONDITIONAL; }
{NUMBER_SIGN}                               { update_position(yytext);  return NUMBER_SIGN; }
{POINTER}                                   { update_position(yytext);  return POINTER; }
{PRINTF}                                    { update_position(yytext);  return PRINTF; }
{SCANF}                                     { update_position(yytext);  return SCANF; }
{DEFINE}                                    { update_position(yytext);  return DEFINE; }
{EXIT}                                      { update_position(yytext);  return EXIT; }
{STRING}                                    { update_position(yytext);  return STRING; }
{TERMINATED_COMMENT}                        { update_position(yytext); return TERMINATED_COMMENT; }
{COMENTARIO_EM_BLOCO}                       { verify_warning(yytext); update_position(yytext);  }
{UNTERMINATED_COMMENT}                      { int init_col = get_initial_position(yytext); print_quebra(); printf("error:lexical:%d:%d: unterminated comment", line_num, init_col); update_position(yytext); return UNTERMINATED_COMMENT; }
{PLUS}                                      { update_position(yytext);  return PLUS; }
{MINUS}                                     { update_position(yytext);  return MINUS; }
{INC}                                       { update_position(yytext);  return INC; }
{DEC}                                       { update_position(yytext);  return DEC; }
{BITWISE_AND}                               { update_position(yytext);  return BITWISE_AND; }
{BITWISE_OR}                                { update_position(yytext);  return BITWISE_OR; }
{BITWISE_NOT}                               { update_position(yytext);  return BITWISE_NOT; }
{BITWISE_XOR}                               { update_position(yytext);  return BITWISE_XOR; }
{NOT}                                       { update_position(yytext);  return NOT; }
{LOGICAL_AND}                               { update_position(yytext);  return LOGICAL_AND; }
{LOGICAL_OR}                                { update_position(yytext);  return LOGICAL_OR; }
{EQUAL}                                     { update_position(yytext);  return EQUAL; }
{NOT_EQUAL}                                 { update_position(yytext);  return NOT_EQUAL; }
{LESS_THAN}                                 { update_position(yytext);  return LESS_THAN; }
{GREATER_THAN}                              { update_position(yytext);  return GREATER_THAN; }
{LESS_EQUAL}                                { update_position(yytext);  return LESS_EQUAL; }
{GREATER_EQUAL}                             { update_position(yytext);  return GREATER_EQUAL; }
{L_SHIFT}                                   { update_position(yytext);  return L_SHIFT; }
{R_SHIFT}                                   { update_position(yytext);  return R_SHIFT; }
{ASSIGN}                                    { update_position(yytext);  return ASSIGN; }
{ADD_ASSIGN}                                { update_position(yytext);  return ADD_ASSIGN; }
{MINUS_ASSIGN}                              { update_position(yytext);  return MINUS_ASSIGN; }
{NUM_OCTAL}                                 { update_position(yytext);  return NUM_OCTAL; }
{NUM_INTEGER}                               { update_position(yytext);  return NUM_INTEGER; }
{NUM_HEXA}                                  { update_position(yytext);  return NUM_HEXA; }
{IDENTIFIER}                                { int init_col = get_initial_position(yytext); update_position(yytext);  if(column_num <= 255) { return IDENTIFIER; } else { print_quebra(); printf("error:lexical:%d:%d: identifier too long", line_num, init_col); return IDENTIFIER_TOO_LONG; } }
\n                                          { line_num++; column_num = 0; }
{WHITESPACE}                                { column_num++; clear_line_buffer();}
{CHARACTER}                                 { update_position(yytext);   return CHARACTER; }
{BARRAINVERTIDA}                            { update_position(yytext);  return BARRAINVERTIDA; }

.                                           { update_position(yytext);print_quebra(); printf("error:lexical:%d:%d: %s", line_num, column_num, yytext); }

%%

void update_position(const char *text) {
    add_to_line_buffer(yytext);
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
void SET_buffer(int total_lines)
{
    //Seta o buffer para o inicio do arquivo
    fseek(stdin, 0, SEEK_SET);

    //For 
    for(int i = 0; i < total_lines; i++)
    {
        fgets(line_buffer, 1000, stdin);
    }
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

            
            if(count>1){ print_quebra(); printf("warning:%d:%d: '/*' within block comment", line, colum);}
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