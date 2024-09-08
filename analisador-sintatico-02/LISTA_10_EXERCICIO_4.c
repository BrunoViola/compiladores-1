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
            //printf("ERRO SINTATICO: CADEIA INCOMPLETA");
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
          //  printf("\n%d", tamanho_maximo_tokens);
    if(tamanho_maximo_tokens==-1){
        printf("ERRO SINTATICO EM: ESPERADO: id, (");
                erro_sintatico = 1;
            
            return;
    }
    switch (vetor[token_posicao]) {
        case IDENTIFIER:
            E(vetor); eat(DOLLAR, vetor); break;
        case LEFTPARENTHESIS:
            //printf("entrou1\n");
            E(vetor); eat(DOLLAR, vetor); break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    //printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
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
                    //printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
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
                    //printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
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
                    //printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
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
                    printf("ERRO SINTATICO EM: %c ESPERADO: +, *, ), $", vetor[token_posicao]);
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                printf("ERRO SINTATICO EM: %s ESPERADO: +, *, ), $", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}

void F(int *vetor) {
    switch (vetor[token_posicao]) {
        case IDENTIFIER:
                    //printf("entrou4\n");

            eat(IDENTIFIER, vetor); break;
        case LEFTPARENTHESIS:
            eat(LEFTPARENTHESIS, vetor); E(vetor); eat(RIGHTPARENTHESIS, vetor); break;
        default:
            if (token_posicao > tamanho_maximo_tokens) {
                if (!erro_sintatico) {
                    //printf("ERRO SINTATICO: CADEIA INCOMPLETA");
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                printf("ERRO SINTATICO EM: %s ESPERADO: id, (", tokenTypeToString(vetor[token_posicao]));
                erro_sintatico = 1;
            }
            break;
    }
}
// ===== FIM SINTATICO =====

int main() {
    char *string = NULL;
    size_t length = 0;
    int read;
    int primeira_linha = 1;
    int erro_lexico;

    while ((read = getline(&string, &length, stdin)) != -1) {
        //Reseta estados
        token_posicao = 0;
        erro_sintatico = 0;
        erro_lexico = 0;
        
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
                if (!primeira_linha) printf("\n");
                primeira_linha = 0;
                printf("ERRO LEXICO: %c", string[i]);
                erro_lexico = 1;
                while(string[i]!='\n' && string[i]!='\0') i++; //adicionei esse while para que quando um primeiro erro seja detectado, a análise de erro lexico para uma linha é imediatamente parada e passamos para a proxima linha (caso ela exista)
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

        //printf("\n%d", tamanho_maximo_tokens);

        //Chamar o analisador sintatico
        if(!erro_lexico){
            S(vetor);

            if (!erro_sintatico) {
                printf("CADEIA ACEITA");
            }
        }
        if (!primeira_linha) printf("\n");
        primeira_linha = 0;
        
        //Liberar memoria alocada para o vetor de inteiros
        free(vetor);
    }

    //Libera a memoria usada para a string
    free(string);

    return 0;
}
