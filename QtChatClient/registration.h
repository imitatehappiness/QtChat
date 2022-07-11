#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog{
    Q_OBJECT
public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
private slots:
    void on_pB_enter_clicked();
public slots:
    void show();

signals:
    void setVisibleLoginForm(bool);
private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
