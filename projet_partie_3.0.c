/////////////////////////////////////////////////////////////////
//                                                             //
// AUTEURS : LECOMTE Mathieu et CASTELLON Valentin             //
//                                                             //
// DATE    : 08/01/2018     				                   //
//                                                             //
// RESUME  : Code source correspondant à la première partie du //
// 			 projet tutoré de S1 : coder un Takuzu 			   //
//                                                             //
/////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include "projet_partie_1.0.h"
#include "projet_partie_2.0.h"
#include "projet_partie_3.0.h"


/*
	Ce fichier contient pour l'instant les en-têtes des fonctions de la partie 1.
	Vous devez coder les définitions. Les fonctions de test de la partie 1 sont également données.
	Comme ces fonctions utilisent la fonction assert, leurs appels sont commentées dans la fonction principale
	(vous ne pouvez les tester avant de les coder !)

	ATTENTION : le code ne compile pas avant d'avoir défini les types structurés.
*/


//////////////////////////////////////////////////////////////
// Code permettant d'utiliser les couleurs dans le terminal //
//////////////////////////////////////////////////////////////


// Couleurs possibles
typedef enum
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  } COULEUR_TERMINAL;


void clear_terminal()
{
  printf("\033[2J");
  printf("\033[0;0H");
}

/*int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...)
{
  int res;
  va_list args;
  printf("\x1B[1;%02d;%02dm", fg + 30, bg + 40);
  va_start(args, format);
  res = vprintf(format, args);
  va_end(args);
  printf("\x1B[00m");
  return res;
}*/



////////////////////////////////////////////
// DÉFINIR LE TYPE STRUCTURÉ cellule ici  //
////////////////////////////////////////////

typedef struct
{
	int val;
	int initial;
}cellule;


//////////////////////////////////////////
// DÉFINIR LE TYPE STRUCTURÉ grille ici //
//////////////////////////////////////////

typedef struct
{
	cellule * tab;
	int n;
}grille;

/**
 * Fonction allouant dynamiquement une grille dont l'adresse est retournée.
 * @param n : nombre de lignes/colonnes (4, 6, ou 8)
 * @return  : adresse de la grille, NULL en cas d'erreur
 */
grille * creer_grille(int n)
{

	assert(n==4 || n==6 || n==8);
	grille * g = malloc(sizeof(grille));
	if (g== NULL)
	{
		printf("Erreur d'allocation !");
		return NULL;
	}

	g->n = n;
	g->tab = malloc(sizeof(cellule)*n*n);
	if (g->tab == NULL)
	{
		printf("Erreur d'allocation du tableau !");
		return NULL;
	}
	int i;
	for (i=0; i< n*n; i++)
	{
		g->tab[i].val=-1;
		g->tab[i].initial=0;
	}
	return g;
	return NULL; //Pour éviter les problèmes compilation
}


/**
 * Fonction désallouant dynamiquement la grille passée en paramètre.
 * @param g : grille à désallouer
 */
void detruire_grille(grille * g){

	free(g->tab);
	free(g);
}

/**
 * Fonction retournant 1 si l'indice est valide par rapport à la grille.
 * @param g      : grille
 * @param indice : entier
 * @return       : 1 si indice est un indice valide pour g, 0 sinon
 */
int est_indice_valide(grille * g, int indice){

	int test;
	if (indice >= 0 && indice < g->n)
	{
		test = 1;
		return test;
	}
	else
	{
		test = 0;
		return test;
	}
}

/**
 * Fonction retournant 1 si (i,j) est une cellule de la grille.
 * @param g : grille
 * @param i : numéro de ligne
 * @param j : numéro de colonne
 * @return  : 1 si (i,j) correspond à une cellule de g, 0 sinon
 */
int est_cellule(grille * g, int i, int j){

	int test=1;
	if(est_indice_valide(g, i)==1  && est_indice_valide(g, j)==1)
	{
		return test;
	}
	else
	{
		test = 0;
		return test;
	}
}


/**
 * Fonction retournant la valeur de la cellule (i,j) de la grille g.
 *
 * @param g : grille
 * @param i : numéro de ligne
 * @param j : numéro de colonne
 */
int get_val_cellule(grille * g, int i, int j){

	assert(est_cellule(g, i, j)==1);
	int valeur = g->tab[(i*g->n)+j].val;
	return valeur;
}


