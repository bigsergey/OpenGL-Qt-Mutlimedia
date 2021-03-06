#include "window.h"
#include "ui_window.h"
#include "mainwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->widget->setSceneObjects(&sceneObjects);
    //init comboBox with models
    ui->modelComboBox->addItem((QString) "surface");
    ui->modelComboBox->addItem((QString) "cuboid");
    ui->modelComboBox->addItem((QString) "cylinder");
    ui->modelComboBox->addItem((QString) "pyramid");
    ui->modelComboBox->addItem((QString) "sphere");

   // timerId = startTimer(300);
    MOVE = 1;
    moveX = 0;
    moveY = 0;
    moveZ = 0;

    //init combobox with textures
    QStringList textures;
    textures << "side1.png" << "side2.png" << "side3.png" << "side4.png" << "side5.png" << "side6.png" << "wall.png" << "blue.png";
    ui->textureComboBox->addItems(textures);

    // Create model
        model = new QStringListModel(this);


        QStringList List;
            List << QString("Light");
            SceneObject* light=new SceneObject();
            light->x=20;
            light->y=20;
            light->z=10;
            light->rotX=50;
            light->rotY=0;
            light->rotZ=0;
            light->sX=0;
            light->sY=0;
            light->sZ=0;
            light->r=180;
            light->g=180;
            light->b=180;
            light->model = QString("light");
            light->texture=QString();
        sceneObjects.append(light);
        model->setStringList(List);

        ui->listView->setModel(model);
        activeObject = sceneObjects.at(0);
        ui->listView->setCurrentIndex(ui->listView->indexAt(QPoint(0,0)));
        ui->listView->
                setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                QAbstractItemView::DoubleClicked);

        connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this, SLOT(onListViewItemClicked(QItemSelection)));
        connect(ui->addButton, SIGNAL(released()), this, SLOT(onAddButtonClicked()));
        connect(ui->deleteButton, SIGNAL(released()), this, SLOT(onDeleteButtonClicked()));
        connect(ui->xPosSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setX(double)));
        connect(ui->yPosSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setY(double)));
        connect(ui->zPosSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setZ(double)));
        connect(ui->xRotSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setRotX(int)));
        connect(ui->intensitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(setRotX(int)));
        connect(ui->yRotSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setRotY(int)));
        connect(ui->zRotSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setRotZ(int)));
        connect(ui->xScaleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setSX(double)));
        connect(ui->yScaleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setSY(double)));
        connect(ui->zScaleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setSZ(double)));
        connect(ui->rSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setR(int)));
        connect(ui->gSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setG(int)));
        connect(ui->bSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setB(int)));
        connect(ui->modelComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setModel(QString)));
        connect(ui->textureComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setTexture(QString)));
        ui->modelComboBox->hide();
        ui->textureComboBox->hide();
        ui->modelLabel->hide();
        ui->textureLabel->hide();
        ui->rotationGroupBox->hide();
        ui->scaleGroupBox->hide();
}


void Window::onListViewItemClicked( const QItemSelection & selection)
{


    //ui->widget->updateGL();
    activeObject = sceneObjects.at(selection.indexes().at(0).row());
    if(activeObject->model == "light") {
        ui->modelComboBox->hide();
        ui->textureComboBox->hide();
        ui->modelLabel->hide();
        ui->textureLabel->hide();
        ui->rotationGroupBox->hide();
        ui->scaleGroupBox->hide();
        ui->intensityLabel->show();
        ui->intensitySpinBox->show();
    } else {
        ui->modelComboBox->show();
        ui->textureComboBox->show();
        ui->modelLabel->show();
        ui->textureLabel->show();
        ui->rotationGroupBox->show();
        ui->scaleGroupBox->show();\
        ui->intensityLabel->hide();
        ui->intensitySpinBox->hide();
    }
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
    if(activeObject->model != "light") {
        ui->modelComboBox->setCurrentIndex(ui->modelComboBox->findText(activeObject->model));
        ui->textureComboBox->setCurrentIndex(ui->textureComboBox->findText(activeObject->texture));
    } else {
        //rotX jest wykorzystywany zamiast intensywnosci
        ui->intensitySpinBox->setValue(activeObject->rotX);
    }



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
        sceneObject->sX=1;
        sceneObject->sY=1;
        sceneObject->sZ=1;
        sceneObject->r=125;
        sceneObject->g=125;
        sceneObject->b=125;
        sceneObjects.append(sceneObject);
        ui->listView->edit(index);
}

