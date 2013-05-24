#pragma once

#include <QThread>

class INotifier : public QThread
{
    Q_OBJECT;

public:
    INotifier();
    ~INotifier();

    bool monitor(const QString &filename);

signals:
    void fileChange(const QString &filename);

private:
    int m_fd;
    QString m_filename;

    virtual void run();
};
