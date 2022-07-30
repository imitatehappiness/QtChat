#include "src/include/databasethread.h"

DatabaseThread::DatabaseThread(){
}

bool DatabaseThread::setQuery(const QString& query){

    QFuture<QPair<QVector<QVector<QVariant>>, bool>> future = QtConcurrent::run(DatabaseAccessor::executeSqlQuery, QString(query));
    future.waitForFinished();
    result.clear();
    QVector<QVector<QVariant>>().swap(result);
    result = future.result().first;

    return  future.result().second;
}

QVector<QVector<QVariant>> DatabaseThread::getData(){
    return result;
}

