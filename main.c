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

int main(){
	 //Remarque : il ne faut pas mettre de retour à la ligne dans color_printf
	/*color_printf(GREEN, MAGENTA, "Début du programme"); printf("\n");*/

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








	/*color_printf(YELLOW, CYAN, "Fin du programme"); printf("\n");*/
	return 0;
}

