#include "compiler.h"

Compiler::Compiler()
{

}

void Compiler::fileChange(const QString &filename)
{
    emit loadFile(filename);
}
