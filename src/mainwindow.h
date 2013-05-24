#pragma once

#include <QMainWindow>
#include "viewer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = NULL);

private slots:
    void loadFile(const QString&);

private:
    Viewer *centralWidget;
};
