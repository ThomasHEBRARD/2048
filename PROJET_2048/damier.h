#ifndef DAMIER_H

class Damier
{
    private:
        int Size;

    public:
        Damier(int size);
        ~Damier();
}

/* On va utiliser les flèches directionnelles, donc il faut leur attitrer des 
variables pour les reconnaitre et mettre des listener */
const int UP = 0;
const int DOWN = 1;
const int RIGHT = 2;
const int LEFT = 3;

#endif // DAMIER_H