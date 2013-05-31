#include "compiler.h"
#include <QRegExp>

Compiler::Compiler()
{
    connect(&m_process, SIGNAL(readyReadStandardError()), this, SLOT(readStdErr()));
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdOut()));
    connect(&m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(done(int, QProcess::ExitStatus)));
}

void Compiler::fileChange(const QString &filename)
{
    // Ensure previous process is dead!
    if (m_process.state() != QProcess::NotRunning)
    {
        m_process.terminate();
        m_process.waitForFinished(500);

        // Still not dead? Try harder!
        if (m_process.state() != QProcess::NotRunning)
        {
            m_process.kill();
            m_process.waitForFinished();
            Q_ASSERT(m_process.state() == QProcess::NotRunning);
        }
    }

    m_filename = filename;

    if (filename.endsWith(".asciidoc"))
        compileAsciidoc(filename);
    else
        emit loadFile(filename);
}

void Compiler::compileAsciidoc(QString filename)
{
    m_process.start(QString("asciidoc"), QStringList(filename));
}

void Compiler::readStdErr()
{
    QByteArray out = m_process.readAllStandardError();
    emit stderr(QString(out));
}

void Compiler::readStdOut()
{
    QByteArray out = m_process.readAllStandardOutput();
    emit stdout(QString(out));
}

void Compiler::done(int exitCode, QProcess::ExitStatus status)
{
    QString outputFile = m_filename.replace(QRegExp(".asciidoc$"), ".html");
    emit loadFile(outputFile);
}
