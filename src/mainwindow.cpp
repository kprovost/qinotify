#include "mainwindow.h"
#include "viewer.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new Viewer(this);
    setCentralWidget(centralWidget);
}

void MainWindow::loadFile(const QString &filename)
{
    qDebug() << "Load file " << filename;

    centralWidget->load(filename);
}
