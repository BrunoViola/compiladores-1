# Nome do arquivo fonte .l
LEXFILE = analisador-02.l

# Nome do arquivo objeto gerado
LEXOBJ = lex.yy.c

# Nome do executável final
EXEC = programa

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -o

# Regra principal
all: $(EXEC)

# Regra para gerar o arquivo lex.yy.c a partir do arquivo .l
$(LEXOBJ): $(LEXFILE)
	flex $(LEXFILE)

# Regra para compilar o lex.yy.c e gerar o executável
$(EXEC): $(LEXOBJ)
	$(CC) $(LEXOBJ) $(CFLAGS) $(EXEC)

# Limpeza dos arquivos gerados
clean:
	rm -f $(LEXOBJ) $(EXEC)
