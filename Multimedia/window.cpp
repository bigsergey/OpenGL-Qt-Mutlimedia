#include "window.h"
#include "ui_window.h"
#include "mainwidget.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
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

void Window::on_addTextureButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
   if (fileName.isEmpty()) {
       return;
   } else {
       qDebug() << fileName;
       //MainWidget->addTexture(fileName);
   }
}
