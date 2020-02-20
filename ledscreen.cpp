#include "ledscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qthread.h"
#include "qlayout.h"

#include "qmediaplayer.h"

#include "positions.h"




ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{

    resize(960,1152);

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(true);
    bgVp->show();

    connect(bgVp,SIGNAL(videoRestart()),this,SIGNAL(bgRestart()));


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setMute(true);
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->show();





    QTimer::singleShot(10,this,SLOT(loadPlayer()));


    for(int i = 0;i<16;i++)
    {

        QPixmap pix(PATH+"award/"+QString::number(i)+".png");
       // pix = pix.scaled((double)pix.width()*ledAwardsRatio,(double)pix.height()*ledAwardsRatio);
        QRect hideG = touch2led(QRect(buttonsTouchX[i]-pix.width()/2,buttonsTouchY[i]-pix.height()/2,pix.width(),pix.height()));
        QRect showG = QRect(buttonsLedX[i],buttonsLedY[i],pix.width()*ledAwardsRatio,pix.height()*ledAwardsRatio);

        powerLabel *b = new powerLabel(this,i,hideG,showG,false,false);
        b->setPixmap(pix);
        b->setScaledContents(true);


        awardButtons.push_back(b);
    }


    QLabel *touchLbl = new QLabel(this);
    touchLbl->resize(1080*Touch2LedRatio,1920*Touch2LedRatio);
    touchLbl->move((width()-touchLbl->width())/2,(height()-touchLbl->height())/2);
    touchLbl->setStyleSheet("border: 1px solid red");
    touchLbl->show();



}

void ledScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"ledBg3.mp4");
    bgVp->play();

    introVp->lower();
   introVp->loadFilePaused(PATH+"ledIntro3.mp4");
}



void ledScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void ledScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}



void ledScreen::showAwards(void)
{

    for(auto b:awardButtons)
    {
        if(b->getId() == 13)
            continue;
        b->animateShow();
    }


}

void ledScreen::hideAwards(void)
{

    for(auto b:awardButtons)
    {
        if(b->getId() == 13)
            continue;
        b->animateHide();
    }
}





QRect ledScreen::touch2led(QRect original)
{

    double offsetX = (width()-1080*Touch2LedRatio)/2;
    double offsetY = (height()-1920*Touch2LedRatio)/2;


    return QRect((double)original.x()*Touch2LedRatio+offsetX,(double)original.y()*Touch2LedRatio+offsetY,(double)original.width()*Touch2LedRatio,(double)original.height()*Touch2LedRatio);

}





void ledScreen::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == 16777216)
        exit(0);



    //qDebug()<<ev->key();
}



