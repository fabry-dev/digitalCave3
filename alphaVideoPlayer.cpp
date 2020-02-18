#include "alphaVideoPlayer.h"


alphaVideo::alphaVideo(QLabel *parent): QLabel(parent)
{
    setStyleSheet("QLabel { background-color : transparent; }");
    videoDrawer = new alphaVideoDrawer(this);
    videoPlayer = new QMediaPlayer(this);
    playlist = new QMediaPlaylist();

    videoPlayer->setPlaylist(playlist);
    videoPlayer->setVideoOutput(videoDrawer);
    connect(videoPlayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(newMediaStatus(QMediaPlayer::MediaStatus)));

    setLoop(false);
}


void alphaVideo::paintEvent(QPaintEvent *e)
{

    QLabel::paintEvent(e);
    emit gotPainted(pixmap());
}




void alphaVideo::setLoop(bool loop)
{

    if(loop)
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    else
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

}


void alphaVideo::addMedia(QString mediaURL)
{
    playlist->clear();
    playlist->addMedia( QUrl::fromLocalFile(mediaURL) );

}


void alphaVideo::play(void)
{
    videoPlayer->play();
}


void alphaVideo::stop()
{
    videoPlayer->stop();
}


void alphaVideo::newMediaStatus(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
    case QMediaPlayer::BufferedMedia:
     //   qDebug()<<"play";
        emit startedPlaying();
        break;
    case QMediaPlayer::EndOfMedia:
     //   qDebug()<<"stopped";
        emit stoppedPlaying();
        break;
    default:
        break;
    }
  //  qDebug()<<status;

}





alphaVideoDrawer::alphaVideoDrawer(QLabel *displayLbl):displayLbl(displayLbl)
{

}

extern QImage qt_imageFromVideoFrame(const QVideoFrame &f);


bool alphaVideoDrawer::present(const QVideoFrame &frame)
{
    Q_UNUSED(frame);
    // Handle the frame and do your processing

    QImage image = qt_imageFromVideoFrame(frame);
    displayLbl->setPixmap(QPixmap::fromImage(image));
    return true;
}
