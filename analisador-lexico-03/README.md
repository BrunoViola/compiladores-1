## 📝 Sobre o exercício
<p align="justify"> 
  Neste problema, também escrevi um arquivo .l e, com a ferramenta Flex, gerei um analisador léxico que aceita as cadeias geradas pelas expressões regulares a seguir, as quais estão apresentadas em ordem de prioridade(da maior para a menor):
&nbsp;(aba)+ (action1)
&nbsp;(a(b∗)a) (action2)
&nbsp;(a|b) (action3)
</p>

<p align="justify"> 
    O programa lê a partir da entrada padrão e imprime um token por linha, chegando ao fim ao encontrar o símbolo de fim de arquivo. Para caracteres que não façam parte do alfabeto, o programa imprime a mensagem 'error'. Quebras de linha que não estão associadas ao token 'comment' são ignoradas.</br></br>


  Exemplo de entrada:
  
      abaabbaba

</p>   
<p>
    Sua respectiva saída:
  
      aba (action 1)
      abba (action 2)
      b (action 3)
      a (action 3)
</p>

## 📄 Conteúdo
- `analisador-03.l`: Arquivo Flex com as definições, regras e código auxiliar em C.
- `Makefile`: O Makefile nos ajuda a compilar o programa com maior praticidade.
- `entrada-exemplo.txt`: Este txt contém um exemplo de entrada que poderemos usar para rodar o programa.

## ⚙️ Como testar o programa
1. Execute o comando 'make' na pasta com os três arquivos a partir do cmd.
2. Um programa.exe será gerado automaticamente, portanto execute o comando 'programa.exe < entrada-exemplo.txt'
