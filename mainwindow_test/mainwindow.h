#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     void Menupart();
     void Toolpart();
     void Centralpart();
     void Dockpart();
     void Statuspart();

private slots:
    void on_widget_windowIconChanged(const QIcon &icon);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
