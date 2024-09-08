#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DOLLAR = 1,
    PLUS,
    MULTIPLY,
    LEFTPARENTHESIS,
    RIGHTPARENTHESIS,
    IDENTIFIER,
    SEMI,
    NUM,
    EQ
} TokenType;

//Funcao utilziada para converter o valor do enum em uma string
const char* tokenTypeToString(TokenType token) {
    switch (token) {
        case DOLLAR: return "$";
        case PLUS: return "+";
        case MULTIPLY: return "*";
        case LEFTPARENTHESIS: return "(";
        case RIGHTPARENTHESIS: return ")";
        case IDENTIFIER: return "id";
        default: return "UNKNOWN";
    }
}

int token_posicao;
int erro_sintatico;
int tamanho_maximo_tokens;
/*
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
        case DOLLAR:
            eat(DOLLAR, vetor); E(vetor); eat(PLUS, vetor); S(vetor); eat(MULTIPLY, vetor); S(vetor);
            break;
        case LEFTPARENTHESIS:
            eat(LEFTPARENTHESIS, vetor); S(vetor); L(vetor);
            break;
        case RIGHTPARENTHESIS:
            eat(RIGHTPARENTHESIS, vetor); E(vetor);
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
        case LEFTPARENTHESIS:
            eat(LEFTPARENTHESIS, vetor);
            break;
        case RIGHTPARENTHESIS:
            eat(RIGHTPARENTHESIS, vetor); S(vetor); L(vetor);
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
*/
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
            if (strncmp(&string[i], "$", 1) == 0) {
                vetor[posicao++] = DOLLAR;
                i ++;
            } else if (strncmp(&string[i], "+", 1) == 0) {
                vetor[posicao++] = PLUS;
                i ++;
            } else if (strncmp(&string[i], "*", 1) == 0) {
                vetor[posicao++] = MULTIPLY;
                i ++;
            } else if (strncmp(&string[i], "(", 1) == 0) {
                vetor[posicao++] = LEFTPARENTHESIS;
                i ++;
            } else if (strncmp(&string[i], ")", 1) == 0) {
                vetor[posicao++] = RIGHTPARENTHESIS;
                i ++;
            } else if (string[i] >= 'a' && string[i] <= 'z') {
                vetor[posicao++] = IDENTIFIER;
                while ((string[i] >= 'a' && string[i] <= 'z')||(string[i] >= '0' && string[i] <= '9')) {
                    i++;
                }
            } else if((strncmp(&string[i], " ", 1) == 0)||(strncmp(&string[i], "\n", 1) == 0)||(strncmp(&string[i], "\r", 1) == 0)){
                i++; //Para ignorar espacos e quebra de linha
            }else {
                printf("ERRO LEXICO: %c", string[i]);
                i++;  
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
        //S(vetor);

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
