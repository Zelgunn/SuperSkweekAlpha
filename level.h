#ifndef LEVEL_H
#define LEVEL_H

#include <QDomElement>

#include "grid.h"
#include "gameobjets/player.h"
#include "gameobjets/monster.h"
#include "gameobjets/players/obiwan.h"
#include "gameobjets/players/darthvader.h"
#include "tile.h"
#include "projectilelist.h"
#include "weaponlist.h"
#include "playerinfo.h"

class Level : public QObject
{
    Q_OBJECT
public:
    Level(const QDomElement &element, QList<Player *> *prototypes, const QList<PlayerInfo *> &playersInfos);

    void setMyPlayer(int playerNumber);
    void initGridPlayerTiles();
    Grid *grid();
    Player *player(int index = 0) const;
    QList<Player *> players() const;
    const ProjectileList *projectiles() const;
    QSize tileSize() const;
    Tile *tiles() const;
    int width() const;
    int height() const;

    bool movePlayer(int playerId, GameObject::Directions direction);
    void arrowTileMove(int playerNumber);

    bool setPlayerPosition(int playerId, int x, int y, GameObject::Directions direction);

    bool playerFires(int playerId);
    ObiWan *obiWan() const;
    DarthVader *darthVader() const;

    double playerTileRatio(int player = 0) const;

    void nextFrame();

private slots:
    void onPlayerHit(GameObject *player, int type);

private:
    Grid *m_grid;
    //Player **m_players;
    QList<Player*> m_players;
    int m_myPlayer;
    ProjectileList *m_projectiles;
    WeaponList m_weapons;
    QSize m_tileSize;
    Tile *m_tiles;
    QString m_name;
};

#endif // LEVEL_H
