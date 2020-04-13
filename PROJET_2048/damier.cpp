#include "damier.h"
#include <iostream>

using namespace std;

/* Constructeur */
Damier::Damier(int size)
{
    /* Déclaration des variables */
    Size = size;
    dam = new int*[Size];

    /* Construction du Damier sous forme de tableau*/
    for (int i = 0; i < Size; i++){
        dam[i] = new int[Size];
        for (int j = 0; j < Size; j++){
            dam[i][j] = 0;
        }
    }
}

/* On construit le Destructeur */
Damier::~Damier()
{
    std::cout <<"Le damier a été détruit, c'est ballot"<< std::endl;
}

/* Première étape, apparition des premiers chiffres */
/* Méthode pour placer un 2 ou un 4 au hasard sur le damier */

void Damier::ApparitionPremiersChiffres()
{
}

bool Damier::Lost()
{
    for (int i=0; i<Size; i++)
    {
        for (int j=0; j<Size; j++)  /* on parcours l'ensemble de la matrice*/
        {
            int x=dam[i][j];
            if (x==0)   /*on vérifie qu'il ne reste pas une case vide*/
                return false;
                                                       /*on peut donc encore fusionner des cases*/
            else if (i-1>=0 && x=dam[i-1][j]){         /*case en haut*/
                return false;
            }
            else if (i+1<=Size &&  x=dam[i+1][j]){     /*case en bas*/
                return false;

}
            else if (j-1>=0 && x=dam[i][j-1]){         /*case à gauche*/
                return false;
            }
            else if (j+1<=Size && x=dam[i][j+1]){      /*case à droite*/
                return false;
            }
        }
    }
    return true;                                      /*le joueur a perdu*/
}
