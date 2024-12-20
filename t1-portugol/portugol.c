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

typedef struct {
    int token;         // ID do token (tipo do token)
    int linha;         // Linha onde o token foi encontrado
    int coluna;        // Coluna onde o token foi encontrado
    char palavra[300];
} TokenInfo;

//Funcao utilizada para converter o valor do enum em uma string
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
int local=0;
int erro_sintatico;
int local;
int primeira_linha;

void armazenar_token(TokenInfo *vetor, int token, int linha, int coluna) {
    vetor[local].token = token;
    vetor[local].linha = linha;
    vetor[local].coluna = coluna;
    
    local++;
}   

void imprimir_erro_sintatico(TokenInfo *vetor, int token_posicao){
    if(vetor[token_posicao].token == IDENTIFICADOR){
        printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", vetor[token_posicao].linha, vetor[token_posicao].coluna, vetor[token_posicao].palavra);
    }else{
        printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", vetor[token_posicao].linha, vetor[token_posicao].coluna, tokenTypeToString(vetor[token_posicao].token));
    }
}

// ============================
// ===== INICIO SINTATICO =====
void PROGRAMA(TokenInfo *vetor);
void PROCEDIMENTO_FUNCAO(TokenInfo *vetor);
void DECLARA_PROCEDIMENTO(TokenInfo *vetor);
void DECLARA_FUNCAO(TokenInfo *vetor);
void PARAMETROS(TokenInfo *vetor);
void DECLARA_PARAMETROS(TokenInfo *vetor);
void BLOCO_VARIAVEIS(TokenInfo *vetor);
void DECLARACOES(TokenInfo *vetor);
void DECLARACOES_ELSE(TokenInfo *vetor);
void DECLARA_TIPO(TokenInfo *vetor);
void DECLARA_VARIAVEIS(TokenInfo *vetor);
void DECLARA_IDENTIFICADOR(TokenInfo *vetor);
void DECLARA_IDENTIFICADOR_ELSE(TokenInfo *vetor);
void VETOR_MATRIZ(TokenInfo *vetor);
void DIMENSAO(TokenInfo *vetor);
void DIMENSAO_X(TokenInfo *vetor);
void TIPO_BASICO(TokenInfo *vetor);
void BLOCO_COMANDOS(TokenInfo *vetor);
void LISTA_COMANDOS(TokenInfo *vetor);
void LISTA_COMANDOS_X(TokenInfo *vetor);
void COMANDOS(TokenInfo *vetor);
void COMANDOS_X(TokenInfo *vetor);
void COMANDOS_X2(TokenInfo *vetor);
void COMANDOS_X3(TokenInfo *vetor);
void EXPRESSAO(TokenInfo *vetor);
void EXPRESSAO_X(TokenInfo *vetor);
void EXPRESSAO_SIMPLES(TokenInfo *vetor);
void EXPRESSAO_SIMPLES_X(TokenInfo *vetor);
void TERMO(TokenInfo *vetor);
void TERMO_X(TokenInfo *vetor);
void FATOR(TokenInfo *vetor);
void VARIAVEL(TokenInfo *vetor);
void EXPRITER(TokenInfo *vetor);
void EXPRITER_X(TokenInfo *vetor);

void eat(int t, TokenInfo *vetor) {
    if (vetor[token_posicao].token == t) {
        token_posicao++;
    } else if (!erro_sintatico) {
        if (token_posicao > local) {
            
            imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
            erro_sintatico = 1;
            return;
        } else {
            imprimir_erro_sintatico(vetor, token_posicao);
            erro_sintatico = 1;
            return;
        }
    }
}

void PROGRAMA(TokenInfo *vetor) {
    if(local==-1){
        
        imprimir_erro_sintatico(vetor, token_posicao);
        erro_sintatico = 1;
        return;
    }
    switch (vetor[token_posicao].token) {
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); PROGRAMA(vetor); break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); PROGRAMA(vetor); break;
        case ALGORITMO:
            eat(ALGORITMO, vetor);eat(IDENTIFICADOR, vetor);eat(PONTO_VIRGULA, vetor); BLOCO_VARIAVEIS(vetor); PROCEDIMENTO_FUNCAO(vetor); BLOCO_COMANDOS(vetor); eat(PONTO, vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            return;
    }
}

