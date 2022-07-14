#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QDialog>
#include <QMap>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>

#include "parameters.h"
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
public slots:
    void show();
signals:
    void setVisibleChatForm(bool, uint, QString);
private slots:
    void signInClicked();
    void registrationClicked();
    void getVisibleLoginForm(bool);
private:
    Ui::Authentication *ui;
    Registration* mRegistration;
    DatabaseThread* mDB;

    QMap<int, QPair<QLineEdit*, QString>> mLineEditsObjects;
    QMap<int, QPair<QPushButton*, QString>> mPushButtonObjects;
    QMap<int, QPair<QLabel*, QString>> mLabelObjects;

    void initFormObject();
};

#endif // AUTHENTICATION_H
