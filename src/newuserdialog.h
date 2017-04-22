#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include "decentralised_crypt.h"
#include "dc_user.h"

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QString dataDir, QWidget *parent = 0);
    ~NewUserDialog();

    void show();

private slots:
    void on_txtUsername_textChanged(const QString &arg1);

    void on_buttons_rejected();

    void on_buttons_accepted();

private:
    Ui::NewUserDialog *_ui;
    decentralised_crypt *_crypt;
    EC_KEY* _keyPair;
    QString _dataDir;
};

#endif // NEWUSERDIALOG_H
