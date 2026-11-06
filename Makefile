CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic

BUILD_DIR = build
FONTES = main.c tarefas.c entrada.c cadastro.c gerenciamento.c
OBJETOS = $(FONTES:%.c=$(BUILD_DIR)/%.o)
HEADERS = tarefas.h entrada.h cadastro.h gerenciamento.h
EXECUTAVEL = $(BUILD_DIR)/listador_tarefas

all: $(EXECUTAVEL)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTAVEL): $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $(OBJETOS)

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

clean:
	rm -rf $(BUILD_DIR)
	rm -f main.o tarefas.o entrada.o cadastro.o gerenciamento.o frente3.o listador_tarefas
	rm -f frente2_cadastro/testes/main_integ.o frente2_cadastro/testes/teste_frente1.o
	rm -f frente2_cadastro/testes/teste_modificacao.o

.PHONY: all run clean
