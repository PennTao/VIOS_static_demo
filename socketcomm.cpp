#include "socketcomm.h"

SocketComm::SocketComm(QObject *parent) :
    QObject(parent)
{
}

void SocketComm::connectToServer(QString host, qint16 port){
    socket = new QTcpSocket();
    inStream.setDevice(socket);
    connect(socket,SIGNAL(connected()),this,SLOT(onConnect()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(onDisconnect()),Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()),this, SLOT(onReadReady()),Qt::DirectConnection);
    socket->connectToHost(host,port);
    socket->waitForConnected(2000);

}

void SocketComm::sendToServer(QString & data){
    QByteArray outData;
    outData.append(data);
    socket->write(outData);
    qDebug() << "Sending data, data = "<< data;
}

void SocketComm::disconnectFromServer(){
    socket->close();

}

void SocketComm::onConnect()
{
    qDebug() << "Connected to Server";
}
void SocketComm::onDisconnect()
{
    qDebug() << "Disconnected from Server";
}
void SocketComm::onReadReady()
{
    qDebug() << "socket byteAvailable : " << socket->bytesAvailable();
    QString searchString;
    inStream>>searchString;


    qDebug() <<"contents" <<socket->readAll();
}
