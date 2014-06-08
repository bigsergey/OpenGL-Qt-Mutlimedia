#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include <QString>
#include <QMessageBox>
#include <QDebug>

class SceneObject
{
public:
    SceneObject();
    void doSomething(QWidget* widget);
    int x;
    int y;
    int z;
    int rotX;
    int rotY;
    int rotZ;
    int sX;
    int sY;
    int sZ;
    int r;
    int g;
    int b;
    QString model;
    QString texture;

public slots:
    void setX(int);
    void setY(int);
    void setZ(int);
    void setRotX(int);
    void setRotY(int);
    void setRotZ(int);
    void setSX(int);
    void setSY(int);
    void setSZ(int);
    void setR(int);
    void setG(int);
    void setB(int);
    void setModel(QString);
    void setTexture(QString);
};

#endif // SCENEOBJECT_H
