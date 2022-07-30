#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <QString>
#include <QColor>

const QColor COLOR_BLUE = QColor("#90C7CA");
struct ClientInformation{
    uint idUser;
    uint idChat;
    QString username;
};

const int MIN_HEIGHT_OBJECT = 24;
namespace idFormObject{

/// @section registration form
/// 1 - 100
const int registrationLineEditLogin            = 1;
const int registrationLineEditPassword         = 2;
const int registrationLineEditConfirmPassword  = 3;
const int registrationLineEditEmail            = 4;
const int registrationPushButtonCancel         = 5;
const int registrationPushButtonEnter          = 6;
const int registrationLabelInformation         = 7;

/// @section authentication form
/// 101 - 200
const int authenticationLineEditLogin          = 101;
const int authenticationLineEditPassword       = 102;
const int authenticationPushButtonRegistration = 103;
const int authenticationPushButtonSignIn       = 104;
const int authenticationLabelInformation       = 105;

/// @section settingmenu form
/// 201 - 300
const int settingMenuLineEditName              = 201;
const int settingMenuLineEditHost              = 202;
const int settingMenuLineEditPort              = 203;
const int settingMenuPushButtonCancel          = 204;
const int settingMenuPushButtonConnect         = 205;

/// @section client form
/// 301 - 400
const int clientLineEditMessage                = 301;
const int clientTextEditDisplay                = 302;
const int clientPushButtonSendMessage          = 303;
const int clientPushButtonSetting              = 304;
const int clientPushButtonDisconnect           = 305;

};
#endif // PARAMETERS_H
