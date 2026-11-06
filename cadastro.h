#ifndef CADASTRO_H
#define CADASTRO_H

#include "tarefas.h"

// Pergunta os dados ao usuário e cadastra uma nova tarefa
void cadastrar_tarefa(ListaTarefas *lista);

// Pede o ID e deixa o usuário alterar os dados da tarefa (Enter = manter)
void editar_tarefa(ListaTarefas *lista);

#endif
