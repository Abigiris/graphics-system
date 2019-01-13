#ifndef PEN
#define PEN

#include "shape.h"

class Pen : public Shape
{
public:
    Pen();
    Pen(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen);
    ~Pen();

    void setPoint(QPoint a);

    void paintShape(QPainter& p, QImage* image, bool isSave);

private:

};


#endif // PEN

