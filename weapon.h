#ifndef WEAPON_H
#define WEAPON_H

#include <QTime>
#include "gameobjets/projectile.h"

class Weapon
{
public:
    Weapon();
    Weapon(const QDomElement &element);

    int ammunition() const;
    void setAmmunition(int ammunitionType);
    int fire();

private:
    int m_ammunitionType;
    double m_reloadTime;
    QTime m_lastUse;

};

#endif // WEAPON_H
