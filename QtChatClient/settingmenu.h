#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QDialog>
#include <QString>
#include <QRegExp>
#include <QRegExpValidator>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>

#include "parameters.h"
#include "./src/include/databasethread.h"

namespace Ui {
class SettingMenu;
}

class SettingMenu : public QDialog{
    Q_OBJECT
public:
    explicit SettingMenu(QWidget *parent = nullptr);
    ~SettingMenu();
    void setName(const QString&);
signals:
    void sendData(const QString &, const QString &, const uint & );
private slots:
    void cancelClicked();
    void connectClicked();
public slots:
    void show();

private:
    Ui::SettingMenu *ui;
    QString mUsername, mHost;
    uint mPort;
    QMap<int, QPair<QLineEdit*, QString>>   mLineEditsObjects;
    QMap<int, QPair<QPushButton*, QString>> mPushButtonObjects;

    void initFormObject();
};

#endif // SETTINGMENU_H
