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

// Imprime as relacoes de um usuario em especifico
void imprimir_grafo_usuario(grafo* g, char* usuario);

// Calcula a semelhanca entre dois usuarios.
double calcular_semelhanca(usuario* us1, usuario* us2);

// Cria um usuario nulo (faz os mallocs)
usuario* criar_usuario_nulo();

// Cria um usuario dado as suas informações e o coloca na lista de usuarios
usuario* criar_usuario(char* nome, int idade, char* filme_predileto, int interesse, int sexo, char* curso, char* genero_musica, char* cidade, usuario** lista);

// Dado uma variavel do tipo usuario, imprime suas informaçoes
void imprimir_usuario(usuario* us);

// Dado uma lista de usuarios, imprime todos
void listar_usuarios(usuario** lista);

// Dado o nome de um usuario, o procura na base de dados e mostra suas informaçoes
void mostrar_usuario(usuario** lista, char* nome);

// Manda um convite de amizade (tipo_convite == 1) ou namoro (tipo_convite == 2) do usuario origem para o usuario destino.
// tipo_convite é 1 para convite de amizade e 2 para convite de namoro.
void mandar_convite(grafo* g, char* origem, char* destino, int tipo_convite);

// Ve os convites do usuario e decide aceitá-los ou não.
void ver_convites(grafo* g, char* nome_usuario);

// Dado o nome de um usuario, sugere possiveis novos amigos verdadeiros com base em afinidade.
void sugerir_amigos(grafo* g, char* nome_usuario);

// Dado o nome de um usuario, detecta as pessoas em sua lista de contatos que nao deveriam estar la devido a baixa afinidade
void detectar_baixa_afinidade(grafo* g, char* nome_usuario);

// Dado o nome de um usuario, encontra o namorado ou a namorada ideal com base em suas afinidades.
void encontrar_par_ideal(grafo* g, char* nome_usuario);
#endif
