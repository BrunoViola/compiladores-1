%{
#include <stdio.h>
#include <string.h>

int line_num = 1;
int column_num = 0;

void update_position(const char *text);
int get_initial_position(const char *text);
void print_string_token(const char *text);
void verify_warning(const char * text);


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
{VOID}                                      { update_position(yytext); printf("VOID\n"); }
{INT}                                       { update_position(yytext); printf("INT\n"); }
{CHAR}                                      { update_position(yytext); printf("CHAR\n"); }
{RETURN}                                    { update_position(yytext); printf("RETURN\n"); }
{BREAK}                                     { update_position(yytext); printf("BREAK\n"); }
{SWITCH}                                    { update_position(yytext); printf("SWITCH\n"); }
{CASE}                                      { update_position(yytext); printf("CASE\n"); }
{DEFAULT}                                   { update_position(yytext); printf("DEFAULT\n"); }
{DO}                                        { update_position(yytext); printf("DO\n"); }
{WHILE}                                     { update_position(yytext); printf("WHILE\n"); }
{FOR}                                       { update_position(yytext); printf("FOR\n"); }
{IF}                                        { update_position(yytext); printf("IF\n"); }
{ELSE}                                      { update_position(yytext); printf("ELSE\n"); }
{TYPEDEF}                                   { update_position(yytext); printf("TYPEDEF\n"); }
{STRUCT}                                    { update_position(yytext); printf("STRUCT\n"); }
{MULTIPLY}                                  { update_position(yytext); printf("MULTIPLY\n"); }
{DIV}                                       { update_position(yytext); printf("DIV\n"); }
{REMAINDER}                                 { update_position(yytext); printf("REMAINDER\n"); }
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
{SCANF}                                     { update_position(yytext); printf("SCANF\n");}
{DEFINE}                                    { update_position(yytext); printf("DEFINE\n");}
{EXIT}                                      { update_position(yytext); printf("EXIT\n");}
{STRING}                                    { update_position(yytext); print_string_token(yytext); }
{TERMINATED_COMMENT}                        { update_position(yytext);}
{COMENTARIO_EM_BLOCO}                       { verify_warning(yytext); update_position(yytext);}
{UNTERMINATED_COMMENT}                      { int init_col = get_initial_position(yytext); printf("error:lexical:%d:%d: unterminated comment\n", line_num, init_col); update_position(yytext);}
{PLUS}                                      { update_position(yytext); printf("PLUS\n");}
{MINUS}                                     { update_position(yytext); printf("MINUS\n");}
{INC}                                       { update_position(yytext); printf("INC\n");}
{DEC}                                       { update_position(yytext); printf("DEC\n");}
{BITWISE_AND}                               { update_position(yytext); printf("BITWISE_AND\n");}
{BITWISE_OR}                                { update_position(yytext); printf("BITWISE_OR\n");}
{BITWISE_NOT}                               { update_position(yytext); printf("BITWISE_NOT\n");}
{BITWISE_XOR}                               { update_position(yytext); printf("BITWISE_XOR\n");}
{NOT}                                       { update_position(yytext); printf("NOT\n");}
{LOGICAL_AND}                               { update_position(yytext); printf("LOGICAL_AND\n");}
{LOGICAL_OR}                                { update_position(yytext); printf("LOGICAL_OR\n");}
{EQUAL}                                     { update_position(yytext); printf("EQUAL\n");}
{NOT_EQUAL}                                 { update_position(yytext); printf("NOT_EQUAL\n");}
{LESS_THAN}                                 { update_position(yytext); printf("LESS_THAN\n");}
{GREATER_THAN}                              { update_position(yytext); printf("GREATER_THAN\n");}
{LESS_EQUAL}                                { update_position(yytext); printf("LESS_EQUAL\n");}
{GREATER_EQUAL}                             { update_position(yytext); printf("GREATER_EQUAL\n");}
{L_SHIFT}                                   { update_position(yytext); printf("L_SHIFT\n");}
{R_SHIFT}                                   { update_position(yytext); printf("R_SHIFT\n");}
{ASSIGN}                                    { update_position(yytext); printf("ASSIGN\n");}
{ADD_ASSIGN}                                { update_position(yytext); printf("ADD_ASSIGN\n");}
{MINUS_ASSIGN}                              { update_position(yytext); printf("MINUS_ASSIGN\n");}
{NUM_OCTAL}                                 { update_position(yytext); printf("NUM_OCTAL(%s)\n", yytext);}
{NUM_INTEGER}                               { update_position(yytext); printf("NUM_INTEGER(%s)\n", yytext);}
{NUM_HEXA}                                  { update_position(yytext); printf("NUM_HEXA(%s)\n", yytext);}
{IDENTIFIER}                                { int init_col = get_initial_position(yytext); update_position(yytext); if(column_num<=255){ printf("IDENTIFIER(%s)\n", yytext);} else{  printf("error:lexical:%d:%d: identifier too long\n", line_num, init_col);} }
\n                                          { line_num++; column_num = 0; }
{WHITESPACE}                                { column_num++;}
{CHARACTER}                                 { update_position(yytext); 	printf("CHARACTER(%c)\n", yytext[3]);}
.                                           { update_position(yytext); printf("error:lexical:%d:%d: %s\n", line_num, column_num, yytext); }

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
    printf("STRING(%s)\n", buffer);
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

int yywrap() {
    return 1;
}

int main(void) {
    yylex();
    return 0;
}
