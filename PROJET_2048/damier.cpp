#include "damier.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/* Constructeur */
Damier::Damier(int size)
{
    /* Déclaration des variables */
    Size = size;
    dam = new int*[Size];
    /* Ajout d'un tableau précédent le dam pour revenir en arrière */
    dam_precedent = new int*[Size];

    /* Construction du Damier sous forme de tableau */
    for (int i = 0; i < Size; i++){
        dam[i] = new int[Size];
        for (int j = 0; j < Size; j++){
            dam[i][j] = 0;
        }
    }

    /* On Fait apparaitre le premier 2 ou 4 */
    ApparitionPremiersChiffres();    
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

	scanf("%f", &borne_minimale);
	scanf("%f", &borne_maximale);
	
    /* Value sera 2 + 2*(un eniter random soit 0 soit 1) */

    value += 2*((int)(rand() * (borne_maximale+1 - borne_minimale) / RAND_MAX + borne_minimale ));

    /* Et on met à jour la case */
    dam[i_apparition][j_apparition] = value;
}

/* 2ème étape: On souhaite rajouter une fonction qui permet de revenir en arrière */
/* Pour cela, il faut avoir 2 tableau. Celui qui sera affiché et joué, et une copy 
de ce tableau au temps t-1 */
void Damier::Retour_en_arriere(int ** tableau_1, int ** tableau_2)
{
    /* Le principe est simple. Si le joueur veut revenir en arrière, 
    on va copier le tableau qui est en jeu avec le précedent.
    /* On boucle sur toutes les cases */
    for (int i = 0; i < Size; i++){
        for (int j = 0; j < Size; j++){
            /* On copie */
            tableau_1[i][j] = tableau_2[i][j];
        }
    }
}

