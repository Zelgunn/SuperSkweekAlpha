#ifndef MULTIPLAYERUPDATER_H
#define MULTIPLAYERUPDATER_H

#include <QStringList>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTimer>
#include <QTime>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

#include "playerinfo.h"

#define PORT_COM 45454

class MultiplayerUpdater : public QTcpServer
{
    Q_OBJECT
public:
    MultiplayerUpdater();

    void appendUpdate(const QString &update);
    void sendUpdates();
    QStringList receivedUpdates();
    bool isConnected() const;

    void startHost(bool enable = true);
    void lookForLocalHost();
    void connectToIP(const QString &ip);

    QString mapPath() const;
    void setMapPath(const QString &mapPath);

    QList<PlayerInfo *> playersInfos() const;
    void connectToPlayer2();

protected:
    void sendUpdate(const QString &update);
    void incomingConnection(int socketfd);

protected slots:
    void broadcastAddress();
    void readUdp();
    void readTcp();
    void disconnected();

signals:
    void newConnection();

private:
    QStringList m_updates;
    QStringList m_receivedUpdates;
    QUdpSocket *m_udpSocket;
    QTcpSocket *m_client;
    QHostAddress m_localAddress;
    QList<PlayerInfo *> m_playersInfos;
    QString m_mapPath;
    QTimer *m_timer;
};

#endif // MULTIPLAYERUPDATER_H
