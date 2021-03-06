/*
 ============================================================================
 Nome        : grafo.c
 Autor		 : Vítor Faccio
 Versão	     : 2.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include "grafo.h"

#define FALSE 0
#define TRUE 1

#define INFINITO INT_MAX

#define RAIO_TERRA 	6372
#define CONST_PI	3.1415926536

//#define DEBUG

struct grafos {
	int id;
	int n_vertices;
	lista_enc_t *vertices;
};

no_t* busca_min_dist (lista_enc_t* lista)
{
	int dist_atual, dist_min = INFINITO - 1;
	no_t* no_distmin = NULL;
	no_t* no_vert = obter_cabeca(lista);
	while(no_vert != NULL){
		dist_atual = obtem_dist_dijkstra(obter_dado(no_vert));
		if(dist_atual <= dist_min){
			dist_min = dist_atual;
			no_distmin = no_vert;
		}
		no_vert = obtem_proximo(no_vert);
	}
	return no_distmin;
}

pilha_t * dijkstra(grafo_t *grafo, vertice_t* fonte, vertice_t* destino)
{
    if (grafo == NULL)	{
			fprintf(stderr,"dijkstra: grafo nulo!");
			exit(EXIT_FAILURE);
	}
	if (fonte == NULL)	{
			fprintf(stderr,"dijkstra: fonte nula!");
			exit(EXIT_FAILURE);
	}
	if (destino == NULL)	{
			fprintf(stderr,"dijkstra: destino nulo!");
			exit(EXIT_FAILURE);
	}

	lista_enc_t* lista_prioridade = cria_lista_enc();
	pilha_t* pilha_caminho = cria_pilha();

	int i, alt;
    no_t* no_aresta;
    no_t* no_vertice;
    arestas_t* aresta;
    vertice_t* vertice_v;

	modifica_dist_dijkstra(fonte,0);
	modifica_anterior_dijkstra(fonte,NULL);
	no_vertice = cria_no(fonte);
	add_cauda(lista_prioridade,no_vertice);

    for(i=1;i<=grafo->n_vertices;i++){
		if(procura_vertice(grafo,i) != fonte){
			modifica_dist_dijkstra(procura_vertice(grafo,i),INFINITO);
			modifica_anterior_dijkstra(procura_vertice(grafo,i),NULL);
			no_vertice = cria_no(procura_vertice(grafo,i));
			add_cauda(lista_prioridade,no_vertice);
		}
    }

	no_vertice = busca_min_dist(lista_prioridade);
	vertice_v = remover_no(lista_prioridade,no_vertice);
	while(no_vertice != NULL){
		modifica_visita_dijkstra(vertice_v,TRUE);

        no_aresta = obter_cabeca(vertice_get_arestas(vertice_v));
        if(no_aresta != NULL){
			aresta = obter_dado(no_aresta);
			while(no_aresta != NULL){
				if(obtem_visita_dijkstra(aresta_get_adjacente(aresta))== FALSE){
					alt = obtem_dist_dijkstra(vertice_v) + aresta_get_peso(aresta);
					if(alt < obtem_dist_dijkstra(aresta_get_adjacente(aresta))){
						modifica_dist_dijkstra(aresta_get_adjacente(aresta),alt);
						modifica_anterior_dijkstra(aresta_get_adjacente(aresta),vertice_v);
					}
				}
				no_aresta = obtem_proximo(no_aresta);
				if(no_aresta != NULL)
					aresta = obter_dado(no_aresta);
			}
		}
		no_vertice = busca_min_dist(lista_prioridade);
		if(no_vertice != NULL)
			vertice_v = remover_no(lista_prioridade,no_vertice);
	}

	vertice_v = destino;
	while(obtem_anterior_dijkstra(vertice_v) != NULL){
        push(vertice_v,pilha_caminho);
        vertice_v = obtem_anterior_dijkstra(vertice_v);
	}
    push(fonte,pilha_caminho);

	free(lista_prioridade);
    return pilha_caminho;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------

grafo_t *cria_grafo(int id)
{
	grafo_t *p = NULL;

	p = (grafo_t*) malloc(sizeof(grafo_t));

	if (p == NULL)	{
		perror("cria_grafo:");
		exit(EXIT_FAILURE);
	}

	p->id = id;
	p->n_vertices = 0;
	p->vertices = cria_lista_enc();

	return p;
}

vertice_t* grafo_adicionar_vertice(grafo_t *grafo, int id, aeroporto_t* aeroporto)
{
	vertice_t *vertice;
	no_t *no;

#ifdef DEBUG
	printf("grafo_adicionar_vertice: %d\n", id);
#endif

	if (grafo == NULL)	{
			fprintf(stderr,"grafo_adicionar_vertice: grafo invalido!");
			exit(EXIT_FAILURE);
	}

	if (procura_vertice(grafo, id) != NULL) {
		fprintf(stderr,"grafo_adicionar_vertice: vertice duplicado!\n");
		exit(EXIT_FAILURE);
	}

	vertice = cria_vertice(id,aeroporto);
	no = cria_no(vertice);

	add_cauda(grafo->vertices, no);
	grafo->n_vertices++;

	return vertice;
}

vertice_t* procura_vertice(grafo_t *grafo, int id)
{
	no_t *no_lista;
	vertice_t *vertice;
	int meu_id;

	if (grafo == NULL)	{
		fprintf(stderr,"procura_vertice: grafo invalido!");
		exit(EXIT_FAILURE);
	}

	if (lista_vazia(grafo->vertices) == TRUE)
		return FALSE;

	no_lista = obter_cabeca(grafo->vertices);

	while (no_lista)
	{
		//obtem o endereco da lista
		vertice = obter_dado(no_lista);

		//obterm o id do vertice
		meu_id = vertice_get_id(vertice);

		if (meu_id == id) {
			return vertice;
		}

		no_lista = obtem_proximo(no_lista);
	}

	return NULL;
}

void adiciona_adjacentes(grafo_t *grafo, vertice_t *vertice, vertice_t *sucessor, double dist)
{
	arestas_t *aresta;

	int id_sucessor;
	int peso;
	int x;

	peso = get_dificuldade_vertices(vertice, sucessor,dist);

	if (sucessor == NULL) {
		fprintf(stderr, "adiciona_adjacentes: sucessor nao encontrado no grafo\n");
		exit(EXIT_FAILURE);
	}

	aresta = cria_aresta(vertice, sucessor,peso,dist);
	adiciona_aresta(vertice, aresta);

#ifdef DEBUG
		printf("\tvertice: %d\n", vertice_get_id(vertice));
		printf("\tsucessor: %d\n", id_sucessor);
		printf("\tpeso: %d\n", peso);
#endif
}

void exportar_grafo_dot(const char *filename, grafo_t *grafo)
{
	FILE *file;

	no_t *no_vert;
	no_t *no_arest;
	vertice_t *vertice;
	vertice_t *adjacente;
	arestas_t *aresta;
	arestas_t *contra_aresta;
	lista_enc_t *lista_arestas;

	int peso;

	if (filename == NULL || grafo == NULL){
		fprintf(stderr, "exportar_grafp_dot: ponteiros invalidos\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "w");

	if (file == NULL){
		perror("exportar_grafp_dot:");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "graph {\n");

	//obtem todos os nos da lista
	no_vert = obter_cabeca(grafo->vertices);
	while (no_vert){
		vertice = obter_dado(no_vert);

		//obtem todos as arestas
		lista_arestas = vertice_get_arestas(vertice);

		no_arest = obter_cabeca(lista_arestas);
		while (no_arest) {
			aresta = obter_dado(no_arest);
			//ignora caso já exportada
			if (aresta_get_status(aresta) == EXPORTADA) {
				no_arest = obtem_proximo(no_arest);
				continue;
			}
			//marca como exportada esta aresta
			aresta_set_status(aresta, EXPORTADA);
			adjacente = aresta_get_adjacente(aresta);
			//marca contra-aresta também como exporta no caso de grafo não direcionados

			contra_aresta = procurar_adjacente(adjacente, vertice);
			aresta_set_status(contra_aresta, EXPORTADA); /**PROBLEMA AQUI, ARESTA NULA**/

			//obtem peso
			peso = aresta_get_peso(aresta);

			fprintf(file, "\t%d -- %d [label = %d];\n",
					vertice_get_id(vertice),
					vertice_get_id(adjacente),
					peso);

			no_arest = obtem_proximo(no_arest);
		}
		no_vert = obtem_proximo(no_vert);
	}
	fprintf(file, "}\n");
	fclose(file);
}

