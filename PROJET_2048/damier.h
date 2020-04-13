#ifndef DAMIER_H

class Damier
{
    private:
        int Size;
        int ** dam;
        int ** dam_precedent;

    public:
        Damier(int size);
        ~Damier();
        void ApparitionPremiersChiffres();
        void Retour_en_arriere();
        void Copier_tableaux(int ** tableau_1, int ** tableau_2);
};

/* On va utiliser les flèches directionnelles, donc il faut leur attitrer des 
        bool Lost();
        void Afficher_le_damier();
};

/* On va utiliser les flèches directionnelles, donc il faut leur attitrer des
variables pour les reconnaitre et mettre des listener */
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;

#endif // DAMIER_H
