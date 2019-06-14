#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "grafo.h"

#define N 1000
#define AMIZADE 1
#define NAMORO 2
#define VERDADEIRO 0.6

int id_max;

struct USUARIO{
    char* nome;
    int id;
    int idade;
    char* filme_predileto;
    int interesse;
    char sexo;
    char* curso;
    char*  genero_musica;
    char* cidade;
};

struct ARESTA{
    double semelhanca;

    char* nome_i;
    char* nome_j;

    // interesse == 'h' se i procura por homens, 'm' se procura por mulheres e 'a' se procura por ambos
    char interesse_i;
    char interesse_j;

    // sexo == 'h' se i é homem e 'm' se é mulher
    char sexo_i;
    char sexo_j;

    // Estado == 0 se o usuario i nao conhece o usuario j
    // Estado == 1 se o usuario i é amigo do usuario j
    // Estado == 2 se o usuario i namora o usuário j
    int estado;

    // Convite == 0 se o usuario i nao convidou o usuario j
    // Convite == 1 se o usuario i enviou um convite de amizade para o usuario j
    // Convite == 2 se o usuario i enviou um convite de namoro para o usuario j
    int convite;
};

struct GRAFO{
    aresta relacao[N][N];
    int num_pessoas;
};

grafo* criar_grafo(int num_pessoas){
    grafo* g = malloc(sizeof(grafo));

    if(g == NULL) return g;

    g->num_pessoas = num_pessoas;

    for(int i = 0; i < num_pessoas; i++){
        g->relacao[i][i].nome_i = malloc(50);
        g->relacao[i][i].nome_j = malloc(50);
    }

    for(int i = 0; i < num_pessoas; i++){
        for(int j = 0; j < num_pessoas; j++){
            if(i == j) continue;
            g->relacao[i][j].semelhanca = 0.0;
            g->relacao[i][j].convite = 0;
            g->relacao[i][j].estado = 0;
            g->relacao[i][j].nome_i = malloc(50);
            g->relacao[i][j].nome_j = malloc(50);
        }
    }
    return g;
}

usuario* criar_usuario_nulo(){
    usuario* us = malloc(sizeof(usuario));
    us->nome = malloc(50);
    us->filme_predileto = malloc(50);
    us->curso = malloc(50);
    us->cidade = malloc(50);
    us->genero_musica = malloc(50);
    return us;
}

usuario* criar_usuario(char* nome, int idade, char* filme_predileto, int interesse, char sexo, char* curso, char* genero_musica, char* cidade, usuario** lista_ids){
    usuario* us = criar_usuario_nulo();

    us->id = id_max++;
    us->idade = idade;
    us->interesse = interesse;
    us->sexo = sexo;

    strcpy(us->nome, nome);
    strcpy(us->curso, curso);
    strcpy(us->genero_musica, genero_musica);
    strcpy(us->cidade, cidade);
    strcpy(us->filme_predileto, filme_predileto);

    lista_ids[us->id] = us;
    return us;
}

double calcular_semelhanca(usuario* us1, usuario* us2){
    double sim_idade = 1 - 0.02*(abs(us1->idade - us2->idade));

    double sim_curso = (double) strcmp(us1->curso, us2->curso);   
    if(sim_curso == 0) sim_curso = 1.0;
    else sim_curso = 0.0;

    double sim_cidade = (double) strcmp(us1->cidade, us2->cidade);   
    if(sim_cidade == 0) sim_cidade = 1.0;
    else sim_cidade = 0.0;

    double sim_filme = (double) strcmp(us1->filme_predileto, us2->filme_predileto);   
    if(sim_filme == 0) sim_filme = 1.0;
    else sim_filme = 0.0;

    double sim_musica = (double) strcmp(us1->genero_musica, us2->genero_musica);   
    if(sim_musica == 0) sim_musica = 1.0;
    else sim_musica = 0.0;

    double total = (12.0*sim_idade + 0.5*sim_filme + 4.0*sim_curso + 0.5*sim_musica + 3.0*sim_cidade);
    total /= 20.0;

    return total;
}

void atualizar_grafo(grafo* g, usuario** lista){
    for(int i = 0; i < id_max; i++){
        strcpy(g->relacao[i][i].nome_i, lista[i]->nome);
        for(int j = 0; j < id_max; j++){
            if(i == j) continue;
            double semelhanca = calcular_semelhanca(lista[i], lista[j]);
            int id_i = lista[i]->id;
            int id_j = lista[j]->id;

            g->relacao[id_i][id_j].semelhanca = semelhanca;
            strcpy(g->relacao[id_i][id_j].nome_i, lista[i]->nome);
            strcpy(g->relacao[id_i][id_j].nome_j, lista[j]->nome);

            g->relacao[id_i][id_j].interesse_i = lista[i]->interesse;
            g->relacao[id_i][id_j].sexo_i = lista[i]->sexo;
            g->relacao[id_i][id_j].interesse_j = lista[j]->interesse;
            g->relacao[id_i][id_j].sexo_i = lista[j]->sexo;
        }
    }
}

