#include "sceneobject.h"

SceneObject::SceneObject()
{
}

void SceneObject::doSomething(QWidget* widget){
    QMessageBox::information(
        widget,
        QString("About"),
        QString("Trololo")
       );
}
