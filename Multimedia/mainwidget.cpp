#include <qmath.h>
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent)
{

}


void MainWidget::addTexture(QString path) {
    QStringList pieces = path.split( "/" );
    QString neededWord = pieces.value( pieces.length() - 1 );
    textures[neededWord] = QString(path);
}
void MainWidget::setSceneObjects(QList<SceneObject*> *sceneObjects){
    this->sceneObjects=sceneObjects;
}

void MainWidget::initializeGL()
{
    qDebug() << "initGL";
    glClearColor( 0.74902, 0.847059, 0.62352, 1.0 );

        // czyszczenie bufora koloru i bufora głębokości
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //initialize textures
    for(int j=0; j<6; ++j) {
        textures[QString("side%1.png").arg(j + 1)]=QString(":/images/side%1.png").arg(j + 1);
    }
    textures["blue.png"]=QString(":/images/blue.png");
    textures["wall.png"]=QString(":/images/wall.png");

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
    glViewport(0, 0, 600, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-7, +7, -7, +7, 1.0, 50.0);
    gluPerspective(45,1.0,0.1,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,20,-20,0,0,0,0,1,0);
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
            drawPyramid(sceneObjects->at(i)->x,
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

    if(texture != "") {
        qDebug() << texture;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bindTexture
                      (QPixmap(textures[texture]), GL_TEXTURE_2D));
    } else {
         glDisable(GL_TEXTURE_2D);
    }
    float radius = 1.0f;
    int subdivisionsHeight = 40;
    int subdivisionsAxis = 40;
    glPushMatrix();
    glColor3f((float) r/255,  (float)g/255,  (float)b/255);
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
            glTexCoord2f((float)(j * 2 * M_PI * radius / subdivisionsAxis),
                         ((float)(i + 1) / subdivisionsHeight));

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

            glTexCoord2f(
                (float)(j * 2 * M_PI * radius / subdivisionsAxis),
                ((float)(i + 1) / subdivisionsHeight)
            );

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

            glTexCoord2f(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                ((float)i / subdivisionsHeight)
            );

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

            glTexCoord2f(
                (float)(j * 2 * M_PI * radius / subdivisionsAxis),
                (float)(i + 1) / subdivisionsHeight
            );

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

            glTexCoord2f(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                (float)(i + 1) / subdivisionsHeight
            );

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

            glTexCoord2f(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                (float)(i + 1) / subdivisionsHeight
            ));
