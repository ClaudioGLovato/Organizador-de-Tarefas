#include "gerenciamento.h"

#define POR_PRAZO 1
#define POR_DIFICULDADE 2

int remover_tarefa_por_id(ListaTarefas *lista, int id) {
    int posicao = 0;

   
    for (No *no = primeiro_no(lista); no != NULL; no = proximo_no(no)) {
        if (dados_tarefa(no)->id == id) {
            return remover_posicao(lista, posicao);
        }
        posicao++;
    }
    return 0;  
}

int marcar_como_feita(ListaTarefas *lista, int id) {
    No *no = buscar(lista, id);
    if (no == NULL) return 0;

    dados_tarefa(no)->status = STATUS_CONCLUIDA;
    return 1;
}


static int deve_trocar(Tarefa *a, Tarefa *b, int criterio) {
    if (criterio == POR_PRAZO) return a->prazo > b->prazo;
    return a->dificuldade > b->dificuldade;
}

// Bubble Sort: 
static void ordenar(ListaTarefas *lista, int criterio) {
    int n = tamanho_lista(lista);

    for (int i = 0; i < n - 1; i++) {
        No *atual = primeiro_no(lista);

        for (int j = 0; j < n - 1 - i; j++) {
            No *proximo = proximo_no(atual);

            if (deve_trocar(dados_tarefa(atual), dados_tarefa(proximo), criterio)) {
                Tarefa auxiliar = *dados_tarefa(atual);
                *dados_tarefa(atual) = *dados_tarefa(proximo);
                *dados_tarefa(proximo) = auxiliar;
            }
            atual = proximo;
        }
    }
}

void ordenar_por_urgencia(ListaTarefas *lista) {
    ordenar(lista, POR_PRAZO);
}

void ordenar_por_dificuldade(ListaTarefas *lista) {
    ordenar(lista, POR_DIFICULDADE);
}
