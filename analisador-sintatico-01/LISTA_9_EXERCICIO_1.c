#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    IF = 1,
    THEN,
    ELSE,
    BEGIN,
    END,
    PRINT,
    SEMI,
    NUM,
    EQ
} TokenType;

//Funcao utilziada para converter o valor do enum em uma string
const char* tokenTypeToString(TokenType token) {
    switch (token) {
        case IF: return "if";
        case THEN: return "then";
        case ELSE: return "else";
        case BEGIN: return "begin";
        case END: return "end";
        case PRINT: return "print";
        case SEMI: return ";";
        case NUM: return "num";
        case EQ: return "=";
        default: return "UNKNOWN";
    }
}

int token_posicao;
int erro_sintatico;
int tamanho_maximo_tokens;

void S(int *vetor);
void L(int *vetor);
void E(int *vetor);

void eat(int t, int *vetor) {
    if (vetor[token_posicao] == t) {
        token_posicao++;
    } else if (!erro_sintatico) {
        if (token_posicao > tamanho_maximo_tokens) {
            printf("ERRO SINTATICO: CADEIA INCOMPLETA");
            erro_sintatico = 1;
            return;
        } else {
            printf("ERRO SINTATICO EM: %s ESPERADO: %s", tokenTypeToString(vetor[token_posicao]), tokenTypeToString(t));
            erro_sintatico = 1;
            return;
        }
    }
}

void S(int *vetor) {
    switch (vetor[token_posicao]) {
        case IF:
            eat(IF, vetor); E(vetor); eat(THEN, vetor); S(vetor); eat(ELSE, vetor); S(vetor);
            break;
        case BEGIN:
            eat(BEGIN, vetor); S(vetor); L(vetor);
            break;
        case PRINT:
            eat(PRINT, vetor); E(vetor);
            break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                printf("ERRO SINTATICO EM: %s ESPERADO: if, begin, print", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            return;
    }
}

void L(int *vetor) {
    switch (vetor[token_posicao]) {
        case END:
            eat(END, vetor);
            break;
        case SEMI:
            eat(SEMI, vetor); S(vetor); L(vetor);
            break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                printf("ERRO SINTATICO EM: %s ESPERADO: end, ;", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

void E(int *vetor) {
    switch (vetor[token_posicao]) {
        case NUM:
            eat(NUM, vetor); eat(EQ, vetor); eat(NUM, vetor);
            break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                printf("ERRO SINTATICO EM: %s ESPERADO: num", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

int main() {
    char *string = NULL;
    size_t length = 0;
    int read;
    int primeira_linha = 1;

    while ((read = getline(&string, &length, stdin)) != -1) {
        //Reseta estados
        token_posicao = 0;
        erro_sintatico = 0;
        
        // Alocação dinamica para o vetor de inteiros
        int vetor_capacidade = 100;
        int *vetor = (int *)malloc(vetor_capacidade * sizeof(int));
        if (vetor == NULL) {
            perror("Erro ao alocar memoria");
            exit(EXIT_FAILURE);
        }
        int posicao = 0;
        int i = 0;

        //Aqui a cadeia lida é Tokenizada
        while (string[i] != '\0' && string[i] != '\n') {
            if (strncmp(&string[i], "if", 2) == 0) {
                vetor[posicao++] = IF;
                i += 2;
            } else if (strncmp(&string[i], "then", 4) == 0) {
                vetor[posicao++] = THEN;
                i += 4;
            } else if (strncmp(&string[i], "else", 4) == 0) {
                vetor[posicao++] = ELSE;
                i += 4;
            } else if (strncmp(&string[i], "begin", 5) == 0) {
                vetor[posicao++] = BEGIN;
                i += 5;
            } else if (strncmp(&string[i], "end", 3) == 0) {
                vetor[posicao++] = END;
                i += 3;
            } else if (strncmp(&string[i], "print", 5) == 0) {
                vetor[posicao++] = PRINT;
                i += 5;
            } else if (string[i] == ';') {
                vetor[posicao++] = SEMI;
                i++;
            } else if (string[i] == '=') {
                vetor[posicao++] = EQ;
                i++;
            } else if (string[i] >= '0' && string[i] <= '9') {
                vetor[posicao++] = NUM;
                while (string[i] >= '0' && string[i] <= '9') {
                    i++;
                }
            } else {
                i++;  //Para ignorar espacos e outros caracteres
            }

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

        if (!primeira_linha) printf("\n");
        primeira_linha = 0;

        //Chamar o analisador sintatico
        S(vetor);

        if (!erro_sintatico) {
            printf("CADEIA ACEITA");
        }

        //Liberar memoria alocada para o vetor de inteiros
        free(vetor);
    }

    //Libera a memoria usada para a string
    free(string);

    return 0;
}
