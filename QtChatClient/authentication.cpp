#include "authentication.h"
#include "ui_authentication.h"

Authentication::Authentication( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentication){

    mDB = new DatabaseThread();
    mRegistration = new Registration();
    connect(mRegistration, SIGNAL(setVisibleLoginForm(bool)), this, SLOT(getVisibleLoginForm(bool)));

    emit setVisibleChatForm(false);
    ui->setupUi(this);
}

Authentication::~Authentication(){
    delete ui;
    delete mDB;
    delete mRegistration;
}

void Authentication::on_pB_login_clicked(){
    QString login, password;
    login = ui->lE_login->text();
    password = ui->lE_password->text();
    QString query = "SELECT id FROM users WHERE login = '" + login + "' AND password = '" + password + "'";
    bool validate = mDB->setQuery(query);
    Q_UNUSED(validate);
    QVector<QVector<QVariant>> res =  mDB->getData();

    if(res.size() == 1){
        emit setVisibleChatForm(true);
        close();
    }else{
        ui->l_information->setStyleSheet("color: red");
        ui->l_information->setText("Invalid login or password");
    }
}

void Authentication::on_pB_registration_clicked(){
    setVisible(false);
    mRegistration->show();
}

void Authentication::getVisibleLoginForm(bool visible){
    ui->lE_login->setText("");
    ui->lE_password->setText("");
    ui->l_information->setStyleSheet("");
    ui->l_information->setText("");

    setVisible(visible);
}

void Authentication::show(){
    if(!isHidden()){
        showNormal();
        activateWindow();
    }
    else {
        ui->l_information->setStyleSheet("");
        ui->l_information->setText("");
        QWidget::show();
    }
}
