#ifndef SPHERE_H
#define SPHERE_H
#include <QString>
#include "sceneobject.h"

class Sphere : public SceneObject
{
public:
    Sphere();
    Sphere(QString name);
    void draw();
};

#endif // SPHERE_H
