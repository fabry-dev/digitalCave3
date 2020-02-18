#ifndef ROTATIVEBUTTON_H
#define ROTATIVEBUTTON_H



#include "qlabel.h"
#include "qobject.h"
#include "QGestureEvent"
#include "qdebug.h"

class rotativeButton : public QLabel
{
      Q_OBJECT
public:
    explicit rotativeButton(QLabel *parent = nullptr);
    void setImage(QString imageSrc, int w, int h);

private:
    bool gestureEvent(QGestureEvent *event);
    void setAngle(int angle);
    bool clicked;
     QPointF clickPos;
    QImage background;
    double savedAngle,lastAngle;
protected:
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *eventRelease);
    void mouseMoveEvent(QMouseEvent *eventMove);

};

#endif // ROTATIVEBUTTON_H
