#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"

#define vpCount 7

class mainScreen : public QLabel
{
    Q_OBJECT
public:
    explicit mainScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *vp;

private slots:
    void startVideo(void);
    void moveVideo(void);

};

#endif // MAINSCREEN_H
