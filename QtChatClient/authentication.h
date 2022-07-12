#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QDialog>

#include "registration.h"
#include "./src/include/databasethread.h"

namespace Ui {
class Authentication;
}

class Authentication : public QDialog{
    Q_OBJECT
public:
     Authentication(QWidget *parent = nullptr);
    ~Authentication();
signals:
    void setVisibleChatForm(bool);
private:
    Ui::Authentication *ui;
    Registration* mRegistration;
    DatabaseThread* mDB;
private slots:
    void on_pB_login_clicked();
    void on_pB_registration_clicked();
    void getVisibleLoginForm(bool);
public slots:
    void show();
};

#endif // AUTHENTICATION_H
