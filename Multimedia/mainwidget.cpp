#include <qmath.h>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent)
{

}


void MainWidget::addTexture(QString path) {
    QStringList pieces = path.split( "/" );
    QString neededWord = pieces.value( pieces.length() - 1 );
    textures[neededWord] = bindTexture
        (QPixmap(QString(path)), GL_TEXTURE_2D);
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

    static GLfloat lightPosition[4] = { 0, 0, 10, 0.5 };
    float ambient[4] = {0.5, 0.5, 0.5, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    //initialize textures
    for(int j=0; j<6; ++j) {
        textures[QString("side%1.png").arg(j + 1)]=bindTexture
                (QPixmap(QString(":/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }
    textures["wall.jpg"]=bindTexture
            (QPixmap(QString(":/images/wall.jpg")), GL_TEXTURE_2D);
    textures["blue.png"]=bindTexture
            (QPixmap(QString(":/images/blue.png")), GL_TEXTURE_2D);


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
    qDebug() << (width - side) / 2;
    qDebug() << (height - side) / 2;
    qDebug() << side;

    glViewport(0, 0, 600, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-7, +7, -7, +7, 1.0, 50.0);
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

}


void MainWidget::drawSphere(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

    float radius = 1.0f;
    int subdivisionsHeight = 40;
    int subdivisionsAxis = 40;
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
    glScalef(sX, SY,sZ);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < subdivisionsHeight; i++)
    {
        for(int j = 0; j < subdivisionsAxis; j++)
        {
            //
            glVertex3f(
                radius * sinf(i * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis),
                radius * sinf(i * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis),
                radius * cosf(i * (M_PI / subdivisionsHeight))
            );
            //vertices->push_back(1.0f);

            glNormal3f(
                sinf(i * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis),
                sinf(i * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis),
                cosf(i * (M_PI / subdivisionsHeight))
            );
/*
            tangents->push_back(glm::vec3(
                sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * cosf(j * 2 * M_PI / subdivisionsAxis)),
                sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * sinf(j * 2 * M_PI / subdivisionsAxis)),
                cosf((i + 0.5f) * (M_PI / subdivisionsHeight))
            ));

            bitangents->push_back(glm::vec3(
                sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * M_PI / subdivisionsAxis),
                sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * M_PI / subdivisionsAxis),
                cosf(i * (M_PI / subdivisionsHeight))
            ));

            texCoords->push_back(glm::vec2(
                (float)(j * 2 * M_PI * radius / subdivisionsAxis),
                (float)i / subdivisionsHeight
                ));
*/
            glVertex3f(
                radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis),
                radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis),
                radius * cosf((i + 1) * (M_PI / subdivisionsHeight))
            );

            glNormal3f(
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis),
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis),
                cosf((i + 1) * (M_PI / subdivisionsHeight))
            );
/*
            tangents->push_back(glm::vec3(
                sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * cosf(j * 2 * M_PI / subdivisionsAxis)),
                sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * sinf(j * 2 * M_PI / subdivisionsAxis)),
                cosf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight))
            ));

            bitangents->push_back(glm::vec3(
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * M_PI / subdivisionsAxis),
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * M_PI / subdivisionsAxis),
                cosf((i + 1) * (M_PI / subdivisionsHeight))
            ));

            texCoords->push_back(glm::vec2(
                (float)(j * 2 * M_PI * radius / subdivisionsAxis),
                ((float)(i + 1) / subdivisionsHeight)
            ));
*/
            glVertex3f(
                radius * sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis),
                radius * sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis),
                radius * cosf(i * (M_PI / subdivisionsHeight))
            );

            glNormal3f(
                sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis),
                sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis),
                cosf(i * (M_PI / subdivisionsHeight))
            );
