#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "shape.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include "oval.h"
#include "poly.h"
#include "curve.h"
#include "pen.h"
#include "fill.h"
#include "fillrect.h"
#include "fillcircle.h"
#include "filloval.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curShapeType = BLANK;
    curShape = NULL;

    image = new QImage(700, 500, QImage::Format_RGB888);
    img = QImage(700, 500, QImage::Format_RGB888);
    rgb = qRgb(0, 0, 0);
    isSave = false;

    QRgb bgRgb = qRgb(255, 255, 255); //background: white
    for (int i = 0; i < image->width(); i++)
        for (int j = 0; j < image->height(); j++)
            image->setPixel(i, j, bgRgb);

    editPos = NULL;
    isEdit = false;

    startPos = NULL;
    endPos = NULL;
    isMove = false;

    cutStartPos = NULL;
    cutEndPos = NULL;
    isCut = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    if (isSave)
    {
        QRgb bgRgb = qRgb(255, 255, 255); //background: white
        for (int i = 0; i < image->width(); i++)
            for (int j = 0; j < image->height(); j++)
                image->setPixel(i, j, bgRgb);
    }

    QPainter p(this);
    p.setPen(curPen);


    if (curShape != NULL)
    {
        for(int i=0; i<shapes.size() - 1; i++)
        {
            shapes[i]->paintShape(p, image, true);
        }
        curShape->paintShape(p, image, isSave);
    }
    else
    {
        for(int i=0; i<shapes.size(); i++)
        {
            shapes[i]->paintShape(p, image, true);
        }
    }


    if (isSave)
    {
        qDebug() << "now save" << saveFileName;
        image->save(saveFileName);
        isSave = false;
    }
    if (isEdit)
    {
       curShape->paintFrame(p);
    }
    if (isCut)
    {
        QPen cutPen(Qt::green, 1 ,Qt::DashDotLine, Qt::RoundCap);
        p.setPen(cutPen);
        int sx = cutStartPos->x();
        int sy = cutStartPos->y();
        int ex = cutEndPos->x();
        int ey = cutEndPos->y();
        p.drawLine(sx, sy, sx, ey);
        p.drawLine(sx, sy, ex, sy);
        p.drawLine(sx, ey, ex, ey);
        p.drawLine(ex, sy, ex, ey);
        p.setPen(curPen);

    }
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (isCut && curShape != NULL && curShape->getType() == _LINE)
    {
        cutStartPos->setX(ev->pos().x());
        cutStartPos->setY(ev->pos().y());
    }
    else if (curShape != NULL && isEdit && curShape->isAround(ev->pos()) != NULL) //edit point
    {
        editPos = curShape->isAround(ev->pos());
    }
    else if (curShape != NULL && isEdit && curShape->isInside(ev->pos())) //move
    {
        isMove = true;
        startPos = new QPoint;
        startPos->setX(ev->pos().x());
        startPos->setY(ev->pos().y());
    }
    else
    {
        QVector<QPoint*> points;
        QPoint* evPos = new QPoint(ev->pos());
        points.push_back(evPos);
        Line* line = new Line(points,curShapeType, rgb, curPen);
        Rect* rect = new Rect(points, curShapeType, rgb, curPen);
        Circle* circle = new Circle(points, curShapeType, rgb, curPen);
        Oval* oval = new Oval(points, curShapeType, rgb, curPen);
        Poly* poly = new Poly(points, curShapeType, rgb, curPen);
        Curve* curve = new Curve(points, curShapeType, rgb, curPen);
        Pen* pen = new Pen(points,curShapeType, rgb, curPen);
        Fill* fill = new Fill(points, curShapeType, rgb, curPen);
        class FillRect* fillRect = new class FillRect(points, curShapeType, rgb, curPen);
        class FillCircle *fillCircle = new class FillCircle(points, curShapeType, rgb, curPen);
        class FillOval *fillOval = new class FillOval(points, curShapeType, rgb, curPen);
        switch (curShapeType)
        {
        case _LINE:
            shapes.append(line);
            curShape = line;
            break;
        case _RECT:
            shapes.append(rect);
            curShape = rect;
            break;
        case _CIRCLE:
            shapes.append(circle);
            curShape = circle;
            break;
        case _OVAL:
            shapes.append(oval);
            curShape = oval;
            break;
        case _POLY:
            if (curShape != NULL && curShape->getType() == _POLY && !((Poly*)curShape)->isPolyEnd())
            {
                //((Poly*)curShape)->startNewLine(ev->pos());
                curShape->setPoint(ev->pos());
            }
            else
            {
                shapes.append(poly);
                poly->startNewLine(ev->pos());
                curShape = poly;
            }
            break;
        case _CURVE:
            if (curShape != NULL && curShape->getType() == _CURVE && !((Curve*)curShape)->isCurveEnd())
            {
                curShape->setPoint(ev->pos());
            }
            else
            {
                shapes.append(curve);
                curve->startNewLine(ev->pos());
                curShape = curve;
            }
            break;
        case _PEN:
            shapes.append(pen);
            curShape = pen;
            break;
        case _FILL:
            shapes.append(fill);
            curShape = fill;
            break;
        case _FILLRECT:
            shapes.append(fillRect);
            curShape = fillRect;
            break;
        case _FILLCIRCLE:
            shapes.append(fillCircle);
            curShape = fillCircle;
            break;
        case _FILLOVAL:
            shapes.append(fillOval);
            curShape = fillOval;
            break;
        default:
            break;
        }

        isEdit = false;
        isMove = false;
    }
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (isCut && isEdit && curShape != NULL && curShape->getType() == _LINE)
    {
        cutEndPos->setX(ev->pos().x());
        cutEndPos->setY(ev->pos().y());
    }
    else if (isMove)
    {
        if (endPos == NULL)
            endPos = new QPoint;
        endPos->setX(ev->pos().x());
        endPos->setY(ev->pos().y());
        curShape->move(endPos->x() - startPos->x(), endPos->y() - startPos->y());
        startPos->setX(ev->pos().x());
        startPos->setY(ev->pos().y());
    }
    else if (editPos != NULL)
    {
        curShape->setPoint(editPos, ev->pos());
    }
    else
    {
        if (curShape != NULL)
        {
            curShape->setPoint(ev->pos());
        }

    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if (isCut && isEdit &&curShape != NULL && curShape->getType() == _LINE)
    {
        cutEndPos->setX(ev->pos().x());
        cutEndPos->setY(ev->pos().y());
        curShape->cutShape(cutStartPos, cutEndPos);
        cutEndPos = NULL;
        cutStartPos = NULL;
        isCut = false;
    }
    else if (isMove)
    {
        isMove = false;
        if (endPos == NULL)
            endPos = new QPoint;
        endPos->setX(ev->pos().x());
        endPos->setY(ev->pos().y());
        curShape->move(endPos->x() - startPos->x(), endPos->y() - startPos->y());
        startPos = NULL;
        endPos = NULL;
    }
    else if (editPos != NULL)
    {
        curShape->setPoint(editPos, ev->pos());
        editPos = NULL;
    }
    else
    {
        if (curShape != NULL)
        {
            if (curShape->getType() == _POLY)
                ((Poly*)curShape)->setEndPoint(ev->pos());
            else if (curShape->getType() == _CURVE)
                ((Curve*)curShape)->setEndPoint(ev->pos());
            else
                curShape->setPoint(ev->pos());

            if (curShape->getType() == _POLY && !((Poly*)curShape)->isPolyEnd())
                isEdit = false;
            else if (curShape->getType() == _CURVE && !((Curve*)curShape)->isCurveEnd())
                isEdit = false;
            else
                 isEdit = true;
        }
    }

    update();
}

