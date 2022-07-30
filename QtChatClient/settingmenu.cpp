#include "settingmenu.h"
#include "ui_settingmenu.h"

SettingMenu::SettingMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingMenu){
    ui->setupUi(this);

    initFormObject();
}

SettingMenu::~SettingMenu(){
    delete ui;
}

void SettingMenu::cancelClicked(){
    mUsername = mHost = "";
    mPort = 0;
    close();
}

void SettingMenu::connectClicked(){
    mUsername = mLineEditsObjects[idFormObject::settingMenuLineEditName].first->text();
    mHost     = mLineEditsObjects[idFormObject::settingMenuLineEditHost].first->text();
    mPort     = mLineEditsObjects[idFormObject::settingMenuLineEditPort].first->text().toUInt();

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

void SettingMenu::setName(const QString &name){
    mLineEditsObjects[idFormObject::settingMenuLineEditName].first->setText(name);
}

void SettingMenu::initFormObject(){
    /// @section QLineEdit =======================================================================================================
    QGridLayout* gLineEdit = new QGridLayout;
    ui->w_widgetsLineEdit->setLayout(gLineEdit);

    mLineEditsObjects[idFormObject::settingMenuLineEditName] = {new QLineEdit(), "Username"};
    mLineEditsObjects[idFormObject::settingMenuLineEditHost] = {new QLineEdit(), "Host"};
    mLineEditsObjects[idFormObject::settingMenuLineEditPort] = {new QLineEdit(), "Port"};

    int row = 1, col = 1;
    for(const auto &w : mLineEditsObjects){
        QLineEdit* lineEdit = w.first;
        lineEdit->setPlaceholderText(w.second);
        lineEdit->setMinimumSize(300, MIN_HEIGHT_OBJECT);
        gLineEdit->addWidget(lineEdit, row, col);
        row++;
    }

    mLineEditsObjects[idFormObject::settingMenuLineEditHost].first->setText("127.0.0.1");
    mLineEditsObjects[idFormObject::settingMenuLineEditPort].first->setText("7777");

    mLineEditsObjects[idFormObject::settingMenuLineEditHost].first->setEnabled(0);
    mLineEditsObjects[idFormObject::settingMenuLineEditPort].first->setEnabled(0);


    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExp portRegex ("^[0-9]+$");

    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    QRegExpValidator *portValidator = new QRegExpValidator(portRegex, this);

    mLineEditsObjects[idFormObject::settingMenuLineEditHost].first->setValidator(ipValidator);
    mLineEditsObjects[idFormObject::settingMenuLineEditPort].first->setValidator(portValidator);

    /// @section QPushButton =======================================================================================================
    QGridLayout* gPushButton = new QGridLayout;
    ui->w_widgetsPushButton->setLayout(gPushButton);

    mPushButtonObjects[idFormObject::settingMenuPushButtonCancel]  = {new QPushButton(), "Cancel"};
    mPushButtonObjects[idFormObject::settingMenuPushButtonConnect] = {new QPushButton(), "Connect"};

    row = 1, col = 1;
    for(const auto &w : mPushButtonObjects){
        QPushButton* pushButton = w.first;
        pushButton->setText(w.second);
        pushButton->setMinimumSize(100, MIN_HEIGHT_OBJECT);
        gPushButton->addWidget(pushButton, row, col);
        col++;
    }

    connect(mPushButtonObjects[idFormObject::settingMenuPushButtonCancel].first,  SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(mPushButtonObjects[idFormObject::settingMenuPushButtonConnect].first, SIGNAL(clicked()), this, SLOT(connectClicked()));
}
