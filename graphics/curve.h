#ifndef CURVE
#define CURVE

#include "shape.h"

class Curve : public Shape
{
public:
    Curve();
    Curve(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~Curve();

    void setPoint(QPoint a);
    void setEndPoint(QPoint a);
    void startNewLine(QPoint a);

    bool isCurveEnd();
    QPoint* isAround(QPoint a);
    bool isInside(QPoint a);
    void refreshData();

    QPoint computeBezierPt(float u);
    void paintShape(QPainter& p, QImage* image, bool isSave);
    void paintFrame(QPainter& p);

    void move(int dx, int dy);
    void rotate(double arg);
    void zoom(double sx, double sy);
    void flip(bool isV);

private:
    bool isEnd;
};

#endif // CURVE

