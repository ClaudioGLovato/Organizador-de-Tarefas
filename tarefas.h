#ifndef TAREFAS_H
#define TAREFAS_H

#include <time.h>

#define TAM_TITULO 100
#define TAM_DESCRICAO 256

typedef enum {
    STATUS_PENDENTE = 0,
    STATUS_CONCLUIDA = 1
} StatusTarefa;

typedef struct {
    int id;
    char titulo[TAM_TITULO];
    char descricao[TAM_DESCRICAO];
    time_t prazo;
    int dificuldade;        // de 1 a 5
    StatusTarefa status;
} Tarefa;

typedef struct ListaTarefas ListaTarefas;
typedef struct No No;

// Criar e destruir
ListaTarefas *criar_lista(void);
void destruir_lista(ListaTarefas *lista);

// Inserir
int inserir_fim(ListaTarefas *lista, Tarefa t);

// Remover pela posição (0 = primeiro).
int remover_posicao(ListaTarefas *lista, int posicao);

// Consultar
No *buscar(ListaTarefas *lista, int id);    
int tamanho_lista(ListaTarefas *lista);
void imprimir_lista(ListaTarefas *lista);

// Percorrer a lista e mexer na tarefa
No *primeiro_no(ListaTarefas *lista);
No *proximo_no(No *no);
Tarefa *dados_tarefa(No *no);

// Escreve a data no formato dd/mm/aaaa hh:mm
void formatar_data(time_t t, char *buffer, int tam);

#endif
