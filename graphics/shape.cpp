#include "shape.h"

Shape::Shape() {}
Shape::Shape(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}
Shape::~Shape() {}

ShapeType Shape::getType() { return type; }

void Shape::setPoint(QPoint a) {}
void Shape::setPoint(QPoint* point, QPoint a)
{
    if (point == NULL)
        point = new QPoint;
    point->setX(a.x());
    point->setY(a.y());
    refreshData();
}

bool Shape::isAroundPoint(QPoint* point, QPoint a)
{
    if ( fabs(point->x() - a.x()) < 2 && fabs(point->y() - a.y()) < 2 )
        return true;
    return false;
}
QPoint* Shape::isAround(QPoint a) { return NULL;}
bool Shape::isInside(QPoint a) { return false;}
void Shape::refreshData() {}

void Shape::paintShape(QPainter& p, QImage* image, bool isSave) {}
void Shape::paintVertex(QPainter &p, int x, int y)
{
    p.drawPoint(x-1, y-1);
    p.drawPoint(x-1, y);
    p.drawPoint(x-1, y+1);
    p.drawPoint(x, y-1);
    p.drawPoint(x, y);
    p.drawPoint(x, y+1);
    p.drawPoint(x+1, y-1);
    p.drawPoint(x+1, y);
    p.drawPoint(x+1, y+1);
}

void Shape::paintFrame(QPainter& p) {}

void Shape::movePoint(QPoint* point, int dx, int dy)
{
    point->setX(point->x() + dx);
    point->setY(point->y() + dy);
}
void Shape::move(int dx, int dy) {}
void Shape::rotatePoint(QPoint* point, double arg)
{
    double sina = sin(arg);
    double cosa = cos(arg);
    int px = point->x();
    int py = point->y();
    point->setX( centerX+(px-centerX)*cosa-(py-centerY)*sina + 0.5);
    point->setY( centerY+(px-centerX)*sina+(py-centerY)*cosa + 0.5);
}
void Shape::rotate(double arg) {}
void Shape::zoomPoint(QPoint* point, double sx, double sy)
{
    int px = point->x();
    int py = point->y();
    point->setX( px*sx+centerX*(1-sx) + 0.5);
    point->setY( py*sy+centerY*(1-sy) + 0.5);
}
void Shape::zoom(double sx, double sy) {}
void Shape::flipPoint(QPoint *point, bool isV)
{
    if (isV)
    {
        int newY = centerY*2 - point->y();
        point->setY(newY);
    }
    else
    {
        int newX = centerX*2 - point->x();
        point->setX(newX);
    }
}
void Shape::flip(bool isV) {}
void Shape::cutShape(QPoint *cutStartPos, QPoint *cutEndPos) { }
