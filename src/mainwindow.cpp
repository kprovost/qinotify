#include "mainwindow.h"
#include "viewer.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_centralWidget = new Viewer(this);
    setCentralWidget(m_centralWidget);
}

void MainWindow::loadFile(const QString &filename)
{
    m_centralWidget->load(filename);
}
