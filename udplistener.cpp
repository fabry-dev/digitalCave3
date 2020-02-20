#include "udplistener.h"

udpListener::udpListener(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(45454, QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

}




void udpListener::processPendingDatagrams()
{
    QByteArray datagram;

    while (socket->hasPendingDatagrams())
    {
        datagram.resize(int(socket->pendingDatagramSize()));
        socket->readDatagram(datagram.data(), datagram.size());

        QString nuMsg = datagram.constData();

        if(nuMsg.contains("quit"))
            exit(0);
        else if(nuMsg.contains("start"))
            emit startVideo();
        else if(nuMsg.contains("stop"))
            emit stopVideo();
        else
            qDebug()<<"udp unknown msg ["<<nuMsg<<" ]";
    }
}
