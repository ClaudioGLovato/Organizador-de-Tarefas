#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H

#include "tarefas.h"

// Remove a tarefa com o ID informado. Retorna 1 se removeu, 0 se não achou.
int remover_tarefa_por_id(ListaTarefas *lista, int id);

// Marca a tarefa com o ID informado como concluída. Retorna 1 se achou, 0 se não.
int marcar_como_feita(ListaTarefas *lista, int id);

// Ordena pelo prazo, do mais próximo para o mais distante.
void ordenar_por_urgencia(ListaTarefas *lista);

// Ordena pela dificuldade, de 1 até 5.
void ordenar_por_dificuldade(ListaTarefas *lista);

#endif
