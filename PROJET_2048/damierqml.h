#ifndef DAMIERQML_H
#define DAMIERQML_H

#include "damier.h"

#include <QObject>
#include <QAbstractListModel>



class DamierQML : public QObject {
    Q_OBJECT
    /* On veut écouter, l'affichage du score, si le joueur a gagné ou perdu 
    Pour le score, on veut la fonction qui renvoi l'entier.
    Pour gagné ou perdu, on veut celles qui renvoient le booléen. */
    Q_PROPERTY(int Get_Score READ Get_Score NOTIFY Chgt_Score)
    Q_PROPERTY(bool Lost READ Lost NOTIFY Gagne_ou_perdu)
    Q_PROPERTY(bool Win READ Win NOTIFY Gagne_ou_perdu)

public:
    explicit DamierQML(QObject *parent = 0);

    /* Le QML va devoir aussi écouter le score et les win/lost, ce qui change en fait */
    int Get_Score() const;
    bool Lost();
    bool Win();

    /* Appliquer cette macro aux déclarations de fonctions des membres
    pour permettre de les invoquer via le système de méta-objets*/
    // Aller en haut
    Q_INVOKABLE void MouvementDamier(0)
    // Aller en bas
    Q_INVOKABLE void MouvementDamier(1)
    // Aller à droite
    Q_INVOKABLE void MouvementDamier(2)
    // Aller à gauche
    Q_INVOKABLE void MouvementDamier(3)

private:
    Damier dam;

signals:
    void Chgt_Score();
    void Gagne_ou_perdu();

public slots:
    void Chgt_Donnees();
    
};

#endif // GRILLE_H