#include "damierqml.h"
#include <QAbstractListModel>

DamierQML::DamierQML(QObject *parent) :
    QAbstractListModel(parent)
{
    /*  Connexion des es écouteurs */
    connect(&dam, &Damier::Chgt_Score, this, &DamierQML::Chgt_Score);
    connect(&dam, &Damier::Gagne_ou_perdu, this, &DamierQML::Gagne_ou_perdu);
    connect(&dam, &Damier::Le_Mouvement_a_ete_fait, this, &DamierQML::Chgt_Donnees);
}

/* Nombre cases */
int DamierQML::NombreCases(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 16;
}

/* Méthode de renseignement, assurance bonnes cases*/
/* QVariant agit comme l'union des types */
QVariant DamierQML::data(const QModelIndex &index, int role) {
    if (index.row() < 0 || index.row() >= 4 * 4) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        int i = index.row() % 4;
        int y = index.row() / 4;
        QString str = QString::number(dam.Get_Value(i, j));
        return str;
    }
    return QVariant();
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

void DamierQML::Chgt_Donnees(){
    /* Va créer (et émettre) un model index pour une ligne et colonne donnée */
    emit dataChanged(createIndex(0,0), createIndex(15,0));
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
int DamierQML::Get_Score(){
    return dam.Get_Score();
}