void libera_grafo (grafo_t *grafo){
	no_t *no_vert;
	no_t *no_arest;
	no_t *no_liberado;
	vertice_t *vertice;
	arestas_t *aresta;
	lista_enc_t *lista_arestas;

	if (grafo == NULL) {
		fprintf(stderr, "libera_grafo: grafo invalido\n");
		exit(EXIT_FAILURE);
	}

	//varre todos os vertices
	no_vert = obter_cabeca(grafo->vertices);
	while (no_vert){
		vertice = obter_dado(no_vert);

		//libera todas as arestas
		lista_arestas = vertice_get_arestas(vertice);
		no_arest = obter_cabeca(lista_arestas);
		while (no_arest){
			aresta = obter_dado(no_arest);

			//libera aresta
			free(aresta);

			//libera no da lsita
			no_liberado = no_arest;
			no_arest = obtem_proximo(no_arest);
			free(no_liberado);
		}

		//libera lista de arestas e vertice
		free(lista_arestas);
		free(vertice);

		//libera no da lista
		no_liberado = no_vert;
		no_vert = obtem_proximo(no_vert);
		free(no_liberado);
	}

	//libera grafo e vertice
	free(grafo->vertices);
	free(grafo);
}

no_t * obter_lista_vertices(grafo_t *grafo)
{
	if (grafo == NULL)	{
			fprintf(stderr,"obter_lista_vertices: grafo invalido!");
			exit(EXIT_FAILURE);
	}

    no_t* cabeca_lista = obter_cabeca(grafo->vertices);

	return cabeca_lista;
}

