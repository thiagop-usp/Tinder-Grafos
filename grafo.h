#ifndef GRAFO_H
#define GRAFO_H

typedef struct GRAFO grafo;
typedef struct ARESTA aresta;
typedef struct USUARIO usuario;

// Cria um grafo com o numero de pessoas especificado.
grafo* criar_grafo(int num_pessoas);

// Atualiza o grafo com as semelhanças entre os usuarios.
void atualizar_grafo(grafo* g, usuario** lista);

// Imprime as relacoes entre os usuarios do grafo
void imprimir_grafo(grafo* g);

// Calcula a semelhanca entre dois usuarios.
double calcular_semelhanca(usuario* us1, usuario* us2);

// Cria um usuario nulo (faz os mallocs)
usuario* criar_usuario_nulo();

// Cria um usuario dado as suas informações e o coloca na lista de usuarios
usuario* criar_usuario(char* nome, int idade, char* filme_predileto, int interesse, char sexo, char* curso, char* genero_musica, char* cidade, usuario** lista);

// Manda um convite de amizade (tipo_convite == 1) ou namoro (tipo_convite == 2) do usuario origem para o usuario destino.
void mandar_convite(grafo* g, char* origem, char* destino, int tipo_convite);

// Ve os convites do usuario e decide aceitá-los ou não.
void ver_convites(grafo* g, char* nome_usuario);

// Dado o nome de um usuario, sugere possiveis novos amigos verdadeiros com base em afinidade.
void sugerir_amigos(grafo* g, char* nome_usuario);
#endif
