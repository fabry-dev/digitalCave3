#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"

#include "positions.h"

#define TIMEOUT_DELAY 30*1000

touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1080,1920);

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();

    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewindAndPlay()));

    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->setMute(false);
    introVp->show();

    timeOutTimer = new QTimer(this);
    connect(timeOutTimer,SIGNAL(timeout()),this,SLOT(showAwardsList()));

    QLabel *iktvaLbl = new QLabel(this);
    QImage iktva(PATH+"iktva.png");
    iktvaLbl->resize(iktva.size());
    iktvaLbl->setPixmap(QPixmap::fromImage(iktva));
    iktvaLbl->move((width()-iktvaLbl->width())/2,1920-iktvaLbl->height()/2-100);
    iktvaLbl->show();


    for(int i = 0;i<16;i++)
    {


        QPixmap pix(PATH+"award/"+QString::number(i)+".png");
        QRect showG = QRect(buttonsTouchX[i]-pix.width()/2,buttonsTouchY[i]-pix.height()/2,pix.width(),pix.height());
        QRect hideG = led2screen(QRect(buttonsLedX[i],buttonsLedY[i],pix.width()*ledAwardsRatio,pix.height()*ledAwardsRatio));

        powerLabel *b = new powerLabel(this,i,hideG,showG,false,true);
        b->setPixmap(pix);
        b->setScaledContents(true);

        connect(b,SIGNAL(clicked()),this,SLOT(buttonClick()));
        awardButtons.push_back(b);
    }


    QTimer::singleShot(10,this,SLOT(loadPlayer()));

    int backY = 1500;
    QPixmap pix(PATH+"back.png");
    backLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-pix.width())/2,backY,pix.width(),pix.height()),true);
    backLbl->hide();
    backLbl->setPixmap(pix);
    backLbl->setScaledContents(true);
    connect(backLbl,SIGNAL(clicked()),this,SLOT(showAwardsList()));



    for(int i = 0;i<16;i++)
    {


        int yearY = 200;
        QPixmap yearPix(PATH+"year/"+QString::number(i)+".png");
        powerLabel *yearLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-yearPix.width())/2,yearY,yearPix.width(),yearPix.height()),false);
        yearLbl->hide();
        yearLbl->setPixmap(yearPix);
        yearLbl->setScaledContents(true);



        int titleY = 400;
        QPixmap titlePix(PATH+"title/"+QString::number(i)+".png");
        powerLabel *titleLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-titlePix.width())/2,titleY,titlePix.width(),titlePix.height()),false);
        titleLbl->hide();
        titleLbl->setPixmap(titlePix);
        titleLbl->setScaledContents(true);




        int logoY = 900;
        int logoX = 100;
        int logoWidth=640;
        int trophyY = 800;
        int trophyX = 650;

        powerLabel *logoLbl;

        if((i == 5)||(i==6)||(i==7)||(i==12))
        {
            logoLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect(logoX,logoY,640,360),false);
            logoPlayer = new mpvWidget(logoLbl);
            logoPlayer->resize(640,360);
            logoPlayer->setProperty("keep-open","yes");
            logoPlayer->setLoop(true);
            logoPlayer->show();
            logoPlayer->setFileToLoad(PATH+"logo/"+QString::number(i)+".mp4");

            QLabel *blackLbl = new QLabel(logoLbl);
            blackLbl->setStyleSheet("QLabel { background-color : black; }");
            blackLbl->resize(logoPlayer->size());
            blackLbl->raise();
            blackLbl->show();
            QTimer::singleShot(500,logoPlayer,SLOT(loadPredefinedFile()));
            logoLbl->show();//needed to load the file
            connect(logoLbl,SIGNAL(showAnimationOver()),logoPlayer,SLOT(playAndRaise()));
            connect(logoLbl,SIGNAL(hideAnimationOver()),logoPlayer,SLOT(stopAndHide()));

        }
        else
        {
            QPixmap logoPix(PATH+"logo/"+QString::number(i)+".png");
            logoPix = logoPix.scaledToWidth(logoWidth,Qt::SmoothTransformation);
            logoLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect(logoX,logoY,logoPix.width(),logoPix.height()),false);
            logoLbl->hide();
            logoLbl->setPixmap(logoPix);
            logoLbl->setScaledContents(true);

        }


        QPixmap trophyPix(PATH+"trophy/"+QString::number(i)+".png");
        powerLabel *trophyLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect(trophyX,trophyY,trophyPix.width()/3,trophyPix.height()/3),false);
        trophyLbl->hide();
        trophyLbl->setPixmap(trophyPix);
        trophyLbl->setScaledContents(true);

        yearLbls.push_back(yearLbl);
        titleLbls.push_back(titleLbl);
        logoLbls.push_back(logoLbl);
        trophyLbls.push_back(trophyLbl);
    }


showAwardsList();

}


void touchScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void touchScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}





void touchScreen::buttonClick(void)
{
    powerLabel *b = (powerLabel*)QObject::sender();
    selectAward(b->getId());


}


void touchScreen::selectAward(int awardId)
{
    emit onAwardSelected();


    timeOutTimer->start(TIMEOUT_DELAY);

    for(auto b:awardButtons)
        b->animateHide();


    titleLbls[awardId]->animateShow();
    yearLbls[awardId]->animateShow();
    logoLbls[awardId]->animateShow();
    trophyLbls[awardId]->animateShow();
    backLbl->animateShow();

    activeContent = awardId;
}


void touchScreen::showAwardsList()
{
    emit onAwardsShowList();

    for(auto b:awardButtons)
    {
            if(b->getId() == 13)
                continue;
        b->animateShow();
    }

    for(auto t: titleLbls)
        if(t->isVisible())t->animateHide();
    for(auto t: yearLbls)
        if(t->isVisible())t->animateHide();
    for(auto t: trophyLbls)
        if(t->isVisible())t->animateHide();
    for(auto t: logoLbls)
        if(t->isVisible())t->animateHide();



    backLbl->animateHide();

    timeOutTimer->stop();
}


void touchScreen::loadPlayer()
{

    bgVp->loadFilePaused(PATH+"touchBg3.mp4");
    bgVp->play();

    introVp->loadFilePaused(PATH+"touchIntro3.mp4");
}


QRect touchScreen::led2screen(QRect original)
{
    int nuW = original.width()/Touch2LedRatio;
    int nuH = original.height()/Touch2LedRatio;

    double x2 = (double)(original.x() + original.width()/2   - ledWidth/2)/(Touch2LedRatio)  + width()/2 - nuW/2;
    double y2 = (double)(original.y() + original.height()/2 - ledHeight/2)/(Touch2LedRatio) + height()/2 - nuH*0.75;


    return QRect(x2,y2,nuW,nuH);
}



