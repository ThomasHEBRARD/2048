#ifndef DAMIERQML_H
#define DAMIERQML_H

#include <QObject>
#include <QStringList>


class DamierQML : public QObject {
    Q_OBJECT
    Q_PROPERTY(int Calcul_du_Score READ  NOTIFY )

public:


signals:


public slots:

private:

};

#endif // GRILLE_H