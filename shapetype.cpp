#include "shapetype.h"
#include "gameblock.h"

Shape::Shape(int type) {
    setShape(type);
}

int Shape::getShape() {
    return _type->getTypeCode();
}

void Shape::setShape(int arg) {
    _type = ShapeType::newType(arg);
}

void Shape::setPosition(QList<block*> list) {
    _type->setPosition(list);
}

ShapeType* ShapeType::newType(int code) {
    switch (code) {
    case IShape:
        return new IShapeType();
    case JShape:
        return new JShapeType();
    case LShape:
        return new LShapeType();
    case OShape:
        return new OShapeType();
    case SShape:
        return new SShapeType();
    case TShape:
        return new TShapeType();
    case ZShape:
        return new ZShapeType();
    default:
        return NULL;
    }
}

void IShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(-30, -10);
    list.at(1)->setPos(-10, -10);
    list.at(2)->setPos(10, -10);
    list.at(3)->setPos(30, -10);
}

void JShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(10, -10);
    list.at(1)->setPos(10, 10);
    list.at(2)->setPos(10, 30);
    list.at(3)->setPos(-10, 30);
}

void LShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(-10, -10);
    list.at(1)->setPos(-10, 10);
    list.at(2)->setPos(-10, 30);
    list.at(3)->setPos(10, 30);
}

void OShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(-10, -10);
    list.at(1)->setPos(10, -10);
    list.at(2)->setPos(-10, 10);
    list.at(3)->setPos(10, 10);
}

void SShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(10, -10);
    list.at(1)->setPos(30, -10);
    list.at(2)->setPos(-10, 10);
    list.at(3)->setPos(10, 10);
}

void TShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(-10, -10);
    list.at(1)->setPos(10, -10);
    list.at(2)->setPos(30, -10);
    list.at(3)->setPos(10, 10);
}

void ZShapeType::setPosition(QList<block *> list) {
    list.at(0)->setPos(-10, -10);
    list.at(1)->setPos(10, -10);
    list.at(2)->setPos(10, 10);
    list.at(3)->setPos(30, 10);
}