void imprimir_grafo(grafo* g){
    int n = g->num_pessoas;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            double sem = g->relacao[i][j].semelhanca;
            int convite = g->relacao[i][j].convite;
            int estado = g->relacao[i][j].estado;

            printf("%s possui %lf%% de semelhança com %s\n", g->relacao[i][j].nome_i, sem * 100.0, g->relacao[i][j].nome_j);

            if(convite == 0){
                printf("%s nao convidou o usuario %s\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(convite == 1){
                printf("%s convidou o usuario %s para amizade\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(convite == 2){
                printf("%s convidou o usuario %s para namoro\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            }

            if(estado == 0){
                printf("%s nao conhece o usuario %s\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(estado == 1){
                printf("%s e %s sao amigos\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(estado == 2){
                printf("%s e %s sao namorados\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            }
        }
        printf("\n");
    }
}

void mandar_convite(grafo* g, char* origem, char* destino, int tipo_convite){
    int n = g->num_pessoas;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            if(strcmp(g->relacao[i][j].nome_i, origem) != 0 || strcmp(g->relacao[i][j].nome_j, destino) != 0) continue;

            // 0 se nao conhece, 1 se é amigo, 2 se sao namorados
            int estado = g->relacao[i][j].estado;

            if(!estado){
                g->relacao[i][j].convite = tipo_convite;
            } else {
                printf("Usuários já se conhecem.\n");
            }
            return;
        }
    }
    printf("Usuários não encontrados no sistema.\n");
}

void ver_convites(grafo* g, char* nome_usuario){
    int n = g->num_pessoas;
    int id = -1;

    for(int i = 0; i < n; i++){
        if(strcmp(g->relacao[i][0].nome_i, nome_usuario) == 0){
            id = i;
            break;
        }
    }

    if(id == -1){
        printf("Usuário não encontrado\n");
        return;
    }

    for(int j = 0; j < n; j++){
        if(j == id) continue;
        int* convite = &(g->relacao[j][id].convite);
        int* estado = &(g->relacao[j][id].estado);
        double semelhanca = g->relacao[j][id].semelhanca;

        if(*convite == 1){
            printf("%s mandou um convite de amizade para você! Recusar (r), Aceitar (a) ou Ignorar (i)?\n", g->relacao[j][id].nome_i);
            printf("A chance de essa ser a amizade ideal é de %lf%%\n", semelhanca*100.0);
            printf("======================================================================================\n");
            char opcao = '-';
            int correta = 0;

            while(!correta){
                scanf(" %c", &opcao);
                switch(opcao){
                    case 'r':
                        *convite = 0;
                        correta = 1;
                        printf("O convite foi removido\n");
                        break;
                    case 'a':
                        *convite = 0;
                        *estado = 1;
                        correta = 1;
                        printf("Você e %s viraram amigos!\n", g->relacao[j][id].nome_i);
                        break;
                    case 'i':
                        correta = 1;
                        printf("Você ignorou o convite...\n");
                        break;
                    default:
                        break;
                }
            }

        }

        if(*convite == 2){
            printf("%s mandou um pedido de namoro para você! Recusar (r), Aceitar (a) ou Ignorar (i)?\n", g->relacao[j][id].nome_i);
            printf("A chance de essa ser o namoro ideal é de %lf%%\n", semelhanca*100.0);
            printf("======================================================================================\n");
            char opcao = '-';
            int correta = 0;

            while(!correta){
                scanf(" %c", &opcao);
                switch(opcao){
                    case 'r':
                        *convite = 0;
                        correta = 1;
                        printf("O convite foi removido\n");
                        break;
                    case 'a':
                        *convite = 0;
                        *estado = 1;
                        correta = 1;
                        printf("Você e %s viraram namorados!\n", g->relacao[j][id].nome_i);
                        break;
                    case 'i':
                        correta = 1;
                        printf("Você ignorou o convite...\n");
                        break;
                    default:
                        break;
                }
            }
        }
        printf("\n");
    }
}

void sugerir_amigos(grafo* g, char* nome_usuario){
    int n = g->num_pessoas;
    int id = -1;

    for(int i = 0; i < n; i++){
        if(strcmp(g->relacao[i][0].nome_i, nome_usuario) == 0){
            id = i;
            break;
        }
    }

    if(id == -1){
        printf("Usuário não encontrado\n");
        return;
    }

    for(int i = 0; i < n; i++){
        if(i == id) continue;
        double semelhanca = g->relacao[i][id].semelhanca;
        int estado = g->relacao[i][id].estado;

        if(semelhanca >= VERDADEIRO && estado == 0){
            printf("Você e %s seriam grandes parceiros!\nSeu grau de afinidade de perfil é de %lf%%!\nDigite (0) para mandar um convite de amizade, (1) para um convite de namoro e (2) para prosseguir.\n", semelhanca*100.0, g->relacao[i][id].nome_i);
            printf("==================================================================\n");

            int tipo_convite = -1;
            scanf(" %d ", &tipo_convite);

            while(tipo_convite != 2){
                mandar_convite(g, nome_usuario, g->relacao[i][id].nome_i, tipo_convite);
                if(tipo_convite == 0){
                    printf("Convite de amizade enviado para %s!\n", g->relacao[i][id].nome_i);
                    tipo_convite = 2;
                }
                else if(tipo_convite == 1){
                    printf("Convite de namoro enviado para %s!\n", g->relacao[i][id].nome_i);
                    tipo_convite = 2;
                }
                else {
                    scanf(" %d ", &tipo_convite);
                }
            }
        }
        printf("\n");
    }
}