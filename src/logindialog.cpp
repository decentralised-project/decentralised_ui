#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QString dataDir, QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::LoginDialog),
    _dataDir(dataDir)
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
    _newUser = new NewUserDialog(_dataDir, this);
    _newUser->show();
}

void LoginDialog::on_buttonBox_rejected()
{
    this->close();
}