void MainWindow::on_openButton_clicked()
{
    qDebug() << "open";
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
            tr("Open Config"), "", tr("JPG Files (*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF)"));
    qDebug() << fileName;
    image->load(fileName);
    ui->label->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::on_saveButton_clicked()
{
    qDebug() << "save";
    isSave = true;
    saveFileName = QFileDialog::getSaveFileName(this,
            tr("Save Image"),
            "",
            tr("JPG Files (*.jpg)")); //选择路径
    qDebug() << saveFileName;
    image->save(saveFileName);
    update();
}

void MainWindow::on_narrowButton_clicked()
{
    qDebug() << "narrow 0.8";
    if (curShape != NULL)
    {
        curShape->zoom(0.8, 0.8);
        update();
    }
}

void MainWindow::on_widenButton_clicked()
{
    qDebug() << "widen 1.2";
    if (curShape != NULL)
    {
        curShape->zoom(1.2, 1.2);
        update();
    }
}

void MainWindow::on_moveButton_clicked()
{
    qDebug() << "move";
}

void MainWindow::on_rotateButton_clicked()
{
    qDebug() << "rotate 90°";
     if (curShape != NULL)
     {
         curShape->rotate(0.5*acos(-1));
         update();
     }
}

void MainWindow::on_cutButton_clicked()
{
    qDebug() << "cut";
    cutStartPos = new QPoint;
    cutEndPos = new QPoint;
    isCut = true;
}

void MainWindow::on_clearButton_clicked()
{
    qDebug() << "clear" ;
    shapes.clear();
    curShape = NULL;
    isEdit = false;
    isMove = false;
    QRgb bgRgb = qRgb(255, 255, 255); //background: white
    for (int i = 0; i < image->width(); i++)
        for (int j = 0; j < image->height(); j++)
            image->setPixel(i, j, bgRgb);
    update();
}