lista_enc_t * obter_lista_enc_vertices(grafo_t *grafo)
{
	if (grafo == NULL)	{
			fprintf(stderr,"obter_lista_vertices: grafo invalido!");
			exit(EXIT_FAILURE);
	}

	return grafo->vertices;
}

int obter_grafo_size(grafo_t *grafo)
{
	if (grafo == NULL)	{
			fprintf(stderr,"grafo_obter_size: grafo invalido!");
			exit(EXIT_FAILURE);
	}

	return grafo->n_vertices;
}

int get_dificuldade_vertices(vertice_t *vertice_1, vertice_t *vertice_2, double dist)
{
	double movimento = (double)(aeroporto_get_movimento(obtem_aeroporto(vertice_1))) +
					   (double)(aeroporto_get_movimento(obtem_aeroporto(vertice_2)));
	movimento /= 10000;						/**	CARECE DE AJUSTES **/

	//dist += dist/movimento;	/**	CARECE DE AJUSTES **/

	return (int)dist;
}

double haversine(double latitude_1, double longitude_1, double latitude_2, double longitude_2)
{
	latitude_1 *= CONST_PI/180;
	latitude_2 *= CONST_PI/180;
	longitude_1 *= CONST_PI/180;
	longitude_2 *= CONST_PI/180;
	double dist = RAIO_TERRA;

	dist *= acos(sin(latitude_1)*sin(latitude_2) + cos(latitude_1)*cos(latitude_2)*cos(longitude_1-longitude_2));

	return dist;
}

void libera_full(lista_enc_t* lista_vertices_aeroportos,lista_enc_t* lista_aeronaves,grafo_t* grafo,void* info,pilha_t* pilha)
{//										OK								OK					OK			 OK
// Libera lista de vértices de aeroportos:
	no_t* no_2;
	no_t* no_1 = obter_cabeca(lista_vertices_aeroportos);
	vertice_t* vertice_1;
	while(no_1 != NULL){
		libera_aeroporto(obter_dado(no_1));
		no_2 = no_1;
		no_1 = obtem_proximo(no_1);
		free(no_2);
	}
	free(lista_vertices_aeroportos);

	no_1 = obter_cabeca(lista_aeronaves);
	while(no_1 != NULL){
		libera_aeronave(obter_dado(no_1));
		no_2 = no_1;
		no_1 = obtem_proximo(no_1);
		free(no_2);
	}
	free(lista_vertices_aeroportos);

	libera_grafo(grafo);

	free(info);

	libera_pilha(pilha);

}

