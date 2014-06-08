#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include <QString>
#include <QMessageBox>

class SceneObject
{
public:
    SceneObject();
    SceneObject(QString name);
    QString name;
    void doSomething(QWidget* widget);
    virtual void draw();
};

#endif // SCENEOBJECT_H
