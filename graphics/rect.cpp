#include "rect.h"
#include "line.h"

Rect::Rect() { type = _RECT; }
Rect::Rect(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}
Rect::~Rect() {}

void Rect::setPoint(QPoint a)
{
    while (points.size() < 4)
    {
        QPoint* newP = new QPoint;
        points.push_back(newP);
    }
    points[2]->setX(a.x());
    points[2]->setY(a.y());
    refreshData();
}

QPoint* Rect::isAround(QPoint a)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (isAroundPoint(points[i], a))
            return points[i];
    }
    return NULL;
}

bool Rect::isInside(QPoint a)
{
    if ( a.x() > minX + 1 && a.x() < maxX - 1
            && a.y() > minY + 1 && a.y() < maxY - 1 )
        return true;
    return false;
}

void Rect::refreshData()
{
    x1 = points[0]->x();
    y1 = points[0]->y();
    if (points.size() < 4)
    {
        x2 = x1;
        y2 = y1;
        x3 = x1;
        y3 = y1;
        x4 = x1;
        y4 = y1;
    }
    else
    {
        //先水平后垂直，顺时针排序
        points[1]->setX(points[2]->x());
        points[1]->setY(points[0]->y());
        points[3]->setX(points[0]->x());
        points[3]->setY(points[2]->y());

        x2 = points[1]->x();
        y2 = points[1]->y();
        x3 = points[2]->x();
        y3 = points[2]->y();
        x4 = points[3]->x();
        y4 = points[3]->y();
    }
    minX = points[0]->x();
    maxX = points[0]->x();
    minY = points[0]->y();
    maxY = points[0]->y();
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i]->x() > maxX) maxX = points[i]->x();
        if (points[i]->x() < minX) minX = points[i]->x();
        if (points[i]->y() > maxY) maxY = points[i]->y();
        if (points[i]->y() < minY) minY = points[i]->y();
    }
    centerX = (minX + maxX) / 2;
    centerY = (minY + maxY) / 2;
}

void Rect::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    Line* l12 = new Line(x1, y1, x2, y2, _LINE, rgb, pen);
    l12->paintShape(p, image, isSave);
    Line* l23 = new Line(x2, y2, x3, y3, _LINE, rgb, pen);
    l23->paintShape(p, image, isSave);
    Line* l34 = new Line(x3, y3, x4, y4, _LINE, rgb, pen);
    l34->paintShape(p, image, isSave);
    Line* l41 = new Line(x4, y4, x1, y1, _LINE, rgb, pen);
    l41->paintShape(p, image, isSave);
}

void Rect::paintFrame(QPainter& p)
{
    QPen curPen = p.pen();
    QPen framePen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    p.setPen(framePen);
    p.drawLine(x1, y1, x2, y2);
    p.drawLine(x2, y2, x3, y3);
    p.drawLine(x3, y3, x4, y4);
    p.drawLine(x4, y4, x1, y1);
    paintVertex(p, x1, y1);
    paintVertex(p, x3, y3);
    p.setPen(curPen);
}

void Rect::move(int dx, int dy)
{
    for (int i = 0; i < points.size(); i++)
    {
        movePoint(points[i], dx, dy);
    }
    refreshData();
}

void Rect::rotate(double arg)
{
    for (int i = 0; i < points.size(); i++)
    {
        rotatePoint(points[i], arg);
    }
    refreshData();
}

void Rect::zoom(double sx, double sy)
{
    for (int i = 0; i < points.size(); i++)
    {
        zoomPoint(points[i], sx, sy);
    }
    refreshData();
}
