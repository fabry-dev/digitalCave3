#ifndef YEARBUTTONS_H
#define YEARBUTTONS_H

#include <QWidget>
#include "qlabel.h"
#include "qdebug.h"
#include "QPropertyAnimation"
#include "QTimer"
#include "QTouchEvent"

class yearButtons : public QWidget
{
    Q_OBJECT
public:
    explicit yearButtons(QWidget *parent = nullptr, QString PATH="", std::vector<int> yearWidths={}, std::vector<int> yearXs={}, int yearY=0,QString imageNameSuffix="");

signals:
    void movingLeft(void);
    void movingRight(void);
    void yearSelected(int);
public slots:
    void moveLeft(void);
    void moveRight(void);
    void animate(void);
    void animationOver(void);

private:
    QString PATH;
    std::vector<QLabel *>years;

    int horizontalPos;
    double ratio;
    std::vector<int>yearWidths;
    std::vector<int>yearXs;
    int yearY;
    double lastPosition,position;
    bool clicked;
    QPointF clickPos;
    std::vector<QPropertyAnimation *> anims;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // YEARBUTTONS_H
