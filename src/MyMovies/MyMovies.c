#include "MyMovies.h"
#include <zephyr/kernel.h>          /* for k_msleep() */


void alocListMovies(void)
{

    for(int i=0; i<=NUM_MAX_FILMES; i++)
    {
       listaFilmes[i].nomeFilme= k_malloc(20);
       listaFilmes[i].sessionTime= k_malloc(10);
       listaFilmes[i].price=0;    
    }

}

void creatListMovies(void)
{
    listaFilmes[0].nomeFilme="MovieA";
    listaFilmes[0].sessionTime="19H00";
    listaFilmes[0].price=9;

    listaFilmes[1].nomeFilme="MovieA";
    listaFilmes[1].sessionTime="21H00";
    listaFilmes[1].price=11;

    listaFilmes[2].nomeFilme="MovieA";
    listaFilmes[2].sessionTime="23H00";
    listaFilmes[2].price=9;

    listaFilmes[3].nomeFilme="MovieB";
    listaFilmes[3].sessionTime="19H00";
    listaFilmes[3].price=10;

    listaFilmes[4].nomeFilme="MovieB";
    listaFilmes[4].sessionTime="21H00";
    listaFilmes[4].price=12;

}

