#ifndef HORIZONTALBUTTON_H
#define HORIZONTALBUTTON_H



#include "qlabel.h"
#include "qobject.h"
#include "QGestureEvent"
#include "qdebug.h"

class horizontalButton : public QLabel
{
      Q_OBJECT
public:
    explicit horizontalButton(QLabel *parent = nullptr);
    void setImage(QString imageSrc, int w, int h);
    void setPosition(int percent);
private:
    bool gestureEvent(QGestureEvent *event);
    double lastPosition,position;
    bool clicked;
    QPointF clickPos;
    QImage background;
protected:
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *eventRelease);
    void mouseMoveEvent(QMouseEvent *eventMove);

};
#endif // HORIZONTALBUTTON_H
