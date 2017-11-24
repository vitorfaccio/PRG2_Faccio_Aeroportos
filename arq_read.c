/*
 ============================================================================
 Name        : arq_read.c
 Author      : Vítor Faccio
 Version     : 1.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 : Leitura da planilha em .ods com as informações dos aeroportos
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arq_read.h"

struct dados_aeroporto {
	int id;
	char *nome;
	char *code;
	char *pais;
	char *cidade;
	int mov_anual;
	int coord_latitude[3];
	char char_lat;
	int coord_longitude[3];
	char char_long;
	float latitude;
	float longitude;
};

lista_enc_t * ler_tabela(char * arquivo)
{
	char buffer[TAM_BUFFER_G];

	int id = 9, mov_anual, coord_latitude[3], coord_longitude[3];
	char buffer_nome[TAM_BUFFER_M], code[TAM_BUFFER_PP], pais[TAM_BUFFER_P], cidade[TAM_BUFFER_P], char_lat, char_long;
	float latitude, longitude;
	int ret = 0;

	FILE *fp;
    lista_enc_t *lista;
    no_t *no;
    aeroporto_t *aeroporto;

	fp = fopen(arquivo, "r");

	if (fp == NULL){
		perror("ler_arquivo");
		exit(EXIT_FAILURE);
	}

	lista = cria_lista_enc();
	fgets(buffer,TAM_BUFFER_G,fp);
	while(fgets(buffer,TAM_BUFFER_G,fp) != 0)
	{
		ret = sscanf(buffer, "%d,%100[^,],%10[^,],%50[^,],%50[^,],%d,\042%d\052 %d' %d\042\042 %c\042,\042%d\052 %d' %d\042\042 %c\042\n",
			&id,buffer_nome,code,pais,cidade,&mov_anual,coord_latitude,(coord_latitude+1),(coord_latitude+2),&char_lat,
			coord_longitude,(coord_longitude+1),(coord_longitude+2),&char_long);

		if (ret != 14) {
			fprintf(stderr, "Arquivo de entrada invalido\n");
			exit(EXIT_FAILURE);
		}
		aeroporto = cria_aeroporto(id,buffer_nome,code,pais,cidade,mov_anual,coord_latitude,char_lat,coord_longitude,char_long);
		no = cria_no(aeroporto);
		add_cauda(lista,no);
	}

	fclose(fp);
	return lista;
}

aeroporto_t * cria_aeroporto(int id, char * buffer_nome, char * code, char * pais, char * cidade, int mov_anual, int * coord_latitude, char char_lat, int * coord_longitude, char char_long)
{
	aeroporto_t * p = malloc(sizeof(aeroporto_t));
	if (p == NULL){

		perror("cria_aeroporto (struct)");
		exit(EXIT_FAILURE);
	}
// ID:
	p->id = id;

// Nome:
	p->nome = malloc(strlen(buffer_nome)+1);
	if (p == NULL){
		perror("cria_aeroporto (nome)");
		exit(EXIT_FAILURE);
	}
	strncpy(p->nome, buffer_nome, strlen(buffer_nome) + 1);

// Code:
	p->code = malloc(strlen(code)+1);
	if (p == NULL){
		perror("cria_aeroporto (code)");
		exit(EXIT_FAILURE);
	}
	strncpy(p->code, code, strlen(code) + 1);

// Pais:
	p->pais = malloc(strlen(pais)+1);
	if (p == NULL){
		perror("cria_aeroporto (pais)");
		exit(EXIT_FAILURE);
	}
	strncpy(p->pais, pais, strlen(pais) + 1);

// Cidade:
	p->cidade = malloc(strlen(cidade)+1);
	if (p == NULL){
		perror("cria_aeroporto (cidade)");
		exit(EXIT_FAILURE);
	}
	strncpy(p->cidade, cidade, strlen(cidade) + 1);

// Movimento anual:
	p->mov_anual = mov_anual;

// Coordenadas de latitude:
	p->coord_latitude[0] = coord_latitude[0];
	p->coord_latitude[1] = coord_latitude[1];
	p->coord_latitude[2] = coord_latitude[2];
	p->char_lat = char_lat;

// Coordenadas de longitude:
	p->coord_longitude[0] = coord_longitude[0];
	p->coord_longitude[1] = coord_longitude[1];
	p->coord_longitude[2] = coord_longitude[2];
	p->char_long = char_long;

// Latitude exata:
	p->latitude = (float)coord_latitude[0] + ((float)coord_latitude[1])/60 + ((float)coord_latitude[2])/3600;
	switch(char_lat){
	case 'S':
		p->latitude *= -1;
		break;
	case 'N':
		break;
	default:
		perror("cria_aeroporto: char_lat indevido");
	}

// Longitude exata:
	p->longitude = (float)coord_longitude[0] + ((float)coord_longitude[1])/60 + ((float)coord_longitude[2])/3600;
	switch(char_long){
	case 'W':
		p->longitude *= -1;
		break;
	case 'E':
		break;
	default:
		perror("cria_aeroporto: char_long indevido");
	}

	return p;
}

/***********************************/
/***********************************/
/***********************************/
/** FUNÇÕES DE RETORNO DE VALORES **/
/***********************************/
/***********************************/
/***********************************/

int aeroporto_get_id(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_id: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->id;
}

char * aeroporto_get_nome(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_nome: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->nome;
}

char * aeroporto_get_code(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_code: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->code;
}

char * aeroporto_get_pais(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_pais: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->pais;
}

char * aeroporto_get_cidade(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_cidade: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->cidade;
}

int aeroporto_get_movimento(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_movimento: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->mov_anual;
}

int * aeroporto_get_coord_lat(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_coord_lat: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->coord_latitude;
}

char aeroporto_get_char_lat(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_char_lat: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->char_lat;
}


int * aeroporto_get_coord_long(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_coord_long: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->coord_longitude;
}

char aeroporto_get_char_long(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_char_long: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->char_long;
}

float aeroporto_get_latitude(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_latitude: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->latitude;
}

float aeroporto_get_longitude(aeroporto_t * aeroporto)
{
	if (aeroporto == NULL){
		perror("aeroporto_get_longitude: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	return aeroporto->longitude;
}
