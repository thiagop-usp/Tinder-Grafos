#ifndef LEITOR_H
#define LEITOR_H
#include "grafo.h"

// Le os usuarios do arquivo de dados .csv e retorna o numero de usuarios lidos
int ler_usuarios_arquivo(usuario** lista, char* nome_arquivo);

// tornar uma string lowercase
char* minuscula(char* str);

#endif
