<h1>📝 Sobre o trabalho </h1>
Utilizou-se a ferramenta Bison para a implementação de um analisador sintático para um <strong>subconjunto</strong> da linguagem C
determinados nas especificações dadas pelo professor. Para a análise léxica, utilizou-se o analisador léxico
desenvolvido em Flex na etapa anterior do compilador (presente <a href="https://github.com/BrunoViola/compiladores-1/tree/main/analisador-lexico-04">aqui</a>), 
realizando-se as devidas adequações para que o mesmo fosse utilizado pelo parser gerado pelo Bison.
Neste ponto do trabalho, o compilador é capaz de reconhecer erros léxicos e sintáticos, sendo que
agora o processo de compilação termina quando o primeiro erro (léxico ou sintático) é encontrado.
Quando um erro léxico é detectado, mostra-se a linha e a coluna onde o erro ocorreu.
<br><br>

<h1>📄 Conteúdo</h1>

- `Makefile`: O Makefile nos ajuda a compilar o programa com maior praticidade.
- `entrada.c`: Este arquivo .C contém um exemplo de entrada que poderemos usar para rodar o programa.
- `lexer.l`: Arquivo Flex com as definições, regras e código auxiliar em C do analisador léxico.
- `sintatico.y`: Arquivo Bison com as definições, regras e código auxiliar em C do que compõe a geração do analisador sintático.
<br><br>

<h1>⚙️ Como testar o programa</h1>
1. Execute o comando 'make' na pasta com os quatro arquivos a partir do cmd.<br>
2. Execute o comando './sintatico < entrada.c'.
<br><br>

<h1>👀 Observação</h1>
- O End of Line Sequence do arquivo .txt deve ser LF e não o CRLF.
