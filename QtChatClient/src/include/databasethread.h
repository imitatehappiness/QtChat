#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QString>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include "databaseaccessor.h"

class DatabaseThread : public QThread{
    Q_OBJECT
public:
    DatabaseThread();
    bool setQuery(const QString&);
    QVector<QVector<QVariant>> getData();
signals:
    void executeSqlQuery(QString);
private:
    QVector<QVector<QVariant>> result;
    QString mQuery;
};

#endif // DATABASETHREAD_H
