#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMap>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>

#include "parameters.h"
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
    void cancelClicked();
    void enterClicked();

public slots:
    void show();

signals:
    void setVisibleLoginForm(bool);
private:
    Ui::Registration *ui;
    DatabaseThread* mDB;
    QMap<int, QPair<QLineEdit*, QString>> mLineEditsObjects;
    QMap<int, QPair<QPushButton*, QString>> mPushButtonObjects;
    QMap<int, QPair<QLabel*, QString>> mLabelObjects;

    void initFormObject();
};

#endif // REGISTRATION_H
