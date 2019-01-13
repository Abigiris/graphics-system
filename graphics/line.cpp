#include "line.h"

Line::Line() { type = _LINE; }
Line::Line(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}
Line::Line(int x1, int y1, int x2, int y2, ShapeType type, QRgb rgb, QPen pen)
{
    QPoint* p1 = new QPoint(x1, y1);
    QPoint* p2 = new QPoint(x2, y2);
    points.push_back(p1);
    points.push_back(p2);
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}
Line::~Line() {}

void Line::setPoint(QPoint a)
{
    while (points.size() < 2)
    {
        QPoint* newP = new QPoint;
        points.push_back(newP);
    }
    points[1]->setX(a.x());
    points[1]->setY(a.y());
    refreshData();
}

QPoint* Line::isAround(QPoint a)
{
    if (isAroundPoint(points[0], a))
        return points[0];
    if (isAroundPoint(points[1], a))
        return points[1];
    return NULL;
}
bool Line::isInside(QPoint a)
{
    if ( a.x() > minX + 1 && a.x() < maxX - 1
            && a.y() > minY + 1 && a.y() < maxY - 1 )
        return true;
    return false;
}
void Line::refreshData()
{
    if (points.size() == 0)
        return;
    x1 = points[0]->x();
    y1 = points[0]->y();
    x2 = points.last()->x();
    y2 = points.last()->y();
    if (x1 > x2) { minX = x2; maxX = x1; }
    else { minX = x1; maxX = x2; }
    if (y1 > y2) { minY = y2; maxY = y1; }
    else { minY = y1; maxY = y2; }
    centerX = (x1 + x2) / 2;
    centerY = (y1 + y2) / 2;
}
void Line::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    //DDA
    double dx, dy, e, x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    e =( fabs(dx) > fabs(dy) ) ? fabs(dx) : fabs(dy);
    dx /= e;
    dy /= e;
    x = x1;
    y = y1;
    for (int i = 1; i <= e; i++)
    {
        int px = (int)(x + 0.5);
        int py = (int)(y + 0.5);
        p.drawPoint(px, py);
        if (isSave)
            image->setPixel(px, py, rgb);
        x += dx;
        y += dy;
    }
}
void Line::paintFrame(QPainter& p)
{
    QPen curPen = p.pen();
    QPen framePen(Qt::blue, 1 ,Qt::DashDotLine, Qt::RoundCap);
    p.setPen(framePen);
    p.drawLine(x1, y1, x1, y2);
    p.drawLine(x1, y1, x2, y1);
    p.drawLine(x2, y1, x2, y2);
    p.drawLine(x1, y2, x2, y2);
    paintVertex(p, x1, y1);
    paintVertex(p, x2, y2);
    p.setPen(curPen);
}

void Line::move(int dx, int dy)
{
    for (int i = 0; i < points.size(); i++)
        movePoint(points[i], dx, dy);
    refreshData();
}

void Line::rotate(double arg)
{
    for (int i = 0; i < points.size(); i++)
        rotatePoint(points[i], arg);
    refreshData();
}

void Line::zoom(double sx, double sy)
{
    for (int i = 0; i < points.size(); i++)
        zoomPoint(points[i], sx, sy);
    refreshData();
}

void Line::flip(bool isV)
{
    for (int i = 0; i < points.size(); i++)
        flipPoint(points[i], isV);
    refreshData();
}

int getCode(int x, int y, int minXW, int maxXW, int minYW, int maxYW)
{
    int code = 0;
    if (y > maxYW)
    {
        //qDebug() << "第一位";
        code = code|0x08;
        //qDebug() << code;
    }
    if (y < minYW)
    {
        //qDebug() << "第二位";
        code = code|0x04;
        //qDebug() << code;
    }
    if (x < minXW)
    {
        //qDebug() << "第三位";
        code = code|0x02;
        //qDebug() << code;
    }
    if (x > maxXW)
    {
        //qDebug() << "第三位";
        code = code|0x01;
        //qDebug() << code;
    }

    return code;
}

void Line::cutShape(QPoint *cutStartPos, QPoint *cutEndPos)
{
    int minXW, maxXW, minYW, maxYW;
    if (cutStartPos->x() < cutEndPos->x())
    {
        minXW = cutStartPos->x();
        maxXW = cutEndPos->x();
    }
    else
    {
        minXW = cutEndPos->x();
        maxXW = cutStartPos->x();
    }
    if (cutStartPos->y() < cutEndPos->y())
    {
        minYW = cutStartPos->y();
        maxYW = cutEndPos->y();
    }
    else
    {
        minYW = cutEndPos->y();
        maxYW = cutStartPos->y();
    }

    int code1 = getCode(x1, y1, minXW, maxXW, minYW, maxYW);
    int code2 = getCode(x2, y2, minXW, maxXW, minYW, maxYW);

    //qDebug() << code1 << code2;

    if (code1 == 0 && code2 == 0)
        return;
    if ( (code1 & code2) != 0)
    {
        points.first()->setX(0);
        points.first()->setY(0);
        points.last()->setX(0);
        points.last()->setY(0);
        refreshData();
    }
    double m = (y2 - y1)/ ((double) x2 - x1); //斜率
    //x1在裁剪区域外
    if (code1 != 0)
    {
        if (points.first()->x() < minXW)
        {
            int newY = (int) points.first()->y() + m * (minXW - points.first()->x()) + 0.5;
            points.first()->setY(newY);
            points.first()->setX(minXW);
        }
        if (points.first()->x() > maxXW)
        {
            int newY = (int) points.first()->y() + m * (maxXW - points.first()->x()) + 0.5;
            points.first()->setY(newY);
            points.first()->setX(maxXW);
        }
        if (points.first()->y() < minYW)
        {
            int newX = (int) points.first()->x() + (minYW - points.first()->y()) / m + 0.5;
            points.first()->setX(newX);
            points.first()->setY(minYW);
        }
        if (points.first()->y() > maxYW)
        {
            int newX = (int) points.first()->x() + (maxYW - points.first()->y()) / m + 0.5;
            points.first()->setX(newX);
            points.first()->setY(maxYW);
        }
    }
    //x2在剪裁区域外
    if (code2 != 0)
    {
        if (points.last()->x() < minXW)
        {
            int newY = (int) points.last()->y() + m * (minXW - points.last()->x()) + 0.5;
            points.last()->setY(newY);
            points.last()->setX(minXW);
        }
        if (points.last()->x() > maxXW)
        {
            int newY = (int) points.last()->y() + m * (maxXW - points.last()->x()) + 0.5;
            points.last()->setY(newY);
            points.last()->setX(maxXW);
        }
        if (points.last()->y() < minYW)
        {
            int newX = (int) points.last()->x() + (minYW - points.last()->y()) / m + 0.5;
            points.last()->setX(newX);
            points.last()->setY(minYW);
        }
        if (points.last()->y() > maxYW)
        {
            int newX = (int) points.last()->x() + (maxYW - points.last()->y()) / m + 0.5;
            points.last()->setX(newX);
            points.last()->setY(maxYW);
        }
    }
    refreshData();
}
