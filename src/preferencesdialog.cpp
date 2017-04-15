#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::PreferencesDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    _ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    QString dataDir = _settings.getDataDirectory();
    QLabel* txtDataDirectory = this->findChild<QLabel*>("txtDataDirectory");
    txtDataDirectory->setText(dataDir);

    QString lang = _settings.getLanguage();
    QComboBox* drpLanguage = this->findChild<QComboBox*>("drpLanguage");
    drpLanguage->setCurrentText(lang);

    int incomingPort = _settings.getIncomingPort();
    QSpinBox* txtIncomingPort = this->findChild<QSpinBox*>("txtIncomingPort");
    txtIncomingPort->setValue(incomingPort);

#ifdef MACOSX
    _ui->centralWidget->setStyleSheet("font-size:12pt;");
#endif
}

PreferencesDialog::~PreferencesDialog()
{
    delete _ui;
}

void PreferencesDialog::on_buttonBox_accepted()
{
    QLabel* txtDataDirectory = this->findChild<QLabel*>("txtDataDirectory");
    _settings.setDataDirectory(txtDataDirectory->text());

    QSpinBox* txtIncomingPort = this->findChild<QSpinBox*>("txtIncomingPort");
    _settings.setIncomingPort(txtIncomingPort->value());

    QComboBox* drpLanguage = this->findChild<QComboBox*>("drpLanguage");
    _settings.setLanguage(drpLanguage->currentText());
}
