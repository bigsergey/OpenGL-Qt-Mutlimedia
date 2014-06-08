#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent)
{

}


void MainWidget::addTexture(QString path) {
   textures[textureNumber] = bindTexture
        (QPixmap(QString(path)), GL_TEXTURE_2D);
   textureNumber++;
   qDebug() << textureNumber;
}
void MainWidget::setSceneObjects(QList<SceneObject*> *sceneObjects){
    this->sceneObjects=sceneObjects;
}

void MainWidget::initializeGL()
{
    qDebug() << "initGL";
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    //initialize textures
    for(int j=0; j<textureNumber; ++j) {
        textures[j]=bindTexture
                (QPixmap(QString(":/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }
}

void MainWidget::paintGL()
{
    qDebug() << "paintGl";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    draw();
}

void MainWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MainWidget::draw()
{
    for(int i=0; i<sceneObjects->count(); i++){
        if(sceneObjects->at(i)->model==QString("sphere")){
            drawSphere(sceneObjects->at(i)->x,
                       sceneObjects->at(i)->y,
                       sceneObjects->at(i)->z,
                       sceneObjects->at(i)->rotX,
                       sceneObjects->at(i)->rotY,
                       sceneObjects->at(i)->rotZ,
                       sceneObjects->at(i)->sX,
                       sceneObjects->at(i)->sY,
                       sceneObjects->at(i)->sZ,
                       sceneObjects->at(i)->r,
                       sceneObjects->at(i)->g,
                       sceneObjects->at(i)->b,
                       sceneObjects->at(i)->texture);
        }else if(sceneObjects->at(i)->model==QString("cuboid")){
            drawCuboid(sceneObjects->at(i)->x,
                       sceneObjects->at(i)->y,
                       sceneObjects->at(i)->z,
                       sceneObjects->at(i)->rotX,
                       sceneObjects->at(i)->rotY,
                       sceneObjects->at(i)->rotZ,
                       sceneObjects->at(i)->sX,
                       sceneObjects->at(i)->sY,
                       sceneObjects->at(i)->sZ,
                       sceneObjects->at(i)->r,
                       sceneObjects->at(i)->g,
                       sceneObjects->at(i)->b,
                       sceneObjects->at(i)->texture);
        }else if(sceneObjects->at(i)->model==QString("cylinder")){
            drawCylinder(sceneObjects->at(i)->x,
                       sceneObjects->at(i)->y,
                       sceneObjects->at(i)->z,
                       sceneObjects->at(i)->rotX,
                       sceneObjects->at(i)->rotY,
                       sceneObjects->at(i)->rotZ,
                       sceneObjects->at(i)->sX,
                       sceneObjects->at(i)->sY,
                       sceneObjects->at(i)->sZ,
                       sceneObjects->at(i)->r,
                       sceneObjects->at(i)->g,
                       sceneObjects->at(i)->b,
                       sceneObjects->at(i)->texture);
        }else if(sceneObjects->at(i)->model==QString("surface")){
            drawSurface(sceneObjects->at(i)->x,
                       sceneObjects->at(i)->y,
                       sceneObjects->at(i)->z,
                       sceneObjects->at(i)->rotX,
                       sceneObjects->at(i)->rotY,
                       sceneObjects->at(i)->rotZ,
                       sceneObjects->at(i)->sX,
                       sceneObjects->at(i)->sY,
                       sceneObjects->at(i)->sZ,
                       sceneObjects->at(i)->r,
                       sceneObjects->at(i)->g,
                       sceneObjects->at(i)->b,
                       sceneObjects->at(i)->texture);
        }else if(sceneObjects->at(i)->model==QString("pyramid")){
            testdraw(sceneObjects->at(i)->x,
                       sceneObjects->at(i)->y,
                       sceneObjects->at(i)->z,
                       sceneObjects->at(i)->rotX,
                       sceneObjects->at(i)->rotY,
                       sceneObjects->at(i)->rotZ,
                       sceneObjects->at(i)->sX,
                       sceneObjects->at(i)->sY,
                       sceneObjects->at(i)->sZ,
                       sceneObjects->at(i)->r,
                       sceneObjects->at(i)->g,
                       sceneObjects->at(i)->b,
                       sceneObjects->at(i)->texture);
        }else if(sceneObjects->at(i)->model==QString("light")){
            drawLight(sceneObjects->at(i)->x,
                       sceneObjects->at(i)->y,
                       sceneObjects->at(i)->z,
                       sceneObjects->at(i)->rotX,
                       sceneObjects->at(i)->rotY,
                       sceneObjects->at(i)->rotZ,
                       sceneObjects->at(i)->sX,
                       sceneObjects->at(i)->sY,
                       sceneObjects->at(i)->sZ,
                       sceneObjects->at(i)->r,
                       sceneObjects->at(i)->g,
                       sceneObjects->at(i)->b,
                       sceneObjects->at(i)->texture);
        }
    }
    if(textureNumber>6) {
        testdraw(0,0,0,0,0,0,0,0,0,0,0,0,QString(""));
    }
}


void MainWidget::drawSphere(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}
void MainWidget::drawCuboid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}
void MainWidget::drawCylinder(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}
void MainWidget::drawSurface(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}
void MainWidget::drawPyramid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}
void MainWidget::drawLight(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}

void MainWidget::testdraw(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){
    qDebug() << "tutrej";
    qglColor(Qt::red);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);

    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
}
