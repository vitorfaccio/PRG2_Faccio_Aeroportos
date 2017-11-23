/*
 ============================================================================
 Name        : main.c
 Author      : Vítor Faccio
 Version     : 1.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Description : Algoritmo de Dijkstra para encontro de caminho mínimo
             : Estrutura de dados: grafo com listas encadeadas
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void) {

	grafo_t *grafo;
	vertice_t* vertice;

no_t* no_vertice;

	fila_t *fila;
	int id;

	grafo = cria_grafo(0);
	fila = cria_fila();

	//Adiciona todos os vertices no grafo
	vertice = grafo_adicionar_vertice(grafo, 1);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo, 2);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo, 3);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo, 4);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo, 5);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo, 6);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo,7);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo,8);
	enqueue(vertice, fila);

	vertice = grafo_adicionar_vertice(grafo,9);
	enqueue(vertice, fila);

        // constrói grafo
	while (!fila_vazia(fila))	{
		vertice = dequeue(fila);
		id = vertice_get_id(vertice);

		switch(id){
			case 1:
				adiciona_adjacentes(grafo, vertice, 10, 6, 14, 2, 7, 3, 9, 7, 12, 9, 4);
				break;
			case 2:
				adiciona_adjacentes(grafo, vertice, 10, 1, 7, 3, 10, 4, 15, 6, 4, 8, 13);
				break;
			case 3:
				adiciona_adjacentes(grafo, vertice, 12, 1, 9, 2, 10, 6, 2, 4, 11, 7, 12, 9, 3);
				break;
			case 4:
				adiciona_adjacentes(grafo, vertice, 10, 2, 15, 3, 11, 5, 6, 7, 10, 6, 8);
				break;
			case 5:
				adiciona_adjacentes(grafo, vertice, 8, 4, 6, 6, 9, 7, 12, 8, 7);
				break;
			case 6:
				adiciona_adjacentes(grafo, vertice, 12, 1, 14, 2, 4, 3, 2, 4, 8, 5, 9, 8, 6);
				break;
			case 7:
				adiciona_adjacentes(grafo, vertice, 8, 1, 12, 3, 12, 4, 10, 5, 12);
				break;
			case 8:
				adiciona_adjacentes(grafo, vertice, 6, 2, 13, 5, 7, 6, 6);
				break;
			case 9:
				adiciona_adjacentes(grafo, vertice, 4, 1, 4, 3, 3);
				break;
			default:
				break;
		}
	}

	exportar_grafo_dot("lista_grafo.dot", grafo);
//  Ordenação
//	exportar_grafo_dot("grafo.dot", grafo);

    pilha_t* pilha = dijkstra(grafo,procura_vertice(grafo,7),procura_vertice(grafo,2));
    vertice_t* vert;
    int i = 1;

    printf("Menor caminho de 7 a 2: \n");
    while(pilha_vazia(pilha) == 0){
        vert = pop(pilha);
        printf("Vertice %d: %d \n",i++,vertice_get_id(vert));
    }

	libera_pilha(pilha);
	libera_fila(fila);
	libera_grafo(grafo);

	return EXIT_SUCCESS;
}

