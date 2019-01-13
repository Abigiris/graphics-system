#ifndef LINE
#define LINE

#include "shape.h"

class Line : public Shape
{
public:
    Line();
    Line(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    Line(int x1, int y1, int x2, int y2, ShapeType type, QRgb rgb, QPen pen);
    ~Line();

    void setPoint(QPoint a);

    QPoint* isAround(QPoint a);
    bool isInside(QPoint a);
    void refreshData();

    void paintShape(QPainter& p, QImage* image, bool isSave);
    void paintFrame(QPainter& p);

    void move(int dx, int dy);
    void rotate(double arg);
    void zoom(double sx, double sy);
    void flip(bool isV);

    void cutShape(QPoint *cutStartPos, QPoint *cutEndPos);

private:
    int x1, y1, x2, y2;
};

#endif // LINE