void MainWindow::on_resetButton_clicked()
{
    qDebug() << "reset" ;
    curShapeType = BLANK;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_lineButton_clicked()
{
    qDebug() << "line" ;
    curShapeType = _LINE;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_curveButton_clicked()
{
    qDebug() << "curve" ;
    curShapeType = _CURVE;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_rectButton_clicked()
{
    qDebug() << "rect" ;
    curShapeType = _RECT;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_circleButton_clicked()
{
    qDebug() << "circle" ;
    curShapeType = _CIRCLE;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_ovalButton_clicked()
{
    qDebug() << "oval" ;
    curShapeType = _OVAL;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_polyButton_clicked()
{
    qDebug() << "poly" ;
    curShapeType = _POLY;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_penButton_clicked()
{
    qDebug() << "pen" ;
    curShapeType = _PEN;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_fillButton_clicked()
{
    qDebug() << "fill" ;
    curShapeType = _FILL;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_actionRotateR90_triggered()
{
    qDebug() << "rotate R 90°";
     if (curShape != NULL)
     {
         curShape->rotate(0.5*acos(-1));
         update();
     }
}

void MainWindow::on_actionRotateL90_triggered()
{
    qDebug() << "rotate L 90°";
     if (curShape != NULL)
     {
         curShape->rotate(0.5*acos(-1));
         curShape->rotate(0.5*acos(-1));
         curShape->rotate(0.5*acos(-1));
         update();
     }
}

void MainWindow::on_actionRotate180_triggered()
{
    qDebug() << "rotate 180°";
     if (curShape != NULL)
     {
         curShape->rotate(0.5*acos(-1));
         curShape->rotate(0.5*acos(-1));
         update();
     }
}

void MainWindow::on_actionFlipV_triggered()
{
    qDebug() << "flip V";
     if (curShape != NULL)
     {
         curShape->flip(true);
         update();
     }
}

void MainWindow::on_actionFlipH_triggered()
{
    qDebug() << "flip H";
     if (curShape != NULL)
     {
         curShape->flip(false);
         update();
     }
}

void MainWindow::on_threeDButton_clicked()
{
    Window *window = new Window();
    window->resize(QSize(500, 500));
    window->show();
}

void MainWindow::on_blackPenButton_clicked()
{
    curPen.setColor(Qt::black);
    rgb = qRgb(0, 0, 0);
}

void MainWindow::on_whitePenButton_clicked()
{
    curPen.setColor(Qt::white);
    rgb = qRgb(255, 255, 255);
}

void MainWindow::on_redPenButton_clicked()
{
    curPen.setColor(Qt::red);
    rgb = qRgb(255, 0, 0);
}

void MainWindow::on_greenPenButton_clicked()
{
    curPen.setColor(Qt::green);
    rgb = qRgb(0, 255, 0);
}

void MainWindow::on_bluePenButton_clicked()
{
    curPen.setColor(Qt::blue);
    rgb = qRgb(0, 0, 255);
}

void MainWindow::on_narrow25_triggered()
{
    qDebug() << "narrow 0.25";
    if (curShape != NULL)
    {
        curShape->zoom(0.25, 0.25);
        update();
    }
}

void MainWindow::on_narrow50_triggered()
{
    qDebug() << "narrow 0.5";
    if (curShape != NULL)
    {
        curShape->zoom(0.5, 0.5);
        update();
    }
}

void MainWindow::on_narrow75_triggered()
{
    qDebug() << "narrow 0.75";
    if (curShape != NULL)
    {
        curShape->zoom(0.75, 0.75);
        update();
    }
}

void MainWindow::on_widen125_triggered()
{
    qDebug() << "widen 1.25";
    if (curShape != NULL)
    {
        curShape->zoom(1.25, 1.25);
        update();
    }
}

void MainWindow::on_widen150_triggered()
{
    qDebug() << "widen 1.5";
    if (curShape != NULL)
    {
        curShape->zoom(1.5, 1.5);
        update();
    }
}



void MainWindow::on_widen200_triggered()
{
    qDebug() << "widen 2.0";
    if (curShape != NULL)
    {
        curShape->zoom(2.0, 2.0);
        update();
    }
}

void MainWindow::on_widen250_triggered()
{
    qDebug() << "widen 2.5";
    if (curShape != NULL)
    {
        curShape->zoom(2.5, 2.5);
        update();
    }
}

void MainWindow::on_fillRectButton_clicked()
{
    qDebug() << "fill rect" ;
    curShapeType = _FILLRECT;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_fillCircleButton_clicked()
{
    qDebug() << "fill circle" ;
    curShapeType = _FILLCIRCLE;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}

void MainWindow::on_fillOvalButton_clicked()
{
    qDebug() << "fill oval" ;
    curShapeType = _FILLOVAL;
    curShape = NULL;
    isEdit = false;
    isMove = false;
    update();
}
