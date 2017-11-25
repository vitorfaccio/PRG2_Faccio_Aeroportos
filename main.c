#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "arq_read.h"

int main()
{
    lista_enc_t* lista_vertices_aeroportos = ler_tabela("PRG2_Faccio_ListaAeroportos_v1.csv");
	aeroporto_t* aeroporto;
	grafo_t* grafo;
	grafo = cria_grafo(0);
	no_t* no_aeroporto = obter_cabeca(lista_vertices_aeroportos);
	while(no_aeroporto != NULL){
		grafo_adicionar_vertice(grafo,aeroporto_get_id(obter_dado(no_aeroporto)),obter_dado(no_aeroporto));
		no_aeroporto = obtem_proximo(no_aeroporto);
	}
/** Grafo criado! **/
int i = 0;

    no_t* no_grafo_1 = obter_lista_vertices(grafo);
    no_t* no_grafo_2;
    vertice_t* vertice;
    while(no_grafo_1 != NULL){
        vertice = obter_dado(no_grafo_1);
        no_grafo_2 = obter_lista_vertices(grafo);
        while(no_grafo_2 != NULL){
            if(obter_dado(no_grafo_2) != vertice)
                adiciona_adjacentes(grafo, vertice, obter_dado(no_grafo_2));
            no_grafo_2 = obtem_proximo(no_grafo_2);
        }
        no_grafo_1 = obtem_proximo(no_grafo_1);
    }
 /** 		Arestas criadas! 			**/
/** mas com pesos a serem arrumados... **/

	exportar_grafo_dot("grafo.dot", grafo);

    return 0;
}
