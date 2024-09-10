#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


typedef enum {
    ALGORITMO = 1,
    INICIO,
    FIM,
    VARIAVEIS,
    INTEIRO,
    REAL,
    CARACTERE,
    LOGICO,
    VETOR,
    MATRIZ,
    TIPO,
    FUNCAO,
    PROCEDIMENTO,
    SE,
    ENTAO,
    SENAO,
    ENQUANTO,
    FACA,
    PARA,
    DE,
    ATE,
    PASSO,
    REPITA,
    LEIA,
    IMPRIMA,
    VERDADEIRO,
    FALSO,
    E,
    OU,
    NAO,
    DIV,
    PONTO_VIRGULA,
    VIRGULA,
    DOIS_PONTOS,
    PONTO,
    ABRE_COLCHETE,
    FECHA_COLCHETE,
    ABRE_PARENTESE,
    FECHA_PARENTESE,
    IGUAL,
    DIFERENTE,
    MAIOR_IGUAL,
    MENOR_IGUAL,
    ATRIBUICAO_ESQUERDA,
    MAIOR,
    MENOR,
    MAIS,
    MENOS,
    MULTIPLICACAO,
    DIVISAO,
    IDENTIFICADOR,
    NUMERO_INTEIRO,
    NUMERO_REAL,
    STRING,
    COMENTARIO_EM_LINHA,
    COMENTARIO_EM_BLOCO,
} TokenType;

//Funcao utilziada para converter o valor do enum em uma string
const char* tokenTypeToString(TokenType token) {
    switch (token) {
        case ALGORITMO: return "algoritmo";
        case INICIO: return "inicio";
        case FIM: return "fim";
        case VARIAVEIS: return "variaveis";
        case INTEIRO: return "inteiro";
        case REAL: return "real";
        case CARACTERE: return "caractere";
        case LOGICO: return "logico";
        case VETOR: return "vetor";
        case MATRIZ: return "matriz";
        case TIPO: return "tipo";
        case FUNCAO: return "funcao";
        case PROCEDIMENTO: return "procedimento";
        case SE: return "se";
        case ENTAO: return "entao";
        case SENAO: return "senao";
        case ENQUANTO: return "enquanto";
        case FACA: return "faca";
        case PARA: return "para";
        case DE: return "de";
        case ATE: return "ate";
        case PASSO: return "passo";
        case REPITA: return "repita";
        case LEIA: return "leia";
        case IMPRIMA: return "imprima";
        case VERDADEIRO: return "verdadeiro";
        case FALSO: return "falso";
        case E: return "e";
        case OU: return "ou";
        case NAO: return "nao";
        case DIV: return "div";
        case PONTO_VIRGULA: return ";";
        case VIRGULA: return ",";
        case DOIS_PONTOS: return ":";
        case PONTO: return ".";
        case ABRE_COLCHETE: return "[";
        case FECHA_COLCHETE: return "]";
        case ABRE_PARENTESE: return "(";
        case FECHA_PARENTESE: return ")";
        case IGUAL: return "=";
        case DIFERENTE: return "<>";
        case MAIOR_IGUAL: return ">=";
        case MENOR_IGUAL: return "<=";
        case ATRIBUICAO_ESQUERDA: return "<-";
        case MAIOR: return ">";
        case MENOR: return "<";
        case MAIS: return "+";
        case MENOS: return "-";
        case MULTIPLICACAO: return "*";
        case DIVISAO: return "/";
        case IDENTIFICADOR: return "identificador";
        case NUMERO_INTEIRO: return "numero inteiro";
        case NUMERO_REAL: return "numero real";
        case STRING: return "string";
        case COMENTARIO_EM_LINHA: return "comentario em linha";
        case COMENTARIO_EM_BLOCO: return "comentario em bloco";
        default: return "UNKNOWN";
    }
}


int token_posicao;
int erro_sintatico;
int tamanho_maximo_tokens;
int primeira_linha;

