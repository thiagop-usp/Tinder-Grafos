#ifndef LEITOR_H
#define LEITOR_H
#include "grafo.h"

// Le os usuarios do arquivo de dados .csv e retorna o numero de usuarios lidos
int ler_usuarios_arquivo(usuario** lista, char* nome_arquivo);

// Dado um usuario, o adiciona na base de dados. Retorna 1 caso a adição tenha sido feita com sucesso e -1 caso contrário
int escrever_usuario_arquivo(usuario* us, char* nome_arquivo);

// Le os dados de um usuario e o retorna
usuario* ler_usuario();

#endif
