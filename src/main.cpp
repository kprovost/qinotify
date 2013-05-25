#include "mainwindow.h"
#include "inotifier.h"
#include "compiler.h"
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

    /* Monitor the file for changes */
    INotifier notifier;
    if (! notifier.monitor(file))
    {
        std::cerr << "Unable to monitor file " << file.toStdString()
            << " for changes." << std::endl;
        return 1;
    }
    notifier.start();

    /* Process files before viewing */
    Compiler c;

    QObject::connect(&notifier, SIGNAL(fileChange(const QString&)),
            &c, SLOT(fileChange(const QString&)));

    /* Update the view whenever the file changes */
    QObject::connect(&c, SIGNAL(loadFile(const QString&)),
            &mainWindow, SLOT(loadFile(const QString&)));

    /* Go! */
    return app.exec();
}
