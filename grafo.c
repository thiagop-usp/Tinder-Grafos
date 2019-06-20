#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "grafo.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"
#define COLOR_BRRED   "\x1b[91m"
#define COLOR_BRWHITE "\x1b[97m"
#define COLOR_RESET   "\x1b[0m"

#define N 1000
#define AMIZADE 1
#define NAMORO 2
#define VERDADEIRO 0.5
#define BAIXA_AFINIDADE 0.2

struct USUARIO{
    char* nome;
    int id;
    int idade;
    char* filme_predileto;
    int interesse;
    int sexo;
    char* curso;
    char*  genero_musica;
    char* cidade;
};

struct ARESTA{
    double semelhanca;

    char* nome_i;
    char* nome_j;

    // interesse == 0 se i procura por homens, 1 se procura por mulheres e 2 se procura por ambos
    int interesse_i;
    int interesse_j;

    // sexo == 0 se i é homem e 1 se é mulher
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

usuario* criar_usuario(char* nome, int idade, char* filme_predileto, int interesse, int sexo, char* curso, char* genero_musica, char* cidade, usuario** lista_ids, int* id_max){
    usuario* us = criar_usuario_nulo();

    us->id = (*id_max)++;
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

    double total = (30.0*sim_idade + 15.0*sim_filme + 30.0*sim_curso + 20.0*sim_musica + 35.0*sim_cidade);
    total /= 130.0;
    total *= (1.0 - (abs(us1->idade - us2->idade)/100.0));
    return total;
}

void atualizar_grafo(grafo* g, usuario** lista, int* id_max){
    for(int i = 0; i < *id_max; i++){
        strcpy(g->relacao[i][i].nome_i, lista[i]->nome);
        for(int j = 0; j < *id_max; j++){
            if(i == j) continue;
            double semelhanca = calcular_semelhanca(lista[i], lista[j]);
            int id_i = lista[i]->id;
            int id_j = lista[j]->id;

            g->relacao[id_i][id_j].semelhanca = semelhanca;
            strcpy(g->relacao[id_i][id_j].nome_i, lista[i]->nome);
            strcpy(g->relacao[id_i][id_j].nome_j, lista[j]->nome);

            g->relacao[id_i][id_j].interesse_i = lista[i]->interesse;
            g->relacao[id_j][id_i].interesse_i = lista[j]->interesse;
            g->relacao[id_j][id_i].interesse_j = lista[i]->interesse;
            g->relacao[id_i][id_j].interesse_j = lista[j]->interesse;
            g->relacao[id_i][id_j].sexo_i = lista[i]->sexo;
            g->relacao[id_j][id_i].sexo_i = lista[j]->sexo;
            g->relacao[id_j][id_i].sexo_j = lista[i]->sexo;
            g->relacao[id_i][id_j].sexo_j = lista[j]->sexo;
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
                printf("%s não mandou convites para o(a) usuário(a) %s\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(convite == 1){
                printf("%s convidou o(a) usuário(a) %s para " COLOR_GREEN "amizade\n" COLOR_RESET, g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(convite == 2){
                printf("%s convidou o(a) usuário(a) %s para " COLOR_MAGENTA "namoro\n" COLOR_RESET, g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            }

            if(estado == 0){
                printf("%s não conhece o(a) usuário(a) %s\n", g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(estado == 1){
                printf("%s e %s são " COLOR_GREEN "amigos(as)\n" COLOR_RESET, g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            } else if(estado == 2){
                printf("%s e %s são " COLOR_MAGENTA "namorados(as)\n" COLOR_RESET, g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
            }
        }
        printf("\n");
    }
}

void imprimir_usuario(usuario* us){
    printf(COLOR_YELLOW "Nome: " COLOR_RESET "%s\n", us->nome);
    printf(COLOR_YELLOW "Idade: " COLOR_RESET "%d\n", us->idade);
    printf(COLOR_YELLOW "Filme predileto: " COLOR_RESET "%s\n", us->filme_predileto);

    char interesse[100];
    char sexo[100];

    if(us->sexo == 0){
        strcpy(sexo, "Homem");
    } else {
        strcpy(sexo, "Mulher");
    }
    if(us->interesse == 0){
        strcpy(interesse, "Homens");
    } else if(us->interesse == 1){
        strcpy(interesse, "Mulheres");
    } else if(us->interesse == 2){
        strcpy(interesse, "Ambos");
    } else {
        strcpy(interesse, "Nao declarado");
    }

    printf(COLOR_YELLOW "Sexo: " COLOR_RESET "%s\n", sexo);
    printf(COLOR_YELLOW "Interesse: " COLOR_RESET "%s\n", interesse);
    printf(COLOR_YELLOW "Curso: " COLOR_RESET "%s\n", us->curso);
    printf(COLOR_YELLOW "Genero musical favorito: " COLOR_RESET "%s\n", us->genero_musica);
    printf(COLOR_YELLOW "Cidade: " COLOR_RESET "%s\n", us->cidade);
}

void listar_usuarios(usuario** lista, int* id_max){
    for(int i = 0; i < *id_max; i++){
        usuario* us = lista[i];
        imprimir_usuario(us);
        printf("\n");
    }
}

void mostrar_usuario(usuario** lista, char* nome, int* id_max){
    for(int i = 0; i < *id_max; i++){
        usuario* us = lista[i];
        if(strcmp(us->nome, nome) == 0){
            printf(COLOR_GREEN "Usuario(a) %s encontrado(a)!\n=============================================\n\n" COLOR_RESET, nome);
            imprimir_usuario(us);
            return;
        }
    }

    printf(COLOR_RED "Usuário não encontrado\n" COLOR_RESET);
    return;
}

void imprimir_grafo_usuario(grafo* g, char* nome_usuario){
    int n = g->num_pessoas;
    int id = -1;
    for(int i = 0; i < n; i++){
        if(strcmp(g->relacao[i][0].nome_i, nome_usuario) == 0){
            id = i;
            break;
        }
    }

    if(id == -1){
        printf(COLOR_RED "Usuário não encontrado\n" COLOR_RESET);
        return;
    }

    for(int i = 0; i < n; i++){
        if(i == id) continue;
        double sem = g->relacao[i][id].semelhanca;
        int convite = g->relacao[i][id].convite;
        int estado = g->relacao[i][id].estado;

        printf("%s possui %lf%% de semelhança com %s\n", g->relacao[i][id].nome_i, sem * 100.0, g->relacao[i][id].nome_j);

        if(convite == 0){
            printf("%s não mandou convites para o(a) usuário(a) %s\n", g->relacao[i][id].nome_i, g->relacao[i][id].nome_j);
        } else if(convite == 1){
            printf("%s convidou o(a) usuário(a) %s para amizade\n", g->relacao[i][id].nome_i, g->relacao[i][id].nome_j);
        } else if(convite == 2){
            printf("%s convidou o(a) usuário(a) %s para namoro\n", g->relacao[i][id].nome_i, g->relacao[i][id].nome_j);
        }

        if(estado == 0){
            printf("%s não conhece o(a) usuário(a) %s\n", g->relacao[i][id].nome_i, g->relacao[i][id].nome_j);
        } else if(estado == 1){
            printf("%s e %s são amigos(as)\n", g->relacao[i][id].nome_i, g->relacao[i][id].nome_j);
        } else if(estado == 2){
            printf("%s e %s são namorados(as)\n", g->relacao[i][id].nome_i, g->relacao[i][id].nome_j);
        }
    }
}

void mandar_convite(grafo* g, char* origem, char* destino, int tipo_convite){
    int n = g->num_pessoas;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            if(strcmp(g->relacao[i][j].nome_i, origem) != 0 || strcmp(g->relacao[i][j].nome_j, destino) != 0) continue;

	    printf(COLOR_GREEN "Convite enviado!\n" COLOR_RESET);
	    g->relacao[i][j].convite = tipo_convite;
            return;
        }
    }
    printf(COLOR_RED "Usuários não encontrados no sistema.\n" COLOR_RESET);
}

void ver_convites(grafo* g){
    int n = g->num_pessoas;
    int num_pendentes = 0;

    printf(COLOR_YELLOW "Os seguintes convites se encontram pendentes:\n" COLOR_RESET);

    for(int i = 0; i < n; i++){
	for(int j = 0; j < n; j++){
	    if(i == j) continue;
	    if(g->relacao[i][j].convite != 0){
		num_pendentes++;
		printf("%s mandou um convite para " COLOR_GREEN  "%s.\n" COLOR_RESET, g->relacao[i][j].nome_i, g->relacao[i][j].nome_j);
	    }
	}
    }

    if(!num_pendentes)
	    printf(COLOR_GREEN "Não há convites pendentes\n" COLOR_RESET);

    printf(COLOR_YELLOW "========================================================================================\n\n" COLOR_RESET);
}

void ver_convites_usuario(grafo* g, char* nome_usuario){
    int n = g->num_pessoas;
    int id = -1;

    for(int i = 0; i < n; i++){
        if(strcmp(g->relacao[i][0].nome_i, nome_usuario) == 0){
            id = i;
            break;
        }
    }

    if(id == -1){
        printf(COLOR_RED "Usuário não encontrado\n" COLOR_RESET);
        return;
    }

    int num_convites = 0;
	
    for(int j = 0; j < n; j++){
        if(j == id) continue;
        int* convite = &(g->relacao[j][id].convite);
        int* estado = &(g->relacao[j][id].estado);
        int* estado2 = &(g->relacao[id][j].estado);
        double semelhanca = g->relacao[j][id].semelhanca;

        if(*convite) num_convites++;

        if(*convite == 1){
            printf("%s mandou um convite de amizade para você! O que deseja fazer?\n\n" COLOR_RED "[0]: Recusar\n" COLOR_GREEN "[1]: Aceitar\n" COLOR_YELLOW "[2]: Ignorar\n" COLOR_RESET, g->relacao[j][id].nome_i);
            printf("A chance de essa ser a amizade ideal é de %lf%%\n", semelhanca*100.0);
            printf("======================================================================================\n");
            char* opcao = malloc(5);
            int correta = 0;

            while(!correta) {
                scanf("%s", opcao);
                if(opcao[0] == '0'){
                    *convite = 0;
                    correta = 1;
                    printf(COLOR_RED "O convite foi removido\n" COLOR_RESET);
                    break;
                } else if (opcao[0] == '1'){
                    *convite = 0;
                    *estado = 1;
                    *estado2 = 1;
                    correta = 1;
                    printf(COLOR_GREEN "Você e %s viraram amigos(as)!\n" COLOR_RESET, g->relacao[j][id].nome_i);
                    break;
                } else if (opcao[0] == '2'){
                    correta = 1;
                    printf(COLOR_YELLOW "Você ignorou o convite...\n" COLOR_RESET);
                }
            }
            printf("\n");
        }

        if(*convite == 2){
            printf("%s mandou um pedido de namoro para você! O que deseja fazer?\n\n" COLOR_RED "[0]: Recusar\n" COLOR_GREEN "[1]: Aceitar\n" COLOR_YELLOW "[2]: Ignorar\n" COLOR_RESET, g->relacao[j][id].nome_i);
            printf("A chance de essa ser o namoro ideal é de %lf%%\n", semelhanca*100.0);
            printf("======================================================================================\n");
            int opcao = -1;
            int correta = 0;

            while(!correta){
                scanf("%d", &opcao);
                switch(opcao){
                    case 0:
                        *convite = 0;
                        correta = 1;
                        printf(COLOR_RED "O convite foi removido\n" COLOR_RESET);
                        break;
                    case 1:
                        *convite = 0;
                        *estado = 2;
                        *estado2 = 2;
                        correta = 1;
                        printf(COLOR_MAGENTA "Você e %s viraram namorados!\n" COLOR_RESET, g->relacao[j][id].nome_i);
                        break;
                    case 2:
                        correta = 1;
                        printf(COLOR_YELLOW "Você ignorou o convite...\n" COLOR_RESET);
                        break;
                    default:
                        break;
                }
            }
            printf("\n");
        }
    }
    if(!num_convites)
        printf(COLOR_YELLOW "Usuário não possui convites pendentes.\n" COLOR_RESET);
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
        printf(COLOR_RED "Usuário não encontrado\n" COLOR_RESET);
        return;
    }

    int num_sugestoes = 0;

    for(int i = 0; i < n; i++){
        if(i == id) continue;
        double semelhanca = g->relacao[i][id].semelhanca;
        int estado = g->relacao[i][id].estado;

        if(semelhanca >= VERDADEIRO && estado == 0){
            num_sugestoes++;
            printf("Você e %s seriam grandes parceiros(as)!\nSeu grau de afinidade de perfil é de %lf%%!\nO que você deseja fazer?\n\n" COLOR_YELLOW "[0]: Mandar um convite de amizade.\n[1]: Enviar um convite de namoro\n[2]: Prosseguir.\n" COLOR_RESET, g->relacao[i][id].nome_i, semelhanca*100.0);
            printf("==================================================================\n");

            int tipo_convite = -1;
            scanf("%d", &tipo_convite);

            while(tipo_convite != 2){
                if(tipo_convite == 0){
		    mandar_convite(g, nome_usuario, g->relacao[i][id].nome_i, AMIZADE);
                    tipo_convite = 2;
                }
                else if(tipo_convite == 1){
		    mandar_convite(g, nome_usuario, g->relacao[i][id].nome_i, NAMORO);
                    tipo_convite = 2;
                }
                else {
                    scanf("%d", &tipo_convite);
                }
            }
        }
    }
    if(!num_sugestoes)
        printf("Desculpe, nao existem sugestoes validas para voce, com base em afinidade de perfil...\n");
}

void detectar_baixa_afinidade(grafo* g, char* nome_usuario){
    int n = g->num_pessoas;
    int id = -1;

    for(int i = 0; i < n; i++){
        if(strcmp(g->relacao[i][0].nome_i, nome_usuario) == 0){
            id = i;
            break;
        }
    }

    if(id == -1){
        printf(COLOR_RED "Usuário não encontrado\n" COLOR_RESET);
        return;
    }

    int num_contatos = 0;

    for(int i = 0; i < n; i++){
        if(i == id) continue;
        double semelhanca = g->relacao[i][id].semelhanca;
        int* estado = &(g->relacao[i][id].estado);

        if(semelhanca <= BAIXA_AFINIDADE && *estado != 0){
            num_contatos++;
            if(*estado == 1)
                printf("%s está registrado como amigo na sua lista de contatos, ", g->relacao[i][id].nome_i);
            else if(*estado == 2)
                printf("%s está registrado como namorado(a) na sua lista de contatos, ", g->relacao[i][id].nome_i);

            printf("mas não deveria estar lá!\nSeu grau de afinidade de perfil é de apenas %lf%%!\nVocê gostaria de removê-lo da lista?\n", semelhanca*100.0);
            printf("==================================================================\n");

            int opcao = -1;
            int correta = 0;
            while(!correta){
                printf("O que você deseja fazer?\n\n" COLOR_YELLOW "[0]: Remover o contato\n[1]: Prosseguir.\n" COLOR_RESET);
                scanf("%d", &opcao);
                if(opcao == 0){
                    printf(COLOR_GREEN "O contato foi removido da sua lista!\n" COLOR_RESET);
                    *estado = 0;
                    correta = 1;
                } else if(opcao == 1){
                    correta = 1;
                } else {
                    printf("O que você deseja fazer?\n\n" COLOR_YELLOW "[0]: Remover o contato\n[1]: Prosseguir.\n" COLOR_RESET);
                }
            }
        }
    }
    if(!num_contatos)
        printf("Todos os contatos possuem grau de afinidade suficiente.\n");
}

void encontrar_par_ideal(grafo* g, char* nome_usuario){
    int n = g->num_pessoas;
    int id = -1;

    for(int i = 0; i < n; i++){
        if(strcmp(g->relacao[i][0].nome_i, nome_usuario) == 0){
            id = i;
            break;
        }
    }

    if(id == -1){
        printf(COLOR_RED "Usuário não encontrado\n" COLOR_RESET);
        return;
    }

    double max_semelhanca = 0.0;
    int ideal = -1;

    for(int i = 0; i < n; i++){
        char sexo_id = g->relacao[id][i].sexo_i;
        char sexo_j = g->relacao[id][i].sexo_j;
        char interesse_id = g->relacao[id][i].interesse_i;
        char interesse_j = g->relacao[id][i].interesse_j;
        int caso1 = interesse_id == 'a' && (interesse_j == 'a' || interesse_j == sexo_id);
        int caso2 = interesse_id == sexo_j && (interesse_j == 'a' || interesse_j == sexo_id);
        int estado = g->relacao[id][i].estado;

        if(i == id || estado == 0 || (!caso1 && !caso2)) continue;

        double semelhanca = g->relacao[i][id].semelhanca;
        if(semelhanca > max_semelhanca){
            max_semelhanca = semelhanca;
            ideal = i;
        }
    }

    if(ideal == -1) {
        printf(COLOR_RED "Desculpe, não foi possível determinar par ideal para o usuário...\n" COLOR_RESET);
        return;
    }

    printf("Encontramos o seu par ideal!\n");
    printf("Você e %s possuem um grau de %lf %% de afinidade de perfil.\n", g->relacao[id][ideal].nome_j, g->relacao[id][ideal].semelhanca*100.0);

    int opcao = -1;
    while(opcao != 0 && opcao != 1){
        printf("O que você deseja fazer?\n\n" COLOR_YELLOW "[0]: Enviar um convite de namoro\n[1]: Prosseguir.\n" COLOR_RESET);
        scanf("%d", &opcao);
        if(opcao == 0){
            printf(COLOR_GREEN "O convite de namoro foi enviado!\n" COLOR_RESET);
            mandar_convite(g, nome_usuario, g->relacao[id][ideal].nome_j, 2);
        }
    }
}
