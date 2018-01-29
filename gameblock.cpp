#include "gameblock.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#include "shapetype.h"

block::block(const QColor &color) : brushColor(color) {

}

QRectF block::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(-10 - penWidth/2, -10 - penWidth/2, 20 + penWidth, 20 + penWidth);
}

void block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(-10, -10, 20, 20, QPixmap(":/images/Brick_Block.png"));
    painter->setBrush(brushColor);
    QColor penColor = brushColor;
    penColor.setAlpha(20);
    painter->setPen(penColor);
    painter->drawRect(-10, -10, 20, 20);
}

QPainterPath block::shape() const{
    QPainterPath path;
    path.addRect(-9.5, -9.5, 19, 19);
    return path;
}

blockGroup::blockGroup() {
    setFlags(QGraphicsItem::ItemIsFocusable);
    oldTransform = transform();
    currentShape = RandomShape;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveOneStep()));
}

void blockGroup::moveOneStep()
{
    moveBy(0, 20);
    if (isColliding()) {
        moveBy(0, -20);
        emit needNewBlock();
    }
}

void blockGroup::startTimer(int interval)
{
    timer->start(interval);
}

void blockGroup::stopTimer()
{
    timer->stop();
}

QRectF blockGroup::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(-40 - penWidth/2, -40 - penWidth/2, 80 + penWidth, 80 + penWidth);
}

void blockGroup::createBlock(const QPointF &point, BlockShape shape) {

    static const QColor colorTable[7] = {
        QColor(200, 0, 0, 100), QColor(255, 200, 0, 100), QColor(0, 0, 200, 100),
        QColor(0, 200, 0, 100), QColor(0, 200, 255, 100), QColor(200, 0, 255, 100),
        QColor(150, 100, 100, 100)
    };
    int shapeId = shape;
    if(shape == RandomShape) {
        shapeId = qrand()%7;
    }
    currentShape = (BlockShape)shapeId;
    QColor color = colorTable[shapeId];
    QList<block *> list;
    setTransform(oldTransform);
    for(int i = 0; i < 4; ++i) {
        block *temp  = new block(color);
        list << temp;
        addToGroup(temp);
    }

    Shape *myShape = new Shape(shapeId);
    myShape->setPosition(list);
    setPos(point);

}

bool blockGroup::isColliding()
{
    QList<QGraphicsItem *> items = childItems();
    QGraphicsItem *item;
    foreach (item, items) {
        if (item->collidingItems().count() > 1)
            return true;
    }
    return false;
}

void blockGroup::buttonDown()
{
    moveBy(0, 20);
    if (isColliding()) {
        moveBy(0, -20);
        emit needNewBlock();
    }
}

void blockGroup::buttonLeft()
{
    moveBy(-20, 0);
    if (isColliding()) {
        moveBy(20, 0);
    }
}

void blockGroup::buttonRight()
{
    moveBy(20, 0);
    if (isColliding()) {
        moveBy(-20, 0);
    }
}

void blockGroup::buttonRotate()
{
    newTransform.rotate(90);
    setTransform(newTransform);
    if (isColliding()) {
         newTransform.rotate(-90);
         setTransform(newTransform);
    }
}

void blockGroup::keyPressEvent(QKeyEvent *event) {
    switch (event->key())
    {
        case Qt::Key_Down:
            moveBy(0, 20);
            if (isColliding()) {
                moveBy(0, -20);
                emit needNewBlock();
            }
            break;
        case Qt::Key_Left:
            moveBy(-20, 0);
            if (isColliding()) {
                moveBy(20, 0);
            }
            break;
        case Qt::Key_Right:
            moveBy(20, 0);
            if (isColliding()) {
                moveBy(-20, 0);
            }
            break;
        case Qt::Key_Space:
            newTransform.rotate(90);
            setTransform(newTransform);
            if (isColliding()) {
                newTransform.rotate(-90);
                setTransform(newTransform);
            }
            break;
    }
}

void blockGroup::clearBlockGroup(bool destroyBlock)
{
    QList<QGraphicsItem *> items = childItems();
    QGraphicsItem *item1;
    foreach (item1, items) {
        removeFromGroup(item1);
        if (destroyBlock) {
            block *removeBlock = (block*)item1;
            removeBlock->deleteLater();
        }
    }
}