Window::~Window()
{
    //killTimer(timerId);
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

        int index = ui->listView->currentIndex().row();
        ui->listView->reset();
        model->removeRow(index);
        ui->listView->setModel(model);
        activeObject = sceneObjects.at(0);
        ui->listView->setCurrentIndex(ui->listView->indexAt(QPoint(0,0)));
    }
}
void Window::on_addTextureButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
   QStringList pieces = fileName.split( "/" );
   QString neededWord = pieces.value( pieces.length() - 1 );
   qDebug() <<neededWord;
   if (fileName.isEmpty()) {
       return;
   } else {
       ui->textureComboBox->addItem(neededWord);
       ui->widget->addTexture(fileName);
   }
}

void Window::setX(double x) {
    this->activeObject->x = x;
    ui->widget->updateGL();
}

void Window::setY(double y) {
    this->activeObject->y = y;
    ui->widget->updateGL();
}

void Window::setZ(double z) {
    this->activeObject->z = z;
    ui->widget->updateGL();
}

void Window::addX(double x) {
    this->activeObject->x = this->activeObject->x + x;
    ui->xPosSpinBox->setValue(ui->xPosSpinBox->value() + x);
}

void Window::addY(double y) {
    this->activeObject->y = this->activeObject->y + y;
    ui->yPosSpinBox->setValue(ui->yPosSpinBox->value() + y);
}

void Window::addZ(double z) {
    this->activeObject->z = this->activeObject->z + z;
    ui->zPosSpinBox->setValue(ui->zPosSpinBox->value() + z);
}

void Window::setRotX(int rotX) {
    this->activeObject->rotX = rotX;
    ui->widget->updateGL();
}

void Window::setRotY(int rotY) {
    this->activeObject->rotY = rotY;
    ui->widget->updateGL();
}

void Window::setRotZ(int rotZ) {
    this->activeObject->rotZ = rotZ;
    ui->widget->updateGL();
}

void Window::setSX(double sX) {
    this->activeObject->sX = sX;
    ui->widget->updateGL();
}

void Window::setSY(double sY) {
    this->activeObject->sY= sY;
    ui->widget->updateGL();
}

void Window::setSZ(double sZ) {
    this->activeObject->sZ = sZ;
    ui->widget->updateGL();
}

void Window::setR(int r) {
    this->activeObject->r = r;
    ui->widget->updateGL();
}

void Window::setG(int g) {
    this->activeObject->g = g;
    ui->widget->updateGL();
}

void Window::setB(int b) {
    this->activeObject->b = b;
    ui->widget->updateGL();
}

void Window::setModel(QString model) {
    this->activeObject->model = model;
    ui->widget->updateGL();
}

void Window::setTexture(QString texture) {
    this->activeObject->texture = texture;
    ui->widget->updateGL();
}

//void Window::timerEvent(QTimerEvent *event)
//{
//    if(moveX != 0)
//    {
//        qDebug() << "MoveX" << moveX;
//        addX(moveX);
//    }
//    if(moveY != 0)
//    {
//        qDebug() << "MoveY" << moveY;
//        addY(moveY);
//    }
//    if(moveZ != 0)
//    {
//        qDebug() << "MoveZ" << moveZ;
//        addZ(moveZ);
//    }

//    // tutaj w kółko ustawiam focus na widget, bo gubił nie wiem dlaczego. Wiem, że to raczej nie dobre rozwiazanie
//    ui->widget->setFocus();
//    ui->widget->updateGL();
//}

void Window::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_Space:
        ui->widget->moveCameraUp();
        break;
    case Qt::Key_C:
        ui->widget->moveCameraDown();
        break;
    case Qt::Key_A:
        ui->widget->moveCameraLeft();
        break;
    case Qt::Key_D:
        ui->widget->moveCameraRight();
        break;
    case Qt::Key_W:
        ui->widget->moveCameraForvard();
        break;
    case Qt::Key_S:
        ui->widget->moveCameraBack();
        break;
    case Qt::Key_Up:
        ui->widget->rotateCameraUp();
        break;
    case Qt::Key_Down:
        ui->widget->rotateCameraDown();
        break;
    case Qt::Key_Left:
        ui->widget->rotateCameraLeft();
        break;
    case Qt::Key_Right:
        ui->widget->rotateCameraRight();
        break;
    }

}

//void Window::keyReleaseEvent(QKeyEvent *event) {

//    switch (event->key()) {
//    case Qt::Key_R:
//        moveZ = 0;
//        break;
//    case Qt::Key_F:
//        moveZ = 0;
//        break;
//    case Qt::Key_A:
//        moveX = 0;
//        break;
//    case Qt::Key_D:
//        moveX = 0;
//        break;
//    case Qt::Key_W:
//        moveY = 0;
//        break;
//    case Qt::Key_S:
//        moveY = 0;
//        break;
//    }
//}
