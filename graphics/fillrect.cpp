#include "fillrect.h"
#include "line.h"

FillRect::FillRect() { type = _FILLRECT; }
FillRect::FillRect(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}
FillRect::~FillRect() {}
void FillRect::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    for (int i = minX; i <= maxX; i++)
    {
        Line* li = new Line(i, minY, i, maxY, _LINE, rgb, pen);
        li->paintShape(p, image, isSave);
    }
}
