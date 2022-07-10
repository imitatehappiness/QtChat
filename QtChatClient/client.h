#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>

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
    QTcpSocket* socket;
    void printMessage(const QString& message);

private slots:
    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();
    void on_pB_connect_clicked();
    void on_pB_sendMessage_clicked();
};

#endif // CLIENT_H
