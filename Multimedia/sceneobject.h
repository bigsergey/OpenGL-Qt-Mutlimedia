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
    double x;
    double y;
    double z;
    int rotX;
    int rotY;
    int rotZ;
    double sX;
    double sY;
    double sZ;
    int r;
    int g;
    int b;
    QString model;
    QString texture;

public slots:
    void setX(double);
    void setY(double);
    void setZ(double);
    void setRotX(int);
    void setRotY(int);
    void setRotZ(int);
    void setSX(double);
    void setSY(double);
    void setSZ(double);
    void setR(int);
    void setG(int);
    void setB(int);
    void setModel(QString);
    void setTexture(QString);
};

#endif // SCENEOBJECT_H
