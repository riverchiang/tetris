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
    void clear_box_group(bool destory_box = false);
public slots:
    void clear_full_rows();
    void move_box();

private:
    QGraphicsLineItem *top_line;
    QGraphicsLineItem *bottom_line;
    QGraphicsLineItem *left_line;
    QGraphicsLineItem *right_line;
    blockGroup *box_group;
    blockGroup *next_box_group;
    QTransform transform1;
    QGraphicsScene *scene;
    QGraphicsWidget *mask_widget;
    QTimer *mytimer;

    void init_view();
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
