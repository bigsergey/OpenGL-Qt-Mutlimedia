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
    void drawSphere(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);
    void drawCuboid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);
    void drawCylinder(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);
    void drawSurface(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);
    void drawPyramid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);
    void drawLight(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);
    void testdraw(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);


signals:
    void texturePathChanged(QString);

public slots:
    void addTexture(QString);

};

#endif // MAINWIDGET_H
