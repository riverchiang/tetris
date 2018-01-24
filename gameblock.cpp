#include "gameblock.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#include "shapetype.h"

block::block(const QColor &color) : brushColor(color) {

}

QRectF block::boundingRect() const {
    qreal pen_width = 1;
    return QRectF(-10-pen_width/2, -10-pen_width/2, 20+pen_width, 20+pen_width);
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
    old_transform = transform();
    current_shape = RandomShape;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_one_step()));
}

void blockGroup::move_one_step()
{
    moveBy(0, 20);
    if (isColliding()) {
        moveBy(0, -20);
        emit need_new_box();
    }
}

void blockGroup::startTimer(int interval)
{
    timer->start(interval);
}

void blockGroup::stop_timer()
{
    timer->stop();
}

QRectF blockGroup::boundingRect() const {
    qreal pen_width = 1;
    return QRectF(-40-pen_width/2, -40-pen_width/2, 80+pen_width, 80+pen_width);
}

void blockGroup::create_box(const QPointF &point, BoxShape shape) {

    static const QColor color_table[7] = {
        QColor(200, 0, 0, 100), QColor(255, 200, 0, 100), QColor(0, 0, 200, 100),
        QColor(0, 200, 0, 100), QColor(0, 200, 255, 100), QColor(200, 0, 255, 100),
        QColor(150, 100, 100, 100)
    };
    int shape_id = shape; //Box_Shape是枚举型，其实也是整型，因为它相当于整型的宏定义
    if(shape == RandomShape) {
        shape_id = qrand()%7;//随机取一个颜色
    }
    QColor color = color_table[shape_id];//根据id选颜色
    QList<block *> list;
    setTransform(old_transform);//恢复方块组前的变换矩阵
    for(int i = 0; i < 4; ++i) { //4个小方块组成一个方块组
        block *temp  = new block(color);
        list << temp;//将小方块加入list列表
        addToGroup(temp);
    }

    Shape *myShape = new Shape(shape_id);
    myShape->setPosition(list);
    setPos(point);//将准备好的俄罗斯方块放入指定的位置，然后进行碰撞检测

}

bool blockGroup::isColliding()
{
    QList<QGraphicsItem *> item_list = childItems();
    QGraphicsItem *item;
    foreach (item, item_list) {
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
        emit need_new_box();
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
    transform1.rotate(90);
    setTransform(transform1);
    if (isColliding()) {
         transform1.rotate(-90);
         setTransform(transform1);
    }
}

void blockGroup::keyPressEvent(QKeyEvent *event) {
    switch (event->key())
    {
        case Qt::Key_Down:
            moveBy(0, 20);
            if (isColliding()) {
                moveBy(0, -20);
                //clear_box_group();
                emit need_new_box();
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
            transform1.rotate(90);
            setTransform(transform1);
            if (isColliding()) {
                transform1.rotate(-90);
                setTransform(transform1);
            }
            break;
    }
}

void blockGroup::clear_box_group(bool destroy_box)
{
    QList<QGraphicsItem *> item_list = childItems();
    QGraphicsItem *item1;
    foreach (item1, item_list) {
        removeFromGroup(item1);
        if (destroy_box) {
            block *box = (block*)item1;
            box->deleteLater();
        }
    }
}
