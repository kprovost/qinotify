#pragma once

#include <QObject>
#include <QProcess>

class Compiler : public QObject
{
    Q_OBJECT;

public:
    Compiler();

public slots:
    void fileChange(const QString &filename);
    void readStdErr();
    void readStdOut();
    void done(int exitCode, QProcess::ExitStatus status);

signals:
    void loadFile(const QString &filename);
    void stderr(const QString &out);
    void stdout(const QString &out);

private:
    void compileAsciidoc(QString filename);

    QProcess m_process;
    QString m_filename;
};
