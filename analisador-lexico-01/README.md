## 📝 Sobre o exercício
<p align="justify"> 
  Neste problema, escrevi um arquivo .l e, com a ferramenta Flex, pude gerar um analisador léxico que reconhece o seguinte autômato:
</p>
<p align="center">
  <img src="imagem/automato.png" width="500px;" alt="Imagem Autômato" />
</p>

<p align="justify"> 
  O programa lê a partir da entrada padrão e imprime um token por linha, chegando ao fim ao encontrar o símbolo de fim de arquivo. Para caracteres que não façam parte do alfabeto, o programa imprime a mensagem ERRO. Quebras de linha são ignoradas.</br></br>


  Exemplo de entrada:
    
      +-abcabc@ abc
      fgh

</p>   
<p>
    Sua respectiva saída:
  
      +
      abcabc
      ERRO
      ERRO
      abc
      fgh
</p>

## 📄 Conteúdo

- `analisador-01.l`: Arquivo Flex com as definições, regras e código auxiliar em C.
- `Makefile`: O Makefile nos ajuda a compilar o programa com maior praticidade.
- `entrada-exemplo.txt`: Este txt contém um exemplo de entrada que poderemos usar para rodar o programa.

## ⚙️ Como testar o programa
1. Execute o comando 'make' na pasta com os três arquivos a partir do cmd.
2. Um programa.exe será gerado automaticamente, portanto execute o comando 'programa.exe < entrada-exemplo.txt'
