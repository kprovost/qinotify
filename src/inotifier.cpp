#include "inotifier.h"
#include <unistd.h>

INotifier::INotifier()
    : m_fd(-1)
{

}

INotifier::~INotifier()
{
    if (m_fd >= 0)
        close(m_fd);
}

bool INotifier::monitor(const QString &filename)
{
    Q_ASSERT(m_fd == -1);

    m_filename = filename;
    return false;
}
