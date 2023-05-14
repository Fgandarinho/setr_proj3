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


/*aloca espaço no uC para armazenar as informações do filme*/
void alocListMovies();

/*cria/insere os filmes consoante os dados do guiao de trabalho*/
void creatListMovies();

/*devolve as informações do filme selecionado*/
/*struct filme showFilme(int num_filme, struct filme *lista);*/
struct filme showFilme(int num_filme);


#endif