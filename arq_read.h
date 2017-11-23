/*
 ============================================================================
 Nome        : arq_read.h
 Autor		 : Vítor Faccio
 Versão	     : 1.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 : Leitura da planilha em .ods com as informações dos aeroportos

 Lê o arquivo que contém as informações necessárias e os guarda num conjunto
 de vértices. Retorna ao main este conjunto.
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

#endif // ARQ_READ_H_INCLUDED
