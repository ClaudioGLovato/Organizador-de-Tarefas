#include <stdio.h>
#include <time.h>
#include "tarefas.h"
#include "entrada.h"
#include "cadastro.h"
#include "gerenciamento.h"

static int carregar_tarefas_exemplo(ListaTarefas *lista) {
    time_t agora = time(NULL);
    if (agora == (time_t)-1) {
        fprintf(stderr, "Erro ao obter a data e hora atuais.\n");
        return 0;
    }

    Tarefa exemplos[] = {
        {
            .titulo = "Estudar linguagem C",
            .descricao = "Revisar listas encadeadas e ponteiros",
            .prazo = agora + 24 * 60 * 60,
            .dificuldade = 3,
            .status = STATUS_PENDENTE
        },
        {
            .titulo = "Finalizar trabalho",
            .descricao = "Revisar e entregar o trabalho da faculdade",
            .prazo = agora + 3 * 24 * 60 * 60,
            .dificuldade = 5,
            .status = STATUS_PENDENTE
        },
        {
            .titulo = "Organizar materiais",
            .descricao = "Separar arquivos e anotacoes",
            .prazo = agora + 7 * 24 * 60 * 60,
            .dificuldade = 1,
            .status = STATUS_PENDENTE
        }
    };

    int quantidade = (int)(sizeof exemplos / sizeof exemplos[0]);
    for (int i = 0; i < quantidade; i++) {
        if (inserir_fim(lista, exemplos[i]) == 0) {
            fprintf(stderr, "Erro ao inserir tarefa de exemplo.\n");
            return 0;
        }
    }

    return 1;
}

static void mostrar_menu(void) {
    printf("\n===== Organizador de Tarefas =====\n");
    printf("1 - Cadastrar tarefa\n");
    printf("2 - Listar tarefas\n");
    printf("3 - Editar tarefa\n");
    printf("4 - Marcar tarefa como feita\n");
    printf("5 - Remover tarefa\n");
    printf("6 - Ordenar por prazo (mais urgente primeiro)\n");
    printf("7 - Ordenar por dificuldade\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

static void aguardar_enter(void) {
    char linha[2];
    printf("\nPressione Enter para continuar...");
    ler_texto(linha, sizeof linha);
}

int main(void) {
    ListaTarefas *lista = criar_lista();
    int opcao, id;

    if (lista == NULL) {
        printf("Erro ao criar a lista.\n");
        return 1;
    }
    if (!carregar_tarefas_exemplo(lista)) {
        destruir_lista(lista);
        return 1;
    }

    do {
        mostrar_menu();
        opcao = ler_inteiro();

        switch (opcao) {
            case 1:
                cadastrar_tarefa(lista);
                break;
            case 2:
                imprimir_lista(lista);
                aguardar_enter();
                break;
            case 3:
                editar_tarefa(lista);
                break;
            case 4:
                printf("ID da tarefa concluída: ");
                id = ler_inteiro();
                if (marcar_como_feita(lista, id)) printf("Tarefa marcada como feita!\n");
                else printf("Tarefa não encontrada.\n");
                break;
            case 5:
                printf("ID da tarefa a remover: ");
                id = ler_inteiro();
                if (remover_tarefa_por_id(lista, id)) printf("Tarefa removida!\n");
                else printf("Tarefa não encontrada.\n");
                break;
            case 6:
                ordenar_por_urgencia(lista);
                printf("Lista ordenada por prazo:\n");
                imprimir_lista(lista);
                aguardar_enter();
                break;
            case 7:
                ordenar_por_dificuldade(lista);
                printf("Lista ordenada por dificuldade:\n");
                imprimir_lista(lista);
                aguardar_enter();
                break;
            case 0:
                printf("Até mais!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    destruir_lista(lista);
    return 0;
}
