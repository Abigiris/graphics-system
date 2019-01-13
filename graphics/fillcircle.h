#ifndef FILLCIRCLE_H
#define FILLCIRCLE_H

#include "circle.h"

class FillCircle : public Circle
{
public:
    FillCircle();
    FillCircle(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~FillCircle();
    void circlePoints(QPainter& p,QImage* image, bool isSave, int centerX, int centerY, int x, int y);
    void paintShape(QPainter& p, QImage* image, bool isSave);
};

#endif // FILLCIRCLE_H
