#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shape.h"
#include "window.h"
#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private slots:
    void on_openButton_clicked();
    void on_saveButton_clicked();
    void on_narrowButton_clicked();
    void on_widenButton_clicked();
    void on_moveButton_clicked();
    void on_rotateButton_clicked();
    void on_cutButton_clicked();
    void on_clearButton_clicked();
    void on_resetButton_clicked();
    void on_lineButton_clicked();
    void on_curveButton_clicked();
    void on_rectButton_clicked();
    void on_circleButton_clicked();
    void on_ovalButton_clicked();
    void on_polyButton_clicked();
    void on_penButton_clicked();
    void on_fillButton_clicked();

    void on_actionRotateR90_triggered();

    void on_actionRotateL90_triggered();

    void on_actionRotate180_triggered();

    void on_actionFlipV_triggered();

    void on_actionFlipH_triggered();

    void on_threeDButton_clicked();

    void on_blackPenButton_clicked();

    void on_whitePenButton_clicked();

    void on_redPenButton_clicked();

    void on_greenPenButton_clicked();

    void on_bluePenButton_clicked();

    void on_narrow25_triggered();

    void on_narrow50_triggered();

    void on_narrow75_triggered();

    void on_widen150_triggered();

    void on_widen125_triggered();

    void on_widen200_triggered();

    void on_widen250_triggered();

    void on_fillRectButton_clicked();

    void on_fillCircleButton_clicked();

    void on_fillOvalButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Shape*> shapes;
    ShapeType curShapeType;
    Shape* curShape;
    QPen curPen;

    QImage* image;
    QImage img;
    QRgb rgb;
    bool isSave;
    QString saveFileName;

    QPoint* editPos;
    bool isEdit;

    QPoint* startPos;
    QPoint* endPos;
    bool isMove;

    QPoint* cutStartPos;
    QPoint* cutEndPos;
    bool isCut;
};

#endif // MAINWINDOW_H
