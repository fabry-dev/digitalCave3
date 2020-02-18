#include "powerLabel.h"

powerLabel::powerLabel(QLabel *parent, int id, QRect hideGeo, QRect showGeo,bool zoomOnClick,bool floatingMovement) : QLabel(parent),id(id),hideGeo(hideGeo),showGeo(showGeo),zoomOnClick(zoomOnClick),floatingMovement(floatingMovement)
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    hide();
    setGeometry(hideGeo);
    showAnim = new QPropertyAnimation(this,"geometry");
    showAnim->setDuration(400);
    showAnim->setEasingCurve(QEasingCurve::InCurve);
    showAnim->setStartValue(hideGeo);
    showAnim->setEndValue(showGeo);

    connect(showAnim,SIGNAL(finished()),this,SIGNAL(showAnimationOver()));

    hideAnim = new QPropertyAnimation(this,"geometry");
    hideAnim->setDuration(400);
    hideAnim->setEasingCurve(QEasingCurve::InCurve);
    hideAnim->setStartValue(showGeo);
    hideAnim->setEndValue(hideGeo);
    connect(hideAnim,SIGNAL(finished()),this,SLOT(hide()));
    connect(hideAnim,SIGNAL(finished()),this,SIGNAL(hideAnimationOver()));

    floatingGone = false;
    floatingFlagStop = false;
    floatingAnim = new QPropertyAnimation(this,"pos");
    zoomOut = new QPropertyAnimation(this,"geometry");
    zoomIn = new QPropertyAnimation(this,"geometry");

    if(floatingMovement)
        connect(showAnim,SIGNAL(finished()),this,SLOT(generateFloatingAnim()));

}

int powerLabel::getId() const
{
    return id;
}


void powerLabel::mousePressEvent(QMouseEvent *ev)
{
    if(zoomOnClick)
    {

        zoomIn->setDuration(100);
        zoomIn->setEasingCurve(QEasingCurve::InCurve);
        zoomIn->setStartValue(this->geometry());
        int centerX = x()+width()/2;
        int centerY = y()+height()/2;
        int nuWidth = (double)width()*1.1;
        int nuHeight = (double)height()*1.1;
        zoomIn->setEndValue(QRect(centerX-nuWidth/2,centerY-nuHeight/2,nuWidth,nuHeight));



        zoomOut->setDuration(100);
        zoomOut->setEasingCurve(QEasingCurve::InCurve);
        zoomOut->setEndValue(showGeo);
        zoomOut->setStartValue(QRect(centerX-nuWidth/2,centerY-nuHeight/2,nuWidth,nuHeight));

        connect(zoomIn,SIGNAL(finished()),zoomOut,SLOT(start()));
        connect(zoomOut,SIGNAL(finished()),this,SIGNAL(clicked()));






       // connect(zoomIn,SIGNAL(finished()),this,SLOT(hide()));
        zoomIn->start(QAbstractAnimation::KeepWhenStopped);

    }
    else
        emit clicked();
}

void powerLabel::stopFloating()
{
    floatingMovement = false;
}


void powerLabel::generateFloatingAnim(void)
{

    if((!floatingMovement )&&(!floatingGone))
        return;

    if((floatingFlagStop ))
    {
        floatingFlagStop = false;
        return;
    }




    floatingAnim->setDuration(500+qrand()%500);
    floatingAnim->setEasingCurve(QEasingCurve::InCurve);
    floatingAnim->setStartValue(pos());

    int randAxis = qrand()%2;
    int randSign = (qrand()%2)*2-1;
    int randMag = 5+qrand()%5;

    if(!floatingGone)
    {


        if(randAxis == 0)
            floatingAnim->setEndValue(QPoint(x()+randSign*randMag,y()));
        else
            floatingAnim->setEndValue(QPoint(x(),y()+randSign*randMag));
    }
    else
        floatingAnim->setEndValue(QPoint(showGeo.x(),showGeo.y()));

    floatingGone = !floatingGone;


    connect(floatingAnim,SIGNAL(finished()),this,SLOT(generateFloatingAnim()));
    floatingAnim->start(QAbstractAnimation::KeepWhenStopped);

}

void powerLabel::animateHide(void)
{
    floatingFlagStop = true;
    floatingAnim->stop();
    hideAnim->start();
}

void powerLabel::animateShow(void)
{
    show();
    showAnim->start();
}
