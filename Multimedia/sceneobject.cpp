#include "sceneobject.h"

SceneObject::SceneObject()
{
    name="Dupa";
}
SceneObject::SceneObject(QString name)
{
    this->name=name;
}

void SceneObject::draw(){

}

void SceneObject::doSomething(QWidget* widget){
    QMessageBox::information(
        widget,
        QString("About"),
        name
       );
}
