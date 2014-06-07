#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

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

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
