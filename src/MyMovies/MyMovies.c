#include "MyMovies.h"
#include <zephyr/kernel.h>          /* for k_malloc() */

/*Variaveis globais*/
struct filme tab_Filmes[NUM_MAX_FILMES];



/*Alocar memória no uC para escrever as informações dos filmes*/
void alocListMovies()
{
  
      for(int i=0; i<NUM_MAX_FILMES; i++)
      {     
            tab_Filmes[i].nomeFilme= k_malloc(10);
            if(tab_Filmes[i].nomeFilme==NULL)
            {
               printk("Mem. Not ALOCADA FILM %d",i);
            }

            tab_Filmes[i].sessionTime=k_malloc(10);
            if(tab_Filmes[i].sessionTime==NULL)
            {
               printk("Mem. Not ALOCADA FILM %d",i);
            }
      }



  
}//fim de void alocListMovies()

void creatListMovies()
{
    tab_Filmes[0].nomeFilme="0_MovieA";
    tab_Filmes[0].sessionTime="19H00";
    tab_Filmes[0].price=9;

    tab_Filmes[1].nomeFilme="1_MovieA";
    tab_Filmes[1].sessionTime="21H00";
    tab_Filmes[1].price=11;

    tab_Filmes[2].nomeFilme="2_MovieA";
    tab_Filmes[2].sessionTime="23H00";
    tab_Filmes[2].price=9;

    tab_Filmes[3].nomeFilme="3_MovieB";
    tab_Filmes[3].sessionTime="19H00";
    tab_Filmes[3].price=10;

    tab_Filmes[4].nomeFilme="4_MovieB";
    tab_Filmes[4].sessionTime="21H00";
    tab_Filmes[4].price=12;
}

/**
 * Função de devolve as informações do filme
 * parametro de saida é do tipo estrutura de filme
 * parametro de entrada indici do filme a procurar
 * ponteiro para a estrutura da lista de filmes
*/
struct filme showFilme(int num_filme)
{
   struct filme ret;
   if(num_filme<NUM_MAX_FILMES)
   {
      ret.nomeFilme=tab_Filmes[num_filme].nomeFilme;
      ret.sessionTime=tab_Filmes[num_filme].sessionTime;
      ret.price=tab_Filmes[num_filme].price;
   }

   return ret;

}