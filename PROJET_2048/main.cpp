/* Import des fichiers du damier */
#include "damier.h"
#include <iostream>

using namespace std;

int main()
{
    /* Damier de taille 4 */
    Damier DAMIER = Damier(4);

    /* Les mouvements viennent d'être codés, 
    Il faut maintenant demander au joueur qu'il rentre les chiffres
    0, 1, 2 ou 3 pour les mouvements UP, RIGHT, LEFT, DOWN. */

    /* Il faut ensuite afficher le nouveau damier, et regarder si
    le joueur a perdu ou pas */

    /* Tant que le joueur n'a pas perdu.. */
    while (!DAMIER.Lost() and DAMIER.Win()){
        /* On affiche le Damier */
        DAMIER.Afficher_le_damier();

        /* On Affiche au joueur ce qu'il faut qu'il rentre pour qu'il puisse jouer*/

        cout << "Entrez 0 pour aller vers le HAUT" << endl;
        cout << "Entrez 1 pour aller vers le BAS" << endl;
        cout << "Entrez 2 pour aller vers la DROITE" << endl;
        cout << "Entrez 3 pour aller vers la GAUCHE" << endl;

        int mouvement_execute; 
        /* On demande au joueur ce qu'il veut faire */
        cin >> mouvement_execute;

        /* On fait un mouvement général du damier */
        DAMIER.MouvementDamier(mouvement_execute);
    }
    /* Message de fin si le joueur a gagné ou perdu */
    if (DAMIER.Win()){
        cout << "Bravo tu as gagné" << endl;
    } else {
        cout << "Tu as perdu" << endl;
    }
}