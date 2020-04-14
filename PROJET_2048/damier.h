#ifndef DAMIER_H
#define DAMIER_H

/* Le Damier va maintenat hériter de la classe QObject */
class Damier : public QObject{
    Q_OBJECT
    /* On va chercher à faire apparaitre le score */
    Q_PROPERTY(int Get_Score READ Get_Score NOTIFY Chgt_Score)

    private:
        int Size;
        int ** dam;
        int ** dam_precedent;
        int score;

    public:

        explicit Damier(QObject *parent = 0)
        Damier(int size);
        ~Damier();
        void ApparitionPremiersChiffres();
        void Retour_en_arriere();
        bool Lost();
        bool Win();
        void Calcul_du_score();
        void Copier_deux_tableaux(int ** tableau_1, int ** tableau_2);
        void Afficher_le_damier();
        void MouvementDamier(int mouvement_execute);

    signals:
        /* Les signaux dès que:
        Un mouvement est fait */
        void Le_Mouvement_a_ete_fait(); 
        /* Le joueur a gagné ou perdu*/

        /* Écoute pour Changement lorsque le joueur a gagné ou perdu */
        void Gagne_ou_perdu();
        /* Le score change */

        /* Écoute pour Changement du score */
        void Chgt_Score();
};

/* On va utiliser les flèches directionnelles, donc il faut leur attitrer des
variables pour les reconnaitre et mettre des listener */
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;


#endif // DAMIER_H
