#include "damier.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <QAbstractListModel>
using namespace std;
 
/* Constructeur */
Damier::Damier(QObject *parent):QObject(parent)
{
    Lancement_Du_Jeu(); 
}

void Damier::Lancement_Du_Jeu(){
    Size = 4;
    dam = new int*[Size];
    /* Ajout d'un tableau prÃ©cÃ©dent le dam pour revenir en arriÃ¨re */
    dam_precedent = new int*[Size];
    int score = 0;

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


/****** PremiÃ¨re Ã©tape, apparition des premiers chiffres ******/
/* MÃ©thode pour placer un 2 ou un 4 au hasard sur le damier */

int Damier::Get_Value(int i, int j){
    return dam[i][j];
}

void Damier::ApparitionPremiersChiffres()
{
    /* On initialise le gÃ©nÃ©rateur alÃ©atoire */
    srand(time(NULL));

    /* On les fait apparaÃ®tre dans un endroit random sur le damier */
    int i_apparition = rand()%Size;
    int j_apparition = rand()%Size;

    /* Il faut s'assurer que la case soit vide sinon il y aura chevauchement */
    while (dam[i_apparition][j_apparition] != 0){
        i_apparition = rand()%Size;
        j_apparition = rand()%Size;
    }
    
    /* Il faut maintenant crÃ©er du random entre 2 et 4 */
    int value = 2;

    //float borne_minimale = 0;
	//float borne_maximale = 1;

    /* On initialise les rand */

	//scanf("%f", &borne_minimale);
	//scanf("%f", &borne_maximale);
	
    /* Value sera 2 + 2*(un eniter random soit 0 soit 1) */

    //value += 2*((int)(rand() * (borne_maximale+1 - borne_minimale) / RAND_MAX + borne_minimale ));

    /* Et on met Ã  jour la case */
    dam[i_apparition][j_apparition] = value;
}

/* 2Ã¨me Ã©tape: On souhaite rajouter une fonction qui permet de revenir en arriÃ¨re */
/* Pour cela, il faut avoir 2 tableau. Celui qui sera affichÃ© et jouÃ©, et une copy 
de ce tableau au temps t-1 */
void Damier::Retour_en_arriere()
{
    /* Le principe est simple. Si le joueur veut revenir en arriÃ¨re, 
    on va copier le tableau qui est en jeu avec le prÃ©cedent.
    Il faut donc crÃ©er une fonction pour copier 2 tableaux */
    Copier_deux_tableaux(dam, dam_precedent);
}

/* MÃ©thode qui permet de copier deux tableaux */
void Damier::Copier_deux_tableaux(int ** tableau_1, int ** tableau_2){
    for (int i = 0; i < Size; i++){
        for (int j = 0; j < Size; j++){
            tableau_1[i][j] = tableau_2[i][j];
        }
    }
}

/* MÃ©thode de calcul de score : On a choisi de faire la sommes des tuiles du jeu */
void Damier::Calcul_du_score(){
    for (int i = 0; i < Size; i++){
        for (int j = 0; j < Size; j++){
            score += dam[i][j];
        }
    }
    /* On prévient du changement de score pour l'affichage */
    emit Chgt_Score();
}

/* Méthode qui permet de renvoyer le score, utile pour QML */
int Damier::Get_Score(){
    return score;
}

/* Méthode qui permet de savoir si le joueur a perdu ou pas*/
bool Damier::Lost(){
    for (int i=0; i<Size; i++){
        /* on parcours l'ensemble de la matrice*/
        for (int j=0; j<Size; j++){
            int x=dam[i][j];
            /*on vÃ©rifie qu'il ne reste pas une case vide*/
            if (x==0){
                return false;   
            /*on peut donc encore fusionner des cases*/ 
            /* On vÃ©rifie pour toutes les cases qu(elles ne peuvent plus bouger*/                                      
            } else if (i-1>=0 && x==dam[i-1][j]){         /*case en haut*/
                return false;
            }
            else if (i+1<=Size && x==dam[i+1][j]){     /*case en bas*/
                return false;
}
            else if (j-1>=0 && x==dam[i][j-1]){         /*case Ã  gauche*/
                return false;
            }
            else if (j+1<=Size && x==dam[i][j+1]){      /*case Ã  droite*/
                return false;
            }
        }
    }
    return true;                                      /*le joueur a perdu*/
}

/* MÃ©thode qui regarde si le joueur a gagnÃ© */
bool Damier::Win(){
    for (int i = 0; i < Size; i++){
        for (int j = 0; j < Size; j++){
            if (dam[i][j] == 2048){
                return true;
            }
        }
    }
    return false;
}

/* Affiche dans la console */

void Damier::Afficher_le_damier(){       /*afficher le damier sur le terminal*/
    for (int i= 0; i< Size; i++){
        for (int j=0; j< Size; j++){
            std::cout<<dam[i][j]<<' ';    /*on rajoute un espace pour plus de clartÃ©*/
        }
        std::cout<<std::endl;
        /* Affichage du score */
        std::cout << "Score : " << score << endl;     /*on revient Ã  la ligne pour chaque fin de ligne*/
    }
}

/* Fonction qui va permettre de gÃ©rer les mouvements des joueurs */
/* Passage aux vecteurs car plus praticables */
/* Argument: l'entier qui reprÃ©sente les mouvements : 
UP = 0,
DOWN = 1,
RIGHT = 2,
LEFT = 3 */
void Damier::MouvementDamier(int mouvement_execute)
{
    if (Lost() || Win()){
        /* On prévient qml que le joueur a gagné ou perdu */
        emit Gagne_ou_perdu();
    } else {
        /* Le joueur dÃ©cide d'aller Ã  gauche */
        if (mouvement_execute == LEFT){
            /* Pour toutes les lignes : */
            for (int i = 0; i < Size; i++){
                /* On enregistre la ligne, et on remet Ã  O la ligne du vrai tableau
                Pour pouvoir ensuite la mettre Ã  jour */
                int *ligne = new int[Size];
                for (int j = 0; j < Size; j++){
                    ligne[j] = dam[i][j];
                    dam[i][j] = 0;
                }

                /* CrÃ©ation du vecteur qui va gÃ©rer les fusions */
                std::vector<int> Ligne_LEFT;

                /* On rajoute tous les Ã©lÃ©ments de la ligne SAUF les 0 */
                for (int j = 0; j < Size; j++){
                    if (ligne[j] != 0){
                        Ligne_LEFT.push_back(ligne[j]);
                    }
                }

                /* Maintenant, Il faut procÃ©der aux fusions des chiffres en partant de la gauche */
                /* On procÃ¨de de la gauche vers la droite pour le mouvement LEFT, donc ici il faudra procÃ©der
                avec les premiers Ã©lÃ©ments du vecteur */

                /* EDOUARD ET MOI SOMMES CONFINÃ‰S ENSEMBLE, ON A RÃ‰FLÃ‰CHI Ã€ LA STRATÃ‰GIE POUR CE MOUVEMENT ENSMEBLE,
                PUIS ON S'EST SÃ‰PARÃ‰ LES AUTRES MOUVEMENTS */

                /* Plusieurs cas : 
                - Soit il n'y a aucun chiffre, dans ce cas lÃ  on passe parce que 
                le vecteur sera de taille nulle, et la ligne restera une ligne de 0 comme dÃ©jÃ  mise prÃ©cÃ©demment.
                - Soit il y a 1 chiffre, donc il le laisse sur la gauche. 
                - Soit il y a 2 chiffres. Dans ce cas lÃ , on les compare, et si ils sont Ã©gaux on fusionne, sinon non.
                Si il y a fusion, on place la fusion au dÃ©but de la ligne du vrai damier, et on supprime les Ã©lÃ©ments 
                fusionnÃ©s du vecteur.
                - Soit il y a 3 chiffres, on le problÃ¨me Ã  2 chiffres puis Ã  un chiffre.
                - Soit il y a 4 chiffres, on traitera le problÃ¨me Ã  2 chiffres 2 fois. */

                /* On introduit un index qui va permettre, pour les cas Ã  2, 3 ou 4 chiffres, de savoir,
                aprÃ¨s fusion ou non, oÃ¹ sont placÃ©s les Ã©lÃ©ments dans la ligne du vrai damier */

                int position_chiffre_dans_damier = 0;

                while (Ligne_LEFT.size() != 0){
                    /* Si il n'y a que 1 chiffre dans le vecteur : */
                    if (Ligne_LEFT.size() == 1){
                        /* On change le vrai tableau, et on met directement le chiffre
                        sur la gauche de la ligne concernÃ©e */
                        /* le .front() nous renvoi le premier Ã©lÃ©ment du vecteur, donc celui qui 
                        a Ã©tÃ© .push_back() en premier, trÃ¨s utile pour ne pas se prÃ©ocupper de la taille
                        du vecteur */
                        dam[i][position_chiffre_dans_damier] = Ligne_LEFT.front();
                        /* Et on vide le vecteur pour ne pas que le programme repasse dans ce if */
                        Ligne_LEFT.erase(Ligne_LEFT.begin());
                        /* Et enfin, on a placÃ© 1 Ã©lÃ©ment dans le vrai damier, donc on incrÃ©mente la position */
                        position_chiffre_dans_damier += 1;


                    /* Ensuite, qu'il y ai 2, 3 ou 4 chiffres, ils devront passer par cette case */    
                    } else if (Ligne_LEFT.size() >= 2){
                        int first_number = Ligne_LEFT.front();
                        Ligne_LEFT.erase(Ligne_LEFT.begin());
                        int second_number = Ligne_LEFT.front();

                        /* On teste les 2 premiers, si ils sont Ã©gaux, il y a fusion */
                        if (first_number == second_number){
                            /* Du coup, on place le double du chiffre en question, seul, Ã  gauche de la ligne
                            du vrai damier */
                            dam[i][position_chiffre_dans_damier] = first_number * 2;
                            /* Comme il y a fusion, il faut enlever les 2 chiffres */
                            Ligne_LEFT.erase(Ligne_LEFT.begin());
                            /* et on incrÃ©mente seulement de 1 la position dans le damier */
                            position_chiffre_dans_damier += 1;

                        /* Si il n'y a pas fusion */
                        } else {
                            /* On colle seulement le premier parce qu'il peut y avoir fusion entre le 
                            deuxieme et le troisieme */
                            dam[i][position_chiffre_dans_damier] = first_number;
                            /* On incrÃ©mente la position pour les prochains tours */
                            position_chiffre_dans_damier += 1;
                        }
                    }
                }
                
            }
            /* ProcÃ©dons Ã  un mouvement sur la DROITE, c'est sensiblement le meme schÃ©ma que prÃ©cÃ©dement,
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
                        /* La diffÃ©rence rÃ©side ici, ce sera dans l'autre sens */
                        Ligne_RIGHT.push_back(ligne[j]);
                    }
                }

                /* On part de la fin, et on dÃ©crÃ©mente */
                int position_chiffre_dans_damier = Size - 1;

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
                            Ligne_RIGHT.pop_back();
                            position_chiffre_dans_damier -= 1;

                        } else {
                            dam[i][position_chiffre_dans_damier] = last_number;
                            position_chiffre_dans_damier -= 1;
                        }
                    }
                }
            } 

        /* ProcÃ©dons Ã  un mouvement sur la droite, c'est sensiblement le meme schÃ©ma que prÃ©cÃ©dement,
        il n'y aura donc pas autant de commentaires */

        } else if (mouvement_execute == UP){
            for (int j = 0; j < Size; j++){
                int *colonne = new int[Size];
                for (int i = 0; i < Size; i++){
                    colonne[i] = dam[i][j];
                    dam[i][j] = 0;
                }
                std::vector<int> Colonne_UP;

                for (int i = 0; i < Size; i++){
                    if (colonne[i] != 0){
                        /* La diffÃ©rence rÃ©side ici, ce sera dans l'autre sens */
                        Colonne_UP.push_back(colonne[i]);
                    }
                }

                /* On part de la fin, et on dÃ©crÃ©mente */
                int position_chiffre_dans_damier = 0;

                while (Colonne_UP.size() != 0){
                    if (Colonne_UP.size() == 1){
                        dam[position_chiffre_dans_damier][j] = Colonne_UP.front();
                        Colonne_UP.erase(Colonne_UP.begin());
                        position_chiffre_dans_damier += 1;

                    } else if (Colonne_UP.size() >= 2){
                        int first_number = Colonne_UP.front();
                        Colonne_UP.erase(Colonne_UP.begin());
                        int second_number = Colonne_UP.front();

                        if (first_number == second_number){
                            dam[position_chiffre_dans_damier][j] = first_number * 2;
                            Colonne_UP.erase(Colonne_UP.begin());
                            position_chiffre_dans_damier += 1;

                        } else {
                            dam[position_chiffre_dans_damier][j] = first_number;
                            position_chiffre_dans_damier += 1;
                        }
                    }
                }
            }

            /* ProcÃ©dons Ã  un mouvement sur la droite, c'est sensiblement le meme schÃ©ma que prÃ©cÃ©dement,
            il n'y aura donc pas autant de commentaires */
            } else if (mouvement_execute == DOWN){
            for (int j = 0; j < Size; j++){
                int *colonne = new int[Size];
                for (int i = 0; i < Size; i++){
                    colonne[i] = dam[i][j];
                    dam[i][j] = 0;
                }
                std::vector<int> Colonne_DOWN;

                for (int i = 0; i < Size; i++){
                    if (colonne[i] != 0){
                        /* La diffÃ©rence rÃ©side ici, ce sera dans l'autre sens */
                        Colonne_DOWN.push_back(colonne[i]);
                    }
                }

                /* On part de la fin, et on dÃ©crÃ©mente */
                int position_chiffre_dans_damier = Size - 1;

                while (Colonne_DOWN.size() != 0){
                    if (Colonne_DOWN.size() == 1){
                        dam[position_chiffre_dans_damier][j] = Colonne_DOWN.back();
                        Colonne_DOWN.pop_back();
                        position_chiffre_dans_damier -= 1;

                    } else if (Colonne_DOWN.size() >= 2){
                        int first_number = Colonne_DOWN.back();
                        Colonne_DOWN.pop_back();
                        int second_number = Colonne_DOWN.back();

                        if (first_number == second_number){
                            dam[position_chiffre_dans_damier][j] = first_number * 2;
                            Colonne_DOWN.pop_back();
                            position_chiffre_dans_damier -= 1;

                        } else {
                            dam[position_chiffre_dans_damier][j] = first_number;
                            position_chiffre_dans_damier -= 1;
                        }
                    }
                }
            }
        }
        /* Sans oublier de dÃ©poser le 2 ou le 4 random */ 
        ApparitionPremiersChiffres();
        /* On met à jour le score */
        Calcul_du_score();
        /* On prévient qml qu'un mouvement a été fait */
        emit Le_Mouvement_a_ete_fait();
    }
}
