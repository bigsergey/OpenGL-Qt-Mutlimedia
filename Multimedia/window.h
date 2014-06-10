#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QStringListModel>
#include "sceneobject.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    SceneObject *activeObject;

private slots:
    void on_aboutButton_clicked();

    void on_addTextureButton_clicked();
    void onListViewItemClicked( const QItemSelection & selection);
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void setX(double);
    void setY(double);
    void setZ(double);
    void addX(double);
    void addY(double);
    void addZ(double);
    void setRotX(int);
    void setRotY(int);
    void setRotZ(int);
    void setSX(double);
    void setSY(double);
    void setSZ(double);
    void setR(int);
    void setG(int);
    void setB(int);
    void setModel(QString);
    void setTexture(QString);
//    void keyReleaseEvent(QKeyEvent *event);
//    void keyPressEvent(QKeyEvent *event);


private:
    Ui::Window *ui;
    QList<SceneObject*> sceneObjects;
    QStringListModel *model;
    int timerId;
    int moveX, moveY, moveZ;
    int MOVE;

protected:
//    void timerEvent(QTimerEvent *event);

};


#endif // WINDOW_H
