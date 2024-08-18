#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
   char *string = NULL;
   char c;
   int length = 0;  // Inicializa length como 0, pois a string começa vazia
   int i = 0, posicao=0, vetor[100];

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
   

   // Calcula o tamanho da string manualmente
   char *aux = string;

   while(aux[i] != '\0') {
      if(aux[i]=='i' && aux[i+1] == 'f'){ //reconhece o IF
         printf("IF\n");
         vetor[posicao] = 1;
         i+=1;
      }else if(aux[i]=='t' && aux[i+1]=='h' && aux[i+2]=='e' && aux[i+3]=='n'){ //reconhece THEN
         printf("THEN\n");
         vetor[posicao] = 2;
         i+=3;
      }else if(aux[i]=='e' && aux[i+1]=='l' && aux[i+2]=='s' && aux[i+3]=='e'){ //reconhece ELSE
         printf("ELSE\n");
         vetor[posicao] = 3;
         i+=3;
      }else if(aux[i]=='b' && aux[i+1]=='e' && aux[i+2]=='g' && aux[i+3]=='i' && aux[i+4]=='n'){ //reconhece BEGIN
         printf("BEGIN\n");
         vetor[posicao] = 4;
         i+=4;
      }else if(aux[i]=='e' && aux[i+1]=='n' && aux[i+2]=='d'){ //reconhece END
         printf("END\n");
         vetor[posicao] = 5;
         i+=2;
      }else if(aux[i]=='p' && aux[i+1]=='r' && aux[i+2]=='i' && aux[i+3]=='n' && aux[i+4]=='t'){ //reconhece PRINT
         printf("PRINT\n");
         vetor[posicao] = 6;
         i+=4;
      }else if(aux[i]==';'){ //reconhece SEMI
         printf("SEMI\n");
         vetor[posicao] = 7;
      }else if((aux[i]=='+' || aux[i]=='-' || (aux[i]>=48 && aux[i]<=57))){ //reconhece NUM
         while(aux[i]>=48 && aux[i]<=57){
            i++;
         }i--;
         printf("NUM\n");
         vetor[posicao] = 8;
      }else if(aux[i]=='='){ //reconhece EQ
         printf("EQ\n");
         vetor[posicao] = 9;
      }
      i++;
   }
   
   // Libera a memória alocada para a string
   free(string);

   return 0;
}
