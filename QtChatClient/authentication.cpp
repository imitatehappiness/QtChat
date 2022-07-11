#include "authentication.h"
#include "ui_authentication.h"

Authentication::Authentication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentication){

    registration = new Registration();
    connect(registration, SIGNAL(setVisibleLoginForm(bool)), this, SLOT(getVisibleLoginForm(bool)));

    emit setVisibleChatForm(false);
    ui->setupUi(this);
}

Authentication::~Authentication(){
    delete ui;
    delete registration;
}

void Authentication::on_pB_login_clicked(){
    emit setVisibleChatForm(true);
    close();
}


void Authentication::on_pB_registration_clicked(){
    setVisible(false);
    registration->show();
}

void Authentication::getVisibleLoginForm(bool visible){
    setVisible(visible);
}

void Authentication::show()
{
    if(!isHidden()) {
        showNormal();
        activateWindow();
    }
    else {
        QWidget::show();
    }
}
