#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::LoginDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

#ifdef MACOSX
    _ui->frame->setStyleSheet("font-size:12pt;");
#endif
}

LoginDialog::~LoginDialog()
{
    delete _ui;
}

void LoginDialog::on_btnNewUser_clicked()
{
    _newUser = new NewUserDialog(this);
    _newUser->show();
}
