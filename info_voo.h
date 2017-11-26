/*
 ============================================================================
 Nome        : info_voo.h
 Autor		 : V�tor Faccio
 Vers�o	     : 1.0
 Copyright   : V�tor Faccio, todos os direitos reservados
 Descri��o	 :
 ============================================================================
 */

#ifndef INFO_VOO_H_INCLUDED
#define INFO_VOO_H_INCLUDED

#include "arq_read.h"
#include "grafo.h"

typedef struct informacoes 	info_t;

info_t* 	cria_info(void *pointer);

aeronave_t*		info_obter_aeronave(info_t *info);
aeroporto_t* 	info_obter_origem(info_t *info);
aeroporto_t* 	info_obter_destino(info_t *info);


#endif // INFO_VOO_H_INCLUDED
