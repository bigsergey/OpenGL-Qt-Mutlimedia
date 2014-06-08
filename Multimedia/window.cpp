#include "window.h"
#include "ui_window.h"
#include "mainwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    // Create model
        model = new QStringListModel(this);

        QStringList List;
//        QString objects[]={"Sphere","Surface", "Pyramide", "Cuboid", "Cylinder"};
//        for(int i=0; i<5; i++) {
//            List << objects[i];
//            sceneObjects.append(new SceneObject(objects[i]));
//        }
        model->setStringList(List);
        ui->listView->setModel(model);
        ui->listView->
                setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                QAbstractItemView::DoubleClicked);

        connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this, SLOT(onListViewItemClicked(QItemSelection)));
        connect(ui->addButton, SIGNAL(released()), this, SLOT(onAddButtonClicked()));
        connect(ui->deleteButton, SIGNAL(released()), this, SLOT(onDeleteButtonClicked()));


}


void Window::onListViewItemClicked( const QItemSelection & selection)
{
    ui->widget->draw();
    sceneObjects.at(selection.indexes().at(0).row())->doSomething(this);
}

void Window::onAddButtonClicked(){
        int row = model->rowCount();
        model->insertRow(row);
        QModelIndex index = model->index(row);
        model->setData(index, "Empty Object");
        sceneObjects.append(new SceneObject());
        ui->listView->edit(index);
}

Window::~Window()
{
    delete ui;
}

void Window::on_aboutButton_clicked()
{
    QMessageBox::information(
        this,
        tr("About"),
        tr("Authors: Sergey Bolshov, Dawid Jewko, Łukasz Pawluczuk, Adam Beczyński")
       );
}

void Window::onDeleteButtonClicked(){
    model->removeRows(ui->listView->currentIndex().row(),1);
    sceneObjects.removeAt(ui->listView->currentIndex().row());
}
void Window::on_addTextureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
   if (fileName.isEmpty()) {
       return;
   } else {
       ui->widget->addTexture(fileName);
   }
}


