# Nome dos arquivos fonte
LEXFILE = lexer.l
YACCFILE = sintatico.y

# Nomes dos arquivos objetos gerados
LEXOBJ = lex.yy.c
YACCOBJ = sintatico.tab.c
YACCHEADER = sintatico.tab.h

# Nome do executável final
EXEC = sintatico

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -O2

# Regra principal
all: $(EXEC)

# Regra para gerar o arquivo sintatico.tab.c e o cabeçalho sintatico.tab.h a partir do arquivo .y
$(YACCOBJ) $(YACCHEADER): $(YACCFILE)
	bison -d $(YACCFILE)

# Regra para gerar o arquivo lex.yy.c a partir do arquivo .l (depende do arquivo de cabeçalho do Bison)
$(LEXOBJ): $(LEXFILE) $(YACCHEADER)
	flex $(LEXFILE)

# Regra para compilar o lex.yy.c e o sintatico.tab.c e gerar o executável
$(EXEC): $(LEXOBJ) $(YACCOBJ)
	$(CC) $(LEXOBJ) $(YACCOBJ) $(CFLAGS) -o $(EXEC)

# Limpeza dos arquivos gerados
clean:
	rm -f $(LEXOBJ) $(YACCOBJ) $(YACCHEADER) $(EXEC)
