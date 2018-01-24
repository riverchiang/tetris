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
    enum BoxShape {IShape, JShape, LShape, OShape, SShape, TShape, ZShape, RandomShape};
    blockGroup();
    QRectF boundingRect() const;
    void clear_box_group(bool destroy_box = false);
    void create_box(const QPointF &point, BoxShape shape = RandomShape);
    bool isColliding();
    BoxShape getCurrentShape() {return current_shape;}
    BoxShape current_shape;
public slots:
    void startTimer(int interval);
    void stop_timer();
    void move_one_step();
    void buttonDown();
    void buttonLeft();
    void buttonRight();
    void buttonRotate();
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void need_new_box();
private:
    QTransform old_transform;
    QTransform transform1;
    QTimer *timer;
};

#endif // GAMEBLOCK_H
