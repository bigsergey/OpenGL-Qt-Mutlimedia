#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QDebug>
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


private slots:
    void on_aboutButton_clicked();

    void on_addTextureButton_clicked();
    void onListViewItemClicked( const QItemSelection & selection);
    void onAddButtonClicked();
    void onDeleteButtonClicked();

    void on_addButton_clicked();

private:
    Ui::Window *ui;
    QList<SceneObject*> sceneObjects;
    QStringListModel *model;
};

#endif // WINDOW_H
