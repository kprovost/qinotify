#pragma once

#include <QWebView>

class Viewer : public QWebView
{
    Q_OBJECT;

public:
    Viewer(QWidget *parent = NULL);
};
