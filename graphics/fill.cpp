#include "fill.h"

Fill::Fill() { type = _FILL;}
Fill::Fill(QVector<QPoint *> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}
Fill::~Fill() { }

void Fill::refreshData()
{

}

bool notEdge(QImage* image, int x, int y)
{
    return image->pixel(x, y) == qRgb(255, 255, 255);
}

void Fill::addPoint(QImage* image, int x, int y)
{
    QPoint* pt = new QPoint(x, y);
    image->setPixel(x, y, rgb);
    points.append(pt);

    if (x < 2 || x > image->width() -2 || y < 2 || y > image->height()-2)
        return;

    if (notEdge(image, x+1, y))
        addPoint(image, x+1, y);
    if (notEdge(image, x-1, y))
        addPoint(image, x-1, y);
    if (notEdge(image, x, y+1))
        addPoint(image, x, y+1);
    if (notEdge(image, x, y-1))
        addPoint(image, x, y-1);
}

void Fill::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    if (points.size() < 2)
    {
        addPoint(image, points.first()->x(), points.first()->y());
    }
    for (int i = 0; i < points.size(); i++)
    {
        p.drawPoint(points[i]->x(), points[i]->y());
        if (isSave)
            image->setPixel(points[i]->x(), points[i]->y(), rgb);
    }
}