/**
 * Fonction modifiant la valeur de la cellule (i,j) de la grille g avec
 * la valeur passée en paramètre.
 * @param g : grille
 * @param i : indice de ligne
 * @param j : indice de colonne
 * @param valeur : valeur à mettre dans le champ val de la cellule (i,j)
 */
void set_val_cellule(grille * g, int i, int j, int valeur){

	assert(est_cellule(g, i, j)==1);
	assert (valeur >= -1 && valeur <= 1);
	g->tab[(i*g->n)+j].val = valeur;
}


/**
 * Fonction retournant 1 si la cellule (i,j) est une cellule initiale,
 * et 0 sinon.
 * @param g : grille
 * @param i : indice de ligne
 * @param j : indice de colonne
 */
int est_cellule_initiale(grille * g, int i, int j){

	assert(est_cellule(g, i,j)==1);
	int test;
	if (g->tab[(i*g->n)+j].initial == 1)
	{
		test =1;}
	else
	{
		test =0;}
	return test;
}


/**
 * Fonction retournant 1 si la cellule (i,j) de la grille g est vide,
 * et 0 sinon.
 * @param g : grille
 * @param i : indice de ligne
 * @param j : indice de colonne
 */
int est_cellule_vide(grille * g, int i, int j){

	assert(est_cellule(g, i,j)==1);
	int test;
	if (g->tab[(i*g->n)+j].val == -1)
	{
		test = 1;
	}
	else
	{
		test = 0;
	}
	return test;
}


/**
 * Fonction affichant la grille sur le terminal.
 * @param g : pointeur sur la grille que l'on souhaite afficher
 */
void afficher_grille(grille * g){

	int x;
	int y;
	int a;
	int b;
	for (x=0; x < g->n ; x++)
	{
		if (g->n == 4)
		{
			for(a=0; a < ((4*g->n)-1); a++)
				printf("* ");
		}
		else if (g->n == 6)
		{
			for(a=0; a < ((4*g->n)-2); a++)
				printf("* ");
		}
		else
		{
			for(a=0; a < ((4*g->n)-3); a++)
				printf("* ");
		}
		printf("\n");
		for (a=0; a < g->n; a++)
		{
			printf("*");
			for (b=0; b < 3; b++)
				printf("  ");
		}
		printf ("* \n");

		for (y=0; y < g->n; y++)
		{

			printf("*  ");
			if (est_cellule_vide(g, x, y) == 1)
			{
				printf("  ");
			}
			else if (est_cellule_initiale(g, x, y) == 1)
			{
				printf("%d%d", get_val_cellule(g, x, y), get_val_cellule(g, x, y));
			}
			else
			{
				printf("%2d", get_val_cellule(g, x, y));
			}
			printf("  ");
		}
	printf("* \n");
	for (a=0; a < g->n; a++)
	{
		printf("*");
		for (b=0; b < 3; b++)
			printf("  ");
	}
		printf ("* \n");
	}

	if (g->n == 4)
		{
			for(a=0; a < ((4*g->n)-1); a++)
				printf("* ");
		}
	else if (g->n == 6)
		{
			for(a=0; a < ((4*g->n)-2); a++)
				printf("* ");
		}
	else
		{
			for(a=0; a < ((4*g->n)-3); a++)
				printf("* ");
		}
	printf("\n");
}


///////////////////////////////////////////////////
//  Code correspondant aux tests de la partie 1  //
///////////////////////////////////////////////////

/**
 * Fonction testant la fonction creer_grille
 */
void test_creer_grille(){
	int i,k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		assert(g->n == k && "Problème dans le champ n de la grille");

		//Vérification que les cellules sont vides
		for(i = 0 ; i < k * k ; i++){
			assert(g->tab[i].val == -1 && "Problème : cellule non vide !");
			assert(g->tab[i].initial == 0 && "Problème : cellule initiale !");
		}
		detruire_grille(g);
	}
	printf("Test de la fonction creer_grille passé !\n");
}

/**
 * Fonction testant la fonction est_indice_valide
 */
