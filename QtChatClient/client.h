#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QString>

#include "settingmenu.h"
#include "authentication.h"

namespace Ui {
class Client;
}

class Client : public QMainWindow{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;
    bool connectedToHost;
    void printMessage(const QString& message);

    QTcpSocket* mSocket;
    SettingMenu* mSettingMenu;
    Authentication* mAuthentication;
    QString mUsername;
    QString mHost;
    uint mPort;
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();
    void on_pB_setting_clicked();
    void on_pB_sendMessage_clicked();
    void getSettingData(QString, QString, uint );
    void getVisibleChatForm(bool);
    void on_pB_disconnect_clicked();
};

#endif // CLIENT_H
