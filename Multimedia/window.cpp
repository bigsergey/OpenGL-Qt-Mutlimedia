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
            List << QString("Light");
            SceneObject* light=new SceneObject();
            light->x=0;
            light->y=0;
            light->z=0;
            light->rotX=0;
            light->rotY=0;
            light->rotZ=0;
            light->sX=0;
            light->sY=0;
            light->sZ=0;
            light->r=0;
            light->g=0;
            light->b=0;
            light->model = QString("light");
            light->texture=QString();
        sceneObjects.append(light);
        model->setStringList(List);

        ui->listView->setModel(model);
        ui->listView->
                setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                QAbstractItemView::DoubleClicked);

        connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this, SLOT(onListViewItemClicked(QItemSelection)));
        connect(ui->addButton, SIGNAL(released()), this, SLOT(onAddButtonClicked()));
        connect(ui->deleteButton, SIGNAL(released()), this, SLOT(onDeleteButtonClicked()));
        connect(ui->xPosSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
        connect(ui->yPosSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
        connect(ui->zPosSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setZ(int)));

}


void Window::onListViewItemClicked( const QItemSelection & selection)
{

    //ui->widget->updateGL();
    activeObject = sceneObjects.at(selection.indexes().at(0).row());
    ui->xPosSpinBox->setValue(activeObject->x);
    ui->yPosSpinBox->setValue(activeObject->y);
    ui->zPosSpinBox->setValue(activeObject->z);
    ui->xRotSpinBox->setValue(activeObject->rotX);
    ui->yRotSpinBox->setValue(activeObject->rotY);
    ui->zRotSpinBox->setValue(activeObject->rotZ);
    ui->xScaleSpinBox->setValue(activeObject->sX);
    ui->yScaleSpinBox->setValue(activeObject->sY);
    ui->zScaleSpinBox->setValue(activeObject->sZ);
    ui->rSpinBox->setValue(activeObject->r);
    ui->gSpinBox->setValue(activeObject->g);
    ui->bSpinBox->setValue(activeObject->b);
    if(ui->modelComboBox->findText(activeObject->model)>=0)ui->modelComboBox->setCurrentIndex(ui->modelComboBox->findText(activeObject->model));
    if(ui->textureComboBox->findText(activeObject->texture)>=0)ui->textureComboBox->setCurrentIndex(ui->textureComboBox->findText(activeObject->texture));


}

void Window::onAddButtonClicked(){
        int row = model->rowCount();
        model->insertRow(row);
        QModelIndex index = model->index(row);
        model->setData(index, "Empty Object");
        SceneObject* sceneObject=new SceneObject();
        sceneObject->x=0;
        sceneObject->y=0;
        sceneObject->z=0;
        sceneObject->rotX=0;
        sceneObject->rotY=0;
        sceneObject->rotZ=0;
        sceneObject->sX=0;
        sceneObject->sY=0;
        sceneObject->sZ=0;
        sceneObject->r=0;
        sceneObject->g=0;
        sceneObject->b=0;
        sceneObjects.append(sceneObject);
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
    if(ui->listView->currentIndex().row()){
        sceneObjects.removeAt(ui->listView->currentIndex().row());
        model->removeRow(ui->listView->currentIndex().row());
    }
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

void Window::setX(int x) {
    qDebug() << x;
    this->activeObject->x = x;
}

void Window::setY(int y) {
    this->activeObject->y = y;
}

void Window::setZ(int z) {
    this->activeObject->z = z;
}

void Window::setRotX(int rotX) {
    this->activeObject->rotX = rotX;
}

void Window::setRotY(int rotY) {
    this->activeObject->rotY = rotY;
}

void Window::setRotZ(int rotZ) {
    this->activeObject->rotZ = rotZ;
}

void Window::setSX(int sX) {
    this->activeObject->sX = sX;
}

void Window::setSY(int sY) {
    this->activeObject->sY= sY;
}

void Window::setSZ(int sZ) {
    this->activeObject->sZ = sZ;
}

void Window::setR(int r) {
    this->activeObject->r = r;
}

void Window::setG(int g) {
    this->activeObject->g = g;
}

void Window::setB(int b) {
    this->activeObject->b = b;
}

void Window::setModel(QString model) {
    this->activeObject->model = model;
}

void Window::setTexture(QString texture) {
    this->activeObject->texture = texture;
}
