#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "cadastro.h"
#include "entrada.h"

#define DIFICULDADE_MIN 1
#define DIFICULDADE_MAX 5
#define LIMITE_PRAZO (30 * 24 * 60 * 60)    // 30 dias, em segundos

/*
 * As funções pedir_... servem para o cadastro e para a edição.
 * Quando editando = 1, apertar Enter mantém o valor que já estava.
 * Elas repetem a pergunta até o usuário digitar algo válido.
 */

// O título é válido se tiver pelo menos um caractere que não seja espaço
static int titulo_valido(const char *titulo) {
    for (int i = 0; titulo[i] != '\0'; i++) {
        if (!isspace((unsigned char)titulo[i])) return 1;
    }
    return 0;
}

static void pedir_titulo(char *titulo, int editando) {
    char texto[TAM_TITULO];

    while (1) {
        if (editando) printf("Novo título (Enter = manter): ");
        else          printf("Título: ");
        ler_texto(texto, sizeof texto);

        if (editando && texto[0] == '\0') return;
        if (titulo_valido(texto)) {
            strcpy(titulo, texto);
            return;
        }
        printf("  O título não pode ser vazio.\n");
    }
}

static void pedir_descricao(char *descricao, int editando) {
    char texto[TAM_DESCRICAO];

    if (editando) printf("Nova descrição (Enter = manter): ");
    else          printf("Descrição (opcional): ");
    ler_texto(texto, sizeof texto);

    // No cadastro a descrição pode ficar vazia; na edição vazio = manter
    if (!editando || texto[0] != '\0') {
        strcpy(descricao, texto);
    }
}

static void pedir_dificuldade(int *dificuldade, int editando) {
    char texto[50];
    int numero;

    while (1) {
        if (editando) printf("Nova dificuldade (%d a %d) [Enter = manter]: ", DIFICULDADE_MIN, DIFICULDADE_MAX);
        else          printf("Dificuldade (%d a %d): ", DIFICULDADE_MIN, DIFICULDADE_MAX);
        ler_texto(texto, sizeof texto);

        if (editando && texto[0] == '\0') return;

        if (!converter_texto_inteiro(texto, &numero)) {
            printf("  Digite um número inteiro.\n");
        } else if (numero < DIFICULDADE_MIN || numero > DIFICULDADE_MAX) {
            printf("  A dificuldade deve ficar entre %d e %d.\n", DIFICULDADE_MIN, DIFICULDADE_MAX);
        } else {
            *dificuldade = numero;
            return;
        }
    }
}

// Monta o time_t a partir da data digitada. Retorna 0 se a data não existe.
static int converter_data(int dia, int mes, int ano, int hora, int minuto, time_t *resultado) {
    struct tm data = {0};
    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;
    data.tm_hour = hora;
    data.tm_min = minuto;
    data.tm_isdst = -1;

    *resultado = mktime(&data);

    // O mktime corrige datas impossíveis (31/02 vira 03/03).
    // Se algum campo mudou, é porque a data digitada não existia.
    if (data.tm_mday != dia || data.tm_mon != mes - 1 || data.tm_year != ano - 1900 ||
        data.tm_hour != hora || data.tm_min != minuto) {
        return 0;
    }
    return 1;
}

static void pedir_prazo(time_t *prazo, int editando) {
    char texto[50];
    int dia, mes, ano, hora, minuto, consumidos;
    time_t data, agora;

    while (1) {
        if (editando) printf("Novo prazo (dd/mm/aaaa hh:mm) [Enter = manter]: ");
        else          printf("Prazo (dd/mm/aaaa hh:mm): ");
        ler_texto(texto, sizeof texto);

        if (editando && texto[0] == '\0') return;

        consumidos = 0;
        if (sscanf(texto, "%d/%d/%d %d:%d %n", &dia, &mes, &ano, &hora, &minuto, &consumidos) != 5 ||
            texto[consumidos] != '\0') {
            printf("  Formato inválido. Exemplo: 25/12/2026 14:30\n");
            continue;
        }
        if (!converter_data(dia, mes, ano, hora, minuto, &data)) {
            printf("  Essa data não existe.\n");
            continue;
        }

        agora = time(NULL);
        if (data < agora) {
            printf("  O prazo não pode estar no passado.\n");
        } else if (data > agora + LIMITE_PRAZO) {
            printf("  O prazo deve ser de no máximo 30 dias a partir de agora.\n");
        } else {
            *prazo = data;
            return;
        }
    }
}

void cadastrar_tarefa(ListaTarefas *lista) {
    Tarefa nova;

    printf("\n--- Cadastro de Nova Tarefa ---\n");
    pedir_titulo(nova.titulo, 0);
    pedir_descricao(nova.descricao, 0);
    pedir_dificuldade(&nova.dificuldade, 0);
    pedir_prazo(&nova.prazo, 0);
    nova.status = STATUS_PENDENTE;

    int id = inserir_fim(lista, nova);   // o id é definido dentro da lista
    if (id == 0) {
        printf("\nErro: memória insuficiente.\n");
    } else {
        printf("\nTarefa '%s' (ID: %d) cadastrada com sucesso!\n", nova.titulo, id);
    }
}

void editar_tarefa(ListaTarefas *lista) {
    char data[20];

    printf("\n--- Edição de Tarefa ---\n");
    printf("ID da tarefa a editar: ");
    int id = ler_inteiro();

    No *no = buscar(lista, id);
    if (no == NULL) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    Tarefa *t = dados_tarefa(no);
    formatar_data(t->prazo, data, sizeof data);
    printf("\nValores atuais:\n");
    printf("  Título: %s\n", t->titulo);
    printf("  Descrição: %s\n", t->descricao);
    printf("  Prazo: %s\n", data);
    printf("  Dificuldade: %d\n", t->dificuldade);
    printf("(Aperte Enter para manter o valor atual)\n\n");

    // Cada função altera direto a tarefa da lista
    pedir_titulo(t->titulo, 1);
    pedir_descricao(t->descricao, 1);
    pedir_prazo(&t->prazo, 1);
    pedir_dificuldade(&t->dificuldade, 1);

    printf("\nTarefa (ID: %d) atualizada com sucesso!\n", id);
}
