#include "fillcircle.h"
#include "line.h"

FillCircle::FillCircle() { type = _FILLCIRCLE; }

FillCircle::FillCircle(QVector<QPoint*> points, ShapeType type, QRgb rgb, QPen pen)
{
    this->points = points;
    this->type = type;
    this->rgb = rgb;
    this->pen = pen;
    refreshData();
}

FillCircle::~FillCircle() {}

void FillCircle::circlePoints(QPainter& p,QImage* image, bool isSave, int centerX, int centerY, int x, int y)
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

void FillCircle::paintShape(QPainter& p, QImage* image,  bool isSave)
{
    p.setPen(pen);
    int ra = r;
    int rb = r;
    int x = 0, y = rb;
    circlePoints(p, image, isSave, centerX, centerY, x, y);

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
        circlePoints(p, image,isSave, centerX, centerY, x, y);

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
        circlePoints(p, image, isSave, centerX, centerY, x, y);
    }
}
