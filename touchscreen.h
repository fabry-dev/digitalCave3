#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"
#include "alphaVideoPlayer.h"
#include "QPropertyAnimation"
#include "powerLabel.h"
class touchScreen : public QLabel
{
    Q_OBJECT
public:
    explicit touchScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp,*introVp;
    std::vector<powerLabel*>awardButtons;
    QRect led2screen(QRect original);
    std::vector<powerLabel *>yearLbls,trophyLbls,logoLbls,titleLbls;
    powerLabel *backLbl;
    int activeContent;
    mpvWidget *logoPlayer;
private slots:
    void loadPlayer(void);
    void buttonClick(void);
    void selectAward(int awardId);
    void showAwardsList(void);
    void startIntroVideo(void);
    void stopIntroVideo(void);
signals:
    void bgShouldRestart(void);
    void onAwardSelected(void);
    void onAwardsShowList(void);

};

#endif // MAINSCREEN_H
