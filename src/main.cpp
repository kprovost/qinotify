#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    mainWindow.loadFile("http://www.google.be");

    return app.exec();
}