bool Damier::Lost(){
    for (int i=0; i<Size; i++){
        /* on parcours l'ensemble de la matrice*/
        for (int j=0; j<Size; j++){
            int x=dam[i][j];
            /*on vérifie qu'il ne reste pas une case vide*/
            if (x==0){
                return false;   
            /*on peut donc encore fusionner des cases*/ 
            /* On vérifie pour toutes les cases qu(elles ne peuvent plus bouger*/                                      
            } else if (i-1>=0 && x==dam[i-1][j]){         /*case en haut*/
                return false;
            }
            else if (i+1<=Size && x==dam[i+1][j]){     /*case en bas*/
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

void Damier::Afficher_le_damier(){       /*afficher le damier sur le terminal*/
    for (int i= 0; i< Size; i++){
        for (int j=0; j< Size; j++){
            std::cout<<dam[i][j]<<' ';    /*on rajoute un espace pour plus de clarté*/
        }
        std::cout<<std::endl;       /*on revient à la ligne pour chaque fin de ligne*/
    }
}

/* Fonction qui va permettre de gérer les mouvements des joueurs */
/* Passage aux vecteurs car plus praticables */
/* Argument: l'entier qui représente les mouvements : 
UP = 0,
DOWN = 1,
RIGHT = 2,
LEFT = 3 */
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
            std::vector<int> Ligne_LEFT;

            /* On rajoute tous les éléments de la ligne SAUF les 0 */
            for (int j = 0; j < Size; j++){
                if (ligne[j] != 0){
                    Ligne_LEFT.push_back(ligne[j]);
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

            while (Ligne_LEFT.size() != 0){
                /* Si il n'y a que 1 chiffre dans le vecteur : */
                if (Ligne_LEFT.size() == 1){
                    /* On change le vrai tableau, et on met directement le chiffre
                    sur la gauche de la ligne concernée */
                    /* le .front() nous renvoi le premier élément du vecteur, donc celui qui 
                    a été .push_back() en premier, très utile pour ne pas se préocupper de la taille
                    du vecteur */
                    dam[i][position_chiffre_dans_damier] = Ligne_LEFT.front();
                    /* Et on vide le vecteur pour ne pas que le programme repasse dans ce if */
                    Ligne_LEFT.erase(Ligne_LEFT.begin());
                    /* Et enfin, on a placé 1 élément dans le vrai damier, donc on incrémente la position */
                    position_chiffre_dans_damier += 1;


                /* Ensuite, qu'il y ai 2, 3 ou 4 chiffres, ils devront passer par cette case */    
                } else if (Ligne_LEFT.size() >= 2){
                    int first_number = Ligne_LEFT.front();
                    Ligne_LEFT.erase(Ligne_LEFT.begin());
                    int second_number = Ligne_LEFT.front();

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
                        Ligne_LEFT.erase(Ligne_LEFT.begin());
                        /* On incrémente la position pour les prochains tours */
                        position_chiffre_dans_damier += 1;
                    }
                }
            }
            
        }
        /* Procédons à un mouvement sur la DROITE, c'est sensiblement le meme schéma que précédement,
        il n'y aura donc pas autant de commentaires */
    } else if (mouvement_execute == RIGHT){
        for (int i = 0; i < Size; i++){
            int *ligne = new int[Size];
            for (int j = 0; j < Size; j++){
                ligne[j] = dam[i][j];
                dam[i][j] = 0;
            }
            std::vector<int> Ligne_RIGHT;

            for (int j = 0; j < Size; j++){
                if (ligne[j] != 0){
                    /* La différence réside ici, ce sera dans l'autre sens */
                    Ligne_RIGHT.push_back(ligne[j]);
                }
            }

            /* On part de la fin, et on décrémente */
            int position_chiffre_dans_damier = 3;

            while (Ligne_RIGHT.size() != 0){
                if (Ligne_RIGHT.size() == 1){
                    dam[i][position_chiffre_dans_damier] = Ligne_RIGHT.back();
                    Ligne_RIGHT.pop_back();
                    position_chiffre_dans_damier -= 1;
 
                } else if (Ligne_RIGHT.size() >= 2){
                    int last_number = Ligne_RIGHT.back();
                    Ligne_RIGHT.pop_back();
                    int before_last_number = Ligne_RIGHT.back();

                    if (last_number == before_last_number){
                        dam[i][position_chiffre_dans_damier] = last_number * 2;
                        position_chiffre_dans_damier -= 1;

                    } else {
                        dam[i][position_chiffre_dans_damier] = last_number;
                        Ligne_RIGHT.pop_back();
                        position_chiffre_dans_damier -= 1;
                    }
                }
            }
        } 

    /* Procédons à un mouvement sur la droite, c'est sensiblement le meme schéma que précédement,
    il n'y aura donc pas autant de commentaires */

    } else if (mouvement_execute == UP){
        for (int j = 0; j < Size; j++){
            int *colonne = new int[Size];
            for (int i = 0; i < Size; i++){
                colonne[i] = dam[i][j];
                dam[i][j] = 0;
            }
            std::vector<int> Colonne_UP;

            for (int i = 0; i < Size; j++){
                if (colonne[i] != 0){
                    /* La différence réside ici, ce sera dans l'autre sens */
                    Colonne_UP.push_back(colonne[i]);
                }
            }

            /* On part de la fin, et on décrémente */
            int position_chiffre_dans_damier = 0;

            while (Colonne_UP.size() != 0){
                if (Colonne_UP.size() == 1){
                    dam[j][position_chiffre_dans_damier] = Colonne_UP.front();
                    Colonne_UP.erase(Colonne_UP.begin());
                    position_chiffre_dans_damier += 1;
 
                } else if (Colonne_UP.size() >= 2){
                    int first_number = Colonne_UP.front();
                    Colonne_UP.erase(Colonne_UP.begin());
                    int second_number = Colonne_UP.front();

                    if (first_number == second_number){
                        dam[j][position_chiffre_dans_damier] = first_number * 2;
                        position_chiffre_dans_damier += 1;

                    } else {
                        dam[j][position_chiffre_dans_damier] = first_number;
                        Colonne_UP.erase(Colonne_UP.begin());
                        position_chiffre_dans_damier += 1;
                    }
                }
            }
        }

        /* Procédons à un mouvement sur la droite, c'est sensiblement le meme schéma que précédement,
        il n'y aura donc pas autant de commentaires */
        } else if (mouvement_execute == DOWN){
        for (int j = 0; j < Size; j++){
            int *colonne = new int[Size];
            for (int i = 0; i < Size; i++){
                colonne[i] = dam[i][j];
                dam[i][j] = 0;
            }
            std::vector<int> Colonne_DOWN;

            for (int i = 0; i < Size; j++){
                if (colonne[i] != 0){
                    /* La différence réside ici, ce sera dans l'autre sens */
                    Colonne_DOWN.push_back(colonne[i]);
                }
            }

            /* On part de la fin, et on décrémente */
            int position_chiffre_dans_damier = 3;

            while (Colonne_DOWN.size() != 0){
                if (Colonne_DOWN.size() == 1){
                    dam[j][position_chiffre_dans_damier] = Colonne_DOWN.back();
                    Colonne_DOWN.pop_back();
                    position_chiffre_dans_damier -= 1;
 
                } else if (Colonne_DOWN.size() >= 2){
                    int first_number = Colonne_DOWN.back();
                    Colonne_DOWN.pop_back();
                    int second_number = Colonne_DOWN.back();

                    if (first_number == second_number){
                        dam[j][position_chiffre_dans_damier] = first_number * 2;
                        position_chiffre_dans_damier -= 1;

                    } else {
                        dam[j][position_chiffre_dans_damier] = first_number;
                        Colonne_DOWN.pop_back();
                        position_chiffre_dans_damier -= 1;
                    }
                }
            }
        }
        /* Sans oublier de déposer le 2 ou le 4 random */
        ApparitionPremiersChiffres();
    }
}