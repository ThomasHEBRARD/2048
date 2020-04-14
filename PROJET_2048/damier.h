#ifndef DAMIER_H
#define DAMIER_H

/* Le Damier va maintenat hériter de la classe QObject */
class Damier : public QObject{
    Q_OBJECT
    Q_PROPERTY(int Get_Score READ Get_Score NOTIFY Chgt_Donnee)
    private:
        int Size;
        int ** dam;
        int ** dam_precedent;

    public:

        explicit Damier(QObject *parent = 0)
        Damier(int size);
        ~Damier();
        void ApparitionPremiersChiffres();
        void Retour_en_arriere();
        bool Lost();
        void Copier_deux_tableaux(int ** tableau_1, int ** tableau_2);
        void Afficher_le_damier();
        void MouvementDamier(int mouvement_execute);

    signals:
        /* Les signaux dès que:
        Un mouvement est fait */
        void Le_Mouvement_a_ete_fait(); 
        /* Le joueur a gagné ou perdu*/

        ///// NE PAS OUBLIER DE PR2VENIR LE CHANGEMENT 
        void Gagne_ou_perdu();
        /* Le score change */

        //////// NE PAS OUBLIER DE EMETTRE LE CHANGEMENT DE SCORE SUR LE MASTER 
        void Chgt_Donnee;
};

/* On va utiliser les flèches directionnelles, donc il faut leur attitrer des
variables pour les reconnaitre et mettre des listener */
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;


#endif // DAMIER_H
