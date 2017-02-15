#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnNewUser_clicked()
{

}
