#include "newuserdialog.h"
#include "ui_newuserdialog.h"

NewUserDialog::NewUserDialog(QString dataDir, QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewUserDialog),
    _dataDir(dataDir)
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

    QDialogButtonBox* buttons = this->findChild<QDialogButtonBox*>("buttons");
    buttons->button(QDialogButtonBox::Ok)->setEnabled(false);

    QDialog::show();
}

void NewUserDialog::on_txtUsername_textChanged(const QString &arg1)
{
    QDialogButtonBox* buttons = this->findChild<QDialogButtonBox*>("buttons");
    if(arg1.size() > 0)
        buttons->button(QDialogButtonBox::Ok)->setEnabled(true);
    else
        buttons->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void NewUserDialog::on_buttons_rejected()
{
    this->close();
}

void NewUserDialog::on_buttons_accepted()
{
    QLineEdit* txtUsername = this->findChild<QLineEdit*>("txtUsername");
    dc_user user(_keyPair, txtUsername->text());
    user.save(_dataDir, "");
    this->close();
}
