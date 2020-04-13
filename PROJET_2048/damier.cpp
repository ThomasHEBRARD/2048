#include "damier.h"
#include <iostream>

using namespace std;

/* Constructeur */
Damier::Damier(int size)
{
    /* Déclaration des variables */
    Size = size;
    dam = new int*[Size];
    /* Ajout d'un tableau précédent le dam pour revenir en arrière */
    dam_precedent = new int*[Size];

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

/****** Première étape, apparition des premiers chiffres ******/
/* Méthode pour placer un 2 ou un 4 au hasard sur le damier */

void Damier::ApparitionPremiersChiffres()
{
    /* On initialise le générateur aléatoire */
    srand(time(NULL));

    /* On les fait apparaître dans un endroit random sur le damier */
    int i_apparition = rand()%Size;
    int j_apparition = rand()%Size;

    /* Il faut s'assurer que la case soit vide sinon il y aura chevauchement */
    while (dam[i_apparition][j_apparition] != 0){
        i_apparition = rand()%Size;
        j_apparition = rand()%Size;
    }
    /* Il faut maintenant créer du random entre 2 et 4 */
    int value = 2;

    float borne_minimale = 0;
	float borne_maximale = 1;

    /* On initialise les rand */

	scanf("%f",&borne_minimale);
	scanf("%f",&borne_maximale);
	
    /* Value sera 2 + 2*(un eniter random soit 0 soit 1) */

    value += 2*((int)(rand() * (borne_maximale+1 - borne_minimale) / RAND_MAX + borne_minimale ));

    /* Et on met à jour la case */
    dam[i_apparition][j_apparition] = value;
}

/* 2ème étape: On souhaite rajouter une fonction qui permet de revenir en arrière */
/* Pour cela, il faut avoir 2 tableau. Celui qui sera affiché et joué, et une copy 
de ce tableau au temps t-1 */
void Damier::Retour_en_arriere()
{
    /* Le principe est simple. Si le joueur veut revenir en arrière, 
    on va copier le tableau qui est en jeu avec le précedent.
    Il nous faut donc une fonction qui permet de copier 2 tableaux */
    Copier_tableaux(dam, dam_precedent);
}

/* Fonction qui permet de copier 2 tableaux */
void Damier::Copier_tableaux(int ** tableau_1, int ** tableau_2)
{
    /* On boucle sur toutes les cases */
    for (int i = 0; i < Size; i++){
        for (int j = 0; j < Size; j++){
            /* On copie */
            tableau_1[i][j] = tableau_2[i][j];
        }
    }
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
            else if (i-1>=0 && x==dam[i-1][j]){         /*case en haut*/
                return false;
            }
            else if (i+1<=Size &&  x==dam[i+1][j]){     /*case en bas*/
                return false;

}
            else if (j-1>=0 && x==dam[i][j-1]){         /*case à gauche*/
                return false;
            }
            else if (j+1<=Size && x==dam[i][j+1]){      /*case à droite*/
                return false;
            }
        }
    }
    return true;                                      /*le joueur a perdu*/
}

/* Affiche dans la console */

void Damier::Afficher_le_damier()       /*afficher le damier sur le terminal*/
{
    for (int i= 0; i< Size; i++)
    {
        for (int j=0; j< Size; j++)
        {
            std::cout<<dam[i][j]<<' ';    /*on rajoute un espace pour plus de clarté*/
        }
        std::cout<<std::endl;       /*on revient à la ligne pour chaque fin de ligne*/
    }
}


void Damier::MouvementDamier(int mouvement_execute)
{
    /* Le joueur décide d'aller à gauche */
    if (mouvement_execute == LEFT){
        /* Pour toutes les lignes : */
        for (int i = 0; i < Size; i++){
            /* On enregistre la ligne, et on remet à O la ligne du vrai tableau
            Pour pouvoir ensuite la mettre à jour */
            int *ligne = new int[Size];
            for (int j = 0; j < Size; j++){
                ligne[j] = dam[i][j];
                dam[i][j] = 0;
            }
            /* On supprime les 0 intermédiaires et on les met tous à gauche */
            int *index_d
            for (int j = 0; j < Size; j++){
                if ligne[j]
            }
        }
    }
}