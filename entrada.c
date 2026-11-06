#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "entrada.h"

void ler_texto(char *destino, int tamanho) {
    
    if (fgets(destino, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada. Saindo...\n");
        exit(0);
    }

    int n = strlen(destino);
    if (n > 0 && destino[n - 1] == '\n') {
        destino[n - 1] = '\0';
    } else {
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

int converter_texto_inteiro(const char *texto, int *numero) {
    char *fim;
    long valor;

    if (texto == NULL || numero == NULL) return 0;

    errno = 0;
    valor = strtol(texto, &fim, 10);
    if (texto == fim || errno == ERANGE || valor < INT_MIN || valor > INT_MAX) return 0;

    while (isspace((unsigned char)*fim)) fim++;
    if (*fim != '\0') return 0;

    *numero = (int)valor;
    return 1;
}

int ler_inteiro(void) {
    char texto[50];
    int numero;

    ler_texto(texto, sizeof texto);
    return converter_texto_inteiro(texto, &numero) ? numero : -1;
}
