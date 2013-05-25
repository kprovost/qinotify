#include "inotifier.h"
#include <errno.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <libgen.h>
#include <string.h>
#include <iostream>

#include <QFileInfo>
#include <QDir>

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

    QFileInfo fi(filename);
    QString directory = fi.dir().path();

    int ret = inotify_add_watch(m_fd, directory.toStdString().c_str(),
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

    QFileInfo fi(m_filename);
    QString file = fi.fileName();

    size_t size = sizeof(struct inotify_event) + NAME_MAX + 1;
    struct inotify_event *event = (struct inotify_event*)new char[size];

    while (1)
    {
        int ret = read(m_fd, event, size);
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;

            cerr << "Inotify failure: " << strerror(errno)
                 << " (" << errno << ")" << endl;
            break;
        }
        Q_ASSERT(ret == sizeof(struct inotify_event));

        if (event->name && event->name != file)
            continue;

        if (event->mask & IN_IGNORED)
            /* This happens when the file is removed (as vim does whenever it
             * saves!) */
            continue;

        if (event->mask & IN_MODIFY
            || event->mask & IN_CREATE
            || event->mask & IN_CLOSE_WRITE)
        {
            emit fileChange(m_filename);
        }
    }

    delete [] event;
}
