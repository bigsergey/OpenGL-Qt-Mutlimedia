#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#define END(array) (array + sizeof(array)/sizeof(array[0]))

#include <QGLWidget>
#include <QString>
#include <QDebug>
#include "sceneobject.h"
#include <QList>
#include <gl/GLU.h>

class MainWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void setSceneObjects(QList<SceneObject*> *sceneObjects);
    void mousePressEvent ( QMouseEvent * event );


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    QMap <QString, QString> textures;
    GLfloat lightPosition[4];
    float ambient[4];

private:
    QList<SceneObject*> * sceneObjects;
    void draw();
    void drawSphere(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);
    void drawCuboid(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);
    void drawCylinder(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);
    void drawSurface(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);
    void drawPyramid(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);
    void drawLight(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);
    void testdraw(double x, double y, double z, int rotX, int rotY, int rotZ, double sX, double SY, double sZ, int r, int g, int b, QString texture);

    float cameraPosX;
    float cameraPosY;
    float cameraPosZ;


signals:
    void texturePathChanged(QString);

public slots:
    void addTexture(QString);
    void moveCameraForvard();
    void moveCameraBack();
    void moveCameraLeft();
    void moveCameraRight();
    void moveCameraUp();
    void moveCameraDown();
    void rotateCameraX();
    void rotateCameraY();

};

#endif // MAINWIDGET_H
