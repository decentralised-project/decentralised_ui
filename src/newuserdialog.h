#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include "decentralised_crypt.h"

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent = 0);
    ~NewUserDialog();

    void show();

private:
    Ui::NewUserDialog *_ui;
    decentralised_crypt *_crypt;
};

#endif // NEWUSERDIALOG_H
