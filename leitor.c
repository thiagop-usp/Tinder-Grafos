#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int ler_usuarios_arquivo(usuario** lista, char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf(COLOR_RED "Arquivo não encontrado\n" COLOR_RESET);
        return -1;
    }

    char cabecalho[100];
    fgets(cabecalho, 100, arquivo);
    int num_usuarios = 0;

    while(!feof(arquivo)){
        char* nome = malloc(50);
        char* filme = malloc(50);
        char* curso = malloc(50);
        char* gen = malloc(50);
        char* cid = malloc(50);
        int idade;
        int interesse, sexo;

        fscanf(arquivo, "%[^,]", nome);

        if(feof(arquivo))
            break;

        fscanf(arquivo, ",%[^,]", filme);
        fscanf(arquivo, ",%[^,]", curso);
        fscanf(arquivo, ",%[^,]", gen);
        fscanf(arquivo, ",%[^,]", cid);

        fscanf(arquivo, "%*c%d%*c%d%*c%d%*c", &idade, &interesse, &sexo);
        criar_usuario(nome, idade, filme, interesse, sexo, curso, gen, cid, lista);

        num_usuarios++;
    }
    fclose(arquivo);
    return num_usuarios;
}

int escrever_usuario_arquivo(usuario* us, char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "a");

    if(arquivo == NULL){
        printf(COLOR_RED "Arquivo não encontrado\n" COLOR_RESET);
        return -1;
    }

    fprintf(arquivo, "%s,", us->nome);
    fprintf(arquivo, "%s,", us->filme_predileto);
    fprintf(arquivo, "%s,", us->curso);
    fprintf(arquivo, "%s,", us->genero_musica);
    fprintf(arquivo, "%s,", us->cidade);
    fprintf(arquivo, "%d,", us->idade);
    fprintf(arquivo, "%d,", us->interesse);
    fprintf(arquivo, "%d\n", us->sexo);

    fclose(arquivo);
    return 1;
}

usuario* ler_usuario(){
    usuario* us = criar_usuario_nulo();

    printf(COLOR_YELLOW "Digite o nome do usuario:\n" COLOR_RESET);
    scanf(" %[^\n]", us->nome);

    printf(COLOR_YELLOW "Digite o filme predileto do usuario:\n" COLOR_RESET);
    scanf(" %[^\n]", us->filme_predileto);

    printf(COLOR_YELLOW "Digite o curso do usuario:\n" COLOR_RESET);
    scanf(" %[^\n]", us->curso);

    printf(COLOR_YELLOW "Digite o genero musical favorito do usuario:\n" COLOR_RESET);
    scanf(" %[^\n]", us->genero_musica);

    printf(COLOR_YELLOW "Digite o a cidade do usuario:\n" COLOR_RESET);
    scanf("%*c%[^\n]", us->cidade);

    printf(COLOR_YELLOW "Digite a idade do usuario:\n" COLOR_RESET);
    scanf("\n%d", &us->idade);

    printf(COLOR_YELLOW "Digite o interesse do usuario\n\n[0]: Homens\n[1]: Mulheres\n[2]: Ambos\n" COLOR_RESET);
    scanf("\n%d", &us->interesse);

    printf(COLOR_YELLOW "Digite o sexo do usuario\n\n[0]: Homem\n[1]: Mulher\n[2]: Nao declarar\n" COLOR_RESET);
    scanf("\n%d", &us->sexo);

    return us;
}

