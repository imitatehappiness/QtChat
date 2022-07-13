#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration){

    ui->setupUi(this);
    initFormObject();

//    QRegExp emailRegex ("^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$");
//    QRegExpValidator *emailValidator = new QRegExpValidator(emailRegex, this);
//    ui->lE_mail->setValidator(emailValidator);

    mDB = new DatabaseThread();
}

Registration::~Registration(){
    delete mDB;
    delete ui;
}

void Registration::enterClicked(){

    QString login, password, confirmPassword, email;
    login = mLineEditsObjects[idFormObject::registrationLineEditLogin].first->text();
    password = mLineEditsObjects[idFormObject::registrationLineEditPassword].first->text();
    confirmPassword =  mLineEditsObjects[idFormObject::registrationLineEditConfirmPassword].first->text();
    email = mLineEditsObjects[idFormObject::registrationLineEditEmail].first->text();

    if(login == ""){
        mLabelObjects[idFormObject::registrationLabelInformation].first->setText("Login is empty");
    }else if(password == ""){
        mLabelObjects[idFormObject::registrationLabelInformation].first->setText("Password is empty");
    }else if(email == ""){
        mLabelObjects[idFormObject::registrationLabelInformation].first->setText("Email is empty");
    }else if (password != confirmPassword){
        mLabelObjects[idFormObject::registrationLabelInformation].first->setText("Passwords don't match");
    }else{
        QString query = "SELECT id FROM users WHERE login = '" + login + "'";
        bool validate = mDB->setQuery(query);

        QVector<QVector<QVariant>> res =  mDB->getData();
        if(res.size() != 0){
            mLabelObjects[idFormObject::registrationLabelInformation].first->setText("Login is already in use");
        }else{

            QString query = "SELECT id FROM users WHERE email = '" + email + "'";
            validate = mDB->setQuery(query);
            res =  mDB->getData();
            if(res.size() != 0){
                mLabelObjects[idFormObject::registrationLabelInformation].first->setText("Email is already in use");
            }else{

                QString query = "INSERT INTO users (login, name, password, email) VALUES ( '" + login + "', '" + login + "', '" + password + "', '" + email + "')";
                validate = mDB->setQuery(query);
                mLabelObjects[idFormObject::registrationLabelInformation].first->setText("");
                emit setVisibleLoginForm(true);
                close();
            }
        }
        Q_UNUSED(validate);
    }
}

void Registration::cancelClicked(){
    emit setVisibleLoginForm(true);
    close();
}

void Registration::show(){
    if(!isHidden()) {
        showNormal();
        activateWindow();
    }else {
        QWidget::show();
        mLineEditsObjects[idFormObject::registrationLineEditLogin].first->setText("");
        mLineEditsObjects[idFormObject::registrationLineEditPassword].first->setText("");
        mLineEditsObjects[idFormObject::registrationLineEditConfirmPassword].first->setText("");
        mLineEditsObjects[idFormObject::registrationLineEditEmail].first->setText("");
        mLabelObjects[idFormObject::registrationLabelInformation].first->setText("");
    }
}

void Registration::initFormObject(){

    /// @section QLineEdit =======================================================================================================
    QGridLayout *gLineEdit = new QGridLayout;
    ui->w_widgetsLineEdit->setLayout(gLineEdit);

    mLineEditsObjects[idFormObject::registrationLineEditLogin]           = {new QLineEdit(), "Login"};
    mLineEditsObjects[idFormObject::registrationLineEditPassword]        = {new QLineEdit(), "Password"};
    mLineEditsObjects[idFormObject::registrationLineEditConfirmPassword] = {new QLineEdit(), "Confirm Password"};
    mLineEditsObjects[idFormObject::registrationLineEditEmail]           = {new QLineEdit(), "Email"};

    int row = 1, col = 1;
    for(const auto &w : mLineEditsObjects){
        QLineEdit * lineEdit = w.first;
        lineEdit->setPlaceholderText(w.second);
        lineEdit->setMinimumSize(300, MIN_HEIGHT_OBJECT);
        gLineEdit->addWidget(lineEdit, row, col);
        row++;
    }
    mLineEditsObjects[idFormObject::registrationLineEditPassword].first->setEchoMode(QLineEdit::EchoMode::Password);
    mLineEditsObjects[idFormObject::registrationLineEditConfirmPassword].first->setEchoMode(QLineEdit::EchoMode::Password);

    /// @section QPushButton =======================================================================================================
    QGridLayout *gPushButton = new QGridLayout;
    ui->w_widgetsPushButton->setLayout(gPushButton);

    mPushButtonObjects[idFormObject::registrationPushButtonCancel] = {new QPushButton(), "Cancel"};
    mPushButtonObjects[idFormObject::registrationPushButtonEnter]  = {new QPushButton(), "Enter"};

    row = 1, col = 1;
    for(const auto &w : mPushButtonObjects){
        QPushButton * pushButton = w.first;
        pushButton->setText(w.second);
        pushButton->setMinimumSize(100, MIN_HEIGHT_OBJECT);
        gPushButton->addWidget(pushButton, row, col);
        col++;
    }

    connect(mPushButtonObjects[idFormObject::registrationPushButtonCancel].first, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(mPushButtonObjects[idFormObject::registrationPushButtonEnter].first, SIGNAL(clicked()), this, SLOT(enterClicked()));

    /// @section QLabel =======================================================================================================
    QGridLayout *gLabel = new QGridLayout;
    ui->w_widgetsLabel->setLayout(gLabel);

    mLabelObjects[idFormObject::registrationLabelInformation] = {new QLabel(), "Information"};

    row = 1, col = 1;
    for(const auto &w : mLabelObjects){
        QLabel * label = w.first;
        label->setMinimumSize(300, MIN_HEIGHT_OBJECT);
        label->setStyleSheet("color: #233738");
        gLabel->addWidget(label, row, col);
        col++;
    }
}



