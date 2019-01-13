#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QCloseEvent>
#include <GL/glu.h>
#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QVector>

struct MyVertex
{
    GLfloat vx;
    GLfloat vy;
    GLfloat vz;
    MyVertex() {}
    MyVertex(GLfloat x, GLfloat y, GLfloat z) : vx(x), vy(y), vz(z) {}
};

struct MyFace
{
    int numV;
    QVector<int> indexV;
};


class Window : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    Window();
    ~Window();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    int numVertices, numFaces, numEdges;
    QVector<MyVertex> vertices;
    QVector<MyFace> faces;

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    QPoint* startPos;
    QPoint* endPos;
    double rotateX;
    double rotateY;
};

#endif // WINDOW_H
