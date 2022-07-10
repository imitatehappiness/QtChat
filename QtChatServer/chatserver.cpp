#include "chatserver.h"


const int PORT = 7777;
const int NAX_CONNECTION = 21;
ChatServer::ChatServer(QObject *parent) : QObject(parent){

}

void ChatServer::startServer(){
    mChatServer = new QTcpServer();
    mClients    = new QVector<QTcpSocket*>;

    mChatServer->setMaxPendingConnections(NAX_CONNECTION);

    connect(mChatServer, SIGNAL(newConnection()), this, SLOT(newClientConnection()));
    mChatServer->listen(QHostAddress::Any, PORT) ? qDebug() << "Server has started. Listening to port " << PORT :
                qDebug() << "Server failed to start. Error: " << mChatServer->errorString();
}

void ChatServer::sendMessageToClients(const QString& message){
    if (mClients->size() > 0){
        for (int i = 0; i < mClients->size(); i++){
            if (mClients->at(i)->isOpen() && mClients->at(i)->isWritable()){
                mClients->at(i)->write(message.toUtf8());
                // add message to DB
            }
        }
    }
}

void ChatServer::newClientConnection(){
    QTcpSocket* client = mChatServer->nextPendingConnection();
    QString ipAddress = client->peerAddress().toString();
    int port = client->peerPort();

    connect(client, &QTcpSocket::disconnected, this, &ChatServer::socketDisconnected);
    connect(client, &QTcpSocket::readyRead,    this, &ChatServer::socketReadyRead);
    connect(client, &QTcpSocket::stateChanged, this, &ChatServer::socketStateChanged);

    mClients->push_back(client);
    qDebug() << "Socket connected from " + ipAddress + ":" + QString::number(port);
}


void ChatServer::socketDisconnected(){
    QTcpSocket* client = qobject_cast<QTcpSocket*>(QObject::sender());
    QString socketIpAddress = client->peerAddress().toString();
    int port = client->peerPort();

    qDebug() << "Socket disconnected from " + socketIpAddress + ":" + QString::number(port);
}

void ChatServer::socketReadyRead(){
    QTcpSocket* client = qobject_cast<QTcpSocket*>(QObject::sender());
    QString socketIpAddress = client->peerAddress().toString();
    int port = client->peerPort();

    QString data = QString(client->readAll());
    qDebug() << "Message: " + data + " (" + socketIpAddress + ":" + QString::number(port) + ")";
    sendMessageToClients(data);
}


void ChatServer::socketStateChanged(QAbstractSocket::SocketState state){
    QTcpSocket* client = qobject_cast<QTcpSocket*>(QObject::sender());
    QString socketIpAddress = client->peerAddress().toString();
    int port = client->peerPort();

    QString desc;

    switch(state){
    case QAbstractSocket::UnconnectedState: desc = "The socket is not connected."; break;
    case QAbstractSocket::HostLookupState:  desc = "The socket is performing a host name lookup."; break;
    case QAbstractSocket::ConnectingState:  desc = "The socket has started establishing a connection."; break;
    case QAbstractSocket::ConnectedState:   desc = "A connection is established."; break;
    case QAbstractSocket::BoundState:       desc = "The socket is bound to an address and port."; break;
    case QAbstractSocket::ClosingState:     desc = "The socket is about to close (data may still be waiting to be written)."; break;
    case QAbstractSocket::ListeningState:   desc = "For internal use only."; break;
    }

    qDebug() << "Socket state changed (" + socketIpAddress + ":" + QString::number(port) + "): " + desc;
}
