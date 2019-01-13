#include "pen.h"
#include "line.h"

Pen::Pen() { type = _PEN; }
Pen::Pen(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}

Pen::~Pen() {}

void Pen::setPoint(QPoint a)
{
    QPoint* newP = new QPoint(a);
    points.push_back(newP);
}

void Pen::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    for (int i = 0; i < points.size(); i++)
    {
        if (i < points.size() - 1)
        {
            Line *li = new Line(points[i]->x(), points[i]->y(), points[i+1]->x(), points[i+1]->y(), _LINE, rgb, pen);
            li->paintShape(p, image, isSave);
        }
        p.drawPoint(points[i]->x(), points[i]->y());
        if (isSave)
            image->setPixel(points[i]->x(), points[i]->y(), rgb);
    }
}

