#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "leitor.h"

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
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"
#define MENU1 "Bem vindo ao Rednit, o lugar perfeito para se relacionar!\n===============================================\n"
#define MENU2 "O que você gostaria de fazer?\n\n"
#define MENU3 "0: Carregar arquivo .csv\n1: Listar relações\n"
#define MENU4 "2: Listar relações (usuário)\n3: Enviar convite de amizade\n4: Ver convites\n"
#define MENU5 "5: Sugerir novos amigos\n6: Detectar falsas amizades\n7: Mostrar menu\n8: Sair\n" COLOR_MAGENTA "===============================================\n"
#define RED0 "     ____ _____  ____ _   _ ___ _____ \n"
#define RED1 "    / _  |____ |/ _  | | / |_ _|_   _|\n"
#define RED2 "   | (_| | |_  | | | | |/  || |  | |\n"
#define RED3 "    > _  |___| | |_| |  /| || |  | |\n"
#define RED4 "   /_/ |_|_____|\\____|_/ |_|___| |_|\n"
#define RED5 "\n"
#define RED RED0 RED1 RED2 RED3 RED4 RED5
#define MENUREP MENU2 MENU3 MENU4 MENU5
#define MENUIN RED MENU1 COLOR_RESET MENUREP

int main(){
    usuario* lista[1000];
    for(int i = 0; i < 1000; i++) lista[i] = criar_usuario_nulo();

    int menu_op = -1;

    printf(COLOR_MAGENTA MENUIN);
    grafo* g = NULL;

    while(menu_op != 8){
        scanf("%d", &menu_op);

        switch(menu_op){
            case 0:
                printf(COLOR_YELLOW "Digite o nome do arquivo .csv\n" COLOR_RESET);
                char nome_arquivo[100];
                scanf("%s", nome_arquivo);

                int n = ler_usuarios_arquivo(lista, nome_arquivo);
                g = criar_grafo(n);
                atualizar_grafo(g, lista);
                printf(COLOR_YELLOW "Base carregada com sucesso!\n===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 1:
                if(g == NULL)
                    printf(COLOR_RED "Você deve carregar uma base de dados antes!\n" COLOR_RESET);
                else
                    imprimir_grafo(g);
                printf(COLOR_YELLOW "===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 2:
                printf(COLOR_YELLOW "Digite o nome do usuário\n" COLOR_RESET);
                char nome_usuario[100];
                scanf("%s", nome_usuario);
                if(g == NULL)
                    printf(COLOR_RED "Você deve carregar uma base de dados antes!\n" COLOR_RESET);
                else
                    imprimir_grafo_usuario(g, nome_usuario);
                printf(COLOR_YELLOW "===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 3:
                printf(COLOR_YELLOW "Digite o nome do remetente\n" COLOR_RESET);
                char origem[100];
                scanf("%s", origem);

                printf(COLOR_YELLOW "Digite o nome do destinatario\n" COLOR_RESET);
                char destino[100];
                scanf("%s", destino);

                printf(COLOR_YELLOW "Qual é o tipo do convite? Digite (1) para convite de amizade e (2) para convite de namoro.\n" COLOR_RESET);

                int tipo_convite;
                scanf("%d", &tipo_convite);

                if(g == NULL)
                    printf(COLOR_RED "Você deve carregar uma base de dados antes!\n" COLOR_RESET);
                else
                    mandar_convite(g, origem, destino, tipo_convite);

                printf(COLOR_YELLOW "===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 4:
                printf(COLOR_YELLOW "Digite o nome do usuário do qual você gostaria de ver os convites.\n" COLOR_RESET);
                scanf("%s", nome_usuario);

                if(g == NULL)
                    printf(COLOR_RED "Você deve carregar uma base de dados antes!\n" COLOR_RESET);
                else
                    ver_convites(g, nome_usuario);

                printf(COLOR_YELLOW "===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 5:
                printf(COLOR_RESET "Digite o nome do usuário do qual você gostaria de realizar sugestões.\n");
                scanf("%s", nome_usuario);

                if(g == NULL)
                    printf(COLOR_RESET "Você deve carregar uma base de dados antes!\n");
                else
                    sugerir_amigos(g, nome_usuario);

                printf(COLOR_YELLOW "===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 6:
                printf(COLOR_RESET "Digite o nome do usuário do qual você gostaria de detectar contatos inválidos.\n");
                scanf("%s", nome_usuario);

                if(g == NULL)
                    printf(COLOR_RESET "Você deve carregar uma base de dados antes!\n");
                else
                    detectar_baixa_afinidade(g, nome_usuario);

                printf(COLOR_YELLOW "===================================================\nDigite a próxima operação.\n" COLOR_RESET);
                break;
            case 7:
                system("clear");
                printf(COLOR_MAGENTA MENUIN);
                break;
        }

    }
    return 0;
}
