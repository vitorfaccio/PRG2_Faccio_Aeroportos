/*
 * grafo.c
 *
 *  Created on: Jul 5, 2016
 *      Author: Renan Augusto Starke
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "grafo.h"
#include "vertice.h"

#define FALSE 0
#define TRUE 1

#define INFINITO INT_MAX

//#define DEBUG

struct grafos {
	int id;
	int n_vertices;
	lista_enc_t *vertices;
};

pilha_t * dijkstra(grafo_t *grafo, vertice_t* fonte, vertice_t* destino)
{
    if (grafo == NULL)	{
			fprintf(stderr,"dijkstra: grafo invalido!");
			exit(EXIT_FAILURE);
	}

	fila_t* fila_prioridade = cria_fila();
	pilha_t* pilha_caminho = cria_pilha();

	int i, alt;
    no_t* no_aresta;
    arestas_t* aresta;
    vertice_t* vertice_v;

	modifica_dist_dijkstra(fonte,0);
	modifica_anterior_dijkstra(fonte,NULL);
	enqueue(fonte,fila_prioridade);

    for(i=1;i<=grafo->n_vertices;i++){
		if(procura_vertice(grafo,i) != fonte){
			modifica_dist_dijkstra(procura_vertice(grafo,i),INFINITO);
			modifica_anterior_dijkstra(procura_vertice(grafo,i),NULL);
			enqueue(procura_vertice(grafo,i),fila_prioridade);
		}
    }

	while(fila_vazia(fila_prioridade) == FALSE){
		vertice_v = dequeue(fila_prioridade);
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
	}


	vertice_v = destino;
	while(obtem_anterior_dijkstra(vertice_v) != NULL){
        push(vertice_v,pilha_caminho);
        vertice_v = obtem_anterior_dijkstra(vertice_v);
	}
    push(fonte,pilha_caminho);

	libera_fila(fila_prioridade);
    return pilha_caminho;

}

void bfs(grafo_t *grafo, vertice_t* inicial)        // Busca em largura         - FILA
{
    fila_t* fila = cria_fila();
    vertice_t* vertice_busca;
    vertice_t* vertice_adjacente;

    no_t* no_verticeatual = obter_cabeca(grafo->vertices);
    no_t* no_aresta;

    while(no_verticeatual != NULL){
        modifica_dist(obter_dado(no_verticeatual),INFINITO);
        modifica_pai(obter_dado(no_verticeatual),NULL);
        no_verticeatual = obtem_proximo(no_verticeatual);
    }

    modifica_dist(inicial,0);
    enqueue(inicial,fila);

    while(fila_vazia(fila) == FALSE){
        vertice_busca = dequeue(fila);
        //explorar lista de arestas
        no_aresta = obter_cabeca(vertice_get_arestas(vertice_busca));
        while(no_aresta != NULL){
            vertice_adjacente = aresta_get_adjacente(obter_dado(no_aresta));
            if(obtem_dist(vertice_adjacente) == INFINITO){
                modifica_dist(vertice_adjacente,obtem_dist(vertice_busca)+1);
                modifica_pai(vertice_adjacente,vertice_busca);
                enqueue(vertice_adjacente,fila);
            }
            no_aresta = obtem_proximo(no_aresta);
        }
    }
}

void dfs(grafo_t *grafo, vertice_t* inicial)        // Busca em profundidade    - PILHA
{
	pilha_t* pilha = cria_pilha();
    vertice_t* vertice_busca;
    vertice_t* vertice_adjacente;

    no_t* no_verticeatual = obter_cabeca(grafo->vertices);
    no_t* no_aresta;

	while(no_verticeatual != NULL){
        modifica_visita(obter_dado(no_verticeatual),0);
        no_verticeatual = obtem_proximo(no_verticeatual);
    }

	push(inicial,pilha);
	while(pilha_vazia(pilha) == FALSE){
		vertice_busca = pop(pilha);
		if(obtem_visita(vertice_busca) == 0){
			modifica_visita(vertice_busca,1);

			//Para todo v adjacente:
			no_aresta = obter_cabeca(vertice_get_arestas(vertice_busca));
			while(no_aresta != NULL){
				vertice_adjacente = aresta_get_adjacente(obter_dado(no_aresta));
				push(vertice_adjacente,pilha);
				no_aresta = obtem_proximo(no_aresta);
			}
		}
	}
}

no_t * obter_lista_vertices(grafo_t *grafo)
{
	if (grafo == NULL)	{
			fprintf(stderr,"grafo_adicionar_vertice: grafo invalido!");
			exit(EXIT_FAILURE);
	}

	return grafo->vertices;
}

void teste_bfs (grafo_t * grafo, vertice_t * inicial)
{
	no_t* no_vertice = obter_cabeca(obter_lista_vertices(grafo));
	vertice_t* vertice = obter_dado(no_vertice);
	bfs(grafo,inicial);
	printf("Analise de busca em largura, vertice inicial: %d ",vertice_get_id(inicial));

	while(vertice != NULL){
		if((obtem_dist(vertice) != INFINITO) && (vertice != inicial)){
			printf("\nVertice %d , endereco 0x%X:",
				vertice_get_id(vertice),
				vertice);
			printf("\n\tDistancia:%d \n\tPai: %d, endereco 0x%X \n",
				obtem_dist(vertice),
				vertice_get_id(obtem_pai(vertice)),
				obtem_pai(vertice));
		}
		no_vertice = obtem_proximo(no_vertice);
		vertice = obter_dado(no_vertice);
	}
}

void teste_dfs (grafo_t * grafo, vertice_t * inicial)
{
	no_t* no_vertice = obter_cabeca(obter_lista_vertices(grafo));
	vertice_t* vertice = obter_dado(no_vertice);
	dfs(grafo,inicial);
	printf("Analise de busca em profundidade, vertice inicial: %d ",vertice_get_id(inicial));

	while(vertice != NULL){
		if((obtem_visita(vertice) == 1) && (vertice != inicial)){
			printf("\nVertice %d , endereco 0x%X:",
				vertice_get_id(vertice),
				vertice);
			printf("\n\tVisitado!\n");		// Tem coisa a melhorar aí, só dizer que foi visitado não adianta tanto
		}
		no_vertice = obtem_proximo(no_vertice);
		vertice = obter_dado(no_vertice);
	}
}
//--------------------------------------------------------------------------------------

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

void adiciona_adjacentes(grafo_t *grafo, vertice_t *vertice, int n, ...)
{
	va_list argumentos;
	vertice_t *sucessor;
	arestas_t *aresta;

	int id_sucessor;
	int peso;
        int x;

	/* Initializing arguments to store all values after num */
	va_start (argumentos, n);

	for (x = 0; x < n; x=x+2 )
	{
		id_sucessor = va_arg(argumentos, int);
		peso = va_arg(argumentos, int);

		sucessor = procura_vertice(grafo, id_sucessor);

		if (sucessor == NULL) {
			fprintf(stderr, "adiciona_adjacentes: sucessor nao encontrado no grafo\n");
			exit(EXIT_FAILURE);
		}

		aresta = cria_aresta(vertice, sucessor,peso);
		adiciona_aresta(vertice, aresta);

#ifdef DEBUG
		printf("\tvertice: %d\n", vertice_get_id(vertice));
		printf("\tsucessor: %d\n", id_sucessor);
		printf("\tpeso: %d\n", peso);
#endif

	}

	va_end (argumentos);
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