void PROCEDIMENTO_FUNCAO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case PROCEDIMENTO:
            DECLARA_PROCEDIMENTO(vetor); PROCEDIMENTO_FUNCAO(vetor); break;
        case FUNCAO:
            DECLARA_FUNCAO(vetor); PROCEDIMENTO_FUNCAO(vetor); break;
        case INICIO:
            break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); PROCEDIMENTO_FUNCAO(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); PROCEDIMENTO_FUNCAO(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DECLARA_PROCEDIMENTO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case PROCEDIMENTO:
            eat(PROCEDIMENTO, vetor); eat(IDENTIFICADOR, vetor); PARAMETROS(vetor); eat(PONTO_VIRGULA, vetor); DECLARA_PARAMETROS(vetor); BLOCO_VARIAVEIS(vetor); BLOCO_COMANDOS(vetor); eat(PONTO_VIRGULA, vetor); break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); DECLARA_PROCEDIMENTO(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); DECLARA_PROCEDIMENTO(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DECLARA_FUNCAO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case FUNCAO:
            eat(FUNCAO, vetor); eat(IDENTIFICADOR, vetor); PARAMETROS(vetor); eat(DOIS_PONTOS, vetor); TIPO_BASICO(vetor); eat(PONTO_VIRGULA, vetor); DECLARA_PARAMETROS(vetor); BLOCO_VARIAVEIS(vetor); BLOCO_COMANDOS(vetor); eat(PONTO_VIRGULA, vetor); break;
            break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); DECLARA_FUNCAO(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); DECLARA_FUNCAO(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void PARAMETROS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case ABRE_PARENTESE:
            eat(ABRE_PARENTESE, vetor); DECLARA_IDENTIFICADOR(vetor); eat(FECHA_PARENTESE, vetor); break;
        case PONTO_VIRGULA:
            break;
        case DOIS_PONTOS:
            break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); PARAMETROS(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); PARAMETROS(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DECLARA_PARAMETROS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case INTEIRO:
            DECLARACOES(vetor); break;
        case REAL:
            DECLARACOES(vetor); break;
        case CARACTERE:
            DECLARACOES(vetor); break; 
        case LOGICO:
            DECLARACOES(vetor); break;
        case IDENTIFICADOR:
            DECLARACOES(vetor); break;
        case TIPO:
            DECLARACOES(vetor); break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); DECLARA_PARAMETROS(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); DECLARA_PARAMETROS(vetor); break;
        case VARIAVEIS:
        case INICIO:
            break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void BLOCO_VARIAVEIS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case VARIAVEIS:
            eat(VARIAVEIS, vetor); DECLARACOES(vetor); break;
        case INICIO:
            break;
        case PROCEDIMENTO:
            break;
        case FUNCAO:
            break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); BLOCO_VARIAVEIS(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); BLOCO_VARIAVEIS(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DECLARACOES(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case INTEIRO:
            DECLARA_VARIAVEIS(vetor); DECLARACOES_ELSE(vetor); break;
        case REAL:
            DECLARA_VARIAVEIS(vetor); DECLARACOES_ELSE(vetor); break;
        case CARACTERE:
            DECLARA_VARIAVEIS(vetor); DECLARACOES_ELSE(vetor); break; 
        case LOGICO:
            DECLARA_VARIAVEIS(vetor); DECLARACOES_ELSE(vetor); break;
        case IDENTIFICADOR:
            DECLARA_VARIAVEIS(vetor); DECLARACOES_ELSE(vetor); break;
        case TIPO:
            DECLARA_TIPO(vetor); DECLARACOES_ELSE(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}
void DECLARACOES_ELSE(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case INTEIRO:
            DECLARACOES(vetor); break;
        case REAL:
            DECLARACOES(vetor); break;
        case CARACTERE:
            DECLARACOES(vetor); break; 
        case LOGICO:
            DECLARACOES(vetor); break;
        case IDENTIFICADOR:
            DECLARACOES(vetor); break;
        case TIPO:
            DECLARACOES(vetor); break;
        default:
            break;
    }
}

void DECLARA_TIPO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case TIPO:
            eat(TIPO, vetor); eat(IDENTIFICADOR, vetor); eat(IGUAL, vetor); VETOR_MATRIZ(vetor); eat(ABRE_COLCHETE, vetor); DIMENSAO(vetor); eat(FECHA_COLCHETE, vetor); TIPO_BASICO(vetor); eat(PONTO_VIRGULA, vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DECLARA_VARIAVEIS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case INTEIRO:
            eat(INTEIRO, vetor); eat(DOIS_PONTOS, vetor); DECLARA_IDENTIFICADOR(vetor); eat(PONTO_VIRGULA, vetor); break;
        case REAL:
            eat(REAL, vetor); eat(DOIS_PONTOS, vetor); DECLARA_IDENTIFICADOR(vetor); eat(PONTO_VIRGULA, vetor); break;
        case CARACTERE:
            eat(CARACTERE, vetor); eat(DOIS_PONTOS, vetor); DECLARA_IDENTIFICADOR(vetor); eat(PONTO_VIRGULA, vetor); break;
        case LOGICO:
            eat(LOGICO, vetor); eat(DOIS_PONTOS, vetor); DECLARA_IDENTIFICADOR(vetor); eat(PONTO_VIRGULA, vetor); break;
        case IDENTIFICADOR:
            eat(IDENTIFICADOR, vetor); eat(DOIS_PONTOS, vetor); DECLARA_IDENTIFICADOR(vetor); eat(PONTO_VIRGULA, vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DECLARA_IDENTIFICADOR(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case IDENTIFICADOR:
            eat(IDENTIFICADOR, vetor); DECLARA_IDENTIFICADOR_ELSE(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}
void DECLARA_IDENTIFICADOR_ELSE(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case VIRGULA:
            eat(VIRGULA, vetor); DECLARA_IDENTIFICADOR(vetor); break;
        default:
            break;
    }
}

void VETOR_MATRIZ(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case VETOR:
            eat(VETOR, vetor); break;
        case MATRIZ:
            eat(MATRIZ, vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DIMENSAO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case NUMERO_INTEIRO:
            eat(NUMERO_INTEIRO, vetor); eat(DOIS_PONTOS, vetor); eat(NUMERO_INTEIRO, vetor); DIMENSAO_X(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void DIMENSAO_X(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case VIRGULA:
            eat(VIRGULA, vetor); DIMENSAO(vetor); break;
        default:
            break;
    }
}

void TIPO_BASICO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case INTEIRO:
            eat(INTEIRO, vetor); break;
        case REAL:
            eat(REAL, vetor); break;
        case CARACTERE:
            eat(CARACTERE, vetor); break;
        case LOGICO:
            eat(LOGICO, vetor); break;
        case IDENTIFICADOR:
            eat(IDENTIFICADOR, vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void BLOCO_COMANDOS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case INICIO:
            eat(INICIO, vetor); LISTA_COMANDOS(vetor); eat(FIM, vetor); break;
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); BLOCO_COMANDOS(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); BLOCO_COMANDOS(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void LISTA_COMANDOS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); LISTA_COMANDOS(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); LISTA_COMANDOS(vetor); break;
        case SE:
        case IDENTIFICADOR:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            COMANDOS(vetor); eat(PONTO_VIRGULA, vetor); 
            if (vetor[token_posicao].token != FIM) { // Verifique se não estamos no fim do bloco de comandos
                LISTA_COMANDOS(vetor);
            }
            break;
        case FIM:
            
        break;
        case ATE: 
        case SENAO:
        break;
        default:
            if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void LISTA_COMANDOS_X(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case COMENTARIO_EM_BLOCO:
            eat(COMENTARIO_EM_BLOCO, vetor); LISTA_COMANDOS_X(vetor); break;
        case COMENTARIO_EM_LINHA:
            eat(COMENTARIO_EM_LINHA, vetor); LISTA_COMANDOS_X(vetor); break;
        case IDENTIFICADOR:
             break;
        default:
            break;
    }
}

void COMANDOS(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case IDENTIFICADOR:
             eat(IDENTIFICADOR, vetor);  COMANDOS_X(vetor); break;
        case SE:
            eat(SE, vetor); EXPRESSAO(vetor); eat(ENTAO, vetor); LISTA_COMANDOS(vetor); COMANDOS_X2(vetor); break;
        case ENQUANTO:
            eat(ENQUANTO, vetor); EXPRESSAO(vetor); eat(FACA, vetor); LISTA_COMANDOS(vetor); eat(FIM, vetor); eat(ENQUANTO, vetor); break;
        case PARA:
            eat(PARA, vetor); eat(IDENTIFICADOR, vetor); eat(DE, vetor); EXPRESSAO(vetor); eat(ATE, vetor); EXPRESSAO(vetor); COMANDOS_X3(vetor); break;
        case REPITA:
            eat(REPITA, vetor); LISTA_COMANDOS(vetor); eat(ATE, vetor); EXPRESSAO(vetor); break;
        case LEIA:
            eat(LEIA, vetor); eat(ABRE_PARENTESE, vetor); VARIAVEL(vetor); eat(FECHA_PARENTESE, vetor); break;
        case IMPRIMA:
            eat(IMPRIMA, vetor); eat(ABRE_PARENTESE, vetor); EXPRITER(vetor); eat(FECHA_PARENTESE, vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void COMANDOS_X(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case ABRE_PARENTESE:
            eat(ABRE_PARENTESE, vetor); EXPRITER(vetor); eat(FECHA_PARENTESE, vetor); break;
        case ABRE_COLCHETE:
            eat(ABRE_COLCHETE, vetor); EXPRITER(vetor); eat(FECHA_COLCHETE, vetor); eat(ATRIBUICAO_ESQUERDA, vetor); EXPRESSAO(vetor); break;
        case ATRIBUICAO_ESQUERDA:
            eat(ATRIBUICAO_ESQUERDA, vetor); EXPRESSAO(vetor); break;
        default:
            break;
    }
}

void COMANDOS_X2(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case FIM:
            eat(FIM, vetor); eat(SE, vetor); break;
        case SENAO:
            eat(SENAO, vetor); LISTA_COMANDOS(vetor); eat(FIM, vetor); eat(SE, vetor); break;
        default:
            break;
    }
}

void COMANDOS_X3(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case FACA:
            eat(FACA, vetor); LISTA_COMANDOS(vetor); eat(FIM, vetor); eat(PARA, vetor); break;
        case PASSO:
            eat(PASSO, vetor); EXPRESSAO(vetor); eat(FACA, vetor); LISTA_COMANDOS(vetor); eat(FIM, vetor); eat(PARA, vetor); break;
        default:
            break;
    }
}

void EXPRESSAO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case MAIS:
        case MENOS:
        case ABRE_PARENTESE:
        case NAO:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case IDENTIFICADOR:
            EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void EXPRESSAO_X(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case IGUAL:
            eat(IGUAL, vetor); EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        case DIFERENTE:
            eat(DIFERENTE, vetor); EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        case MENOR:
            eat(MENOR, vetor); EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        case MENOR_IGUAL:
            eat(MENOR_IGUAL, vetor); EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        case MAIOR_IGUAL:
            eat(MAIOR_IGUAL, vetor); EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        case MAIOR:
            eat(MAIOR, vetor); EXPRESSAO_SIMPLES(vetor); EXPRESSAO_X(vetor); break;
        default:
            break;
    }
}

void EXPRESSAO_SIMPLES(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case MAIS:
        case MENOS:
        case OU:
            EXPRESSAO_SIMPLES_X(vetor);
        break;
        case ABRE_PARENTESE:
        case NAO:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case IDENTIFICADOR:
            TERMO(vetor); EXPRESSAO_SIMPLES_X(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void EXPRESSAO_SIMPLES_X(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case MAIS:
            eat(MAIS, vetor); TERMO(vetor); EXPRESSAO_SIMPLES_X(vetor); break;
        case MENOS:
            eat(MENOS, vetor); TERMO(vetor); EXPRESSAO_SIMPLES_X(vetor); break;
        case OU:
            eat(OU, vetor); TERMO(vetor); EXPRESSAO_SIMPLES_X(vetor); break;
        case ABRE_PARENTESE:
        case NAO:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case VERDADEIRO:
        case FALSO:
        case STRING:
            TERMO(vetor); EXPRESSAO_SIMPLES_X(vetor); break;
        default:
            
            break;
    }
}

void TERMO(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case ABRE_PARENTESE:
        case NAO:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case IDENTIFICADOR:
            FATOR(vetor); TERMO_X(vetor); break;
        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao);//se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void TERMO_X(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case MULTIPLICACAO:
            eat(MULTIPLICACAO, vetor); FATOR(vetor); TERMO_X(vetor); break;
        case DIVISAO:
            eat(DIVISAO, vetor); FATOR(vetor); TERMO_X(vetor); break;
        case DIV:
            eat(DIV, vetor); FATOR(vetor); TERMO_X(vetor); break;
        case E:
            eat(E, vetor); FATOR(vetor); TERMO_X(vetor); break;
        case MENOS:
        case MAIS:
            break;     
        default:
            
            break;
    }
}

void FATOR(TokenInfo *vetor) {
    int verifica;
    switch (vetor[token_posicao].token) {
        case ABRE_PARENTESE:
            eat(ABRE_PARENTESE, vetor); EXPRESSAO(vetor); eat(FECHA_PARENTESE, vetor); break;
        case NAO:
            eat(NAO, vetor); FATOR(vetor); break;
        case NUMERO_INTEIRO:
            eat(NUMERO_INTEIRO, vetor); break;
        case NUMERO_REAL:
            eat(NUMERO_REAL, vetor); break;
        case VERDADEIRO:
            eat(VERDADEIRO, vetor); break;
        case FALSO:
            eat(FALSO, vetor); break;
        case STRING:
            eat(STRING, vetor); break;
        case IDENTIFICADOR:
            verifica = token_posicao + 1;
            if(vetor[verifica].token==ABRE_PARENTESE){
                eat(IDENTIFICADOR, vetor); eat(ABRE_PARENTESE, vetor); EXPRITER(vetor); eat(FECHA_PARENTESE, vetor);
            }else if(vetor[verifica].token== ABRE_COLCHETE){
                VARIAVEL(vetor);
            }else{
                VARIAVEL(vetor);
            } break;

        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void VARIAVEL(TokenInfo *vetor) {
    int verifica;
    switch (vetor[token_posicao].token) {
        case IDENTIFICADOR:
            verifica = token_posicao + 1;
            if(vetor[verifica].token==ABRE_COLCHETE){
                eat(IDENTIFICADOR, vetor); eat(ABRE_COLCHETE, vetor); EXPRITER(vetor); eat(FECHA_COLCHETE, vetor);
            }else{
                eat(IDENTIFICADOR, vetor);
            } break;

        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void EXPRITER(TokenInfo *vetor) {
    switch (vetor[token_posicao].token) {
        case MAIS:
        case MENOS:
        case ABRE_PARENTESE:
        case NAO:
        case NUMERO_INTEIRO:
        case NUMERO_REAL:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case IDENTIFICADOR:
            EXPRESSAO(vetor); EXPRITER_X(vetor); break;

        default:
            if (token_posicao > local) {
                if (!erro_sintatico) {
                    imprimir_erro_sintatico(vetor, token_posicao); //se a cadeia for encerrada de maneira incompleta, esta mensagem eh impressa
                    erro_sintatico = 1;
                }
            } else if (!erro_sintatico) {
                imprimir_erro_sintatico(vetor, token_posicao);
                erro_sintatico = 1;
            }
            break;
    }
}

void EXPRITER_X(TokenInfo *vetor){
    switch (vetor[token_posicao].token) {
        case VIRGULA:
            eat(VIRGULA, vetor); EXPRITER(vetor); break;     
        default:
            
            break;
    }
}

// ===== FIM SINTATICO =====
// ============================

int main() {
    char *string = NULL;
    size_t length = 0;
    int read;
    primeira_linha = 1;
    int erro_lexico;
    int linha = 0;
    int i, j;
    //Alocacao dinamica para o vetor de inteiros
    int vetor_capacidade = 300;
    TokenInfo *vetor = (TokenInfo *)malloc(vetor_capacidade * sizeof(TokenInfo));
    if (vetor == NULL) {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&string, &length, stdin)) != -1) {
        linha++;
        //Reseta estados
        token_posicao = 0;
        erro_sintatico = 0;
        erro_lexico = 0;
        
        i = 0;


        // ===== ANALISADOR LEXICO =====
        //Aqui a cadeia lida eh Tokenizada
        while (string[i] != '\0' && string[i] != '\n') {
            j = 0;
            if(strncasecmp(&string[i], "algoritmo", 9) == 0) {
                i += 9;
                armazenar_token(vetor, ALGORITMO, linha, (i+1));
            }else if (strncasecmp(&string[i], "inicio", 6) == 0) {
                
                armazenar_token(vetor, INICIO, linha, (i+1));
                i += 6;
            }else if (strncasecmp(&string[i], "fim", 3) == 0) {
                armazenar_token(vetor, FIM, linha, (i+1));
                i += 3;
            }else if (strncasecmp(&string[i], "variaveis", 9) == 0) {
                armazenar_token(vetor, VARIAVEIS, linha, (i+1));
                i += 9;
            }else if (strncasecmp(&string[i], "inteiro", 7) == 0) {
                armazenar_token(vetor, INTEIRO, linha, (i+1));
                i += 7;
            }else if (strncasecmp(&string[i], "real", 4) == 0) {
                armazenar_token(vetor, REAL, linha, (i+1));
                i += 4;
            }else if (strncasecmp(&string[i], "caractere", 9) == 0) {
                armazenar_token(vetor, CARACTERE, linha, (i+1));
                i += 9;
            }else if (strncasecmp(&string[i], "logico", 6) == 0) {
                armazenar_token(vetor, LOGICO, linha, (i+1));
                i += 6;
            }else if (strncasecmp(&string[i], "tipo", 4) == 0) {
                armazenar_token(vetor, TIPO, linha, (i+1));
                i += 4;
            }else if (strncasecmp(&string[i], "funcao", 6) == 0) {
               armazenar_token(vetor, FUNCAO, linha, (i+1));
               i += 6;
            } else if (strncasecmp(&string[i], "procedimento", 12) == 0) {
               armazenar_token(vetor, PROCEDIMENTO, linha, (i+1));
               i += 12;
            }  else if (strncasecmp(&string[i], "entao", 5) == 0) {
               armazenar_token(vetor, ENTAO, linha, (i+1));
               i += 5;
            } else if (strncasecmp(&string[i], "senao", 5) == 0) {
               armazenar_token(vetor, SENAO, linha, (i+1));
               i += 5;
            } else if (strncasecmp(&string[i], "enquanto", 8) == 0) {
               armazenar_token(vetor, ENQUANTO, linha, (i+1));
               i += 8;
            } else if (strncasecmp(&string[i], "faca", 4) == 0) {
               armazenar_token(vetor, FACA, linha, (i+1));
               i += 4;
            } else if (strncasecmp(&string[i], "para", 4) == 0) {
               armazenar_token(vetor, PARA, linha, (i+1));
               i += 4;
            } else if (strncasecmp(&string[i], "de", 2) == 0) {
               armazenar_token(vetor, DE, linha, (i+1));
               i += 2;
            } else if (strncasecmp(&string[i], "ate", 3) == 0) {
               armazenar_token(vetor, ATE, linha, (i+1));
               i += 3;
            } else if (strncasecmp(&string[i], "passo", 5) == 0) {
               armazenar_token(vetor, PASSO, linha, (i+1));
               i += 5;
            } else if (strncasecmp(&string[i], "repita", 6) == 0) {
               armazenar_token(vetor, REPITA, linha, (i+1));
               i += 6;
            } else if (strncasecmp(&string[i], "leia", 4) == 0) {
               armazenar_token(vetor, LEIA, linha, (i+1));
               i += 4;
            } else if (strncasecmp(&string[i], "imprima", 7) == 0) {
               armazenar_token(vetor, IMPRIMA, linha, (i+1));
               i += 7;
            } else if (strncasecmp(&string[i], "verdadeiro", 10) == 0) {
               armazenar_token(vetor, VERDADEIRO, linha, (i+1));
               i += 10;
            } else if (strncasecmp(&string[i], "falso", 5) == 0) {
               armazenar_token(vetor, FALSO, linha, (i+1));
               i += 5;
            } else if (strncasecmp(&string[i], "e", 1) == 0) {
               armazenar_token(vetor, E, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "ou", 2) == 0) {
               armazenar_token(vetor, OU, linha, (i+1));
               i += 2;
            } else if (strncasecmp(&string[i], "nao", 3) == 0) {
               armazenar_token(vetor, NAO, linha, (i+1));
               i += 3;
            } else if (strncasecmp(&string[i], "div", 3) == 0) {
               armazenar_token(vetor, DIV, linha, (i+1));
               i += 3;
            }  else if (strncasecmp(&string[i], ";", 1) == 0) {
               armazenar_token(vetor, PONTO_VIRGULA, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], ",", 1) == 0) {
               armazenar_token(vetor, VIRGULA, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], ":", 1) == 0) {
               armazenar_token(vetor, DOIS_PONTOS, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], ".", 1) == 0) {
               armazenar_token(vetor, PONTO, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "[", 1) == 0) {
               armazenar_token(vetor, ABRE_COLCHETE, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "]", 1) == 0) {
               armazenar_token(vetor, FECHA_COLCHETE, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "(", 1) == 0) {
               armazenar_token(vetor, ABRE_PARENTESE, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], ")", 1) == 0) {
               armazenar_token(vetor, FECHA_PARENTESE, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "=", 1) == 0) {
               armazenar_token(vetor, IGUAL, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "<>", 2) == 0) {
               armazenar_token(vetor, DIFERENTE, linha, (i+1));
               i += 2;
            } else if (strncasecmp(&string[i], ">=", 2) == 0) {
               armazenar_token(vetor, MAIOR_IGUAL, linha, (i+1));
               i += 2;
            } else if (strncasecmp(&string[i], "<=", 2) == 0) {
               armazenar_token(vetor, MENOR_IGUAL, linha, (i+1));
               i += 2;
            } else if (strncasecmp(&string[i], "<-", 2) == 0) {
               armazenar_token(vetor, ATRIBUICAO_ESQUERDA, linha, (i+1));
               i += 2;
            } else if (strncasecmp(&string[i], ">", 1) == 0) {
               armazenar_token(vetor, MAIOR, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "<", 1) == 0) {
               armazenar_token(vetor, MENOR, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "+", 1) == 0) {
               armazenar_token(vetor, MAIS, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "-", 1) == 0) {
               armazenar_token(vetor, MENOS, linha, (i+1));
               i += 1;
            } else if (strncasecmp(&string[i], "*", 1) == 0) {
               armazenar_token(vetor, MULTIPLICACAO, linha, (i+1));
               i += 1;
            }else if(string[i]=='/' && string[i+1]=='/'){// reconhecimento de comentarios de linha
                i+=1; //add dois por conta das duas barras
                //armazenar_token(vetor, COMENTARIO_EM_LINHA, linha, (i+1));
                while (string[i] != '\n') {
                    i++;
                }
                i++;
            } else if (strncasecmp(&string[i], "/", 1) == 0) { // o reconhecimento da divisao deve ser abaixo do comentario de linha por questoes de precedencia
               armazenar_token(vetor, DIVISAO, linha, (i+1));
               i += 1;
            }else if((strncmp(&string[i], " ", 1) == 0)||(strncmp(&string[i], "\n", 1) == 0)||(strncmp(&string[i], "\r", 1) == 0)||(strncmp(&string[i], "\0", 1) == 0)){
                i++; //Para ignorar espacos e quebra de linha
            } else if ((strncasecmp(&string[i], "matriz", 6) == 0) && (string[i+6]=='[')) {
                armazenar_token(vetor, MATRIZ, linha, (i+1));
                i += 6;
            } else if ((strncasecmp(&string[i], "vetor", 5) == 0) && (string[i+5]=='[')) {
                armazenar_token(vetor, VETOR, linha, (i+1));
                i += 5;
            } else if ((strncasecmp(&string[i], "se", 2) == 0) && (string[i+2]==' ' || string[i+2]==';'||string[i+2]=='(')) {
               armazenar_token(vetor, SE, linha, (i+1));
               i += 2;
            }else if ((string[i] >= 'a' && string[i] <= 'z')||(string[i] >= 'A' && string[i] <= 'Z')||(string[i]=='_')) {//[a-zA-Z_][a-zA-Z0-9_]*
                while ((string[i] >= 'a' && string[i] <= 'z')||(string[i] >= 'A' && string[i] <= 'Z')||(string[i]=='_')||(string[i] >= '0' && string[i] <= '9')) {
                    vetor[local].palavra[j] = string[i]; //aqui armazeno o identificador para ser impresso em um possivel erro sintatico
                    j++;
                    i++;
                }
                armazenar_token(vetor, IDENTIFICADOR, linha, (i));
               // printf("Identificador\n");
            }else if(string[i] >= '0' && string[i] <= '9'){//[0-9]+
                armazenar_token(vetor, NUMERO_INTEIRO, linha, (i+1));
                while (string[i] >= '0' && string[i] <= '9') {
                    i++;
                }
                if(string[i]=='.'){ //[0-9]+.[0-9]*
                    armazenar_token(vetor, NUMERO_REAL, linha, (i+1));
                    //printf("Numero real\n");
                    i++;
                    while (string[i] >= '0' && string[i] <= '9') {
                        i++;
                    }
                }
            }else if(string[i]=='"'){// token string "texto"
                i++;
                while ((string[i] >= 32 && string[i] <= 33)||(string[i] >= 35 && string[i] <= 126)) {
                    i++;
                }
                if(string[i]=='"'){
                    //printf("string\n");
                }else{
                    printf("ERRO LEXICO. Linha: %d Coluna: %d -> '%c'", linha, i+1, string[i]);
                    return 0;
                }
                i++; //precisa desse i++ para não detectar o fechamento da string como uma nova string
                armazenar_token(vetor, STRING, linha, (i+1));
            }else if (string[i] == '{') {  // Reconhecimento de comentário em bloco
                i++;  // Avanca para o proximo caractere depois de '{'

                while (1) {  // Loop infinito até encontrar o '}' que fecha o comentário
                    // Se chegar ao final da string atual, ler uma nova linha
                    if (string[i] == '\n') {
                        getline(&string, &length, stdin);  // Lê a próxima linha
                        linha++;
                        i = 0;  // Reinicia o índice 'i' para a nova linha
                    }

                    // Se encontrar o '}' que fecha o comentário
                    if (string[i] == '}') {
                        //printf("comentário em bloco\n");
                        i++;  // Avança após '}'
                        break;  // Sai do loop, comentário fechado
                    }
                    // Avanca para o proximo caractere
                    i++;
                    if(string[i]=='\0'){ //isso aqui é para caso um comentario em bloco nao tenha sido finalizado corretamente
                        return 0;
                    }  
                }
                //armazenar_token(vetor, COMENTARIO_EM_BLOCO, linha, (i+1));
            }else {
                printf("ERRO LEXICO. Linha: %d Coluna: %d -> '%c'", linha, i+1, string[i]);
                erro_lexico = 1;
                return 0; 
            }
             
            // ===== FIM ANALISADOR LEXICO
            
            //Se necessario, Aqui eh aumentada a capacidade do vetor
            if (local >= vetor_capacidade) {
                vetor_capacidade *= 2; // Dobre a capacidade
                TokenInfo *temp = realloc(vetor, vetor_capacidade * sizeof(TokenInfo));
                if (temp == NULL) {
                    perror("Erro ao realocar memoria");
                    free(vetor); // Libere a memória previamente alocada
                    exit(EXIT_FAILURE);
                }
                vetor = temp; // Atualize o ponteiro
            }
            
        }
    }
    if(!erro_lexico){
            PROGRAMA(vetor); //Chama o analisador sintatico

            if (!erro_sintatico) {
                printf("PROGRAMA CORRETO.");
                primeira_linha = 0;
            }
    }
    //Libera a memoria usada para a string
    free(string);
    
    return 0;
}