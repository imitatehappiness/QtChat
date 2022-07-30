#include <QCoreApplication>
#include "chatserver.h"
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    ChatServer* server = new ChatServer();
    server->startServer();

    return a.exec();
}
