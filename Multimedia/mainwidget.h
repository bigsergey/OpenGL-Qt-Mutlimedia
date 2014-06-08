#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#define END(array) (array + sizeof(array)/sizeof(array[0]))

#include <QGLWidget>
#include <QString>
#include <QDebug>

class MainWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void draw();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    QMap <QString, GLuint> textures;

private:

    void testdraw(int x, int y, int z, int rotX, int rotY, int rotZ, int sX, int SY, int sZ, int r, int g, int b, QString texture);


signals:
    void texturePathChanged(QString);

public slots:
    void addTexture(QString);

};

#endif // MAINWIDGET_H
