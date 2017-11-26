/*
 ============================================================================
 Nome        : info_voo.c
 Autor		 : Vítor Faccio
 Versão	     : 1.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "info_voo.h"

struct informacoes {
	/** O voo dependerá de uma série de detalhes fornecidos pelo usuário. Dentre elas são: **/
	aeronave_t *aeronave;
	aeroporto_t *origem;
	aeroporto_t *destino;
};

info_t * cria_info(void *pointer)		// G a m b i a r r a
{
	grafo_t *grafo = pointer;

	if (grafo == NULL) {
		perror("cria_info: grafo nulo");
		exit(EXIT_FAILURE);
	}

	info_t *p = NULL;
	p = malloc(sizeof(info_t));

	if (p == NULL) {
		perror("cria_info: malloc");
		exit(EXIT_FAILURE);
	}

	int id_origem, id_destino, id_aeronave;


	/** Inicializar a comunicação e fornecer lista de aeroportos: **/
	printf("Seja bem vindo, usuario! Abaixo esta' a lista de aeroportos disponiveis, listados por numero de ID, codigo, cidade e pais.\n\n");
	no_t* no_aeroporto = obter_lista_vertices(grafo);
	vertice_t* vertice_aeroporto;
	aeroporto_t* aeroporto;
	while(no_aeroporto != NULL){
		vertice_aeroporto = obter_dado(no_aeroporto);
		aeroporto = obtem_aeroporto(vertice_aeroporto);
		printf("\t%d - %s: %s, %s\n",aeroporto_get_id(aeroporto),aeroporto_get_code(aeroporto),
				aeroporto_get_cidade(aeroporto),aeroporto_get_pais(aeroporto));
		no_aeroporto = obtem_proximo(no_aeroporto);
	}

	/** Receber o aeroporto de origem: **/
	printf("Digite o ID do aeroporto de origem.\n");
	scanf("%d",&id_origem);
	id_destino = id_origem;
	p->origem = obtem_aeroporto(procura_vertice(grafo,id_origem));

	/** Receber o aeroporto de destino: **/
	printf("\nDigite o ID do aeroporto de Destino.\n");
	while(1){
		scanf("%d",&id_destino);
		if(id_destino != id_origem)
			break;
		printf("ID invalido, voce selecionou o proprio aeroporto de origem. Reinsira o aeroporto de destino.\n");
	}
	p->destino = obtem_aeroporto(procura_vertice(grafo,id_destino));

	/** Receber o avião utilizado: **/
	printf("Abaixo sao listados os avioes disponiveis para seu voo, com a respectiva autonomia de cada um.\n");
	lista_enc_t* lista_aeronaves = ler_tabela_aeronaves("PRG2_Faccio_ListaAeronaves_v1.csv");
	no_t* no_aeronave = obter_cabeca(lista_aeronaves);

	aeronave_t* aeronave;
	while(no_aeronave != NULL){
		aeronave = obter_dado(no_aeronave);
		printf("\t%d - %s: %d km\n",aeronave_obter_id(aeronave),aeronave_obter_nome(aeronave),
				aeronave_obter_autonomia(aeronave));
		no_aeronave = obtem_proximo(no_aeronave);
	}

	/** Receber a aeronave utilizada: **/
	printf("\nDigite o ID da aeronave a ser utilizada.\n");
	scanf("%d",&id_aeronave);

	no_aeronave = obter_cabeca(lista_aeronaves);
	while(no_aeronave != NULL){
		if(aeronave_obter_id(obter_dado(no_aeronave)) == id_aeronave){
			p->aeronave = obter_dado(no_aeronave);
			break;
		}
		no_aeronave = obtem_proximo(no_aeronave);
	}

	return p;
}

aeronave_t* info_obter_aeronave(info_t *info)
{
	if (info == NULL)	{
			fprintf(stderr,"info_obter_aeronave: info invalida!");
			exit(EXIT_FAILURE);
	}

	return info->aeronave;
}

aeroporto_t* info_obter_origem(info_t *info)
{
	if (info == NULL)	{
			fprintf(stderr,"info_obter_origem: info invalida!");
			exit(EXIT_FAILURE);
	}

	return info->origem;
}

aeroporto_t* info_obter_destino(info_t *info)
{
	if (info == NULL)	{
			fprintf(stderr,"info_obter_destino: info invalida!");
			exit(EXIT_FAILURE);
	}

	return info->destino;
}
