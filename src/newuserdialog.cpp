#include "newuserdialog.h"
#include "ui_newuserdialog.h"

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewUserDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    _crypt = new decentralised_crypt(this);
}

NewUserDialog::~NewUserDialog()
{
    delete _ui;
    delete _crypt;
}

void NewUserDialog::show()
{
    QPlainTextEdit* txtPublicKey = this->findChild<QPlainTextEdit*>("txtPublicKey");
    EC_KEY* keyPair = _crypt->generate_key_pair();
    const EC_POINT* pub =_crypt->get_public_key(keyPair);

    txtPublicKey->setPlainText(_crypt->to_base58(pub));

    QDialog::show();
}
