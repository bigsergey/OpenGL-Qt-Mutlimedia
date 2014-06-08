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

void SceneObject::setX(int x) {
    qDebug() << x;
    this->x = x;
}

void SceneObject::setY(int y) {
    this->y = y;
}

void SceneObject::setZ(int z) {
    this->z = z;
}

void SceneObject::setRotX(int rotX) {
    this->rotX = rotX;
}

void SceneObject::setRotY(int rotY) {
    this->rotY = rotY;
}

void SceneObject::setRotZ(int rotZ) {
    this->rotZ = rotZ;
}

void SceneObject::setSX(int sX) {
    this->sX = sX;
}

void SceneObject::setSY(int sY) {
    this->sY= sY;
}

void SceneObject::setSZ(int sZ) {
    this->sZ = sZ;
}

void SceneObject::setR(int r) {
    this->r = r;
}

void SceneObject::setG(int g) {
    this->g = g;
}

void SceneObject::setB(int b) {
    this->b = b;
}

void SceneObject::setModel(QString model) {
    this->model = model;
}

void SceneObject::setTexture(QString texture) {
    this->texture = texture;
}
