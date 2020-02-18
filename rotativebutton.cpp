#include "rotativebutton.h"
#include "math.h"
#include "qpainter.h"
#include "qmath.h"
rotativeButton::rotativeButton(QLabel *parent): QLabel(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents, true);
    setStyleSheet("border: 1px solid red");
    savedAngle=0;
    lastAngle=0;
    clicked = false;

}



void rotativeButton::setImage(QString imageSrc,int w,int h)
{

    background.load(imageSrc);



    background = background.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);


   setAngle(0);

}


void rotativeButton::setAngle(int angle)
{

    angle = angle%360;

    //Move windows's coordinate system to center.

    QPixmap newPixmap(size());
    newPixmap.fill(QColor::fromRgb(0, 0, 0, 0));

    QPainter p(&newPixmap);

    p.setRenderHint(QPainter::SmoothPixmapTransform,true);
    p.translate(width() / 2, height() / 2);
    p.rotate(angle);
    p.translate(-width() / 2, -height() / 2);
    p.translate((width()-background.width())/2,(height()-background.height())/2);
    p.drawPixmap(0, 0, QPixmap::fromImage(background));
    p.end();


    setPixmap(newPixmap);

}


bool rotativeButton::gestureEvent(QGestureEvent *event)
{

    qDebug()<<event;

    return true;

}


bool rotativeButton::event(QEvent *event)
{
   if (event->type() == QEvent::Gesture)
            return gestureEvent(static_cast<QGestureEvent*>(event));

  return QWidget::event(event);
}




//Detect click hold and release (when using a mouse)

//Mark the picture as clicked
void rotativeButton::mousePressEvent(QMouseEvent *eventPress)
{
    clickPos = eventPress->pos();//store the click position
    clicked = true;
}


//unmark the picture as clicked
void rotativeButton::mouseReleaseEvent(QMouseEvent *eventRelease)
{
    clicked = false;
    savedAngle += lastAngle;

}


//check if muse mouvement qualifies as a swaf
void rotativeButton::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(!clicked) //not clicked. Not interested
        return;

    QPoint reactivePos = eventMove->pos();//store the actual position

    QPointF center = QPointF(width()/2.0,height()/2.0);

    QPointF v1 = clickPos-center;
    QPointF v2 = reactivePos-center;

    lastAngle = 180*qAtan2(v1.x()*v2.y()-v1.y()*v2.x(),v1.x()*v2.x()+v1.y()*v2.y())/M_PI;

    setAngle(savedAngle+lastAngle);

}



