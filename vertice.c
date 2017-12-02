/*
 ============================================================================
 Nome        : vertice.c
 Autor		 : Renan Starke - Modificado por Vítor Faccio
 Versão	     : 2.0
 Copyright   : Renan Starke, todos os direitos reservados
 Descrição	 :
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "vertice.h"

#define FALSE 0
#define TRUE 1

struct vertices {
	int id;
	aeroporto_t *aeroporto;
	int estado_visitavel;
	lista_enc_t *arestas;

	/* Informações para busca em largura */
	int dist_larg;
    vertice_t* pai_larg;

    /* Informações para busca em profundidade */
    int visita_prof;

	/* Informacoes para componentes conexos */
	int id_grupo;
	vertice_t* pai;

	/* Informacoes para Dijkstra */
	int dist_dijkstra;
	vertice_t* anterior_dijkstra;
	int visita_dijkstra;
};

struct arestas {
	int peso;
	double dist;
	vertice_t *fonte;
	vertice_t *dest;

	/* status para expotacao em arquivo */
	status_aresta_t status;
};

//////////////////////////////////////////////////////////////FUNÇÕES MINHAS, ESTÃO NO MEIO PRA ACESSAR MAIS FÁCIL
void modifica_dist(vertice_t* vertice, int dist)
{
    if (vertice == NULL){
		fprintf(stderr, "modifica_dist: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->dist_larg = dist;
}

void modifica_pai(vertice_t* vertice, vertice_t* pai)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_pai: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->pai_larg = pai;
}

void modifica_visita(vertice_t* vertice, int n)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_visita: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->visita_prof = n;
}

void modifica_dist_dijkstra(vertice_t* vertice, int n)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_dist_dijkstra: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->dist_dijkstra = n;
}

void modifica_anterior_dijkstra(vertice_t* vertice, vertice_t* anterior)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_anterior_dijkstra: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->anterior_dijkstra = anterior;
}

void modifica_aeroporto(vertice_t* vertice, aeroporto_t* aeroporto)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_aeroporto: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->aeroporto = aeroporto;
}

void modifica_visita_dijkstra(vertice_t* vertice, int n)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_visita_dijkstra: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->visita_dijkstra = n;
}

