#ifndef SOCKETCOMM_H
#define SOCKETCOMM_H

#include <QObject>
#include <QTcpSocket>
#include <sstream>
#include <QDataStream>
using namespace std;
class SocketComm : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    QDataStream inStream;
public:
    explicit SocketComm(QObject *parent = 0);
    void connectToServer(QString host, qint16 port);
    void disconnectFromServer();
    void sendToServer(QString &data);

signals:

public slots:
    void onConnect();
    void onDisconnect();
    void onReadReady();

};

#endif // SOCKETCOMM_H
