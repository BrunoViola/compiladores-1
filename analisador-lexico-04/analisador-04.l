%{
#include <stdio.h>
#include <string.h>

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
COMENTARIO_EM_BLOCO     "/*"(.|\n)*?"*/"
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
CHARACTER               "\’"[^\n]"\’"
IDENTIFIER              ([a-z]|[A-Z]|"_")+[a-zA-Z0-9_]*

%%
{VOID}                                      { update_position(yytext);print_quebra(); printf("VOID"); }
{INT}                                       { update_position(yytext);print_quebra(); printf("INT"); }
{CHAR}                                      { update_position(yytext);print_quebra(); printf("CHAR"); }
{RETURN}                                    { update_position(yytext);print_quebra(); printf("RETURN"); }
{BREAK}                                     { update_position(yytext);print_quebra(); printf("BREAK"); }
{SWITCH}                                    { update_position(yytext);print_quebra(); printf("SWITCH"); }
{CASE}                                      { update_position(yytext);print_quebra(); printf("CASE"); }
{DEFAULT}                                   { update_position(yytext);print_quebra(); printf("DEFAULT"); }
{DO}                                        { update_position(yytext);print_quebra(); printf("DO"); }
{WHILE}                                     { update_position(yytext);print_quebra(); printf("WHILE"); }
{FOR}                                       { update_position(yytext);print_quebra(); printf("FOR"); }
{IF}                                        { update_position(yytext);print_quebra(); printf("IF"); }
{ELSE}                                      { update_position(yytext);print_quebra(); printf("ELSE"); }
{TYPEDEF}                                   { update_position(yytext);print_quebra(); printf("TYPEDEF"); }
{STRUCT}                                    { update_position(yytext);print_quebra(); printf("STRUCT"); }
{MULTIPLY}                                  { update_position(yytext);print_quebra(); printf("MULTIPLY"); }
{DIV}                                       { update_position(yytext);print_quebra(); printf("DIV"); }
{REMAINDER}                                 { update_position(yytext);print_quebra(); printf("REMAINDER"); }
{SEMICOLON}                                 { update_position(yytext);print_quebra(); printf("SEMICOLON");}
{COMMA}                                     { update_position(yytext);print_quebra(); printf("COMMA");}
{COLON}                                     { update_position(yytext);print_quebra(); printf("COLON");}
{L_PAREN}                                   { update_position(yytext);print_quebra(); printf("L_PAREN"); }
{R_PAREN}                                   { update_position(yytext);print_quebra(); printf("R_PAREN"); }
{L_CURLY_BRACKET}                           { update_position(yytext);print_quebra(); printf("L_CURLY_BRACKET");}
{R_CURLY_BRACKET}                           { update_position(yytext);print_quebra(); printf("R_CURLY_BRACKET");}  
{L_SQUARE_BRACKET}                          { update_position(yytext);print_quebra(); printf("L_SQUARE_BRACKET");}
{R_SQUARE_BRACKET}                          { update_position(yytext); print_quebra(); printf("R_SQUARE_BRACKET");}
{TERNARY_CONDITIONAL}                       { update_position(yytext);print_quebra(); printf("TERNARY_CONDITIONAL");}
{NUMBER_SIGN}                               { update_position(yytext);print_quebra(); printf("NUMBER_SIGN");}
{POINTER}                                   { update_position(yytext);print_quebra(); printf("POINTER");}
{PRINTF}                                    { update_position(yytext);print_quebra(); printf("PRINTF");}
{SCANF}                                     { update_position(yytext);print_quebra(); printf("SCANF");}
{DEFINE}                                    { update_position(yytext);print_quebra(); printf("DEFINE");}
{EXIT}                                      { update_position(yytext);print_quebra(); printf("EXIT");}
{STRING}                                    { update_position(yytext);print_quebra(); print_string_token(yytext); }
{TERMINATED_COMMENT}                        { update_position(yytext);}
{COMENTARIO_EM_BLOCO}                       { verify_warning(yytext); update_position(yytext);}
{UNTERMINATED_COMMENT}                      { int init_col = get_initial_position(yytext);print_quebra(); printf("error:lexical:%d:%d: unterminated comment", line_num, init_col); update_position(yytext);}
{PLUS}                                      { update_position(yytext);print_quebra(); printf("PLUS");}
{MINUS}                                     { update_position(yytext);print_quebra(); printf("MINUS");}
{INC}                                       { update_position(yytext);print_quebra(); printf("INC");}
{DEC}                                       { update_position(yytext);print_quebra(); printf("DEC");}
{BITWISE_AND}                               { update_position(yytext);print_quebra(); printf("BITWISE_AND");}
{BITWISE_OR}                                { update_position(yytext);print_quebra(); printf("BITWISE_OR");}
{BITWISE_NOT}                               { update_position(yytext);print_quebra(); printf("BITWISE_NOT");}
{BITWISE_XOR}                               { update_position(yytext);print_quebra(); printf("BITWISE_XOR");}
{NOT}                                       { update_position(yytext);print_quebra(); printf("NOT");}
{LOGICAL_AND}                               { update_position(yytext);print_quebra(); printf("LOGICAL_AND");}
{LOGICAL_OR}                                { update_position(yytext);print_quebra(); printf("LOGICAL_OR");}
{EQUAL}                                     { update_position(yytext);print_quebra(); printf("EQUAL");}
{NOT_EQUAL}                                 { update_position(yytext);print_quebra(); printf("NOT_EQUAL");}
{LESS_THAN}                                 { update_position(yytext);print_quebra(); printf("LESS_THAN");}
{GREATER_THAN}                              { update_position(yytext);print_quebra(); printf("GREATER_THAN");}
{LESS_EQUAL}                                { update_position(yytext);print_quebra(); printf("LESS_EQUAL");}
{GREATER_EQUAL}                             { update_position(yytext);print_quebra(); printf("GREATER_EQUAL");}
{L_SHIFT}                                   { update_position(yytext);print_quebra(); printf("L_SHIFT");}
{R_SHIFT}                                   { update_position(yytext);print_quebra(); printf("R_SHIFT");}
{ASSIGN}                                    { update_position(yytext);print_quebra(); printf("ASSIGN");}
{ADD_ASSIGN}                                { update_position(yytext);print_quebra(); printf("ADD_ASSIGN");}
{MINUS_ASSIGN}                              { update_position(yytext);print_quebra(); printf("MINUS_ASSIGN");}
{NUM_OCTAL}                                 { update_position(yytext);print_quebra(); printf("NUM_OCTAL(%s)", yytext);}
{NUM_INTEGER}                               { update_position(yytext);print_quebra(); printf("NUM_INTEGER(%s)", yytext);}
{NUM_HEXA}                                  { update_position(yytext);print_quebra(); printf("NUM_HEXA(%s)", yytext);}
{IDENTIFIER}                                { int init_col = get_initial_position(yytext); update_position(yytext);print_quebra(); if(column_num<=255){ printf("IDENTIFIER(%s)", yytext);} else{  printf("error:lexical:%d:%d: identifier too long\n", line_num, init_col);} }
\n                                          { line_num++; column_num = 0; }
{WHITESPACE}                                { column_num++;}
{CHARACTER}                                 { update_position(yytext);print_quebra(); 	printf("CHARACTER(%c)", yytext[3]);}
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
    // Remover as aspas duplas iniciais e finais
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
        if(text[i]=='/' && text[i+1]=='*'){
            count++;
            colum++;
            i++;
            if(count>1) printf("warning:%d:%d: ’/*’ within block comment\n", line, colum);
        }
    }
}

void print_quebra(){
    if (first == 0){
        printf("\n");
    }else{
        first = 0;
    }
}

int yywrap() {
    return 1;
}

int main(void) {
    yylex();
    return 0;
}
