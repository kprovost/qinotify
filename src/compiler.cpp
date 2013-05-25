#include "compiler.h"
#include <QRegExp>

Compiler::Compiler()
{

}

void Compiler::fileChange(const QString &filename)
{
    QString outputFile;

    if (filename.endsWith(".asciidoc"))
    {
        outputFile = compileAsciidoc(filename);
    }
    else
        outputFile = filename;

    emit loadFile(outputFile);
}

QString Compiler::compileAsciidoc(QString filename)
{
    QString cmd = QString("asciidoc %1").arg(filename);
    system(cmd.toStdString().c_str());

    return filename.replace(QRegExp(".asciidoc$"), ".html");
}
