# Nome do executável
EXEC = programa

# Lista de arquivos-fonte
SRC = portugol.c

# Lista de arquivos objeto gerados após a compilação dos arquivos fonte
OBJ = $(SRC:.c=.o)

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Regra padrão
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados pela compilação
clean:
	rm -f $(OBJ) $(EXEC)

# Regra para rodar o programa
run: $(EXEC)
	./$(EXEC)

