#include "yearbuttons.h"

//int yearWidths[]={111,111,111,131,151,191,151,131,111,111,111};
//int yearXs[]={-111,-111,-111,20,191,382,613,804,960,960,960};

#define SWIPE_RANGE 200

yearButtons::yearButtons(QWidget *parent,QString PATH,std::vector<int>yearWidths,std::vector<int>yearXs,int yearY,QString imageNameSuffix) : QWidget(parent),PATH(PATH),yearWidths(yearWidths),yearXs(yearXs),yearY(yearY)
{

    resize(parent->size());
    QPixmap bg;
    horizontalPos = 0;//central position
    for(int i = 0;i<6;i++)
    {
        QLabel *year = new QLabel(this);
        //year->setStyleSheet("border: 1px solid red");
        bg.load(PATH+QString::number(i)+imageNameSuffix+".png");



        ratio = (double)bg.width()/bg.height();
        year->setScaledContents(true);

        year->setPixmap(bg);
        year->resize(yearWidths[3+i+horizontalPos],yearWidths[3+i+horizontalPos]/ratio);
        year->move(yearXs[3+i+horizontalPos],yearY-year->height()/2);
        year->show();
        years.push_back(year);

        QPropertyAnimation *anim = new QPropertyAnimation(year, "geometry");
        anim->setDuration(300);
        anim->setEasingCurve(QEasingCurve::InCurve);
        anims.push_back(anim);

    }

    connect(anims[0],SIGNAL(finished()),this,SLOT(animationOver()));
    lastPosition = 0;

}


void yearButtons::moveLeft()
{
    if(horizontalPos<=-3)
        return;

    emit movingLeft();
    horizontalPos--;

    animate();

}


void yearButtons::moveRight()
{
    if(horizontalPos>=2)
        return;

    emit movingRight();
    horizontalPos++;

    animate();

}


void yearButtons::animate()
{

    for(int i = 0;i<6;i++)
    {

        anims[i]->setStartValue(years[i]->geometry());
        QRect geo=QRect(yearXs[3+i+horizontalPos],yearY-(yearWidths[3+i+horizontalPos]/ratio)/2,yearWidths[3+i+horizontalPos],yearWidths[3+i+horizontalPos]/ratio);
        anims[i]->setEndValue(geo);
        anims[i]->start(QAbstractAnimation::KeepWhenStopped);

    }


}

void yearButtons::animationOver()
{

    emit yearSelected(2-horizontalPos);

}


//Detect click hold and release (when using a mouse)

//Mark the picture as clicked
void yearButtons::mousePressEvent(QMouseEvent *eventPress)
{
    clickPos = eventPress->pos();//store the click position
    clicked = true;
}


//unmark the picture as clicked
void yearButtons::mouseReleaseEvent(QMouseEvent *eventRelease)
{
    clicked = false;
    lastPosition = position;


}


//check if muse mouvement qualifies as a swaf
void yearButtons::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(!clicked) //not clicked. Not interested
        return;

    QPoint activePos = eventMove->pos();//store the actual position

    QPointF center = QPointF(width()/2.0,height()/2.0);

    QPointF d = activePos-clickPos;

    if(d.x()>SWIPE_RANGE)
    {
        moveRight();
        clicked = false;

    }
    else if(d.x()<-SWIPE_RANGE)
    {

        moveLeft();
        clicked = false;

    }




}
