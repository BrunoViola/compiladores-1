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

//Funcao para converter o valor do enum em uma string
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

int token_posicao = 0;
int erro_sintatico = 0;
int tamanho_maximo_tokens = 0;

void S(int *vetor);
void L(int *vetor);
void E(int *vetor);

void eat(int t, int *vetor){
        // printf("\nEM: %s : %s", tokenTypeToString(t), tokenTypeToString(vetor[token_posicao]));
         //printf("\n%d posicao %d tam", token_posicao, tamanho_maximo_tokens);
   if(vetor[token_posicao]==t){
     // printf("\ndentro");
      
      token_posicao++;
   }else if(!erro_sintatico){
      if(token_posicao > tamanho_maximo_tokens){
         printf("ERRO SINTATICO: CADEIA INCOMPLETA");
         erro_sintatico = 1;
         return;
      }else{
         printf("ERRO SINTATICO EM: %s ESPERADAO: %s", tokenTypeToString(t), tokenTypeToString(vetor[token_posicao]));
         return;
      }
      erro_sintatico = 1;
      return;
   }
}

void S(int *vetor){
   switch (vetor[token_posicao])
   {
   case IF:
      eat(IF, vetor); E(vetor); eat(THEN, vetor); S(vetor); eat(ELSE, vetor); S(vetor); break;
   case BEGIN: eat(BEGIN, vetor); S(vetor); L(vetor); break;
   case PRINT: eat(PRINT, vetor); E(vetor); break;
   
   default:
      if(!erro_sintatico) printf("ERRO SINTATICO EM: %s ESPERADO: if, begin, print", tokenTypeToString(vetor[token_posicao]));
      erro_sintatico = 1;
      return;
      break;
   }

   if(token_posicao<tamanho_maximo_tokens && !erro_sintatico){
      S(vetor);
   }

   return;
}

void L(int *vetor){
   switch (vetor[token_posicao])
   {
   case END: eat(END, vetor); break;
   case SEMI: eat(SEMI, vetor); S(vetor); L(vetor); break;
  
   default:
      if(!erro_sintatico) printf("ERRO SINTATICO EM: %s ESPERADO: end, ;", tokenTypeToString(vetor[token_posicao]));
      erro_sintatico = 1;
      break;
   }
   return;
}

void E(int *vetor){
   switch (vetor[token_posicao])
   {
   case NUM:
      eat(NUM, vetor); eat(EQ, vetor); eat(NUM, vetor); break;
   default:
      if(!erro_sintatico) printf("ERRO SINTATICO EM: %s ESPERADO: num", tokenTypeToString(vetor[token_posicao]));
      erro_sintatico = 1;
      break;
   }
   return;
}

int main(){
   char *string = NULL;
   char c;
   int length = 0;  // Inicializa length como 0, pois a string começa vazia
   int i = 0, posicao=0, vetor[100];
   int eh_num = 1;

   while(fscanf(stdin, "%c", &c) != EOF) {
      string = realloc(string, length + 1 + 1); // realoca espaço para o novo caractere + '\0'
      if (string == NULL) {
         printf("Erro ao alocar memória");
         return 1;
      }

      string[length] = c; // Armazena o caractere lido na posição correta
      length++;
   }

   // Adiciona o caractere nulo ao final da string lida
   if (string != NULL) {
     string[length] = '\0';
   }
   
   char *aux = string;

   while(aux[i] != '\0') {
      if(aux[i]=='i' && aux[i+1] == 'f'){ //reconhece o IF
         printf("IF\n");
         vetor[posicao] = 1;
         posicao++;
         i+=1;
      }else if(aux[i]=='t' && aux[i+1]=='h' && aux[i+2]=='e' && aux[i+3]=='n'){ //reconhece THEN
         printf("THEN\n");
         vetor[posicao] = 2;
         posicao++;
         i+=3;
      }else if(aux[i]=='e' && aux[i+1]=='l' && aux[i+2]=='s' && aux[i+3]=='e'){ //reconhece ELSE
         printf("ELSE\n");
         vetor[posicao] = 3;
         posicao++;
         i+=3;
      }else if(aux[i]=='b' && aux[i+1]=='e' && aux[i+2]=='g' && aux[i+3]=='i' && aux[i+4]=='n'){ //reconhece BEGIN
         printf("BEGIN\n");
         vetor[posicao] = 4;
         posicao++;
         i+=4;
      }else if(aux[i]=='e' && aux[i+1]=='n' && aux[i+2]=='d'){ //reconhece END
         printf("END\n");
         vetor[posicao] = 5;
         posicao++;
         i+=2;
      }else if(aux[i]=='p' && aux[i+1]=='r' && aux[i+2]=='i' && aux[i+3]=='n' && aux[i+4]=='t'){ //reconhece PRINT
         printf("PRINT\n");
         vetor[posicao] = 6;
         posicao++;
         i+=4;
      }else if(aux[i]==';'){ //reconhece SEMI
         printf("SEMI\n");
         vetor[posicao] = 7;
         posicao++;
      }else if((aux[i]=='+' || aux[i]=='-' || (aux[i]>=48 && aux[i]<=57))){ //reconhece NUM
         if(aux[i] == '+' || aux[i] == '-') {
            i++; // avança para o proximo caractere
            eh_num = 0; //evita que + ou - sejam reconhecidos como NUM
         }
         while(aux[i]>=48 && aux[i]<=57){
            i++;
            eh_num = 1; //confirma que estamos trantando de um numero
         }i--;
         if(eh_num){ 
            printf("NUM\n");
            vetor[posicao] = 8;
            posicao++;
         }else{
            printf("ERRO\n");
         }
      }else if(aux[i]=='='){ //reconhece EQ
         printf("EQ\n");
         vetor[posicao] = 9;
         posicao++;
      }
      i++;
   }

   //for(int i=0; i<posicao;i++) printf("%d", vetor[i]);
   printf("\n");
   tamanho_maximo_tokens = posicao-1;
   // Libera a memória alocada para a string
   free(string);
   S(vetor);
   if(!erro_sintatico) printf("CADEIA ACEITA");
   return 0;
}
