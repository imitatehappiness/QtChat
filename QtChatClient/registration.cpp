#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration){

    ui->setupUi(this);

    QRegExp emailRegex ("^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$");
    QRegExpValidator *emailValidator = new QRegExpValidator(emailRegex, this);
    ui->lE_mail->setValidator(emailValidator);

    mDB = new DatabaseThread();
}

Registration::~Registration(){
    delete mDB;
    delete ui;
}

void Registration::on_pB_enter_clicked(){
    ui->l_information->setStyleSheet("color: red");
    if(ui->lE_login->text() == ""){
        ui->l_information->setText("Login is empty");
    }else if(ui->lE_password->text() == ""){
        ui->l_information->setText("Password is empty");
    }else if(ui->lE_mail->text() == ""){
        ui->l_information->setText("Email is empty");
    }else if (ui->lE_confirmPassword->text() != ui->lE_password->text()){
        ui->l_information->setText("Passwords don't match");
    }else{
        QString login, password, email;
        login = ui->lE_login->text();
        password = ui->lE_password->text();
        email = ui->lE_mail->text();

        QString query = "SELECT id FROM users WHERE login = '" + login + "'";
        bool validate = mDB->setQuery(query);
        Q_UNUSED(validate);

        QVector<QVector<QVariant>> res =  mDB->getData();
        if(res.size() != 0){
            ui->l_information->setText("Login is already in use");
        }else{

            QString query = "SELECT id FROM users WHERE email = '" + email + "'";
            validate = mDB->setQuery(query);
            res =  mDB->getData();
            if(res.size() != 0){
                ui->l_information->setText("Email is already in use");
            }else{

                QString query = "INSERT INTO users (login, name, password, email) VALUES ( '" + login + "', '" + login + "', '" + password + "', '" + email + "')";
                validate = mDB->setQuery(query);
                ui->l_information->setText("");
                ui->l_information->setStyleSheet("");
                emit setVisibleLoginForm(true);
                close();
            }
        }
    }
}

void Registration::show(){
    if(!isHidden()) {
        showNormal();
        activateWindow();
    }
    else {
        QWidget::show();
        ui->lE_login->setText("");
        ui->lE_password->setText("");
        ui->lE_confirmPassword->setText("");
        ui->lE_mail->setText("");
        ui->l_information->setText("");
    }
}

void Registration::on_pB_cancel_clicked(){
    emit setVisibleLoginForm(true);
    close();
}




