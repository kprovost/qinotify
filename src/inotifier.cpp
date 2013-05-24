#include "inotifier.h"
#include <errno.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <string.h>
#include <iostream>

using namespace std;

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

    m_fd = inotify_init();
    Q_ASSERT(m_fd > 0);

    int ret = inotify_add_watch(m_fd, filename.toStdString().c_str(),
            IN_CLOSE_WRITE | IN_MODIFY);
    if (ret == -1)
    {
        cerr << "Unable to monitor file " << filename.toStdString() << ": "
            << strerror(errno) << " (" << errno << ")" << endl;
        return false;
    }

    return true;
}

void INotifier::run()
{
    Q_ASSERT(m_fd != -1);

    /* Emit initial file change so we load the file for the first time */
    emit fileChange(m_filename);

    while (1)
    {
        struct inotify_event event;
        int ret = read(m_fd, &event, sizeof(struct inotify_event));
        if (ret == -1)
        {
            cerr << "Inotify failure: " << strerror(errno)
                 << " (" << errno << ")" << endl;
            break;
        }
        Q_ASSERT(ret == sizeof(struct inotify_event));

        /* TODO: Handle file deletion / re-creation */
        emit fileChange(m_filename);
    }

    Q_ASSERT(false);
}
