## 📝 Sobre o exercício
<p align="justify"> 
  Neste exercício, escrevi um arquivo .c com o intuito de implementar um analisador descendente recursivo para a seguinte gramática:
  Exemplo de entrada:
  
      S -> if E then S else S
      S -> begin S L
      S -> print E
      L -> end
      L -> ; S L
      E -> num = num
</p>

<p align="justify"> 
  O programa lê a partir da entrada padrão e chega ao fim ao encontrar o símbolo de fim de arquivo. 
  O objetivo do programa é imprimir "CADEIA ACEITA" para aquelas cadeias que não possuam erros sintáticos e informar erros sintáticos ao usuário, sendo dois exemplos:
   ERRO SINTATICO: CADEIA INCOMPLETA ou ERRO SINTATICO EM: = ESPERADO: if, begin, print.
</br></br>
</p>   

## 📄 Conteúdo

- `LISTA_I_EXERCICIO_1.c`: implementação do analisador léxico e sintático em C.
- `Makefile`: O Makefile nos ajuda a compilar o programa com maior praticidade.
- `entrada.txt`: Este txt contém um exemplo de entrada que poderemos usar para rodar o programa.
- `saida.txt`: Este txt contém a saída do txt de entrada exemplo.

## ⚙️ Como testar o programa
1. Execute o comando 'make' na pasta com os três arquivos a partir do cmd.
2. Um programa.exe será gerado automaticamente, portanto execute o comando 'programa.exe < entrada.txt'
