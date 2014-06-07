#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#define END(array) (array + sizeof(array)/sizeof(array[0]))

#include <QGLWidget>
#include <QString>

class MainWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    GLuint textures[100];
    int textureNumber = 6;

private:
    void draw();

signals:
    void texturePathChanged(QString);

public slots:
    void addTexture(QString);

};

#endif // MAINWIDGET_H