void test_est_indice_valide(){
	int i,k;
	for(k = 4; k <= 8 ; k+=2){

		grille * g = creer_grille(k);
		for(i = 0 ; i < k ; i++)
			assert(est_indice_valide(g,i) == 1 && "Problème indice valide non reconnu !");

		assert(est_indice_valide(g,-1) == 0 && "Problème indice non valide reconnu !");
		assert(est_indice_valide(g,k)  == 0 && "Problème indice non valide reconnu !");
		detruire_grille(g);
	}
	printf("Test de la fonction est_indice_valide passé !\n");
}

/**
 * Fonction testant la fonction est_cellule
 */
void test_est_cellule(){
	int i,j,k;
	for(k = 4; k <= 8 ; k+=2){

		grille * g = creer_grille(k);
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule(g,i,j) == 1 && "Problème indice valide non reconnu !");
		assert(est_cellule(g,-1,1) == 0 && "Problème indice non valide reconnu !");
		assert(est_cellule(g,k,1)  == 0 && "Problème indice non valide reconnu !");
		assert(est_cellule(g,1,-1) == 0 && "Problème indice non valide reconnu !");
		assert(est_cellule(g,1,k)  == 0 && "Problème indice non valide reconnu !");
		detruire_grille(g);
	}
	printf("Test de la fonction est_cellule passé !\n");
}

/**
 * Fonction testant la fonction get_val_cellule
 */
void test_get_val_cellule(){
	grille * g = creer_grille(6);
	g->tab[0].val = 1;
	g->tab[6].val = 1;
	g->tab[15].val = 0;
	assert(get_val_cellule(g,0,0) == 1 && "Problème de valeur");
	assert(get_val_cellule(g,1,0) == 1 && "Problème de valeur");
	assert(get_val_cellule(g,2,3) == 0 && "Problème de valeur");
	assert(get_val_cellule(g,1,4) == -1 && "Problème de valeur");
	detruire_grille(g);
	printf("Test de la fonction get_val_cellule passé !\n");
}


/**
 * Fonction testant la fonction set_val_cellule
 */
void test_set_val_cellule(){
	int k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		set_val_cellule(g,0,0,1);
		assert(get_val_cellule(g,0,0) == 1 && "Problème de valeur");
		set_val_cellule(g,k-1,k-1,0);
		assert(get_val_cellule(g,k-1,k-1) == 0 && "Problème de valeur");
		set_val_cellule(g,0,k-2,1);
		assert(get_val_cellule(g,0,k-2) == 1 && "Problème de valeur");
		set_val_cellule(g,k-2,1,0);
		assert(get_val_cellule(g,k-2,1) == 0 && "Problème de valeur");
		set_val_cellule(g,k-1,k-1,-1);
		assert(get_val_cellule(g,k-1,k-1) == -1 && "Problème de valeur");
		detruire_grille(g);
	}
	printf("Test de la fonction set_val_cellule passé !\n");
}

/**
 * Fonction testant la fonction est_cellule_initiale
 */
void test_est_cellule_initiale(){
	int i,j,k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].initial = 0;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_initiale(g,i,j) == 0 && "Problème valeur initiale au début");
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].initial = 1;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_initiale(g,i,j) == 1 && "Problème valeur initiale au début");
		detruire_grille(g);
	}
	printf("Test de la fonction est_cellule_initiale passé !\n");
}

/**
 * Fonction testant la fonction est_cellule_vide
 */
void test_est_cellule_vide(){
	int i,j,k;
	for(k = 4; k <= 8 ; k+=2){
		grille * g = creer_grille(k);
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].val = -1;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_vide(g,i,j) == 1 && "Problème valeur initiale au début");
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].val = 0;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_vide(g,i,j) == 0 && "Problème valeur initiale au début");
		for(i = 0 ; i < k * k ; i++){
			g->tab[i].val = 1;
		}
		for(i = 0 ; i < k ; i++)
			for(j = 0 ; j < k ; j++)
				assert(est_cellule_vide(g,i,j) == 0 && "Problème valeur initiale au début");
		detruire_grille(g);
	}
	printf("Test de la fonction est_cellule_vide passé !\n");
}

/**
 * Fonction testant la fonctino afficher_grille
 */
