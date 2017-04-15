#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

#ifdef MACOSX
    _ui->centralWidget->setStyleSheet("font-size:12pt;");
#endif
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