/*
            tangents->push_back(glm::vec3(
                sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis)),
                sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis)),
                cosf((i + 0.5f) * (M_PI / subdivisionsHeight))
            ));

            bitangents->push_back(glm::vec3(
                sinf(i * (M_PI / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis),
                sinf(i * (M_PI / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis),
                cosf(i * (M_PI / subdivisionsHeight))
            ));

            texCoords->push_back(glm::vec2(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                ((float)i / subdivisionsHeight)
            ));
*/
            //
            glVertex3f(
                radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis),
                radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis),
                radius * cosf((i + 1) * (M_PI / subdivisionsHeight))
            );

            glNormal3f(
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis),
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis),
                cosf((i + 1) * (M_PI / subdivisionsHeight))
            );
/*
            tangents->push_back(glm::vec3(
                sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * cosf(j * 2 * M_PI / subdivisionsAxis)),
                sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * sinf(j * 2 * M_PI / subdivisionsAxis)),
                cosf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight))
            ));

            bitangents->push_back(glm::vec3(
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * M_PI / subdivisionsAxis),
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * M_PI / subdivisionsAxis),
                cosf((i + 1) * (M_PI / subdivisionsHeight))
            ));

            texCoords->push_back(glm::vec2(
                (float)(j * 2 * M_PI * radius / subdivisionsAxis),
                (float)(i + 1) / subdivisionsHeight
            ));
*/
            glVertex3f(
                radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis),
                radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis),
                radius * cosf((i + 1) * (M_PI / subdivisionsHeight))
            );

            glNormal3f(
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis),
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis),
                cosf((i + 1) * (M_PI / subdivisionsHeight))
            );
/*
            tangents->push_back(glm::vec3(
                sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis)),
                sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis)),
                cosf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight))
            ));

            bitangents->push_back(glm::vec3(
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis),
                sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis),
                cosf((i + 1) * (M_PI / subdivisionsHeight))
            ));

            texCoords->push_back(glm::vec2(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                (float)(i + 1) / subdivisionsHeight
            ));
*/
            glVertex3f(
                radius * sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis),
                radius * sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis),
                radius * cosf(i * (M_PI / subdivisionsHeight))
            );

            glNormal3f(
                sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis),
                sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis),
                cosf(i * (M_PI / subdivisionsHeight))
            );
