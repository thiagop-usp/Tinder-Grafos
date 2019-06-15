#include "leitor.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* minuscula(char* str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int ler_usuarios_arquivo(usuario** lista, char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "r+");
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

        nome = minuscula(nome);
        filme = minuscula(filme);
        curso = minuscula(curso);
        gen = minuscula(gen);
        cid = minuscula(cid);

        fscanf(arquivo, "%*c%d%*c%d%*c%d%*c", &idade, &interesse, &sexo);
        criar_usuario(nome, idade, filme, interesse, sexo, curso, gen, cid, lista);

        num_usuarios++;
    }
    return num_usuarios;
}

