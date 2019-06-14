#include "leitor.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

usuario* ler_usuario(usuario** lista){
    char* nome;
    char* filme;
    char* curso;
    char* gen;
    char* cid;

    nome = malloc(50);
    scanf("%[^\n] ", nome);
    filme = malloc(50);
    scanf("%[^\n] ", filme);
    curso = malloc(50);
    scanf("%[^\n] ", curso);
    gen = malloc(50);
    scanf("%[^\n] ", gen);
    cid = malloc(50);
    scanf("%[^\n] ", cid);

    int idade, interesse;
    char sexo;

    scanf("%d %d ", &idade, &interesse);
    scanf("%c ", &sexo);
    usuario* us = criar_usuario(nome, idade, filme, interesse, sexo, curso, gen, cid, lista);

    return us;
}

