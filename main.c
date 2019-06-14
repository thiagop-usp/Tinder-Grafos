#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "leitor.h"

int main(){
    usuario* lista[1000];
    for(int i = 0; i < 1000; i++) lista[i] = criar_usuario_nulo();

    usuario* us1 = ler_usuario(lista);
    usuario* us2 = ler_usuario(lista);
    usuario* us3 = ler_usuario(lista);
    usuario* us4 = ler_usuario(lista);

    grafo* g = criar_grafo(4);
    atualizar_grafo(g, lista);

    sugerir_amigos(g, "alberto");
    return 0;
}
