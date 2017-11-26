/*
 ============================================================================
 Nome        : info_voo.h
 Autor		 : Vítor Faccio
 Versão	     : 1.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 :
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
