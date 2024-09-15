 %{
 #include <stdio.h>
 extern int yylex();
 extern char* yytext;
 void yyerror(void *s);
 %}
%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
%token MULTIPLY
%token DIV
%token REMAINDER
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINTER
%token PRINTF
%token SCANF
%token DEFINE
%token EXIT
%token STRING
%token TERMINATED_COMMENT
%token COMENTARIO_EM_BLOCO
%token UNTERMINATED_COMMENT
%token PLUS
%token MINUS
%token INC
%token DEC
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT
%token LOGICAL_AND
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token L_SHIFT
%token R_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token NUM_OCTAL
%token NUM_INTEGER
%token NUM_HEXA
%token IDENTIFIER
%token IDENTIFIER_TOO_LONG
%token CHARACTER
%token BARRAINVERTIDA

%start programa
%%
Programa: declaracoes Programa
    | funcao Programa
    | /* vazio */ { printf("SUCCESSFUL COMPILATION."); return 0; }
; 

declaracoes: NUMBER_SIGN DEFINE IDENTIFIER expressao { }
   | declaracao_de_variaveis { }
   | declaracao_de_prototipo { }
;

funcao: tipo multiply_loop IDENTIFIER parametros L_CURLY_BRACKET declaracao_de_variaveis_loop comandos R_CURLY_BRACKET { }
   | tipo multiply_loop IDENTIFIER parametros L_CURLY_BRACKET comandos R_CURLY_BRACKET { }
;

multiply_loop: MULTIPLY multiply_loop   { }
               | /* vazio */ {}
;

declaracao_de_variaveis_loop: declaracao_de_variaveis declaracao_de_variaveis_loop   { }
               | /* vazio */{}
;

declaracao_de_variaveis: tipo declaracao_de_variaveis_cerne SEMICOLON{ }
;

declaracao_de_variaveis_cerne: multiply_loop IDENTIFIER expressao_loop ASSIGN expressao_de_atribuicao declaracao_de_variaveis_cerne_loop{ }
               | multiply_loop IDENTIFIER expressao_loop declaracao_de_variaveis_cerne_loop {}
;

declaracao_de_variaveis_cerne_loop: COMMA declaracao_de_variaveis_cerne declaracao_de_variaveis_cerne_loop{}
               | /*vazio*/{}
;
expressao_loop: L_SQUARE_BRACKET expressao R_SQUARE_BRACKET expressao_loop{}
               | /*vazio*/{}

;

declaracao_de_prototipo: tipo multiply_loop IDENTIFIER parametros SEMICOLON{}
;

parametros: L_PAREN parametros_cerne R_PAREN{}
;

parametros_cerne: tipo multiply_loop IDENTIFIER expressao_loop parametros_cerne_loop{}
               | /*vazio*/{}
;

parametros_cerne_loop: COMMA parametros_cerne parametros_cerne_loop
               | /*vazio*/{}
;

tipo: INT{}
               | CHAR{}
               | VOID{}
;

blocos: L_CURLY_BRACKET comandos R_CURLY_BRACKET{}
;

comandos: lista_de_comandos_loop{}
;

lista_de_comandos_loop: lista_de_comandos lista_de_comandos_loop{}
               | /*vazio*/{}
;

%%
int main(int argc, char** argv)
{
   yyparse();    
   return 0;
}