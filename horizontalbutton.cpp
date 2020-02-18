#include "horizontalbutton.h"
#include "math.h"
#include "qpainter.h"
#include "qmath.h"


horizontalButton::horizontalButton(QLabel *parent): QLabel(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents, true);
    setStyleSheet("border: 1px solid red");
    lastPosition = 0;
}


void horizontalButton::setImage(QString imageSrc, int w, int h)
{

    background.load(imageSrc);

    background = background.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);



    setPosition(0);
}


void horizontalButton::setPosition(int nuPosition)
{
    if(nuPosition<-background.width())
        nuPosition = -background.width();
    else if(nuPosition>background.width())
        nuPosition = background.width();


    position = nuPosition;

    QPixmap newPixmap(size());
    newPixmap.fill(QColor::fromRgb(0, 0, 0, 0));

    QPainter p(&newPixmap);

    p.setRenderHint(QPainter::SmoothPixmapTransform,true);
    double x = nuPosition;
    double y = (height()-background.height())/2;
    p.translate(x, y);
    p.drawPixmap(0, 0, QPixmap::fromImage(background));
    p.end();


    setPixmap(newPixmap);

}



//Detect click hold and release (when using a mouse)

//Mark the picture as clicked
void horizontalButton::mousePressEvent(QMouseEvent *eventPress)
{
    clickPos = eventPress->pos();//store the click position
    clicked = true;
}


//unmark the picture as clicked
void horizontalButton::mouseReleaseEvent(QMouseEvent *eventRelease)
{
    clicked = false;
    lastPosition = position;


}


//check if muse mouvement qualifies as a swaf
void horizontalButton::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(!clicked) //not clicked. Not interested
        return;

    QPoint activePos = eventMove->pos();//store the actual position

    QPointF center = QPointF(width()/2.0,height()/2.0);

    QPointF d = activePos-clickPos;

    double x = lastPosition+d.x();


    setPosition(x);

}


