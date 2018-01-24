#ifndef SHAPETYPE_H
#define SHAPETYPE_H

#include <QList>

class ShapeType;
class block;
class Shape {
public:
    Shape(int type);
    int getShape();
    void setShape(int arg);
    void setPosition(QList<block *> list);
private:
    ShapeType *_type;
};

class ShapeType {
public:
    virtual int getTypeCode() = 0;
    virtual void setPosition(QList<block *> list) = 0;
    static ShapeType *newType(int code);
    static const int IShape = 0;
    static const int JShape = 1;
    static const int LShape = 2;
    static const int OShape = 3;
    static const int SShape = 4;
    static const int TShape = 5;
    static const int ZShape = 6;
};

class IShapeType : public ShapeType {
public:
        int getTypeCode() {
            return IShape;
        }
        void setPosition(QList<block *> list);
};

class JShapeType : public ShapeType {
public:
        int getTypeCode() {
            return JShape;
        }
        void setPosition(QList<block *> list);
};

class LShapeType : public ShapeType {
public:
        int getTypeCode() {
            return LShape;
        }
        void setPosition(QList<block *> list);
};

class OShapeType : public ShapeType {
public:
        int getTypeCode() {
            return OShape;
        }
        void setPosition(QList<block *> list);
};

class SShapeType : public ShapeType {
public:
        int getTypeCode() {
            return SShape;
        }
        void setPosition(QList<block *> list);
};

class TShapeType : public ShapeType {
public:
        int getTypeCode() {
            return TShape;
        }
        void setPosition(QList<block *> list);
};

class ZShapeType : public ShapeType {
public:
        int getTypeCode() {
            return ZShape;
        }
        void setPosition(QList<block *> list);
};

#endif //SHAPETYPE_H
