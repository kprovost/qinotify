#pragma once

#include <QObject>

class Compiler : public QObject
{
    Q_OBJECT;

public:
    Compiler();

public slots:
    void fileChange(const QString &filename);

signals:
    void loadFile(const QString &filename);

private:
    QString compileAsciidoc(QString filename);
};
