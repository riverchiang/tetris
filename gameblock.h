#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H

#include <QGraphicsObject>
#include <QGraphicsItemGroup>

class block : public QGraphicsObject
{
public:
    block(const QColor &color = Qt::red);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
private:
    QColor brushColor;
};

class blockGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    enum BlockShape {IShape, JShape, LShape, OShape, SShape, TShape, ZShape, RandomShape};
    blockGroup();
    QRectF boundingRect() const;
    void clearBlockGroup(bool destroyBlock = false);
    void createBlock(const QPointF &point, BlockShape shape = RandomShape);
    bool isColliding();
    BlockShape getCurrentShape() {return currentShape;}
    BlockShape currentShape;
public slots:
    void startTimer(int interval);
    void stopTimer();
    void moveOneStep();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonRotate();
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void needNewBlock();
private:
    QTransform oldTransform;
    QTransform newTransform;
    QTimer *timer;
};

#endif // GAMEBLOCK_H
