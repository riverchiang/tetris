#include "gamescreen.h"
#include "gameblock.h"
#include <QKeyEvent>
#include <QList>
#include <QTimer>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent)
{
    init_view();
}

void GameScreen::setGamePanel()
{
    panelGirdLayout = new QGridLayout();
    buttonDown = new QPushButton();
    buttonLeft = new QPushButton();
    buttonRight = new QPushButton();
    buttonRotate = new QPushButton();

    buttonDown->setIcon(QIcon(":/images/down.jpg"));
    buttonDown->setIconSize(QSize(60,20));

    buttonLeft->setIcon(QIcon(":/images/left.jpg"));
    buttonLeft->setIconSize(QSize(20,60));

    buttonRight->setIcon(QIcon(":/images/right.jpg"));
    buttonRight->setIconSize(QSize(20,60));

    buttonRotate->setIcon(QIcon(":/images/rotate.jpg"));
    buttonRotate->setIconSize(QSize(60,60));

    panelGirdLayout->addWidget(buttonLeft, 0, 0);
    panelGirdLayout->addWidget(buttonRotate, 0, 1);
    panelGirdLayout->addWidget(buttonRight, 0, 2);
    panelGirdLayout->addWidget(buttonDown, 1, 1);
    panelWidget = new QWidget();
    panelWidget->setLayout(panelGirdLayout);
    panelWidget->move(120, 470);
    scene->addWidget(panelWidget);

    connect(buttonDown, SIGNAL(clicked()), box_group, SLOT(buttonDown()));
    connect(buttonLeft, SIGNAL(clicked()), box_group, SLOT(buttonLeft()));
    connect(buttonRight, SIGNAL(clicked()), box_group, SLOT(buttonRight()));
    connect(buttonRotate, SIGNAL(clicked()), box_group, SLOT(buttonRotate()));
}

void GameScreen::setScoreLCD()
{
    myLCDNumber = new QLCDNumber;
    myLCDNumber->setDigitCount(8);
    myLCDNumber->setSegmentStyle(QLCDNumber::Flat);
    myLCDNumber->display(score);
    myLCDNumber->move(100, 0);
    scene->addWidget(myLCDNumber);
}

void GameScreen::init_view()
{
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(CacheBackground);
    setWindowTitle(tr("Teris"));
    setMinimumSize(510, 610);
    setMaximumSize(510, 610);
    scene = new QGraphicsScene;
    scene->setSceneRect(5, 5, 500, 600);
    setScene(scene);

    top_line = scene->addLine(97, 47, 303, 47);
    bottom_line = scene->addLine(97, 453, 303, 453);
    left_line = scene->addLine(97, 47, 97, 453);
    right_line = scene->addLine(303, 47, 303, 453);

    QGraphicsRectItem *item = new QGraphicsRectItem(320,100,100,80);
    scene->addItem(item);

    scoreLabel = new QLabel("next block");
    scoreLabel->move(330, 70);
    scene->addWidget(scoreLabel);

    next_box_group = new blockGroup;
    scene->addItem(next_box_group);
    next_box_group->createBlock(QPointF(360,140));

    box_group = new blockGroup;
    scene->addItem(box_group);

    box_group->createBlock(QPointF(200, 70));
    box_group->setFocus();
    box_group->startTimer(1000);

    connect(box_group, SIGNAL(needNewBlock()), this, SLOT(clear_full_rows()));

    setScoreLCD();
    setGamePanel();
}

void GameScreen::clear_full_rows()
{
    box_group->clearBlockGroup(false);

    for (int y = 429; y > 50; y-=20) {
        QList<QGraphicsItem *> list = scene->items(99, y, 202, 22, Qt::ContainsItemShape, Qt::AscendingOrder);
        if (list.count() == 10) {
            foreach (QGraphicsItem *item2, list) {
                block *box = (block *) item2;
                QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
                box->setGraphicsEffect(opacity);
                QPropertyAnimation *anim = new QPropertyAnimation( opacity, "opacity" );
                anim->setDuration( 200 );
                anim->setStartValue( 0.8 );
                anim->setEndValue( 0.1 );
                anim->setEasingCurve( QEasingCurve::InCubic );
                anim->start(QAbstractAnimation::DeleteWhenStopped);
                connect(anim, SIGNAL(finished()), box, SLOT(deleteLater()));
            }
            rows << y;
        }
    }

    score += rows.count();
    myLCDNumber->display(score);
    QTimer::singleShot(400, this, SLOT(move_box()));
}

void GameScreen::move_box()
{
    for(int i = rows.count(); i > 0; --i) {
        int row = rows.at(i-1);
        foreach(QGraphicsItem *item1, scene->items(99, 49, 202, row-47, Qt::ContainsItemShape,  Qt::AscendingOrder)) {
            item1->moveBy(0, 20);
        }
    }
    rows.clear();
    box_group->createBlock(QPointF(200, 70), next_box_group->getCurrentShape());
    next_box_group->clearBlockGroup(true);
    next_box_group->createBlock(QPointF(360,140));
}

bool GameScreen::iscolliding()
{
    QList<QGraphicsItem *> item_list = box_group->childItems();
    QGraphicsItem *item1;

    foreach (item1, item_list) {
        if (item1->collidingItems().count() > 1) {
            return true;
        }
    }
    return false;
}

