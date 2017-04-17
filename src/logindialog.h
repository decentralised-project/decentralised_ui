#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "newuserdialog.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:

    void on_btnNewUser_clicked();

    void on_buttonBox_rejected();

private:
    Ui::LoginDialog *_ui;
    NewUserDialog *_newUser;
};

#endif // LOGINDIALOG_H