void quebra_linha(){
    if (!primeira_linha) printf("\n");
    primeira_linha = 0;
}
/*
// ===== INICIO SINTATICO =====
void S(int *vetor);
void E(int *vetor);
void ELinha(int *vetor);
void T(int *vetor);
void TLinha(int *vetor);
void F(int *vetor);

void eat(int t, int *vetor) {
    if (vetor[token_posicao] == t) {
        token_posicao++;
    } else if (!erro_sintatico) {
        if (token_posicao > tamanho_maximo_tokens) {
            quebra_linha();
            printf("ERRO SINTATICO EM: %s ESPERADO: %s", tokenTypeToString(vetor[token_posicao]), tokenTypeToString(t)); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
            erro_sintatico = 1;
            return;
        } else {
            quebra_linha();
            printf("ERRO SINTATICO EM: %s ESPERADO: %s", tokenTypeToString(vetor[token_posicao]), tokenTypeToString(t));
            erro_sintatico = 1;
            return;
        }
    }
}

void S(int *vetor) {
    if(tamanho_maximo_tokens==-1){
        quebra_linha();
        printf("ERRO SINTATICO EM: ESPERADO: id, (");
        erro_sintatico = 1;
        return;
    }
    switch (vetor[token_posicao]) {
        case IDENTIFIER:
            E(vetor); eat(DOLLAR, vetor); break;
        case LEFTPARENTHESIS:
            E(vetor); eat(DOLLAR, vetor); break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    quebra_linha();
                    printf("ERRO SINTATICO EM: ESPERADO: id, ("); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                quebra_linha();
                printf("ERRO SINTATICO EM: %s ESPERADO: id, (", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            return;
    }
}

void E(int *vetor) {
    switch (vetor[token_posicao]) {
        case IDENTIFIER:
            T(vetor); ELinha(vetor); break;
        case LEFTPARENTHESIS:
            T(vetor); ELinha(vetor); break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    quebra_linha();
                    printf("ERRO SINTATICO EM: ESPERADO: id, ("); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                quebra_linha();
                printf("ERRO SINTATICO EM: %s ESPERADO: id, (", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

void ELinha(int *vetor) {
    switch (vetor[token_posicao]) {
        case PLUS:
            eat(PLUS, vetor); T(vetor); ELinha(vetor); break;
        case RIGHTPARENTHESIS:
            break;
        case DOLLAR:
            break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    quebra_linha();
                    printf("ERRO SINTATICO EM: ESPERADO: +, ), $"); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                quebra_linha();
                printf("ERRO SINTATICO EM: %s ESPERADO: +, ), $", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

void T(int *vetor) {
    switch (vetor[token_posicao]) {
        case IDENTIFIER:
            F(vetor); TLinha(vetor); break;
            break;
        case LEFTPARENTHESIS:
            F(vetor); TLinha(vetor); break;
            break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    quebra_linha();
                    printf("ERRO SINTATICO EM: ESPERADO: id, ("); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                quebra_linha();
                printf("ERRO SINTATICO EM: %s ESPERADO: id, (", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

void TLinha(int *vetor) {
    switch (vetor[token_posicao]) {
        case MULTIPLY:
            eat(MULTIPLY, vetor); F(vetor); TLinha(vetor); break;
        case PLUS:
            break;
        case RIGHTPARENTHESIS:
            break;
        case DOLLAR:
            break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    quebra_linha();
                    printf("ERRO SINTATICO EM: ESPERADO: +, *, ), $"); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                quebra_linha();
                printf("ERRO SINTATICO EM: %s ESPERADO: +, *, ), $", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

void F(int *vetor) {
    switch (vetor[token_posicao]) {
        case IDENTIFIER:
            eat(IDENTIFIER, vetor); break;
        case LEFTPARENTHESIS:
            eat(LEFTPARENTHESIS, vetor); E(vetor); eat(RIGHTPARENTHESIS, vetor); break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    quebra_linha();
                    printf("ERRO SINTATICO EM: ESPERADO: id, ("); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                quebra_linha();
                printf("ERRO SINTATICO EM: %s ESPERADO: id, (", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}
// ===== FIM SINTATICO =====
*/

