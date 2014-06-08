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
    void setX(int);
    void setY(int);
    void setZ(int);
    void addX(int);
    void addY(int);
    void addZ(int);
    void setRotX(int);
    void setRotY(int);
    void setRotZ(int);
    void setSX(int);
    void setSY(int);
    void setSZ(int);
    void setR(int);
    void setG(int);
    void setB(int);
    void setModel(QString);
    void setTexture(QString);
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::Window *ui;
    QList<SceneObject*> sceneObjects;
    QStringListModel *model;
    int timerId;
    int moveX, moveY, moveZ;
    int MOVE;

protected:
    void timerEvent(QTimerEvent *event);

};


#endif // WINDOW_H
