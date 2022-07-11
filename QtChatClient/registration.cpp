#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration){
    ui->setupUi(this);
}

Registration::~Registration(){
    delete ui;
}

void Registration::on_pB_enter_clicked(){
    emit setVisibleLoginForm(true);
    close();
}

void Registration::show()
{
    if(!isHidden()) {
        showNormal();
        activateWindow();
    }
    else {
        QWidget::show();
    }
}