/*
            tangents->push_back(glm::vec3(
                sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis)),
                sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis)),
                cosf((i + 0.5f) * (M_PI / subdivisionsHeight))
            ));

            bitangents->push_back(glm::vec3(
                sinf(i * (M_PI / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis),
                sinf(i * (M_PI / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis),
                cosf(i * (M_PI / subdivisionsHeight))
            ));

            texCoords->push_back(glm::vec2(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                (float)i / subdivisionsHeight
            ));
*/
         }
    }
    glEnd();
    glPopMatrix();
}
void MainWidget::drawCuboid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int sY, int sZ, int r, int g, int b, QString texture){

    //frontFace
/*
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, -0.5, -0.5);
        glNormal3f(0,0,-1.0);
        glVertex3f(-0.5, 0.5, -0.5);
        glNormal3f(0,0,-1.0);
        glVertex3f(0.5, 0.5, -0.5);
        glNormal3f(0,0,-1.0);

        glVertex3f(0.5, 0.5, -0.5);
        glNormal3f(0,0,-1.0);
        glVertex3f(0.5, -0.5, -0.5);
        glNormal3f(0,0,-1.0);
        glVertex3f(-0.5, -0.5, -0.5);
        glNormal3f(0,0,-1.0);
    //glEnd();
    //backFace
    //glBegin(GL_QUADS);
       /*
        glNormal3f(0,0,1.0f);
        glVertex3f(-0.5f, -0.5f, -1.5f);
        glNormal3f(0,0,1.0f);
        glVertex3f(-0.5f, 0.5f, -1.5f);
        glNormal3f(0,0,1.0f);
        glVertex3f(0.5f, 0.5f, -1.5f);
        glNormal3f(0,0,1.0f);
        glVertex3f(0.5f, -0.5f, -1.5f);
    //glEnd();
    //leftFace
    //glBegin(GL_QUADS);
        glNormal3f(-1.0f,0,0);
        glVertex3f(-0.5f, -0.5f, -1.5f);
        glNormal3f(-1.0f,0,0);
        glVertex3f(-0.5f, 0.5f, -1.5f);
        glNormal3f(-1.0f,0,0);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glNormal3f(-1.0f,0,0);
        glVertex3f(-0.5f, -0.5f, -0.5f);
    //glEnd();
    //rightFace
    //glBegin(GL_QUADS);
        glNormal3f(1.0f,0,0);
        glVertex3f(0.5f, -0.5f, -1.5f);
        glNormal3f(1.0f,0,0);
        glVertex3f(0.5f, 0.5f, -1.5f);
        glNormal3f(1.0f,0,0);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glNormal3f(1.0f,0,0);
        glVertex3f(0.5f, -0.5f, -0.5f);
    //glEnd();
    //topFace
    //glBegin(GL_QUADS);
        glNormal3f(0.0f,1.0f,0);
        glVertex3f(0.5f, 0.5f, -1.5f);
        glNormal3f(0.0f,1.0f,0);
        glVertex3f(-0.5f, 0.5f, -1.5f);
        glNormal3f(0.0f,1.0f,0);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glNormal3f(0.0f,1.0f,0);
        glVertex3f(0.5f, 0.5f, -0.5f);
    //glEnd();
    //bottomFace
    //glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f,0);
        glVertex3f(0.5f, -0.5f, -1.5f);
        glNormal3f(0.0f, -1.0f,0);
        glVertex3f(-0.5f, -0.5f, -1.5f);
        glNormal3f(0.0f, -1.0f,0);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glNormal3f(0.0f, -1.0f,0);
        glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();


    /*
    glBegin(GL_TRIANGLES);
        glNormal3f(0,0,1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        //glVertex3f(1,-1,0);
    */
    //glEnd();

    //drawSphere(x, y, z, rotX, rotY, rotZ, sX, SY, sZ, r, g, b, texture);

    int subdivisionsX = 2;
    int subdivisionsY = 2;
    int subdivisionsZ = 2;
    float sizeX = sX;//1.0f;
    float sizeY = sY;//1.0f;
    float sizeZ = sZ;//1.0f;
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
    glScalef(sX, sY,sZ);
    glBegin(GL_TRIANGLES);
    for(int j = -1; j < subdivisionsZ - 1; j++)	//Top Face
        {
            for(int i = -1; i < subdivisionsX - 1; i++)
            {
                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (-0.5f + j) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, 1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (-0.5f + j + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, 1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                texCoords->push_back(glm::vec2((i * sizeX / subdivisionsX), (j + 1) * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (-0.5f + j) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, 1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (-0.5f + j) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, 1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j * sizeZ / subdivisionsZ)));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (-0.5f + j + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, 1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (-0.5f + j + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, 1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));*/
            }
        }

        for(int j = -1; j < subdivisionsZ - 1; j++)	//Bottom Face
        {
            for(int i = -1; i < subdivisionsX - 1; i++)
            {
                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (-0.5f + j) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, -1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (-0.5f + j) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, -1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (-0.5f + j + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, -1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (-0.5f + j) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, -1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (-0.5f + j + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, -1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (-0.5f + j + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(0.0f, -1.0f, 0.0f);/*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));*/
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Front Face
        {
            for(int i = - 1; i < subdivisionsX - 1; i++)
            {
                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, 1.0f);/*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, 1.0f);/*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, 1.0f);/*
                tangents->push_back(glm::vec3(0.0f ,1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, 1.0f);/*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, 1.0f);/*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, 1.0f);/*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));*/
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Back Face
        {
            for(int i = - 1; i < subdivisionsX - 1; i++)
            {
                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, -1.0f);/*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, -1.0f);/*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, -1.0f);/*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, -1.0f);/*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i) * sizeX / subdivisionsX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, -1.0f);/*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    (-0.5f + i + 1) * sizeX / subdivisionsX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                glNormal3f(0.0f, 0.0f, -1.0f);/*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));*/
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Left Face
        {
            for(int i = - 1; i < subdivisionsZ - 1; i++)
            {
                glVertex3f(
                    -0.5f * sizeX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    (-0.5f + i) * sizeZ / subdivisionsZ
                );
                glNormal3f(-1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    -0.5f * sizeX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    (-0.5f + i + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(-1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    -0.5f * sizeX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    (-0.5f + i) * sizeZ / subdivisionsZ
                );
                glNormal3f(-1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    -0.5f * sizeX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    (-0.5f + i + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(-1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    -0.5f * sizeX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    (-0.5f + i + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(-1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    -0.5f * sizeX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    (-0.5f + i) * sizeZ / subdivisionsZ
                );
                glNormal3f(-1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));*/
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Right Face
        {
            for(int i = - 1; i < subdivisionsZ - 1; i++)
            {
                glVertex3f(
                    0.5f * sizeX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    (-0.5f + i) * sizeZ / subdivisionsZ
                );
                glNormal3f(1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    0.5f * sizeX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    (-0.5f + i) * sizeZ / subdivisionsZ
                );
                glNormal3f(1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    0.5f * sizeX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    (-0.5f + i + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(1.0f, 0.0f ,0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f ,0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    0.5f * sizeX,
                    (-0.5f + j) * sizeY / subdivisionsY,
                    (-0.5f + i + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));*/

                glVertex3f(
                    0.5f * sizeX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    (-0.5f + i) * sizeZ / subdivisionsZ
                );
                glNormal3f(1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));*/

                glVertex3f(
                    0.5f * sizeX,
                    (-0.5f + j + 1) * sizeY / subdivisionsY,
                    (-0.5f + i + 1) * sizeZ / subdivisionsZ
                );
                glNormal3f(1.0f, 0.0f, 0.0f);/*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));*/
            }
        }
        glEnd();
        glPopMatrix();
}
void MainWidget::drawCylinder(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

    int subdivisionsHeight = 2;
    float radius = 1.0f;
    int subdivisionsAxis = 20;
    float height = 1.0f;
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
    glScalef(sX, SY,sZ);
    glBegin(GL_TRIANGLES);
    for(int i = -1; i < subdivisionsHeight - 1; i++)	//Tangents bitangents fix for sides
        {
            for(int j = -1; j < subdivisionsAxis - 1; j++)
            {
                //Side

                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * ((-0.5f + i) / subdivisionsHeight), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf(j * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf(j * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * ((-0.5f + i + 1) / subdivisionsHeight), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf(j * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf(j * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * ((-0.5f + i) / subdivisionsHeight), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
/*
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);

                bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));

                texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
                texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
                texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
*/
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), ((-0.5f + i + 1) / subdivisionsHeight), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * ((-0.5f + i) / subdivisionsHeight), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * ((-0.5f + i + 1) / subdivisionsHeight), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));

                glNormal3f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf(j * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf(j * (2 * M_PI / subdivisionsAxis)));
/*
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);

                bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));

                texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
                texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
                texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
*/
                //Top
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * 0.5f, radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(0.0f, height * 0.5f, 0.0f);
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * 0.5f, radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));

                glNormal3f(0.0f, 1.0f, 0.0f);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glNormal3f(0.0f, 1.0f, 0.0f);
/*
                tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);

                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);

                texCoords->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                texCoords->push_back(0.5f);texCoords->push_back(0.5f);
                texCoords->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);
*/
                //Bottom
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * (-0.5f), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * (-0.5f), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glVertex3f(0.0f, height * (-0.5f), 0.0f);

                glNormal3f(0.0f, -1.0f, 0.0f);
                glNormal3f(0.0f, -1.0f, 0.0f);
                glNormal3f(0.0f, -1.0f, 0.0f);
/*
                tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);

                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);

                texCoords->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                texCoords->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                texCoords->push_back(0.5f);texCoords->push_back(0.5f);
*/
            }
        }
    glEnd();
    glPopMatrix();
}
void MainWidget::drawSurface(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){
}
void MainWidget::drawPyramid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}
void MainWidget::drawLight(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

}

void MainWidget::testdraw(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

    glPushMatrix();
    qglColor(Qt::red);
    glTranslatef(x,y,z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
    glScalef(sX, SY,sZ);
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
    glPopMatrix();
}
