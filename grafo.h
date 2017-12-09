/*
 ============================================================================
 Nome        : grafo.h
 Autor		 : Vítor Faccio
 Versão	     : 2.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 :
 ============================================================================
 */

#ifndef GRAFO_GRAFO_H_
#define GRAFO_GRAFO_H_

#include "info_voo.h"
#include "arq_read.h"

#include "vertice.h"
#include "pilha.h"
#include "fila.h"
#include "lista_enc.h"

typedef struct grafos grafo_t;

/* Cria um novo grafo com id */
grafo_t*		cria_grafo(int id);
vertice_t* 		grafo_adicionar_vertice(grafo_t *grafo, int id, aeroporto_t *aeroporto);
void 			adiciona_adjacentes(grafo_t *grafo, vertice_t *vertice, vertice_t *sucessor, double dist);
vertice_t* 		procura_vertice(grafo_t *grafo, int id);
void 			exportar_grafo_dot(const char *filename, grafo_t *grafo);
void 			libera_grafo (grafo_t *grafo);
no_t*			obter_lista_vertices(grafo_t *grafo);
lista_enc_t*	obter_lista_enc_vertices(grafo_t *grafo);
int 			get_dificuldade_vertices(vertice_t *vertice_1, vertice_t *vertice_2, double dist);
double 			haversine(double latitude_1, double longitude_1, double latitude_2, double longitude_2);

no_t*			busca_menos_distante(lista_enc_t *Q);
int 			busca_vertice(lista_enc_t *lista, vertice_t *vertice_procurado);
lista_enc_t*	componentes_conexos(grafo_t *grafo);

no_t* 			busca_min_dist (lista_enc_t* lista);
pilha_t* 		dijkstra(grafo_t *grafo, vertice_t *fonte, vertice_t *destino);

void 			libera_full(lista_enc_t* lista_vertices_aeroportos,lista_enc_t* lista_aeronaves,grafo_t* grafo,void* info,pilha_t* pilha);

#endif /* GRAFO_GRAFO_H_ */
