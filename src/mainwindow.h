#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include "viewer.h"

class MainWindow : public QWidget
{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = NULL);

public slots:
    void loadFile(const QString&);

    void stderr(const QString&);
    void stdout(const QString&);
    void clear();

private:
    QGridLayout *m_layout;
    QWidget *m_window;
    Viewer *m_centralWidget;
    QTextEdit *m_errorBox;
};
