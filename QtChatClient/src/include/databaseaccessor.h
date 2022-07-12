#ifndef DATABASEACCESSOR_H
#define DATABASEACCESSOR_H

#include <QString>
#include <QtSql>
#include <QSqlQuery>
#include <QVector>
#include <QVariant>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

/// @class DatabaseAccessor  - singleton database accessor
class DatabaseAccessor : public QObject{
    Q_OBJECT
public:
    static DatabaseAccessor* getInstance();
    static QPair<QVector<QVector<QVariant>>, bool> executeSqlQuery(const QString&);
    /// BD information
    QString dbHostName;
    QString dbName;
    QString dbUserName;
    QString dbPassword;
    QString dbType;
    int     dbPort;

private:
    DatabaseAccessor();
    DatabaseAccessor(const DatabaseAccessor& );
    DatabaseAccessor& operator=(const DatabaseAccessor& );
    static QSqlDatabase sDBPtr;
    static QMutex sDBMutex;

public slots:

signals:
    void finished();
};


#endif // DATABASEACCESSOR_H
