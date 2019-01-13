#ifndef POLY
#define POLY

#include "shape.h"

class Poly : public Shape
{
public:
    Poly();
    Poly(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~Poly();

    void setPoint(QPoint a);
    void setEndPoint(QPoint a);
    void startNewLine(QPoint a);

    bool isPolyEnd();
    QPoint* isAround(QPoint a);
    bool isInside(QPoint a);
    void refreshData();

    void paintShape(QPainter& p, QImage* image, bool isSave);
    void paintFrame(QPainter& p);

    void move(int dx, int dy);
    void rotate(double arg);
    void zoom(double sx, double sy);
    void flip(bool isV);

private:
    bool isEnd ;
};


#endif // POLY

