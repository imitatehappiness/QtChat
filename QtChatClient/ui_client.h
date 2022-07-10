/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lE_inputName;
    QPushButton *pB_connect;
    QTextEdit *tE_allMessage;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lE_inputMessage;
    QPushButton *pB_sendMessage;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(487, 347);
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lE_inputName = new QLineEdit(centralWidget);
        lE_inputName->setObjectName(QStringLiteral("lE_inputName"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lE_inputName->sizePolicy().hasHeightForWidth());
        lE_inputName->setSizePolicy(sizePolicy);
        lE_inputName->setMinimumSize(QSize(40, 24));

        horizontalLayout->addWidget(lE_inputName);

        pB_connect = new QPushButton(centralWidget);
        pB_connect->setObjectName(QStringLiteral("pB_connect"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pB_connect->sizePolicy().hasHeightForWidth());
        pB_connect->setSizePolicy(sizePolicy1);
        pB_connect->setMinimumSize(QSize(100, 24));

        horizontalLayout->addWidget(pB_connect);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tE_allMessage = new QTextEdit(centralWidget);
        tE_allMessage->setObjectName(QStringLiteral("tE_allMessage"));

        gridLayout->addWidget(tE_allMessage, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lE_inputMessage = new QLineEdit(centralWidget);
        lE_inputMessage->setObjectName(QStringLiteral("lE_inputMessage"));
        sizePolicy.setHeightForWidth(lE_inputMessage->sizePolicy().hasHeightForWidth());
        lE_inputMessage->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lE_inputMessage);

        pB_sendMessage = new QPushButton(centralWidget);
        pB_sendMessage->setObjectName(QStringLiteral("pB_sendMessage"));
        sizePolicy1.setHeightForWidth(pB_sendMessage->sizePolicy().hasHeightForWidth());
        pB_sendMessage->setSizePolicy(sizePolicy1);
        pB_sendMessage->setMinimumSize(QSize(100, 24));

        horizontalLayout_2->addWidget(pB_sendMessage);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        Client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 487, 20));
        Client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Client->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client->setStatusBar(statusBar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", nullptr));
        pB_connect->setText(QApplication::translate("Client", "Connect", nullptr));
        pB_sendMessage->setText(QApplication::translate("Client", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