void modifica_estado_visitavel(vertice_t* vertice, int n)
{
	if (vertice == NULL){
		fprintf(stderr, "modifica_estado_visitavel: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    vertice->estado_visitavel = n;
}

int obtem_dist_dijkstra(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_dist_dijkstra: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    return vertice->dist_dijkstra;
}

int obtem_dist(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_dist: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    return vertice->dist_larg;
}

vertice_t * obtem_pai(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_pai: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

    return vertice->pai_larg;
}

int obtem_visita(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_visita: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertice->visita_prof;
}

int obtem_visita_dijkstra(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_visita_dijkstra: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertice->visita_dijkstra;
}

vertice_t * obtem_anterior_dijkstra(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_anterior_dijkstra: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertice->anterior_dijkstra;
}

aeroporto_t * obtem_aeroporto(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_aeroporto: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertice->aeroporto;
}

int obtem_estado_visitavel(vertice_t* vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "obtem_estado_visitavel: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertice->estado_visitavel;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vertice_t *cria_vertice(int id, aeroporto_t* aeroporto)
{
	vertice_t *p = NULL;

	p = malloc(sizeof(vertice_t));

	if (p == NULL) {
		perror("cria_vertice:");
		exit(EXIT_FAILURE);
	}

	p->id = id;
	p->aeroporto = aeroporto;
	p->estado_visitavel = FALSE;
	p->arestas = cria_lista_enc();
	p->id_grupo = -1;
	p->pai = NULL;
	p->visita_dijkstra = FALSE;

	return p;
}

int vertice_get_id(vertice_t *vertice)
{
	if (vertice == NULL)
	{
		fprintf(stderr, "vertice_obter_id: vertice invalido!\n");
		exit(EXIT_FAILURE);
	}

	return vertice->id;
}

arestas_t *cria_aresta(vertice_t *fonte, vertice_t *destino, int peso, double dist)
{
	arestas_t *p;

	p = (arestas_t*)malloc(sizeof(arestas_t));

	if (p == NULL) {
		perror("cria_aresta:");
		exit(EXIT_FAILURE);
	}

	p->peso = peso;
	p->fonte = fonte;
	p->dest = destino;
	p->dist = dist;

	return p;
}

void adiciona_aresta(vertice_t *vertice, arestas_t *aresta)
{
	no_t *no;

	if (vertice == NULL || aresta == NULL)	{
		fprintf(stderr, "adiciona_aresta: dados invalidos\n");
		exit(EXIT_FAILURE);
	}

	no = cria_no(aresta);
	add_cauda(vertice->arestas, no);

}

void aresta_set_dist(arestas_t *aresta, double dist)
{
	if (aresta == NULL){
		fprintf(stderr, "aresta_set_dist: aresta invalida\n");
		exit(EXIT_FAILURE);
	}

	aresta->dist = dist;
}

lista_enc_t *vertice_get_arestas(vertice_t *vertice)
{
	if (vertice == NULL){
		fprintf(stderr, "vertice_get_arestas: vertice invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertice->arestas;
}

int aresta_get_peso (arestas_t *aresta) {
	if (aresta == NULL){
		fprintf(stderr, "aresta_get_peso: aresta invalida\n");
		exit(EXIT_FAILURE);
	}

	return aresta->peso;
}

double aresta_get_dist (arestas_t *aresta){
	if (aresta == NULL){
		fprintf(stderr, "aresta_get_dist: aresta invalida\n");
		exit(EXIT_FAILURE);
	}

	return aresta->dist;
}

vertice_t *aresta_get_fonte(arestas_t *aresta)
{
	if (aresta == NULL){
		fprintf(stderr, "aresta_get_fonte: aresta invalido\n");
		exit(EXIT_FAILURE);
	}

	return aresta->fonte;
}

vertice_t *aresta_get_adjacente(arestas_t *aresta)
{
	if (aresta == NULL){
		fprintf(stderr, "aresta_get_adjacente: aresta invalido\n");
		exit(EXIT_FAILURE);
	}

	return aresta->dest;
}

arestas_t *procurar_adjacente(vertice_t *vertice, vertice_t *adjacente)
{
	no_t *no;
	arestas_t *aresta;

	if (vertice == NULL){
		fprintf(stderr, "procurar_adjacente: aresta invalido\n");
		exit(EXIT_FAILURE);
	}

	no = obter_cabeca(vertice->arestas);

	while (no){

		aresta = obter_dado(no);

		if (aresta->dest == adjacente || aresta->fonte == adjacente)
			return aresta;

		no = obtem_proximo(no);
	}

	return NULL;
}

status_aresta_t aresta_get_status (arestas_t *aresta)
{
	if (aresta == NULL){
		fprintf(stderr, "aresta_get_status: aresta invalida\n");
		exit(EXIT_FAILURE);
	}

	return aresta->status;
}

void aresta_set_status(arestas_t *aresta, status_aresta_t status)
{
	if (aresta == NULL){
		fprintf(stderr, "aresta_set_status: aresta invalida\n");
		exit(EXIT_FAILURE);
	}

	aresta->status = status;
}

/*------------------------------------------*/
void vertice_set_grupo(vertice_t *vertice, int grupo) {

	if (vertice == NULL){
			fprintf(stderr, "vertice_set_grupo: vertice invalido\n");
			exit(EXIT_FAILURE);
	}

	vertice->id_grupo = grupo;
}

int vertice_get_grupo(vertice_t *vertice) {

	if (vertice == NULL){
			fprintf(stderr, "vertice_get_grupo: vertice invalido\n");
			exit(EXIT_FAILURE);
	}

	return vertice->id_grupo;
}

void vertice_set_pai(vertice_t *vertice, vertice_t *pai) {

	if (vertice == NULL){
			fprintf(stderr, "vertice_set_pai: vertice invalido\n");
			exit(EXIT_FAILURE);
	}

	vertice->pai = pai;
}
