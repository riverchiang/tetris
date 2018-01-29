#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>
#include <QLabel>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>

class blockGroup;

class GameScreen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameScreen(QWidget *parent = 0);
    bool iscolliding();
public slots:
    void clearFullRows();
    void moveBlock();

private:
    QGraphicsLineItem *topLine;
    QGraphicsLineItem *bottomLine;
    QGraphicsLineItem *leftLine;
    QGraphicsLineItem *rightLine;
    blockGroup *boxGroup;
    blockGroup *nextBoxGroup;
    QGraphicsScene *scene;

    void initView();
    void setGamePanel();
    void setScoreLCD();
    QList<int> rows;
    int score = 0;

    QLCDNumber *myLCDNumber;
    QPushButton *buttonDown;
    QPushButton *buttonLeft;
    QPushButton *buttonRight;
    QPushButton *buttonRotate;
    QGridLayout *panelGirdLayout;
    QWidget *panelWidget;
    QLabel *scoreLabel;
};

#endif // GAMESCREEN_H
