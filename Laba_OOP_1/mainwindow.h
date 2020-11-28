#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tablecollection.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_create_table_clicked();


    void on_pushButton_2_clicked();

    void on_save_2_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    TableCollection *Table_;

};
#endif // MAINWINDOW_H
