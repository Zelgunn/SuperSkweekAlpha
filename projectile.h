#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"

class Projectile : public GameObject
{
public:
    Projectile();
    Projectile(Directions direction, int ownerID);
    Projectile(const QDomElement &element);
    ~Projectile();

    void move(double ratio);

    const QPixmap *model() const;
    int ttl() const;

    int ownerID() const;
    void setOwnerID(int ownerID);

private:
    int m_ttl;
    int m_ownerID;
};

#endif // PROJECTILE_H
