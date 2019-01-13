#include "window.h"
#include <math.h>
#include <qmessagebox.h>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <QDebug>
using namespace std;

Window::Window()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Config"), "", tr("OFF Files (*.off)"));
    qDebug() << fileName;
    char*  fileNameChar;
    QByteArray ba = fileName.toLatin1();
    fileNameChar = ba.data();
    ifstream inFile(fileNameChar, ios::in);
    if (!inFile) exit(-1);
    string off;
    inFile >> off;
    inFile >> numVertices >> numFaces >> numEdges;
    //vertex
    GLfloat x, y, z;
    for (int i = 0; i < numVertices; i++)
    {
        inFile >> x >> y >> z;
        MyVertex vi = MyVertex(x, y, z);
        vertices.append(vi);
    }
    //face
    for (int i = 0; i < numFaces; i++)
    {
        MyFace f;
        inFile >> f.numV;
        int index;
        for (int j = 0; j < f.numV; j++)
        {
            inFile >> index;
            f.indexV.append(index);
        }
        faces.append(f);
    }

    startPos = NULL;
    endPos = NULL;
}


Window::~Window()
{

}

void Window::initializeGL()
{
//    initializeOpenGLFunctions();
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initializeOpenGLFunctions();
     glClearColor(0,0,0,1);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_LIGHT0);
     glEnable(GL_LIGHTING);
     glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
     glEnable(GL_COLOR_MATERIAL);
}

void Window::resizeGL(int w, int h)
{
        gluPerspective( 45.0f, w/h, 0.1f, 100.0f );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void Window::mousePressEvent(QMouseEvent *ev)
{
    startPos = new QPoint(ev->pos());
    rotateX = 0;
    rotateY = 0;
}
void Window::mouseMoveEvent(QMouseEvent *ev)
{
    if (endPos == NULL)
        endPos = new QPoint();
    endPos->setX(ev->pos().x());
    endPos->setY(ev->pos().y());

    double x = (double)(endPos->x()-startPos->x())/this->width()*60;
    double y = (double)(endPos->y()-startPos->y())/this->height()*60;
    if (fabs(x) > 5)
    {
        rotateX = x;
    }
    if(fabs(y) > 5)
    {
        rotateY = y;
    }
    update();
}
void Window::mouseReleaseEvent(QMouseEvent *ev)
{
    if (endPos == NULL)
        endPos = new QPoint();
    endPos->setX(ev->pos().x());
    endPos->setY(ev->pos().y());

    double x = (double)(endPos->x()-startPos->x())/this->width()*60;
    double y = (double)(endPos->y()-startPos->y())/this->height()*60;
    if (fabs(x) > 5)
    {
        rotateX = x;
    }
    if(fabs(y) > 5)
    {
        rotateY = y;
    }
    endPos = NULL;
    startPos = NULL;
    update();
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBegin(GL_POLYGON);
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < faces.size(); i++)
        {
            MyFace fi = faces[i];
            for (int j = 0; j < fi.numV; j++)
            {
                switch (fi.indexV[j]%3)
                {
                case 0:
                    glColor3f(1.0f, 0.0f, 0.0f);//蓝色
                    break;
                case 1:
                    glColor3f(0.0f, 1.0f, 0.0f);//蓝色
                    break;
                case 2:
                    glColor3f(0.0f, 0.0f, 1.0f);//蓝色
                    break;
                case 3:
                    glColor3f(0.0f, 1.0f, 1.0f);//蓝色
                    break;
                case 4:
                    glColor3f(1.0f, 0.0f, 1.0f);//蓝色
                    break;
                case 5:
                    glColor3f(1.0f, 1.0f, 0.0f);//蓝色
                    break;
                }

                MyVertex vij = vertices[fi.indexV[j]];
                glVertex3f(vij.vx, vij.vy, vij.vz);
            }
        }

       glEnd();

    glRotated(rotateX, 0.0, -1.0, 0.0);
    glRotated(rotateY, -1.0, 0.0, 0.0);
}