void test_afficher_grille(){
	grille * g = creer_grille(4);
	int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
	int i;
	for(i = 0 ; i < 16 ; i++){
		g->tab[i].val = val_cellule[i];
		g->tab[i].initial = initial_cellule[i];
	}
	afficher_grille(g);
	printf("L'affichage doit être celui de la grille solution dans le pdf\n");
}


//////////////////////
////   PARTIE 2   ////
//////////////////////


/**
* Fonction modifiant une cellule pour la rendre initiale.
* @param g : pointeur sur la grille
* @param i : indice de ligne
* @param j : indice de colonne
*/
void rendre_cellule_initiale (grille * g, int i, int j)
{
    assert(est_cellule(g,i,j)==1);
    assert(est_cellule_initiale(g,i,j)==0);
    g->tab[(i*g->n)+j].initial=1;
}





/**
* Fonction retournant une grille avec les informations contenues
* dans le fichier passé en paramètre.
* @param nom_fichier : fichier contenant l'instance du problème
* @return : pointeur sur la grille créée
*/
grille * initialiser_grille (char nom_fichier[])
{

    FILE * f = fopen (nom_fichier, "rt");

    if (f == NULL)
    {
        printf("Le fichier ne s'est pas ouvert correctement. \n");
    }

    int n;
    fscanf(f,"%d", &n);
    grille * g = creer_grille(n);
    int init;
    fscanf (f, "%d", &init);
    int x;
    int i, j, val;

    for (x = 0; x < init; x++)
    {
            fscanf(f,"%d",&i);
            fscanf(f,"%d",&j);
            fscanf(f,"%d",&val);
            set_val_cellule(g,i,j,val);
            rendre_cellule_initiale(g,i,j);
    }

    return g;
}



/**
* Fonction testant si la grille est entièrement remplie.
* @param g : grille à tester
* @return : 1 si la grille est pleine, 0 sinon
*/
int est_grille_pleine (grille *g)
{
    int i,j;
    for (i=0;i<g->n; i++)
    {
        for (j=0; j < g->n; j++)
        {
            if (get_val_cellule(g, i, j)==-1)
                return 0;
        }
    }
    return 1;
}




/**
* Fonction vérifiant qu'il n'existe pas 3 zéro ou 3 un consécutifs dans
* la grille (ligne ou colonne).
* @param g : grille à tester
* @return : 1 si c'est le cas, 0 sinon
*/
int pas_zero_un_consecutifs (grille * g)
{
    int i, j;
    for (i=0; i < g->n; i++)
    {
        for (j=0; j < g->n; j++)
        {
            if (est_cellule(g, i, j+3)==1)
            {
                if ((get_val_cellule(g, i, j) == get_val_cellule(g, i, j+1)) && (get_val_cellule(g, i, j+1) == get_val_cellule(g, i, j+2)))
                    return 0;
            }
            if (est_cellule(g, i+3, j)==1)
            {
                if ((get_val_cellule(g, i, j) == get_val_cellule(g, i+1, j)) && (get_val_cellule(g, i+1, j) == get_val_cellule(g, i+2, j)))
                    return 0;
            }
            else return 1;
        }
    }

}




/**
* Fonction testant si le nombre de zéros est égal au nombre de uns dans
* chaque ligne/colonne.
* @param g : grille à tester
* @return : 1 si c'est le cas, 0 sinon
*/
int meme_nombre_zero_un (grille * g)
{
    int i, j;
    int score0=0;
    int score1=0;
    for (i=0; i < g->n; i++)    //BOUCLE POUR LIGNES//
    {
        for (j=0; j < g->n; j++)
        {
            if (get_val_cellule(g, i, j)==1)
                score1++;
            else
                score0++;
        }
        if (score0!=score1)
            return 0;
    }
    for (i=0; i < g->n; i++)    //BOUCLE POUR COLONNES//
    {
        for (j=0; j < g->n; j++)
        {
            if (get_val_cellule(g, j, i)==1)
                score1++;
            else
                score0++;
        }
        if (score0!=score1)
        return 0;
    }
    return 1;
}




