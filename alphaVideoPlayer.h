#ifndef TRANSPARENTVIDEODRAWER_H
#define TRANSPARENTVIDEODRAWER_H


#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "QMainWindow"
#include "QGraphicsVideoItem"
#include "QAbstractVideoSurface"
#include "qlabel.h"
#include "qobject.h"





class alphaVideoDrawer : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    alphaVideoDrawer(QLabel *displayLbl);


private:
    QLabel *displayLbl;

protected:
    bool present(const QVideoFrame &frame);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const
    {
        Q_UNUSED(handleType);

        // Return the formats you will support
        return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_ARGB32;
    }
};


class alphaVideo : public QLabel
{
    Q_OBJECT
public:
    alphaVideo(QLabel *parent = nullptr);
    void addMedia(QString mediaURL);
    void setLoop(bool loop);


private:
    alphaVideoDrawer *videoDrawer;
    QMediaPlayer *videoPlayer;
    QMediaPlaylist *playlist;


public slots:
    void play(void);
    void stop(void);

private slots:
    void newMediaStatus(QMediaPlayer::MediaStatus status);

signals:
    void startedPlaying(void);
    void stoppedPlaying(void);
    void gotPainted(const QPixmap*);

protected:
    void paintEvent(QPaintEvent *e);

};









#endif // TRANSPARENTVIDEODRAWER_H
