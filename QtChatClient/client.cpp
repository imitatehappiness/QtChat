#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client){

    mDB = new DatabaseThread();

    mAuthentication = new Authentication();
    mAuthentication->show();

    mSettingMenu = new SettingMenu();
    ui->setupUi(this);
    connectedToHost = false;

    ui->pB_sendMessage->setEnabled(0);
    connect(mSettingMenu, SIGNAL(sendData(const QString &, const QString &, const uint & )), this, SLOT(getSettingData(const QString &, const QString &, const uint & )));
    connect(mAuthentication, SIGNAL(setVisibleChatForm(bool)), this, SLOT(getVisibleChatForm(bool)));
    connect(this, SIGNAL(sendMessageEnter()), this, SLOT(on_pB_sendMessage_clicked()));
}

Client::~Client(){
    delete mAuthentication;
    delete mSettingMenu;
    delete mDB;
    delete mSocket;
    delete ui;
}

void Client::printMessage(const QString &message){
    ui->tE_display->append(message);
}

void Client::socketConnected(){
    qDebug() << "Connected to server.";
    printMessage("<font color=\"Green\">Connected to server.</font>");
    QString name = mUsername;
    mSocket->write("<font color=\"Purple\">" + name.toUtf8() + " has joined the chat room.</font>");
    connectedToHost = true;
}

void Client::socketDisconnected(){
    qDebug() << "Disconnected from server.";
    QString name = mUsername;
    printMessage("<font color=\"Red\">" + name.toUtf8() + " disconnected from server.</font>");
    connectedToHost = false;
}

void Client::socketReadyRead(){
    ui->tE_display->append(mSocket->readAll());
}

void Client::on_pB_setting_clicked(){
    mSettingMenu->show();

}

void Client::on_pB_sendMessage_clicked(){
    QString name = mUsername;
    QString message = ui->lE_inputMessage->text();

    mSocket->write("<font color=\"Blue\">" + name.toUtf8() + "</font>: " + message.toUtf8());
    ui->lE_inputMessage->clear();
}

void Client::getSettingData(const QString& username, const QString& host, const uint& port){
    mUsername = username;
    mHost = host;
    mPort = port;

    qDebug() << mHost;
    qDebug() << mPort;

    ui->pB_sendMessage->setEnabled(0);

    if (!connectedToHost){
        mSocket = new QTcpSocket();
        mSocket->connectToHost(mHost, mPort);
        connect(mSocket, SIGNAL(connected()),    this, SLOT(socketConnected()));
        connect(mSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        connect(mSocket, SIGNAL(readyRead()),    this, SLOT(socketReadyRead()));

        ui->pB_sendMessage->setEnabled(1);
    }
}

void Client::getVisibleChatForm(bool visible){
    setVisible(visible);
}

void Client::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);
    QApplication::closeAllWindows();
}

void Client::on_pB_disconnect_clicked(){
    if (connectedToHost){
        mSocket->write("<font color=\"Orange\">" + mUsername.toUtf8() + " has left the chat room.</font>");
        mSocket->disconnectFromHost();
    }
    ui->pB_sendMessage->setEnabled(0);
}

void Client::keyPressEvent(QKeyEvent *event){
    //QKeyEvent* key = static_cast<QKeyEvent*>(event);
    if (event->key() == Qt::Key_Return){
        emit sendMessageEnter();
    }
}
