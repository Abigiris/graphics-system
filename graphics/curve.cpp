#include "curve.h"
#include "line.h"

Curve::Curve() { type = _CURVE; }
Curve::Curve(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    this->isEnd = false;
    refreshData();
}
Curve::~Curve() {}

void Curve::setPoint(QPoint a)
{
    while (points.size() < 1) //delete
    {
        QPoint* newP = new QPoint;
        points.append(newP);
    }
    points.last()->setX(a.x());
    points.last()->setY(a.y());
    refreshData();
}

void Curve::setEndPoint(QPoint a)
{
    if (points.size() > 2 && isAroundPoint(points[points.size()-2], a))
    {
        isEnd = true;
        points.last() = points[points.size()-2];
    }
    else
    {
        points.last()->setX(a.x());
        points.last()->setY(a.y());
        startNewLine(a);
    }
    refreshData();
}

void Curve::startNewLine(QPoint a)
{
    if (isEnd)
        return ;
    QPoint* newP = new QPoint;
    points.append(newP);
    points.last()->setX(a.x());
    points.last()->setY(a.y());
    refreshData();
}

bool Curve::isCurveEnd() { return isEnd; }
QPoint* Curve::isAround(QPoint a)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (isAroundPoint(points[i], a))
            return points[i];
    }
    return NULL;
}

bool Curve::isInside(QPoint a)
{
    if (!isEnd) return false;
    if ( a.x() > minX + 1 && a.x() < maxX - 1
            && a.y() > minY + 1 && a.y() < maxY - 1 )
        return true;
    return false;
}

void Curve::refreshData()
{
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





int binomialCoeffs(int k,int n)
{
    int i,c = 1;
    if(k == 0)
        return c;
    else
    {
        for(i = n-k+1; i <= n; i++)
            c *= i;
        for(i = 1; i <= k; i++)
            c /= i;
        return c;
    }
}

QPoint Curve::computeBezierPt(float u)
{
    QPoint bezierPt;
    for (int k = 0; k < points.size(); k++)
    {
        float bernstein = binomialCoeffs(k, points.size()-1) * pow(u, k) * pow(1-u, points.size()-1-k);
        int newX = (int)bezierPt.x() + points[k]->x()*bernstein + 0.5;
        int newY = (int)bezierPt.y() + points[k]->y()*bernstein + 0.5;
        bezierPt.setX(newX);
        bezierPt.setY(newY);
    }
    return bezierPt;
}

void Curve::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    int nBezPts = points.size()*50;
    for (int k = 0; k < nBezPts; k++)
    {
        float u = float(k) / float(nBezPts);
        QPoint bezierPt = computeBezierPt(u);
        p.drawPoint(bezierPt.x(), bezierPt.y());
        if (isSave)
            image->setPixel(bezierPt.x(), bezierPt.y(), rgb);
    }
}

void Curve::paintFrame(QPainter& p)
{
    QPen curPen = p.pen();
    QPen framePen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    p.setPen(framePen);
    p.drawLine(minX, minY, minX, maxY);
    p.drawLine(minX, minY, maxX, minY);
    p.drawLine(maxX, minY, maxX, maxY);
    p.drawLine(minX, maxY, maxX, maxY);
    for (int i = 0; i < points.size() - 1; i++)
    {
        paintVertex(p, points[i]->x(), points[i]->y());
    }
    p.setPen(curPen);
}

void Curve::move(int dx, int dy)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        movePoint(points[i], dx, dy);
    }
    refreshData();
}

void Curve::rotate(double arg)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        rotatePoint(points[i], arg);
    }
    refreshData();
}

void Curve::zoom(double sx, double sy)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        zoomPoint(points[i], sx, sy);
    }
    refreshData();
}

void Curve::flip(bool isV)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        flipPoint(points[i], isV);
    }
    refreshData();
}
