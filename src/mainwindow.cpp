#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = NULL;
    QObject::connect(client, &decentralised_p2p::connectionEstablished,
                     this, &MainWindow::on_connectionEstablished);
    QObject::connect(client, &decentralised_p2p::dataReceived,
                     this, &MainWindow::on_dataReceived);
    QObject::connect(client, &decentralised_p2p::connectionDropped,
                     this, &MainWindow::on_connectionDropped);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}

void MainWindow::show()
{
    QSettings settings;
    int windowWidth = settings.value("ui/windowWidth").toInt();
    int windowHeight = settings.value("ui/windowHeight").toInt();
    if(windowWidth > 0 && windowHeight > 0)
        this->resize(windowWidth, windowHeight);

    QSplitter* splitterMain = this->findChild<QSplitter*>("splitterMain");
    splitterMain->setSizes(QList<int>() << 400 << 100);

    QMainWindow::show();

    int incomingPort = settings.value("net/incomingPort").toInt();
    if(incomingPort == 0)
    {
        incomingPort = 6453;
        settings.setValue("net/incomingPort", incomingPort);
    }

    terminalWrite(tr("Decentralised Core v1.0.0"), "darkgreen");
    client = new decentralised_p2p(0, incomingPort);
    client->Start();
    terminalWrite(tr("Listening on local port %1 for incoming connections")
                  .arg(QString::number(incomingPort)), NULL);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   QSettings settings;
   settings.setValue("ui/windowWidth", this->width());
   settings.setValue("ui/windowHeight", this->height());
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionLogin_triggered()
{
    login = new LoginDialog(this);
    login->show();
}

void MainWindow::on_actionAbout_Decentralised_triggered()
{
    about = new AboutDialog(this);
    about->show();
}

void MainWindow::on_actionPreferences_triggered()
{
    preferences = new PreferencesDialog(this);
    preferences->show();
}

void MainWindow::on_actionDecentralised_Website_triggered()
{
    QDesktopServices::openUrl(QUrl("http://decentralised-project.org", QUrl::TolerantMode));
}

void MainWindow::on_dataReceived(QByteArray data)
{

}

void MainWindow::on_connectionEstablished()
{

}

void MainWindow::on_connectionDropped()
{

}

void MainWindow::terminalWrite(QString text, QString color)
{
    if(color == NULL)
        color = "#404040";

    QString timeStamp = "[" + QTime::currentTime().toString("HH:mm") + "]";

    QLabel* terminal = this->findChild<QLabel*>("txtTerminal");
    QString existing = terminal->text();
    terminal->setText(QString("%1<div style=\"color:%2;margin-bottom:5px;\">%3 %4</div>")
                      .arg(existing, color, timeStamp, text));
}

void MainWindow::on_txtInput_returnPressed()
{
    QLineEdit* input = this->findChild<QLineEdit*>("txtInput");
    input->clear();
}
