#ifndef RECT
#define RECT

#include "shape.h"

class Rect : public Shape
{
public:
    Rect();
    Rect(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~Rect();

    void setPoint(QPoint a);

    QPoint* isAround(QPoint a);
    bool isInside(QPoint a);
    void refreshData();

    void paintShape(QPainter& p, QImage* image, bool isSave);
    void paintFrame(QPainter& p);

    void move(int dx, int dy);
    void rotate(double arg);
    void zoom(double sx, double sy);

protected:
    int x1, y1, x2, y2, x3, y3, x4, y4;
};

#endif // RECT

