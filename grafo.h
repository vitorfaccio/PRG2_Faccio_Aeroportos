/*
 * grafo.h
 *
 *  Created on: Jul 5, 2016
 *      Author: Renan Augusto Starke
 */

#ifndef GRAFO_GRAFO_H_
#define GRAFO_GRAFO_H_

#include "vertice.h"
#include "pilha.h"
#include "fila.h"

typedef struct grafos grafo_t;

/* Cria um novo grafo com id */
grafo_t*		cria_grafo(int id);
vertice_t* 		grafo_adicionar_vertice(grafo_t *grafo, int id, aeroporto_t *aeroporto);
void 			adiciona_adjacentes(grafo_t *grafo, vertice_t *vertice, int n, ...);
vertice_t* 		procura_vertice(grafo_t *grafo, int id);
void 			exportar_grafo_dot(const char *filename, grafo_t *grafo);
void 			libera_grafo (grafo_t *grafo);

no_t*			busca_menos_distante(lista_enc_t *Q);
int 			busca_vertice(lista_enc_t *lista, vertice_t *vertice_procurado);
lista_enc_t*	componentes_conexos(grafo_t *grafo);

pilha_t* 		dijkstra(grafo_t *grafo, vertice_t *fonte, vertice_t *destino);
void 			bfs(grafo_t *grafo, vertice_t* inicial);
void 			dfs(grafo_t *grafo, vertice_t* inicial);
no_t*			obter_lista_vertices(grafo_t *grafo);
void 			teste_bfs (grafo_t * grafo, vertice_t * inicial);
void 			teste_dfs (grafo_t * grafo, vertice_t * inicial);

#endif /* GRAFO_GRAFO_H_ */
