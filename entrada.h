#ifndef ENTRADA_H
#define ENTRADA_H

// Lê uma linha inteira (aceita espaços) e tira o '\n' do final
void ler_texto(char *destino, int tamanho);

// Lê uma linha e converte para número. Retorna -1 se não for um número.
int ler_inteiro(void);

// Converte uma linha inteira em int; rejeita texto extra e valores fora do intervalo.
int converter_texto_inteiro(const char *texto, int *numero);

#endif
