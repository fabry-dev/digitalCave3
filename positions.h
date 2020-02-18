#ifndef POSITIONS_H
#define POSITIONS_H



static int buttonsLedX[16] = {0,140,0,150,0,140,0,150,750,600,760,580,740,600,750,570};
static int buttonsLedY[16] = {-30,150,280,430,550,690,810,940,-30,120,280,430,550,690,830,940};
static int buttonsTouchX[16] = {910,145,425,725,200,170,930,895,535,550,935,420,900,185,640,210};
static int buttonsTouchY[16] = {420,145,350,145,620,1010,730,1060,1230,920,1365,1670,1720,1785,1510,1400};

static double Touch2LedRatio = (double)53.1/250; //size led = size touch * Touch2Led
static double ledAwardsRatio = 0.6;

static double ledWidth = 960;
static double ledHeight = 1152;

#endif // POSITIONS_H
