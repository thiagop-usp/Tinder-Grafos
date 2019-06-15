#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "leitor.h"

#define MENU1 "Bem vindo ao Rednit, o lugar perfeito para se relacionar!\n===============================================\n"
#define MENU2 "O que você gostaria de fazer?\n\n"
#define MENU3 "0: Carregar arquivo .csv\n1: Listar relações\n"
#define MENU4 "2: Enviar convite de amizade\n3: Ver convites\n"
#define MENU5 "4: Sugerir novos amigos\n5: Detectar falsas amizades\n6: Mostrar menu\n7: Sair\n"

#define RED0 "     ____ _____  ____ _   _ ___ _____ \n"
#define RED1 "    / _  |____ |/ _  | | / |_ _|_   _|\n"
#define RED2 "   | (_| | |_  | | | | |/  || |  | |\n"
#define RED3 "    > _  |___| | |_| |  /| || |  | |\n"
#define RED4 "   /_/ |_|_____|\\____|_/ |_|___| |_|\n"
#define RED5 "\n"
#define RED RED0 RED1 RED2 RED3 RED4 RED5
#define MENUREP MENU2 MENU3 MENU4 MENU5
#define MENUIN RED MENU1 MENUREP

int main(){
    usuario* lista[1000];
    for(int i = 0; i < 1000; i++) lista[i] = criar_usuario_nulo();

    int menu_op = -1;

    printf(MENUIN);
    grafo* g = NULL;

    while(menu_op != 7){
        scanf("%d", &menu_op);

        switch(menu_op){
            case 0:
                printf("Digite o nome do arquivo .csv\n");
                char nome_arquivo[100];
                scanf("%s", nome_arquivo);

                int n = ler_usuarios_arquivo(lista, nome_arquivo);
                g = criar_grafo(n);
                atualizar_grafo(g, lista);
                printf("Base carregada com sucesso!\n===================================================\nDigite a próxima operação.\n");
                break;
            case 1:
                if(g == NULL)
                    printf("Você deve carregar uma base de dados antes!\n");
                else
                    imprimir_grafo(g);
                printf("===================================================\nDigite a próxima operação.\n");
                break;
            case 2:
                printf("Digite o nome do remetente\n");
                char origem[100];
                scanf("%s", origem);

                printf("Digite o nome do destinatario\n");
                char destino[100];
                scanf("%s", destino);

                printf("Qual é o tipo do convite? Digite (1) para convite de amizade e (2) para convite de namoro.\n");

                int tipo_convite;
                scanf("%d", &tipo_convite);

                if(g == NULL)
                    printf("Você deve carregar uma base de dados antes!\n");
                else
                    mandar_convite(g, origem, destino, tipo_convite);

                printf("===================================================\nDigite a próxima operação.\n");
                break;
            case 3:
                printf("Digite o nome do usuário do qual você gostaria de ver os convites.\n");
                char usuario[100];
                scanf("%s", usuario);

                if(g == NULL)
                    printf("Você deve carregar uma base de dados antes!\n");
                else
                    ver_convites(g, usuario);

                printf("===================================================\nDigite a próxima operação.\n");
                break;
            case 4:
                printf("Digite o nome do usuário do qual você gostaria de realizar sugestões.\n");
                scanf("%s", usuario);

                if(g == NULL)
                    printf("Você deve carregar uma base de dados antes!\n");
                else
                    sugerir_amigos(g, usuario);

                printf("===================================================\nDigite a próxima operação.\n");
                break;
            case 5:
                printf("Digite o nome do usuário do qual você gostaria de detectar contatos inválidos.\n");
                scanf("%s", usuario);

                if(g == NULL)
                    printf("Você deve carregar uma base de dados antes!\n");
                else
                    detectar_baixa_afinidade(g, usuario);

                printf("===================================================\nDigite a próxima operação.\n");
                break;
            case 6:
                system("clear");
                printf(MENUREP);
                break;
        }

    }
    return 0;
}
