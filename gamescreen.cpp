#include "gamescreen.h"
#include "gameblock.h"
#include <QKeyEvent>
#include <QList>
#include <QTimer>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent)
{
    initView();
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

    connect(buttonDown, SIGNAL(clicked()), boxGroup, SLOT(buttonDown()));
    connect(buttonLeft, SIGNAL(clicked()), boxGroup, SLOT(buttonLeft()));
    connect(buttonRight, SIGNAL(clicked()), boxGroup, SLOT(buttonRight()));
    connect(buttonRotate, SIGNAL(clicked()), boxGroup, SLOT(buttonRotate()));
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

void GameScreen::initView()
{
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(CacheBackground);
    setWindowTitle(tr("Teris"));
    setMinimumSize(510, 610);
    setMaximumSize(510, 610);
    scene = new QGraphicsScene;
    scene->setSceneRect(5, 5, 500, 600);
    setScene(scene);

    topLine = scene->addLine(97, 47, 303, 47);
    bottomLine = scene->addLine(97, 453, 303, 453);
    leftLine = scene->addLine(97, 47, 97, 453);
    rightLine = scene->addLine(303, 47, 303, 453);

    QGraphicsRectItem *item = new QGraphicsRectItem(320,100,100,80);
    scene->addItem(item);



    scoreLabel = new QLabel("Next block");
    scoreLabel->move(330, 70);
    font = scoreLabel->font();
    font.setPointSize(15);
    font.setBold(true);
    scoreLabel->setFont(font);
    scene->addWidget(scoreLabel);

    nextBoxGroup = new blockGroup;
    scene->addItem(nextBoxGroup);
    nextBoxGroup->createBlock(QPointF(360,140));

    boxGroup = new blockGroup;
    scene->addItem(boxGroup);

    boxGroup->createBlock(QPointF(200, 70));
    boxGroup->setFocus();
    boxGroup->startTimer(1000);

    connect(boxGroup, SIGNAL(needNewBlock()), this, SLOT(clearFullRows()));

    setScoreLCD();
    setGamePanel();
}

void GameScreen::clearFullRows()
{
    boxGroup->clearBlockGroup(false);

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
    QTimer::singleShot(400, this, SLOT(moveBlock()));
}

bool GameScreen::checkGameFinish()
{
    QList<QGraphicsItem *> list = scene->items(99, 49, 202, 22, Qt::ContainsItemShape, Qt::AscendingOrder);
    if (list.count() > 0)
        return true;
    return false;
}

void GameScreen::finishGame()
{
    QWidget *mask = new QWidget;
    QLabel *finishLabel = new QLabel(mask);
    QHBoxLayout *layout = new QHBoxLayout();
    font = finishLabel->font();

    font.setPointSize(27);
    font.setBold(true);
    finishLabel->setFont(font);

    finishLabel->setText("Game Over");
    layout->addWidget(finishLabel);

    mask->setPalette(QPalette(QColor(0, 0, 0, 150)));
    mask->resize(200, 400);
    mask->setLayout(layout);

    gameFinishWidget = scene->addWidget(mask);
    gameFinishWidget->setPos(100, 50);
    gameFinishWidget->setZValue(1);
}

void GameScreen::moveBlock()
{
    for(int i = rows.count(); i > 0; --i) {
        int row = rows.at(i-1);
        foreach(QGraphicsItem *item1, scene->items(99, 49, 202, row-47, Qt::ContainsItemShape,  Qt::AscendingOrder)) {
            item1->moveBy(0, 20);
        }
    }
    rows.clear();

    if (checkGameFinish())
    {
        finishGame();
    }
    else {
        boxGroup->createBlock(QPointF(200, 70), nextBoxGroup->getCurrentShape());
        nextBoxGroup->clearBlockGroup(true);
        nextBoxGroup->createBlock(QPointF(360,140));
    }
}

bool GameScreen::iscolliding()
{
    QList<QGraphicsItem *> items = boxGroup->childItems();
    QGraphicsItem *item1;

    foreach (item1, items) {
        if (item1->collidingItems().count() > 1) {
            return true;
        }
    }
    return false;
}

