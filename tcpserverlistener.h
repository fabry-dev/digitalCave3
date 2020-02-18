#ifndef TCPSERVERLISTENER_H
#define TCPSERVERLISTENER_H

#include <QObject>
#include "QTcpSocket"
#include "qdatastream.h"
#include "qthread.h"


class tcpServerListener;

class tcpServerControl : public QObject
{
    Q_OBJECT
public:
    explicit tcpServerControl(QObject *parent = nullptr, QString ip="", qint64 port=60000);

    QThread *workerThread;
    tcpServerListener *listener;
};


class tcpServerListener : public QObject
{
    Q_OBJECT
public:
    explicit tcpServerListener(QObject *parent = nullptr, QString ip="", qint64 port=60000);
signals:
    void startVideo(void);
    void stopVideo(void);
private:
    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString ip;
    qint64 port;
private slots:
    void process(void);
    void newDataToRead(void);
    void displayError(QAbstractSocket::SocketError socketError);
public slots:
};




#endif // TCPSERVERLISTENER_H
