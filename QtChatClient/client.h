#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QStyle>
#include <QScrollBar>
#include <QListView>

#include "parameters.h"
#include "settingmenu.h"
#include "authentication.h"
#include "./src/include/databasethread.h"

namespace Ui {
class Client;
}

class Client : public QMainWindow{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);
    ~Client();
public slots:
    void show();
private:
    Ui::Client *ui;
    bool connectedToHost;
    void printMessage(const QString& message);
    void setTrayIcon();
    void setChatContent();
    void setUsersRoom(int idRoom);
    QTcpSocket* mSocket;
    SettingMenu* mSettingMenu;
    Authentication* mAuthentication;
    QString mHost;
    uint mPort;
    DatabaseThread* mDB;
    QSystemTrayIcon* trayIcon;
    ClientInformation mClientInfo;

signals:
    void sendMessageEnter();
protected:
   virtual void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();
    void on_pB_setting_clicked();
    void on_pB_sendMessage_clicked();
    void getSettingData(const QString &, const QString &, const uint & );
    void getVisibleChatForm(bool, uint, const QString &);
    void on_pB_disconnect_clicked();
};

#endif // CLIENT_H