int main() {
    char *string = NULL;
    size_t length = 0;
    int read;
    primeira_linha = 1;
    int erro_lexico;

    while ((read = getline(&string, &length, stdin)) != -1) {
        //Reseta estados
        token_posicao = 0;
        erro_sintatico = 0;
        erro_lexico = 0;
        
        //Alocacao dinamica para o vetor de inteiros
        int vetor_capacidade = 100;
        int *vetor = (int *)malloc(vetor_capacidade * sizeof(int));
        if (vetor == NULL) {
            perror("Erro ao alocar memoria");
            exit(EXIT_FAILURE);
        }
        int posicao = 0;
        int i = 0;

        // ===== ANALISADOR LEXICO =====
        //Aqui a cadeia lida eh Tokenizada
        while (string[i] != '\0' && string[i] != '\n') {
            //printf("\n i = %d ", i);

            if(strncasecmp(&string[i], "algoritmo", 9) == 0) {
                vetor[posicao++] = ALGORITMO;
                printf("algoritmo\n");
                i += 9;
            }else if (strncasecmp(&string[i], "inicio", 6) == 0) {
                vetor[posicao++] = INICIO;
                printf("inicio\n");
                i += 6;
            }else if (strncasecmp(&string[i], "fim", 3) == 0) {
                vetor[posicao++] = FIM;
                printf("fim\n");
                i += 3;
            }else if (strncasecmp(&string[i], "variaveis", 9) == 0) {
                vetor[posicao++] = VARIAVEIS;
                printf("variaveis\n");
                i += 9;
            }else if (strncasecmp(&string[i], "inteiro", 7) == 0) {
                vetor[posicao++] = INTEIRO;
                printf("inteiro\n");
                i += 7;
            }else if (strncasecmp(&string[i], "real", 4) == 0) {
                vetor[posicao++] = REAL;
                printf("real\n");
                i += 4;
            }else if (strncasecmp(&string[i], "caractere", 9) == 0) {
                vetor[posicao++] = CARACTERE;
                printf("caractere\n");
                i += 9;
            }else if (strncasecmp(&string[i], "logico", 6) == 0) {
                vetor[posicao++] = LOGICO;
                printf("logico\n");
                i += 6;
            }else if (strncasecmp(&string[i], "vetor", 5) == 0) {
                vetor[posicao++] = VETOR;
                printf("vetor\n");
                i += 5;
            }else if (strncasecmp(&string[i], "matriz", 6) == 0) {
                vetor[posicao++] = MATRIZ;
                printf("matriz\n");
                i += 6;
            }else if (strncasecmp(&string[i], "tipo", 4) == 0) {
                vetor[posicao++] = TIPO;
                printf("tipo\n");
                i += 4;
            }            if (strncasecmp(&string[i], "funcao", 6) == 0) {
               vetor[posicao++] = FUNCAO;
               printf("funcao\n");
               i += 6;
            } else if (strncasecmp(&string[i], "procedimento", 12) == 0) {
               vetor[posicao++] = PROCEDIMENTO;
               printf("procedimento\n");
               i += 12;
            } else if (strncasecmp(&string[i], "se", 2) == 0) {
               vetor[posicao++] = SE;
               printf("se\n");
               i += 2;
            } else if (strncasecmp(&string[i], "entao", 5) == 0) {
               vetor[posicao++] = ENTAO;
               printf("entao\n");
               i += 5;
            } else if (strncasecmp(&string[i], "senao", 5) == 0) {
               vetor[posicao++] = SENAO;
               printf("senao\n");
               i += 5;
            } else if (strncasecmp(&string[i], "enquanto", 8) == 0) {
               vetor[posicao++] = ENQUANTO;
               printf("enquanto\n");
               i += 8;
            } else if (strncasecmp(&string[i], "faca", 4) == 0) {
               vetor[posicao++] = FACA;
               printf("faca\n");
               i += 4;
            } else if (strncasecmp(&string[i], "para", 4) == 0) {
               vetor[posicao++] = PARA;
               printf("para\n");
               i += 4;
            } else if (strncasecmp(&string[i], "de", 2) == 0) {
               vetor[posicao++] = DE;
               printf("de\n");
               i += 2;
            } else if (strncasecmp(&string[i], "ate", 3) == 0) {
               vetor[posicao++] = ATE;
               printf("ate\n");
               i += 3;
            } else if (strncasecmp(&string[i], "passo", 5) == 0) {
               vetor[posicao++] = PASSO;
               printf("passo\n");
               i += 5;
            } else if (strncasecmp(&string[i], "repita", 6) == 0) {
               vetor[posicao++] = REPITA;
               printf("repita\n");
               i += 6;
            } else if (strncasecmp(&string[i], "leia", 4) == 0) {
               vetor[posicao++] = LEIA;
               printf("leia\n");
               i += 4;
            } else if (strncasecmp(&string[i], "imprima", 7) == 0) {
               vetor[posicao++] = IMPRIMA;
               printf("imprima\n");
               i += 7;
            } else if (strncasecmp(&string[i], "verdadeiro", 10) == 0) {
               vetor[posicao++] = VERDADEIRO;
               printf("verdadeiro\n");
               i += 10;
            } else if (strncasecmp(&string[i], "falso", 5) == 0) {
               vetor[posicao++] = FALSO;
               printf("falso\n");
               i += 5;
            } else if (strncasecmp(&string[i], "e", 1) == 0) {
               vetor[posicao++] = E;
               printf("e\n");
               i += 1;
            } else if (strncasecmp(&string[i], "ou", 2) == 0) {
               vetor[posicao++] = OU;
               printf("ou\n");
               i += 2;
            } else if (strncasecmp(&string[i], "nao", 3) == 0) {
               vetor[posicao++] = NAO;
               printf("nao\n");
               i += 3;
            } else if (strncasecmp(&string[i], "div", 3) == 0) {
               vetor[posicao++] = DIV;
               printf("div\n");
               i += 3;
            }  else if (strncasecmp(&string[i], ";", 1) == 0) {
               vetor[posicao++] = PONTO_VIRGULA;
               printf(";\n");
               i += 1;
            } else if (strncasecmp(&string[i], ",", 1) == 0) {
               vetor[posicao++] = VIRGULA;
               printf(",\n");
               i += 1;
            } else if (strncasecmp(&string[i], ":", 1) == 0) {
               vetor[posicao++] = DOIS_PONTOS;
               printf(":\n");
               i += 1;
            } else if (strncasecmp(&string[i], ".", 1) == 0) {
               vetor[posicao++] = PONTO;
               printf(".\n");
               i += 1;
            } else if (strncasecmp(&string[i], "[", 1) == 0) {
               vetor[posicao++] = ABRE_COLCHETE;
               printf("[\n");
               i += 1;
            } else if (strncasecmp(&string[i], "]", 1) == 0) {
               vetor[posicao++] = FECHA_COLCHETE;
               printf("]\n");
               i += 1;
            } else if (strncasecmp(&string[i], "(", 1) == 0) {
               vetor[posicao++] = ABRE_PARENTESE;
               printf("(\n");
               i += 1;
            } else if (strncasecmp(&string[i], ")", 1) == 0) {
               vetor[posicao++] = FECHA_PARENTESE;
               printf(")\n");
               i += 1;
            } else if (strncasecmp(&string[i], "=", 1) == 0) {
               vetor[posicao++] = IGUAL;
               printf("=\n");
               i += 1;
            } else if (strncasecmp(&string[i], "<>", 2) == 0) {
               vetor[posicao++] = DIFERENTE;
               printf("<>\n");
               i += 2;
            } else if (strncasecmp(&string[i], ">=", 2) == 0) {
               vetor[posicao++] = MAIOR_IGUAL;
               printf(">=\n");
               i += 2;
            } else if (strncasecmp(&string[i], "<=", 2) == 0) {
               vetor[posicao++] = MENOR_IGUAL;
               printf("<=\n");
               i += 2;
            } else if (strncasecmp(&string[i], "<-", 2) == 0) {
               vetor[posicao++] = ATRIBUICAO_ESQUERDA;
               printf("<-\n");
               i += 2;
            } else if (strncasecmp(&string[i], ">", 1) == 0) {
               vetor[posicao++] = MAIOR;
               printf(">\n");
               i += 1;
            } else if (strncasecmp(&string[i], "<", 1) == 0) {
               vetor[posicao++] = MENOR;
               printf("<\n");
               i += 1;
            } else if (strncasecmp(&string[i], "+", 1) == 0) {
               vetor[posicao++] = MAIS;
               printf("+\n");
               i += 1;
            } else if (strncasecmp(&string[i], "-", 1) == 0) {
               vetor[posicao++] = MENOS;
               printf("-\n");
               i += 1;
            } else if (strncasecmp(&string[i], "*", 1) == 0) {
               vetor[posicao++] = MULTIPLICACAO;
               printf("*\n");
               i += 1;
            }else if(string[i]=='/' && string[i+1]=='/'){// reconhecimento de comentarios de linha
                i+=1; //add dois por conta das duas barras
                while (string[i] != '\n') {
                    i++;
                }
                printf("comentario em linha\n");
                i++;
                vetor[posicao++] = COMENTARIO_EM_LINHA;
            } else if (strncasecmp(&string[i], "/", 1) == 0) { // o reconhecimento da divisao deve ser abaixo do comentario de linha por questoes de precedencia
               vetor[posicao++] = DIVISAO;
               printf("/\n");
               i += 1;
            }else if((strncmp(&string[i], " ", 1) == 0)||(strncmp(&string[i], "\n", 1) == 0)||(strncmp(&string[i], "\r", 1) == 0)||(strncmp(&string[i], "\0", 1) == 0)){
                i++; //Para ignorar espacos e quebra de linha
            } else if ((string[i] >= 'a' && string[i] <= 'z')||(string[i] >= 'A' && string[i] <= 'Z')||(string[i]=='_')) {//[a-zA-Z_][a-zA-Z0-9_]*
                //printf("\n\n%d ", i);
                vetor[posicao++] = IDENTIFICADOR;
                while ((string[i] >= 'a' && string[i] <= 'z')||(string[i] >= 'A' && string[i] <= 'Z')||(string[i]=='_')||(string[i] >= '0' && string[i] <= '9')) {
                    i++;
                }
                printf("Identificador\n");
            } else if(string[i] >= '0' && string[i] <= '9'){//[0-9]+
                vetor[posicao++] = NUMERO_INTEIRO;
                while (string[i] >= '0' && string[i] <= '9') {
                    i++;
                }
                if(string[i]=='.'){ //[0-9]+.[0-9]*
                    vetor[posicao++] = NUMERO_REAL;
                    printf("Numero real\n");
                    i++;
                    while (string[i] >= '0' && string[i] <= '9') {
                        i++;
                    }
                }else{
                    printf("Numero inteiro\n");//[0-9]+
                }
            }else if(string[i]=='"'){// token string "texto"
                i++;
                while ((string[i] >= 32 && string[i] <= 33)||(string[i] >= 35 && string[i] <= 126)) {
                    i++;
                }
                if(string[i]=='"'){
                    printf("string\n");
                }else{
                    printf("ERRO LEXICO: %c", string[i]);
                    return 0;
                }
                i++; //precisa desse i++ para não detectar o fechamento da string como uma nova string
                vetor[posicao++] = STRING;
            }else if (string[i] == '{') {  // Reconhecimento de comentário em bloco
                i++;  // Avança para o próximo caractere depois de '{'

                while (1) {  // Loop infinito até encontrar o '}' que fecha o comentário
                    // Se chegar ao final da string atual, ler uma nova linha
                    if (string[i] == '\n') {
                        getline(&string, &length, stdin);  // Lê a próxima linha
                        i = 0;  // Reinicia o índice 'i' para a nova linha
                    }

                    // Se encontrar o '}' que fecha o comentário
                    if (string[i] == '}') {
                        printf("comentário em bloco\n");
                        i++;  // Avança após '}'
                        break;  // Sai do loop, comentário fechado
                    }
                    // Avança para o próximo caractere
                    i++;
                    if(string[i]=='\0'){ //isso aqui é para caso um comentario em bloco nao tenha sido finalizado corretamente
                        return 0;
                    }

                    vetor[posicao++] = COMENTARIO_EM_BLOCO;
                }
            }else {
                quebra_linha();
                printf("ERRO LEXICO: %c aa", string[i]);
                erro_lexico = 1;
                return 0; 
            }
             
            // ===== FIM ANALISADOR LEXICO
            
            //Se necessario, Aqui eh aumentada a capacidade do vetor
            if (posicao >= vetor_capacidade) {
                vetor_capacidade *= 2;
                vetor = (int *)realloc(vetor, vetor_capacidade * sizeof(int));
                if (vetor == NULL) {
                    perror("Erro ao realocar memoria");
                    exit(EXIT_FAILURE);
                }
            }
            
        }

        tamanho_maximo_tokens = posicao - 1;

        if(!erro_lexico){
            //S(vetor); //Chama o analisador sintatico

            if (!erro_sintatico) {
                //quebra_linha();
                //printf("CADEIA ACEITA");
                primeira_linha = 0;
            }
        }
        
        
        //Liberar memoria alocada para o vetor de inteiros
        free(vetor);
    }

    //Libera a memoria usada para a string
    free(string);

    return 0;
}