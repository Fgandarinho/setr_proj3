/** \file MyMovies.h
 *	\author Fernando Gandarinho e Tomás Silva
 *
 *	\brief Este ficheiro pretende definir as funçoes para gestão da estrutura dos filmes. 
 *  
 * 	\date 16/05/2023
 * 	\bug There are no bugs 
 */
#ifndef _MYMOVIES_H_
#define _MYMOVIES_H_

/*Modulo com objetivo de criar espaço e armazenar filmes e seus dados*/

#define NUM_MAX_FILMES 5

/*Estrutura de dados para filme*/
/** \brief Definiçao da estrutura de dados para os filmes.
 *    Esta estrutura contém os vários filmes existentes na maquina de filmes.
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	\param[in] *nomeFilme: define o nome do filme
 * 	\param[in] *sessionTime: define o tempo e sessão do filme
 * 	\param[in] price: define o preço do filme
 * 
 * 	\date 16/05/2023
 * 
 */
struct filme
{
    char *nomeFilme;
    char *sessionTime;
    int price;
};


/*aloca espaço no uC para armazenar as informações do filme*/
/** \brief aloca espaço necessário para armazenar a lista dos filmes.
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 *  
 * 	\date 16/05/2023
 * 
 */
void alocListMovies();

/*cria/insere os filmes consoante os dados do guiao de trabalho*/
/** \brief cria/insere os filmes de forma default seguindo o guião.
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 *  
 * 	\date 16/05/2023
 * 
 */
void creatListMovies();

/*devolve as informações do filme selecionado*/
/*struct filme showFilme(int num_filme, struct filme *lista);*/
/** \brief Função para devolver as informações do filme selecionado.
 * 
 * 	\author Fernando Gandarinho e Tomás Silva
 * 	\param[in] num_filme: define o numero do filme a procurar
 * 	\param[in] *filme: define o ponteiro para a estrutura do filme a procurar
 * 
 * 	\date 16/05/2023
 * 
 */
struct filme showFilme(int num_filme);


#endif
