#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QDialog>
#include <QString>
#include <QRegExp>
#include <QRegExpValidator>

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
    void on_pB_cancel_clicked();
    void on_pB_save_clicked();
public slots:
    void show();

private:
    Ui::SettingMenu *ui;
    QString mUsername, mHost;
    uint mPort;

};

#endif // SETTINGMENU_H
