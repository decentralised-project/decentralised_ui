#include "newuserdialog.h"
#include "ui_newuserdialog.h"

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewUserDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    _keyPair = NULL;
    _crypt = new decentralised_crypt(this);
}

NewUserDialog::~NewUserDialog()
{
    delete _ui;
    delete _crypt;
    if(_keyPair)
        EC_KEY_free(_keyPair);
}

void NewUserDialog::show()
{
    QPlainTextEdit* txtPublicKey = this->findChild<QPlainTextEdit*>("txtPublicKey");
    _keyPair = _crypt->generate_key_pair();
    const EC_POINT* pub =_crypt->get_public_key(_keyPair);

    txtPublicKey->setPlainText(_crypt->to_base58(pub));

    QDialog::show();
}

void NewUserDialog::on_txtUsername_textChanged(const QString &arg1)
{
    QLineEdit* txtUsername = this->findChild<QLineEdit*>("txtUsername");
    if(txtUsername->text().size() > 0)
    {
        QDialogButtonBox* buttons = this->findChild<QDialogButtonBox*>("buttons");
        buttons->setEnabled(true);
    }
}

void NewUserDialog::on_buttons_rejected()
{
    this->close();
}

void NewUserDialog::on_buttons_accepted()
{
    QLineEdit* txtUsername = this->findChild<QLineEdit*>("txtUsername");
    dc_user user(_keyPair, txtUsername->text());
    user.save("X:/decentralised_ui/", "");
}
