#include <stdio.h>
#include <stdlib.h>
#include "tarefas.h"

struct No {
    Tarefa dado;
    struct No *prox;
};

struct ListaTarefas {
    No *inicio;
    int tamanho;
    int proximo_id;
};

ListaTarefas *criar_lista(void) {
    ListaTarefas *lista = malloc(sizeof(ListaTarefas));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->tamanho = 0;
        lista->proximo_id = 1;
    }
    return lista;
}

void destruir_lista(ListaTarefas *lista) {
    if (lista == NULL) return;

    No *atual = lista->inicio;
    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int inserir_fim(ListaTarefas *lista, Tarefa t) {
    if (lista == NULL) return 0;

    No *novo = malloc(sizeof(No));
    if (novo == NULL) return 0;

    t.id = lista->proximo_id;
    lista->proximo_id++;
    novo->dado = t;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No *ultimo = lista->inicio;
        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo;
    }
    lista->tamanho++;
    return t.id;
}

int remover_posicao(ListaTarefas *lista, int posicao) {
    if (lista == NULL) return 0;
    if (posicao < 0 || posicao >= lista->tamanho) return 0;

    No *alvo;
    if (posicao == 0) {
        alvo = lista->inicio;
        lista->inicio = alvo->prox;
    } else {
        No *anterior = lista->inicio;
        for (int i = 0; i < posicao - 1; i++) {
            anterior = anterior->prox;
        }
        alvo = anterior->prox;
        anterior->prox = alvo->prox;
    }

    free(alvo);
    lista->tamanho--;
    return 1;
}

No *buscar(ListaTarefas *lista, int id) {
    if (lista == NULL) return NULL;

    for (No *no = lista->inicio; no != NULL; no = no->prox) {
        if (no->dado.id == id) return no;
    }
    return NULL;
}

int tamanho_lista(ListaTarefas *lista) {
    return lista != NULL ? lista->tamanho : 0;
}

No *primeiro_no(ListaTarefas *lista) {
    return lista != NULL ? lista->inicio : NULL;
}

No *proximo_no(No *no) {
    return no != NULL ? no->prox : NULL;
}

Tarefa *dados_tarefa(No *no) {
    return no != NULL ? &no->dado : NULL;
}

void formatar_data(time_t t, char *buffer, int tam) {
    struct tm *info = localtime(&t);
    if (buffer == NULL || tam <= 0) return;
    if (info == NULL) {
        buffer[0] = '\0';
        return;
    }
    strftime(buffer, tam, "%d/%m/%Y %H:%M", info);
}

void imprimir_lista(ListaTarefas *lista) {
    char data[20];

    if (lista == NULL || lista->inicio == NULL) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    for (No *no = lista->inicio; no != NULL; no = no->prox) {
        Tarefa *t = &no->dado;
        formatar_data(t->prazo, data, sizeof data);
        printf("[%d] %s | %s | dif: %d | %s\n    %s\n", 
        t->id, t->titulo, data, t->dificuldade, t->status == STATUS_CONCLUIDA ? "Concluída" : "Pendente",t->descricao);
    }
}
