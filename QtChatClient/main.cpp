#include "client.h"
#include <QApplication>

#include <QProxyStyle>
#include <QStyleFactory>
#include <QFile>

const QString FONT_FAMILY_APP = "Times";
const uint FONT_SIZE_APP = 9;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    a.setStyle(new QProxyStyle(QStyleFactory::create("Fusion")));
    a.setFont(QFont(FONT_FAMILY_APP, FONT_SIZE_APP));

    QFile styleFile(":/stylesheet/appstyles.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleQSS = styleFile.readAll();
    a.setStyleSheet(styleQSS);

    Client w;
    w.show();

    return a.exec();
}