/**
* Fonction testant qu'il n'existe pas deux lignes identiques ou deux
* colonnes identiques.
* @param g : grille à tester
* @return : 1 si c'est le cas, 0 sinon
*/
int lignes_colonnes_distinctes(grille * g){


    int i, j, k;
    int count_colonne=0;
    int count_ligne=0;

    for (k=0; k < g->n-1; k++)
    {
        for (i=k+1; i < g->n; i++)
        {
            for (j=0; j < g->n; j++)
            {
                if (get_val_cellule(g, k, j) == get_val_cellule(g, i, j))
                    count_ligne++;
            }
            if (count_ligne == g->n)
            {
                return 0;
            }
            count_ligne = 0;
        }
    }

    for (k=0; k < g->n-1; k++)
    {
        for (i=k+1; i < g->n; i++)
        {
            for (j=0; j < g->n; j++)
            {
                if (get_val_cellule(g, j, k) == get_val_cellule(g, j, i))
                    count_colonne++;
            }
            if (count_colonne == g->n)
            {
                return 0;
            }
            count_colonne = 0;
        }
    }
    return 1;
}


/**
* Fonction déterminant si la partie est gagnée.
* @param g : grille à tester
* @return : 1 si la partie est gagnée, 0 sinon
*/
int est_partie_gagnee(grille * g)
{
    if (est_grille_pleine(g)==1)
    {
        if (pas_zero_un_consecutifs(g)==1)
        {
            if (meme_nombre_zero_un(g)==1)
            {
                if (lignes_colonnes_distinctes(g)==1)
                    return 1;
            }
        }
    }
    return 0;
}



///////////////////////////////////////////////////
//  Code correspondant aux tests de la partie 2  //
///////////////////////////////////////////////////

void test_rendre_cellule_initiale ()
{
    grille * g = creer_grille(6);
    g->tab[0].initial=0;
    rendre_cellule_initiale(g,0,0);
    if (g->tab[0].initial==1)
        printf("Test de la fonction rendre_cellule_initiale passé !\n");
    else
        printf("Erreur dans la fonction rendre_cellule_initiale !\n");
        detruire_grille(g);
}


void test_initialiser_grille ()
{
    grille * g = initialiser_grille("grille1.txt");
	afficher_grille(g);
    g = initialiser_grille("grille2.txt");
	afficher_grille(g);
    g = initialiser_grille("grille3.txt");
	afficher_grille(g);
    g = initialiser_grille("grille4.txt");
	afficher_grille(g);

    printf("L'affichage doit être celui des grilles dans le dossier ! \n");
}


void test_est_grille_pleine()
{
    grille * g = creer_grille(4);
    int i, j;
    for (i=0; i < g->n; i++)
    {
        for (j=0; j < g->n; j++)
        {
            set_val_cellule(g, i, j, 0);
        }
    }
    if(est_grille_pleine(g)==1)
        printf("Test de la fonction est_grille_pleine passé ! \n");
    else
        printf("Erreur dans la fonction est_grille_pleine ! \n");
    detruire_grille(g);
}


void test_pas_zero_un_consecutifs ()
{
    grille * g = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int i;

    for(i = 0 ; i < 16 ; i++)
    {
		g->tab[i].val = val_cellule[i];
		g->tab[i].initial = initial_cellule[i];
	}

    int score = 0;
    if (pas_zero_un_consecutifs(g)==1)
        score++;

    set_val_cellule(g, 0, 0, 1);
    set_val_cellule(g, 1, 0, 1);
    set_val_cellule(g, 2, 0, 1);

    if (pas_zero_un_consecutifs(g)==0)
        score++;

    set_val_cellule(g, 0, 0, 0);
    set_val_cellule(g, 1, 0, 1);
    set_val_cellule(g, 2, 0, 0);

    set_val_cellule(g, 0, 0, 1);
    set_val_cellule(g, 0, 1, 1);
    set_val_cellule(g, 0, 2, 1);

    if (pas_zero_un_consecutifs(g)==0)
        score++;

    if (score == 3)
        printf("Test de la fonction pas_zero_un_consecutifs passé ! \n");
    else
        printf("Erreur dans la fonction pas_zero_un_consecutifs ! \n");
    detruire_grille(g);

}


