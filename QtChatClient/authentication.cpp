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
    initFormObject();
}

Authentication::~Authentication(){
    delete ui;
    delete mDB;
    delete mRegistration;
}

void Authentication::signInClicked(){
    QString login, password;
    login = mLineEditsObjects[idFormObject::authenticationLineEditLogin].first->text();
    password = mLineEditsObjects[idFormObject::authenticationLineEditPassword].first->text();
    QString query = "SELECT id FROM users WHERE login = '" + login + "' AND password = '" + password + "'";
    bool validate = mDB->setQuery(query);
    Q_UNUSED(validate);
    QVector<QVector<QVariant>> res =  mDB->getData();

    if(res.size() == 1){
        emit setVisibleChatForm(true);
        close();
    }else{
        mLabelObjects[idFormObject::authenticationLabelInformation].first->setText("Invalid login or password");
    }
}

void Authentication::registrationClicked(){
    setVisible(false);
    mRegistration->show();
}

void Authentication::getVisibleLoginForm(bool visible){
    mLineEditsObjects[idFormObject::authenticationLineEditLogin].first->setText("");
    mLineEditsObjects[idFormObject::authenticationLineEditPassword].first->setText("");
    mLabelObjects[idFormObject::authenticationLabelInformation].first->setText("");

    setVisible(visible);
}

void Authentication::show(){
    if(!isHidden()){
        showNormal();
        activateWindow();
    }else {
        mLineEditsObjects[idFormObject::authenticationLineEditLogin].first->setText("");
        mLineEditsObjects[idFormObject::authenticationLineEditPassword].first->setText("");
        mLabelObjects[idFormObject::authenticationLabelInformation].first->setText("");
        QWidget::show();
    }
}

void Authentication::initFormObject(){
    /// @section QLineEdit =======================================================================================================
    QGridLayout *gLineEdit = new QGridLayout;
    ui->w_widgetsLineEdit->setLayout(gLineEdit);

    mLineEditsObjects[idFormObject::authenticationLineEditLogin]    = {new QLineEdit(), "Login"};
    mLineEditsObjects[idFormObject::authenticationLineEditPassword] = {new QLineEdit(), "Password"};

    int row = 1, col = 1;
    for(const auto &w : mLineEditsObjects){
        QLineEdit * lineEdit = w.first;
        lineEdit->setPlaceholderText(w.second);
        lineEdit->setMinimumSize(300, MIN_HEIGHT_OBJECT);
        gLineEdit->addWidget(lineEdit, row, col);
        row++;
    }

    mLineEditsObjects[idFormObject::authenticationLineEditPassword].first->setEchoMode(QLineEdit::EchoMode::Password);


    /// @section QPushButton =======================================================================================================
    QGridLayout *gPushButton = new QGridLayout;
    ui->w_widgetsPushButton->setLayout(gPushButton);

    mPushButtonObjects[idFormObject::authenticationPushButtonRegistration] = {new QPushButton(), "Registration"};
    mPushButtonObjects[idFormObject::authenticationPushButtonSignIn]  = {new QPushButton(), "Sign In"};

    row = 1, col = 1;
    for(const auto &w : mPushButtonObjects){
        QPushButton * pushButton = w.first;
        pushButton->setText(w.second);
        pushButton->setMinimumSize(100, MIN_HEIGHT_OBJECT);
        gPushButton->addWidget(pushButton, row, col);
        col++;
    }

    connect(mPushButtonObjects[idFormObject::authenticationPushButtonSignIn].first, SIGNAL(clicked()), this, SLOT(signInClicked()));
    connect(mPushButtonObjects[idFormObject::authenticationPushButtonRegistration].first, SIGNAL(clicked()), this, SLOT(registrationClicked()));

    /// @section QLabel =======================================================================================================
    QGridLayout *gLabel = new QGridLayout;
    ui->w_widgetsLabel->setLayout(gLabel);

    mLabelObjects[idFormObject::authenticationLabelInformation] = {new QLabel(), "Information"};

    row = 1, col = 1;
    for(const auto &w : mLabelObjects){
        QLabel * label = w.first;
        label->setMinimumSize(300, MIN_HEIGHT_OBJECT);
        label->setStyleSheet("color: #233738");
        gLabel->addWidget(label, row, col);
        col++;
    }
}
