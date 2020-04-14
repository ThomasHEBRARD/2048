#include "damierqml.h"

DamierQML::DamierQML(QObject *parent) :
    QAbstractListModel(parent)
{
}



/* On va maintenant traduire nos fonctions pour que QML puisse les interpréter */

void DamierQML::UP(){
    dam.MouvementDamier(0);
}

void DamierQML::DOWN(){
    dam.MouvementDamier(1);
}

void DamierQML::RIGHT(){
    dam.MouvementDamier(2);
}

void DamierQML::LEFT(){
    dam.MouvementDamier(3);
}

void DamierQML::(){
    /* Va créer (et émettre) un model index pour une ligne et colonne donnée */
    emit dataChanged(createIndex(0,0), createIndex(15,0))
}

/* Méthode Win */
bool DamierQML::Win(){
    return dam.Win();
}

/* Méthode Lost */
bool DamierQML::Lost(){
    return dam.Lost();
}

/* La méthode Get_Score qui sera utile pour afficher le score */
int DamierQML::Get_Score() const{
    return dam.Get_Score();
}