void test_meme_nombre_zero_un()
{
    grille * g = creer_grille(4);
    int i, j;
    for (i=0; i < g->n; i++)
    {
        for (j=0; j < g->n; j++)
        {
            if (i%2==0 && j%2==0)
                set_val_cellule(g, i, j, 0);
            else
                set_val_cellule(g, i, j, 1);
        }
    }
    set_val_cellule(g, 1, 1, 0);
    set_val_cellule(g, 1, 3, 0);
    set_val_cellule(g, 3, 1, 0);
    set_val_cellule(g, 3, 3, 0);
    if (meme_nombre_zero_un(g)==1)
        printf("Test de la fonction meme_nombre_zero_un passé ! \n");
    else
        printf("Erreur dans la fonction meme_nombre_zero_un ! \n");

    detruire_grille(g);
}


void test_lignes_colonnes_distinctes()
{
    grille * g1 = creer_grille(4);
    grille * g2 = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int val_cellule2[16] = {0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0};
	int initial_cellule2[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};

	int i;
	for(i = 0 ; i < 16 ; i++)
    {
		g1->tab[i].val = val_cellule[i];
		g1->tab[i].initial = initial_cellule[i];
	}
	for(i = 0 ; i < 16 ; i++)
    {
		g2->tab[i].val = val_cellule2[i];
		g2->tab[i].initial = initial_cellule2[i];
	}

     if(lignes_colonnes_distinctes(g1) == 1)
    {
        if(lignes_colonnes_distinctes(g2) == 0)
        {
            printf("Test de la fonction lignes_colonnes_distinctes réussi !\n");
        }

        else
            printf("Erreur dans la fonction lignes_colonnes_distinctes !\n");
    }


    else
        printf("Erreur dans la fonction lignes_colonnes_distinctes !\n");
    detruire_grille(g1);
    detruire_grille(g2);
}


void test_est_partie_gagnee ()
{
    grille * g1 = creer_grille(4);
    grille * g2 = creer_grille(4);
    int val_cellule[16] = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    int val_cellule2[16] = {0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0};
	int initial_cellule2[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};

	int i;
	for(i = 0 ; i < 16 ; i++)
    {
		g1->tab[i].val = val_cellule[i];
		g1->tab[i].initial = initial_cellule[i];
	}
	for(i = 0 ; i < 16 ; i++)
    {
		g2->tab[i].val = val_cellule2[i];
		g2->tab[i].initial = initial_cellule2[i];
	}

    if (est_partie_gagnee(g1)==1 && est_partie_gagnee(g2)==0)
    {
        printf("Test de la fonction _est_partie_gagnee réussi !\n");
    }
    else
        printf("Erreur dans la fonction est_partie_gagnee !\n");
}


//////////////////////
////   PARTIE 3   ////
//////////////////////


/**
* Fonction déterminant si un mouvement est valide. Si c'est le cas,
* elle met à jour les indices de ligne et colonne et la valeur en
* fonction de la saisie.
* @param g : pointeur sur la grille
* @param mouv : chaîne de caractères contenant le mouvement
* @param ligne : indice de ligne à modifier en fonction de mouv
* @param colonne : indice de colonne à modifier en fonction de mouv
* @param val : valeur à modifier en fonction de mouv
* @return : 1 si le mouvement est valide, et 0 sinon
*/
int est_mouvement_valide(grille * g, char mouv[], int * ligne, int * colonne, int * val)
{

    * ligne = mouv[0]-'A';
    * colonne = mouv[1]-'A';

    if(est_cellule(g,*ligne,*colonne) == 0 || est_cellule_initiale(g,*ligne,*colonne) == 1 )
    {
        return 0;
    }
    else
    {
        if( mouv[2]!='1' && mouv[2]!='0')
        {
            * val = -1;
            return 1;
        }

        else 
        {
            * val = mouv[2]-'0';
            return 1;
        }
    }
    return 0;
}


/**
* Fonction effectuant un tour de jeu :
* - saisie jusqu'à ce que l'utilisateur saisisse un mouvement valide,
* - modification de la grille en fonction de la saisie.
* @param g : pointeur sur la grille
*/
void tour_de_jeu(grille * g)
{
	int i=0;
	int j=0;
	int val=0;
	char mouvement[4];
	int a;
	do
	{
	printf("Veuillez saisir un mouvement valide : ");
	scanf("%s",mouvement);
	a=est_mouvement_valide(g,mouvement,&i,&j,&val);
	}
	while(a==0);
	set_val_cellule(g,i,j,val);
}

