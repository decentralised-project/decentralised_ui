#include "newuserdialog.h"
#include "ui_newuserdialog.h"

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

#ifdef MACOSX
    _ui->centralWidget->setStyleSheet("font-size:12pt;");
#endif
}

NewUserDialog::~NewUserDialog()
{
    delete ui;
}

void NewUserDialog::show()
{
    QLabel* txtPublicKey = this->findChild<QLabel*>("txtPublicKey");
    txtPublicKey->setText("Key");

    QDialog::show();
}
