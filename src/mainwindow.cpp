#include "mainwindow.h"
#include "viewer.h"
#include <qdebug.h>
#include <QColor>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    //: QMainWindow(parent)
    : QWidget(parent)
{
    m_centralWidget = new Viewer(this);

    m_errorBox = new QTextEdit(this);
    m_errorBox->setReadOnly(true);

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_centralWidget, 0, 0);
    m_layout->addWidget(m_errorBox, 10, 0);

    setLayout(m_layout);
}

void MainWindow::loadFile(const QString &filename)
{
    m_centralWidget->load(filename);
}

void MainWindow::stderr(const QString& err)
{
    int origFw = m_errorBox->fontWeight();
    QColor origColor = m_errorBox->textColor();

    m_errorBox->setFontWeight(QFont::Bold);
    m_errorBox->setTextColor(QColor("Red"));
    m_errorBox->append(err);

    m_errorBox->setFontWeight(origFw);
    m_errorBox->setTextColor(origColor);

    m_errorBox->show();
}

void MainWindow::stdout(const QString& warn)
{
    int origFw = m_errorBox->fontWeight();
    QColor origColor = m_errorBox->textColor();

    m_errorBox->setFontWeight(QFont::Normal);
    m_errorBox->setTextColor(QColor("Black"));
    m_errorBox->append(warn);

    m_errorBox->setFontWeight(origFw);
    m_errorBox->setTextColor(origColor);

    m_errorBox->show();
}

void MainWindow::clear()
{
    m_errorBox->hide();
    m_errorBox->clear();
}
