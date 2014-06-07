#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QGLWidget>

class MainWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void draw();


signals:

public slots:

};

#endif // MAINWIDGET_H
