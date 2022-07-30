#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client){

    ui->setupUi(this);

    mDB = new DatabaseThread();

    mAuthentication = new Authentication();
    mAuthentication->show();

    mSettingMenu = new SettingMenu();
    connectedToHost = false;

    ui->pB_sendMessage->setEnabled(0);

    connect(mSettingMenu, SIGNAL(sendData(const QString &, const QString &, const uint & )), this, SLOT(getSettingData(const QString &, const QString &, const uint & )));
    connect(mAuthentication, SIGNAL(setVisibleChatForm(bool, uint, QString)), this, SLOT(getVisibleChatForm(bool, uint, QString)));
    connect(this, SIGNAL(sendMessageEnter()), this, SLOT(on_pB_sendMessage_clicked()));
}

Client::~Client(){
    delete mAuthentication;
    delete mSettingMenu;
    delete mDB;
    delete ui;
}

void Client::printMessage(const QString &message){
    ui->tE_display->append(message);
}

void Client::socketConnected(){
    qDebug() << "Connected to server.";
    printMessage("<font color=\"Green\">Connected to server.</font>");
    QString name = mUsername;
    mSocket->write("<font color=\"#233738\">" + name.toUtf8() + " has joined the chat room.</font>");
    connectedToHost = true;
}

void Client::socketDisconnected(){
    qDebug() << "Disconnected from server.";
    QString name = mUsername;
    printMessage("<font color=\"#B53543\">" + name.toUtf8() + " disconnected from server.</font>");
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
    bool validate;

    /// insert content
    QString query = "INSERT INTO contents (chat_id, user_id, content) VALUES (" + QString::number(mClientInfo.idChat) + ", " +
                                                                                  QString::number(mClientInfo.idUser) + ", '" +
                                                                                  message + "')";
    validate = mDB->setQuery(query);

    ///select content id
    query = "SELECT id FROM contents WHERE chat_id = " + QString::number(mClientInfo.idChat) +
                                     " AND user_id = " + QString::number(mClientInfo.idUser) +
                                     " AND content = '" + message + "'";

    validate = mDB->setQuery(query);
    QVector<QVector<QVariant>> res =  mDB->getData();
    int idContent = res.size() != 0 ? res[0][0].toInt() :  -1;

    /// insert message
    query = "INSERT INTO messages (chat_id, user_id, content_id, date_create) VALUES (" + QString::number(mClientInfo.idChat) + ", " +
                                                                                          QString::number(mClientInfo.idUser) + ", " +
                                                                                          QString::number(idContent) + ", current_timestamp)";
    validate = mDB->setQuery(query);
    Q_UNUSED(validate);

    mSocket->write("<font color=\"#155049\" style=\"font-weight: bold;\">" + name.toUtf8() + "</font>: " + message.toUtf8());
    ui->lE_inputMessage->clear();
}

void Client::getSettingData(const QString& username, const QString& host, const uint& port){
    mUsername = username;
    mHost = host;
    mPort = port;

    ui->pB_sendMessage->setEnabled(0);

    if (!connectedToHost){
        mSocket = new QTcpSocket(this);
        mSocket->connectToHost(mHost, mPort);
        connect(mSocket, SIGNAL(connected()),    this, SLOT(socketConnected()));
        connect(mSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        connect(mSocket, SIGNAL(readyRead()),    this, SLOT(socketReadyRead()));

        ui->pB_sendMessage->setEnabled(1);
    }
}

void Client::getVisibleChatForm(bool visible, uint id, QString name){
    mClientInfo.idUser = id;
    mClientInfo.idChat = 1;
    mClientInfo.username = name;
    setVisible(visible);
    setTrayIcon();
}

void Client::closeEvent(QCloseEvent *event){
    Q_UNUSED(event);
    QApplication::closeAllWindows();
}

void Client::on_pB_disconnect_clicked(){
    if (connectedToHost){
        mSocket->write("<font color=\"#5b836d\">" + mUsername.toUtf8() + " has left the chat room.</font>");
        mSocket->disconnectFromHost();
    }
    ui->pB_sendMessage->setEnabled(0);
}

void Client::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Return){
        emit sendMessageEnter();
    }
}

void Client::setTrayIcon(){
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/style/style/icons/chat-icon.png"));
    trayIcon->setToolTip("Messanger");

    QMenu* menu = new QMenu(this);

    QAction* viewWindow = new QAction(trUtf8("Open messanger"), this);
    QAction* quitAction = new QAction(trUtf8("Exit"), this);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    trayIcon->setContextMenu(menu);
    trayIcon->show();
}

void Client::show(){
    if(!isHidden()) {
        showNormal();
        activateWindow();
    }else {
        QWidget::show();
    }
}
