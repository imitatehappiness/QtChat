#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>

#include "./src/include/databasethread.h"
namespace Ui {
class Registration;
}

class Registration : public QDialog{
    Q_OBJECT
public:
    Registration(QWidget *parent = nullptr);
    ~Registration();
private slots:
    void on_pB_enter_clicked();
    void on_pB_cancel_clicked();
public slots:
    void show();

signals:
    void setVisibleLoginForm(bool);
private:
    Ui::Registration *ui;
    DatabaseThread* mDB;

};

#endif // REGISTRATION_H
