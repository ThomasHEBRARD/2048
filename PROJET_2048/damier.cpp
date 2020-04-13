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
