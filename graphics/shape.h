#ifndef SHAPE
#define SHAPE

#include <QVector>
#include <QPoint>
#include <QPainter>
#include <cmath>
#include <QDebug>

enum ShapeType { BLANK, _LINE, _CURVE, _RECT, _CIRCLE, _OVAL, _POLY, _PEN, _FILL, _FILLRECT, _FILLCIRCLE, _FILLOVAL};

class Shape
{
public:
    Shape();
    Shape(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~Shape();

    ShapeType getType();

    virtual void setPoint(QPoint a);
    void setPoint(QPoint* point, QPoint a);

    bool isAroundPoint(QPoint* point, QPoint a);
    virtual QPoint* isAround(QPoint a);
    virtual bool isInside(QPoint a);
    virtual void refreshData();

    virtual void paintShape(QPainter& p, QImage* image, bool isSave);
    void paintVertex(QPainter& p, int x, int y);
    virtual void paintFrame(QPainter& p);

    void movePoint(QPoint* point, int dx, int dy);
    virtual void move(int dx, int dy);
    void rotatePoint(QPoint* point, double arg);
    virtual void rotate(double arg);
    void zoomPoint(QPoint* point, double sx, double sy);
    virtual void zoom(double sx, double sy);
    void flipPoint(QPoint* point, bool isV);
    virtual void flip(bool isV);
    virtual void cutShape(QPoint* cutStartPos, QPoint* cutEndPos);
protected:
    ShapeType type;
    QVector<QPoint*> points;
    int centerX, centerY;
    int minX, maxX, minY, maxY;
    QRgb rgb;
    QPen pen;
};

#endif // SHAPE

