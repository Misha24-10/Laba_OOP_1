#include <QCoreApplication>
#include "test.h"
#include "tablecellfunction.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    testTablecell();

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Laba Table");
    w.show();
    return a.exec();
}
