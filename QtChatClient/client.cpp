#include "client.h"
#include "ui_client.h"

const QString HOST = "localhost";
const int PORT = 7777;
Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    connectedToHost = false;
}

Client::~Client(){
    delete ui;
}

void Client::printMessage(const QString &message){
    ui->tE_allMessage->append(message);
}

void Client::socketConnected(){
    qDebug() << "Connected to server.";
    printMessage("<font color=\"Green\">Connected to server.</font>");
    QString name = ui->lE_inputName->text();
    socket->write("<font color=\"Purple\">" + name.toUtf8() + " has joined the chat room.</font>");
    ui->pB_connect->setText("Disconnect");
    connectedToHost = true;
}

void Client::socketDisconnected(){
    qDebug() << "Disconnected from server.";
    QString name = ui->lE_inputName->text();
    printMessage("<font color=\"Red\">" + name.toUtf8() + " disconnected from server.</font>");
    ui->pB_connect->setText("Connect");
    connectedToHost = false;
}

void Client::socketReadyRead(){
    ui->tE_allMessage->append(socket->readAll());
}

void Client::on_pB_connect_clicked(){
    if(ui->lE_inputName->text() == ""){
        return;
    }
    if (!connectedToHost){
        socket = new QTcpSocket();

        connect(socket, SIGNAL(connected()),    this, SLOT(socketConnected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        connect(socket, SIGNAL(readyRead()),    this, SLOT(socketReadyRead()));

        socket->connectToHost(HOST, PORT);
    }
    else{
        QString name = ui->lE_inputName->text();
        socket->write("<font color=\"Orange\">" + name.toUtf8() + " has left the chat room.</font>");
        socket->disconnectFromHost();
    }
}

void Client::on_pB_sendMessage_clicked(){
    QString name = ui->lE_inputName->text();
    QString message = ui->lE_inputMessage->text();
    socket->write("<font color=\"Blue\">" + name.toUtf8() + "</font>: " + message.toUtf8());
    ui->lE_inputMessage->clear();
}