/**
* Fonction permettant de jouer au Takuzu.
* @param ch : Chaîne de caractères contenant le nom du fichier
* correspondant à l'instance du Takuzu
*/
void jouer(char ch[])
{
	grille * g = initialiser_grille(ch);
	afficher_grille(g);
	while(est_partie_gagnee(g)==0)
	{
		tour_de_jeu(g);
		afficher_grille(g);
	}
}

/**
* Fonction permettant de choisir aléatoirement une grille dont la taille
* est saisie par l'utilisateur.
* @param s : chaîne de caractères contenant le nom de la grille
* choisie aléatoirement
*/
void choisir_grille(char s[])
{
    int taille;
    do
	{
	printf("Veuillez saisir la taille de la grille souhaitée : ");
	scanf("%d", &taille);
	}
	while(taille!=4 && taille!=6 && taille!=8);

    int random = rand()%5+1;

    s[9]=taille+'0';
    s[17]=random+'0';

}



///////////////////////////////////////////////////
//  Code correspondant aux tests de la partie 3  //
///////////////////////////////////////////////////

void test_est_mouvement_valide ()
{
    grille * g1 = creer_grille(4);
    int val_cellule[16] = {-1,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
    char mouvbon[10]="AC0";
    char mouvinit[10]="AB";
    char mouv[]="AA";
    int * l = malloc(sizeof(int));
    int * c = malloc(sizeof(int));
    int * v = malloc(sizeof(int));
    int i;

    for(i = 0 ; i < 16 ; i++)
	{
		g1->tab[i].val = val_cellule[i];
		g1->tab[i].initial = initial_cellule[i];
	}

    if (est_mouvement_valide(g1, mouvbon, l, c, v)==1)
    {
        if (est_mouvement_valide(g1, mouvinit, l, c, v)==0)
        {
            if (est_mouvement_valide(g1, mouv, l, c, v)==0)
            {
                printf("Test de la fonction est_mouvement_valide réussi !\n");
            }
            else
            {
                printf("Erreur dans la fonction est_mouvement_valide !\n");
            }
        }
        else
        {
            printf("Erreur dans la fonction est_mouvement_valide !\n");
        }
    }

    else
    {
        printf("Erreur dans la fonction est_mouvement_valide !\n");
    }
    free(l);
    free(c);
    free(v);
}


void test_tour_de_jeu()
{
	grille * g = creer_grille(4);
	int val_cellule[16] = {0,1,1,0,1,1,0,1,0,0,1,1,1,1,0,0};
	int initial_cellule[16] = {0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1};
	int i;
	for(i = 0 ; i < 16 ; i++)
    {
		g->tab[i].val = val_cellule[i];
		g->tab[i].initial = initial_cellule[i];
	}
	afficher_grille(g);
	tour_de_jeu(g);
	afficher_grille(g);
}

void test_jouer()
{
	char ch[]="jouer.txt";
	jouer(ch);
}

void test_choisir_grille ()
{
    char s[]="Grilles/G6/grille2.txt";
    choisir_grille(s);
    grille * g = initialiser_grille(s);
    afficher_grille(g);
}




























int main(){
	 //Remarque : il ne faut pas mettre de retour à la ligne dans color_printf
	color_printf(GREEN, MAGENTA, "Début du programme"); printf("\n");

	//Décommenter chaque fonction lorsque la fonction à tester a été codée

	srand(time(NULL));

	/* test_creer_grille();
	test_est_indice_valide();
	test_est_cellule();
	test_get_val_cellule();
	test_set_val_cellule();
	test_est_cellule_initiale();
	test_est_cellule_vide();
	test_afficher_grille();

	// TESTS PARTIE 2 //

	test_rendre_cellule_initiale();
	test_est_grille_pleine();
	test_meme_nombre_zero_un();
	test_pas_zero_un_consecutifs();
	test_initialiser_grille();
	test_lignes_colonnes_distinctes();
	test_est_partie_gagnee();

	// TEST PARTIE 3//

	test_est_mouvement_valide ();
	test_tour_de_jeu();
	test_jouer();
	test_choisir_grille(); */

    char s[]="Grilles/G4/grille1.txt";
	choisir_grille(s);
	jouer(s);








	color_printf(YELLOW, CYAN, "Fin du programme"); printf("\n");
	return 0;
}