*/
            glTexCoord2f(
                (float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis),
                (float)i / subdivisionsHeight
            );
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

            glTexCoord2f(
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

    //drawSphere(x, y, z, rotX, rotY, rotZ, sX, SY, sZ, r, g, b, texture);

    if(texture != "") {
        qDebug() << texture;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bindTexture
                      (QPixmap(textures[texture]), GL_TEXTURE_2D));
    } else {
         glDisable(GL_TEXTURE_2D);
    }

    int subdivisionsX = 2;
    int subdivisionsY = 2;
    int subdivisionsZ = 2;
    float sizeX = sX;//1.0f;
    float sizeY = sY;//1.0f;
    float sizeZ = sZ;//1.0f;
    glPushMatrix();
    glColor3f((float) r/255,  (float)g/255,  (float)b/255);
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
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (j) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                */
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f((i * sizeX / subdivisionsX), (j + 1) * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    ( j + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                */
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ);
                glVertex3f(
                    ( i + 1) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    (j) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                */
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, (j * sizeZ / subdivisionsZ));
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    ( j) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                */
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ);
                glVertex3f(
                    ( i) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    ( j + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                */
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ);
                glVertex3f(
                    ( i + 1) * sizeX / subdivisionsX,
                    0.5f * sizeY,
                    ( j + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                */
            }
        }

        for(int j = -1; j < subdivisionsZ - 1; j++)	//Bottom Face
        {
            for(int i = -1; i < subdivisionsX - 1; i++)
            {
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (j) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                */
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (j) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                */
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ);
                glVertex3f(
                    ( i) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    ( j + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                */
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (j) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                */
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (j + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                */
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    -0.5f * sizeY,
                    (j + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                */
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Front Face
        {
            for(int i = - 1; i < subdivisionsX - 1; i++)
            {
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    (j) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    (j) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    (j + 1) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f ,1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    ( j) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    (j + 1) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, 1.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    ( j + 1) * sizeY / subdivisionsY,
                    0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                */
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Back Face
        {
            for(int i = - 1; i < subdivisionsX - 1; i++)
            {
                glNormal3f(0.0f, 0.0f, -1.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    ( j) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, -1.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    (j + 1) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, -1.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    (j) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, -1.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    (j) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, -1.0f);
                glTexCoord2f(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    (i) * sizeX / subdivisionsX,
                    ( j + 1) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                */
                glNormal3f(0.0f, 0.0f, -1.0f);
                glTexCoord2f((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    (i + 1) * sizeX / subdivisionsX,
                    (j + 1) * sizeY / subdivisionsY,
                    -0.5f * sizeZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                */
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Left Face
        {
            for(int i = - 1; i < subdivisionsZ - 1; i++)
            {
                glNormal3f(-1.0f, 0.0f, 0.0f);
                glTexCoord2f(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY);
                glVertex3f(
                    -0.5f * sizeX,
                    (j) * sizeY / subdivisionsY,
                    ( i) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                */
                glNormal3f(-1.0f, 0.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY);
                glVertex3f(
                    -0.5f * sizeX,
                    (j) * sizeY / subdivisionsY,
                    (i + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                */
                glNormal3f(-1.0f, 0.0f, 0.0f);
                glTexCoord2f(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    -0.5f * sizeX,
                    (j + 1) * sizeY / subdivisionsY,
                    (i) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                */
                glNormal3f(-1.0f, 0.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY);
                glVertex3f(
                    -0.5f * sizeX,
                    (j) * sizeY / subdivisionsY,
                    (i + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                */
                glNormal3f(-1.0f, 0.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    -0.5f * sizeX,
                    (j + 1) * sizeY / subdivisionsY,
                    (i + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                */
                glNormal3f(-1.0f, 0.0f, 0.0f);
                glTexCoord2f(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    -0.5f * sizeX,
                    (j + 1) * sizeY / subdivisionsY,
                    (i) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                */
            }
        }

        for(int j = - 1; j < subdivisionsY - 1; j++)	//Right Face
        {
            for(int i = - 1; i < subdivisionsZ - 1; i++)
            {
                glNormal3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY);
                glVertex3f(
                    0.5f * sizeX,
                    (j) * sizeY / subdivisionsY,
                    (i) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                */
                glNormal3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    0.5f * sizeX,
                    (j + 1) * sizeY / subdivisionsY,
                    (i) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                */
                glNormal3f(1.0f, 0.0f ,0.0f);
                glTexCoord2f((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY);
                glVertex3f(
                    0.5f * sizeX,
                    (j) * sizeY / subdivisionsY,
                    (i + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f ,0.0f));
                */
                glNormal3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY);
                glVertex3f(
                    0.5f * sizeX,
                    (j) * sizeY / subdivisionsY,
                    (i + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                */
                glNormal3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    0.5f * sizeX,
                    (j + 1) * sizeY / subdivisionsY,
                    ( i) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                */
                glNormal3f(1.0f, 0.0f, 0.0f);
                glTexCoord2f((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY);
                glVertex3f(
                    0.5f * sizeX,
                    ( j + 1) * sizeY / subdivisionsY,
                    (i + 1) * sizeZ / subdivisionsZ
                );
                /*
                tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                */
            }
        }
        glEnd();
        glPopMatrix();
}
void MainWidget::drawCylinder(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){

    if(texture != "") {
        qDebug() << texture;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bindTexture
                      (QPixmap(textures[texture]), GL_TEXTURE_2D));
    } else {
         glDisable(GL_TEXTURE_2D);
    }

    int subdivisionsHeight = 2;
    float radius = 1.0f;
    int subdivisionsAxis = 20;
    float height = 1.0f;
    glPushMatrix();
    glColor3f((float)r/255, (float)g/255,(float) b/255);
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
                glNormal3f(cosf(j * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf(j * (2 * M_PI / subdivisionsAxis)));
                glTexCoord2f((float)(j * 2 * M_PI * radius / subdivisionsAxis), ((float)i / subdivisionsHeight));
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * ((float)(i) / subdivisionsHeight), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf(j * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf(j * (2 * M_PI / subdivisionsAxis)));
                glTexCoord2f((float)(j * 2 * M_PI * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight));
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * ((float)(i + 1) / subdivisionsHeight), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glTexCoord2f((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis), ((float)i / subdivisionsHeight));
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * ((float)(i) / subdivisionsHeight), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));

/*
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);

                bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));




*/
                glNormal3f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glTexCoord2f((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight));
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height *((float)(i + 1) / subdivisionsHeight), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glTexCoord2f((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis), ((float)i / subdivisionsHeight));
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * ((float)(i) / subdivisionsHeight), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(cosf(j * (2 * M_PI / subdivisionsAxis)), 0.0f, sinf(j * (2 * M_PI / subdivisionsAxis)));
                glTexCoord2f((float)(j * 2 * M_PI * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight));
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * ((float)(i + 1) / subdivisionsHeight), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));

/*
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
                tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);

                bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
                bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
*/



                //Top
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(cosf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f, sinf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * 0.5f, radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(0.5f, 0.5f);
                glVertex3f(0.0f, height * 0.5f, 0.0f);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * 0.5f, radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));

/*
                tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);

                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);




*/
                //Bottom
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f(cosf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f, sinf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                glVertex3f(radius * cosf(j * (2 * M_PI / subdivisionsAxis)), height * (-0.5f), radius * sinf(j * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f, sinf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);
                glVertex3f(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)), height * (-0.5f), radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
                glNormal3f(0.0f, -1.0f, 0.0f);
                glTexCoord2f(0.5f, 0.5f);
                glVertex3f(0.0f, height * (-0.5f), 0.0f);

/*
                tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
                tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);

                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
                bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);




*/
            }
        }
    glEnd();
    glPopMatrix();
}
void MainWidget::drawSurface(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){
    if(texture != "") {
        qDebug() << texture;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bindTexture
                      (QPixmap(textures[texture]), GL_TEXTURE_2D));
    } else {
         glDisable(GL_TEXTURE_2D);
    }
    glPushMatrix();
    glColor3f((float) r/255,  (float)g/255,  (float)b/255);
    glTranslatef(x,y,z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
    glScalef(sX, SY,sZ);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glTexCoord2f(-1,-1);
        glVertex3f(-1,-1,0);
        glTexCoord2f(-1,1);
        glVertex3f(-1,1,0);
        glTexCoord2f(1,1);
        glVertex3f(1,1,0);
        glTexCoord2f(1,-1);
        glVertex3f(1,-1,0);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glTexCoord2f(1,-1);
        glVertex3f(1,-1,0);
        glTexCoord2f(1,1);
        glVertex3f(1,1,0);
        glTexCoord2f(-1,1);
        glVertex3f(-1,1,0);
        glTexCoord2f(-1,-1);
        glVertex3f(-1,-1,0);
    glEnd();
    glPopMatrix();
}
void MainWidget::drawPyramid(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){
    if(texture != "") {
        qDebug() << texture;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bindTexture
                      (QPixmap(textures[texture]), GL_TEXTURE_2D));
    } else {
         glDisable(GL_TEXTURE_2D);
    }
    glPushMatrix();
    glColor3f((float) r/255,  (float)g/255,  (float)b/255);
    glTranslatef(x,y,z);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);
    glScalef(sX, SY,sZ);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glTexCoord2f(-1,-1);
        glVertex3f(-1,-1,0);
        glTexCoord2f(-1,1);
        glVertex3f(-1,1,0);
        glTexCoord2f(1,1);
        glVertex3f(1,1,0);
        glTexCoord2f(1,-1);
        glVertex3f(1,-1,0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glTexCoord2f(-1,-1);
        glVertex3f(-1,-1,0);
        glTexCoord2f(1,-1);
        glVertex3f(1,-1,0);
        glTexCoord2f(-1,1);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glTexCoord2f(1,-1);
        glVertex3f(1,-1,0);
        glTexCoord2f(1,1);
        glVertex3f(1,1,0);
        glTexCoord2f(-1,1);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glTexCoord2f(1,1);
        glVertex3f(1,1,0);
        glTexCoord2f(-1,1);
        glVertex3f(-1,1,0);
        glTexCoord2f(1,-1);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glTexCoord2f(-1,1);
        glVertex3f(-1,1,0);
        glTexCoord2f(-1,-1);
        glVertex3f(-1,-1,0);
        glTexCoord2f(1,1);
        glVertex3f(0,0,1.2);
    glEnd();
    glPopMatrix();
}
void MainWidget::drawLight(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture){
    lightPosition[0] = x;
    lightPosition[1] = y;
    lightPosition[2] = z;
    lightPosition[3] = 1;
    ambient[0] = (float) r/255 * rotX/100;
    ambient[1] = (float) g/255 * rotX/100;
    ambient[2] = (float) b/255 * rotX/100;
    ambient[3] = 1.0;
    qDebug() << ambient[3];
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable( GL_COLOR_MATERIAL );
}

void MainWidget::moveCameraForvard() {
    qDebug() << "forvard move";
}

void MainWidget::moveCameraBack() {
    qDebug()<< "back move";
}

void MainWidget::moveCameraLeft() {
    qDebug()<< "left move";
}

void MainWidget::moveCameraRight() {
    qDebug()<< "right move";
}

void MainWidget::moveCameraUp() {
    qDebug()<< "up move";
}

void MainWidget::moveCameraDown() {
    qDebug()<< "down move";
}

void MainWidget::rotateCameraX() {
    qDebug()<< "rotX";
}
void MainWidget::rotateCameraY() {
    qDebug()<< "rotY";
}

void MainWidget::mousePressEvent ( QMouseEvent * event ){
    printf("\nMouse in board");
    setFocus();
}
