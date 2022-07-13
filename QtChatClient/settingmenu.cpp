#include "settingmenu.h"
#include "ui_settingmenu.h"

SettingMenu::SettingMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingMenu){
    ui->setupUi(this);

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExp portRegex ("^[0-9]+$");

    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    QRegExpValidator *portValidator = new QRegExpValidator(portRegex, this);

    ui->lE_host->setValidator(ipValidator);
    ui->lE_port->setValidator(portValidator);
}

SettingMenu::~SettingMenu(){
    delete ui;
}

void SettingMenu::on_pB_cancel_clicked(){
    mUsername = mHost = "";
    mPort = 0;
    close();
}

void SettingMenu::on_pB_save_clicked(){
    mUsername = ui->lE_name->text();
    mHost = ui->lE_host->text();
    mPort = ui->lE_port->text().toUInt();

    emit sendData(mUsername, mHost, mPort);
    close();
}

void SettingMenu::show(){
    if(!isHidden()) {
        showNormal();
        activateWindow();
    }
    else {
        QWidget::show();
    }
}
