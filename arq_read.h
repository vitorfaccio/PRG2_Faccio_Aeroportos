/*
 ============================================================================
 Nome        : arq_read.h
 Autor		 : V�tor Faccio
 Vers�o	     : 2.0
 Copyright   : V�tor Faccio, todos os direitos reservados
 Descri��o	 : Leitura da planilha em .ods com as informa��es dos aeroportos

 L� o arquivo que cont�m as informa��es necess�rias e os guarda num conjunto
 de v�rtices. Retorna este conjunto a quem chamar a fun��o.
 ============================================================================
 */

#ifndef ARQ_READ_H_INCLUDED
#define ARQ_READ_H_INCLUDED

#include "lista_enc.h"

typedef struct dados_aeroporto 	aeroporto_t;
typedef struct dados_aeronave 	aeronave_t;

lista_enc_t * ler_tabela_aeroportos(char * arquivo);
lista_enc_t * ler_tabela_aeronaves(char * arquivo);
aeroporto_t * cria_aeroporto(int id, char * buffer_nome, char * code, char * pais, char * cidade, int mov_anual, int * coord_latitude, char char_lat, int * coord_longitude, char char_long);
aeronave_t * cria_aeronave(int id, char * buffer_nome, int autonomia);

/** Fun��es de retorno **/

int 	aeroporto_get_id(aeroporto_t * aeroporto);
char* 	aeroporto_get_nome(aeroporto_t * aeroporto);
char* 	aeroporto_get_code(aeroporto_t * aeroporto);
char* 	aeroporto_get_pais(aeroporto_t * aeroporto);
char* 	aeroporto_get_cidade(aeroporto_t * aeroporto);
int 	aeroporto_get_movimento(aeroporto_t * aeroporto);
char* 	aeroporto_get_code(aeroporto_t * aeroporto);
int* 	aeroporto_get_coord_lat(aeroporto_t * aeroporto);
char 	aeroporto_get_char_lat(aeroporto_t * aeroporto);
int* 	aeroporto_get_coord_long(aeroporto_t * aeroporto);
char 	aeroporto_get_char_long(aeroporto_t * aeroporto);
double 	aeroporto_get_latitude(aeroporto_t * aeroporto);
double 	aeroporto_get_longitude(aeroporto_t * aeroporto);

int aeronave_obter_id(aeronave_t* aeronave);
char* aeronave_obter_nome(aeronave_t* aeronave);
int aeronave_obter_autonomia(aeronave_t* aeronave);

#endif // ARQ_READ_H_INCLUDED
