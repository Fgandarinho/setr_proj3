#ifndef _MYMOVIES_H_
#define _MYMOVIES_H_

/*Modulo com objetivo de criar espaço e armazenar filmes e seus dados*/

#define NUM_MAX_FILMES 5

/*Estrutura de dados para filme*/
struct filme
{
    char *nomeFilme;
    char *sessionTime;
    int price;
};

/*cria um array estático para uma estrutura de filmes*/
static struct filme listaFilmes[NUM_MAX_FILMES];

/*cria a lista de filmes consoante o guião de trabalho*/
void alocListMovies(void);

void creatListMovies(void);


#endif