#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include "QDebug"
#include "QUdpSocket"
#include "QTimer"

#define msgStopVideo "stop"
#define msgStartVideo "start"
#define msgQuit "quit"


class udpListener : public QObject
{
    Q_OBJECT
public:
    explicit udpListener(QObject *parent = nullptr);

signals:
    void startVideo(void);
    void stopVideo(void);
public slots:
private slots:
    void processPendingDatagrams(void);
private:
    QUdpSocket *socket;
};

#endif // UDPLISTENER_H
