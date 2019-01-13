#ifndef FILLOVAL_H
#define FILLOVAL_H

#include "oval.h"

class FillOval : public Oval
{
public:
    FillOval();
    FillOval(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~FillOval();
    void ovalPoints(QPainter& p,QImage* image, bool isSave, int centerX, int centerY, int x, int y);
    void paintShape(QPainter& p, QImage* image, bool isSave);
};

#endif // FILLOVAL_H
