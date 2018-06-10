#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "projet_partie_1.0.h"
#include "projet_partie_2.0.h"



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
