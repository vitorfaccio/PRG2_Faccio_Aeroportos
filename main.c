/*
 ============================================================================
 Nome        : main.c
 Autor		 : Vítor Faccio
 Versão	     : 2.0
 Copyright   : Vítor Faccio, todos os direitos reservados
 Descrição	 :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "arq_read.h"

#define FALSE 0
#define TRUE 1

int main()
{
    lista_enc_t* lista_vertices_aeroportos = ler_tabela_aeroportos("PRG2_Faccio_ListaAeroportos_v1.csv");
    lista_enc_t* lista_aeronaves = ler_tabela_aeronaves("PRG2_Faccio_ListaAeronaves_v1.csv");
	aeroporto_t* aeroporto;
	grafo_t* grafo;
	grafo = cria_grafo(0);

	no_t* no_aeroporto = obter_cabeca(lista_vertices_aeroportos);
	while(no_aeroporto != NULL){
		grafo_adicionar_vertice(grafo,aeroporto_get_id(obter_dado(no_aeroporto)),obter_dado(no_aeroporto));
		no_aeroporto = obtem_proximo(no_aeroporto);
	}
/** Grafo criado! **/

/**	 	Cria lista de informações:	  **/
	info_t* info = cria_info();

/** Requisitar ao usuário a aeronave: **/
	info_set_aeronave(info,lista_aeronaves);

/*
printf("\n\nRecapitulando os dados digitados:\n");
printf("Origem: %s\nDestino: %s\nAeronave: %s\n",
	aeroporto_get_cidade(info_obter_origem(info)),
	aeroporto_get_cidade(info_obter_destino(info)),
	aeronave_obter_nome(info_obter_aeronave(info)));
printf("Autonomia da aeronave: %d km\n",aeronave_obter_autonomia(info_obter_aeronave(info)));
 Pronto para criar a malha de conexões!
*/

    no_t* no_grafo_1 = obter_lista_vertices(grafo);
    no_t* no_grafo_2;
    vertice_t* vertice;
    double distancia;
    while(no_grafo_1 != NULL){
        vertice = obter_dado(no_grafo_1);
        no_grafo_2 = obter_lista_vertices(grafo);
        while(no_grafo_2 != NULL){
            distancia = haversine(aeroporto_get_latitude(obtem_aeroporto(vertice)),
									aeroporto_get_longitude(obtem_aeroporto(vertice)),
									aeroporto_get_latitude(obtem_aeroporto(obter_dado(no_grafo_2))),
									aeroporto_get_longitude(obtem_aeroporto(obter_dado(no_grafo_2))));
            if(distancia <= (double)aeronave_obter_autonomia(info_obter_aeronave(info)) && obter_dado(no_grafo_2) != vertice){
                adiciona_adjacentes(grafo, vertice, obter_dado(no_grafo_2),distancia);
                modifica_estado_visitavel(vertice,TRUE);
                modifica_estado_visitavel(obter_dado(no_grafo_2),TRUE);
            }
            no_grafo_2 = obtem_proximo(no_grafo_2);
        }
        no_grafo_1 = obtem_proximo(no_grafo_1);
    }
/** 				  Arestas criadas com SUCESSO! 	   				 **/


/**			  Obtenção dos aeroportos de origem e destino	    	 **/
	info_set_aeroportos(info,grafo);

/** Início do processo de busca do menor caminho entre os aeroportos **/
	pilha_t* pilha = dijkstra(grafo,procura_vertice(grafo,aeroporto_get_id(info_obter_origem(info))),procura_vertice(grafo,aeroporto_get_id(info_obter_destino(info))));
    vertice_t* vert;
    int i = 1;

    printf("Menor caminho de %s a %s: \n",aeroporto_get_cidade(info_obter_origem(info)),aeroporto_get_cidade(info_obter_destino(info)));
    while(pilha_vazia(pilha) == 0){
        vert = pop(pilha);
        printf("Vertice %d: %s \n",i++,aeroporto_get_cidade(obtem_aeroporto(vert)));
    }





	exportar_grafo_dot("grafo_semmovimento.dot", grafo);

    return 0;
}
