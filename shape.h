#ifndef SHAPE_H
#define SHAPE_H

#include "shapetype.h"

class Shape {
public:
    Shape(int type) {
        setShape(type);
    }
    int getShape() {
        return _type->getTypeCode();
    }
    void setShape(int arg) {
        switch (arg) {
            case IShape:
                _type = new IShapeType();
                break;
            case JShape:
                _type = new JShapeType();
            default:
                break;
        }
    }
    void setPosition() {
        switch(getShape()) {
            case IShape:
            break;
            case JShape:
            break;
        }
    }
    static const int IShape = 0;
    static const int JShape = 1;
private:
    ShapeType *_type;
};

#endif // SHAPE_H
