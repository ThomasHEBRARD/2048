#include "damier.h"
#include <iostream>
#include <vector>

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

/* Fonction qui va permettre de gérer les mouvements des joueurs */
/* Passage aux vecteurs car plus praticables */
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
            /* Création du vecteur qui va gérer les fusions */
            std::vector<int> Ligne;
            /* On rajoute tous les éléments de la ligne SAUF les 0 */
            for (int j = 0; j < Size; j++){
                if (ligne[j] != 0){
                    Ligne.push_back(ligne[j]);
                }
            }

            /* Maintenant, Il faut procéder aux fusions des chiffres en partant de la gauche */
            /* On procède de la gauche vers la droite pour le mouvement LEFT, donc ici il faudra procéder
            avec les premiers éléments du vecteur */

            /* EDOUARD ET MOI SOMMES CONFINÉS ENSEMBLE, ON A RÉFLÉCHI À LA STRATÉGIE POUR CE MOUVEMENT ENSMEBLE,
            PUIS ON S'EST SÉPARÉ LES AUTRES MOUVEMENTS */

            /* Plusieurs cas : 
            - Soit il n'y a aucun chiffre, dans ce cas là on passe parce que 
            le vecteur sera de taille nulle, et la ligne restera une ligne de 0 comme déjà mise précédemment.
            - Soit il y a 1 chiffre, donc il le laisse sur la gauche. 
            - Soit il y a 2 chiffres. Dans ce cas là, on les compare, et si ils sont égaux on fusionne, sinon non.
            Si il y a fusion, on place la fusion au début de la ligne du vrai damier, et on supprime les éléments 
            fusionnés du vecteur.
            - Soit il y a 3 chiffres, on le problème à 2 chiffres puis à un chiffre.
            - Soit il y a 4 chiffres, on traitera le problème à 2 chiffres 2 fois. */

            /* On introduit un index qui va permettre, pour les cas à 2, 3 ou 4 chiffres, de savoir,
            après fusion ou non, où sont placés les éléments dans la ligne du vrai damier */

            int position_chiffre_dans_damier = 0;

            while (Ligne.size() != 0){
                /* Si il n'y a que 1 chiffre dans le vecteur : */
                if (Ligne.size() == 1){
                    /* On change le vrai tableau, et on met directement le chiffre
                    sur la gauche de la ligne concernée */
                    /* le .front() nous renvoi le premier élément du vecteur, donc celui qui 
                    a été .push_back() en premier, très utile pour ne pas se préocupper de la taille
                    du vecteur */
                    dam[i][position_chiffre_dans_damier] = Ligne.front();
                    /* Et on vide le vecteur pour ne pas que le programme repasse dans ce if */
                    Ligne.erase(0);
                    /* Et enfin, on a placé 1 élément dans le vrai damier, donc on incrémente la position */
                    position_chiffre_dans_damier += 1;


                /* Ensuite, qu'il y ai 2, 3 ou 4 chiffres, ils devront passer par cette case */    
                } else if (Ligne.size() >= 2){
                    int first_number = Ligne.front();
                    Ligne.erase(0);
                    int second_number = Ligne.front();

                    /* On teste les 2 premiers, si ils sont égaux, il y a fusion */
                    if (first_number == second_number){
                        /* Du coup, on place le double du chiffre en question, seul, à gauche de la ligne
                        du vrai damier */
                        dam[i][position_chiffre_dans_damier] = first_number * 2;

                        /* et on incrémente seulement de 1 la position dans le damier */
                        position_chiffre_dans_damier += 1;

                    /* Si il n'y a pas fusion */
                    } else {
                        /* On colle seulement le premier parce qu'il peut y avoir fusion entre le 
                        deuxieme et le troisieme */
                        dam[i][position_chiffre_dans_damier] = first_number;
                        /* et on enlève seulement le premier chiffre, pour justement
                        tester la fusion entre le 2eme et le potentiel 3eme */
                        Ligne.erase(0);
                        /* On incrémente la position pour les prochains tours */
                        position_chiffre_dans_damier += 1;
                    }
                }
            }

            /* Les autres mouvements */
            
        }
    }
}