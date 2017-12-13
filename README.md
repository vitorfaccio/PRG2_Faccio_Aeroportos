*PRG2_Faccio_Aeroportos
*Cálculo de menor caminho entre aeroportos da América Latina
*Versão 2.0
*Readme.txt
*Projeto executado em novembro e dezembro de 2017
*Arquivo escrito em doze de dezembro de 2017
*Autor: Vítor Faccio 
*Para o programa completo, visite: 		
https://github.com/vitorfaccio/PRG2_Faccio_Aeroportos
*Projeto final da unidade curricular de Programação de 
Computadores II, lecionada por Renan Starke

>Todos os direitos reservador ao autor

--------------------------------------------------------------------
/* Este documento possui as informações básicas para o uso do programa.
Em caso de dúvidas de qualquer porte, entre em contato com o autor 
por meio do e-mail vitorfaccio.ifsc@gmail.com */
--------------------------------------------------------------------
	
	Este projeto tem como objetivo fornecer a lista de todos os
aeroportos internacionais da América Latina ao usuário, bem como a 
de aeronaves disponíveis para voo, e fornecer o menor caminho entre
dois aeroportos à escolha deste considerando a distância entre eles 
e suas movimentações anuais. São utilizadas estruturas de grafos e
listas encadeadas para o armazenamento e montagem das informações, 
além do algoritmo de Dijkstra para o cálculo do caminho a ser 
fornecido.	
	O projeto foi escrito, compilado e testado baseando-se no sistema
  operacional Windows 10 de 64 bits, processador Intel Core 
i5-3337U, por meio de software CodeBlocks (versão 12.11).

1. LISTA DE ARQUIVOS DO PROJETO
	O projeto deve contar com os seguintes arquivos para seu
funcionamento:
-PRG2_Faccio_ListaAeroportos_v3.csv
	*Lista de aeroportos disponíveis, pode ser expandida a 
cargo do usuário desde que obedeça ao padrão utilizado:
ID/Nome/Código IATA/País/Cidade/Movimento Anual/Latitude/Longitude

-PRG2_Faccio_ListaAeronaves_v1.csv
	*Novamente, lista de aeronaves disponíveis, pode ser 
expandida a cargo do usuário desde que obedeça ao padrão utilizado:
ID/Nome/Autonomia (km)

-main.c

-grafo.c/h

-vertice.c/h

-info_voo.c/h

-arq_read.c/h

-pilha.c/h

-fila.c/h

-lista_enc.c/h

-no.c/h

2. A EXECUÇÃO DO PROGRAMA
	Para executar o programa, baixe todos os arquivos citados 
anteriormente, 

3. FUNCIONAMENTO DO PROGRAMA
	Após iniciado, o programa executará as seguintes tarefas:
	-Disposição da lista de aeronaves com suas respectivas 
autonomias; o usuário deverá em seguida digitar o ID correspondente
à aeronave escolhida.
	-Disposição da lista de aeroportos disponíveis para que se
trafegue com o avião de sua escolha - autonomias menores que a 
distância entre dois aeroportos anulam a possibilidade de tráfego 
entre eles; o usuário deverá primeiramente inserir o ID do aeroporto 
de origem, posteriormente o de destino.
	-Fornecidos os três dados, o programa disponibiliza logo 
abaixo na tela a lista de aeroportos que compõem o menor caminho, 
iniciando pela origem e terminando com o destino.
