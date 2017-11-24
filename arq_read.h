/*
 ============================================================================
 Nome        : arq_read.h
 Autor		 : V�tor Faccio
 Vers�o	     : 1.0
 Copyright   : V�tor Faccio, todos os direitos reservados
 Descri��o	 : Leitura da planilha em .ods com as informa��es dos aeroportos

 L� o arquivo que cont�m as informa��es necess�rias e os guarda num conjunto
 de v�rtices. Retorna este conjunto a quem chamar a fun��o.
 ============================================================================
 */

#ifndef ARQ_READ_H_INCLUDED
#define ARQ_READ_H_INCLUDED

#include "lista_enc.h"

#define TAM_BUFFER_G 	200
#define TAM_BUFFER_M 	100
#define TAM_BUFFER_P	50
#define TAM_BUFFER_PP 	10

#define RAIO_TERRA 	6371

typedef struct dados_aeroporto aeroporto_t;
lista_enc_t * ler_tabela(char * arquivo);
aeroporto_t * cria_aeroporto(int id, char * buffer_nome, char * code, char * pais, char * cidade, int mov_anual, int * coord_latitude, char char_lat, int * coord_longitude, char char_long);

/** Fun��es de retorno **/

int 	aeroporto_get_id(aeroporto_t * aeroporto);
char * 	aeroporto_get_nome(aeroporto_t * aeroporto);
char * 	aeroporto_get_code(aeroporto_t * aeroporto);
char * 	aeroporto_get_pais(aeroporto_t * aeroporto);
char * 	aeroporto_get_cidade(aeroporto_t * aeroporto);
int 	aeroporto_get_movimento(aeroporto_t * aeroporto);
char * 	aeroporto_get_code(aeroporto_t * aeroporto);
int * 	aeroporto_get_coord_lat(aeroporto_t * aeroporto);
char 	aeroporto_get_char_lat(aeroporto_t * aeroporto);
int * 	aeroporto_get_coord_long(aeroporto_t * aeroporto);
char 	aeroporto_get_char_long(aeroporto_t * aeroporto);
float 	aeroporto_get_latitude(aeroporto_t * aeroporto);
float 	aeroporto_get_longitude(aeroporto_t * aeroporto);

#endif // ARQ_READ_H_INCLUDED
