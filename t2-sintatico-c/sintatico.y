 %{
 #include <stdio.h>
 #include <stdlib.h>
 extern int yylex();
 extern char* yytext;
 extern int line_num;
 extern int column_num;
 void yyerror(void *s);
 extern void print_quebra(); 
 extern char line_buffer[];
 extern void SET_buffer(int total_lines);
 
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
programa: declaracoes programa {}
    | funcao programa {}
    | /* vazio*/ {}
; 

declaracoes: NUMBER_SIGN DEFINE IDENTIFIER expressao { }
   | declaracao_de_variaveis { }
   | declaracao_de_prototipo { }
;

funcao: tipo multiply_loop IDENTIFIER parametros L_CURLY_BRACKET declaracao_de_variaveis_loop comandos R_CURLY_BRACKET { }
;

multiply_loop: MULTIPLY multiply_loop   { }
               | /* vazio */ {}
;

declaracao_de_variaveis_loop: declaracao_de_variaveis declaracao_de_variaveis_loop   { }
               | /* vazio */{}
;

declaracao_de_variaveis: tipo declaracao_de_variaveis_cerne SEMICOLON{ }
;

declaracao_de_variaveis_cerne: multiply_loop IDENTIFIER expressao_loop igual_expr_atrib declaracao_de_variaveis_cerne_loop{ }
;

igual_expr_atrib: ASSIGN expressao_de_atribuicao{}
               | {}
;

declaracao_de_variaveis_cerne_loop: COMMA declaracao_de_variaveis_cerne {}
               | /*vazio*/{}
;
expressao_loop: L_SQUARE_BRACKET expressao R_SQUARE_BRACKET expressao_loop{}
               | /*vazio*/{}

;

declaracao_de_prototipo: tipo multiply_loop IDENTIFIER parametros SEMICOLON{}
;

parametros: L_PAREN parametros_controle R_PAREN{}
;

parametros_controle: parametros_cerne{}
               | {}
;

parametros_cerne: tipo multiply_loop IDENTIFIER expressao_loop parametros_cerne_loop{}
;

parametros_cerne_loop: COMMA parametros_cerne
               | /*vazio*/{}
;

tipo: INT{}
               | CHAR{}
               | VOID{}
;

bloco: L_CURLY_BRACKET comandos R_CURLY_BRACKET{}
;

comandos: lista_de_comandos_loop{}
;

lista_de_comandos_loop: lista_de_comandos lista_de_comandos_loop{}
               | /*vazio*/{}
;

lista_de_comandos: DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON {}
               | IF L_PAREN expressao R_PAREN bloco complem_else_bloco {}
               | WHILE L_PAREN expressao R_PAREN bloco {}
               | FOR L_PAREN complem_expressao SEMICOLON complem_expressao SEMICOLON complem_expressao R_PAREN bloco {}
               | PRINTF L_PAREN STRING complem_comma_expr R_PAREN SEMICOLON {}
               | SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON {}
               | EXIT L_PAREN expressao R_PAREN SEMICOLON {} 
               | RETURN complem_expressao SEMICOLON {}
               | expressao SEMICOLON {}
               | SEMICOLON {}
               | bloco {}
;

complem_else_bloco: ELSE bloco {}
               | /*vazio*/ {}
;

complem_expressao: expressao {}
               | /*vazio*/ {}
;

complem_comma_expr: COMMA expressao {}
               |  {}
;

expressao: expressao_de_atribuicao {}
               | expressao COMMA expressao_de_atribuicao {}
;

expressao_de_atribuicao: expressao_condicional {}
               |expressao_unaria operadores expressao_de_atribuicao {}
;

operadores: ASSIGN{}
               | ADD_ASSIGN {}
               | MINUS_ASSIGN {}
;

expressao_condicional: expressao_or_logico {}
               | expressao_or_logico TERNARY_CONDITIONAL expressao COLON expressao_condicional {}
;

expressao_or_logico: expressao_and_logico {}
               | expressao_or_logico LOGICAL_OR expressao_and_logico {}
;

expressao_and_logico: expressao_or {}
               | expressao_and_logico LOGICAL_AND expressao_or {}
;

expressao_or: expressao_xor {}
               | expressao_or BITWISE_OR expressao_xor {}
;

expressao_xor: expressao_and {}
               | expressao_xor BITWISE_XOR expressao_and{}
;

expressao_and: expressao_de_igualdade {}
               | expressao_and BITWISE_AND expressao_de_igualdade {}
;

expressao_de_igualdade: expressao_relacional {}
               | expressao_de_igualdade equal_or_not_equal expressao_relacional {}
;

equal_or_not_equal: EQUAL {}
               | NOT_EQUAL {}
;

expressao_relacional: expressao_shift {}
               | expressao_relacional comparadores expressao_shift {}
;

comparadores: LESS_THAN {}
               | LESS_EQUAL {}
               | GREATER_THAN {}
               | GREATER_EQUAL {}
;

expressao_shift: expressao_aditiva {}
               | expressao_shift opshifts expressao_aditiva {}
;

opshifts: R_SHIFT {}
               | L_SHIFT {}
;

expressao_aditiva: expressao_multiplicativa {}
               | expressao_aditiva minus_or_plus expressao_multiplicativa {}
;

minus_or_plus: MINUS {}
               | PLUS {}
;

expressao_multiplicativa: expressao_cast {}
               | expressao_multiplicativa operadores_multiplicativa expressao_cast {}
;

operadores_multiplicativa: MULTIPLY {}
               | DIV {}
               | REMAINDER {}
;

expressao_cast: expressao_unaria {}
               | L_PAREN tipo multiply_loop R_PAREN expressao_cast {}
;

expressao_unaria: expressao_pos_fixa {}
               | INC expressao_unaria {}
               | DEC expressao_unaria {}
               | operadores_unaria expressao_cast {}
;

operadores_unaria: BITWISE_AND {}
               | MULTIPLY {}
               | PLUS {}
               | MINUS {}
               | BITWISE_NOT {}
               | NOT {}
;

expressao_pos_fixa: expressa_primaria {}
               | expressao_pos_fixa L_SQUARE_BRACKET expressao R_SQUARE_BRACKET {}
               | expressao_pos_fixa INC {}
               | expressao_pos_fixa DEC {}
               | expressao_pos_fixa L_PAREN expressao_de_atribuicao_loop R_PAREN {}
;

expressao_de_atribuicao_loop: expressao_de_atribuicao {}
               | expressao_de_atribuicao COMMA expressao_de_atribuicao_loop
               | {}
;

expressa_primaria: IDENTIFIER{}
               | numero {}
               | CHARACTER {}
               | STRING {}
               | L_PAREN expressao R_PAREN {}
;

numero: NUM_INTEGER{}
               | NUM_HEXA {}
               | NUM_OCTAL {}
;
%%
void yyerror(void *s){
    SET_buffer(line_num);
    if (yychar == 0){
        printf("error:syntax:%d:%d: expected declaration or statement at end of input\n%s\n", line_num, column_num, line_buffer);
    } 

	printf("error:syntax:%d:%d: %s", line_num, column_num, yytext);
	printf("\n%s", line_buffer);  // Imprime o conteúdo da linha atual
    for(int i = 0; i < column_num-1 ; i++) {
		printf(" "); //Alinha o ^ com o erro
	}
    printf("^");
    print_quebra();  // Função para limpeza ou manipulação adicional
    exit(1);
}

int main(int argc, char** argv)
{
   yyparse();
   print_quebra();
   printf("SUCCESSFUL COMPILATION.");
   return 0;
}