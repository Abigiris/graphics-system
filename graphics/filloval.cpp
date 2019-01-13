#include "filloval.h"
#include "line.h"

FillOval::FillOval() { type = _FILLOVAL; }

FillOval::FillOval(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}

FillOval::~FillOval() { }

void FillOval::ovalPoints(QPainter& p,QImage* image, bool isSave, int centerX, int centerY, int x, int y)
{
    Line *l1 = new Line(x+centerX, y+centerY, -x+centerX, -y+centerY, _LINE, rgb, pen);
    Line *l2 = new Line(-x+centerX, y+centerY, x+centerX, -y+centerY, _LINE, rgb, pen);
    l1->paintShape(p, image, isSave);
    l2->paintShape(p, image, isSave);
    Line *l3 = new Line(x+centerX, y+centerY, x+centerX, -y+centerY, _LINE, rgb, pen);
    Line *l4 = new Line(x+centerX, y+centerY, -x+centerX, y+centerY, _LINE, rgb, pen);
    Line *l5 = new Line(-x+centerX, -y+centerY, x+centerX, -y+centerY, _LINE, rgb, pen);
    Line *l6 = new Line(-x+centerX, -y+centerY, -x+centerX, y+centerY, _LINE, rgb, pen);
    l3->paintShape(p, image, isSave);
    l4->paintShape(p, image, isSave);
    l5->paintShape(p, image, isSave);
    l6->paintShape(p, image, isSave);
}

void FillOval::paintShape(QPainter& p, QImage* image, bool isSave)
{
    p.setPen(pen);
    int x = 0, y = rb;
    ovalPoints(p, image, isSave, centerX, centerY, x, y);

    double d1 = pow(rb, 2) - pow(ra, 2) * rb + 0.25 * pow(ra, 2);
    while ( pow(ra,2) * (y - 0.5) > pow(rb, 2) * (x + 1) )
    {
        //在区域一
        if (d1 < 0) //选择E点
        {
            d1 += pow(rb, 2)*(2 * x + 3);
        }
        else          //选择SE点
        {
            d1 += pow(rb, 2)*(2 * x + 3) + pow(ra, 2)*(-2 * y + 2);
            y--;
        }
        x++;
        ovalPoints(p, image, isSave, centerX, centerY, x, y);

    }

    double d2 = pow(rb, 2) * pow(x + 0.5, 2) + pow(ra, 2) * pow(y - 1, 2) - pow(ra * rb, 2);
    while (y > 0)       //区域二
    {
        if (d2 < 0)       //选择SE点
        {
            d2 += pow(rb, 2) * (2 * x + 2) + pow(ra, 2)*(-2 * y + 3);
            x++;
        }
        else
        {
            d2 += pow(ra, 2) * (-2 * y + 3);
        }
        y--;
        ovalPoints(p, image, isSave, centerX, centerY, x, y);
    }
}
