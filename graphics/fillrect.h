#ifndef FILLRECT_H
#define FILLRECT_H

#include "rect.h"

class FillRect : public Rect
{
public:
    FillRect();
    FillRect(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~FillRect();
    void paintShape(QPainter& p, QImage* image, bool isSave);
};

#endif // FILLRECT_H
