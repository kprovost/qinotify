#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    /* Argument parsing */
    QStringList args = app.arguments();
    QString appName = args.at(0);
    args.removeAt(0);

    QString file;
    if (args.size() == 1)
    {
       file = args.at(0);
    }

    if (file.isEmpty())
    {
        std::cerr << "Usage: " << appName.toStdString() << " <file>" << std::endl;
        return 1;
    }

    /* Go! */
    mainWindow.loadFile(file);

    return app.exec();
}
