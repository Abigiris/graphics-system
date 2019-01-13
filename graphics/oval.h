#ifndef OVAL_H
#define OVAL_H

#include "shape.h"

class Oval : public Shape
{
public:
    Oval();
    Oval(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~Oval();

    void setPoint(QPoint a);

    QPoint* isAround(QPoint a);
    bool isInside(QPoint a);
    void refreshData();

    void ovalPoints(QPainter& p,QImage* image, bool isSave, int centerX, int centerY, int x, int y);
    void paintShape(QPainter& p, QImage* image, bool isSave);
    void paintFrame(QPainter& p);

    void move(int dx, int dy);
    void rotate(double arg);
    void zoom(double sx, double sy);

protected:
    int x1, y1, x2, y2, x3, y3, x4, y4, ra, rb;
};

#endif // OVAL_H
