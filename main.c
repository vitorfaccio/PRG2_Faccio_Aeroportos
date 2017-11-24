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
int i = 0;

	no_t* no_aeroporto = obter_cabeca(lista_vertices_aeroportos);

	while(no_aeroporto != NULL){
		grafo_adicionar_vertice(grafo,aeroporto_get_id(obter_dado(no_aeroporto)),obter_dado(no_aeroporto));
		no_aeroporto = obtem_proximo(no_aeroporto);
	}

	for(i=1;i<=10;i++){
		adiciona_adjacentes(grafo,procura_vertice(grafo,i),2,i+1,3);
	}

	exportar_grafo_dot("grafo.dot", grafo);

    return 0;
}
