#ifndef DAMIERQML_H
#define DAMIERQML_H

#include <QObject>
#include <QStringList>


class DamierQML : public QObject {
    Q_OBJECT
    /* On veut écouter, l'affichage du score, si le joueur a gagné ou perdu 
    Pour le score, on veut la fonction qui renvoi l'entier.
    Pour gagné ou perdu, on veut celles qui renvoient le booléen. */
    Q_PROPERTY(int Get_Score READ Get_Score NOTIFY Chgt_Donnes)
    Q_PROPERTY(bool Lost READ Lost NOTIFY Gagne_ou_perdu)
    Q_PROPERTY(bool Win READ Win NOTIFY Gagne_ou_perdu)

public:


signals:
    void Chgt_Score();
    void Gagne_ou_perdu;

public slots:
    void Chgt_Donnees();
    
private:
    Damier dam;

};

#endif // GRILLE_H